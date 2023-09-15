#ifndef __KERNEL_MEMORY_BANK_H__
#define __KERNEL_MEMORY_BANK_H__

#include <stdint.h>

typedef struct {
    size_t length;
    size_t start_paddr;

} Memory_Bank_t;

#endif