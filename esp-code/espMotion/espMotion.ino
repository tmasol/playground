
#define PIR_PIN_SIG D7
#define LED_PIN D4

bool motionStatus = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN_SIG, INPUT);   // declare sensor as input
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite (LED_PIN, LOW);
}

void loop() {

  long pirStatus = digitalRead(PIR_PIN_SIG);
  if(pirStatus == HIGH) {
      digitalWrite (LED_BUILTIN, LOW);
      digitalWrite (LED_PIN, LOW);
      motionStatus = true;
  }
  else {
      digitalWrite (LED_BUILTIN, HIGH);
      digitalWrite (LED_PIN, HIGH);
      motionStatus = false;
  }
  
}
