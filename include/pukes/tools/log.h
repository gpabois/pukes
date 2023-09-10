/**
 * @file log.h
 * @author Gaël PABOIS
 * @brief 
 * @version 0.1
 * @date 2023-09-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __LOG_H__
#define __LOG_H__

#include <stdint.h>

#define DEBUG 0
#define TRACE 1
#define INFO 2
#define WARNING 3
#define ERROR 4
#define PANIC 5

void logn(uint8_t level, const char *fmt, ...);
void log(uint8_t level, const char *fmt, ...);

#endif