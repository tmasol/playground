#include <Wire.h>
#include <LiquidCrystal.h>

 //LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int analog = analogRead(0);

 #define ledPin  13                  // LED connected to digital pin 13
 #define buttonPin (analog < 50)                 // button on pin 4
 #define alfaButton ((analog > 700) && (analog < 1024))
 #define charlieButton ((analog > 95) && (analog < 150))
 #define deltaButton ((analog > 250) && (analog < 350))
 #define noshootButton ((analog > 400) && (analog < 500))
 #define subtractButton ((analog > 600) && (analog < 750))
 
 
 int value = LOW;                    // previous value of the LED
 int buttonState;                    // variable to store button state
 int lastButtonState;                // variable to store last button state
 long interval = 100;                // blink interval - change to suit
 long previousMillis = 0;            // variable to store last time LED was updated
 long startTime ;                    // start time for stop watch
 long elapsedTime ;                  // elapsed time for stop watch
 int fractional;                     // variable used to store fractional part of time
 int fractional2;
 
unsigned long LastDebounceTime = 0;
unsigned long DebounceDelay = 50;
unsigned long LastDebounceTime2 = 0;
unsigned long DebounceDelay2 = 50;
unsigned long LastDebounceTime3 = 0;
unsigned long DebounceDelay3 = 50;
unsigned long LastDebounceTime4 = 0;
unsigned long DebounceDelay4 = 50;
unsigned long LastDebounceTime5 = 0;
unsigned long DebounceDelay5 = 50;

 boolean test = false;
 boolean start = false;
 boolean lockout = false;            //**NEW BOOLEAN**
 byte lastbuttonState2 = 0;          // new global variable
 byte buttonState1 = 0;
 byte buttonState2 = 0;
 
 int Points = 0;
 float Faktor = 0;
 float elapsedTime2 ;

 
int SwitchState =0;
int SwitchDebounce;
int LastSwitchState=HIGH;
int LastSwitchDebounce=LOW;
int LastSwitchState2=HIGH;
int LastSwitchDebounce2=LOW;
int LastSwitchState3=HIGH;
int LastSwitchDebounce3=LOW;
int LastSwitchState4=HIGH;
int LastSwitchDebounce4=LOW;
int LastSwitchState5=HIGH;
int LastSwitchDebounce5=LOW;
int Counter=0;
int Counter2=0;
int Counter3=0;
int Counter4=0;
int Counter5=0;

