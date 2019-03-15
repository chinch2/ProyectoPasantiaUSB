#include <EEPROM.h>
#include <EtherCard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Key.h>
#include <Keypad.h>
#include <ctype.h>
#define LED 6 //led del teensy 2.0
//-------Escribo IP default en la EEPROM----
void updateIP(String inString[4]);
//-------Busco IP default en la EEPROM------
void readIP();
//-----------Ethernet-------------------------
// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
const char website[] PROGMEM = "10.20.184.70";
String request;//char request[30];
byte Ethernet::buffer[400];
static uint32_t timer = 0;
bool onrequest = false;
char requestc[50];
//int printStatus = 0;
String configuracion[5];
String IPROM = "";
//------------Display---------------------

// Inicializar el LCD
int DTYPE = 0X27,//configuracion[2].toInt(),
    DCOLS = 20,//configuracion[3].toInt(),
    DROWS = 2;//configuracion[4].toInt();
LiquidCrystal_I2C lcd(DTYPE, DCOLS, DROWS); //creacion de objeto
//-----------Escaner e impresora----------------
char c;
String buff = "";//char buff[8];
const int dispara = 18;
//-------------Teclado-----------------------
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {10, 11, 12, 13}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {14, 15, 16, 17}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
unsigned int pagos[3] = {0, 0, 0};
String mensa[3] = {"Pago tarjeta", "Pago Efectivo", "Pago Otros"};
unsigned int monto;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  buff = "";//buff[0] = '\0';
  Serial.println(F("\n[webClient]"));
  Serial.print("MAC: ");
  for (byte i = 0; i < 6; ++i) {
    Serial.print(mymac[i], HEX);
    if (i < 5)
      Serial.print(':');
  }

  Serial.println("\nProceding to access Ethernet Controller\r\n");
  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, 20) == 0) {
    Serial.println(F("Failed to access Ethernet controller"));
  }

  Serial.println("\r\nDHCP...\r\n\r\n");
  if (!ether.dhcpSetup()) {
    Serial.println(F("DHCP failed"));
  }

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  String IPdef[] = {"10", "20", "184", "70"};
  readIP();
  String IPnative = "10.20.184.70";
  //----Buscar en la EEPROM la ip default y compararla con la que se esta usando-----
  if (IPROM != IPnative) { //EEPROM vacia
    //ESCRIBO EN MI EEPROM LA IP DEL SERVIDOR, SOLO EJECUTAR UNA SOLA VEZ
    Serial.println();
    Serial.println("EEPROM distinta, actualizando");
    updateIP(IPdef); // Si IPdef es diferente a la que esta guardada la escribe sino no
    delay(1000);
    Serial.print("reseteando. EEPROM actualizada");
    asm("jmp 0x0000");
  }
  Serial.println("IP en la EPPROM: " + IPROM);
  int ip[4];
  for (int i = 0; i < 4; i++) {
    ip[i] = EEPROM.read(i);
    //ip[i] = IPdef[i].toInt();
    ether.hisip[i] = ip[i];//IPdef[i].toInt();
  }
  ether.printIp("Server: ", ether.hisip);
  Serial.println("Solicitando configuracion inicial...");
  //----Configuracion inicial-----------
  //IPROM.toCharArray(website, IPROM.length() + 1);
  //Serial.println(IPROM);
  //Serial.println(website);
  int x = 0;
  onrequest = true;
  timer = 0;
  while (onrequest) {
    ether.packetLoop(ether.packetReceive());

    if (millis() > timer) {
      timer = millis() + 5000;
      Serial.println();
      Serial.print("<<< REQ de setup");
      ether.browseUrl(PSTR("/setup.php"), "?t=3", website, my_callback);
      x++;
      if (x > 5) {
        Serial.println("Fallo request");
        onrequest = false;
      }
    }
  }
  //Verifico que la IP de servidor no haya cambiado, si es asi actualizo
  //la EPPROM y reseteo
  Serial.println();
  Serial.println("IP en la EPPROM: " + IPROM);
  Serial.println("IP actual: " + configuracion[0]);
  if (configuracion[0] != IPROM) {
    Serial.print("Actualizando EPPROM con nueva IP: ");
    String IPnueva[4];
    int i = 0, r = 0, t = 0;
    for (i = 0; i < configuracion[0].length(); i++) {
      if (configuracion[0].charAt(i) == '.') {
        IPnueva[t] = configuracion[0].substring(r, i);
        r = (i + 1);
        t++;
      }
    }
    for (int k = 0; k < 4; k++) {
      Serial.println(IPnueva[k]);
    }
    Serial.println("Guardando nueva IP en la EPPROM");
    updateIP(IPnueva);
    Serial.print("Guardada nueva IP en la EPPROM: ");
    for (int k = 0; k < 4; k++) {
      Serial.print(IPnueva[k]);
      if (k < 3) {
        Serial.print(".");
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    ip[i] = EEPROM.read(i);
    //ip[i] = IPdef[i].toInt();
    ether.hisip[i] = ip[i];//IPdef[i].toInt();
  }
  ether.printIp("Server: ", ether.hisip);
  //Inicializando los pines de entrada y salida
  pinMode(dispara, OUTPUT); //Trigger del escaner
  pinMode(LED, OUTPUT);  //Teensy
  Serial.println("Botones inicializados");
  Serial1.begin(configuracion[1].toInt());
  //inicializo la pantalla
  lcd.init();
  //Limpiar la pantalla
  lcd.clear();
  Serial.println("Pantalla inicializada");
  delay(1000);
}

void loop() {

  if (Serial1.available()) {
    c = Serial1.read();
    //Serial.print(c);
    // if( c == 10) Serial.print("hubo r");
    // if( c == 13) Serial.print("hubo n");
    if ( c == 13) {
      //const char *req = "?id=";
      //strcpy(request,req);
      //strcat(request,buff);
      request = "?estacion=1&id=" + buff; // put your main code here, to run repeatedly:
      request.toCharArray(requestc, request.length() + 1);
      Serial.println(request);
      Serial.println(requestc);
      int x = 0;
      onrequest = true;
      timer = 0;
      while (onrequest) {
        ether.packetLoop(ether.packetReceive());

        if (millis() > timer) {
          timer = millis() + 5000;
          Serial.println("Request de salida");
          Serial.print("<<< REQ ");
          Serial.print(requestc);
          ether.browseUrl(PSTR("/salida.php"), requestc, website, my_callback);
          x++;
          if (x > 5) {
            Serial.println("Fallo request");
            onrequest = false;
            buff = "";
          }
        }
      }
      buff = "";//buff[j] = '\0';
    } else {//strcat(buff,c);//buff=buff+c;
      buff = buff + c;//buff[j] = c;
      //buff[j+1] = '\0';
      //j++;
    }
  }
}
// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  //Serial.println("callback" + status);
  onrequest = false;
  Serial.print(">>>");
  Ethernet::buffer[off + len] = 0;
  //Serial.print((const char*) Ethernet::buffer + off);
  String salida = (const char*) Ethernet::buffer + off;
  //salida = salida.substring(0);
  Serial.print(salida);
  int pos =   salida.indexOf("\r\n\r\n") + 4;
  salida = salida.substring(pos);
  while (salida.length() > 0) {
    int fin = salida.indexOf("-end");
    if (fin == 0) salida = "";
    String salcomando = salida.substring(0, fin);
    Serial.println(salcomando);
    comando(salcomando);
    //Serial.println();
    //Serial.print(salida1);
    salida = salida.substring(fin + 4);
    //Serial.print(salida1);
  }
}

