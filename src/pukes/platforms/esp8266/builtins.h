/**
 * @file builtins.h
 * @author Gaël PABOIS
 * @brief Builtins ESP8266 functions
 * @note
 * Those functions are avalaible in the ROM section
 * @version 0.1
 * @date 2023-09-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>

extern uint32_t SPIRead(uint32_t addr, void *outptr, uint32_t len);
extern uint32_t SPIEraseSector(int);
extern uint32_t SPIWrite(uint32_t addr, void *inptr, uint32_t len);

extern void ets_printf(char*, ...);
extern void ets_delay_us(int);
extern void ets_memset(void*, uint8_t, uint32_t);
extern void ets_memcpy(void* dest, const void* src, uint32_t size);