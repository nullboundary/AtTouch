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


#ifndef AtTouch_H
#define AtTouch_H

#include <WProgram.h>
#include <Wire.h>



extern "C" void bttnPressISR(void) __attribute__ ((signal)); 


class AtTouch {

public:
  friend void bttnPressISR(void); //make friend so bttnPressISR can access private var keyhit	
 
  AtTouch();
  
  void begin(int interruptPin);
  int readActiveKey(); 
  
  boolean hit();
  int getKey();
  void update();
  boolean hold();

private:

  int readActiveAddress();	
	
  int _changePin;
  int _interruptVal;
  volatile boolean keyHit;
  static AtTouch* pAtTouch; //ptr to AtTouch class for the ISR
  int activeKey_; //the current key num pressed
 volatile boolean holdDown_; //is the button held down, or just pressed
 volatile unsigned long startTime; //the press and hold startTime


};

#endif

