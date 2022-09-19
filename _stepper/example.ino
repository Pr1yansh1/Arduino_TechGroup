
// create stepper object 
StepperTB myStepper(en, dir, pulse);

// initialize pins
const int motorButton = A0;
const int pumpButton = A1;
const int pump = 13;

// setup function: runs once
// -----------------------------------------------------------------------------
void setup(){
	// initialize pins
	myStepper.initPins();
  pinMode(pump, OUTPUT);
  digitalWrite(pump, HIGH);  // Water off to begin
  pinMode(motorButton, INPUT);
  pinMode(pumpButton, INPUT);
}


// loop function: repeats indefinitely
// -------------------------------------------------------------------------------
void loop(){
  water();
  travel();
}

void travel() {
  if (analogRead(motorButton) < 256) test_step(cw);  // Move right
  if (analogRead(motorButton) >= 768) test_step(ccw);  // Move left
}

void water() {
  if (analogRead(pumpButton) == 0) {
    // Water for 400 ms
    digitalWrite(pump, LOW);
    delay(800);
    digitalWrite(pump, HIGH);
  }
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
