int aoutPin = 33;
int i = 0;
int speed_step = 5;
int pause = 500;
bool dir = true;

void setup() {
  pinMode(aoutPin, OUTPUT);

}

void loop() {

  analogWrite(aoutPin, 0);
  /*
  if(dir){
    i = i + speed_step;
  } else {
    i = i - speed_step;
  }
    
  if(i < 50){
    dir = true;
  }

  if(i > 200){
    dir = false;
  }
  
  analogWrite(aoutPin, i);
  delay(pause);
  */
}
