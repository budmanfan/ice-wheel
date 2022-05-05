#include <Bounce.h>

// define Pins
int pin_aout_speed = 0;
int pin_ain_poti = 14;
int pin_din_hall0 = 33;
int pin_dout_mosfet0 = 13;
int pin_dout_mosfet1 = 15;
int pin_dout_mosfet2 = 16;

// debounce Inputs
Bounce in_hall0 = Bounce(pin_din_hall0, 2);

// define Variables
unsigned int val_poti = 0;
int val_speed_8uint = 0;
float val_speed_Hz = 0;
unsigned long val_start_rising_hall0 = 0;
unsigned long val_hightime_hall0 = 0;
unsigned int timeout_speed_measurement = 200;

// special Variables
//elapsedMicros since_risingEdge_hall0;
elapsedMillis since_last_hall_change;

// Test Variables
elapsedMillis sinceStart;
elapsedMicros timestamp;
bool timestamp_reset = false;

int test_int = 0;


void setup() {
  Serial.begin(115200);

  pinMode(pin_aout_speed, OUTPUT);
  
  pinMode(pin_dout_mosfet0, OUTPUT);
  pinMode(pin_dout_mosfet1, OUTPUT);
  pinMode(pin_dout_mosfet2, OUTPUT);
}

void loop() {

  unsigned long currentMicros = micros();

  // Measure High Time Hall0
  in_hall0.update();
  if(in_hall0.risingEdge()) {
    val_start_rising_hall0 = currentMicros;
    //since_risingEdge_hall0 = 0;
    since_last_hall_change = 0;
  }
  if(in_hall0.fallingEdge()) {
    val_hightime_hall0 = currentMicros - val_start_rising_hall0;
    //val_hightime_hall0 = since_risingEdge_hall0;
    since_last_hall_change = 0;
  }
  
  // Calculate Rotations per Second (rps)
  val_speed_Hz = 500000.0 / val_hightime_hall0;
  if(since_last_hall_change > timeout_speed_measurement) {
    val_speed_Hz = 0.0;
  }

  // Write Poti Value to Speed Output
  val_poti = analogRead(pin_ain_poti);
  //val_speed_8uint = val_poti / 4;  
  //analogWrite(pin_aout_speed, 100);

  if(sinceStart > 3000){    
    test_int = 0;
  }
  if(sinceStart < 1000){
    test_int = 100;
  }

  if(sinceStart > 2000 && !timestamp_reset){
    timestamp = 0;
    timestamp_reset = true;
  }
  if(sinceStart > 2000 && sinceStart < 6000){
    Serial.print(timestamp);
    Serial.print(",");
    Serial.print(test_int);
    Serial.print(",");
    Serial.println(val_speed_Hz);
  }  

  analogWrite(pin_aout_speed, test_int);
  //Serial.println(val_speed_Hz);
}
