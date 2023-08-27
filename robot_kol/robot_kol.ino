#define EN        8

int   adcValue1         = 0;
int   adcValue2         = 0;
int   direction_info    = 0;
int   direction         = 0;
bool  counter           = false;
float ssDelay;

typedef struct
{
  byte stepPin;
  byte dirPin;
  int limit;
  int currentPos;
  int topSpdDelay;
  int slowSpdDelay;
  float acclrt_ratio;
}
steppers;

steppers s1;

void setup()
{
  Serial.begin(9600);

  if(!initSteppers())
  {
    Serial.println("Initialization faied!");
    for(;;);
  }
}

void loop()
{
  driveOnCommand(s1, findDirection(A0, A1));
  // driveOnCommand(s1, findDummyDirection());
  // driveToPosition(s1, 5000);
}

bool initSteppers()
{
  // steppers s1, s2, s3, s4, s5, s6, s7, s8;
  pinMode(EN, OUTPUT);

  s1.stepPin = 2;
  s1.dirPin = 5;
  s1.limit = 4000;
  s1.currentPos = 0;
  s1.topSpdDelay = 300;
  s1.slowSpdDelay = 6000;
  s1.acclrt_ratio = 0.995;

  pinMode(s1.stepPin, OUTPUT);
  pinMode(s1.dirPin, OUTPUT);

  // s2.stepPin = 2;
  // s2.dirPin = 3;
  // s2.limit = 100;
  // s2.currentPos = 0;
  // s2.topSpdDelay = 1000;
  // s2.slowSpdDelay = 10000;
  // s2.acclrt_ratio = 0.9975;

  // pinMode(s2.stepPin, OUTPUT);
  // pinMode(s2.dirPin, OUTPUT);

  // s3.stepPin = 4;
  // s3.dirPin = 5;
  // s3.limit = 100;
  // s3.currentPos = 0;
  // s3.topSpdDelay = 1000;
  // s3.slowSpdDelay = 10000;
  // s3.acclrt_ratio = 0.9975;

  // pinMode(s3.stepPin, OUTPUT);
  // pinMode(s3.dirPin, OUTPUT);

  // s4.stepPin = 6;
  // s4.dirPin = 7;
  // s4.limit = 100;
  // s4.currentPos = 0;
  // s4.topSpdDelay = 1000;
  // s4.slowSpdDelay = 10000;
  // s4.acclrt_ratio = 0.9975;

  // pinMode(s4.stepPin, OUTPUT);
  // pinMode(s4.dirPin, OUTPUT);

  // s5.stepPin = 8;
  // s5.dirPin = 9;
  // s5.limit = 100;
  // s5.currentPos = 0;
  // s5.topSpdDelay = 1000;
  // s5.slowSpdDelay = 10000;
  // s5.acclrt_ratio = 0.9975;

  // pinMode(s5.stepPin, OUTPUT);
  // pinMode(s5.dirPin, OUTPUT);

  // s6.stepPin = 10;
  // s6.dirPin = 11;
  // s6.limit = 100;
  // s6.currentPos = 0;
  // s6.topSpdDelay = 1000;
  // s6.slowSpdDelay = 10000;
  // s6.acclrt_ratio = 0.9975;

  // pinMode(s6.stepPin, OUTPUT);
  // pinMode(s6.dirPin, OUTPUT);

  // s7.stepPin = 12;
  // s7.dirPin = 13;
  // s7.limit = 100;
  // s7.currentPos = 0;
  // s7.topSpdDelay = 1000;
  // s7.slowSpdDelay = 10000;
  // s7.acclrt_ratio = 0.9975;

  // pinMode(s7.stepPin, OUTPUT);
  // pinMode(s7.dirPin, OUTPUT);

  // s8.stepPin = 14;
  // s8.dirPin = 15;
  // s8.limit = 100;
  // s8.currentPos = 0;
  // s8.topSpdDelay = 1000;
  // s8.slowSpdDelay = 10000;
  // s8.acclrt_ratio = 0.9975;

  // pinMode(s8.stepPin, OUTPUT);
  // pinMode(s8.dirPin, OUTPUT);

  return true;
}

