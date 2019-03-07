#include <EEPROM.h>
#include <EtherCard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LED 11 //led del teensy 2.0

//-------Escribo IP default en la EEPROM----
void updateIP(String inString[4]);
//-------Busco IP default en la EEPROM------
String readIP();
//-----------Ethernet-------------------------
// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
const char website[] PROGMEM = "10.20.184.70";
byte Ethernet::buffer[400];
static uint32_t timer;
bool onrequest = false;
int printStatus = 0;
String configuracion[5];
//-------------------------Display-----------                                                                                                                                                                                                                      ----------
const byte DCOLS = 8; //four columns
const byte DROWS = 2; //four columns

LiquidCrystal_I2C lcd(0x3f, DCOLS, DROWS); //en caso de ser 16x2
//LiquidCrystal_I2C lcd(0x27, DCOLS, DROWS);//en caso de ser 20x2

// El numero de los pines (constantes siempre):

const int button_1 = 20;
const int button_2 = 21;

//Variables que cambian:
//int boton1 = 0; //Variables para leer el estatus de los botones
//int boton2 = 0;
static void my_callback (byte status, word off, word len);

void setup()
{ //char website[15] PROGMEM;

  Serial.begin(9600);

  Serial1.begin(9600);
  delay(1000);
  Serial.println(F("\n[webClient]"));
  Serial.print("MAC: ");
  for (byte i = 0; i < 6; ++i) {
    Serial.print(mymac[i], HEX);
    if (i < 5)
      Serial.print(':');
  }

  Serial.println("\nProceding to access Ethernet Controller\r\n");

  // Change 'SS' to your Slave Select pin, if you arn't using the default pin

  if (ether.begin(sizeof Ethernet::buffer, mymac, 0) == 0) {
    Serial.println(F("Failed to access Ethernet controller"));
  }

  Serial.println("\r\nDHCP...\r\n\r\n");
  if (!ether.dhcpSetup()) {
    Serial.println(F("DHCP failed"));
  }

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  String IPdef[] = {"10", "20", "184", "70"};

  //----Buscar en la EEPROM la ip default y compararla con la que se esta usando-----
  //if (EEPROM.read(0) == 255) { //EEPROM vacia
  //ESCRIBO EN MI EEPROM LA IP DEL SERVIDOR, SOLO EJECUTAR UNA SOLA VEZ
  updateIP(IPdef); // Si IPdef es diferente a la que esta guardada la escribe sino no
  delay(1000);
  int ip[4];
  for (int j = 0; j < 4; j++) {
    ip[j] = EEPROM.read(j);
    ether.hisip[j] = ip[j];
  }
  ether.printIp("Server para configuracion inicial: ", ether.hisip);
  Serial.println("Solicitando configuracion inicial desde la EEPROM...");
  String IPROM = readIP();
  //----Configuracion inicial-----------
  // IPROM.toCharArray(website, IPROM.length() + 1);
  Serial.println(IPROM);
  Serial.println(website);
  int x = 0;
  onrequest = true;
  timer = 0;
  while (onrequest) {
    ether.packetLoop(ether.packetReceive());

    if (millis() > timer) {
      timer = millis() + 3000;
      Serial.println();
      Serial.print("<<< REQ ");
      ether.browseUrl(PSTR("/setup.php"), "", website, my_callback);
      x++;
      if (x > 5) {
        Serial.println("Fallo request");
        onrequest = false;
      }
    }
  }
  //Inicializando los pines de entrada y salida
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);  //Teensy
  Serial.println("Botones inicializados");
  //digitalWrite(LED_BUILTIN, LOW);
  // Inicializar el LCD
  lcd.init();
  //Limpiar la pantalla
  lcd.clear();
  Serial.println("Pantalla inicializada");
}

