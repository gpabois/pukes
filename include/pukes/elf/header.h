#pragma once

/**
 * @file elf.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>

#define EI_NIDENT 16
#define EI_MAG0 0x7f
#define EI_MAG1 'E'
#define EI_MAG2 'L'
#define EI_MAG3 'F'
#define Elf32_Addr uint32_t
#define Elf32_Off uint32_t
#define Elf32_Word uint32_t
/**
 * @brief 
 * @note ELF Header File
 * See https://man7.org/linux/man-pages/man5/elf.5.html
*/
typedef struct {
    /**
     * @brief This array of bytes specifies how to interpret the file, 
     * independent of the processor or the file's remaining contents.  
     * 
     * @note
     * Within this array everything is named by macros, 
     * which start with the prefix EI_ and may contain
     * values which start with the prefix ELF.  
     * The following macros are defined:
     * - EI_MAG0: The first byte of the magic number.  It must be filled with ELFMAG0.  (0: 0x7f)
     * - EI_MAG1: The second byte of the magic number.  It must be filled with ELFMAG1.  (1: 'E')
     * - EI_MAG2: The third byte of the magic number.  It must be filled with ELFMAG2.  (2: 'L')
     * - EI_MAG3: The fourth byte of the magic number.  It must be filled with ELFMAG3.  (3: 'F')
     * - EI_CLASS: The fifth byte identifies the architecture for this binary:
     *  -# ELFCLASSNONE: This class is invalid.;
     *  -# ELFCLASS32: This defines the 32-bit architecture.  
     *      It supports machines with files and virtual address spaces up to 4 Gigabytes.
     *  -# ELFCLASS64: This defines the 64-bit architecture.
     *
     */
    uint8_t       e_ident[EI_NIDENT];
    /**
     * @brief This member of the structure identifies the object file type:
     * - ET_NONE: An unknown type ;
     * - ET_REL: A relocatable file ;
     * - ET_EXEC: An executable file ;
     * - ET_DYN: A shared object ;
     * - ET_CORE: A core file.
     * 
     */
    uint16_t      e_type;
    uint16_t      e_machine;
    uint32_t      e_version;
    Elf32_Addr    e_entry;
    Elf32_Off     e_phoff;
    Elf32_Off     e_shoff;
    uint32_t      e_flags;
    uint16_t      e_ehsize;
    uint16_t      e_phentsize;
    uint16_t      e_phnum;
    uint16_t      e_shentsize;
    uint16_t      e_shnum;
    uint16_t      e_shstrndx;
} Elf32_ElfHdr_t;

/**
 * @brief The program header
 */
typedef struct {
    /**
     * @brief This member of the structure indicates what kind of
     * segment this array element describes or how to interpret
     * the array element's information.
     */
    uint32_t   p_type;
    /**
     * @brief This member holds the offset from the beginning of the
     * file at which the first byte of the segment resides.
     */
    Elf32_Off  p_offset;
    /**
     * @brief This member holds the virtual address at which the first
     * byte of the segment resides in memory.
     */
    Elf32_Addr p_vaddr;
    /**
     * @brief On systems for which physical addressing is relevant, this
     * member is reserved for the segment's physical address.
     * @note
     * Under BSD this member is not used and must be zero.
     * 
     */
    Elf32_Addr p_paddr;
    /**
     * @brief This member holds the number of bytes in the file image of
     * the segment.  It may be zero.
     */
    uint32_t   p_filesz;
    /**
     * @brief This member holds the number of bytes in the memory image
     * of the segment.  It may be zero.
     */
    uint32_t   p_memsz;
    /**
     * @brief This member holds a bit mask of flags relevant to the segment:

              PF_X   An executable segment.
              PF_W   A writable segment.
              PF_R   A readable segment.

              A text segment commonly has the flags PF_X and PF_R .  A
              data segment commonly has PF_W and PF_R.
     */
    uint32_t   p_flags;
    /**
     * @brief This member holds the value to which the segments are
              aligned in memory and in the file.  Loadable process
              segments must have congruent values for p_vaddr and
              p_offset, modulo the page size.  Values of zero and one
              mean no alignment is required.  Otherwise, p_align should
              be a positive, integral power of two, and p_vaddr should
              equal p_offset, modulo p_align.
     * 
     */
    uint32_t   p_align;
} Elf32_Phdr_t;

/**
 * @brief 
 * 
 */
typedef struct {
    /**
     * @brief This member specifies the name of the section.  Its value
     * is an index into the section header string table section,
     * giving the location of a null-terminated string.
     */
    uint32_t   sh_name;
    /**
     * @brief This member categorizes the section's contents and
     * semantics.
     */
    uint32_t   sh_type;
    /**
     * @brief Sections support one-bit flags that describe miscellaneous
     * attributes.  If a flag bit is set in sh_flags, the
     * attribute is "on" for the section.  Otherwise, the
     * attribute is "off" or does not apply.  Undefined
     * attributes are set to zero.
     */
    uint32_t   sh_flags;
    /**
     * @brief 
     * 
     */
    Elf32_Addr sh_addr;
    Elf32_Off  sh_offset;
    uint32_t   sh_size;
    uint32_t   sh_link;
    uint32_t   sh_info;
    uint32_t   sh_addralign;
    uint32_t   sh_entsize;
} Elf32_Shdr_t;