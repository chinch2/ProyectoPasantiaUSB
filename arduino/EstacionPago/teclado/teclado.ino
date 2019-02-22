#include <Key.h>
#include <Keypad.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);
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
bool Resp = true;
void setup() {
  // put your setup code here, to run once:
lcd.init();
lcd.clear();
Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
  }
 }
/*void leeteclado(){
  for(int y=0; y<=3; y++){
    digitalWrite(keyin[y],HIGH);
      for(int z=0; z<=3; z++){
        if(digitalRead(keyout[z]) == HIGH){
          return tecla[y][z];
        }
      }
      digitalWrite(keyin[y],LOW);
  }
}*/


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
