#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <stdint.h>

#define SerialHandle_t int

#define ERR_SERIAL_CANNOT_OPEN_CONNECTION 0x1
#define ERR_SERIAL_CANNOT_GET_PARAMETERS 0x2
#define ERR_SERIAL_CANNOT_SET_PARAMETERS 0x3
 
/**
 * @brief Open a connection through a serial port (USB, UART, etc.)
 * 
 * @param device 
 * @param baud_rate 
 * @param fd
 * @return uint8t_t 0 on success, else error code.
 */

uint8_t open_serial_port(const char * device, uint32_t baud_rate, SerialHandle_t* fd);
/**
 * @brief Close the serial port
 * 
 * @param fd 
 * @return uint8_t 
 */
uint8_t close_serial_port(SerialHandle_t* fd);
/**
 * @brief Write to the port.
 * 
 * @param fd 
 * @param buffer 
 * @param size 
 * @return size_t the number of bytes written.
 */

size_t write_port(SerialHandle_t fd, uint8_t * buffer, size_t size);
/**
 * @brief Read value from the port.
 * 
 * @param fd 
 * @param buffer 
 * @param size 
 * @return size_t the number of bytes read.
 */
size_t read_port(SerialHandle_t fd, uint8_t * buffer, size_t size);

#endif