int Led = 12;
int buttonpin = 7;
int sensorpin = A5;
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
  val = digitalRead(buttonpin);
  if (val == HIGH)
  {
    digitalWrite (Led, HIGH);
    delay(3000);
  }
  else
  {
    digitalWrite (Led, LOW);
  } 

  sensorvalue = analogRead (sensorpin);
  //delay(5);
  Serial.println (sensorvalue, DEC);

}
