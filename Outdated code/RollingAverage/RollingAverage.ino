const int samples = 10;
const int refreshRate = 500;
int rolling[samples]; // global variable will keep track of relevant samples

void setup() {
  Serial.begin(9600);

}

void loop() {
  int tempRolling[samples];
   
  int data = analogRead(0);
  tempRolling[samples - 1] = data; // the last element is the new value
  
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

