

void init_oled();
//void write_oled();
void write_c(uint8_t command);
void write_d();

FILE oled_stream;

void oled_print_char(const char data);
void print_test();
void oled_print(const char* string);