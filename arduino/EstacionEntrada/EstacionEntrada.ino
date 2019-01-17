// El numero de los pines:
int button_1 = 12;
int button_2 = 7;
int rele = 8;

void setup()
{
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  pinMode(rele, OUTPUT);
}
//Las señales provenientes de los pines se leen y se les hace un and
//De tal manera que si ambos pulsadores estan bajos, se activa el relé
void loop()
{
  digitalWrite(rele, (digitalRead(button_1) && digitalRead(button_2)));
}
