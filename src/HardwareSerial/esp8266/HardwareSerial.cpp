#include "HardwareSerial.h"

namespace StreamDeviceAT{

    void HardwareSerial::begin(unsigned long baud)
    {
        end();
        _uart = uart_init(_uart_nr, baud, static_cast<int>(SERIAL_8N1), static_cast<int>(SERIAL_FULL), 1, _rx_size, false);
    }

    void HardwareSerial::end(void)
    {
        if (uart_get_debug() == _uart_nr)
        {
            uart_set_debug(UART_NO);
        }

        uart_uninit(_uart);
        _uart = nullptr;
    }

    int HardwareSerial::available(void)
    {
        int result = static_cast<int>(uart_rx_available(_uart));
        if (!result)
        {
            optimistic_yield(10000);
        }
        return result;
    }

    int HardwareSerial::read(void)
    {
        return uart_read_char(_uart);
    }

    size_t HardwareSerial::write(const uint8_t *buffer, size_t size)
    {
        return uart_write(_uart, (const char*)buffer, size);
    }

}
