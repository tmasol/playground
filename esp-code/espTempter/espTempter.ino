#include "DHT.h"
DHT mojeDHT(D4, DHT11);

void setup() {
  mojeDHT.begin();
  Serial.begin(9600);
}

void loop() {
  
  float tep = mojeDHT.readTemperature();
  float vlh = mojeDHT.readHumidity();

  if (isnan(tep) || isnan(vlh)) {
    Serial.println("Chyba při čtení z DHT senzoru!");
  } 
  else {

    Serial.print("Teplota: "); 
    Serial.print(tep);
    Serial.print(" stupnu Celsia, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlh);
    Serial.println("  %");
    
  }

  delay(5000);
  
}
