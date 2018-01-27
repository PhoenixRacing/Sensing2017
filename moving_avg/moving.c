#include "moving.h"
#include "stdlib.h"
#include "stdio.h"

/**
 * This method creates a cyclical buffer of the desired size
 * @param size This is the size of the buffer
 */
cyclical_buffer * create_buffer(int size){
  unsigned int * buffer = malloc(sizeof(unsigned int)*size);
  cyclical_buffer * buff = malloc(sizeof(cyclical_buffer));
  buff->index = 0;
  buff->size = size;
  buff->buffer = buffer;
  return buff;
}

/**
 * This method adds a data point to the buffer
 * @param buff This is the buffer to add the point to
 * @param datum This is the point of data to add to the buffer
 */
void add_data_point(cyclical_buffer * buff, unsigned int datum){
  *(buff->buffer + buff->index) = datum;
  if(++(buff->index)>=buff->size)
    buff->index = 0;
}

/**
 * This method gets the current average of the cyclical buffer
 * @param buff This is the buffer to get the average of
 */
unsigned int get_avg(cyclical_buffer * buff){
  unsigned long sum = 0;
  for(int i = 0; i < buff->size; i++){
    sum += *(buff->buffer + i);
  }
  unsigned int res = sum/buff->size;
  return res;
}

/**
 * This method is used to print the buffer for debugging purposes
 * @param buff This is the buffer to print
 */
void print_buffer(cyclical_buffer * buff){
  printf("[");
  for(int i = 0; i < buff->size; i++){
    printf("%d",*(buff->buffer + i));
    if(i + 1 < buff->size)
      printf(",");
  }
  printf("]\n");
}

/*
Example code
int main (void){
  cyclical_buffer * buff = create_buffer(2); //create buffer of size 2
  add_data_point(buff, 2); //add data point (value:2) to the buffer
  add_data_point(buff, 4);
  add_data_point(buff, 7);
  add_data_point(buff, 3);// add more data points
  unsigned int avf = get_avg(buff); //get average of buffer
    
}
*/
