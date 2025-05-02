#include <IRremote.hpp>

// Pin de señal conectado al módulo KY-022
#define IR_RECEIVE_PIN 15
#define LedPin 11

void setup() {
  Serial.begin(9600);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); 
  Serial.println("Receptor IR iniciado");
}

void loop() {
Serial.println("nada");
  if (IrReceiver.decode()) {                                                                      

    digitalWrite(LedPin, HIGH);
    Serial.print("Código recibido: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
     delay(3000);

    IrReceiver.resume(); 
    digitalWrite(LedPin, LOW);
  }
}