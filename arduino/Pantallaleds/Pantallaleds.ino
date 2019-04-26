int timer = 100;
int segment[] = {0, 1, 2, 3, 4, 5, 13};
int anode[] = {7, 8, 9, 10};
void setup() {
  // put your setup code here, to run once:
  for (int thisPin = 0; thisPin < 6; thisPin++) {
    digitalWrite(segment[thisPin], HIGH);
    pinMode(segment[thisPin], OUTPUT);
  }
  for (int thisPin = 0; thisPin < 3; thisPin++) {
    digitalWrite(anode[thisPin], HIGH);
    pinMode(anode[thisPin], OUTPUT);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 3; i++) {
    digitalWrite(anode[i], LOW);
    for (int j = 0; j < 7; j++) {
      digitalWrite(segment[j], LOW);
      //delay(100);
    }
    delay(6);
    for (int j = 0; j < 7; j++) {
      digitalWrite(segment[j], HIGH);
    }
    //delay(100);
    digitalWrite(anode[i], HIGH);
  }

}
