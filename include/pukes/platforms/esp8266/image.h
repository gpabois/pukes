/**
 * @file rom.h
 * @author your name (you@domain.com)
 * @brief Define ROM related functions and types
 * @version 0.1
 * @date 2023-09-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>

typedef struct {
	uint8_t i_ident;
	uint8_t i_flags[2];
	uint8_t sh_length;

	uint32_t entry;
} Image_Header_t;

typedef struct {
	uint8_t* address;
	uint32_t length;
} Image_Section_Header_t;