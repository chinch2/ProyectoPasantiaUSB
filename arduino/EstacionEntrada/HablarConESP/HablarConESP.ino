/* Serial pass through for teensy */

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{
  /* send everything received from the hardware uart to usb serial & vv */
  if (Serial.available() > 0) {
    char ch = Serial.read();
    Serial1.print(ch);
  }
  if (Serial1.available() > 0) {
    char ch = Serial1.read();
    Serial.print(ch);
  }
}
