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

//Crear el objeto lcd  dirección  0x3f y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3f, 16, 2);

//Crear la nueva interfaz serial para la impresora
//NewSoftSerial mySerial(14, 13);// Rx  Tx  por ahora no sirve
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor


// El numero de los pines (constantes siempre):

const int button_1 = 21;
const int button_2 = 20;
const int rele = 19;
const int RESET = 12; //Hardware reset para el ESP8266

//Variables que cambian:
int boton1 = 0; //Variables para leer el estatus de los botones
int boton2 = 0;
int relay = 0;

void setup()
{ //----------------------FUNCIONES  QUE DEBEN SER DECLARADAS-------------------------
  //boolean connectWiFi();
  //Inicializando los pines de entrada y salida
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(rele, OUTPUT);
  pinMode(RESET,OUTPUT); //Teensy con ESP8266
  reset();               //Teensy con ESP8266
  delay(2000);
  pinMode(LED,OUTPUT);   //Teensy
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  //digitalWrite(LED_BUILTIN, LOW);

  // Inicializar el LCD
  lcd.init();
  //Limpiar la pantalla
  lcd.clear();

  
  Serial.begin(57600);
  Serial.println(F("\n[webClient]"));

  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, 8) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
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

  ether.printIp("SRV: ", ether.hisip);
  mySerial.begin(9600);
  delay(4000);    //Esperar que se setee el pto serial y se prenda el dispositivo
}
//Las señales provenientes de los pines se leen y se les hace un and
//De tal manera que si ambos pulsadores estan bajos, se activa el relé

void loop()
{
  boton1 = digitalRead(button_1);
  boton2 = digitalRead(button_2);

  if (boton1 == LOW && boton2 == HIGH) { //Está el carro, no se ha presionado el botón
    //-----------------------------------GET REQUEST 1-------------------------------------------------------------
    Serial.println("Está el carro, no se ha presionado el botón");
    
    ether.packetLoop(ether.packetReceive());

  if (millis() > timer) {
    timer = millis() + 1000;
    ether.browseUrl(PSTR("/standby.php"), "", website, my_callback);
    Serial.println("Sending a request...");
  }

  //Analizo el header & web page. Ejemplo una fecha actual
  
    //char comma = 44;
    //char dot = 46;
    String msg1 = Serial1.readStringUntil(',');
    String msg2 = Serial1.readStringUntil('.');
    String msg3 = Serial1.readStringUntil(',');
    String msg4 = Serial1.readStringUntil(';');
    
       //----------------LCD DISPLAY--------------------------

    //Encender la luz de fondo.
    lcd.backlight();
    lcd.clear();
    // Mover el cursor a la primera posición de la pantalla (0, 0)
    lcd.setCursor(0, 0);
    lcd.print(msg1);
    lcd.setCursor(0, 1);
    lcd.print(msg2);
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(msg3);    //Otras palabras. Tiene que ir de 8 en 8 por e display.
    lcd.setCursor(0, 1);
    lcd.print(msg4);
    delay(1500);

  } if (boton1 == LOW && boton2 == LOW) {
    //ENTRÓ ALGUIEN!
    //-----------------------------------GET REQUEST 2-------------------------------------------------------------
    Serial.println("ENTRÓ ALGUIEN!");
    
  ether.packetLoop(ether.packetReceive());

  if (millis() > timer) {
    timer = millis() + 1000;
    ether.browseUrl(PSTR("/ticket.php"), "?estacion=1", website, my_callback);
    Serial.println("Sending a request...");
  }

  //Analizo el header & web page. Ejemplo una fecha actual

    //char comma = 44;
    //char dot = 46;
    String msg1 = Serial1.readStringUntil(',');
    String msg2 = Serial1.readStringUntil('.');
    String msg3 = Serial1.readStringUntil(':');
    String msg4 = Serial1.readStringUntil(';');

      String msg5 = Serial1.readStringUntil(';');
      Serial.println(msg5);
    
    
       //----------------LCD DISPLAY--------------------------

    //Encender la luz de fondo.
    lcd.backlight();
    lcd.clear();
    // Mover el cursor a la primera posición de la pantalla (0, 0)
    lcd.setCursor(0, 0);
    lcd.print(msg1);
    lcd.setCursor(0, 1);
    lcd.print(msg2);
    digitalWrite(LED,HIGH);
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(msg3);    //Otras palabras. Tiene que ir de 8 en 8 por e display.
    lcd.setCursor(0, 1);
    lcd.print(msg4);
//IMPRIMIENDO----------------------------------------------------------------------
    printer.begin();        // Init printer (same regardless of serial type)
    printer.justify('L');
    printer.println("***  MY ENGINEERING STUFFS  ***\n");
    printer.justify('C');
    printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
    printer.println("TICKET NUMERO: ");
    printer.println(msg4);
    printer.boldOn();
    printer.setSize('L');
    printer.println("001\n");
    printer.println("Fecha:");
    printer.println(msg5);
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
    
  } if (boton1 == HIGH && boton2 == HIGH) {  //No hay nadie...
    //-----------------------------------GET REQUEST 3-------------------------------------------------------------
    Serial.println("No hay nadie...");
    
  ether.packetLoop(ether.packetReceive());

  if (millis() > timer) {
    timer = millis() + 1000;
    ether.browseUrl(PSTR("/standby.php"), "", website, my_callback);
    Serial.println("Sending a request...");
  }

  //Analizo el header & web page. Ejemplo una fecha actual

    //char comma = 44;
    //char dot = 46;
    String msg1 = Serial1.readStringUntil(',');
    String msg2 = Serial1.readStringUntil('.');
    String msg3 = Serial1.readStringUntil(',');
    String msg4 = Serial1.readStringUntil(';');
    
       //----------------LCD DISPLAY--------------------------

    //Encender la luz de fondo.
    lcd.backlight();
    lcd.clear();
    // Mover el cursor a la primera posición de la pantalla (0, 0)
    lcd.setCursor(0, 0);
    lcd.print(msg1);
    lcd.setCursor(0, 1);
    lcd.print(msg2);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(msg3);
    lcd.setCursor(0,1);
    lcd.print(msg4);
    delay(2000);

  }
  
}

//------------------Funciones para el weblclient-------------------------
// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
}
void reset()
{
  digitalWrite(RESET,LOW);
  digitalWrite(LED,HIGH);
  delay(100);
  digitalWrite(RESET,HIGH);
  digitalWrite(LED,LOW);
}
