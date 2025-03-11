    #include <QTRSensors.h>
    #define PinIN1 4
    #define PinIN2 5
    #define PinIN3 6
    #define PinIN4 7
    #define lowSpeed 100
    #define highSpeed 200
    #define PinCalibrate 3
    
    QTRSensors qtr;
    constexpr uint8_t sensorCount = 8;
    uint16_t sensorValues[sensorCount];
    constexpr uint16_t FORWARD_THRESHOLD_LOW = 3000;
    constexpr uint16_t FORWARD_THRESHOLD_HIGH = 4999;
    constexpr uint16_t RIGHT_TURN_THRESHOLD = 2000;
    constexpr uint16_t LEFT_TURN_THRESHOLD = 5000;
    constexpr uint8_t sensorPins[sensorCount] = {A0, A1, A2, A3, A4, A5, A6, A7};

    void setup() {

    Serial.begin(9600);

        pinMode(PinCalibrate, INPUT_PULLUP);

        DDRD |= (1 << PinIN1) | (1 << PinIN2) | (1 << PinIN3) | (1 << PinIN4);
        qtr.setTypeRC();
        qtr.setSensorPins(sensorPins, sensorCount);
        qtr.setEmitterPin(2);
        delay(500);

        while (digitalRead(PinCalibrate) == HIGH);
        calibrate();
    }

    void calibrate(){

        for (uint8_t i = 0; i < 100; i++) {
            qtr.calibrate();
            delay(20);
        }

    }

    void carAction(uint8_t left1, uint8_t left2, uint8_t right1, uint8_t right2, uint8_t speedL, uint8_t speedR) {

    if (speedL > 0) {
        analogWrite(PinIN1, left1 ? speedL : 0);
        analogWrite(PinIN2, left2 ? speedL : 0);
    } else {
        analogWrite(PinIN1, 0);
        analogWrite(PinIN2, 0);
    }
    
    if (speedR > 0) {
        analogWrite(PinIN3, right1 ? speedR : 0);
        analogWrite(PinIN4, right2 ? speedR : 0);
    } else {
        analogWrite(PinIN3, 0);
        analogWrite(PinIN4, 0);
    }
    }


    void carForward() { carAction(1, 0, 1, 0, highSpeed, highSpeed); }
    void carReverse() { carAction(0, 1, 0, 1, lowSpeed, lowSpeed); }
    void carLeftTurn() { carAction(0, 0, 1, 0, lowSpeed, highSpeed); }
    void carRightTurn() { carAction(1, 0, 0, 0, highSpeed, lowSpeed); }
    void carStop() { carAction(0, 0, 0, 0, 0, 0); }

    void run(){
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


    void loop() {
    run();
    }