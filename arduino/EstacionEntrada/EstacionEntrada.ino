#include <SoftwareSerial.h>
//#include <NewSoftSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define SSID "PNP"  //Red a la que se conectará el ESP826
#define PASS "PNPSISTEMAS"  //Contraseña de la red
#define DST_IP "10.20.184.158" //Dirección del servidor Web
#define LED 11 //led del teensy 2.0
#define rxPin 14  //serial que va a la impresora
#define txPin 13 //serial que va a la impresora

//Crear el objeto lcd  dirección  0x3f y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3f, 16, 2);

//Crear la nueva interfaz serial para la impresora
//NewSoftSerial mySerial(14, 13);// Rx  Tx  por ahora no sirve
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);


// El numero de los pines (constantes siempre):

const int button_1 = 1;
const int button_2 = 2;
const int rele = 3;
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
  pinMode(LED,OUTPUT);   //Teensy
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  //digitalWrite(LED_BUILTIN, LOW);

  // Inicializar el LCD
  lcd.init();
  //Limpiar la pantalla
  lcd.clear();

  
  //Empiezo a hablar con el ESP8266 (Teensy 2.0)
  Serial1.begin(115200);    //Serial físico conectado al ESP8266boolean connectWiFi()
  Serial.begin(115200);//Serial conectado a la PC
  //mySerial.begin(115200); //Serial del teensy que va a la impresora
  mySerial.begin(9600);
  delay(4000);    //Esperar que se setee el pto serial y se prenda el dispositivo
  //Seteando el ESP como se quiere
  
  if(!cwmode3()) Serial.println("cwmode3 failed");
  boolean wifi_connected=false;  //no me he podido conectar a la red Wifi
  for(int i=0;i<5;i++)    //5 intentos para conectarme al wifi
  {
    if(connectWiFi())  //Verificar si realmente hay conexión
    {
      wifi_connected = true;  //Verificada la conexión
      break;
    }
  }
  if (!wifi_connected) hang("wifi not connected");  //Verificar que todo esté bien
  delay(250);    
  if(!cipmux0()) hang("cipmux0 failed");
  delay(250);
  if(!cipmode0()) hang("cipmode0 failed");
  delay(250);
}
//Las señales provenientes de los pines se leen y se les hace un and
//De tal manera que si ambos pulsadores estan bajos, se activa el relé

