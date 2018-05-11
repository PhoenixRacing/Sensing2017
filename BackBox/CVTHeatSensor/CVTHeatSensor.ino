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
#define NODE_ADDRESS 90 // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 2 // Number of bytes  expected to be received by the master I2C node
const int refreshRate = 500;
unsigned int data;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);

  Serial.println("Adafruit MLX90614 test");  
  Wire.begin(NODE_ADDRESS);  // Activate I2C network
  Wire.onRequest(requestEvent); // Request attention of master node
  mlx.begin();  
}

void loop() {
  data = mlx.readObjectTempC();
  Serial.print("Temperature read: ");
  Serial.println(data);
  Serial.println("*****");
  delay(refreshRate);
}
void requestEvent()
{
  byte payload[2];
  payload[0] = data & 0xFF;
  payload[1] = (data >> 8) &0xFF;
  Wire.write(payload,PAYLOAD_SIZE);
}
