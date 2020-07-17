#include <LiquidCrystal.h>
#include <Chrono.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Chrono g_shot_chrono;

int ledPin = 13;
int buzzer = 12;
int ledStateA = HIGH;
int loopCounter = 0;

String formatZeros(int number) {
  if (number < 10) {
    return "0" + String(number);
  } else {
    return String(number);
  }
}
String formatTimeToString(unsigned long time) {
  unsigned long timeSeconds = time / 1000; // convert the milliseconds in seconds by dividing by 1000
  int mSeconds = time % 1000; // the rest milliseconds what remains after the sharing
  int remainder = timeSeconds % 3600; // calculate the remaining seconds by dividing the rest by 3600. (3600 seconds = 60 seconds x 60 minutes)
  int minutes = remainder / 60; // calculate the minutes by dividing by 60 (1 minute = 60 seconds)
  int seconds = remainder % 60; // calculate the seconds by dividing the rest by 60 (1 minute = 60 seconds)
  //Make 9 -> "009" and 87 -> "087"
  if (mSeconds < 10) {
    mSeconds = "00" + mSeconds;
  } else if (mSeconds < 100) {
    mSeconds = "0" + mSeconds;
  }
  return formatZeros(minutes) + ":" + formatZeros(seconds) + "." + String(mSeconds);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH); 
  lcd.begin(16, 2);
  lcd.print("Get ready..");

  unsigned char i;
  for (i = 3; i > 0; i--) {
    lcd.setCursor(5, 2);
    lcd.print(i);
    if(i==1) {
      delay(750);
      digitalWrite(buzzer, LOW);
      delay(250); 
    }
    else {
      delay(1000);
      digitalWrite(buzzer, HIGH); 
    }
  }
  
  g_shot_chrono.restart();
  lcd.clear();
}

void loop() {
  digitalWrite(buzzer, HIGH); 
  lcd.setCursor(0, 0);
  lcd.print("START");

  digitalWrite(ledPin, ledStateA);
  
  int analogData = analogRead(0);
  if ( (analogData > 600) && (analogData < 750) ) {
    g_shot_chrono.stop();
    ledStateA = LOW;
  }
  if ( (analogData > 400) && (analogData < 500) ) {
    g_shot_chrono.resume();
    ledStateA = HIGH;
  }

  if (g_shot_chrono.hasPassed(3540000)){
    g_shot_chrono.stop();
    lcd.print("Out of range! Max time is 59m.");
  }

  lcd.setCursor(0, 1);
  lcd.print(formatTimeToString(g_shot_chrono.elapsed()));
  loopCounter++;
}