int sensorPin = A1;
int sensorValue = 0;

 void setup()
 {
   Serial.begin(9600);

   lcd.begin(16, 2);
   // Print a message to the LCD.
   lcd.print("PRAKTISK SKYTING");

    lcd.setCursor(0,0);      
    lcd.print("A:");

    lcd.setCursor(-4,1);   
    lcd.print("C:");
    
    lcd.setCursor(-4,2);
    lcd.print("D:");

    lcd.setCursor(-4,3);      
    lcd.print("N:");    

   //pinMode(A0, OUTPUT);         // sets the digital pin as output

   pinMode(buttonPin, INPUT);       // not really necessary, pins default to INPUT anyway
   //digitalWrite(buttonPin, HIGH);   // turn on pullup resistors. Wire button so that press shorts pin to ground.

 }

 void loop()
 { 
  sensorValue = analogRead(sensorPin);  
  
   buttonState2 = digitalRead(buttonPin);
   if(buttonState2 == HIGH){
     if(lockout == false){ // #1
       delay(3000);
       tone(A0, 4000, 1000);
       start = true;
       startTime = millis();
       lastButtonState = buttonState2;
       lockout = true; // (The lockout) this will make sure it does not go back to this IF statement
     }
   }
   if(buttonState2 == HIGH || sensorValue < 28 && start == true){ // #2
     elapsedTime =   millis() - startTime;              // store elapsed time
     lastButtonState = buttonState;                     // store buttonState in lastButtonState, to compare next time

     lcd.setCursor(9,0);

     lcd.print(" ");
     // routine to report elapsed time
     lcd.print( (int)(elapsedTime / 1000UL));         // divide by 1000 to convert to seconds - then cast to an int to print

     lcd.print(".");

     fractional = (int)(elapsedTime % 1000UL);



     lcd.print(fractional);  // print fractional part of time
   }
   //else lcd.clear(); // #3
   

 //_____________________________________________________       
        
  int CurrentSwitch = digitalRead(alfaButton);
  if (CurrentSwitch != LastSwitchDebounce)
  {
    LastDebounceTime = millis();
  } 
  if ((millis() - LastDebounceTime) > DebounceDelay) 
  {
    if (CurrentSwitch != LastSwitchState) 
    {
      if (CurrentSwitch == HIGH)
      {
        Counter=Counter+5;
        lcd.setCursor(2,0); 
        lcd.print(Counter);
      } 
    }
    LastSwitchState=CurrentSwitch;
  }
  LastSwitchDebounce = CurrentSwitch; 
 
 //----------------------------------------
int CurrentSwitch2 = digitalRead(charlieButton);
  if (CurrentSwitch2 != LastSwitchDebounce2)
  {
    LastDebounceTime2 = millis();
  } 
  if ((millis() - LastDebounceTime2) > DebounceDelay) 
  {
    if (CurrentSwitch2 != LastSwitchState2) 
    {
      if (CurrentSwitch2 == HIGH)
      {
        Counter2=Counter2+3;
        lcd.setCursor(2,1); 
        lcd.print(Counter2);
      } 
    }
    LastSwitchState2=CurrentSwitch2;
  }
  LastSwitchDebounce2 = CurrentSwitch2;
  
 //----------------------------------------
int CurrentSwitch3 = digitalRead(deltaButton);
  if (CurrentSwitch3 != LastSwitchDebounce3)
  {
    LastDebounceTime3 = millis();
  } 
  if ((millis() - LastDebounceTime3) > DebounceDelay) 
  {
    if (CurrentSwitch3 != LastSwitchState3) 
    {
      if (CurrentSwitch3 == HIGH)
      {
        Counter3=Counter3+1;
        lcd.setCursor(-2,2); 
        lcd.print(Counter3);
      } 
    }
    LastSwitchState3=CurrentSwitch3;
  }
  LastSwitchDebounce3 = CurrentSwitch3; 
  //----------------------------------------  
  
  int CurrentSwitch4 = digitalRead(noshootButton);
  if (CurrentSwitch4 != LastSwitchDebounce4)
  {
    LastDebounceTime4 = millis();
  } 
  if ((millis() - LastDebounceTime4) > DebounceDelay) 
  {
    if (CurrentSwitch4 != LastSwitchState4) 
    {
      if (CurrentSwitch4 == HIGH)
      {
        Counter4=Counter4+10;
        lcd.setCursor(-2,3); 
        lcd.print(Counter4);
      } 
    }
    LastSwitchState4=CurrentSwitch4;
  }
  LastSwitchDebounce4 = CurrentSwitch4; 
  //---------------------------------------- 
 
 int CurrentSwitch5 = digitalRead(subtractButton);
  if (CurrentSwitch5 != LastSwitchDebounce5)
  {
    LastDebounceTime5 = millis();
  } 
  if ((millis() - LastDebounceTime5) > DebounceDelay) 
  {
    if (CurrentSwitch5 != LastSwitchState5) 
    {
      if (CurrentSwitch5 == HIGH)
      {
        Counter5=Counter5+1;
        //lcd.setCursor(-2,3); 
        //
        lcd.print(Counter5);
      } 
    }
    LastSwitchState5=CurrentSwitch5;
  }
  LastSwitchDebounce5 = CurrentSwitch5; 
  //----------------------------------------   



        Points=Counter+Counter2+Counter3-Counter4-Counter5;
       // Points=Points * 1000;
        
        lcd.setCursor(10,1); 
        lcd.print((int)(Points)); 
       
       lcd.setCursor(5,0);
       lcd.print("TID:"); 
       
       lcd.setCursor(5,1);
       lcd.print("PNG:"); 
       
       lcd.setCursor(1,3);
       lcd.print("FAK:"); 
       
      
      elapsedTime2 = elapsedTime;
      Faktor = (float)Points / (float)elapsedTime2;
      //float half = (float) one / (float) two;
       lcd.setCursor(6,3);
       lcd.print( (float)Faktor * 1000); 
       
Serial.println(sensorValue); 
//delay(100);
      
                                
 }
