#ifndef __HARDWARESERIAL_H__
#define __HARDWARESERIAL_H__

#include "../Stream/Stream.h"

namespace StreamDeviceAT{

    class HardwareSerial : public StreamDeviceAT::Stream
    {
    public:

        HardwareSerial() {}
        
        ~HardwareSerial() {}

    public:

        int available(void) override
        {
            return 0;
        }

        int read(void) override
        {
            return -1;
        }

        size_t print(const std::string&) override
        {
            return 0;
        }
    };

}

#endif  // !__HARDWARESERIAL_H__
