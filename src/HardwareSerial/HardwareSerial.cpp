#include "HardwareSerial.h"

namespace StreamDeviceAT{

    void HardwareSerial::begin(unsigned long baud)
    {
        ;
    }

    void HardwareSerial::end(void)
    {
        ;
    }

    int HardwareSerial::available(void)
    {
        return static_cast<int>(_rx_buff.length());
    }

    int HardwareSerial::read(void)
    {
        return _rx_buff.length() ? static_cast<int>(_rx_buff[0]) : -1;
    }

    size_t HardwareSerial::write(const uint8_t *buffer, size_t size)
    {
        return 0;
}

}
