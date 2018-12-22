#define sample 500

byte inPinH = 0;
float valH;

int dirty[10];
byte index = 0;
int maxVal = 0;

//byte pin = 9;

volatile boolean state = false;

void setup() {
  Serial.begin(9600);

  pinMode(2, INPUT);  //To Switch
  pinMode(3, INPUT_PULLUP); //To Button
}

void loop() {
  valH = average(inPinH, sample);

  //valH = constrain(valH, 0, 100);
  //valH = map(valH, 0, 100, 0, 255);
  //analogWrite(pin, valH);

  if (digitalRead(2) == 1) {  //Default Calibration
    if (millis() > 2000) {
      if (index < 10) {
        dirty[index] = valH;
        index++;
      } else {
        for (byte i = 1; i < 10; i++) {
          maxVal = max(dirty[i], maxVal);
        }
      }
    }
  }

  delay(1);

  if (digitalRead(2) == 1) {
    attachInterrupt(digitalPinToInterrupt(3), interrupt, FALLING);
    Serial.println(jail(valH, maxVal)); //Clear signal
  } else {
    Serial.println(valH); //Dirty signal
  }
}

float average(int inPin, int sam) {
  int arr[sam];
  unsigned long average = 0;

  for (int i = 0; i < sam; i++) {
    arr[i] = analogRead(inPin);
    average += arr[i];
  }

  return average / sam;
}

float jail(float avg, int dirty) {
  return max(0, avg - dirty);
}

void interrupt() {  //Re-calibrate
  index = 0;
  maxVal = 0;
}
