/**
 * @file slip.h
 * @author Gaël PABOIS
 * @brief Serial Line Internet Protocol
 * @version 0.1
 * @date 2023-09-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <pukes/tools/serial.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Write a slip packet into the stream
 * 
 * @param fd 
 * @param data 
 * @param length 
 */
uint8_t write_slip_packet(SerialHandle_t fd, uint8_t* data, size_t length);