void loop()
{
  //-----------------------------------Teensy con ESP8266-----------------------------
  //reset();  //De esta forma funciona.
  //delay(5000);  //Tiempo para que el ESP8266 se resetee
  //-----------ME CONECTO AL SERVIDOR POR EL PUERTO 80----------------------
  String cmd = "AT+CIPSTART=\"TCP\",\"";  //Hago este comando: AT+CIPSTART="TCP","IP DESTINO",80
  cmd += DST_IP; //IP de destino
  cmd += "\",80"; //Puerto destino (HTTP)
  
  Serial1.println(cmd);  //Mando el comando al ESP8266
  
  if(Serial1.find("OK"))  //El mensaje se devuelve cuando se establece conexión (PUNTO DEBIL, SUELE NO FUNCIONAR)
  {
    Serial.print("Connected to server at ");  //debug message
    Serial.println(DST_IP);
  }
  else
  {
    Serial.println("'OK' response not received");  //weak spot!
  }
  
  //veo el estado de botones que son entradas digitales

  boton1 = digitalRead(button_1);
  boton2 = digitalRead(button_2);

  if (boton1 == LOW && boton2 == HIGH) { //Está el carro, no se ha presionado el botón
    //-----------------------------------GET REQUEST 1-------------------------------------------------------------
    Serial.println("Está el carro, no se ha presionado el botón");
  cmd =  "GET /Haycarro.php HTTP/1.0\r\n\r\n";  //construct http GET request
  Serial1.print("AT+CIPSEND=");
  Serial1.println(cmd.length());  //esp8266 needs to know message length of incoming message - .length provides this
  
  if(Serial1.find(">"))    //prompt offered by esp8266
  {
    Serial.println("found > prompt - issuing GET request");  //a debug message
    Serial1.println(cmd);  //this is our http GET request
  }
  else
  {
    Serial1.println("AT+CIPCLOSE");  //doesn't seem to work here?
    Serial.println("No '>' prompt received after AT+CPISEND");
  }

  //Analizo el header & web page. Ejemplo una fecha actual

  if (Serial1.find("-8\r\n\r\n")) //get the date line from the http header (for example)
  {
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

  }else
  {
    Serial1.println("AT+CIPCLOSE");  //doesn't seem to work here?
    Serial.println("HTTP GET FAILURE");
  }

  } if (boton1 == LOW && boton2 == LOW) {
    //ENTRÓ ALGUIEN!
    //-----------------------------------GET REQUEST 2-------------------------------------------------------------
    Serial.println("ENTRÓ ALGUIEN!");
  cmd =  "GET /ticket.php?estacion=1 HTTP/1.0\r\n\r\n";  //construct http GET request
  //cmd += "Host: cse.dmu.ac.uk\r\n\r\n";        //test file on my web
  Serial1.print("AT+CIPSEND=");
  Serial1.println(cmd.length());  //esp8266 needs to know message length of incoming message - .length provides this

  if(Serial1.find(">"))    //prompt offered by esp8266
  {
    Serial.println("found > prompt - issuing GET request");  //a debug message
    Serial1.println(cmd);  //this is our http GET request
  }
  else
  {
    Serial1.println("AT+CIPCLOSE");  //doesn't seem to work here?
    Serial.println("No '>' prompt received after AT+CPISEND");
  }

  //Analizo el header & web page. Ejemplo una fecha actual

  if (Serial1.find("-7\r\n\r\n")) //get the date line from the http header (for example)
  {
    //char comma = 44;
    //char dot = 46;
    String msg1 = Serial1.readStringUntil(',');
    String msg2 = Serial1.readStringUntil('.');
    String msg3 = Serial1.readStringUntil(':');
    String msg4 = Serial1.readStringUntil(';');

    if (Serial1.find("-6\r\n\r\n")) { //Imprimo la fecha de entrada. msg4 es el ID y msg5 la fecha de entrada

      String msg5 = Serial1.readStringUntil(';');
      Serial.println(msg5);
    }
    
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
    delay(3000);
    digitalWrite(LED,LOW);

  }else
  {
    Serial1.println("AT+CIPCLOSE");  //doesn't seem to work here?
    Serial.println("HTTP GET FAILURE");
  }
    
  } if (boton1 == HIGH && boton2 == HIGH) {  //No hay nadie...
    //-----------------------------------GET REQUEST 3-------------------------------------------------------------
    Serial.println("No hay nadie...");
  cmd =  "GET /standby.php HTTP/1.0\r\n\r\n";  //construct http GET request
  //cmd += "Host: cse.dmu.ac.uk\r\n\r\n";        //test file on my web
  Serial1.print("AT+CIPSEND=");
  Serial1.println(cmd.length());  //esp8266 needs to know message length of incoming message - .length provides this

  if(Serial1.find(">"))    //prompt offered by esp8266
  {
    Serial.println("found > prompt - issuing GET request");  //a debug message
    Serial1.println(cmd);  //this is our http GET request
  }
  else
  {
    Serial1.println("AT+CIPCLOSE");  //doesn't seem to work here?
    Serial.println("No '>' prompt received after AT+CPISEND");
  }

  //Analizo el header & web page. Ejemplo una fecha actual

  if (Serial1.find("-8\r\n\r\n")) //get the date line from the http header (for example)
  {
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

  }else
  {
    Serial1.println("AT+CIPCLOSE");  //doesn't seem to work here?
    Serial.println("HTTP GET FAILURE");
  }

  }

   Serial1.println("AT+CIPCLOSE");  

  if(Serial1.find("OK"))  //rarely seems to find Unlink? :(
  {
    Serial.println("Connection Closed Ok...");
  }
  else
  {
    Serial.println("connection close failure");
  }
  
}

//------------------Funciones para el weblclient con el ESP8266-------------------------
  boolean connectWiFi()
{
  String cmd="AT+CWJAP=\"";  //form eg: AT+CWJAP="PNP","PNPSISTEMAS"
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial1.println(cmd);
  delay(5000); //tiempo de conexión
  if(Serial1.find("OK"))  //respuesta esperada
  {
    Serial.println("Connected to WiFi...");
    return true;
  }
  else
  {
    Serial.println("Not connected to WiFi.");
    return false;
  }
}
//--------------------------------------------------------------------------------  
//ditch this in favour of hardware reset. Done
boolean softwarereset()
{
  Serial1.println("AT+RST");
  if (Serial1.find("ready"))
  {
    return true;
  }
  else
  {
    return false;
  }
}
//--------------------------------------------------------------------------------
void reset()
{
  digitalWrite(RESET,LOW);
  digitalWrite(LED,HIGH);
  delay(100);
  digitalWrite(RESET,HIGH);
  digitalWrite(LED,LOW);
}
//------------------------------------------------------------------------------
boolean cwmode3()
// Odd one. CWMODE=3 means configure the device as access point & station.

{
  Serial1.println("AT+CWMODE=3");
  if (Serial1.find("OK"))
  {
    return true;
  }
  else
  {
    return false;
  }
}
//----------------------------------------------------------------------------------
boolean cipmux0()
{
  Serial1.println("AT+CIPMUX=0");
  if (Serial1.find("OK"))
  {
    return true;
  }
  else
  {
    return false;
  }
}
//-----------------------------------------------------------------------
boolean cipmode0()
{
  Serial1.println("AT+CIPMODE=0");
  if (Serial1.find("OK"))
  {
    return true;
  }
  else
  {
    return false;
  }
}
//------------------------------------------------------------------------
void hang(String error_String)    //for debugging
{
  Serial.print("Halted...   ");
  Serial.println(error_String);
  while(1)
  {
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }
}
//----------------------------------------------------------------------------
void hangreset (String error_String)    //for debugging
{
  Serial.print(error_String);
  Serial.println(" - resetting");
  reset();
}
//----------------------------------------------------------------------------
void printResponse() { //What's ESP doing right now?
  while (Serial1.available()) {
    Serial.println(Serial1.readStringUntil('\n')); 
  }
}
