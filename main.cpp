#include "gmock/gmock.h"
#include "device_driver.h"
#include "mock_flash.h"
#include "app.h"
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

    MockFlash stMockFlash;
    DeviceDriver stDeviceDriver { &stMockFlash };
};

class ApplicationTest : public DeviceDriverTest
{
protected:
    // void SetUp() override
    // {
    // }
public:
    Application stApplication { &stDeviceDriver };
};

TEST_F(DeviceDriverTest, ReadFromHWSuccess)
{
    EXPECT_CALL(stMockFlash, read(ADDRESS))
        .Times(5)
        .WillRepeatedly(testing::Return(NORMAL_DATA1));

    int data = stDeviceDriver.read(ADDRESS);
    EXPECT_EQ(NORMAL_DATA1, data);
}

TEST_F(DeviceDriverTest, ReadFromHWFail)
{
    EXPECT_CALL(stMockFlash, read(ADDRESS))
        .WillOnce(testing::Return(NORMAL_DATA1))
        .WillOnce(testing::Return(NORMAL_DATA1))
        .WillRepeatedly(testing::Return(NORMAL_DATA2));

    try
    {
        stDeviceDriver.read(ADDRESS);
        FAIL();
    }
    catch(const ReadFailException &e)
    {
        EXPECT_EQ(string{ e.what() }, string{ "Reliability read failed" });
    }
}

TEST_F(DeviceDriverTest, WriteSuccess)
{
    EXPECT_CALL(stMockFlash, read(ADDRESS))
        .Times(1)
        .WillRepeatedly(testing::Return(INVALID_DATA));
    EXPECT_CALL(stMockFlash, write(ADDRESS, NORMAL_DATA1))
        .Times(1);

    stDeviceDriver.write(ADDRESS, NORMAL_DATA1);
}

TEST_F(DeviceDriverTest, WriteFail)
{
    EXPECT_CALL(stMockFlash, read(ADDRESS))
        .Times(1)
        .WillRepeatedly(testing::Return(NORMAL_DATA2));
    EXPECT_CALL(stMockFlash, write(testing::_, testing::_))
        .Times(0);

    try
    {
        stDeviceDriver.write(ADDRESS, NORMAL_DATA1);
    }
    catch(const WriteFailException &e)
    {
        EXPECT_EQ(string{ e.what() }, string{ "Data already exists" });
    }
    
}

TEST_F(ApplicationTest, ReadAndPrintSuccess)
{
    vector<int> expected;
    for (int i=0; i<=4; i++)
    {
        EXPECT_CALL(stMockFlash, read(i))
            .Times(5)
            .WillRepeatedly(testing::Return(i));
        expected.push_back(i);
    }

    EXPECT_THAT(expected, stApplication.ReadAndPrint(0, 4));
}

TEST_F(ApplicationTest, WriteAllSuccess)
{
    for (int i=0; i<=4; i++)
    {
        EXPECT_CALL(stMockFlash, read(i))
            .Times(1)
            .WillRepeatedly(testing::Return(INVALID_DATA));
        EXPECT_CALL(stMockFlash, write(i, NORMAL_DATA1))
            .Times(1);
    }

    stApplication.WriteAll(NORMAL_DATA1);
}