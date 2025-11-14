void setup() {
  pinMode(7,INPUT);
}

void loop(){
    Serial.begin(9600);
    int sensor = 1;
    int state = 0;

  sensor = digitalRead(7);
  if (sensor == HIGH) {
    if (state == 0){ //just turned on
      Serial.println("On1");
   
    state = 1;
    }
      else{} //been on
  } 
  else {
    if (state == 1){ //just turned off
    Serial.println("Off1");
    state = 0;
    }
    else{}//been off
  } 
}
