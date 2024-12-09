#ifndef __STREAM_H__
#define __STREAM_H__

#include <stdint.h>
#include <string>

namespace StreamDeviceAT{

    class Stream
    {
    public:

        Stream() {}
        
        ~Stream() {}

    public:

        virtual int available(void) = 0;
        virtual int read(void) = 0;
        virtual size_t write(uint8_t) = 0;

        virtual size_t print(const std::string&) = 0;
    };
    
}

#endif  // !__STREAM_H__
