#pragma once
#include "flash_memory_device.h"
#include <stdexcept>

#define INVALID_DATA    (0xFF)
#define NORMAL_DATA1    (0xAA)
#define NORMAL_DATA2    (0x55)

class ReadFailException : public std::exception
{ 
public:
    using _Mybase = std::exception;
    explicit ReadFailException(const char* _Message) : _Mybase(_Message) {}
};

class WriteFailException : public std::exception
{ 
public:
    using _Mybase = std::exception;
    explicit WriteFailException(const char* _Message) : _Mybase(_Message) {}
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice *hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice *m_hardware;
};