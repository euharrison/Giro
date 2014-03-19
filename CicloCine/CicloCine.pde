

import processing.serial.*;


int imgCount = 33;
PImage[] imgs = new PImage[imgCount];

int current = 0;
char lastValue = '0';

Serial arduino;


void setup() {
  size(1024, 768);
  background(0);
  
  for (int i = 0; i < imgCount; i++){
    imgs[i] = requestImage("02_bison/"+(i+1)+".png");
  }
  
  //*
  // Print a list of the serial ports, for debugging purposes:
  println(Serial.list());
  String portName = Serial.list()[0];
  arduino = new Serial(this, portName, 9600);
  //*/
}
 
void draw() {
  float scale = width/1920.f;
  if (imgs[current].width > 0) {
    image(imgs[current], 0, (height-(1080*scale))/2.f, 1920*scale, 1080*scale);
  }
}

void keyPressed() {
  if (key == 'z') {
    nextFrame();
  }
}

//*
void serialEvent(Serial arduino) {
  while (arduino.available() > 0) {
    int inByte = arduino.read();
    if (inByte != 10 && inByte != 13) 
    {
      if (inByte == '1' && lastValue == '0') {
        nextFrame();
      }
      lastValue = char(inByte);
      println(char(inByte));
    }
  }
} 
//*/

void nextFrame() {
  current++;
  if (current >= imgCount) {
    current = 0;
  }
}
