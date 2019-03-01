#include <EEPROM.h>
#include <EtherCard.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Key.h>
#include <Keypad.h>
#include <ctype.h>
#define LED 11 //led del teensy 2.0
#define rxPin 14  //serial que viene del escaner
#define txPin 13 //serial que va a la impresora
//-------Escribo IP default en la EEPROM----
void updateIP(String inString[4]);
// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
const char website[] PROGMEM = "10.20.184.70";
String request;//char request[30];
String prequest;
byte Ethernet::buffer[400];
static uint32_t timer = 0;
bool onrequest = false;
bool ponrequest = false;
char requestc[15];
char prequestc[100];
//int printStatus = 0;
//------------Display---------------------
const byte DCOLS = 8; //four columns
const byte DROWS = 2; //four columns

LiquidCrystal_I2C lcd(0x3f, DCOLS, DROWS);
//-----------Escaner e impresora----------------
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
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

byte rowPins[ROWS] = {0, 4, 9, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {15, 16, 17, 19}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
unsigned int pagos[3] = {0, 0, 0};
String mensa[3] = {"Pago tarjeta", "Pago Efectivo", "Pago Otros"};
unsigned int monto;

void setup() {
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
  if (ether.begin(sizeof Ethernet::buffer, mymac, 20) == 0) {
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
    }else{*/
  int ip[4];
  for (int i = 0; i < 4; i++) {
    ip[i] = IPdef[i].toInt();
    ether.hisip[i] = ip[i];//IPdef[i].toInt();
  }
  ether.printIp("Server: ", ether.hisip);
  Serial.println("Solicitando configuracion inicial...");
  //}
  /*String recivedData;
    recivedData = read_String(0);

    Serial.print("recivedData:");
    Serial.println(recivedData);
    //const char *websiteIP = recivedData.c_str();
    Serial.println(websiteIP);*/
  //Inicializando los pines de entrada y salida
  pinMode(dispara, OUTPUT); //Trigger del escaner
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
  delay(1000);

}

void loop() {
  ether.packetLoop(ether.packetReceive());

  String buff = "10000023";
  Pantalla("Monto 1000");
  /*lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Monto 10");
    lcd.setCursor(0, 1);
    lcd.print("00");*/
  modopago(1000);
  delay(3000);
}

// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println("callback" + status);
  onrequest = false;
  ponrequest = false;
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
    Serial.println("*" + salcomando + "*");
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
  Serial.println("\r\ncomando:" + cmd + "modo:" + cmd1 + "argumento:" + cmd2 + "*");
  if (cmd1 == "-disp") {
    Serial.print(cmd2);
    Pantalla(cmd2);
    /*lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(cmd.substring(0, DCOLS));
      lcd.setCursor(0, 1);
      lcd.print(cmd.substring(DCOLS, DCOLS * 2));*/
  }
  /*    if(cmd1 == "-prin") {
      Imprimir(cmd);
    }
    if(cmd1 == "-barr") {
      Serial.print("Habriendo barrera");
    }
    if(cmd1 == "-conf") {
      Config(cmd);
    }*/
  if (cmd1 == "-pago") {
    String salida1 = cmd2;
    monto = salida1.toInt();
    Serial.println("Monto a pagar:" + monto);
    modopago(monto);
  }
}

//---------Imprimir en Display-----------------
void Pantalla(String muestra) {
  //----------------LCD DISPLAY--------------------------

  //Encender la luz de fondo.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(muestra.substring(0, DCOLS));
  lcd.setCursor(0, 1);
  lcd.print(muestra.substring(DCOLS, DCOLS * 2));
}

void modopago(unsigned int mnt) {
  String teclado = "";
  bool respuesta = true;
  pagos[0] = 0;
  pagos[1] = 0;
  pagos[2] = 0;
  while (respuesta) {
    ether.packetLoop(ether.packetReceive());

    char key = keypad.getKey();
    Serial.print(key);
    switch (key)
    {
      case 'A':
      case 'B':
      case 'C': {
          pagos[key - 65] = teclado.toInt();
          teclado = "";
          Pantalla(mensa[key - 65]);
          /*lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(mensa[key - 65].substring(0, DCOLS));
            lcd.setCursor(0, 1);
            lcd.print(mensa[key - 65].substring(DCOLS, DCOLS * 2));*/
        } break;
      case 'D': {
          teclado = "";
          Serial.println("Enter");
          if (mnt >= pagos[0] + pagos[1] + pagos[2]) {
            Pantalla("Monto incompleto");
            /*lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Monto in");
              lcd.setCursor(0, 1);
              lcd.print("completo");*/
          } else {
            Pantalla("Procesando");
            /*lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Procesan");
              lcd.setCursor(0, 1);
              lcd.print("do");*/
            return;
            Serial.println("Preparando Request");
            prequest = "?estacion=1&id=" + buff + "&pa=" + pagos[0] + "&pb=" + pagos[1] + "&pc=" + pagos[2];
            Serial.println(prequest);
            prequest.toCharArray(prequestc, prequest.length() + 1);
            Serial.println(prequestc);
            int x = 0;
            ponrequest = true;
            timer = 0;
            while (ponrequest) {
              ether.packetLoop(ether.packetReceive());

              if (millis() > timer) {
                timer = millis() + 5000;
                Serial.println("Request de pago\r\n");
                Serial.print("<<< REQ: ");
                Serial.print(prequestc);
                ether.browseUrl(PSTR("/pago.php"), prequestc, website, my_callback);
                x++;
                if (x > 5) {
                  Serial.print("Fallo request");
                  ponrequest = false;
                }
              }
            }
            buff = "";//buff[j] = '\0';
            Serial.println("Modo pago finalizado\r\n");
            respuesta = false;
            //requestpago();

          }
        } break;
      case '#': {
          teclado = "";
          Pantalla("Cancelado");
          /*lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Cancelad");
            lcd.setCursor(0, 1);
            lcd.print("o");*/
          respuesta = false;
        } break;
      case '*': {
          teclado = "";
          Pantalla("");
          /*lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("");
            lcd.setCursor(0, 1);
            lcd.print("");*/
        } break;
      default:

        if (isDigit(key)) {
          teclado = teclado + key;
          Pantalla(teclado);
          /*lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(teclado.substring(0, 8));
            lcd.setCursor(0, 1);
            lcd.print(teclado.substring(8, 16));*/
        }
        break;
    }
  }
}

/*void requestpago() {
  Serial.println("Preparando Request");
  prequest = "?estacion=1&id=" + buff + "&pa=" + pagos[0] + "&pb=" + pagos[1] + "&pc=" + pagos[2];
  Serial.println(prequest);
  prequest.toCharArray(prequestc, prequest.length() + 1);
  Serial.println(prequestc);
  int x = 0;
  ponrequest = true;
  timer = 0;
  while (ponrequest) {
    ether.packetLoop(ether.packetReceive());

    if (millis() > timer) {
      timer = millis() + 5000;
      Serial.println("Request de pago\r\n");
      Serial.print("<<< REQ: ");
      Serial.print(prequestc);
      ether.browseUrl(PSTR("/pago.php"), prequestc, website, my_callback);
      x++;
      if (x > 5) {
        Serial.print("Fallo request");
        ponrequest = false;
      }
    }
  }
  buff = "";//buff[j] = '\0';
  Serial.println("Modo pago finalizado\r\n");
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