void driveOnCommand(steppers _stp, int dirIn)
{
  if(!counter)
  {
    counter = true;
    ssDelay = _stp.slowSpdDelay;
  }

  digitalWrite(EN, LOW);

  if(dirIn == 1)
  {
    if(direction == 0)
    {
      /* accelerating */
      direction = 1;
      digitalWrite(_stp.dirPin, LOW);
      while(ssDelay > _stp.topSpdDelay)
      {
        digitalWrite(_stp.stepPin, HIGH);
        delayMicroseconds(ssDelay);
        digitalWrite(_stp.stepPin, LOW);
        delayMicroseconds(ssDelay);
        ssDelay *= _stp.acclrt_ratio;
        //Serial.println(ssDelay);
      }
    }

    else if(direction == 2)
    {
      /* deaccelerating */
      digitalWrite(_stp.dirPin, HIGH);
      while(ssDelay < _stp.slowSpdDelay)
      {
        digitalWrite(_stp.stepPin, HIGH);
        delayMicroseconds(ssDelay);
        digitalWrite(_stp.stepPin, LOW);
        delayMicroseconds(ssDelay);
        ssDelay /= _stp.acclrt_ratio;
      }

      if(dirIn == 1)
      {
        /* accelerating */
        direction = 1;
        digitalWrite(_stp.dirPin, LOW);
        while(ssDelay > _stp.topSpdDelay)
        {
          digitalWrite(_stp.stepPin, HIGH);
          delayMicroseconds(ssDelay);
          digitalWrite(_stp.stepPin, LOW);
          delayMicroseconds(ssDelay);
          ssDelay *= _stp.acclrt_ratio;
        }
      }
    }

    /* top speed driving */
    if(ssDelay <= _stp.topSpdDelay)
    {
      digitalWrite(_stp.stepPin, HIGH);
      delayMicroseconds(_stp.topSpdDelay); 
      digitalWrite(_stp.stepPin, LOW);
      delayMicroseconds(_stp.topSpdDelay);
    }
  }

  else if(dirIn == 2)
  {

    if(direction == 0)
    {
      /* accelerating */
      direction = 2;
      digitalWrite(_stp.dirPin, HIGH);
      while(ssDelay > _stp.topSpdDelay)
      {
        digitalWrite(_stp.stepPin, HIGH);
        delayMicroseconds(ssDelay);
        digitalWrite(_stp.stepPin, LOW);
        delayMicroseconds(ssDelay);
        ssDelay *= _stp.acclrt_ratio;
      }
    }

    else if(direction == 1)
    {
      /* deaccelerating */
      digitalWrite(_stp.dirPin, LOW);
      while(ssDelay < _stp.slowSpdDelay)
      {
        digitalWrite(_stp.stepPin, HIGH);
        delayMicroseconds(ssDelay);
        digitalWrite(_stp.stepPin, LOW);
        delayMicroseconds(ssDelay);
        ssDelay /= _stp.acclrt_ratio;
      }

      if(dirIn == 2)
      {
        /* accelerating */
        direction = 2;
        digitalWrite(_stp.dirPin, HIGH);
        while(ssDelay > _stp.topSpdDelay)
        {
          digitalWrite(_stp.stepPin, HIGH);
          delayMicroseconds(ssDelay);
          digitalWrite(_stp.stepPin, LOW);
          delayMicroseconds(ssDelay);
          ssDelay *= _stp.acclrt_ratio;
        }
      }
    }

    /* top speed driving */
    if(ssDelay <= _stp.topSpdDelay)
    {
      digitalWrite(_stp.stepPin, HIGH);
      delayMicroseconds(_stp.topSpdDelay); 
      digitalWrite(_stp.stepPin, LOW);
      delayMicroseconds(_stp.topSpdDelay);
    }
  }
}

void driveToPosition(steppers stp, int targetPos)
{
  /* enable stepper */
  digitalWrite(EN, LOW);

  /* check for limits */
  targetPos > stp.limit ? targetPos = stp.limit : targetPos = targetPos;
  targetPos < 0 ? targetPos = 0 : targetPos = targetPos;
  /* check for direction */
  targetPos > stp.currentPos ? digitalWrite(stp.dirPin, LOW) : digitalWrite(stp.dirPin, HIGH);
  /* calculations for accelerating */
  int positionDiff = abs(stp.currentPos - targetPos);
  float slowSpdDelay = stp.slowSpdDelay;
  int counter = 0;
  int topSpdLoop;
  
  /* for debugging */

  // Serial.print("target pos: ");
  // Serial.println(targetPos);

  // Serial.print("current pos: ");
  // Serial.println(stp.currentPos);

  // Serial.print("position diff: ");
  // Serial.println(positionDiff);

  // Serial.print("topSpdLoop: ");
  // Serial.println(topSpdLoop);

  // Serial.print("slowSpdDelay: ");
  // Serial.println(slowSpdDelay);

  // Serial.print("topSpdDelay: ");
  // Serial.println(stp.topSpdDelay);

  /* increasing speed */
  while(slowSpdDelay > stp.topSpdDelay)
  {
    digitalWrite(stp.stepPin, HIGH);
    delayMicroseconds(slowSpdDelay);
    digitalWrite(stp.stepPin, LOW);
    delayMicroseconds(slowSpdDelay);
    slowSpdDelay *= stp.acclrt_ratio;
    counter++;
  }

  topSpdLoop = positionDiff - (2 * counter);

  /* top speed driving */
  for(int j = 0; j < topSpdLoop; j++)
  {
    digitalWrite(stp.stepPin, HIGH);
    delayMicroseconds(stp.topSpdDelay);
    digitalWrite(stp.stepPin, LOW);
    delayMicroseconds(stp.topSpdDelay);
  }
  
  /* decreasing speed */
  while(slowSpdDelay < stp.slowSpdDelay)
  {
    digitalWrite(stp.stepPin, HIGH);
    delayMicroseconds(slowSpdDelay);
    digitalWrite(stp.stepPin, LOW);
    delayMicroseconds(slowSpdDelay);
    slowSpdDelay /= stp.acclrt_ratio;
  }


  /* enable stepper */
  digitalWrite(EN, HIGH);
}

