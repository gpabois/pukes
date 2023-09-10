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

#define BIN_MAGIC_FLASH 0xe9
#define BIN_MAGIC_IROM 2

typedef struct {
	/**
	 * @brief Magic number (Either BIN_MAGIC_FLASH or BIN_MAGIC_IROM)
	 */
	uint8_t i_ident;
	/**
	 * @brief Number of sections within the image.
	 */
	uint8_t length;
	uint8_t i_flags[2];

	uint32_t entry;
} Image_Header_t;

typedef struct {
	uint8_t* address;
	uint32_t length;
} Image_Section_Header_t;