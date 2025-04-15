#pragma once
#include "device_driver.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;

class Application
{
public:
    Application(DeviceDriver *pstDeviceDriver) : m_pstDeviceDriver{pstDeviceDriver} {}

    vector<int> ReadAndPrint(long nStartAddr, long nEndAddr)
    {
        vector<int> ret;

        for (long addr=nStartAddr; addr<=nEndAddr; addr++)
        {
            int data = m_pstDeviceDriver->read(addr);
            ret.push_back(data);
            cout << "ADDR(" << addr << ") : " << data << "\n";
        }

        return ret;
    }

    void WriteAll(int data)
    {
        for (long addr=0; addr<=4; addr++)
        {
            m_pstDeviceDriver->write(addr, data);
        }
    }
private:
    DeviceDriver *m_pstDeviceDriver;
};