#define sample 500

byte inPinH = 0;
float valH;

int dirty[10];
byte index = 0;
int maxVal = 0;

byte s01 = 2;
byte s02 = 3;
byte pin = 9;

void setup() {
  Serial.begin(9600);

  pinMode(s01, INPUT);  //To Switch
  pinMode(s02, INPUT_PULLUP); //To Button
  pinMode(pin, OUTPUT); //To LED
}

void loop() {
  valH = average(inPinH, sample);

  if (digitalRead(s01) == 1) {
    analogWrite(pin, map(constrain(jail(valH, maxVal), 0, 100), 0, 100, 0, 255));
  } else {
    analogWrite(pin, map(constrain(valH, 0, 500), 0, 500, 0, 255));
  }

  if (digitalRead(s01) == 1) {  //Default Calibration
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

  if (digitalRead(s01) == 1) {
    attachInterrupt(digitalPinToInterrupt(s02), interrupt, FALLING);
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
