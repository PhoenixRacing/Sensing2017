#include <Adafruit_MAX31865.h>
#include <Wire.h>
// Use software SPI: CS, DI, DO, CLK

#define DEBUG

#define RREF  430.0
#define RNOMINAL  100.0
#define NODE_ADDRESS 2 // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 2 // Number of pieces of information to send
unsigned int data[] = {0,0}; //store recent data globally so it can be sent whenever master node requests it
Adafruit_MAX31865 max = Adafruit_MAX31865(8, 11, 12, 13);

#ifdef __cplusplus
extern "C"{
  #endif
  #include <moving.h>
  #ifdef __cplusplus
} ;
#endif
#define PIN_1 A0
#define BUFF1_LEN 10

#define THRESHOLD 700

#define MAXTIME 400000 //
#define CONVERTER 29750*22 //wheel diameter is 22"
unsigned long lastTime;
//unsigned float lastfreqmeasurement = 0.6; //start with the frequency for going at 5MPH
unsigned long lastRevTime = 800000;

cyclical_buffer * buff1;

unsigned int convertMPH(unsigned long input){
  if(input<=lastRevTime+1000){
    return 9999;
  }
  if(input>=MAXTIME){
    return 0;
  }
  unsigned int MPH = CONVERTER/input;
  return MPH;
}

unsigned int convertHz(unsigned long input){
  unsigned int Hz = (1000000)/input;
  return Hz;
}

void setup() {
#ifdef DEBUG
Serial.begin(115200);
Serial.println("Starting Wheel Speed and Gearbox Temperature Node in Debugging Mode");
#endif
max.begin(MAX31865_3WIRE);
Wire.begin(NODE_ADDRESS);  // Activate I2C network
Wire.onRequest(requestEvent); // call requestEvent() whenever master node asks for data
buff1 = create_buffer(BUFF1_LEN);
lastTime = micros();
}

void loop() {
  updateTemp();
  /* Ok so for variable debouncing for wheel speed:
   Expect 0.6-10Hz in frequency measurement based on 22in diameter wheels and 5-40mph.
   If we take measurements twice per wheel rotation, add in a factor of 2! we do not account for that
   Considering that the time between frequency measurements would be 1/freq
   and we want to lastRevTime something that's ... about half of that time
   We're changing lastRevTime based on the lastfreqmeasurement, considering it won't go all over the place
   And then doing 1/freqmeasured * 1000000 to get into microseconds
   And then *1/2 to get the amount of lastRevTime time we want to be reasonable, based on
   the previous frequency measurement. */
  //lastRevTime = (1/lastfreqmeasurement) * .5 * 1000000 ; //convert the last freq measured into seconds, then microseconds, and take half of it as your lastRevTime time.
  unsigned long revTime;
  if((analogRead(PIN_1) > THRESHOLD) && ((micros() - lastTime) > lastRevTime*.75)){
    revTime = micros() - lastTime;
    lastTime = micros();
    unsigned int mph = convertMPH(revTime);
    #ifdef DEBUG
    Serial.print(mph);
    Serial.print(" MPH |\t");
    Serial.print(convertHz(revTime));
    Serial.println(" Hz");
    #endif
    add_data_point(buff1, mph);
    data[0] = get_avg(buff1);
  }
  if((micros() - lastTime) > MAXTIME){
    data[0] = 0;
    buff1 = create_buffer(BUFF1_LEN);
    lastRevTime = MAXTIME;
  }
  //lastfreqmeasurement = convertHz(revtime);
  lastRevTime = revTime;

}
//
//void requestEvent(){ //This function is called like an interrupt whenever master node calls requestFrom(NODE_ADDRESS)
//   byte* payload = (byte*) & data[1]; //important conversion from unsigned int to byte array
//   Wire.write(payload, PAYLOAD_SIZE);
//   #ifdef DEBUG
//   Serial.print((byte)payload[0]);
//   Serial.print("|");
//   Serial.println((byte)payload[1]);
//   Serial.println("requested");
//  #endif
//}

void requestEvent(){ //This function is called like an interrupt whenever master node calls requestFrom(NODE_ADDRESS)
  //send speed
  byte* payload1 = (byte*) & data[0];
  Wire.write(payload1, PAYLOAD_SIZE);

  byte* payload2 = (byte*) & data[1];
  Wire.write(payload2, PAYLOAD_SIZE);

  #ifdef DEBUG
  Serial.println("requested");
  #endif
}

void updateTemp(){
  uint16_t  rtd = max.readRTD();
  float ratio = rtd;
  ratio /= 32768;
  float temp = max.temperature(100, RREF);
  data[1] = temp ; //max.temperature(100,RREF);
  #ifdef DEBUG
  //Serial.print("temp: ");
  //Serial.println(data[1]);
  checkRTDFault();
  #endif
}

void checkRTDFault(){
  uint8_t fault = max.readFault();
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
