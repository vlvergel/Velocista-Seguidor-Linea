#include <QTRSensors.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 11
#define LedPin 12

#define PWMA 19  // Pin PWM para motor A Derecha
#define AIN2 18  // Pin dirección A2
#define AIN1 17  // Pin dirección A1
#define BIN1 16  // Pin dirección B1
#define BIN2 15  // Pin dirección B2
#define PWMB 14  // Pin PWM para motor B Izquierda



//variavles de control y configuracion
int cruzero = 135 ; //velozidad incial
int PRO = 0 ;
int INT = 0 ;
int DER = 0 ;
int LAST = 0 ;
float VEL ;//velocidad

#define NUM_SENSORS 8
#define TIMEOUT 3500
#define EMITTER_PIN 2

QTRSensors qtr ;
uint8_t sensorPins[NUM_SENSORS] = {10, 9, 8, 7, 6, 5, 4, 3};
unsigned int  sensorValues[NUM_SENSORS];
unsigned int position = 0;

bool estado = false;

void setup() {
  Serial.begin(9600);

  //configuracion de pines -falta

  qtr.setTypeRC();
  qtr.setSensorPins(sensorPins, NUM_SENSORS);
  qtr.setTimeout(TIMEOUT);
  qtr.setEmitterPin(EMITTER_PIN);

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

  calibrar();

  // configuracion inicial de motores -falta

}

void loop() {
  Serial.println("fuera");
  if (IrReceiver.decode()) {
    if(IrReceiver.decodedIRData.decodedRawData == 0xF20DFF00){
      Serial.println("Código init");
      estado=true;
    }
    if(IrReceiver.decodedIRData.decodedRawData == 0xE31CFF00){
      Serial.println("Código calibrar");
      calibrar();
    }
    IrReceiver.resume(); 
  }

  while(estado){
    
    qtr.read (sensorValues);
    position = qtr.readLineBlack(sensorValues);
    PRO = ((position) - 3500);

    Serial.println(String(position) + " posicion " + String(PRO) + " PRO");

    if (PRO < - 2500){ //VALOR TEMPORAL
      Serial.println("izquierda");
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      analogWrite(PWMA, 200);

      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMB, 135);

    }else if(PRO > 2500){

      Serial.println("izquierda");
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      analogWrite(PWMA, 135);

      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMB, 200);

    }else{
      DER = (PRO - LAST);
      INT = (PRO + LAST);
      VEL = (PRO * 0.1) + (DER * 4.5) + (INT * 0.006);// VALORES A CALIBRAR
      Serial.println(VEL);
      if (VEL > cruzero) VEL = cruzero;
      if (VEL < -cruzero) VEL = -cruzero;

      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);

      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);

      Serial.print("motor 1 :");
      Serial.print(cruzero - VEL);
      Serial.print(" motor 2 :");
      Serial.println(cruzero + VEL);
      
      if ((cruzero - VEL)<135 && (cruzero - VEL) != 0){
        analogWrite(PWMA, 135);
      }else{
        analogWrite(PWMA, cruzero - VEL);
      }

      if ((cruzero + VEL)<135 && (cruzero + VEL) != 0){
        analogWrite(PWMB, 135);
      }else{
        analogWrite(PWMB, cruzero + VEL);
      }
      
      // Actualización de la última posición
      LAST = PRO;
    } 
    if(IrReceiver.decode()){
      if(IrReceiver.decodedIRData.decodedRawData == 0xE916FF00){
        Serial.println("Código paro");
        estado=false;
      }
      IrReceiver.resume(); 
    } 
  }
  analogWrite(PWMA, 0);  // Velocidad (0-255)
  analogWrite(PWMB, 0);
}

void calibrar(){
  Serial.println("calibrar");
  digitalWrite(LedPin, HIGH);
  for (int i = 0; i < 200; i++) {
    qtr.calibrate();
  }
  digitalWrite(LedPin, LOW);
}