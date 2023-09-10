#include <pukes/elf/elf.h>
#include <stdlib.h> 
#include <string.h>

const char* __string_table(Elf_t* elf) {
    Elf32_ElfHdr_t *hdr = elf->header;
    size_t pos = hdr->e_shoff + (hdr->e_shentsize * hdr->e_shstrndx);
    return elf->__data + pos;
}

char delete_elf(Elf_t* elf) {
    if(elf->__data != 0) free(elf->__data);
    elf->__data = 0;
}

Elf_Section_Iterator_t elf_iter_sections(Elf_t* elf) {
    Elf_Section_Iterator_t it = {
        .elf = elf,
        .curr = 0
    };
    return it;
}

char elf_find_section_by_name(Elf_t* elf, const char *name, Elf_Section_t* dest) {
    Elf_Section_Iterator_t it = elf_iter_sections(elf);

    while(elf_next_section_it(&it, dest)) {
        if(strcmp(dest->name, name))
            return 1;
    }

    return 0;
}

char elf_next_section_it(Elf_Section_Iterator_t* it, Elf_Section_t* dest) {
    Elf32_ElfHdr_t *hdr = it->elf->header;
    if(it->curr >= hdr->e_shnum) return 0;

    size_t sec_pos = hdr->e_shoff + (hdr->e_shentsize * it->curr);
    Elf32_Shdr_t* shdr = it->elf->__data + sec_pos;
    const char* sec_name = __string_table(it->elf) + shdr->sh_name;

    dest->hdr = shdr;
    dest->name = sec_name;
    dest->data = it->elf->__data + shdr->sh_offset;

    it->curr++;
    return 1;
}

char load_elf_from_file(FILE* file, Elf_t* dest) {
    // Get the length of the elf file.
    int length = fseek(file, 0L, SEEK_END);
    fseek(file, 0L, SEEK_SET); // Rewind to the beginning the file.

    // Allocate enough memory to store the content of the elf file.
    void* raw = malloc(length);
    if(raw == 0) return ELF_ERR_ALLOC_ERROR;
    
    // Read the whole file
    fread(raw, length, 1, file);
    
    // The first bytes are the elf header.
    if(length < sizeof(Elf32_ElfHdr_t)) return ELF_ERR_CANNOT_READ_HEADER;
    Elf32_ElfHdr_t* hdr = (Elf32_ElfHdr_t*)raw;

    // Assert the magic numbers
    if(memcmp(hdr->e_ident, "\x7fELF", 4)) return ELF_ERR_INVALID_MAGIC_NUMBERS;

    // Read string table section header
    dest->header = hdr;
    dest->__data = raw;
    dest->__len = length;

    return 0;
}