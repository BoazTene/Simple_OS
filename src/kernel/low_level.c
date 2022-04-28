#include "low_level.h"

/**
 * @brief A handly C wrapper function for the byte in assembly instruction.
 * 
 * @param port The device port
 * @return unsigned char 
 */
unsigned char port_byte_in(unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%al": "=a" (result): "d" (port));

    return result;
}

/**
 * @brief A handy C wrapper function for the byte 'out' assembly instruction.
 *  
 * 
 * @param port The device's port 
 * @param data The data to send to the device.
 */
void port_byte_out(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx": : "a" (data), "d" (port));
}

/**
 * @brief A handly C wrapper function for the word 'in' assembly instruction.
 * 
 * @param port The devices's port
 * @return unsigned char 
 */
unsigned char port_word_in(unsigned short port) {
    unsigned short result;
    __asm__("In %%dx, %%ax": "=a" (result): "d" (port));
    
    return result;
}

/**
 * @brief A handly C wrapper function for the word 'out' assembly instruction.
 * 
 * @param port The device's port.
 * @param data The data to send to the device.
 */
void port_word_out(unsigned short port, unsigned char data) {
    __asm__("out %%ax, %%dx":: "a" (data), "d" (data));
}