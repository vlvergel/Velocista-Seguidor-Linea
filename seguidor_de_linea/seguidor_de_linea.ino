#include <QTRSensors.h>

#define BotonPin 18
#define LedPin 19
#define PinIn1 4
#define PinIn2 5c:\Users\danie\Documents\Velocista-Seguidor-Linea\cartest4\cartest4.ino
#define PinIn3 6
#define PinIn4 7

//variavles de control y configuracion
int cruzero = 45 ; //velozidad incial
int PRO = 0 ;
int INT = 0 ;
int DER = 0 ;
int LAST = 0 ;
float VEL ;//velocidad

#define NUM_SENSORS 8
#define TIMEOUT 3500
#define EMITTER_PIN 2

QTRSensors qtr ;
uint8_t sensorPins[NUM_SENSORS] = {3, 4, 5, 6, 7, 8, 9, 10};
unsigned int  sensorValues[NUM_SENSORS];
unsigned int position = 0;



void setup() {
  Serial.begin(9600);

  //configuracion de pines -falta
  pinMode(BotonPin, INPUT);

  qtr.setTypeRC();
  qtr.setSensorPins(sensorPins, NUM_SENSORS);
  qtr.setTimeout(TIMEOUT);
  qtr.setEmitterPin(EMITTER_PIN);

  calibrar();

  // configuracion inicial de motores -falta

}

void loop() {

  int estadoBoton = digitalRead(BotonPin);

  if (estadoBoton == LOW){
    calibrar();
  }

  qtr.read (sensorValues);
  position = qtr.readLineBlack(sensorValues);
  PRO = ((position) - 3500);c:\Users\danie\Documents\Velocista-Seguidor-Linea\seguidor_de_linea\seguidor_de_linea.ino

  Serial.println(String(position) + " posicion\n" + String(PRO) + " PRO");

  if (PRO < - 2800){ //VALOR TEMPORAL

  }else if(PRO > 2800){

  }else{
    DER = (PRO - LAST);
    INT = (PRO + LAST);
    VEL = (PRO * 0.55) + (DER * 4.2) + (INT * 0.006);// VALORES A CALIBRAR

    if (VEL > cruzero) VEL = cruzero;
    if (VEL < -cruzero) VEL = -cruzero;


    // Actualización de la última posición
        LAST = PRO;
  }

}

void calibrar(){
  digitalWrite(LedPin, HIGH);
  for (int i = 0; i < 200; i++) {
    qtr.calibrate();
  }
  digitalWrite(LedPin, LOW);
}
