/**
 * @file buffer.h
 * @author your name (you@domain.com)
 * @brief Simple buffer
 * @version 0.1
 * @date 2023-09-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define MIN(a, b) (a < b) ? (a) : (b)
#define MAX(a, b) (a < b) ? (b) : (a)

typedef struct {
    uint8_t *data;
    size_t capacity;
    size_t length;
} Buffer_t;

void init_buffer(Buffer_t* buf, uint8_t* array, size_t length);

/**
 * @brief Read values from the buffer and copy it to data
 * 
 * @param buf 
 * @param data 
 * @param length 
 * @return size_t 
 */
size_t read_buffer(Buffer_t* buf, uint8_t* data, size_t length);

/**
 * @brief Consume length bytes from the buffer (does not perform copy)
 * 
 * @param buf 
 * @param length 
 * @return size_t 
 */
size_t consume_buffer(Buffer_t* buf, size_t length);

/**
 * @brief Write data to the buffer
 * 
 * @param buf 
 * @param data 
 * @param length 
 * @return size_t The number of bytes written.
 */
size_t write_buffer(Buffer_t* buf, uint8_t* data, size_t length);

/**
 * @brief Write a byte in the buffer
 * 
 * @param buf 
 * @param byte 
 * @return size_t 
 */
size_t write_byte(Buffer_t* buf, uint8_t byte);

/**
 * @brief Write a word in the buffer
 * 
 * @param buf 
 * @param byte 
 * @return size_t 
 */
size_t write_word(Buffer_t* buf, uint16_t word);