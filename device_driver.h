#pragma once
#include "flash_memory_device.h"
#include <stdexcept>

class ReadFailException : public std::exception
{ 
public:
    using _Mybase = std::exception;
    explicit ReadFailException(const char* _Message) : _Mybase(_Message) {}
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice *hardware);
    int read(long address);
    void write(long address, int data);
    void SetDeviceDriver(FlashMemoryDevice *hardware);

protected:
    FlashMemoryDevice *m_hardware;
};