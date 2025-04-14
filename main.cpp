#include "gmock/gmock.h"
#include "device_driver.h"

int main()
{
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

TEST(DeviceDriver, ReadFromHW)
{
    // TODO : replace hardware with a Test Double
    FlashMemoryDevice *hardware = nullptr;
    DeviceDriver driver{ hardware };
    int data = driver.read(0xFF);
    EXPECT_EQ(0, data);
}