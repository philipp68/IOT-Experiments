#define ledPin1 11
#define ledPin2 12

#define led1Cycle 100U
#define led2Cycle 275U

unsigned long led1LastMillis = 0;
unsigned long led2LastMillis = 0;

boolean led1State = false;
boolean led2State = false;

boolean cycleCheck(unsigned long *lastMillis, unsigned int cycle) 
{
 unsigned long currentMillis = millis();
 if(currentMillis - *lastMillis >= cycle)
 {
   *lastMillis = currentMillis;
   return true;
 }
 else
   return false;
}

void setup()
{
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
}

void loop()
{
 if(cycleCheck(&led1LastMillis, led1Cycle))
 {
   digitalWrite(ledPin1, led1State);
   led1State = !led1State;
 }
 if(cycleCheck(&led2LastMillis, led2Cycle))
 {
   digitalWrite(ledPin2, led2State);
   led2State = !led2State;
 }
}
