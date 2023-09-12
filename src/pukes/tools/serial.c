#include <pukes/tools/serial.h>
#include <pukes/tools/log.h>

#include <fcntl.h>
#include <termios.h>
 
uint8_t open_serial_port(const char * device, uint32_t baud_rate, SerialHandle_t* dest) {
    SerialHandle_t fd = open(device, O_RDWR | O_NOCTTY);
    // Cannot open device.
    if(fd == -1) {
        logn(ERROR, "cannot get file descriptor for %s", device);
        return ERR_SERIAL_CANNOT_OPEN_CONNECTION;
    }
        

    // Flush away any bytes previously read or written.
    int result = tcflush(fd, TCIOFLUSH);
    if(result) {
        logn(WARNING, "failed to discard the data written to the object");
    }

    struct termios options;
    result = tcgetattr(fd, &options);
    if(result) {
        logn(ERROR, "cannot get parameters for %s", device);
        close(fd);
        return ERR_SERIAL_CANNOT_GET_PARAMETERS;
    }

    // Turn off any options that might interfere with our ability to send and
    // receive raw binary bytes.
    options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    options.c_oflag &= ~(ONLCR | OCRNL);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    // Set up timeouts: Calls to read() will return as soon as there is
    // at least one byte available or when 100 ms has passed.
    options.c_cc[VTIME] = 1;
    options.c_cc[VMIN] = 0;

    switch(baud_rate) {
        case 4800:   cfsetospeed(&options, B4800);   break;
        case 9600:   cfsetospeed(&options, B9600);   break;
        case 19200:  cfsetospeed(&options, B19200);  break;
        case 38400:  cfsetospeed(&options, B38400);  break;
        case 115200: cfsetospeed(&options, B115200); break;
        default:
            logn(WARNING, "baud rate %u is not supported, using 9600.", baud_rate);
            cfsetospeed(&options, B9600);
            break;
    }
    cfsetispeed(&options, cfgetospeed(&options));
    result = tcsetattr(fd, TCSANOW, &options);
    if (result)
    {
        logn(ERROR, "cannot set parameters for %s", device);
        close(fd);
        return ERR_SERIAL_CANNOT_SET_PARAMETERS;
    }
    *dest = fd;
    return 0;
}

uint8_t close_serial_port(SerialHandle_t* dest) {
    if(*dest == -1) {
        return 0;
    }
    close(*dest);
    *dest = -1;
    return 0;
}

size_t write_port(SerialHandle_t fd, Buffer_t* buf) {
  size_t written = write(fd, buf->data, buf->length);
  consome_buffer(buf, written);
  return written;
}

size_t read_port(int fd, Buffer_t* buf)
{
  size_t received = 0;
  while (buf->length < buf->capacity)
  {
    size_t r = read(fd, buf->data + buf->length, buf->capacity - buf->length);
    if (r < 0)
    {
      log(ERROR, "failed to read from port");
      return -1;
    }
    if (r == 0)
    {
      // Timeout
      break;
    }
    buf->length += r;
    received += r;
  }
  return received;
}
 