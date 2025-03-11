#define PinIN1 7  // Motor A
#define PinIN2 6  
#define PinIN3 5  // Motor B
#define PinIN4 10 

void setup() {
  Serial.begin(9600);

  pinMode(PinIN1, OUTPUT);
  pinMode(PinIN2, OUTPUT);
  pinMode(PinIN3, OUTPUT);
  pinMode(PinIN4, OUTPUT);
}

// Función para controlar el movimiento con velocidad
void carAction(int left1, int left2, int right1, int right2, int speed) {
  analogWrite(PinIN1, left1 * speed);
  analogWrite(PinIN2, left2 * speed);
  analogWrite(PinIN3, right1 * speed);
  analogWrite(PinIN4, right2 * speed);
}

void carForward(int speed) { carAction(1, 0, 1, 0, speed); }
void carReverse(int speed) { carAction(0, 1, 0, 1, speed); }
void carLeftTurn(int speed) { carAction(0, 0, 1, 0, speed); }
void carRightTurn(int speed) { carAction(1, 0, 0, 0, speed); }
void carStop() { carAction(0, 0, 0, 0, 0); }

void loop() {
  carForward(150);  // Avanzar con 150/255 de velocidad
  delay(3000);

    carForward(50);  // Avanzar con 150/255 de velocidad
  delay(3000);
  
  carStop();
  delay(1000);
  
  carReverse(200);  // Retroceder con 200/255 de velocidad
  delay(3000);
  
  carStop();
  delay(1000);
}
