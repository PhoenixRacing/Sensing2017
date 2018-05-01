#include <Wire.h>
#define NODE_ADDRESS 3 // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 2 // Number of bytes  expected to be received by the master I2C node

#ifdef __cplusplus
extern "C"{
  #endif
  #include <moving.h>
  #ifdef __cplusplus
} ;
#endif
#define PIN_1 A0
#define BUFF1_LEN 15

const int threshold = 700;
const unsigned int debounce = 400; //this is calculated, little higher than the length of our highest frequency 
unsigned long lastTime;

cyclical_buffer * buff1;

unsigned int data; //store recent data globally so it can be sent whenever master node requests it

void requestEvent(){ //This function is called like an interrupt whenever master node calls requestFrom(NODE_ADDRESS)
  byte* payload = (byte*) & data; //important conversion from unsigned int to byte array
  Wire.write(payload, PAYLOAD_SIZE);
}

unsigned int convertUnits(unsigned long input){
   unsigned int freq = (1000000)/input;
  return freq;
}

void setup() {
  Wire.begin(NODE_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // call requestEvent() whenever master node asks for data
  buff1 = create_buffer(BUFF1_LEN);
  Serial.begin(115200);
  lastTime = micros();
}

void loop() {
    unsigned long revTime;
  if((analogRead(PIN_1) > threshold) && ((micros() - lastTime) > debounce)){
    revTime = micros() - lastTime;
    lastTime = micros();
    //Serial.println(revTime);
    unsigned int freq = convertUnits(revTime);
   //Serial.println(freq);
    add_data_point(buff1, freq);
    
    Serial.println(get_avg(buff1));
  }
    Serial.print(data);
}
