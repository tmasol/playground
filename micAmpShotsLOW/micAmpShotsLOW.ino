
int shotCounterTime[10];

int g_current_shot = 0;
int g_sensitivity = 1;
byte g_sample_window = 50;
int g_threshold = 680;

const int kMicPin = A0; //set the input for the mic/amplifier 

int SampleSound() {
  uint32_t start_millis = millis();  // Start of sample window 
  // the peak to peak reading will be the total loudness change across the 
  // sample wiindow!
  int peak_to_peak = 0; // peak_to_peak level
  int sample = 0;
  int signal_max = 0;
  int signal_min = 1024;

  // collect data for duration of g_sample_window
  while (millis() - start_millis < g_sample_window) {
    sample = analogRead(kMicPin);
    if (sample < 1024) {
       // toss out spurious readings 
      if (sample > signal_max) {
        signal_max = sample; // save just the max levels
      }
      else if (sample < signal_min) {
        signal_min = sample; // save just the min levels
      }
    }
  }
  peak_to_peak = signal_max - signal_min; // max - min = peak-peak amplitude
  return (peak_to_peak);
}


void setup() {
   Serial.begin(9600);
   delay(125);
   SensToThreshold();
}


void loop() {
   ShotListener();
}

void SensToThreshold() {
  g_threshold = g_threshold + g_sensitivity;

  Serial.print(SampleSound());
  Serial.print(" - ");
  Serial.print(g_threshold);
  Serial.println();
}

void ShotListener() {
  if (SampleSound() >= g_threshold) {
    RecordShot();
  }
}

void RecordShot() {
  //shotCounterTime[g_current_shot] = "shot";
  Serial.println("shot");
  g_current_shot++;
  delay(25);
}
