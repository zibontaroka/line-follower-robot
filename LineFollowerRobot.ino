// === Motor Control Pins (L298N) ===
const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;
const int IN3 = 7;
const int IN4 = 6;
const int ENB = 5;

// === IR Sensor Pins ===
const int LEFT      = A4;
const int CEN_LEFT  = A3;
const int CENTER    = A2;
const int CEN_RIGHT = A1;
const int RIGHT     = A0;

// === Speed Control ===
int baseSpeed = 140;   // Normal moving speed
int turnSpeed = 60;    // Speed during slight turns

void setup() {
  // Motor pins as output
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Sensor pins as input
  pinMode(LEFT, INPUT);
  pinMode(CEN_LEFT, INPUT);
  pinMode(CENTER, INPUT);
  pinMode(CEN_RIGHT, INPUT);
  pinMode(RIGHT, INPUT);

  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // === Read IR Sensor Values ===
  int left      = digitalRead(LEFT);
  int cenLeft   = digitalRead(CEN_LEFT);
  int center    = digitalRead(CENTER);
  int cenRight  = digitalRead(CEN_RIGHT);
  int right     = digitalRead(RIGHT);

  // === Decision Making ===

  // Moving straight
  if ((left == 0 && cenLeft == 0 && center == 1 && cenRight == 0 && right == 0) ||
      (left == 0 && cenLeft == 1 && center == 1 && cenRight == 1 && right == 0) ||
      (left == 1 && cenLeft == 1 && center == 1 && cenRight == 1 && right == 0) ||
      (left == 0 && cenLeft == 1 && center == 1 && cenRight == 1 && right == 1)) {
    moveForward();
  }
  
  // Slight Right Adjustments
  else if ((cenLeft == 0 && center == 0 && cenRight == 1) ||
           (cenLeft == 0 && center == 1 && cenRight == 1)) {
    slightRight();
  }
  
  // Slight Left Adjustments
  else if ((cenLeft == 1 && center == 1 && cenRight == 0) ||
           (cenLeft == 1 && center == 0 && cenRight == 0)) {
    slightLeft();
  }
  
  // Sharp Left Turn
  else if ((left == 1 && right == 0) ||
           (left == 1 && cenLeft == 1 && cenRight == 0 && right == 0)) {
    turnLeft();
  }

  // Sharp Right Turn
  else if ((left == 0 && right == 1) ||
           (left == 0 && cenLeft == 0 && cenRight == 1 && right == 1)) {
    turnRight();
  }

  // Default action: Stop if no valid path
  else {
    stopMotors();
  }
}

// === Movement Functions ===

// Move forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
}

// Move backward (not used but available)
void moveReverse() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
}

// Slight left movement (adjust left side slower)
void slightLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, turnSpeed);   // Left motor slower
  analogWrite(ENB, baseSpeed);   // Right motor normal
}

// Slight right movement (adjust right side slower)
void slightRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, baseSpeed);   // Left motor normal
  analogWrite(ENB, turnSpeed);   // Right motor slower
}

// Turn right in place until center sensor detects the line
void turnRight() {
  stopMotors();
  delay(100); // Small pause before turning
  
  while (digitalRead(CENTER) == 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, baseSpeed);
    analogWrite(ENB, baseSpeed);
  }

  stopMotors();
  delay(50);
}

// Turn left in place until center sensor detects the line
void turnLeft() {
  stopMotors();
  delay(100); // Small pause before turning

  while (digitalRead(CENTER) == 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, baseSpeed);
    analogWrite(ENB, baseSpeed);
  }

  stopMotors();
  delay(50);
}

// Stop all motors
void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
