#define DIRECTION 0
#define STEP      1

void setup() 
{
  pinMode(DIRECTION, OUTPUT);
  pinMode(STEP, OUTPUT);

  digitalWrite(DIRECTION, HIGH);
  delay(100);
  for(int x = 0; x < 1074; x++) 
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(1000);
  }
}

void loop() 
{

}
