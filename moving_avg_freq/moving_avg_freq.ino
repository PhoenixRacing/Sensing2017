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
const unsigned int debounce = 400;
unsigned long lastTime;

cyclical_buffer * buff1;


void setup() {
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
//  else{
//    Serial.println("Not");
//    }
}

unsigned int convertUnits(unsigned long input){
   unsigned int freq = (1000000)/input;
  return freq;
}
