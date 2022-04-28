/**
 * @brief A handly C wrapper function for the byte in assembly instruction.
 * 
 * @param port The device port
 * @return unsigned char 
 */
unsigned char port_byte_in(unsigned short port);

/**
 * @brief A handly C wrapper function for the word 'in' assembly instruction.
 * 
 * @param port The devices's port
 * @return unsigned char 
 */
unsigned char port_word_in(unsigned short port);

/**
 * @brief A handy C wrapper function for the byte 'out' assembly instruction.
 *  
 * 
 * @param port The device's port 
 * @param data The data to send to the device.
 */
void port_byte_out(unsigned short port, unsigned char data);


/**
 * @brief A handly C wrapper function for the word 'out' assembly instruction.
 * 
 * @param port The device's port.
 * @param data The data to send to the device.
 */
void port_word_out(unsigned short port, unsigned char data);