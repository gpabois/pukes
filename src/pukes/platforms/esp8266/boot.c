#include <pukes/platforms/esp8266/builtins.h>
#include <pukes/platforms/esp8266/image.h>

typedef void Entry_t(void);

#define MAX_SPI_READ_SIZE 16
#define MIN(a, b) a < b ? a : b

/**
 * @brief Load image from SPI Flash
 * 
 * @param pos 
 * @return Entry_t* 
 */
Entry_t* load_image_from_flash(uint32_t pos) {
    uint8_t sec_id;
    uint8_t* write_pos;
    uint32_t remaining;

    Image_Header_t hdr;
    Image_Section_Header_t sec_hdr;

    SPIRead(pos, &hdr, sizeof(Image_Header_t));
    pos += sizeof(Image_Header_t);

    // Load every image sections
    for(sec_id = hdr.length; sec_id > 0; sec_id--) {
        SPIRead(pos, &sec_hdr, sizeof(Image_Section_Header_t));
        pos += sizeof(Image_Section_Header_t);

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

/**
 * @brief Boot stage 2
 * @note
 * Load kernel image from the SPI Flash 
 * then jump to the entry point.
 * 
 * @param pos 
 */
void _call_boot_stage_2(uint32_t pos) {
    Entry_t* entry = load_image_from_flash(pos);
    // Jump to the entry
    entry();
}