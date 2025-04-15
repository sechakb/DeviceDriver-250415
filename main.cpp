#include "gmock/gmock.h"
#include "device_driver.h"
#include "mock_flash.h"
#include <string>

using std::string;

int main()
{
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

TEST(DeviceDriver, ReadFromHWSuccess)
{
    MockFlash stMockFlash;
    EXPECT_CALL(stMockFlash, read(0xFF))
        .Times(5)
        .WillRepeatedly(testing::Return(0));

    DeviceDriver driver{ &stMockFlash };
    int data = driver.read(0xFF);
    EXPECT_EQ(0, data);
}

TEST(DeviceDriver, ReadFromHWFail)
{
    MockFlash stMockFlash;
    EXPECT_CALL(stMockFlash, read(0xEE))
        .WillOnce(testing::Return(0))
        .WillOnce(testing::Return(0))
        .WillRepeatedly(testing::Return(1));

    try
    {
        DeviceDriver driver{ &stMockFlash };
        int data = driver.read(0xEE);
        FAIL();
    }
    catch(const ReadFailException &e)
    {
        EXPECT_EQ(string{ e.what() }, string{ "Reliability read failed" });
    }
}