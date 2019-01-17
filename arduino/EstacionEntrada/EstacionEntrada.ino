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
}
//Las señales provenientes de los pines se leen y se les hace un and
//De tal manera que si ambos pulsadores estan bajos, se activa el relé
//Inicio con el led apagado
 
  //----------------MIENTRAS NO TENGO EL RELÉ---------------------
void loop()
{//----------------MIENTRAS NO TENGO EL RELÉ---------------------
  
  
  //leo el estado de botones que son entradas digitales
  
  boton1 = digitalRead(button_1);
  boton2 = digitalRead(button_2);
    //----------------MIENTRAS NO TENGO EL RELÉ---------------------
  if (boton1==LOW && boton2==LOW) {

    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
     digitalWrite(LED_BUILTIN, LOW);
  } 
  //----------------MIENTRAS NO TENGO EL RELÉ---------------------
}
