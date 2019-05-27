#include <EEPROM.h>
#include <EtherCard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Key.h>
#include <Keypad.h>
#include <ctype.h>

#define joseduino

#ifdef joseduino

#define LED 0
#define button_1 1
#define button_2 2
#define tr1 12
#define tr2 13
#define tr3 14
#define tr4 15
#define tc1 18
#define tc2 19
#define tc3 20
#define tc4 21
#define papel 24
#define dispara 25
#define barrera 26
#define RXS1 22
#define TXS1 23
#define RXS2 27
#define TXS2 28
#define ss 3

#else //Para teensy++ 2.0

#define LED 6
#define button_1 8
#define button_2 9
#define tr1 10
#define tr2 11
#define tr3 12
#define tr4 13
#define tc1 14
#define tc2 15
#define tc3 16
#define tc4 17
#define papel 38
#define dispara 39
#define barrera 40
#define RXS1 24
#define TXS1 25
#define RXS2 26
#define TXS2 27
#define ss 20

#endif
//-------Escribo IP default en la EEPROM----
void updateIP(String inString[4]);
//-------Busco IP default en la EEPROM------
void readIP();
//-----------Ethernet-------------------------
// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x32 };
const char website[] PROGMEM = "192.168.1.102";
String request;//char request[30];
String prequest;
byte Ethernet::buffer[400];
static uint32_t timer = 0;
bool onrequest = false;
bool ponrequest = false;
char requestc[15];
char prequestc[100];
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
//-------------Teclado-----------------------
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {tr1, tr2, tr3, tr4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {tc1, tc2, tc3, tc4}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
unsigned int pagos[3] = {0, 0, 0};
String mensa[3] = {"Pago tarjeta", "Pago Efectivo", "Pago Otros"};
unsigned int monto;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  delay(1000);
  buff = "";//buff[0] = '\0';
  Serial1.println(F("\n[webClient]"));
  Serial1.print("MAC: ");
  for (byte i = 0; i < 6; ++i) {
    Serial1.print(mymac[i], HEX);
    if (i < 5)
      Serial1.print(':');
  }

  Serial1.println("\nProceding to access Ethernet Controller\r\n");
  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, ss) == 0) {
    Serial1.println(F("Failed to access Ethernet controller"));
  }

  Serial1.println("\r\nDHCP...\r\n\r\n");
  if (!ether.dhcpSetup()) {
    Serial1.println(F("DHCP failed"));
  }

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  String IPdef[] = {"192", "168", "1", "102"};
  readIP();
  String IPnative = "192.168.1.102";
  //----Buscar en la EEPROM la ip default y compararla con la que se esta usando-----
  if (IPROM != IPnative) { //EEPROM vacia
    //ESCRIBO EN MI EEPROM LA IP DEL SERVIDOR, SOLO EJECUTAR UNA SOLA VEZ
    Serial1.println();
    Serial1.println("EEPROM distinta, actualizando");
    updateIP(IPdef); // Si IPdef es diferente a la que esta guardada la escribe sino no
    delay(1000);
    Serial1.print("reseteando. EEPROM actualizada");
    asm("jmp 0x0000");
  }

  Serial1.println("IP en la EPPROM: " + IPROM);
  int ip[4];
  for (int i = 0; i < 4; i++) {
    ip[i] = EEPROM.read(i);
    //ip[i] = IPdef[i].toInt();
    ether.hisip[i] = ip[i];//IPdef[i].toInt();
  }
  ether.printIp("Server: ", ether.hisip);
  Serial1.println("Solicitando configuracion inicial...");
  //----Configuracion inicial-----------
  //IPROM.toCharArray(website, IPROM.length() + 1);
  //Serial1.println(IPROM);
  //Serial1.println(website);
  int x = 0;
  onrequest = true;
  timer = 0;
  while (onrequest) {
    ether.packetLoop(ether.packetReceive());

    if (millis() > timer) {
      timer = millis() + 5000;
      Serial1.println();
      Serial1.print("<<< REQ de setup");
      ether.browseUrl(PSTR("/setup.php"), "?t=2", website, my_callback);
      x++;
      if (x > 5) {
        Serial1.println("Fallo request");
        onrequest = false;
      }
    }
  }
  //Verifico que la IP de servidor no haya cambiado, si es asi actualizo
  //la EPPROM y reseteo
  Serial1.println();
  Serial1.println("IP en la EPPROM: " + IPROM);
  Serial1.println("IP actual: " + configuracion[0]);
  if (configuracion[0] != IPROM) {
    Serial1.print("Actualizando EPPROM con nueva IP: ");
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
      Serial1.print(IPnueva[k]);
      if ( k < 3 ) {
        Serial1.print(".");
      }
    }
    Serial1.println();
    Serial1.println("Guardando nueva IP en la EPPROM");
    updateIP(IPnueva);
    Serial1.print("Guardada nueva IP en la EPPROM: ");
    for (int k = 0; k < 4; k++) {
      Serial1.print(IPnueva[k]);
      if (k < 3) {
        Serial1.print(".");
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
  Serial1.println("Botones inicializados");
  Serial.begin(configuracion[1].toInt());
  // Inicializar el LCD
  lcd.init();
  //Limpiar la pantalla
  lcd.clear();
  Serial1.println("Pantalla inicializada");
  delay(1000);
}

void loop() {
  digitalWrite(dispara, HIGH);
  delay(300);
  if (analogRead(papel) > 50) {
    digitalWrite(dispara, LOW);
    delay(300);
  }
  if (Serial.available()) {
    c = Serial.read();
    //Serial1.print(c);
    // if( c == 10) Serial1.print("hubo r");
    // if( c == 13) Serial1.print("hubo n");
    if ( c == 13) {
      //const char *req = "?id=";
      //strcpy(request,req);
      //strcat(request,buff);
      request = "?id=" + buff; // put your main code here, to run repeatedly:
      request.toCharArray(requestc, request.length() + 1);
      Serial1.println(request);
      Serial1.println(requestc);
      int x = 0;
      onrequest = true;
      timer = 0;
      while (onrequest) {
        ether.packetLoop(ether.packetReceive());

        if (millis() > timer) {
          timer = millis() + 5000;
          Serial1.println("Request de consulta");
          Serial1.print("<<< REQ ");
          Serial1.print(requestc);
          ether.browseUrl(PSTR("/consulta.php"), requestc, website, my_callback);
          x++;
          if (x > 5) {
            Serial1.println("Fallo request");
            onrequest = false;
            buff = "";
          }
        }
      }
    } else {//strcat(buff,c);//buff=buff+c;
      buff = buff + c;//buff[j] = c;
      //buff[j+1] = '\0';
      //j++;
    }
  }
}
// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  //Serial1.println("callback" + status);
  onrequest = false;
  ponrequest = false;
  Serial1.print(">>>");
  Ethernet::buffer[off + len] = 0;
  //Serial1.print((const char*) Ethernet::buffer + off);
  String salida = (const char*) Ethernet::buffer + off;
  //salida = salida.substring(0);
  Serial1.print(salida);
  int pos =   salida.indexOf("\r\n\r\n") + 4;
  salida = salida.substring(pos);
  while (salida.length() > 0) {
    int fin = salida.indexOf("-end");
    if (fin == 0) salida = "";
    String salcomando = salida.substring(0, fin);
    Serial1.println(salcomando);
    comando(salcomando);
    //Serial1.println();
    //Serial1.print(salida1);
    salida = salida.substring(fin + 4);
    //Serial1.print(salida1);
  }

}

