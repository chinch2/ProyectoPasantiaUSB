#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <EtherCard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define joseduino

#ifdef joseduino

#define LED 0
#define button_1 1
#define button_2 2
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
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
const char website[] PROGMEM = "10.20.184.123";
byte Ethernet::buffer[400];
static uint32_t timer = 0;
bool onrequest = false;
String requestF;
char requestFc[50];
int printStatus = 0;
String configuracion[5];
String IPROM = "";
//int LED, RXS1, TXS1, RXS2, TXS2, button_1, button_2, barrera, ss; //output pins
//-------------------------Display-----------                                                                                                                                                                                                                      ----------

// Inicializar el LCD
int DTYPE = 0x27,//configuracion[2].toInt(),
    DCOLS = 20,//configuracion[3].toInt(),
    DROWS = 2;//configuracion[4].toInt();
LiquidCrystal_I2C lcd(DTYPE, DCOLS, DROWS); //creacion de objeto
// El numero de los pines (constantes siempre):
SoftwareSerial mySerial1(RXS1, TXS1); // RXS1, TXS1
//SoftwareSerial mySerial2(RXS2, TXS2); // RXS2, TXS2

char c;
String buff;

void setup()
{
  mySerial1.begin(9600);
  Serial1.begin(9600);
  delay(1000);
  buff = "";
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
  String IPdef[] = {"10", "20", "184", "123"};
  readIP();
  String IPnative = "10.20.184.123";
  //----Buscar en la EEPROM la ip default y compararla con la que se esta usando-----
  if (IPROM != IPnative) { //EEPROM vacia
    //ESCRIBO EN MI EEPROM LA IP DEL SERVIDOR, SOLO EJECUTAR UNA SOLA VEZ
    Serial1.println();
    Serial1.println("EEPROM distinta, actualizando\r\n");
    updateIP(IPdef); // Si IPdef es diferente a la que esta guardada la escribe sino no
    delay(1000);
    Serial1.print("reseteando. EEPROM actualizada\r\n");
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
  Serial1.println("Solicitando configuracion inicial...\r\n");
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
      Serial1.print("<<< REQ de setup\r\n");
      ether.browseUrl(PSTR("/setup.php"), "?t=1", website, my_callback);
      x++;
      if (x > 5) {
        Serial1.println("Fallo request\r\n");
        onrequest = false;
      }
    }
  }
  //Verifico que la IP de servidor no haya cambiado, si es asi actualizo
  //la EPPROM y reseteo
  Serial1.println();
  Serial1.println("IP en la EPPROM: " + IPROM + "\r\n");
  Serial1.println("IP actual: " + configuracion[0] + "\r\n");
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
    Serial1.println("Guardando nueva IP en la EPPROM\r\n");
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
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);  //Teensy
  pinMode(barrera, OUTPUT);
  Serial1.println("Botones inicializados");
  Serial.begin(configuracion[1].toInt());
  //Serial.begin(9600);
  // Inicializar el LCD
  lcd.init();
  //Limpiar la pantalla
  lcd.clear();
  Serial1.println("Pantalla inicializada");
  delay(1000);
}

