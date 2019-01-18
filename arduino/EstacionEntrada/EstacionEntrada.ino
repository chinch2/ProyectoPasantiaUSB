#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x3f y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3f,16,2);
// El numero de los pines (constantes siempre):
const int button_1 = 12;
const int button_2 = 7;
const int rele = 8;

//Variables que cambian:
int boton1 = 0; //Variables para leer el estatus de los botones
int boton2 = 0;
int relay = 0;

void setup()
{
  //Inicializando los pines de entrada y salida
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(rele, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  // Inicializar el LCD
  lcd.init();
  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  //lcd.begin(16, 2);
  //Limpiar la pantalla
  lcd.clear();
  
}
//Las señales provenientes de los pines se leen y se les hace un and
//De tal manera que si ambos pulsadores estan bajos, se activa el relé
 
void loop()
{
  //veo el estado de botones que son entradas digitales
  
  boton1 = digitalRead(button_1);
  boton2 = digitalRead(button_2);

  if (boton1==LOW && boton2==HIGH) {//Está el carro, no se ha presionado el botón
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
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Pulse 1 ");
  lcd.setCursor(0, 1);
  lcd.print("Segundo");
  delay(1000);
  lcd.clear();
  
    
  } if (boton1==LOW && boton2==LOW) {
    //ENTRÓ ALGUIEN!
    lcd.setCursor(0, 0);
    lcd.print("Imprimie");
    lcd.setCursor(0, 1);
    lcd.print("ndo...");
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(4000);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off (LOW is the voltage level)
    
  } if (boton1==HIGH && boton2==HIGH) {
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
    
  
}
