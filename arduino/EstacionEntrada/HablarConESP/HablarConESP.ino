/* Serial pass through for teensy */
#include <SoftwareSerial.h>
#define rxPin 14  //serial que va a la impresora
#define txPin 13 //serial que va a la impresora
  SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  //Serial1.begin(9600);
}

void loop()
{
  /* send everything received from the hardware uart to usb serial & vv */
  if (Serial.available() > 0) {
    char ch = Serial.read();
    if (ch == '*'){
    //Serial1.print("\x1A\x1A\x1A");
    //chr(27).'@'.chr(27).'(B'.chr(16).chr(0).chr(05).chr(2).chr(0).chr(10).chr(0).chr(0).'ABCDERGHJK'); opcion 1
      //mySerial.print("\x1B\x40\x1B\x28\x42\x10\x00\x05\x02\x00\x0A\x00\x00");//opcion 1
      //mySerial.print("ABCDERGHJK\r\n");//opcion 1
      //chr(29).'h'.chr(50).chr(29).'k'.chr(4).trim(substr($row_tbimp->ref,7,5)).chr(0).chr(10) opcion 2
      //mySerial.print("\x1D\x68\x32\x1D\x6B\x04");
      //mySerial.print("12345\x00\x0A");//opcion 2
  //  mySerial.print("ABCDERGHJK\r\n");
    delay(500);
    //Serial1.print("\r");  
    mySerial.print("\r");  
  } else {
      //Serial1.print(ch);
      mySerial.print(ch);
      Serial.print(ch);
  }
  
  }
  //if (Serial1.available() > 0) {
  if (mySerial.available() > 0) {
   //char ch2 = Serial1.read();
   char ch2 = mySerial.read();
    Serial.print(ch2);
    
  }

}
