void setup() {
  pinMode(7,INPUT);
      Serial.begin(9600);
}

void loop(){

    int sensor = 0;
    int state = 0;

  sensor = digitalRead(7);
  if (sensor == 1 && state == 0){
    Serial.println("On1");
    state = 1;
    delay(50);
  }
  else if (sensor ==1 && state == 1){

  }
  else{
    Serial.println("OFF");
    delay(50);
  }
}
