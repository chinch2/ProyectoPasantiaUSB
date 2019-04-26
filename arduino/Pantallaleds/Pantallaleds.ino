int timer = 100;
int segment[] = {0, 1, 2, 3, 4, 5, 6};
int anode[] = {7, 8, 9, 10};
void setup() {
  // put your setup code here, to run once:
  for (int thisPin = 0; thisPin < 7; thisPin++) {
    digitalWrite(segment[thisPin], HIGH);
    pinMode(segment[thisPin], OUTPUT);
  }

  for (int thisPin = 0; thisPin < 4; thisPin++) {
    digitalWrite(anode[thisPin], HIGH);
    pinMode(anode[thisPin], OUTPUT);
  }
}
void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(anode[0], LOW);

  digitalWrite(segment[0], HIGH);
  digitalWrite(segment[1], HIGH);
  digitalWrite(segment[2], HIGH);
  digitalWrite(segment[3], HIGH);
  digitalWrite(segment[4], LOW);
  digitalWrite(segment[5], LOW);
  digitalWrite(segment[6], HIGH);

  delay(5);

  digitalWrite(segment[0], HIGH);
  digitalWrite(segment[1], HIGH);
  digitalWrite(segment[2], HIGH);
  digitalWrite(segment[3], HIGH);
  digitalWrite(segment[4], HIGH);
  digitalWrite(segment[5], HIGH);
  digitalWrite(segment[6], HIGH);

  digitalWrite(anode[0], HIGH);

  digitalWrite(anode[1], LOW);

  digitalWrite(segment[0], LOW);
  digitalWrite(segment[1], LOW);
  digitalWrite(segment[2], HIGH);
  digitalWrite(segment[3], LOW);
  digitalWrite(segment[4], LOW);
  digitalWrite(segment[5], HIGH);
  digitalWrite(segment[6], LOW);

  delay(5);

  digitalWrite(segment[0], HIGH);
  digitalWrite(segment[1], HIGH);
  digitalWrite(segment[2], HIGH);
  digitalWrite(segment[3], HIGH);
  digitalWrite(segment[4], HIGH);
  digitalWrite(segment[5], HIGH);
  digitalWrite(segment[6], HIGH);

  digitalWrite(anode[1], HIGH);

  digitalWrite(anode[2], LOW);

  digitalWrite(segment[0], HIGH);
  digitalWrite(segment[1], HIGH);
  digitalWrite(segment[2], HIGH);
  digitalWrite(segment[3], HIGH);
  digitalWrite(segment[4], LOW);
  digitalWrite(segment[5], LOW);
  digitalWrite(segment[6], HIGH);

  delay(5);

  digitalWrite(segment[0], HIGH);
  digitalWrite(segment[1], HIGH);
  digitalWrite(segment[2], HIGH);
  digitalWrite(segment[3], HIGH);
  digitalWrite(segment[4], HIGH);
  digitalWrite(segment[5], HIGH);
  digitalWrite(segment[6], HIGH);

  digitalWrite(anode[2], HIGH);

  digitalWrite(anode[3], LOW);

  digitalWrite(segment[0], HIGH);
  digitalWrite(segment[1], HIGH);
  digitalWrite(segment[2], HIGH);
  digitalWrite(segment[3], HIGH);
  digitalWrite(segment[4], LOW);
  digitalWrite(segment[5], LOW);
  digitalWrite(segment[6], HIGH);

  delay(5);

  digitalWrite(segment[0], HIGH);
  digitalWrite(segment[1], HIGH);
  digitalWrite(segment[2], HIGH);
  digitalWrite(segment[3], HIGH);
  digitalWrite(segment[4], HIGH);
  digitalWrite(segment[5], HIGH);
  digitalWrite(segment[6], HIGH);

  digitalWrite(anode[3], HIGH);

  digitalWrite(anode[4], LOW);

  digitalWrite(segment[0], HIGH);
  digitalWrite(segment[1], HIGH);
  digitalWrite(segment[2], HIGH);
  digitalWrite(segment[3], HIGH);
  digitalWrite(segment[4], LOW);
  digitalWrite(segment[5], LOW);
  digitalWrite(segment[6], HIGH);

  delay(5);

  digitalWrite(segment[0], HIGH);
  digitalWrite(segment[1], HIGH);
  digitalWrite(segment[2], HIGH);
  digitalWrite(segment[3], HIGH);
  digitalWrite(segment[4], HIGH);
  digitalWrite(segment[5], HIGH);
  digitalWrite(segment[6], HIGH);

  digitalWrite(anode[4], HIGH);

}
