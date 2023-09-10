#include <pukes/platforms/esp8266/builtins.h>
#include <pukes/platforms/esp8266/rom.h>

// new rom header (irom section first) there is
// another 8 byte header straight afterward the
// standard header
typedef struct {
	// general rom header
	uint8_t magic;
	uint8_t count; // second magic for new header
	uint8_t flags1;
	uint8_t flags2;
	uint32_t entry;
	// new type rom, lib header
	uint32_t add; // zero
	uint32_t len; // length of irom section
} rom_header_new;

typedef void Code_t(void);

#define MAX_SPI_READ_SIZE 16
#define MIN(a, b) a < b ? a : b

Code_t* load_rom(uint32_t pos) {
    uint8_t sec_id;
    uint8_t* write_pos;
    uint32_t remaining;

    ROM_Header_t hdr;
    ROM_Section_Header_t sec_hdr;

    SPIRead(pos, &hdr, sizeof(ROM_Header_t));
    pos += sizeof(ROM_Header_t);

    for(sec_id = hdr.count; sec_id > 0; sec_id--) {
        SPIRead(pos, &sec_hdr, sizeof(ROM_Section_Header_t));
        pos += sizeof(ROM_Section_Header_t);

        write_pos = sec_hdr.address;
        remaining = sec_hdr.length;

        // Load the whole section, 16 bytes per 16 bytes.
        while(remaining > 0) {
            uint32_t read = MIN(remaining, MAX_SPI_READ_SIZE);
            SPIRead(pos, write_pos, read);
            pos += MIN(remaining, MAX_SPI_READ_SIZE);
            write_pos += read;
            remaining -= read;
        }
    }

    return hdr.entry;
}

void _call_boot_stage_2(uint32_t pos) {
    Code_t* entry = load_rom(pos);
    entry();
}