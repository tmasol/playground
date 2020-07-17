// from https://diygeeks.org/learn/microphone-with-arduino-uno/

int micPin=3;
int ledPin=13;


int num_Measure = 128 ; // Set the number of measurements   
int pinSignal = A0; // pin connected to pin O module sound sensor   
long Sound_signal;    // Store the value read Sound Sensor   
long sum = 0 ; // Store the total value of n measurements   
long level = 0 ; // Store the average value   
 

void setup() {
  Serial.begin (9600);

  pinMode(micPin, INPUT);
  pinMode(ledPin, OUTPUT);
}
  
void loop () {
  digitalWrite(ledPin,LOW);
  
   // Performs 128 signal readings   
  for ( int i = 0 ; i <num_Measure; i ++)  
  {  
   Sound_signal = analogRead(pinSignal);  
    sum =sum + Sound_signal;  
  }  
 
  level = sum / num_Measure; // Calculate the average value   

  if(level > 50) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin,LOW);
  }
  Serial.print("Sound Level: ");
  Serial.println (level);  
  sum = 0 ; // Reset the sum of the measurement values  
  delay(20);

}
