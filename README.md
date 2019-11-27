# CodeLock
Arduino project making a code locking system 
# Files
Testing_keypad.ino

Final Project CPSC42.docx
# Description
This project is show case the basic of a safe electric security system. With all the basic function. Screen display for instruction and show the user his/her input. With the function to reset your password or just unlock the safe. The default password is [1234]. 

If you want to unlock, the LCD screen display # reset and * Unlock  
	
If you hit * pound key for unlocking. It will ask for the password. When password is type correctly the servo motor will mover all the way to 180. To place the servo motor back just hit the * pound key. The motor will move back to its original place to relock. 

If you hit # hash tag for the reset. It will ask you for the password. When you got the password correct then it will ask you for the new password and verified it. Then it will become your new password. If you get your verification wrong, then your old password will remain.

If password is type wrong, you'll get yell at. Do this enough time and program will initiate alarm or torture.
# Usage
#include <Keypad.h>

#include <LiquidCrystal.h>

#include <Servo.h> //tells to use servo library

# Authors and acknowledgment
https://gist.github.com/gannybuzz/02bf3ad4c3db1268b29c
