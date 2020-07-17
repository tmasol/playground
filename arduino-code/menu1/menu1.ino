/*+++++++++++++++++++++++++++++++++++++++++++++++++++
Author      : Fahmi Ghani
Date        : 5 July 2015
Project     : LCD Menu Function
Component   : LCD Keypad shield
Description : Simple Menu function on LCD
              Button Function:
                Up/Down - change Menu Page
                Select - enter page
                Left - Exit

Video Link: http://youtu.be/cMqif5ICS5M

+++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int keypad_pin = A0;
int keypad_value = 0;
int keypad_value_old = 0;

char btn_push;

byte mainMenuPage = 1;
byte mainMenuPageOld = 1;
byte mainMenuTotal = 4;

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);  // Initialize a 2x16 type LCD

  MainMenuDisplay();
  delay(1000);
}

void loop() {
  btn_push = ReadKeypad();

  MainMenuBtn();

  // enter selected menu 
  if (btn_push == 'S') {
    WaitBtnRelease();
    switch (mainMenuPage) {
      case 1:
        MenuA();
        break;
      case 2:
        MenuB();
        break;
      case 3:
        MenuC();
        break;
      case 4:
        MenuD();
        break;
    }

    MainMenuDisplay();
    WaitBtnRelease();
  }

  delay(10);

}  //--------------- End of loop() loop ---------------------
void MenuA() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Timer");

  while (ReadKeypad() != 'L') {
    // Insert Task for Menu A here
  }
}
void MenuB() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Review");

  while (ReadKeypad() != 'L') {
    // Insert Task for Menu B here
  }
}
void MenuC() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setting");

  while (ReadKeypad() != 'L') {
    // Insert Task for Menu C here
  }
}
void MenuD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Empty for now");

  while (ReadKeypad() != 'L') {
    // Insert Task for Menu D here
  }
}

void MainMenuDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IPSC Shot timer");
  lcd.setCursor(0, 1);
  switch (mainMenuPage) {
    case 1:
      lcd.print("[Start]");
      break;
    case 2:
      lcd.print("[Review]");
      break;
    case 3:
      lcd.print("[Setting]");
      break;
    case 4:
      lcd.print("[]");
      break;
  }
}

void MainMenuBtn() {
  WaitBtnRelease();
  if (btn_push == 'U') {
    mainMenuPage++;
    if (mainMenuPage > mainMenuTotal) mainMenuPage = 1;
  } else if (btn_push == 'D') {
    mainMenuPage--;
    if (mainMenuPage == 0) mainMenuPage = mainMenuTotal;
  }

  if (mainMenuPage != mainMenuPageOld)  // only update display when page change
  {
    MainMenuDisplay();
    mainMenuPageOld = mainMenuPage;
  }
}

char ReadKeypad() {
  keypad_value = analogRead(keypad_pin);
  if (keypad_value < 50) {
    // Vpravo(RIGHT)
    // return 'R';
    return 'S';
  }
  if ((keypad_value > 95) && (keypad_value < 150)) {
    // Nahoru(UP)
    return 'U';
  } else if ((keypad_value > 250) && (keypad_value < 350)) {
    // Dolu(DOWN)
    return 'D';
  } else if ((keypad_value > 400) && (keypad_value < 500)) {
    // Vlevo(LEFT
    return 'L';
  } else if ((keypad_value > 600) && (keypad_value < 750)) {
    // Vyber(SELECT)
    return 'S';
  } else
    return 'N';
}

void WaitBtnRelease() {
  while (analogRead(keypad_pin) < 800) {}
}
