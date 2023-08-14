int  adcValue1         = 0x00;
int  adcValue2         = 0x00;
int  direction_info    = 0x00;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  find_direction();
  delay(100);
}

void find_direction()
{
		//Setting the blind spot
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


		//Determining the direction
		if((adcValue1 != 0) || (adcValue2 != 0))
		{
			if((adcValue1 > 0) && (adcValue2 == 0))
			{
				direction_info = 0x01; //RIGHT
        Serial.print("Direction: ");
        Serial.println("Right");
			}
			else if((adcValue1 > 0) && (adcValue2 < 0))
			{
				if((adcValue1) > abs(adcValue2))
				{
					direction_info = 0x01; //RIGHT
          Serial.print("Direction: ");
          Serial.println("Right");
				}
				else
				{
					direction_info = 0x08; //DOWN
          Serial.print("Direction: ");
          Serial.println("Down");
				}
			}
			else if((adcValue1 == 0) && (adcValue2 < 0))
			{
				direction_info = 0x08; //DOWN
          Serial.print("Direction: ");
          Serial.println("Down");
			}
			else if((adcValue1 < 0) && (adcValue2 < 0))
			{
				if(abs(adcValue1) > abs(adcValue2))
				{
					direction_info = 0x02; //LEFT
          Serial.print("Direction: ");
          Serial.println("Left");
				}
				else
				{
					direction_info = 0x08; //DOWN
          Serial.print("Direction: ");
          Serial.println("Down");
				}
			}
			else if((adcValue1 < 0) && (adcValue2 == 0))
			{
				direction_info = 0x02; //LEFT
        Serial.print("Direction: ");
        Serial.println("Left");
			}
			else if((adcValue1 < 0) && (adcValue2 > 0))
			{
				if(abs(adcValue1) > adcValue2)
				{
					direction_info = 0x02; //LEFT
          Serial.print("Direction: ");
          Serial.println("Left");
				}
				else
				{
					direction_info = 0x04; //UP
          Serial.print("Direction: ");
          Serial.println("Up");
				}
			}
			else if((adcValue1 == 0) && (adcValue2 > 0))
			{
				direction_info = 0x04; //UP
        Serial.print("Direction: ");
        Serial.println("Up");
			}
			else if((adcValue1 > 0) && (adcValue2 > 0))
			{
				if(adcValue1 > adcValue2)
				{
					direction_info = 0x01; //RIGHT
          Serial.print("Direction: ");
          Serial.println("Right");
				}
				else
				{
					direction_info = 0x04; //UP
          Serial.print("Direction: ");
          Serial.println("Up");
				}
			}
		}
}
