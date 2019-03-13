#include <EEPROM.h>
#include <EtherCard.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LED 11 //led del teensy 2.0

//-------Escribo IP default en la EEPROM----
void updateIP(String inString[4]);
//-------Busco IP default en la EEPROM------
void readIP();
//-----------Ethernet-------------------------
// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
const char website[] PROGMEM = "10.20.184.70";
byte Ethernet::buffer[400];
static uint32_t timer;
bool onrequest = false;
int printStatus = 0;
String configuracion[5];
String IPROM = "";
//-------------------------Display-----------                                                                                                                                                                                                                      ----------
const byte DCOLS = 20; //four columns
const byte DROWS = 2; //four columns

//LiquidCrystal_I2C lcd(0x3f, DCOLS, DROWS); //en caso de ser 16x2
LiquidCrystal_I2C lcd(0x27, DCOLS, DROWS);//en caso de ser 20x2

// El numero de los pines (constantes siempre):

const int button_1 = 20;
const int button_2 = 21;

void setup() {
  Serial.begin(9600);
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
  }

  Serial.println("\r\nDHCP...\r\n\r\n");
  if (!ether.dhcpSetup()) {
    Serial.println(F("DHCP failed"));
  }

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  String IPdef[] = {"10", "20", "184", "70"};
  readIP();
  String IPnative = "10.20.184.70";
  //----Buscar en la EEPROM la ip default y compararla con la que se esta usando-----
  if (IPROM != IPnative) {
    //ESCRIBO EN MI EEPROM LA IP DEL SERVIDOR, SOLO EJECUTAR UNA SOLA VEZ
    Serial.println();
    Serial.println("EEPROM distinta, actualizando");
    updateIP(IPdef); // Si IPdef es diferente a la que esta guardada la escribe sino no
    delay(1000);
    Serial.print("reseteando. EEPROM actualizada");
    asm("jmp 0x0000");
  }
  Serial.println("IP en la EPPROM: " + IPROM);
  int ip[4];
  for (int j = 0; j < 4; j++) {
    ip[j] = EEPROM.read(j);
    //ip[j] = IPdef[j].toInt();
    ether.hisip[j] = ip[j];//IPdef[i].toInt();
  }
  ether.printIp("Server: ", ether.hisip);
  Serial.println("Solicitando configuracion inicial...");
  //----Configuracion inicial-----------
  //IPROM.toCharArray(website, IPROM.length() + 1);
  //Serial.println(IPROM);
  //Serial.println(website);
  int x = 0;
  onrequest = true;
  timer = 0;
  while (onrequest) {
    ether.packetLoop(ether.packetReceive());

    if (millis() > timer) {
      timer = millis() + 5000;
      Serial.println();
      Serial.print("<<< REQ de setup");
      ether.browseUrl(PSTR("/setup.php"), "", website, my_callback);
      x++;
      if (x > 5) {
        Serial.println("Fallo request");
        onrequest = false;
      }
    }
  }
  //Verifico que la IP de servidor no haya cambiado, si es asi actualizo
  //la EPPROM y reseteo
  Serial.println();
  Serial.println("IP en la EPPROM: " + IPROM);
  Serial.println("IP actual: " + configuracion[0]);
  if (configuracion[0] != IPROM) {
    Serial.print("Actualizando EPPROM con nueva IP: ");
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
      Serial.println(IPnueva[k]);
    }
    Serial.println("Guardando nueva IP en la EPPROM");
    updateIP(IPnueva);
    Serial.print("Guardada nueva IP en la EPPROM: ");
    for (int k = 0; k < 4; k++) {
      Serial.print(IPnueva[k]);
      if (k < 3) {
        Serial.print(".");
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
}

void loop() {

}

// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  onrequest = false;
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
    Serial.println("Empezando conf");
    conf(cmd2);
  }
  /*if (cmd1 == "-pago") {
    String salida1 = cmd2;
    monto = salida1.toInt();
    Serial.print("Monto a pagar: ");
    Serial.println(monto);
    modopago(monto);
    }*/
}

void conf(String arg) {
  int i = 0, r = 0, t = 0;
  for (i = 0; i < arg.length(); i++) {
    if (arg.charAt(i) == ',') {
      configuracion[t] = arg.substring(r, i);
      r = (i + 1);
      t++;
    }
  }
  for (int k = 0; k < 5; k++) {
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
  Serial.println();
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
