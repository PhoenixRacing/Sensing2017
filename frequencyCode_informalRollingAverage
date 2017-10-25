float hall_effect_sensor = 0;            // analog pin used to connect the sharp sensor
float val = 0;                 // variable to store the values from sensor(initially zero)
float time[100];
float diff[100];
int i=0;
int k=0;
float total_time = 0;
float frequency;

void setup(){
  Serial.begin(9600);
}
 
void loop(){
  val = analogRead(hall_effect_sensor);       // reads the value of the Hall Effect Sensor

    if (val<100) {
        time[i] = (millis());
        diff[k] = time[i]-time[i-1];
        total_time = total_time+time[i];

        float rollingAvg = (((diff[k])+
        (diff[k-1])+
        (diff[k-2])+
        (diff[k-3])+
        (diff[k-4]))/5);

        frequency = 1000/rollingAvg;

        Serial.print("Frequency: ");
        Serial.print(frequency);
        Serial.println();
        delay(100);
        i++;
        k++;

        if (i>5000){
          i=0;
          k=0;
        }
    }
}
