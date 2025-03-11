#include <QTRSensors.h>
#define PinIN1 4
#define PinIN2 5
#define PinIN3 6
#define PinIN4 7
QTRSensors qtr;
constexpr uint8_t sensorCount = 8;
    constexpr uint16_t FORWARD_THRESHOLD_LOW = 3000;
    constexpr uint16_t FORWARD_THRESHOLD_HIGH = 4999;
    constexpr uint16_t RIGHT_TURN_THRESHOLD = 2000;
    constexpr uint16_t LEFT_TURN_THRESHOLD = 5000;
uint16_t sensorValues[sensorCount];
constexpr uint8_t sensorPins[sensorCount] = {A0, A1, A2, A3, A4, A5, A6, A7};
void setup() {
Serial.begin(9600);

    DDRD |= (1 << PinIN1) | (1 << PinIN2) | (1 << PinIN3) | (1 << PinIN4);
    qtr.setTypeRC();
    qtr.setSensorPins(sensorPins, sensorCount);
    qtr.setEmitterPin(2);
    delay(500);

    Serial.println("Calibrando sensores...");
    for (uint8_t i = 0; i < 100; i++) {
        qtr.calibrate();
    }
    Serial.println("Calibración completa.");
}
void carAction(uint8_t left1, uint8_t left2, uint8_t right1, uint8_t right2) {
    PORTD = (PORTD & 0x0F) | (left1 << PinIN1) | (left2 << PinIN2) | (right1 << PinIN3) | (right2 << PinIN4);
}
void carForward() { carAction(1, 0, 1, 0); }
void carReverse() { carAction(0, 1, 0, 1); }
void carLeftTurn() { carAction(0, 0, 1, 0); }
void carRightTurn() { carAction(1, 0, 0, 0); }
void carStop() { carAction(0, 0, 0, 0); }
void loop() {
    uint16_t position = qtr.readLineBlack(sensorValues);

    Serial.print("Sensor Values: ");
    for (uint8_t i = 0; i < sensorCount; i++) {
        Serial.print(sensorValues[i]);
        Serial.print(" ");
    }
    Serial.print(" | Position: ");
    Serial.println(position);

    if (position >= FORWARD_THRESHOLD_LOW && position <= FORWARD_THRESHOLD_HIGH) { 
        carForward();
    } else if (position < RIGHT_TURN_THRESHOLD && position > 0) {  
        carRightTurn();
    } else if (position >= LEFT_TURN_THRESHOLD) {  
        carLeftTurn();
    } else if (position == 0) {
        carStop();
    }
}