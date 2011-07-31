#include <Wire.h>
#include <AtTouch.h>

int interruptPin = 3;
int ledPin = 13; 

AtTouch touch;

int hitKeyVal;
boolean keyDown = false;

void setup()
{
  touch.begin(interruptPin);
  Serial.begin(9600);
  pinMode(13,OUTPUT);

  Serial.println("ATTouch Lib v0.1 by nomidesign.net");

}


void loop()
{
  
  digitalWrite(ledPin,LOW);

  if(touch.pressHold() == true) //press and hold
  {
    keyDown = true; 
    hitKeyVal = touch.getKey();
  }

  if(touch.hit() == true) //just press once
  { 
    keyDown = true;
    hitKeyVal = touch.readActiveKey(); //read which key was hit
  } 


  if(keyDown == true)
  {
    keyDown = false;
    digitalWrite(ledPin,HIGH);
    
    if(hitKeyVal == 9) //key #9 is end of key press signal (key up)
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


