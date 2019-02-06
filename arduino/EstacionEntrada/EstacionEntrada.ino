#include <EtherCard.h>
#include <Adafruit_Thermal.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LED 11 //led del teensy 2.0
#define rxPin 14  //serial que va a la impresora
#define txPin 13 //serial que va a la impresora
//-----------Ethernet-------------------------
// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700];
static uint32_t timer;
const char website[] PROGMEM = "10.20.184.70";

//-------------------------Display---------------------

//Crear el objeto lcd  dirección  0x3f y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3f, 16, 2);

//----------------------Impresora------------------------
//Crear la nueva interfaz serial para la impresora
//NewSoftSerial mySerial(14, 13);// Rx  Tx  por ahora no sirve
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor


// El numero de los pines (constantes siempre):

const int button_1 = 21;
const int button_2 = 20;
const int RESET = 12; //Hardware reset para el ESP8266

//Variables que cambian:
int boton1 = 0; //Variables para leer el estatus de los botones
int boton2 = 0;

void setup()
{ //----------------------FUNCIONES  QUE DEBEN SER DECLARADAS-------------------------
  Serial.begin(9600);
  Serial.println(F("\n[webClient]"));
  Serial.print("MAC: ");
  for (byte i = 0; i < 6; ++i) {
    Serial.print(mymac[i], HEX);
    if (i < 5)
      Serial.print(':');
  }

  Serial.println("\nProceding to access Ethernet Controller\r\n");
  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, 8) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
      Serial.println("\r\nDHCP...\r\n\r\n");
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  

  // or provide a numeric IP address instead of a string
  //byte hisip[] = { 10,20,184,70 };
  ether.hisip[0] = 10;
  ether.hisip[1] = 20;
  ether.hisip[2] = 184;
  ether.hisip[3] = 70;

  ether.printIp("Server: ", ether.hisip);

  //Inicializando los pines de entrada y salida
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(rele, OUTPUT);
  pinMode(RESET,OUTPUT); //Teensy con ESP8266
  pinMode(LED,OUTPUT);   //Teensy
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  //digitalWrite(LED_BUILTIN, LOW);
  // Inicializar el LCD
  lcd.init();
  //Limpiar la pantalla
  lcd.clear();
  
  mySerial.begin(9600);
  delay(4000);    //Esperar que se setee el pto serial y se prenda el dispositivo
}
//Las señales provenientes de los pines se leen y se les hace un and
//De tal manera que si ambos pulsadores estan bajos, se activa el relé

void loop()
{delay(1000);
  boton1 = digitalRead(button_1);
  boton2 = digitalRead(button_2);

  if (boton1 == LOW && boton2 == HIGH) { //Está el carro, no se ha presionado el botón
    //-----------------------------------GET REQUEST 1-------------------------------------------------------------
    Serial.println("Está el carro, no se ha presionado el botón");
    
    ether.packetLoop(ether.packetReceive());

  if (millis() > timer) {
    timer = millis() + 1000;
    Serial.println();
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR("/standby.php"), "?carro=1", website, my_callback);
  }

  } if (boton1 == LOW && boton2 == LOW) {
    //ENTRÓ ALGUIEN!
    //-----------------------------------GET REQUEST 2-------------------------------------------------------------
    Serial.println("ENTRÓ ALGUIEN!");
    
  ether.packetLoop(ether.packetReceive());

  if (millis() > timer) {
    timer = millis() + 1000;
    Serial.println();
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR("/ticket.php"), "?estacion=1", website, my_callback);
  }
    
  } if (boton1 == HIGH && boton2 == HIGH) {  //No hay nadie...
    //-----------------------------------GET REQUEST 3-------------------------------------------------------------
    Serial.println("No hay nadie...");
    
  ether.packetLoop(ether.packetReceive());

  if (millis() > timer) {
    timer = millis() + 1000;
    Serial.println();
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR("/standby.php?carro=0"), "", website, my_callback);
  }
  
}

}

// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+len] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  String salida = (const char*) Ethernet::buffer + off;
  int pos =   salida.indexOf("\r\n\r\n")+4;
  String salida1 = salida.substring(pos);
  while(salida1.length() > 0){
    int fin=salida1.indexOf("-end");
    if (fin==0) salida1="";
    comando(salida1.substring(0,fin));
    Serial.println();
    Serial.print(salida1);
    salida1 = salida1.substring(fin+4);
    }
    
  }

void comando(String cmd){
  String cmd1 = cmd.substring(0,5);
  Serial.print("\r\ncmd1: ");
  Serial.println(cmd1);
  if (cmd1 == "-disp") Pantalla(cmd);
  if(cmd1 == "-barre") Serial.print("\r\nHabriendo barrera");
  if(cmd1 == "-print") Imprimir();
}
//---------Imprimir en Display-----------------
void Pantalla(String salida1){
//----------------LCD DISPLAY--------------------------

    //Encender la luz de fondo.
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(salida1.substring(5, 13));
    lcd.setCursor(0, 1);
    lcd.print(salida1.substring(13, 21));
    delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(salida1.substring(21, 29));
    lcd.setCursor(0, 1);
    lcd.print(salida1.substring(29, 37));
    delay(1500);
}

void Imprimir() {
    Serial.print("\r\nImprimiendo...");
    //IMPRIMIENDO----------------------------------------------------------------------
    digitalWrite(LED,HIGH);
    printer.begin();        // Init printer (same regardless of serial type)
    printer.justify('L');
    printer.println("***  MY ENGINEERING STUFFS  ***\n");
    printer.justify('C');
    printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
    printer.println("TICKET NUMERO: ");
    //printer.println(msg4);
    printer.boldOn();
    printer.setSize('L');
    printer.println("001\n");
    printer.println("Fecha:");
    //printer.println(msg5);
    printer.boldOff();
    printer.justify('C');
    printer.setSize('S');
    printer.println("***  HAVE A NICE DAY  ***");
    printer.justify('C');
    printer.print("DATE:24/01/2018\t");
    printer.println("TIME: 00:07");
    printer.println("TODAY: WEDNESDAY");   
    printer.write(10);
    printer.write(10);
    printer.write(10);
    delay(3000);
    digitalWrite(LED,LOW);
}
