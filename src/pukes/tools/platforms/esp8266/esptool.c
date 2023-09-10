#include <pukes/elf/elf.h>
#include <pukes/platforms/esp8266/rom.h>

#include <stdio.h>

void create_binary(const char* obj_filpath) {
    FILE* out = 0;
    FILE* in = 0;
    Elf_t elf = {.__data=0};

    in = fopen(in, "rb");
    int elfErrCode = load_elf_from_file(in, &elf);
    // Something went wrong...
    if(elfErrCode) {
        goto cleanup;
    }
    fclose(in); in = 0;

    cleanup:
        if(in) fclose(in);
        if(out) fclose(out);
        delete_elf(&elf);

    return;
}