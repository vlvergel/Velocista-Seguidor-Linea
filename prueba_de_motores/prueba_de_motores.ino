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

  digitalWrite(PinMotorA, LOW);
  digitalWrite(PinMotorA2, HIGH);
  digitalWrite(PinMotorB, HIGH);
  digitalWrite(PinMotorB2, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("PARTE 1");
  analogWrite(PinMotorA, 200); // Velocidad (0-255)
  digitalWrite(PinMotorA2, LOW);
  analogWrite(PinMotorB, LOW); // Velocidad (0-255)
  digitalWrite(0, 200);
  delay(2000); // Espera 2 segundos

  
}
