#include <IRremote.hpp>

#define PWMA 19  // Pin PWM para motor A Derecha
#define AIN2 18  // Pin dirección A2
#define AIN1 17  // Pin dirección A1
#define BIN1 16  // Pin dirección B1
#define BIN2 15  // Pin dirección B2
#define PWMB 14  // Pin PWM para motor B Izquierda
#define IR_RECEIVE_PIN 11

bool estado = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.begin(9600);
}

void loop() {
  if(IrReceiver.decode()){
    
    Serial.println("entrar");
    
    if(IrReceiver.decodedIRData.decodedRawData == 0xF20DFF00){
      Serial.println("Código init");
      estado=true;
    }
    IrReceiver.resume(); 
  }
  while(estado){
    Serial.println("motor");
    analogWrite(PWMA, 200);  // Velocidad (0-255)
    analogWrite(PWMB, 200);

   if(IrReceiver.decode()){
      Serial.println("salir");
    
      if(IrReceiver.decodedIRData.decodedRawData == 0xE916FF00){
        Serial.println("Código paro");
        estado=false;
      }
      IrReceiver.resume(); 
    } 
  }
  
  Serial.println("parar");
  analogWrite(PWMA, 0);  // Velocidad (0-255)
  analogWrite(PWMB, 0);
    
  
}

