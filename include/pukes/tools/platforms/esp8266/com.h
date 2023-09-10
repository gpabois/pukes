#ifndef __ESP_TOOLS_COM_H__
#define __ESP_TOOLS_COM_H__

#include <stdint.h>
#include <pukes/tools/serial/serial.h>

#define ESP_CMD_FLASH_BEGIN 0x02

typedef struct {
    char magic[5];
    char byte;
    char op;
    uint32_t length;
} Esp_RequestHeader_t;

/**
 * @brief Write binary into the flash memory of the device.
 * 
 * @param device the port name
 * @param length the number of binaries to write
 * @param binary_fp the filenames
 * @param offset the offsets
 * @return uint8_t 
 */
uint8_t write_flash(const char *device, uint32_t length, const char* binary_fp[], uint32_t offset);

/**
 * @brief Send a command to the ESP to beginning flash writing.
 * 
 * @param dev 
 * @param size 
 * @param offset 
 * @return uint8_t 
 */
uint8_t begin_write_flash(SerialHandle_t* dev, uint32_t size, uint32_t offset);


#endif