#ifdef __cplusplus
extern "C"{
  #endif
  #include <moving.h>
  #ifdef __cplusplus
} ;
#endif
#define PIN_1 A1
#define PIN_2 A2
#define BUFF1_LEN 10
#define BUFF2_LEN 5

cyclical_buffer * buff1;
cyclical_buffer * buff2;
void setup() {
  buff1 = create_buffer(BUFF1_LEN);
  buff2 = create_buffer(BUFF2_LEN);
  Serial.begin(9600);
}

void loop() {
  add_data_point(buff1, analogRead(PIN_1));
  add_data_point(buff2, analogRead(PIN_2));
  Serial.print(get_avg(buff1));
  Serial.print(",");
  Serial.println(get_avg(buff2));
}
