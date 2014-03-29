void setup() {
  // put your setup code here, to run once:
 Serial1.begin(115200);
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  
  while(!Serial);
  while(Serial1.available())
    Serial.write(Serial1.read());
}
