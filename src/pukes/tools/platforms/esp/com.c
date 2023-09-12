#include <pukes/tools/platforms/esp/com.h>
#include <pukes/tools/serial.h>
#include <pukes/tools/slip.h>

uint8_t open_esp(const char *device, EspType_t* type, Esp_t* esp) {
    esp->type = type;
    return open_serial_port(device, esp->type->baudrate, &esp->fd);
}

uint8_t close_esp(Esp_t* esp) {
    return close_serial_port(&esp->fd);
}

uint8_t esp_send_command(Esp_t* esp, Esp_Command_t* cmd) {
    return write_slip_packet(
        esp->fd,
        cmd,
        sizeof(Esp_Command_Header_t) + cmd->hdr.size
    );
}