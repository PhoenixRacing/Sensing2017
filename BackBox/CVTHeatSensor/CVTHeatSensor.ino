/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#define NODE_ADDRESS 3 // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 2 // Number of bytes  expected to be received by the master I2C node
const int samples = 10;
const int refreshRate = 500;
unsigned int avg;
int rolling[samples]; // global variable will keep track of relevant samples

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);

  Serial.println("Adafruit MLX90614 test");  
  Wire.begin(NODE_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // Request attention of master node
  mlx.begin();  
}

void loop() {
  float tempRolling[samples];
  float data = mlx.readObjectTempC();
  tempRolling[samples - 1] = data;
  for(int i = 0; i < samples - 1; i ++){ // copy the last elements of the old array into the beginning of the new array
    tempRolling[i] = rolling[i+1];
  }
  
  for(int i = 0; i < samples; i ++){ // overwrite the old array with the new one
    rolling[i] = tempRolling[i];
  }
  float sum = 0;
  for(int i = 0; i < samples; i ++){ // sum the elements
    sum += rolling[i];
  }
  avg = sum/samples;
  
  printArray(rolling, samples);
  Serial.print("Rolling Average: ");
  Serial.println(avg);
  Serial.println("*****");
  delay(refreshRate);
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
void requestEvent()
{
  //currently sending values to LCD around 109 C
  byte payload[2];
  payload[0] = avg & 0xFF;
  payload[1] = (avg >> 8) &0xFF;
  Wire.write(payload,PAYLOAD_SIZE);
}
