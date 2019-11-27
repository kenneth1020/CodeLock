#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h> //tells to use servo library

Servo myservo; //declares servo
int pos = 0; // LCD Connections

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = { 8, 7, 6, 5 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 4, 3, 2, 1 };
// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char* password = "1234";
char* savePassword = "1234";
char* retypepassword[4] = {0, 0, 0, 0};
char validpassword[4] = {0, 0, 0, 0};
int currentposition = 0;
int buzz = 9;
int invalidcount = 0;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

void setup() {
  displayscreen();
  Serial.begin(9600);
  pinMode(buzz, OUTPUT);
  myservo.attach(10); //SERVO ATTACHED//
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("HELLO");

}

void loop()
{
  if ( currentposition == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reset #");
    lcd.setCursor(0, 2);
    lcd.print("Unlocking *");
  }
  int l ;
  char option = keypad.getKey();
  if (option != NO_KEY) {
    //if user wants to reset password
    if ( option == '#') {
      int k = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Resetting");
      lcd.setCursor(0, 2);
      lcd.print("Old Password");
      while (k == 0) {
        char code = keypad.getKey();
        if (code != NO_KEY) {
          //reseting password
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("PASSWORD:");
          lcd.setCursor(7, 1);
          lcd.print(" ");
          lcd.setCursor(0, 1);
          for (l = 0; l <= currentposition; ++l)
          {
            lcd.print("uwu");
            keypress();
          }
          if (code == password[currentposition])
          {
            ++currentposition;
            if (currentposition == 4)
            {
              passwordReset();
              k = 1;
            }
          }
          else
          {
            ++invalidcount;
            incorrect();
            currentposition = 0;
            k = 1;
          }
        }
      }
    }


    //if user choose option to enter password
    if ( option == '*') {
      int p = 0;
      displayscreen();
      while (p == 0 ) {
        //for password
        char code = keypad.getKey();
        if (code != NO_KEY)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("PASSWORD:");
          lcd.setCursor(7, 1);
          lcd.print(" ");
          lcd.setCursor(0, 1);
          for (l = 0; l <= currentposition; ++l)
          {
            lcd.print("uwu");
            keypress();
          }
          if (code == password[currentposition])
          {
            ++currentposition;
            if (currentposition == 4)
            {
              int a = 0;
              unlockdoor();
              lcd.clear();
              while (a == 0)
              {
                lcd.setCursor(0, 0);
                lcd.print("To relock");
                lcd.setCursor(1, 2);
                lcd.print("Press *");
                char key = keypad.getKey();
                if (key == '*')
                {
                  for (pos = 180; pos >= 0; pos -= 5) // goes from 180 degrees to 0 degrees
                  {
                    myservo.write(pos); // tell servo to go to position in variable 'pos'
                    delay(50); // waits 15ms for the servo to reach the position
                  }

                  currentposition = 0;
                  a = 1;
                  p = 1;
                }
              }//endless loop until user hit * to relock

            }//when currentpostion reach 4

          }//if password is correct code == password

          else
          {
            ++invalidcount;
            incorrect();
            currentposition = 0;
          }
          if (invalidcount == 5)
          {
            ++invalidcount;
            torture1();
            p = 1;

          }
          if (invalidcount == 8)
          {
            torture2();
            p = 1;
          }

        }//end of code putting for user

      }//end of while
      // LOOP ENDS!!!//
    }//end of option if user hit *

  }//end of option NO_KEY

}//end of void loop

//********Password Reseting!!!!***********//
void passwordReset() {
  int count = 0;
  for (int b = 0; b < 4; b++)
  {
    savePassword[b] = password[b];
    Serial.print(password[b]);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("New PASSWORD:");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("New PASSWORD:");
  int y = 0;
  while (y == 0) {
    //checking
    char retype = keypad.getKey();
    if (retype != NO_KEY)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Retype Password:");
      lcd.setCursor(0, 1);
      int l;
      for (l = 0; l <= count; ++l)
      {
        lcd.print("uwu");
        keypress();
      }
      if (retype != '*' && retype != '#')
      {
        retypepassword[count] = retype;
        Serial.println(retype);
        Serial.println(retypepassword[count]);
        ++count;
      }

      if (count == 4)
      {
        verified();
        y = 1;
      }

    }//end of retype NO_KEY
  }//end of while y == 0
}//end password reset method

