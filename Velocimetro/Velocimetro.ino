
void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
}

void loop() {
  int value = digitalRead(2); 

  Serial.println(value);
//  delay(10);

}

