#include "device_driver.h"
#include <stdexcept>

#define REPEAT (4)

class ReadFailException : public std::exception
{ 
public:
    using _Mybase = std::exception;
    explicit ReadFailException(const char* _Message) : _Mybase(_Message) {}
};

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    unsigned char ret = m_hardware->read(address);
    for (int i=0; i<REPEAT; i++)
    {
        if (ret != m_hardware->read(address))
        {
            throw ReadFailException("Reliability read failed");
        }
    }
    return (int)(ret);
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}