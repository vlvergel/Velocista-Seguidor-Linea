#include <QTRSensors.h>

#define PinIn1 4
#define PinIn2 5
#define PinIn3 6
#define PinIn4 7

//variavles de control y configuracion
int cruzero = 45 //velozidad incial
int PRO = 0
int INT = 0
int DER = 0
int LAST = 0 
float VEL  //velocidad

#define NUM_SENSORS 8
#define TIMEOUT 3500
#define EMITTER_PIN 2

QTRSensors qtr
uint8_t sensorPins[sensorCount] = {A0, A1, A2, A3, A4, A5, A6, A7};
unsigned int  sensorValues[sensorCount];
unsigned int position = 0;



void setup() {
  Serial.begin(9600);

  //configuracion de pines -falta

  qtr.setTypeAnalog();
  qtr.setSensorPins(sensorPins, NUM_SENSORS);
  qtr.setTimeout(TIMEOUT);
  qtr.setEmitterPin(EMITTER_PIN);

  digitalWrite(2, HIGH);
  for (int i = 0; i < 200; i++) {
    qtr.calibrate();
  }
  digitalWrite(2, LOW);

  // configuracion inicial de motores -falta

}

void loop() {
  qtr.read (sensorValues);

  position = qtr.readLineBlack(sensorValues)
  PRO = ((position) - 3500);

  if (PRO < - 2800){ //VALOR TEMPORAL

  }else if(PRO > 2800){

  }else{
    DER = (PRO - LAST);
    INT = (PRO + LAST);
    vel = (PRO * 0.55) + (DER * 4.2) + (INT * 0.006);// VALORES A CALIBRAR

    if (vel > cruzero) vel = cruzero;
    if (vel < -cruzero) vel = -cruzero;


    // Actualización de la última posición
        LAST = PRO;
  }

}
