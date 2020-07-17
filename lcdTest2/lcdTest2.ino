// Arduino LCD 16x2 Shield

// připojení knihovny
#include <LiquidCrystal.h>
// inicializace LCD displeje
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// nastavení čísla propojovacího pinu
// pro osvětlení LCD displeje
#define lcdSvit 10

void setup() {
  // zahájení komunikace s displejem,
  // 16 znaků, 2 řádky
  lcd.begin(16, 2);
  
}

void loop() {
  // načtení údajů z analogového pinu A0 do proměnné
  int analogData = analogRead(0);

  lcd.setCursor(0,0);
  // vytištění textu na displej
  lcd.print("Stisknuto:      ");
  // nastavení výpisu na třináctý znak, první řádek
  lcd.setCursor(12, 0);
  // vytištění textu na displej
  lcd.print(analogData);
  // nastavení výpisu na třetí znak, druhý řádek
  lcd.setCursor(2, 1);
  // vytištění textu na displej pomocí zavolání funkce
  // s předáním aktuálně změřené hodnoty na vstupu
  lcd.print(nactiTlacitka(analogData));

}
String nactiTlacitka(int analog) {
  // proměnná pro uložení textu pro výpis
  String text;
  // postupná kontrola pomocí podmínek if,
  // pro každé tlačítko je uveden rozsah hodnot,
  // ve kterých je detekováno a poté nastaven text na výstup
  if (analog < 50) text = "Vpravo(RIGHT)";
  if ((analog > 700) && (analog < 1024)) text = "             ";
  if ( (analog > 95) && (analog < 150) ) text = "Nahoru(UP)";
  if ( (analog > 250) && (analog < 350) ) text = "Dolu(DOWN)";
  if ( (analog > 400) && (analog < 500) ) text = "Vlevo(LEFT)";
  if ( (analog > 600) && (analog < 750) ) text = "Vyber(SELECT)";
  // vrácení textu jako výstup funkce
  return text;
}
