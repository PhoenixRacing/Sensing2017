

int sensorpin = 0;            // analog pin used to connect the sharp sensor
int val = 0;                 // variable to store the values from sensor(initially zero)
const int ledPin = 13;       // 
double val2 = val*1.5;
const int TonePin = 8;

void setup()
{
  Serial.begin(9600);               // starts the serial monitor
  pinMode(ledPin, OUTPUT);          // declares output through pin 13 
  tone(TonePin, 440);               // declares that pin 8 will play 440hz
}
 
void loop()
{
  val = analogRead(sensorpin);       // reads the value of the sharp sensor
  Serial.println(val*1.5);            // prints the value of the sensor to the serial monitor
  delay(1);

if (val>100)  {
digitalWrite(ledPin, HIGH);
tone(TonePin, 440);
delay(128-(val/8));
digitalWrite(ledPin, LOW);
noTone(TonePin);
delay(128-(val/8));
}

else  {
  digitalWrite(ledPin, LOW);
  noTone(TonePin);
}
}