void comando(String cmd) {
  String cmd1 = cmd.substring(0, 5);
  String cmd2 = cmd.substring(5);
  Serial.println("\r\ncomando:" + cmd + " modo:" + cmd1 + " argumento:" + cmd2);
  if (cmd1 == "-disp") {
    Serial.println(cmd2);
    Pantalla(cmd2);
  }
  /*if (cmd1 == "-prin") {
    Imprimir(cmd);
    }*/
  if (cmd1 == "-barr") {
    Serial.print("Habriendo barrera");
  }
  if (cmd1 == "-conf") {
    Serial.println("Empezando conf");
    conf(cmd2);
  }
  /*if (cmd1 == "-pago") {
    String salida1 = cmd2;
    monto = salida1.toInt();
    Serial.print("Monto a pagar: ");
    Serial.println(monto);
    modopago(monto);
    }*/
}

void conf(String arg) {
  int i = 0, r = 0, t = 0;
  for (i = 0; i < arg.length(); i++) {
    if (arg.charAt(i) == ',') {
      configuracion[t] = arg.substring(r, i);
      r = (i + 1);
      t++;
    }
  }
  for (int k = 0; k < 5; k++) {
    Serial.println(configuracion[k]);
  }
}

//---------Imprimir en Display-----------------
void Pantalla(String muestra) {
  //----------------LCD DISPLAY--------------------------

  //Encender la luz de fondo.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(muestra.substring(0, DCOLS));
  lcd.setCursor(0, 1);
  lcd.print(muestra.substring(DCOLS, DCOLS * 2));
}

void updateIP(String inString[4])
{
  int ip[4];
  int m;
  int i;
  int n;
  Serial.print("Guardando IP en la EEPROM: ");
  for (m = 0; m < 4; m++) {
    Serial.print(inString[m]);
    if (m < 3) {
      Serial.print(".");
    }
  }
  Serial.print("\r\n");

  for (i = 0; i < 4; i++) {
    ip[i] = inString[i].toInt();
    EEPROM.update(i, ip[i]);
  }
  Serial.print("Guardada en EEPROM IP: ");
  for (n = 0; n < 4; n++) {
    Serial.print(EEPROM.read(n));
    if (n < 3) {
      Serial.print(".");
    }
  }
  Serial.println();
}

void readIP() {

  int j;
  for (j = 0; j < 4; j++) {
    IPROM = IPROM + (String)EEPROM.read(j);
    if (j < 3) {
      IPROM = IPROM + ".";
    }
  }
}