void comando(String cmd) {
  String cmd1 = cmd.substring(0, 5);
  String cmd2 = cmd.substring(5);
  Serial1.println("\r\ncomando:" + cmd + " modo:" + cmd1 + " argumento:" + cmd2);
  if (cmd1 == "-disp") {
    Serial1.println(cmd2);
    Pantalla(cmd2);
  }
  /*if (cmd1 == "-prin") {
    Imprimir(cmd);
    }*/
  if (cmd1 == "-barr") {
    Serial1.print("Habriendo barrera");
  }
  if (cmd1 == "-conf") {
    Serial1.println("Empezando conf");
    conf(cmd2);
  }
  if (cmd1 == "-pago") {
    String salida1 = cmd2;
    monto = salida1.toInt();
    Serial1.print("Monto a pagar: ");
    Serial1.println(monto);
    modopago(monto);
  }
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
    Serial1.println(configuracion[k]);
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

void modopago(unsigned int mnt) {
  Serial1.println("Modo pago iniciado");
  String teclado = "";
  bool respuesta = true;
  unsigned int cmb;
  pagos[0] = 0;
  pagos[1] = 0;
  pagos[2] = 0;
  while (respuesta) {

    char key = keypad.getKey();
    Serial1.print(key);
    switch (key)
    {
      case 'A':
      case 'B':
      case 'C': {
          pagos[key - 65] = teclado.toInt();
          teclado = "";
          Pantalla(mensa[key - 65]);
        } break;
      case 'D': {
          teclado = "";
          Serial1.println("Enter");
          if (mnt > pagos[0] + pagos[1] + pagos[2]) {
            Pantalla("Monto incompleto");

          } else {
            Pantalla("Procesando");
            cmb = (pagos[0] + pagos[1] + pagos[2]) - mnt;
            respuesta = false;
            requestpago(cmb);
            buff = "";//buff[j] = '\0';
            Serial1.println("Modo pago finalizado");

          }
        } break;
      case '#': {
          teclado = "";
          buff = "";//buff[j] = '\0';
          Serial1.println("Modo pago finalizado");
          Pantalla("Cancelado");
          respuesta = false;
        } break;
      case '*': {
          teclado = "";
          Pantalla("");
        } break;
      default:

        if (isDigit(key)) {
          teclado = teclado + key;
          Pantalla(teclado);
        }
        break;
    }
  }
}

void requestpago(unsigned int cambio) {
  String change = String(cambio);
  prequest = "?id=" + buff + "&pa=" + pagos[0] + "&pb=" + pagos[1] + "&pc=" + pagos[2] + "&cambio=" + change; // put your main code here, to run repeatedly:
  prequest.toCharArray(prequestc, prequest.length() + 1);
  Serial1.println(prequest);
  Serial1.println(prequestc);
  int x = 0;
  ponrequest = true;
  timer = 0;
  while (ponrequest) {
    ether.packetLoop(ether.packetReceive());

    if (millis() > timer) {
      timer = millis() + 5000;
      Serial1.println("Request de pago");
      Serial1.print("<<< REQ: ");
      Serial1.print(prequestc);
      ether.browseUrl(PSTR("/pago.php"), prequestc, website, my_callback);
      x++;
      if (x > 5) {
        Serial1.print("Fallo request");
        ponrequest = false;
      }
    }
  }
}

void updateIP(String inString[4])
{
  int ip[4];
  int m;
  int i;
  int n;
  Serial1.print("Guardando IP en la EEPROM: ");
  for (m = 0; m < 4; m++) {
    Serial1.print(inString[m]);
    if (m < 3) {
      Serial1.print(".");
    }
  }
  Serial1.print("\r\n");

  for (i = 0; i < 4; i++) {
    ip[i] = inString[i].toInt();
    EEPROM.update(i, ip[i]);
  }
  Serial1.print("Guardada en EEPROM IP: ");
  for (n = 0; n < 4; n++) {
    Serial1.print(EEPROM.read(n));
    if (n < 3) {
      Serial1.print(".");
    }
  }
  Serial1.println();
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
