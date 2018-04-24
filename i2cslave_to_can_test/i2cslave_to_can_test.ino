int potIn = A0;
const byte dataLen = 4;
int potRead;

#include <Wire.h>
#define NODE_ADDRESS 8 
#define PAYLOAD_SIZE 2
#define RREF      430.0 //we have PT100, resistor reference 
#define RNOMINAL  100.0 // The 'nominal' 0-degrees-C resistance of the sensor: 100.0 for PT100, 1000.0 for PT1000

Adafruit_MAX31865 max = Adafruit_MAX31865(5, 6, 7, 8); //SPI: CS, DI, DO, CLK

void setup() {
  Serial.begin(9600);
  Wire.begin(NODE_ADDRESS);  
  Wire.onRequest(sendData); 
  Serial.println("setup");
}

void loop() {
  delay(100);
  potRead = analogRead(potIn);  
  sendData(potRead);
}

void sendData(unsigned int data){
  byte* payload = (byte*) & data; 
  Wire.write(payload, PAYLOAD_SIZE);
  Serial.println(payload[1]);
}

void checkFaults(uint8_t fault){
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold");
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold");
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias");
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage");
    }
    max.clearFault();
  }
}

void printArray(int arr[], int len){ // useful for debugging
  Serial.print("{");
  for(int i = 0; i < len - 1; i ++){
    Serial.print(arr[i]);
    Serial.print(", ");
  }
  Serial.print(arr[len - 1]);
  Serial.println("}");
}
