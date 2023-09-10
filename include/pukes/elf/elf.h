#ifndef __ELF_FILE_H__
#define __ELF_FILE_H__

#include <pukes/elf/header.h>
#include <stdio.h>

#define ELF_ERR_ALLOC_ERROR 0x01
#define ELF_ERR_CANNOT_READ_HEADER 0x02
#define ELF_ERR_INVALID_MAGIC_NUMBERS 0x03

typedef struct {
    void* __data;
    size_t __len;
    Elf32_ElfHdr_t *header;
} Elf_t;

typedef struct {
    Elf32_Shdr_t *hdr;
    const char* name;
    void* section;
} Elf_Section_t;

typedef struct {    
    Elf_t* elf;
    uint16_t curr;
} Elf_Section_Iterator_t;

/**
 * @brief Load ELF from file
 * 
 * @param file 
 * @param dest 
 * @return char 0 on success, else an error code
 */
char load_elf_from_file(FILE* file, Elf_t* dest);

/**
 * @brief Delete an ELF internal dynamically allocated data.
 * 
 * @param elf 
 * @return char 
 */
char delete_elf(Elf_t* elf);

/**
 * @brief Returns an iterator over the sections of the elf.
 * 
 * @param elf 
 * @return Elf_Section_Iterator_t 
 */
Elf_Section_Iterator_t elf_iter_sections(Elf_t* elf);

/**
 * @brief Iterate over the elf sections.
 * 
 * @param it 
 * @param dest 
 * @return char 1 if there is an item, 0 if not.
 */
char elf_next_section_it(Elf_Section_Iterator_t* it, Elf_Section_t* dest);

/**
 * @brief Rewind the iterator.
 * 
 * @param it 
 * @param dest 
 * @return char 1 if there is an item, 0 if not.
 */
char elf_rewind_section_it(Elf_Section_Iterator_t* it);

#endif