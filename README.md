```
Name    : AtTouch Readme                    
Author  : Noah Shibley                       
Date    : July 31th 2011                                    
Version : 0.1                                              
Notes   : Arduino Library for the Atmel AT42QT1070 QTouch 7-channel Sensor IC via i2c
```

Works with Wire or I2c libraries for arduino. 

### Functions

```cpp
begin(int interruptPin); //initializes and configures the library
hit(); //returns whether a key has been hit or not, True/False
getKey(); //returns the keyNum currently held down.
readActiveKey(); //returns the keyNum currently pressed. 
hold(); //returns whether or not the a key has been held for 900ms 
```
