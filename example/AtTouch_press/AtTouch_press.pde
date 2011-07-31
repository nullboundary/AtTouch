#include <Wire.h>
#include <AtTouch.h>

int interruptPin = 3; //only 2 or 3 are external interrupt pins on the arduino UNO

AtTouch touch;

int hitKeyNum;
int ledPin = 13; 


void setup()
{
  touch.begin(interruptPin);
  Serial.begin(9600);
  pinMode(13,OUTPUT);

  Serial.println("ATTouch Lib v0.1 by nomidesign.net");

  
}


void loop()
{
	
  digitalWrite(ledPin.LOW); 	
	
  if(touch.hit() == true) //checks if the hit flag has been triggered by the interrupt 
  {
		hitKeyNum = touch.readActiveKey();
	    digitalWrite(ledPin,HIGH);

	    if(hitKeyNum == 9) //key #9 is end of key press signal (key up)
	    {
	      Serial.println("keyUP"); 
	    }
	    else
	    {
	        Serial.print("button #");
	        Serial.print(hitKeyVal);  
	        Serial.println(" Down");
	    }
  }
  
}
