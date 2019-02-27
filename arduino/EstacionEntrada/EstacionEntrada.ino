#include <EEPROM.h>
#include <EtherCard.h>
//#include "thermalprinter.h"
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LED 11 //led del teensy 2.0
#define rxPin 14  //serial que viene del escaner
#define txPin 13 //serial que va a la impresora
//-------Escribo IP default en la EEPROM----
void updateIP(String inString[4]);
//-------Busco IP default en la EEPROM------
String read_String(char add);
//-----------Ethernet-------------------------
// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
const char website[] PROGMEM = "10.20.184.70";
byte Ethernet::buffer[700];
static uint32_t timer;
//bool confonreq = true;
//bool onrequest = false;
int printStatus = 0;
//-------------------------Display-----------                                                                                                                                                                                                                      ----------

//Crear el objeto lcd  dirección  0x3f y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3f, 16, 2);

//----------------------Impresora------------------------
//Crear la nueva interfaz serial para la impresora
//NewSoftSerial mySerial(14, 13);// Rx  Tx  por ahora no sirve
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
//Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
//Epson TM88 = Epson(rxPin, txPin); // init the Printer with Output-Pin


// El numero de los pines (constantes siempre):

const int button_1 = 21;
const int button_2 = 20;
const int RESET = 12; //Hardware reset para el ESP8266

//Variables que cambian:
//int boton1 = 0; //Variables para leer el estatus de los botones
//int boton2 = 0;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
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
  if (ether.begin(sizeof Ethernet::buffer, mymac, 8) == 0) {
    Serial.println(F("Failed to access Ethernet controller"));
  } else Serial.println(F("Ethernet controller access success"));
  Serial.println("\r\nDHCP...\r\n\r\n");
  if (!ether.dhcpSetup()) {
    Serial.println(F("DHCP failed"));
  } else Serial.println(F("DHCP success"));
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  String IPdef[] = {"10", "20", "184", "70"};
  //----Buscar en la EEPROM la ip default y compararla con la que se esta usando-----
  /*if(EEPROM.read(0) == 255){//EEPROM vacia
    //ESCRIBO EN MI EEPROM LA IP DEL SERVIDOR, SOLO EJECUTAR UNA SOLA VEZ
    updateIP(IPdef); // Si IPdef es diferente a la que esta guardada la escribe sino no
    delay(1000);
    for(int j=0; j<4; j++){
      ether.hisip[j] = EEPROM.read(j);
    }
    ether.printIp("Server: ", ether.hisip);
    Serial.println("Solicitando configuracion inicial desde la EEPROM...");
    //----Configuracion inicial-----------
    ether.packetLoop(ether.packetReceive());

    if (millis() > timer) {
    timer = millis() + 3000;
    Serial.println();
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR("/setup.php"), "", website, my_callback);
    }
    //----Configuracion inicial--------------
    }else{*/
  int ip[4];
  for (int i = 0; i < 4; i++) {
    ip[i] = IPdef[i].toInt();
    ether.hisip[i] = ip[i];//IPdef[i].toInt();
  }
  ether.printIp("Server: ", ether.hisip);
  //}
  /*String recivedData;
    recivedData = read_String(0);

    Serial.print("recivedData:");
    Serial.println(recivedData);
    //const char *websiteIP = recivedData.c_str();
    Serial.println(websiteIP);*/
  //Inicializando los pines de entrada y salida
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(RESET, OUTPUT); //Teensy con ESP8266
  pinMode(LED, OUTPUT);  //Teensy
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.println("Botones inicializados");
  //digitalWrite(LED_BUILTIN, LOW);
  // Inicializar el LCD
  lcd.init();
  //Limpiar la pantalla
  lcd.clear();
  Serial.println("Pantalla inicializada");
}
//Las señales provenientes de los pines se leen y se les hace un and
//De tal manera que si ambos pulsadores estan bajos, se activa el relé

void loop()
{
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
  Serial.print("\r\ncmd1: ");
  Serial.println(cmd1);
  if (cmd1 == "-disp") {
    cmd = cmd.substring(5);
    Pantalla(cmd);
  }
  if (cmd1 == "-prin") {
    Imprimir(cmd);
  }
  if (cmd1 == "-barr") {
    Serial.print("Habriendo barrera");
  }
  /*if(cmd1 == "-conf") {
    Config(cmd);
    }*/

}
//---------Imprimir en Display-----------------
void Pantalla(String salida1) {
  //----------------LCD DISPLAY--------------------------

  //Encender la luz de fondo.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(salida1.substring(0, 8));
  lcd.setCursor(0, 1);
  lcd.print(salida1.substring(8, 16));
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(salida1.substring(16, 24));
  lcd.setCursor(0, 1);
  lcd.print(salida1.substring(24, 32));
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
  mySerial.write("\x1B\x61\x01");
  //TM88.println(Imprime);
  mySerial.println(Imprime);
  //TM88.barcodeHeight(50);
  mySerial.write("\x1D\x68\x32");
  //TM88.barcodeWidth(3);
  mySerial.write("\x1D\x77\x03");
  //TM88.barcodeNumberPosition(2);
  mySerial.write("\x1D\x48\x02");

  //TM88.printBarcode(70,8);
  mySerial.write("\x1d\x6b\x46\x08");
  //TM88.println(codificado);
  mySerial.println(codificado);
  //TM88.feed(5);
  mySerial.write("\n\n\n\n\n\n");
  //TM88.cut();
  //mySerial.write("\x1D\x56\x42\x0A");
  digitalWrite(LED, LOW);
}
/*void Config(String cnf){
  Serial.print("\r\nCargando configuracion inicial...");
  String confi = cnf.substring(5);
  Serial.println(confi);

  }*/
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
