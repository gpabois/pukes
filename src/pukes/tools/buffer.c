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

#include <pukes/tools/buffer.h>

void init_buffer(Buffer_t* buf, uint8_t* array, size_t length) {
    buf->data = array;
    buf->capacity = length;
    buf->length = 0;
}

size_t write_buffer(Buffer_t* buf, uint8_t* data, size_t length) {
    size_t rem = buf->capacity - buf->length;
    size_t written = MIN(rem, length);
    memcpy(buf->data + buf->length, data, written);
    buf->length += written;
    return written;
}

size_t read_buffer(Buffer_t* buf, uint8_t* data, size_t length) {
    size_t read = MIN(buf->length, length);
    size_t rem = buf->length - read;
    memcpy(data, buf->data, read);
    memmove(buf->data, buf->data + rem, rem);
    buf->length -= read;
    return read;
}