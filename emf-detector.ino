#define sample 500

int inPinH = 0;
float valH;

int pin = 9;

void setup() {
  Serial.begin(9600);
}

void loop(){
  valH = average(inPinH, sample);

  valH = constrain(valH, 0, 100);
  valH = map(valH, 0, 100, 0, 255);
  //analogWrite(pin, valH);

  delay(1);
  Serial.println(valH);
}

float average(int inPin, int sam){
  int arr[sam];
  unsigned long average = 0;

  for(int i = 0; i < sam; i++){
     arr[i] = analogRead(inPin);
     average += arr[i];
  }

  return average / sam;
}
