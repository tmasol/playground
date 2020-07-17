#include <LiquidCrystal.h>

// Teploměr a vlhkoměr DHT11/22

// připojení knihovny DHT
#include "DHT.h"
// nastavení čísla pinu s připojeným DHT senzorem
#define pinDHT 12

// odkomentování správného typu čidla
#define typDHT11 DHT11     // DHT 11
//#define typDHT22 DHT22   // DHT 22 (AM2302)

// inicializace DHT senzoru s nastaveným pinem a typem senzoru
DHT mojeDHT(pinDHT, typDHT11);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600); 
   lcd.begin(16, 2);
  
  lcd.setCursor(0,0);
lcd.print("Teplota");

  // zapnutí komunikace s teploměrem DHT
  mojeDHT.begin();
}

void loop() {
  // pomocí funkcí readTemperature a readHumidity načteme
  // do proměnných tep a vlh informace o teplotě a vlhkosti,
  // čtení trvá cca 250 ms
  float tep = mojeDHT.readTemperature();
  float vlh = mojeDHT.readHumidity();
  // kontrola, jestli jsou načtené hodnoty čísla pomocí funkce isnan


  
  if (isnan(tep) || isnan(vlh)) {
    // při chybném čtení vypiš hlášku
    Serial.println("Chyba při čtení z DHT senzoru!");
  } else {
    // pokud jsou hodnoty v pořádku,
    // vypiš je po sériové lince

    lcd.setCursor(0, 2);
    lcd.print(tep);
    lcd.print("C");

     lcd.setCursor(9, 2);
     lcd.print(vlh);
     lcd.print("%");
    
    Serial.print("Teplota: "); 
    Serial.print(tep);
    Serial.print(" stupnu Celsia, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlh);
    Serial.println("  %");
  }
  // pauza pro přehlednější výpis

  
  delay(1250);
}
