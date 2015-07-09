```
Name    : AtTouch Readme                    
Author  : Noah Shibley, NoMi Design  nomidesign.net                        
Date    : July 31th 2011                                    
Version : 0.1                                              
Notes   : Arduino Library for the Atmel AT42QT1070 QTouch 7-channel Sensor IC via i2c
```

A setup tutorial:
http://nomidesign.net/2011/08/01/attouch-library-for-arduino-and-the-at42qt1070/


### Functions

```cpp
begin(int interruptPin); //initializes and configures the library
hit(); //returns whether a key has been hit or not, True/False
getKey(); //returns the keyNum currently held down.
readActiveKey(); //returns the keyNum currently pressed. 
hold(); //returns whether or not the a key has been held for 900ms 
```