void loop()
{

  if (digitalRead(button_1) == HIGH && digitalRead(button_2) == HIGH) {  //No hay nadie
    //-----------------------------------GET REQUEST 3-------------------------------------------------------------
    ether.packetLoop(ether.packetReceive());
    if (millis() > timer) {
      timer = millis() + 5000;
      Serial1.println();
      Serial1.print("<<< REQ de standby\r\n");
      ether.browseUrl(PSTR("/standby.php"), "?carro=0", website, my_callback);
    }

  }

  if (digitalRead(button_1) == LOW && digitalRead(button_2) == HIGH) {  //Hay alguien
    //-----------------------------------GET REQUEST 3-------------------------------------------------------------
    ether.packetLoop(ether.packetReceive());
    if (millis() > timer) {
      timer = millis() + 2000;
      Serial1.println();
      Serial1.print("<<< REQ de carro\r\n");
      ether.browseUrl(PSTR("/standby.php"), "?carro=1", website, my_callback);
    }

  }

  if (digitalRead(button_1) == LOW && digitalRead(button_2) == LOW) {  //Entro alguien
    //-----------------------------------GET REQUEST 3-------------------------------------------------------------
    ether.packetLoop(ether.packetReceive());
    if (millis() > timer) {
      timer = millis() + 1000;
      Serial1.println();
      Serial1.print("<<< REQ de ticket\r\n");
      ether.browseUrl(PSTR("/ticket.php"), "", website, my_callback);
    }

  }

  if (mySerial1.available()) {
    c = mySerial1.read();
    //Serial1.print(c);
    // if( c == 10) Serial1.print("hubo r");
    // if( c == 13) Serial1.print("hubo n");
    if ( c == 13) {
      //const char *req = "?id=";
      //strcpy(request,req);
      //strcat(request,buff);
      requestF = "?IDF=" + buff; // put your main code here, to run repeatedly:
      requestF.toCharArray(requestFc, requestF.length() + 1);
      Serial1.println(requestF);
      Serial1.println(requestFc);
      int x = 0;
      onrequest = true;
      timer = 0;
      while (onrequest) {
        ether.packetLoop(ether.packetReceive());

        if (millis() > timer) {
          timer = millis() + 5000;
          Serial1.println("Request de Entrada fijo");
          Serial1.print("<<< REQ ");
          Serial1.print(requestFc);
          ether.browseUrl(PSTR("/ticket.php"), requestFc, website, my_callback);
          x++;
          if (x > 5) {
            Serial1.println("Fallo request");
            onrequest = false;
            buff = "";
          }
        }
      }
      buff = "";//buff[j] = '\0';
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
  //ponrequest = false;
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
  Serial1.println("comando:" + cmd + " modo:" + cmd1 + " argumento:" + cmd2);
  if (cmd1 == "-disp") {
    Serial1.println(cmd2);
    Pantalla(cmd2);
  }
  if (cmd1 == "-prin") {
    Imprimir(cmd2);
  }
  if (cmd1 == "-barr") {
    Serial1.print("Habriendo barrera");
    digitalWrite(barrera, HIGH);
    delay(3000);
    digitalWrite(barrera, LOW);
  }
  if (cmd1 == "-conf") {
    Serial1.println("Empezando conf");
    conf(cmd2);
  }
  /*if (cmd1 == "-pago") {
    String salida1 = cmd2;
    monto = salida1.toInt();
    Serial1.print("Monto a pagar: ");
    Serial1.println(monto);
    modopago(monto);
    }*/
}

void conf(String arg) {
  Serial1.println(arg);
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

void Imprimir(String printed) {
  Serial1.println("Imprimiendo...");
  Serial1.println(printed);
  //String Imprime = printed.substring(5);
  String codificado = printed.substring(21);
  //Serial1.print(Imprime);
  Serial1.println(codificado);
  //IMPRIMIENDO----------------------------------------------------------------------
  digitalWrite(LED, HIGH);
  //TM88.start();
  //TM88.justifyCenter();
  Serial.write("\x1B\x61\x01");
  //TM88.println(Imprime);
  Serial.println(printed);
  //TM88.barcodeHeight(50);
  Serial.write("\x1D\x68\x32");
  //TM88.barcodeWidth(3);
  Serial.write("\x1D\x77\x03");
  //TM88.barcodeNumberPosition(2);
  Serial.write("\x1D\x48\x02");

  //TM88.printBarcode(70,8);
  Serial.write("\x1d\x6b\x46\x08");
  //TM88.println(codificado);
  Serial.println(codificado);
  //TM88.feed(5);
  Serial.write("\n\n\n\n\n\n");
  //TM88.cut();
  Serial.write("\x1D\x56\x42\x0A");
  digitalWrite(LED, LOW);
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
