#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);

const int key_0 = 15; 
const int key_1 = 16;
const int key_2 = 17;
const int key_3 = 19;
const int key_4 = 0;
const int key_5 = 4;
const int key_6 = 9;
const int key_7 = 10;
int key[8] = {0,0,0,0,0,0,0,0};
String teclado = "";
int pos = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(key_0,OUTPUT);
pinMode(key_1,OUTPUT);
pinMode(key_2,OUTPUT);
pinMode(key_3,OUTPUT);
pinMode(key_4,OUTPUT);
pinMode(key_5,OUTPUT);
pinMode(key_6,OUTPUT);
pinMode(key_7,OUTPUT);
lcd.init();
lcd.clear();
}

void loop() {
  key[0] = digitalRead(key_0);
  key[1] = digitalRead(key_1);
  key[2] = digitalRead(key_2);
  key[3] = digitalRead(key_3);
  key[4] = digitalRead(key_4);
  key[5] = digitalRead(key_5);
  key[6] = digitalRead(key_6);
  key[7] = digitalRead(key_7);
  // put your main code here, to run repeatedly:
digitalWrite(key_0,HIGH);
if(key[0] == HIGH && key[4] == HIGH){//1
  teclado = teclado+"1";
  Pantalla(teclado);
}
if(key[0] == HIGH && key[5] == HIGH){//2
  teclado = teclado+"2";
  Pantalla(teclado);
}
if(key[0] == HIGH && key[6] == HIGH){//3
  teclado = teclado+"3";
  Pantalla(teclado);
}
if(key[0] == HIGH && key[7] == HIGH){//A
  teclado = teclado+"A";
  Pantalla(teclado);
}
digitalWrite(key_0,LOW);
digitalWrite(key_1,HIGH);
if(key[1] == HIGH && key[4] == HIGH){//4
  teclado = teclado+"4";
  Pantalla(teclado);
}
if(key[1] == HIGH && key[5] == HIGH){//5
  teclado = teclado+"5";
  Pantalla(teclado);
}
if(key[1] == HIGH && key[6] == HIGH){//6
  teclado = teclado+"6";
  Pantalla(teclado);
}
if(key[1] == HIGH && key[7] == HIGH){//B
  teclado = teclado+"B";
  Pantalla(teclado);
}
digitalWrite(key_1,LOW);
digitalWrite(key_2,HIGH);
if(key[2] == HIGH && key[4] == HIGH){//7
  teclado = teclado+"7";
  Pantalla(teclado);
}
if(key[2] == HIGH && key[5] == HIGH){//8
  teclado = teclado+"8";
  Pantalla(teclado);
}
if(key[2] == HIGH && key[6] == HIGH){//9
  teclado = teclado+"9";
  Pantalla(teclado);
}
if(key[2] == HIGH && key[7] == HIGH){//C
  teclado = teclado+"C";
  Pantalla(teclado);
}
digitalWrite(key_2,LOW);
digitalWrite(key_3,HIGH);
if(key[3] == HIGH && key[4] == HIGH){//*
  teclado = teclado+"*";
  Pantalla(teclado);
}
if(key[3] == HIGH && key[5] == HIGH){//0
  teclado = teclado+"0";
  Pantalla(teclado);
}
if(key[3] == HIGH && key[6] == HIGH){//#
  teclado = teclado+"#";
  Pantalla(teclado);
}
if(key[3] == HIGH && key[7] == HIGH){//D
  teclado = teclado+"D";
  Pantalla(teclado);
}
digitalWrite(key_3,LOW);


}
void Pantalla(String tecla){
  if(pos < 8) {
  lcd.setCursor(pos,0);
  lcd.print(tecla);
  pos++;
  }
  if(pos >= 8 && pos <= 15){
    lcd.setCursor(1,pos);
    lcd.print(tecla);
    if(pos == 15){
      pos = 0;
    }else {
    pos++;
   }
  }
}
