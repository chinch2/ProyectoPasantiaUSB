#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define SSID "PNP"  //Red a la que se conectará el ESP826
#define PASS "PNPSISTEMAS"  //Contraseña de la red
#define DST_IP "146.227.57.195" //Dirección del servidor Web

//Crear el objeto lcd  dirección  0x3f y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3f, 16, 2);
// El numero de los pines (constantes siempre):

const int button_1 = 1;
const int button_2 = 2;
const int rele = 3;
const int LED = 11;
const int RESET = 12; //Hardware reset para el ESP8266

//Variables que cambian:
int boton1 = 0; //Variables para leer el estatus de los botones
int boton2 = 0;
int relay = 0;
int loops = 0;  //Contador de Pruebas

void setup()
{
  //Inicializando los pines de entrada y salida
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(rele, OUTPUT);
  //pinMode(RESET,OUTPUT); //Teensy
  //reset();               //Teensy
  pinMode(LED,OUTPUT);   //Teensy
  
  //digitalWrite(LED_BUILTIN, LOW);

  // Inicializar el LCD
  lcd.init();
  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  //lcd.begin(16, 2);
  //Limpiar la pantalla
  lcd.clear();
  //Empiezo a hablar con el ESP8266 (Teensy 2.0)
  //Serial1.begin(115200);    //Serial físico conectado al ESP8266
  Serial.begin(115200); //Serial conectado a la PC
  delay(4000);    //Esperar que se setee el pto serial y se prenda el dispositivo
  /*if(!cwmode3()) Serial.println("cwmode3 failed");
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
  delay(250);*/
}
//Las señales provenientes de los pines se leen y se les hace un and
//De tal manera que si ambos pulsadores estan bajos, se activa el relé

void loop()
{
  /*-----------------------------------Teensy con ESP8266-----------------------------
   reset();  //De esta forma funciona.
  delay(5000);  //Tiempo para que el ESP8266 se resetee
  //Serial.print("loops = ");  //Chequea para conexión exitosa al servidor
  //Serial.println(loops); 
  loops++;
  String cmd = "AT+CIPSTART=\"TCP\",\"";  //Hago este comando: AT+CPISTART="TCP","146.227.57.195",80
  cmd += DST_IP; //IP de destino
  cmd += "\",80"; //Puerto destino (HTTP)

  Serial1.println(cmd);  //Mando el comando al ESP8266

  delay(2000);  //Esperar un poco para obtener respuesta de forma exitosa.
  if(Serial1.find("Linked"))  //El mensaje se devuelve cuando se establece conexión (PUNTO DEBIL, SUELE NO FUNCIONAR)
  {
   // Serial.print("Connected to server at ");  //debug message
   // Serial.println(DST_IP);
  }
  else
  {
  //  Serial.println("'Linked' response not received");  //weak spot!
  }

  cmd =  "GET /~sexton/test.txt HTTP/1.0\r\n";  //construct http GET request
  cmd += "Host: cse.dmu.ac.uk\r\n\r\n";        //test file on my web
  Serial1.print("AT+CIPSEND=");                //www.cse.dmu.ac.uk/~sexton/test.txt
  Serial1.println(cmd.length());  //esp8266 needs to know message length of incoming message - .length provides this

  if(Serial1.find(">"))    //prompt offered by esp8266
  {
   // Serial.println("found > prompt - issuing GET request");  //a debug message
    Serial1.println(cmd);  //this is our http GET request
  }
  else
  {
    Serial1.println("AT+CIPCLOSE");  //doesn't seem to work here?
    Serial.println("No '>' prompt received after AT+CPISEND");
  }

  //Analizo el header & web page. Ejemplo una fecha actual

  if (Serial1.find("Date: ")) //get the date line from the http header (for example)
  {
    for (int i=0;i<31;i++)  //this should capture the 'Date: ' line from the header
    {
      if (Serial1.available())  //new cahracters received?
      {
        char c=Serial1.read();  //print to console
        Serial.write(c);
      }
      else i--;  //if not, keep going round loop until we've got all the characters
    }
  }

  Serial1.println("AT+CIPCLOSE");  

  if(Serial1.find("Unlink"))  //rarely seems to find Unlink? :(
  {
    Serial.println("Connection Closed Ok...");
  }
  else
  {
    //Serial.println("connection close failure");
  }
   */
  //veo el estado de botones que son entradas digitales

  boton1 = digitalRead(button_1);
  boton2 = digitalRead(button_2);

  if (boton1 == LOW && boton2 == HIGH) { //Está el carro, no se ha presionado el botón
    //----------------LCD DISPLAY--------------------------
    //Limpiar el display
    //lcd.clear();
    //Encender la luz de fondo.
    lcd.backlight();
    lcd.clear();
    // Mover el cursor a la primera posición de la pantalla (0, 0)
    lcd.setCursor(0, 0);
    lcd.print("Bienveni");
    lcd.setCursor(0, 1);
    lcd.print("do!");
    delay(1500);
    lcd.setCursor(0, 0);
    lcd.print("Pulse 1 ");
    lcd.setCursor(0, 1);
    lcd.print("Segundo");
    delay(1500);
    lcd.clear();


  } if (boton1 == LOW && boton2 == LOW) {
    //ENTRÓ ALGUIEN!
    lcd.setCursor(0, 0);
    lcd.print("Imprimie");
    lcd.setCursor(0, 1);
    lcd.print("ndo...");
    digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(4000);
    digitalWrite(LED, LOW);    // turn the LED off (LOW is the voltage level)

  } if (boton1 == HIGH && boton2 == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Desarrol");
    lcd.setCursor(0, 1);
    lcd.print("los PNP");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dash Tex");
    lcd.setCursor(0, 1);
    lcd.print("t");
    delay(1000);
  }

  /*Leo el analogico de rele
  int PtoSerial = analogRead(rele);
  // print out the value you read:
  Serial.println(PtoSerial);*/
}

/*------------------Funciones para el weblclient con el ESP8266-------------------------
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
  if (Serial1.find("no change"))  //only works if CWMODE was 3 previously
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

 */
