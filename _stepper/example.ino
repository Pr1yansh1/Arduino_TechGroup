// Initialize pins
// Motors and others
const int limitL = A0, limitR = A3;
const int dirL = A1, pulseL = A2;  // Left motor
const int dirR = A4, pulseR = A5;  // Right motor
const int electromagnet = 5;

// create stepper objects
StepperTB myStepperL(dirL, pulseL);
StepperTB myStepperR(dirR, pulseR);

// setup function: runs once
// -----------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(colA, INPUT);
  pinMode(colB, INPUT);
  pinMode(colC, INPUT);
  pinMode(colD, INPUT);
  pinMode(colE, INPUT);
  pinMode(colF, INPUT);
  pinMode(colG, INPUT);
  pinMode(colH, INPUT);

  pinMode(enG_L, OUTPUT);
  pinMode(selC, OUTPUT);
  pinMode(selB, OUTPUT);
  pinMode(selA, OUTPUT);

  // Until button is pressed, don't enable the muxes
  digitalWrite(enG_L, HIGH);
  
  // initialize pins
  pinMode(electromagnet,OUTPUT);
  myStepperL.initPins();
  myStepperR.initPins();
  // Set speed
  myStepperL.setSpeed(120);  //rpm
  myStepperR.setSpeed(120);  //rpm
  turnOffElectromagnet();
  reset();
}

// This code runs in a continuous loop
void loop() {
  reset();
}

int *decode(String a) {
  static int curr_move[4];
  curr_move[0] = a[0] - 'a';
  curr_move[1] = a[1] - '1';
  curr_move[2] = a[2] - 'a';
  curr_move[3] = a[3] - '1';
  
  return curr_move;
}

// motor functions
// -------------------------------------------------------------------------------

// step functions to spin motor
void stepL(bool dir, int numStep) {
  myStepperL.setDirection(dir);
  myStepperL.step(numStep);
}

void stepR(bool dir, int numStep) {
  myStepperR.setDirection(dir);
  myStepperR.step(numStep);
}

// general move functions
void moveUp(int halfSquares) {
  for (int i = 0; i < 42 * halfSquares; i++) {
    stepL(ccw, 5);
    stepR(cw, 5);
  }
}

void moveDown(int halfSquares) {
  for (int i = 0; i < 42 * halfSquares; i++) {
    stepL(cw, 5);
    stepR(ccw, 5);
  }
}

void moveLeft(int halfSquares) {
  for (int i = 0; i < 42 * halfSquares; i++) {
    stepL(ccw, 5);
    stepR(ccw, 5);
  }
}

void moveRight(int halfSquares) {
  for (int i = 0; i < 42 * halfSquares; i++) {
    stepL(cw, 5);
    stepR(cw, 5);
  }
}

void moveLeftUp(int halfSquares) {
  for (int i = 0; i < 84 * halfSquares; i++) {
    stepL(ccw, 5);
  }
}

void moveRightDown(int halfSquares) {
  for (int i = 0; i < 84 * halfSquares; i++) {
    stepL(cw, 5);
  }
}

void moveLeftDown(int halfSquares) {
  for (int i = 0; i < 84 * halfSquares; i++) {
    stepR(ccw, 5);
  }
}

void moveRightUp(int halfSquares) {
  for (int i = 0; i < 84 * halfSquares; i++) {
    stepR(cw, 5);
  }
}

void reset() {
  moveRight(1);  // Move right half a square so not to break horizontal limit switch when moving down (ie. in A file)
  while (analogRead(limitR) > 100) {  // Move down
    stepL(cw, 5);
    stepR(ccw, 5);
  }
  while (analogRead(limitL) > 100) {  // Move left
    stepL(ccw, 5);
    stepR(ccw, 5);
  }
}

// master move function
void masterMove(int *curr_move) {
  // Extract moves from array into meaningful variable names
  int initC = curr_move[0];
  int initR = curr_move[1];
  int finalC = curr_move[2];
  int finalR = curr_move[3];
  int dCol = finalC - initC;
  int dRow = finalR - initR;

  // Move to initial square. Double initC and initR since functions move halfSquares
  Serial.println("Moving to initial square");
  moveRight(2 * initC);
  moveUp(2 * initR);
  turnOnElectromagnet();
  
  Serial.println("Moving piece with electromagnet");
  if (dRow == 0) {  // This is horizontal move
    if (dCol > 0) {
      moveRight(2 * dCol);
    }
    else {
      moveLeft(2 * abs(dCol));
    }
  }

  else if (dCol == 0) {  // This is vertical move
    if (dRow > 0) {
      moveUp(2 * dRow);
    }
    else {
      moveDown(2 * abs(dRow));
    }
  }

  else if (abs(dRow) == abs(dCol)) {  // This is a diagonal move
    if (dRow > 0 && dCol > 0) {
      moveRightUp(2 * dRow);
    }
    else if (dRow > 0 && dCol < 0) {
      moveLeftUp(2 * dRow);
    }
    else if (dRow < 0 && dCol > 0) {
      moveRightDown(2 * abs(dRow));
    }
    else if (dRow < 0 && dCol < 0) {
      moveLeftDown(2 * abs(dRow));
    }
  }

  else {  // This is a knight move
    if (dRow == 1 && dCol == 2) {  // Up 1, Right 2
      moveUp(1);
      moveRight(4);
      moveUp(1);
    }
    else if (dRow == 1 && dCol == -2) {  // Up 1, Left 2
      moveUp(1);
      moveLeft(4);
      moveUp(1);
    }
    else if (dRow == -1 && dCol == -2) {  // Down 1, Left 2
      moveDown(1);
      moveLeft(4);
      moveDown(1);
    }
    else if (dRow == -1 && dCol == -2) {  // Down 1, Right 2
      moveDown(1);
      moveRight(4);
      moveDown(1);
    }

    else if (dRow == 2 && dCol == 1) {  // Up 2, Right 1
      moveRight(1);
      moveUp(4);
      moveRight(1);
    }
    else if (dRow == 2 && dCol == -1) {  // Up 2, Left 1
      moveLeft(1);
      moveUp(4);
      moveLeft(1);
    }
    else if (dRow == -2 && dCol == 1) {  // Down 2, Right 1
      moveRight(1);
      moveDown(4);
      moveRight(1);
    }
    else if (dRow == -2 && dCol == -1) {  // Down 2, Left 1
      moveLeft(1);
      moveDown(4);
      moveLeft(1);
    }
  }

  Serial.println("Finished moving");

  turnOffElectromagnet();
}

// other functions
// -------------------------------------------------------------------------------
void turnOnElectromagnet() {
  digitalWrite(electromagnet,LOW);
}

void turnOffElectromagnet() {
  digitalWrite(electromagnet,HIGH);
}
