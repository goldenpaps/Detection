void setup() {
  pinMode(7,INPUT);
  Serial.begin(9600);
}

void loop(){
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
