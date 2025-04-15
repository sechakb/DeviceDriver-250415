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

class DeviceDriverTest : public testing::Test
{
protected:
    // void SetUp() override
    // {
    // }
public:
    const long ADDRESS = 0xFF;

    MockFlash stNormalFlash;
    MockFlash stBadFlash;
    DeviceDriver stDeviceDriver { nullptr };

    void SetupNormal()
    {
        EXPECT_CALL(stNormalFlash, read(ADDRESS))
            .Times(5)
            .WillRepeatedly(testing::Return(0));
    }

    void SetupBad()
    {
        EXPECT_CALL(stBadFlash, read(ADDRESS))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillRepeatedly(testing::Return(1));
    }
};

TEST_F(DeviceDriverTest, ReadFromHWSuccess)
{
    stDeviceDriver.SetDeviceDriver(&stNormalFlash);
    SetupNormal();

    int data = stDeviceDriver.read(ADDRESS);
    EXPECT_EQ(0, data);
}

TEST_F(DeviceDriverTest, ReadFromHWFail)
{
    stDeviceDriver.SetDeviceDriver(&stBadFlash);
    SetupBad();

    try
    {
        int data = stDeviceDriver.read(ADDRESS);
        FAIL();
    }
    catch(const ReadFailException &e)
    {
        EXPECT_EQ(string{ e.what() }, string{ "Reliability read failed" });
    }
}