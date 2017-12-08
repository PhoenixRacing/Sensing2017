#include <Wire.h>

#define NODE_ADDRESS 2 // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 2 // Number of bytes  expected to be received by the master I2C node



const int gearbox_pin = 5;
const int rpm_pin = 2; // interrupts must be on pins 2,3 for 328 based arduinos

int sensor_buffer_i = 0;

const int max_samples = 50;
int gearbox_temps[max_samples];
unsigned long wheel_rpm_timings[max_samples];

const int sensor_delay = 500;
const int data_send_delay = 1000;

unsigned long last_time_read_sensors = 0;
unsigned long last_time_send_data = 0;

volatile int wheel_rpm_this_window = 0;

void increment_wheel_rpm_isr() {
  wheel_rpm_this_window += 1;
}

int read_gearbox_temp(){
  // Unimplemented
  return -1;
}

void read_sensors() {
  sensor_buffer_i = (sensor_buffer_i + 1) % max_samples;
  wheel_rpm_timings[sensor_buffer_i] = wheel_rpm_this_window;
  wheel_rpm_this_window = 0;

  gearbox_temps[sensor_buffer_i] = read_gearbox_temp();
}

void send_data() {
  // Average and send
  // Unimplemented
}

void request_event()
{
  byte* payload = (byte*) & data;
  Wire.write(payload,PAYLOAD_SIZE);
}

void setup() {
  Serial.begin(9600);

  Wire.begin(NODE_ADDRESS);  // Activate I2C network
  Wire.onRequest(request_event); // Request attention of master node

  pinMode(gearbox_pin, INPUT);

  // Attach an interrupt to rpm_pin. When it rises (low to high) it triggers increment_wheel_rpm_isr
  pinMode(rpm_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(rpm_pin), increment_wheel_rpm_isr, RISING);
}

void loop() {
  if (millis() > last_time_read_sensors + sensor_delay) {
    read_sensors();
  }

  if (millis() > last_time_send_data + data_send_delay) {
    send_data();
  }
}
