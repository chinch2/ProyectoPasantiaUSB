static uint32_t timer = 0;
//int segment[] = {0, 1, 2, 3, 4, 5, 6};
int n[10] = {B01000000, B01001111, B00010010, B00000110, B00001101, B00100100, B00100000, B01001110, B00000000, B00001100}; // 0-9
int a[4] = {B00001110, B00001101, B00001011, B00000111};
int h[4] = {0, 0, 0, 0};
int mins = (h[2] * 10) + h[3];
int horas = (h[0] * 10) + h[1];
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  DDRD = B11111111; //PINS 0-7 OUTPUT
  DDRB = B11111111; //PINS 8-13 OUTPUT
  PORTD = B11111111;
  PORTB = B00001111;
  /*for (int thisPin = 0; thisPin < 7; thisPin++) {
    digitalWrite(segment[thisPin], HIGH);
    pinMode(segment[thisPin], OUTPUT);
    }

    for (int thisPin = 0; thisPin < 4; thisPin++) {
    digitalWrite(anode[thisPin], HIGH);
    pinMode(anode[thisPin], OUTPUT);
    }*/
}
void loop() {

  //-------CLOCK-------
  if (millis() - timer > 60000) {//pasó un minuto

    mins = (h[2] * 10) + h[3];

    horas = (h[0] * 10) + h[1];

    mins++;
    timer = millis();

    if (mins > 59) {

      mins = 0;
      horas++;

    }

    if (horas > 23) horas = 0;


    h[0] = horas / 10;
    h[1] = horas % 10;
    h[2] = mins / 10;
    h[3] = mins % 10;
  }
  disp(h);
  //Serial.println(timer);
  //Serial.println(millis());
}

void disp (int o[4]) {

  for (int i = 0; i < 4; i++) {

    PORTB = a[i];

    PORTD = n[o[i]];

    delay(5);

    PORTD = B11111111;

    PORTB = 00001111;

  }

}
