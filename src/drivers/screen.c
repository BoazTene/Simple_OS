#include "screen.h"

/**
 * @brief Enables the cursor and sets the start and end of the cursor.
 * 
 * @param cursor_start the start of the cursor.
 * @param cursor_end the end of the cursor.
 */
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
    port_byte_out(REG_SCREEN_CTRL, 0x0A);
    port_byte_out(REG_SCREEN_DATA, (port_byte_in(REG_SCREEN_DATA) & 0xc) | cursor_start);

    port_byte_out(REG_SCREEN_CTRL, 0x0B);
    port_byte_out(REG_SCREEN_DATA, (port_byte_in(REG_SCREEN_DATA) & 0xe) | cursor_end);
}

/**
 * @brief disables the cursor.
 * 
 */
void disable_cursor() {
	port_byte_out(REG_SCREEN_CTRL, 0x0A);
	port_byte_out(REG_SCREEN_DATA, 0x20);
}

/**
 * @brief Get the screen offset.
 * 
 * @param column The column number
 * @param row The row number
 * @return int 
 */
unsigned char get_screen_offset(int column, int row) {
    return ((MAX_COLS * row) + column) * 2;   
}

void print_string(char *string, int column, int row, char attribute_type) {
    int init_offset = get_screen_offset(column, row); // the offset of the first char.
    int i = 0;

    char *test = "boaz";
    
    // print_char_offset(string[1], attribute_type, (init_offset));
    print_bytes(test[0], 0);
    // while (i < 6) {  
  
    //     i++;
    // }
}

void print_bytes(unsigned char n, int row) {
    unsigned char bytes[4];

    // n = 'b';
  
    bytes[0] = (n >> 24);
    bytes[1] = (n >> 16);
    bytes[2] = (n >> 8);
    bytes[3] = n ;

    print_char(bytes[0] + '0', 1 + row, 0, WHITE_ON_BLACK);
    print_char(bytes[1] + '0', 2 + row, 0, WHITE_ON_BLACK);
    print_char(bytes[2] + '0', 3 + row, 0, WHITE_ON_BLACK);
    print_char(bytes[3] + '0', 4 + row, 0, WHITE_ON_BLACK);
}

void print_char(char character, int column, int row, char attribute_type) {
    if (!attribute_type) {
        attribute_type = WHITE_ON_BLACK;
    }

    int offset;

    if (column >= 0 && row >= 0) {
        offset = get_screen_offset(column, row);
    } else {
        offset = get_cursor();
    }

    print_char_offset(character, attribute_type, offset);
}

/**
 * @brief prints a char at a specific offset.
 * 
 * @param character character to print.
 * @param attribute_type the type attribute of the char. 
 * @param offset the offset in the array.
 */
void print_char_offset(char character, char attribute_type, int offset) {
    unsigned char *video_memory = (unsigned char*) VIDEO_ADDRESS;
    video_memory += offset;

    *video_memory = character;
    video_memory++;
    *video_memory = attribute_type;
}

/**
 * @brief Feels the entire video buffer with spaces with and white on black attribute.
 * 
 */
void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    unsigned char *screen = (unsigned char * ) VIDEO_ADDRESS;


    for (i = 0; i < screen_size; i++) {
        print_char_offset(' ', WHITE_ON_BLACK, i*2);
    }

    set_cursor(get_screen_offset(0, 0));
}

// /* Print a char on the screen at col , row , or at cursor position */
// void print_char(char character, char attribute_byte ) {
//     /* Create a byte ( char ) pointer to the start of video memory */
//     unsigned char *vidmem = ( unsigned char *) (VIDEO_ADDRESS);

//     *vidmem = character;
//     vidmem++;
//     *vidmem = attribute_byte;
// }

/**
 * @brief Get the cursor offset.
 * 
 * @return int 
 */
int get_cursor() {
    // The device uses its control register as an index
    // to select its internal registers , of which we are
    // interested in :
    // reg 14: which is the high byte of the cursor ’s offset
    // reg 15: which is the low byte of the cursor ’s offset
    // Once the internal register has been selected , we may read or
    // write a byte on the data register .
    
    // port_byte_out(REG_SCREEN_CTRL, 14);
    // int offset = port_byte_in (REG_SCREEN_DATA) << 8;
    // port_byte_out ( REG_SCREEN_CTRL , 15);
    // offset += port_byte_in ( REG_SCREEN_DATA);

    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */

    // Since the cursor offset reported by the VGA hardware is the
    // number of characters , we multiply by two to convert it to
    // a character cell offset .
    // return offset*2;
}

void set_cursor(int offset) {
    // int offset = get_screen_offset(x, y);
    offset /= 2;

    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}
