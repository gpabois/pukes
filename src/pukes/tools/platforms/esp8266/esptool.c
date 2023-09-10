#include <pukes/elf/elf.h>
#include <pukes/platforms/esp8266/image.h>
#include <pukes/tools/log.h>

#include <stdio.h>

#define ERR_BUFFER_PARTIAL_WRITE 0x1
#define ERR_SECTION_NOT_FOUND 0x2

/**
 * @brief Write ELF section into the file buffer.
 * 
 * @param section 
 * @param buff 
 * @return char returns 0 on success, or an error code.
 */
char write_elf_section(Elf_Section_t* section, FILE* buff) {
    Image_Section_Header_t ishdr = {
        .address = section->hdr->sh_addr,
        .length = section->hdr->sh_size
    };

    const void* data = section->data;

    // Write section header
    fwrite(&ishdr, sizeof(Image_Section_Header_t), 1, buff);
    // Write section data
    fwrite(data, ishdr.length, 1, buff);

    return 0;
}

char write_elf_section_by_name(Elf_t* elf, const char* name, FILE* buff) {
    Elf_Section_t sec;

    if(elf_find_section_by_name(elf, name, &sec)) {
        return write_elf_section(&sec, buff);
    }

    return ERR_SECTION_NOT_FOUND;
}

void create_bin_file(const char* obj_fp, const char* out_fp, char* sections[], int sec_length) {
    FILE* out = 0;
    FILE* in = 0;
    Elf_t elf = {.__data=0};

    out = fopen(out, "wb");

    in = fopen(in, "rb");
    int elfErrCode = load_elf_from_file(in, &elf);
    fclose(in); in = 0;

    if(elfErrCode) goto cleanup; // Something went wrong...

    Image_Header_t ihdr = {
        .i_ident = BIN_MAGIC_FLASH,
        .length = sec_length
    };

    // Write the header.
    fwrite(&ihdr, sizeof(Image_Header_t), 1, out);
    // Write the sections.
    for(uint8_t i = 0; i < ihdr.length; i++) {
        int errcode = write_elf_section_by_name(&elf, sections[i], out);
        
        if(errcode) {
            goto cleanup;
        }
    }


    cleanup:
        if(in) fclose(in);
        if(out) fclose(out);
        delete_elf(&elf);

    return;
}