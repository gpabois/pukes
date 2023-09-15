#ifndef __KERNEL_MEMORY_ZONE_H__
#define __KERNEL_MEMORY_ZONE_H__

#include <pukes/kernel/memory/page.h>
#include <stddef.h>

typedef struct {
    Page_t* first;
    size_t length;
    Memory_Zone_t* next;
} Memory_Zone_t;

#endif