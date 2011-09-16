/************************************************************************************
 * 	
 * 	Name    : AtTouch                         
 * 	Author  : Noah Shibley, NoMi Design  nomidesign.net                        
 * 	Date    : July 18th 2011                                    
 * 	Version : 0.1                                              
 * 	Notes   : Arduino Library for use with the AT42QT1070 Q-touch chip via i2c                       
 * 
 * 	Copyright (c) 2011 NoMi Design All right reserved.
 * 
 * 	This file is part of AtTouch.
 * 
 * 		    AtTouch is free software: you can redistribute it and/or modify
 * 		    it under the terms of the GNU General Public License as published by
 * 		    the Free Software Foundation, either version 3 of the License, or
 * 		    (at your option) any later version.
 * 
 * 		    AtTouch is distributed in the hope that it will be useful,
 * 		    but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 		    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 		    GNU General Public License for more details.
 * 
 * 		    You should have received a copy of the GNU General Public License
 * 		    along with AtTouch.  If not, see <http://www.gnu.org/licenses/>.
 * 
 ***********************************************************************************/


#include "AtTouch.h"

AtTouch* AtTouch::pAtTouch = 0; 

/***********************************************************
 * 
 * AtTouch
 * 
 ***********************************************************/
AtTouch::AtTouch()
{
  pAtTouch = this;	//the ptr points to this object
 
}

/***********************************************************
 * 
 * begin
 * 
 ***********************************************************/
void AtTouch::begin(int interruptPin){

  _changePin = interruptPin;
  _interruptVal = interruptPin-2;  //arduino interupt values 0=pin2, 1=pin3
	
  keyHit = false; 
  holdDown_ = false;
  startTime = 0;

  Wire.begin(); 

  // reset device by writing non-zero value to register 0x39  
  Wire.beginTransmission(0x1B); // transmit to device 
  Wire.send(0x39);             // sets register pointer to the reset register (0x39)  
  Wire.send(0xFF);             // send non-zero value to initiate a reset
  Wire.endTransmission();      // stop transmitting 
  delay(100); // wait for device to restart
  Wire.begin(); // re-open the i2c after device has restarted

  pinMode(_changePin, INPUT);
  attachInterrupt(_interruptVal,bttnPressISR,FALLING);  //setup the key change interrupt, call bttnpress on interrupt

}

/***********************************************************
 * 
 * hit
 * 
 ***********************************************************/
boolean AtTouch::hit()
{
  
  return keyHit;
}  

void AtTouch::update()
{
	if (keyHit == true)
	{
		activeKey_ = readActiveKey();
		
	}
	
}



int AtTouch::getKey()
{
	return activeKey_;
}

/***********************************************************
 * 
 * readActiveKey
 * 
 ***********************************************************/
int AtTouch::readActiveKey()
{
  
  
  int keyAddress = readActiveAddress();
  //Serial.println(keyAddress);
  
  int keyValue = 0; //start at one, for key0
  for(int i = keyAddress ;i>0;i = i>>1) //shift until you hit 1, thats which bit place
  {
   keyValue++; //increment keyValue to find bit place
  }
 	activeKey_ = keyValue; //save the keyValue for later
	if(keyValue == 9) { holdDown_ = false; } //9 is key up, so stop press and hold timer

  return keyValue;
  
  
}

/***********************************************************
 * 
 * readActiveAddress
 * 
 ***********************************************************/
int AtTouch::readActiveAddress(){

  if(keyHit == false) //not active return right away
  {
    return -1;
  }
  else
  {

    int readstatus = 0;
    int bttnNum = 0;

    // to clear change int we must read both status bytes 02 and 03
    Wire.beginTransmission(0x1B); // transmit to device 
    Wire.send(0x02); // want to read detection status // set pointer
    Wire.endTransmission();      // stop transmitting
    Wire.requestFrom(0x1B, 1);    // request 1 byte from slave device
    readstatus = Wire.receive();

    Wire.beginTransmission(0x1B); // transmit to device 
    Wire.send(0x03); // want to read key status // set pointer
    Wire.endTransmission();      // stop transmitting
    Wire.requestFrom(0x1B, 1);    // request 1 byte from slave device
    bttnNum = Wire.receive();

    keyHit = false;
    if (readstatus == 1) // seems to trigger int twice for each press... this filters the second one...
    {
      
      if(bttnNum == 0)
      {
        Serial.println("button read error");
      }  
      return bttnNum;
    }

  }



}

boolean AtTouch::hold()
{
  if(holdDown_ == true)
  {
 	  unsigned long currentTime = millis();
	  unsigned long elapsedTime = currentTime - startTime;

	  if (elapsedTime >= 1100) //interval time as passed
	  {
		
		return true; 
	  }
	  else
	  {
		return false;
	  }
   }
   else
   {
	    return false; 
   }	
}


/***********************************************************
 * 
 * bttnPressISR
 * 
 ***********************************************************/
void bttnPressISR()
{
	AtTouch::pAtTouch->keyHit = true;
	AtTouch::pAtTouch->holdDown_ = true;
	AtTouch::pAtTouch->startTime = millis(); //start hold time,TODO figure out how to do this without reading a function
}



