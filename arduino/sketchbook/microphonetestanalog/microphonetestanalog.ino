int Led = 12;
int buttonpin = 7;
int sensorpin = A4;
int sensorvalue = 0;
int val = 0;

void setup() {
  Serial.begin (9600);
  // put your setup code here, to run once:
  pinMode (Led, OUTPUT);
  pinMode (buttonpin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly
  sensorvalue = analogRead (sensorpin);
  if(sensorvalue >= 527)
  {
    digitalWrite (Led, HIGH);
    delay(3000);
  }
  else
  {
    digitalWrite (Led, LOW);
  }
  //delay(5);
  Serial.println (sensorvalue, DEC);

}
