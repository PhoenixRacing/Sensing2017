#include <Wire.h>
#define NODE_ADDRESS 3 // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 2 // Number of bytes  expected to be received by the master I2C node

#define DEBUG

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
#define DEBOUNCE 175000 //(us) this is calculated, a little lower than the wavelength of our highest frequency 
#define MAXTIME 240000 //wavelength of lowest measurable frequency
unsigned long lastTime;

cyclical_buffer * buff1;

unsigned int data; //store recent data globally so it can be sent whenever master node requests it

void requestEvent(){ //This function is called like an interrupt whenever master node calls requestFrom(NODE_ADDRESS)
  byte* payload = (byte*) & data; //important conversion from unsigned int to byte array
  Wire.write(payload, PAYLOAD_SIZE);
}

unsigned int convertRPM(unsigned long input){
  if(input<=DEBOUNCE+1000){
    return 9999;
  }
  if(input>=MAXTIME){
    return 0;
  }
  unsigned int RPM = (2*60*1000000)/input;
  return RPM;
}

unsigned int convertHz(unsigned long input){
  unsigned int Hz = (1000000)/input;
  return Hz;
}

void setup() {
  Wire.begin(NODE_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // call requestEvent() whenever master node asks for data
  buff1 = create_buffer(BUFF1_LEN);
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
  lastTime = micros();
}

void loop() {
    unsigned long revTime;
  if((analogRead(PIN_1) > THRESHOLD) && ((micros() - lastTime) > DEBOUNCE)){
    revTime = micros() - lastTime;
    lastTime = micros();
    unsigned int rpm = convertRPM(revTime);
    #ifdef DEBUG
    Serial.print(rpm);
    Serial.print(" RPM | \t");
    Serial.print(convertHz(revTime));
    Serial.println(" Hz");
    #endif
    add_data_point(buff1, rpm);
    data = get_avg(buff1);
  }
  if((micros() - lastTime) > MAXTIME){
    data = 0;
    buff1 = create_buffer(BUFF1_LEN);
  }
}
