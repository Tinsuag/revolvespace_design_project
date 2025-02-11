#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

int analogInputPin = A0;       // select the analog input pin for the potentiometer
int potValue = 0;              // variable to store the potentiometer value
int lastPotValue = -1;         // variable to store the previous potentiometer value

const int buttonForward = 2;   // button for forward direction control
const int buttonReverse = 3;  // button for backward direction control

bool isForward = true;         // variable to track the motor direction
bool lastDirection = true;     // variable to store the previous motor direction

void setup() {
  // initialize the serial port:
  Serial.begin(9600);

  // set up buttons as inputs with internal pull-up resistors:
  pinMode(buttonForward, INPUT_PULLUP);
  pinMode(buttonReverse, INPUT_PULLUP);
}

void loop() {
  // read the analog value from the potentiometer:
  potValue = analogRead(analogInputPin);

  // map the potentiometer value to the desired speed range:
  int motorSpeed = map(potValue, 0, 1023, -500, 500);

  // set the speed of the stepper motor:
  myStepper.setSpeed(abs(motorSpeed));

  // check the direction buttons:
  bool currentDirectionForward = digitalRead(buttonForward) == LOW;
  bool currentDirectionReverse = digitalRead(buttonReverse) == LOW;

  // determine the direction based on the button state:
  if (currentDirectionForward && !currentDirectionReverse) {
    isForward = true;
  } else if (!currentDirectionForward && currentDirectionReverse) {
    isForward = false;
  }

  // move the stepper motor in the selected direction:
  if (isForward) {
    myStepper.step(1);  // move forward
  } else {
    myStepper.step(-1);  // move backward
  }

  // check if the potentiometer value has changed:
  if (potValue != lastPotValue) {
    // Print the potentiometer value and stepper motor speed when the value changes:
    Serial.print("Potentiometer Value: ");
    Serial.println(potValue);
    Serial.print("Stepper Motor Speed: ");
    Serial.println(abs(motorSpeed));

    // Update the last potentiometer value:
    lastPotValue = potValue;
  }

  // check if the motor direction has changed:
  if (isForward != lastDirection) {
    // Print the motor direction status when it changes:
    Serial.print("Direction: ");
    Serial.println(isForward ? "Forward" : "Reverse");

    // Update the last direction value:
    lastDirection = isForward;
  }

  delay(50);  // adjust delay as needed for smoother operation
}