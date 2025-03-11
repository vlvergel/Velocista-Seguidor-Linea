#include <QTRSensors.h>


// left motor
const int PinIN1 = 4;
const int PinIN2 = 5;

// right motor
const int PinIN3 = 6;
const int PinIN4 = 7;

// switch
const int PinSwitch = 2;

void setup() {
  Serial.begin(9600);
  
  pinMode(PinIN1, OUTPUT);
  pinMode(PinIN2, OUTPUT);
  pinMode(PinIN3, OUTPUT);
  pinMode(PinIN4, OUTPUT);
}

void carAction(bool left1, bool left2, bool right1, bool right2) {
  digitalWrite(PinIN1, left1);
  digitalWrite(PinIN2, left2);
  digitalWrite(PinIN3, right1);
  digitalWrite(PinIN4, right2);
}

void carForward() { carAction(HIGH, LOW, HIGH, LOW); }
void carReverse() { carAction(LOW, HIGH, LOW, HIGH); }
void carLeftTurn() { carAction(LOW, LOW, HIGH, LOW); }
void carRightTurn() { carAction(HIGH, LOW, LOW, LOW); }
void carStop() { carAction(LOW, LOW, LOW, LOW); }

void loop() {

}