//********Checking function!!!!***********//
void verified()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Retype New");
  lcd.setCursor(0, 2);
  lcd.print("Password: ");
  int g = 0;
  int pass = 0;
  while (g == 0) {
    char type = keypad.getKey();
    Serial.println(retypepassword[currentposition]);
    if (type != NO_KEY)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Verifying");
      lcd.setCursor(0, 2);
      int l;
      for (l = 0; l <= pass; ++l)
      {
        lcd.print("uwu");
        keypress();
      }
      if (type != '*' && type != '#')
      {
        validpassword[pass] = type;
        ++pass;
      }

      if (pass == 4) {

        if (validpassword[0] == retypepassword[0] &&
            validpassword[1] == retypepassword[1] &&
            validpassword[2] == retypepassword[2] &&
            validpassword[3] == retypepassword[3] )
        {

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("NEW Password:");
          delay(1000);
          lcd.setCursor(0, 2);
          lcd.print("Verified:");
          for (int d = 0; d < 4; d++)
          {
            password[d] = retypepassword[d];
          }
          delay(3000);
          g = 1;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Reset #");
          lcd.setCursor(0, 2);
          lcd.print("Unlocking *");
          currentposition = 0;
          break;
        }//end of if checker

        else
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("NEW Password:");
          delay(1000);
          lcd.setCursor(0, 2);
          lcd.print("Denied:");
          for (int c = 0; c < 4; c++)
          {
            password[c] = savePassword[c];
          }
          g = 1;
          delay(3000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Reset #");
          lcd.setCursor(0, 2);
          lcd.print("Unlocking *");
          currentposition = 0;
          break;
        }//end of else
      }//end of pass ==4
    }//end of while(g==0)
  }//end of new NO_KEY
}//end of verified

//********OPEN THE DOOR FUNCTION!!!!***********//

void unlockdoor()
{
  delay(900);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Access Granted");
  unlockbuzz();

  for (pos = 0; pos <= 180; pos += 5) // goes from 0 degrees to 180 degrees
  { // in steps of 1 degree
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(50);
  }

}

//************WRONG CODE FUNCTION********//

void incorrect()
{
  delay(500);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("CODE");
  delay(1000);
  lcd.setCursor(6, 0);
  lcd.print("INCORRECT");
  lcd.setCursor(15, 1);
  delay(1000);
  lcd.println(" ");
  lcd.setCursor(4, 1);
  lcd.println("GET AWAY!!!");
  delay(1000);

  lcd.setCursor(13, 1);
  lcd.println(" ");
  Serial.println("CODE INCORRECT YOU ARE UNAUTHORIZED");
  digitalWrite(buzz, HIGH);
  delay(3000);
  lcd.clear();
  digitalWrite(buzz, LOW);
  displayscreen();
}
//************** CLEAR THE SCREEN!!!*************//
void clearscreen()
{
  lcd.setCursor(0, 0);
  lcd.println(" ");
  lcd.setCursor(0, 1);
  lcd.println(" ");
  lcd.setCursor(0, 2);
  lcd.println(" ");
  lcd.setCursor(0, 3);
  lcd.println(" ");
}
//**************KEYPRESS********************//
void keypress()
{
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz, LOW);
}
//********DISPALAY FUNCTION!!!*************//
void displayscreen()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("*ENTER THE CODE*");
  lcd.setCursor(1 , 1);
  lcd.println("TO _/_ (OPEN)!!");
}
//*************** ARM SERVO***********//
void armservo()
{

  for (pos = 180; pos <= 180; pos += 5)
  {
    myservo.write(pos);
    delay(5);
  }
  delay(5000);

  for (pos = 180; pos >= 0; pos -= 5)
  {
    myservo.write(pos);
  }

}
//**********UNLOCK BUZZ*************//
void unlockbuzz()
{
  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(80);
  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(200);
  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(80);
  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(80);
}
//**********COUNTER BEEP**********//
void counterbeep()
{
  delay(1200);
  lcd.clear();
  digitalWrite(buzz, HIGH);

  lcd.setCursor(2, 15);
  lcd.println(" ");
  lcd.setCursor(2, 14);
  lcd.println(" ");
  lcd.setCursor(2, 0);
  delay(200);
  lcd.println("GET IN WITHIN:::");

  lcd.setCursor(4, 1);
  lcd.print("5");
  delay(200);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  digitalWrite(buzz, LOW);
  delay(1000);
}
//*********TORTURE1***********//
void torture1()
{
  delay(1000);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("LOL..");
  lcd.clear();
  int t;
  int i;
  for (i = 0; i < 100; i = i + 10) {
    for (t = 666; t < 5000; t = t + 2)
    {
      tone(buzz, t, 5);
    }
    lcd.setCursor(2, 0);
    lcd.print("REEEEEEEE");
    for (t = 5000; t > 666; t = t - 2)
    {
      tone(buzz, t, 5);
    } 
  }
   lcd.clear();
  lcd.setCursor(1, 1);
  lcd.print(" HOW WAS THAT??");
  delay(5000);
  lcd.clear();
  tone(buzz, 0, 10);

}
//*****TORTURE2*****//
void torture2()
{
  delay(1000);
  lcd.setCursor(1, 0);
  lcd.print(" ");
  lcd.setCursor(2, 0);
  lcd.print("EAR DRUMS ARE");
  lcd.setCursor(0, 1);
  lcd.print(" PRECIOUS!! ");
  delay(1500);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(" WAIT FOR");
  lcd.setCursor(4, 1);
  lcd.print(" 1 MINUTE");
  digitalWrite(buzz, HIGH);
  delay(55000);
  counterbeep();
  lcd.clear();
  digitalWrite(buzz, LOW);
  lcd.setCursor(2, 0);
  lcd.print("WANT ME TO");
  lcd.setCursor(1, 1);
  lcd.print("REDICULE MORE??");
  delay(2500);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("RE RE RE RE RE RE");
  delay(1700);
  lcd.clear();
}
