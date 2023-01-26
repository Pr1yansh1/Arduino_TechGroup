
// create stepper object 
StepperTB myStepper(en, dir, pulse);

// Initialize pins
// Motors and others
const int pump = 13;

// Raspberry Pi interface
const int waterSignal = 2;
const int leftSignal = 3;
const int rightSignal = 4;
const int readySignal = 5;

// setup function: runs once
// -----------------------------------------------------------------------------
void setup(){
	// initialize pins
	myStepper.initPins();
  pinMode(pump, OUTPUT);
  digitalWrite(pump, HIGH);  // Water off to begin

  pinMode(waterSignal, INPUT);
  pinMode(leftSignal, INPUT);
  pinMode(rightSignal, INPUT);
  pinMode(readySignal, OUTPUT);
  
  digitalWrite(readySignal, HIGH);  // Ready to read Raspberry command
  test_step(ccw);
}


// loop function: repeats indefinitely
// -------------------------------------------------------------------------------
void loop(){
  if (digitalRead(waterSignal) == HIGH) {
    digitalWrite(readySignal, LOW);
    water();
  }
  else if (digitalRead(leftSignal)) {
    digitalWrite(readySignal, LOW);
    test_step(ccw);
  }
  else if (digitalRead(rightSignal)) {
    digitalWrite(readySignal, LOW);
    test_step(cw);
  }
  digitalWrite(readySignal, HIGH);
}

void water() {
    // Water for 800 ms
  digitalWrite(pump, LOW);
  delay(800);
  digitalWrite(pump, HIGH);
  return; 
}

//////// Motor testing functions
void test_step(int dir){
  
  // Set speed
  myStepper.setSpeed(120);  //rpm
  
  // set direction
  myStepper.setDirection(dir);

  // 4 full revolution 
  int numStep = 800;

  // step function to spin motor 
  myStepper.step(numStep);
  delay(1000);  // in mS 
}


void test_rotate(){
  // Set speed
  myStepper.setSpeed(120);  //rpm
  
  // set direction
  myStepper.setDirection(ccw);
  
  myStepper.rotate(90);
  delay(1000); 
}
