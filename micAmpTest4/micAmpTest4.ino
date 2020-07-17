#define MicSamples 50
#define MicPin A0
 
void setup() {
   Serial.begin(9600);
}

void loop() {
   long signalAvg = 0, signalMax = 0, signalMin = 1024, t0 = millis();
    for (int i = 0; i < MicSamples; i++)
    {
        int k = analogRead(MicPin);
        signalMin = min(signalMin, k);
        signalMax = max(signalMax, k);
        signalAvg += k;
    }
    signalAvg /= MicSamples;
 
    //Serial.print(" Min: " + String(signalMin));
    //Serial.println(" Max: " + String(signalMax));
    //Serial.print(" Avg: " + String(signalAvg));
    //Serial.println("");

    int millivolts = int(1000 * (3.3 * signalMax) / 1024);
    Serial.println(signalMax);
}
