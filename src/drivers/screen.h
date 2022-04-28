
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// Attribute byte for our default colour scheme .
#define WHITE_ON_BLACK 0x0f
// Screen device I / O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#include "stdint.h"


void print_char(char character, int column, int row, char attribute_type);

void print_string(char *string, int column, int row, char attribute_type);

int get_cursor();

void set_cursor(int offset);

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);

void disable_cursor();

void clear_screen();