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
//-----------Ethernet-------------------------
// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
const char website[] PROGMEM = "10.20.184.70";
String request;//char request[30];
String prequest;
byte Ethernet::buffer[700];
static uint32_t timer;
bool onrequest = false;
bool respuesta = false;
char requestc[15];
char prequestc[30];
int printStatus = 0;
int j=0; //contador de llenado del buff del escaner
//-------------------------Display-----------                                                                                                                                                                                                                      ----------

//Crear el objeto lcd  dirección  0x3f y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3f, 16, 2);
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
char c; 
String buff;//char buff[8];
const int dispara = 18;
//-------------Teclado-----------------------
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {0, 4, 9, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {15, 16, 17, 19}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
String teclado = "";
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
  }else Serial.println(F("Ethernet controller access success"));
      Serial.println("\r\nDHCP...\r\n\r\n");
  if (!ether.dhcpSetup()){
    Serial.println(F("DHCP failed"));
  }else Serial.println(F("DHCP success"));
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
  delay(3000);    //Esperar que se setee el pto serial y se prenda el dispositivo
  Serial.print("ready\r\n");

}

void loop() {
    
  if (mySerial.available()) {
   c = mySerial.read();
 //   Serial.print(c);
 // if( c == 10) Serial.print("hubo r"); 
 // if( c == 13) Serial.print("hubo n");
   if( c == 13){
    //const char *req = "?id=";
    //strcpy(request,req);
    //strcat(request,buff);
    onrequest = true;
    request = "?id="+buff;// put your main code here, to run repeatedly:
    request.toCharArray(requestc,request.length() + 1);
    Serial.println(request);
    Serial.println(requestc);
    while(onrequest){
    ether.packetLoop(ether.packetReceive());

    if(millis() > timer){
      timer = millis() + 5000;
      Serial.println();
      Serial.print("<<< REQ ");
      Serial.print(requestc);
      ether.browseUrl(PSTR("/consulta.php"), requestc, website, my_callback);
      }
    }
   }else {//strcat(buff,c);//buff=buff+c;
      buff = buff + c;//buff[j] = c;
      //buff[j+1] = '\0';
      //j++;
   }
}
}
// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  onrequest = false;
  Serial.println(">>>");
  Ethernet::buffer[off+len] = 0;
  //Serial.print((const char*) Ethernet::buffer + off);
  String salida = (const char*) Ethernet::buffer + off;
  Serial.print(salida);
  int pos =   salida.indexOf("\r\n\r\n")+4;
  salida = salida.substring(pos);
  while(salida.length() > 0){
    int fin=salida.indexOf("-end");
    if (fin==0) salida="";
    Serial.print(salida.substring(0,fin));
    comando(salida.substring(0,fin));
    //Serial.println();
    //Serial.print(salida1);
    salida = salida.substring(fin+4);
    //Serial.print(salida1);
    }
    
}

void comando(String cmd){
  String cmd1 = cmd.substring(0,5);
  Serial.print("\r\ncmd1: ");
  Serial.println(cmd1);
  if (cmd1 == "-disp") {
    Pantalla(cmd.substring(5));
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
    respuesta = true;
    modopago();
  }

}

//---------Imprimir en Display-----------------
void Pantalla(String muestra){
//----------------LCD DISPLAY--------------------------

    //Encender la luz de fondo.
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(muestra.substring(0, 8));
    lcd.setCursor(0, 1);
    lcd.print(muestra.substring(8, 16));
}

void modopago(){
  Serial.println("Modo pago iniciando");
  while(respuesta){
  char key = keypad.getKey();
  
        if (isDigit(key)){
            teclado = teclado + key;
            Pantalla(teclado);
          }
        if(key == 'A') {
              teclado = teclado + key;
              Pantalla("Pago en Tarjeta");
          }
        if(key == 'B') {
              teclado = teclado + key;
              Pantalla("Pago en Efectivo");
          }
        if(key == 'C') {
              teclado = teclado + key;
              Pantalla("Pago en Otros");
          }
        if(key == 'D') {
              Serial.println("Enter");
              onrequest = true;
              prequest = "?estacion=1&id="+buff;// put your main code here, to run repeatedly:
              prequest.toCharArray(prequestc,prequest.length() + 1);
              Serial.println(prequest);
              Serial.println(prequestc);
              while(onrequest){
              ether.packetLoop(ether.packetReceive());
      
              if(millis() > timer){
              timer = millis() + 5000;
              Serial.println("Request de pago\r\n");
              Serial.print("<<< REQ: ");
              Serial.print(prequestc);
              ether.browseUrl(PSTR("/pago.php"), prequestc, website, my_callback);
              }
            }
      respuesta = false;
          }
        if(key == '*'){
              teclado = "";
              Serial.print("Borrado");
          }
        if(key == '#'){
              Serial.print("Cancelado");
              Pantalla("Cancelado");
              respuesta = false;      
          } 
      }
      teclado = "";
      buff = "";//buff[j] = '\0';
      onrequest = false;
      Serial.println("Modo pago finalizado\r\n");
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
