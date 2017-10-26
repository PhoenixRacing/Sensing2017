#include <Wire.h>

#define NODE_ADDRESS 2 // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 2 // Number of bytes  expected to be received by the master I2C node
byte nodePayload[PAYLOAD_SIZE];

const int samples = 10;
const int debounce = 10;
const int threshold = 100;
int rolling[samples]; // global variable will keep track of relevant samples

const int wheelDia = 20;

const int inp = 0;

unsigned long lastTime;

void setup() {
  Serial.begin(9600);
  lastTime = micros();

  Wire.begin(NODE_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // Request attention of master node
}

void loop() {
  int sense = analogRead(inp);
  unsigned long revTime;

  if(sense < threshold && (unsigned long)(micros() - lastTime) > debounce){
    revTime = micros() - lastTime;
    lastTime = micros();
    avg = updateAverage(revTime);
    speed = convertUnits(avg);
    sendData(speed);
  }
}

void sendData(int data){
  byte* payload = (byte*) & data;
  Wire.write(payload, PAYLOAD_SIZE);
}

void receiveData(){
  byte payload[PAYLOAD_SIZE];
  for(int i = 0; i < PAYLOAD_SIZE; i ++){
    payload[i] = Wire.read()
  }
  int data = *((int*)payload);
}

int updateAverage(int newVal){
  int tempRolling[samples];

  tempRolling[samples - 1] = newVal; // the last element is the new value

  for(int i = 0; i < samples - 1; i ++){ // copy the last elements of the old array into the beginning of the new array
    tempRolling[i] = rolling[i+1];
  }

  for(int i = 0; i < samples; i ++){ // overwrite the old array with the new one
    rolling[i] = tempRolling[i];
  }
  int sum = 0;
  for(int i = 0; i < samples; i ++){ // sum the elements
    sum += rolling[i];
  }
  int avg = sum/samples;

  return avg;
}

int convertUnits(int input){
  //to Hz:
  unsigned int freq = 1000000/input;
  //MPH:
  float circ = wheelDia * 3.1416;
  int speedMPH = (freq * 3600 * circ)/63360;
  return speedMPH;
  /*
  //RPM:
  unsigned int RPM = input * 60 * 2;
  return RPM;
  */
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
