#include <IRremote.h>

#define PIN_IR 3
#define PIN_DETECT 2

IRsend irsend;
void setup() {
  Serial.begin(9600);
  pinMode(PIN_DETECT, INPUT);
  pinMode(PIN_IR, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  irsend.enableIROut(36);
  irsend.mark(0);
  delay(1000);  // wait for system to settle
}

void loop() {
  digitalWrite(LED_BUILTIN,digitalRead(PIN_DETECT));
  int pindetector = digitalRead(PIN_DETECT);
  Serial.println(pindetector);
}
