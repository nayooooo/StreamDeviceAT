#ifndef __HARDWARESERIAL_H__
#define __HARDWARESERIAL_H__

#include "../../Stream/Stream.h"

#include <Arduino.h>

namespace StreamDeviceAT{

    class HardwareSerial : public StreamDeviceAT::Stream
    {
    public:

        HardwareSerial(): _uart_nr(UART0), _rx_size(256), _tx_buff("") {}
        
        ~HardwareSerial() {}

    public:

        void begin(unsigned long baud);
        void end(void);

        int available(void) override;
        int read(void) override;
        size_t write(uint8_t c) override { return write(&c, 1); }
        size_t write(const uint8_t *buffer, size_t size);

        size_t print(const std::string& s) override { return write(reinterpret_cast<const uint8_t*>(s.c_str()), s.length()); }

    private:

        int _uart_nr;
        uart_t* _uart = nullptr;
        size_t _rx_size;

        std::string _tx_buff;
    };

}

#endif  // !__HARDWARESERIAL_H__
