#define Direction 0
#define Step      1

void setup() {
  pinMode(Direction, OUTPUT);
  pinMode(Step, OUTPUT);

  digitalWrite(0,HIGH);
  for(int x = 0; x < 100; x++) 
  {
    digitalWrite(Step, HIGH);
    delayMicroseconds(5000);
    digitalWrite(Step, LOW);
    delayMicroseconds(5000);
  }
  
}

void loop() 
{

}
