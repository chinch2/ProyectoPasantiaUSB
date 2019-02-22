#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);

const int keyin[4] = {0,4,9,10}; 
const int keyout[4] = {15,16,17,19};
String teclado = "";
char p;
const char tecla[4][4] = { {'1','2','3','A'},
                           {'4','5','6','B'},
                           {'7','8','9','C'},
                           {'*','0','#','D'} };
bool Resp = true;
void setup() {
  // put your setup code here, to run once:
for(int x=0; x<=3;x++){
  pinMode(keyin[x],INPUT);
  pinMode(keyout[x],OUTPUT);  
}

lcd.init();
lcd.clear();
}

void loop() {
while(Resp){
  p = leeteclado();
  teclado = teclado + p;
  Pantalla(teclado);
}
}
char leeteclado(){
  for(int x=0; x<=3; x++){
    digitalWrite(keyin[x],HIGH);
      for(int y=0; y<=3; y++){
        if(digitalRead(keyout[y]) == HIGH){
          return tecla[x][y];
        }
      }
      digitalWrite(keyin[x],LOW);
  }
}


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
