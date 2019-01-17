#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F,16,2);

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
  
  
  
}
//Las señales provenientes de los pines se leen y se les hace un and
//De tal manera que si ambos pulsadores estan bajos, se activa el relé
 
void loop()
{
  //veo el estado de botones que son entradas digitales
  
  boton1 = digitalRead(button_1);
  boton2 = digitalRead(button_2);

  if (boton1==LOW) {//Está el carro, no se ha presionado el botón
    //----------------LCD DISPLAY--------------------------
   //Encender la luz de fondo.
  lcd.backlight();
  
  // Escribimos el Mensaje en el LCD.
  lcd.setCursor(10, 0);
  lcd.print("Bienvenido");
  lcd.setCursor(4, 1);
  lcd.print("Tome su ticket");
   //desplazamos una posición a la izquierda
  lcd.scrollDisplayLeft(); 
  delay(1000);
    
  } else {
    lcd.clear();
    lcd.noBacklight();

  }
    
  if (boton1==LOW && boton2==LOW) {
    //ENTRÓ ALGUIEN!
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off (LOW is the voltage level)
    
  } 
}
