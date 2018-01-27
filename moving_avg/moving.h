typedef struct cyclical_buffer
{
  int index;
  int size;
  unsigned int * buffer;
} cyclical_buffer;

cyclical_buffer * create_buffer(int size);
void add_data_point(cyclical_buffer * buff, unsigned int datum);
unsigned int get_avg(cyclical_buffer * buff);
void print_buffer(cyclical_buffer * buff);
