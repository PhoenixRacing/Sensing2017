int rpm = 4000;
int dutyCycle = 6;
unsigned long cycleTime = (2*60*1000000)/rpm;
unsigned long highTime = cycleTime/dutyCycle;
unsigned long lowTime = cycleTime - highTime;

void setup() {
  Serial.begin(9600);
  Serial.print("cycleTime= \t");
  Serial.println(cycleTime);
  Serial.print("lowTime= \t");
  Serial.println(lowTime);
  Serial.print("highTime= \t");
  Serial.println(highTime);

}

void loop() {
  digitalWrite(8, HIGH);
  delayMicroseconds(highTime);
  digitalWrite(8, LOW);
  delayMicroseconds(lowTime);
  

}
