#include "device_driver.h"

#define REPEAT (4)

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
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
    if (m_hardware->read(address) != INVALID_DATA)
    {
        throw WriteFailException("Data already exists");
    }
    m_hardware->write(address, (unsigned char)data);
}