const int mvMax = 100;
const int sampleWindow = 50;
unsigned int sample;
const int kMicPin = A0;

const int g_threshold = 1500;
int g_current_shot = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    ShotListener();

    Serial.println(SampleSound());
}

int SampleSound() {
    unsigned long startMillis= millis(); 
    unsigned int peakToPeak = 0; 
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;
    while (millis() - startMillis < sampleWindow) {
        sample = analogRead(kMicPin);
        if (sample < 1024) {
            if (sample > signalMax) {
                signalMax = sample; 
            }
            else if (sample < signalMin) {
                signalMin = sample; 
            }
        }
    }
    peakToPeak = signalMax - signalMin;
    int millivolts = int(1000 * (3.3 * peakToPeak) / 1024);
    return (millivolts);
}


void ShotListener() {
  if (SampleSound() >= g_threshold) {
    RecordShot();
  }
}

void RecordShot() {
  //shotCounterTime[g_current_shot] = "shot";
  g_current_shot++;
  Serial.println("shot no."+String(g_current_shot));
  delay(sampleWindow);
}
