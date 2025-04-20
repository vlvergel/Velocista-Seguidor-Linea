#define PinMotorA 16
#define PinMotorA2 17
#define PinMotorB 18
#define PinMotorB2 19

void setup() {
  // put your setup code here, to run once:
  pinMode(PinMotorA, OUTPUT);
  pinMode(PinMotorA2, OUTPUT);
  pinMode(PinMotorB, OUTPUT);
  pinMode(PinMotorB2, OUTPUT);

  digitalWrite(PinMotorA, HIGH);
  digitalWrite(PinMotorA2, LOW);
  digitalWrite(PinMotorB, HIGH);
  digitalWrite(PinMotorB2, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("PARTE 1");
  analogWrite(PinMotorA, 200); // Velocidad (0-255)
  digitalWrite(PinMotorA2, LOW);
  analogWrite(PinMotorB, 200); // Velocidad (0-255)
  digitalWrite(PinMotorB2, LOW);
  delay(2000); // Espera 2 segundos

  // Giro en sentido contrario
  Serial.println("PARTE 2");
  digitalWrite(PinMotorA, LOW);
  analogWrite(PinMotorA2, 200);
  digitalWrite(PinMotorB, LOW);
  analogWrite(PinMotorB2, 200);  // Velocidad (0-255)
  delay(2000); // Espera 2 segundos

  // Detener motor
  Serial.println("PARTE 3");
  digitalWrite(PinMotorA, LOW);
  digitalWrite(PinMotorA2, LOW);
  digitalWrite(PinMotorB, LOW);
  digitalWrite(PinMotorB2, LOW);
  delay(2000);
}
