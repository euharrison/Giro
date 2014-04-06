import processing.serial.*;


Sequence[] sequences;
int current = -1;

Serial arduino;
char arduinoValue = '0';


void setup() {
  size(1024, 768);
  background(0);
  frameRate(30);
  
  sequences = new Sequence[3];
  sequences[0] = new Sequence("bison", 32);
  sequences[1] = new Sequence("cachorro", 12);
  sequences[2] = new Sequence("macaco", 19);
  
  changeSequence(0);
  
  //arduino
  println(Serial.list());
  String portName = Serial.list()[0];
  arduino = new Serial(this, portName, 9600);
}
 
void draw() {
  sequences[current].draw();
}

void keyPressed() {
  if (key == ' ') {
    sequences[current].update();
  }
  if (key == 'z') {
    changeSequenceRandom();
  }
}

void serialEvent(Serial arduino) {
  while (arduino.available() > 0) {
    int inByte = arduino.read();
    if (inByte != 10 && inByte != 13) 
    {
      if (arduinoValue == '0' && inByte == '1') {
        sequences[current].update();
      }
      arduinoValue = char(inByte);
      println(char(inByte));
    }
  }
} 

void changeSequenceRandom() {
  if (sequences.length > 1) {
    int newIndex;
    do {
      newIndex = int(random(sequences.length));
    } while(newIndex == current);
   changeSequence(newIndex); 
  }    
}

void changeSequence(int newIndex) {
  if (newIndex == current) return; 
  if (current > -1) {
    sequences[current].unload();
  }
  current = newIndex;
  sequences[current].load();
}


//================================================

class Sequence { 
  
  String[] paths;
  ArrayList<PImage> images;
  
  int current = 0;
  
  Sequence (String folder, int totalFrames) { 
    paths = new String[totalFrames];
    for (int i = 0; i < paths.length; i++){
      paths[i] = folder+"/"+(i+1)+".jpg";
    }
    images = new ArrayList<PImage>();
  }
  
  void load() {
    for (int i = 0; i < paths.length; i++){
      images.add(requestImage(paths[i]));
    }
    current = 0;
  }
  
  void unload() {
    while (images.size() > 0){
      g.removeCache(images.get(0));  
      images.remove(0);
    }
    System.gc();
  }
  
  void update() { 
    current++;
    if (current >= paths.length) {
      current = 0;
    }
  }
  
  void draw() { 
    PImage image = images.get(current);
    if (image != null && image.width > 0) {
      float scale = (float)width/image.width;
      image(image, 0, (height-(image.height*scale))/2.f, image.width*scale, image.height*scale);
    }
    image = null;
  } 
  
} 
