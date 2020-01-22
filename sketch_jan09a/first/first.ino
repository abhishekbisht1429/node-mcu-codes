int ledPin = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.print("setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH); // turn the LED on
  delay(1000); // wait for a second
  digitalWrite(ledPin, LOW); // turn the LED off
  delay(1000); // wait for a second
  Serial.print("looping");
}
