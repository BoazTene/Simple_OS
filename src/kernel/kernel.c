
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
void printChar(char chr) {
    char* video_memory = (char*) 0xb8000;
    *video_memory = chr; // putting a character into the video memory address.
}

// The kernel entry point.
void _start() {
    
}   


