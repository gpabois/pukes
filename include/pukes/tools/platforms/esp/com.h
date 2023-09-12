#ifndef __ESP_TOOLS_COM_H__
#define __ESP_TOOLS_COM_H__

#include <stdint.h>
#include <pukes/tools/serial.h>

#define ESP_OP_FLASH_BEGIN 0x02
#define ESP_OP_FLASH_DATA 0x03

typedef struct {
    SerialHandle_t fd;
    EspType_t* type;
} Esp_t;

typedef struct {
    const char* name;
    uint32_t sector_size;
    uint32_t baudrate;
    uint32_t ram_block_size;
    uint32_t flash_write_size;
} EspType_t;

static EspType_t Esp8266 = {
    .name = "ESP8266",
    .sector_size = 0x1000,
    .baudrate = 115200,
    .ram_block_size = 0x1800,
    .flash_write_size = 0x400
};

typedef struct {
    uint8_t direction;
    uint8_t op;
    uint16_t size;
    uint32_t checksum_or_value;
} Esp_Command_Header_t;

typedef struct {
    /**
     * @brief 0x00 for request, 0x01 for response
     */
    Esp_Command_Header_t hdr;
    uint8_t data[65535];
} Esp_Command_t;

/**
 * @brief Open a connection to the ESP
 * 
 * @param device 
 * @param esp 
 * @return uint8_t 
 */
uint8_t open_esp(const char *device, EspType_t* type, Esp_t* esp);

/**
 * @brief Close the connection to the ESP
 * 
 * @param esp 
 * @return uint8_t 
 */
uint8_t close_esp(Esp_t* esp);

/**
 * @brief Send a command to the ESP.
 * 
 * @param dev 
 * @param size 
 * @param offset 
 * @return uint8_t 
 */
uint8_t esp_send_command(Esp_t* esp, Esp_Command_t* cmd);


#endif