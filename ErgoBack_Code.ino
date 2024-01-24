#include <Servo.h>

// Constants won't change
const int BUTTON_PIN = 7;
const int SERVO_PIN = A0;

const int BUTTON1_PIN = 6;
const int SERVO1_PIN = A1;

const int BUTTON2_PIN = 5;
const int SERVO2_PIN = A2;
const int SERVO3_PIN = A3;

Servo servo;
Servo servo1;
Servo servo2;
Servo servo3;

int angle = 0;

int lastButtonState;
int currentButtonState;

int lastButtonState1;
int currentButtonState1;

int lastButtonState2;
int currentButtonState2;

int defaultSpeed = 1;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  servo.attach(SERVO_PIN);
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);

  servo.write(angle);
  servo1.write(angle);
  servo2.write(angle);
  servo3.write(angle);

  currentButtonState = digitalRead(BUTTON_PIN);
  currentButtonState1 = digitalRead(BUTTON1_PIN);
  currentButtonState2 = digitalRead(BUTTON2_PIN);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    processCommand(command);
  }

  lastButtonState = currentButtonState;
  currentButtonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("Button 0 is pressed");
    moveServo(servo);
  }

  lastButtonState1 = currentButtonState1;
  currentButtonState1 = digitalRead(BUTTON1_PIN);

  if (lastButtonState1 == HIGH && currentButtonState1 == LOW) {
    Serial.println("Button 1 is pressed");
    moveServo(servo1);
  }

  lastButtonState2 = currentButtonState2;
  currentButtonState2 = digitalRead(BUTTON2_PIN);

  if (lastButtonState2 == HIGH && currentButtonState2 == LOW) {
    Serial.println("Button 2 is pressed");
    moveServo(servo2);
    moveServo(servo3);
  }
}

void moveServo(Servo &servoToMove) {
  int increment;

  switch (defaultSpeed) {
    case 1:
      increment = 1;
      break;
    case 2:
      increment = 3;
      break;
    case 3:
      increment = 5;
      break;
    default:
      increment = 1;
      break;
  }

  for (int i = 0; i <= 180; i += increment) {
    servoToMove.write(i);
    delay(15);
  }

  servoToMove.write(90);
}

void processCommand(char command) {
  switch (command) {
    case '1':
      defaultSpeed = 1;
      break;
    case '2':
      defaultSpeed = 2;
      break;
    case '3':
      defaultSpeed = 3;
      break;
    default:
      break;
  }
  Serial.print("Default Speed: ");
  Serial.println(defaultSpeed);
}
