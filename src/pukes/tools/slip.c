#include <pukes/tools/slip.h>
#include <pukes/tools/serial.h>
#include <pukes/tools/buffer.h>

/**
 * @brief Initialise a SLIP datagram
 * 
 * @param fd 
 * @return size_t 
 */
size_t begin_slip_packet(SerialHandle_t fd) {
    uint8_t _buf[1] = {0xC0};

}
size_t write_slip_packet(SerialHandle_t fd, Buffer_t* data) {
    uint8_t _buf[1000];
    Buffer_t buff;
    init_buffer(&buff, _buf, 1000);

    size_t written = 0;
    uint16_t w;

    for(uint8_t* byte = data->data; data->length > 0; byte++, data->length--) 
    {
        switch (*byte) {
            case 0xC0:
                write_byte(&buff, 0xDB);
                write_byte(&buff, 0xDC);
            break;
            case 0xDB:
                write_byte(&buff, 0xDB);
                write_byte(&buff, 0xDD);
            break;
            default:
                write_byte(&buff, byte);
            break;
        }
    }

   return write_port(fd, data);
}

size_t end_slip_packet(SerialHandle_t fd) {
    uint8_t _buf[1] = {0xC0};
    Buffer_t buf = {.length=1, .data=_buf, .capacity=1};
    return write_port(fd, &buf);
}