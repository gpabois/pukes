#ifndef __KERNEL_SETUP_H__
#define __KERNEL_SETUP_H__

/**
 * @brief Entry point of the kernel (called by the bootloader)
 * 
 */
void setup_kernel();

/**
 * @brief Architecture-related setup.
 */
void setup_arch();

#endif