void loop()
{ char website[15] PROGMEM;

  //----Configuracion inicial-----------
  /*if(confonreq){
    while(confonreq){
    ether.packetLoop(ether.packetReceive());
    if (millis() > timer) {
    timer = millis() + 4000;
    Serial.println("Solicitando configuracion inicial...");
    Serial.println();
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR("/setup.php"), "", website, my_callback);
    }
    }
    }*/
  //----Configuracion inicial--------------
  //boton1 = digitalRead(button_1);
  //boton2 = digitalRead(button_2);
  //delay(1000);
  //Serial.print(boton1);
  //Serial.print(boton2);
  //delay(1000);
  if (digitalRead(button_1) == HIGH && digitalRead(button_2) == HIGH) {  //No hay nadie
    //-----------------------------------GET REQUEST 3-------------------------------------------------------------
    ether.packetLoop(ether.packetReceive());
    if (millis() > timer) {
      timer = millis() + 4000;
      Serial.println();
      Serial.print("<<< REQ ");
      ether.browseUrl(PSTR("/standby.php"), "?carro=0&estacion=1", website, my_callback);
    }

  }

  if (digitalRead(button_1) == LOW && digitalRead(button_2) == HIGH) {  //Hay alguien
    //-----------------------------------GET REQUEST 3-------------------------------------------------------------
    ether.packetLoop(ether.packetReceive());
    if (millis() > timer) {
      timer = millis() + 2000;
      Serial.println();
      Serial.print("<<< REQ ");
      ether.browseUrl(PSTR("/standby.php"), "?carro=1&estacion=1", website, my_callback);
    }

  }

  if (digitalRead(button_1) == LOW && digitalRead(button_2) == LOW) {  //Entro alguien
    //-----------------------------------GET REQUEST 3-------------------------------------------------------------
    ether.packetLoop(ether.packetReceive());
    if (millis() > timer) {
      timer = millis() + 1000;
      Serial.println();
      Serial.print("<<< REQ ");
      ether.browseUrl(PSTR("/ticket.php"), "?estacion=1", website, my_callback);
    }

  }

}
// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  //onrequest = false;
  //confonreq = false;
  Serial.println(">>>");
  Ethernet::buffer[off + len] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  String salida = (const char*) Ethernet::buffer + off;
  int pos =   salida.indexOf("\r\n\r\n") + 4;
  String salida1 = salida.substring(pos);
  while (salida1.length() > 0) {
    int fin = salida1.indexOf("-end");
    if (fin == 0) salida1 = "";
    String action = salida1.substring(0, fin);
    Serial.print(action);
    comando(action);
    //Serial.println();
    //Serial.print(salida1);
    salida1 = salida1.substring(fin + 4);
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
  if (cmd1 == "-prin") {
    Imprimir(cmd);
  }
  if (cmd1 == "-barr") {
    Serial.print("Habriendo barrera");
  }
  if (cmd1 == "-conf") {
    Config(cmd2);
  }
  /*if (cmd1 == "-pago") {
    String salida1 = cmd2;
    monto = salida1.toInt();
    Serial.print("Monto a pagar: ");
    Serial.println(monto);
    modopago(monto);
    }*/
}

void Config(String arg) {
  int i = 0;
  while (arg.length() > 0) {
    int p =   arg.indexOf(",");
    if (p == 0) arg = "";
    configuracion[i] = arg.substring(0, p);
    arg = arg.substring(p + 1);
    i++;
  }
  for (int k = 0; k < 5; k++) {
    Serial.print(k);
    Serial.println(configuracion[k]);
  }
}

//---------Imprimir en Display-----------------
void Pantalla(String salida1) {
  //----------------LCD DISPLAY--------------------------

  //Encender la luz de fondo.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(salida1.substring(0, DCOLS));
  lcd.setCursor(0, 1);
  lcd.print(salida1.substring(DCOLS, DCOLS * 2));
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(salida1.substring(DCOLS * 2, DCOLS * 3));
  lcd.setCursor(0, 1);
  lcd.print(salida1.substring(DCOLS * 3, DCOLS * 4));
  delay(1500);
}

void Imprimir(String printed) {
  Serial.print("Imprimiendo...");
  String Imprime = printed.substring(5);
  String codificado = Imprime.substring(21);
  Serial.print(Imprime);
  Serial.println(codificado);
  //IMPRIMIENDO----------------------------------------------------------------------
  digitalWrite(LED, HIGH);
  //TM88.start();
  //TM88.justifyCenter();
  Serial1.write("\x1B\x61\x01");
  //TM88.println(Imprime);
  Serial1.println(Imprime);
  //TM88.barcodeHeight(50);
  Serial1.write("\x1D\x68\x32");
  //TM88.barcodeWidth(3);
  Serial1.write("\x1D\x77\x03");
  //TM88.barcodeNumberPosition(2);
  Serial1.write("\x1D\x48\x02");

  //TM88.printBarcode(70,8);
  Serial1.write("\x1d\x6b\x46\x08");
  //TM88.println(codificado);
  Serial1.println(codificado);
  //TM88.feed(5);
  Serial1.write("\n\n\n\n\n\n");
  //TM88.cut();
  //mySerial.write("\x1D\x56\x42\x0A");
  digitalWrite(LED, LOW);
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
}

String readIP() {
  String myipdef = "";
  int j;
  Serial.println("Leyendo IP de la EEPROM: ");
  for (j = 0; j < 4; j++) {
    myipdef = myipdef + (String)EEPROM.read(j);
    if (j < 3) {
      myipdef = myipdef + ".";
    }
  }
  return myipdef;
}
