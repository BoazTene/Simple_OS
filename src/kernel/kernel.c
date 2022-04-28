#include "../drivers/screen.h"


/**
 * @brief Simulating the prinf in libc, the function gets an array of chars and print it to the screen.
 * sets the attribute
 * 
 * @param character 
 * @param attribute
 */
void printCharWithAttribute(char chr, int attribute) {
    char* video_memory = (char*) 0xb8000;
    *video_memory = chr; // putting a character into the video memory address.
    video_memory++;
    *video_memory = attribute;
}

/**
 * @brief Simulating the prinf in libc, the function gets an array of chars and print it to the screen.
 *  doesn't set the attribute.
 * @param character 
 */
// void printChar(char chr) {
//     char* video_memory = (char*) 0xb8000;
//     *video_memory = chr; // putting a character into the video memory address.
// }

// The kernel entry point.
void _start() {
    // enable_cursor(3, 7);
    // clear_screen();
    // set_cursor(0, 0);
    // print_char("1", -1, -1, WHITE_ON_BLACK);
    // set_cursor(4);
    // unsigned char bytes[4];
    // unsigned char n = 'b';

    // bytes[0] = (n >> 24) & 0xFF;
    // bytes[1] = (n >> 16) & 0xFF;
    // bytes[2] = (n >> 8) & 0xFF;
    // bytes[3] = n & 0xFF;

    char *string = "boaz";
    // string  

    // print_char((string[1] =="o"[0]) + "0"[0], 2, 0, WHITE_ON_BLACK);
    print_string(string, 2, 0, WHITE_ON_BLACK);
    // print_char(bytes[0] + '0', 0, 0, WHITE_ON_BLACK);
    // print_char(bytes[1] + '0', 1, 0, WHITE_ON_BLACK);
    // print_char(bytes[2] + '0', 2, 0, WHITE_ON_BLACK);
    // print_char(bytes[3] + '0', 3, 0, WHITE_ON_BLACK);
    // print_char(((int) n==9) + '0', 4, 0, WHITE_ON_BLACK);

}   


