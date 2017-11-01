const int out = 13;
const int highTime = 15;

void setup(){
  Serial.begin(9600);
  pinMode(out, OUTPUT);
}

void loop(){
  int val = analogRead(0);
  int freq = map(val, 0, 1023, 5, 50);
  Serial.println(freq);
  digitalWrite(out, HIGH);
  delay(highTime);
  digitalWrite(out, LOW);
  int delayTime = 1000/freq - highTime;
  delay(delayTime);
}
