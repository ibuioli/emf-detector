import processing.serial.*;
Serial mySerial;
PrintWriter output;
float value;
int pValue;

int x;
int sensitivity = 300;

void settings() {
  size(600, 300);
  noSmooth();
}

void setup() {
  mySerial = new Serial( this, Serial.list()[0], 9600 );
  mySerial.bufferUntil('\n');
  output = createWriter("data/data.csv");

  x = width;
  background(200);
}

void draw() {
  line(x, height, x, height - value);

  if (x >= width) {
    background(200);
    x = 0;
  } else {
    x++;
  }
}

void serialEvent (Serial mySerial) {
  // get the ASCII string:
  String inString = mySerial.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // convert to an int and map to the screen height:
    value = float(inString);
    output.println(value);
    println(value);
    value = map(value, 0, sensitivity, 0, height);
  }
}

void keyPressed() {
  output.flush();  // Writes the data to the file
  output.close();  // Finishes the file
  exit();          // Stops the program
}