bool findDirection(byte analogPin1, byte analogPin2)
{
    adcValue1 = analogRead(analogPin1);
    adcValue2 = analogRead(analogPin2);

		/* set the blind spot */
		if(adcValue1 > 550)
		{
			adcValue1 = adcValue1 - 550;
		}
		else if(adcValue1 < 450)
		{
			adcValue1 = adcValue1 - 450;
		}
		else
		{
			adcValue1 = 0; //max 1945 //min -1945
		}

		if(adcValue2 > 550)
		{
			adcValue2 = adcValue2 - 550;
		}
		else if(adcValue2 < 450)
		{
			adcValue2 = adcValue2 - 450;
		}
		else
		{
			adcValue2 = 0; //max 1095 //min -2760
		}


		/* determine the direction */
		if((adcValue1 != 0) || (adcValue2 != 0))
		{
			if((adcValue1 > 0) && (adcValue2 == 0))
			{
				direction_info = 0x01; //RIGHT
        // Serial.print("Direction: ");
        // Serial.println("Right");
			}
			else if((adcValue1 > 0) && (adcValue2 < 0))
			{
				if((adcValue1) > abs(adcValue2))
				{
					direction_info = 0x01; //RIGHT
          // Serial.print("Direction: ");
          // Serial.println("Right");
				}
				else
				{
					direction_info = 0x08; //DOWN
          // Serial.print("Direction: ");
          // Serial.println("Down");
          return 1;
				}
			}
			else if((adcValue1 == 0) && (adcValue2 < 0))
			{
				direction_info = 0x08; //DOWN
          // Serial.print("Direction: ");
          // Serial.println("Down");
          return 1;
			}
			else if((adcValue1 < 0) && (adcValue2 < 0))
			{
				if(abs(adcValue1) > abs(adcValue2))
				{
					direction_info = 0x02; //LEFT
          // Serial.print("Direction: ");
          // Serial.println("Left");
				}
				else
				{
					direction_info = 0x08; //DOWN
          // Serial.print("Direction: ");
          // Serial.println("Down");
          return 1;
				}
			}
			else if((adcValue1 < 0) && (adcValue2 == 0))
			{
				direction_info = 0x02; //LEFT
        // Serial.print("Direction: ");
        // Serial.println("Left");
			}
			else if((adcValue1 < 0) && (adcValue2 > 0))
			{
				if(abs(adcValue1) > adcValue2)
				{
					direction_info = 0x02; //LEFT
          // Serial.print("Direction: ");
          // Serial.println("Left");
				}
				else
				{
					direction_info = 0x04; //UP
          // Serial.print("Direction: ");
          // Serial.println("Up");
          return 2;
				}
			}
			else if((adcValue1 == 0) && (adcValue2 > 0))
			{
				direction_info = 0x04; //UP
        // Serial.print("Direction: ");
        // Serial.println("Up");
        return 2;
			}
			else if((adcValue1 > 0) && (adcValue2 > 0))
			{
				if(adcValue1 > adcValue2)
				{
					direction_info = 0x01; //RIGHT
          // Serial.print("Direction: ");
          // Serial.println("Right");
				}
				else
				{
					direction_info = 0x04; //UP
          // Serial.print("Direction: ");
          // Serial.println("Up");
          return 2;
				}
			}
		}

    return 0;
}

unsigned long time;

int findDummyDirection()
{
  time = (millis() % 10000);
  //Serial.println(time);

   if(time < 5000)
  {
    return 1;
  }
  else
  {
    return 2;
  }
}
