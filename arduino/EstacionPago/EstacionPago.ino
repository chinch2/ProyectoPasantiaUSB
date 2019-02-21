#include <EEPROM.h>
#include <EtherCard.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LED 11 //led del teensy 2.0
#define rxPin 14  //serial que viene del escaner
#define txPin 13 //serial que va a la impresora
//-------Escribo IP default en la EEPROM----
void updateIP(String inString[4]);
//-----------Ethernet-------------------------
// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
const char website[] PROGMEM = "10.20.184.70";
String request;//char request[30];
byte Ethernet::buffer[700];
static uint32_t timer;
bool onrequest = false;
char requestc[15];
int printStatus = 0;
int j=0; //contador de llenado del buff del escaner
//-------------------------Display-----------                                                                                                                                                                                                                      ----------

//Crear el objeto lcd  dirección  0x3f y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3f, 16, 2);
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
char c; 
String buff;//char buff[8];//char buff[8];
const int dispara = 18;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  buff = "";//buff[0] = '\0';
  Serial.print("Codigo de barra: \r\n");
  Serial.println(F("\n[webClient]"));
  Serial.print("MAC: ");
  for (byte i = 0; i < 6; ++i) {
    Serial.print(mymac[i], HEX);
    if (i < 5)
      Serial.print(':');
  }

  Serial.println("\nProceding to access Ethernet Controller\r\n");
  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, 8) == 0){
    Serial.println(F("Failed to access Ethernet controller"));
      Serial.println("\r\nDHCP...\r\n\r\n");
  }
  if (!ether.dhcpSetup()){
    Serial.println(F("DHCP failed"));
  }
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  String IPdef[] = {"10","20","184","70"};
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
  for(int i=0;i<4;i++){
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
  pinMode(dispara,OUTPUT); //Trigger del escaner
  pinMode(LED,OUTPUT);   //Teensy
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.println("Botones inicializados");
  //digitalWrite(LED_BUILTIN, LOW);
  // Inicializar el LCD
  lcd.init();
  //Limpiar la pantalla
  lcd.clear();
  Serial.println("Pantalla inicializada");
  delay(1000);    //Esperar que se setee el pto serial y se prenda el dispositivo

}

void loop() {
  //const char *req = "?id=";
  //strcpy(request,req);
  //strcat(request,(const char*)buff);
  ether.packetLoop(ether.packetReceive());
  
    if (millis() > timer && onrequest) {
        timer = millis() + 5000;
        Serial.println();
        Serial.print("<<< REQ ");
        ether.browseUrl(PSTR("/consulta.php"), requestc, website, my_callback);
      }
  if (mySerial.available()) {
   c = mySerial.read();
 //   Serial.print(c);
 // if( c == 10) Serial.print("hubo r"); 
 // if( c == 13) Serial.print("hubo n");
   if( c == 13){
    request = "?id="+buff;// put your main code here, to run repeatedly:
    request.toCharArray(requestc,request.length());//+ 1);
    Serial.println(requestc);
    Serial.println();
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR("/consulta.php"), requestc, website, my_callback);
    onrequest = true;
    timer = millis() + 5000;
      //j=0;
    buff = "";//buff[j] = '\0';
   }//else strcat(buff,(const char*)c);//buff=buff+c;
      buff = buff + c;//buff[j] = c;
      //buff[j+1] = '\0';
      //j++;
}

}
// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  onrequest = false;
  Serial.println(">>>");
  Ethernet::buffer[off+len] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  String salida = (const char*) Ethernet::buffer + off;
  int pos =   salida.indexOf("\r\n\r\n")+4;
  String salida1 = salida.substring(pos);
  while(salida1.length() > 0){
    int fin=salida1.indexOf("-end");
    if (fin==0) salida1="";
    String action = salida1.substring(0,fin);
    Serial.print(action);
    comando(action);
    //Serial.println();
    //Serial.print(salida1);
    salida1 = salida1.substring(fin+4);
    //Serial.print(salida1);
    }
    
}

void comando(String cmd){
  String cmd1 = cmd.substring(0,5);
  Serial.print("\r\ncmd1: ");
  Serial.println(cmd1);
  if (cmd1 == "-disp") {
    Pantalla(cmd);
  }
/*    if(cmd1 == "-prin") {
    Imprimir(cmd);
  }
  if(cmd1 == "-barr") {
    Serial.print("Habriendo barrera");
  }
  /*if(cmd1 == "-conf") {
    Config(cmd);
  }*/

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

void updateIP(String inString[4])
{
  int ip[4];
  int m;
  int i;
  int n;
  Serial.print("Guardando IP en la EEPROM: ");
  for(m=0; m<4; m++) {
    Serial.print(inString[m]);
    if(m<3){
    Serial.print(".");
    }
  }
  Serial.print("\r\n");
  
  for (i=0; i<4; i++) {
  ip[i] = inString[i].toInt();
  EEPROM.update(i,ip[i]);
  }
  Serial.print("Guardada en EEPROM IP: ");
  for(n=0; n<4; n++){
  Serial.print(EEPROM.read(n));
    if(n<3){
      Serial.print(".");
    }
  }
}
