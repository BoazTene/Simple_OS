void printf(char character) {
    char* video_memory = (char*) 0xb8000;
    *video_memory = character; // putting an X into the video memory address.
}

void main() {
    printf((char) 'X');
}   


