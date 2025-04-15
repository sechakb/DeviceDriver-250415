#pragma once

#include "flash_memory_device.h"

class MockFlash : public FlashMemoryDevice
{
public:
    // unsigned char read(long address) override {}
    // void write(long address, unsigned char data) override {}
    MOCK_METHOD(unsigned char, read, (long), (override));
    MOCK_METHOD(void, write, (long, unsigned char), (override));
};