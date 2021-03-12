/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2017  Answer Wong
 * For latest info, see https://github.com/asnwerear/Tiny3D
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#include "Adapter/Linux/T3DLinuxDeviceInfo.h"
#include "Adapter/T3DFactoryInterface.h"

#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/utsname.h>
#include <X11/Xlib.h>
#include <sstream>


namespace Tiny3D
{
    LinuxDeviceInfo::LinuxDeviceInfo()
        : mOSVersion()
        , mSWVersion()
        , mHWVersion()
        , mCPUType()
        , mCPUArchitecture()
        , mDeviceID()
        , mCPUCores(0)
        , mSystemRAM(0)
        , mScreenWidth(0)
        , mScreenHeight(0)
        , mScreenDPI(0.0f)
    {
        collectSystemInfo();
    }

    LinuxDeviceInfo::~LinuxDeviceInfo()
    {

    }

    void LinuxDeviceInfo::collectSystemInfo()
    {
        struct utsname name;
        if (uname(&name) == 0)
        {
            mHWVersion = name.release;
            mCPUArchitecture = name.machine;
        }

        // Operating System 相关信息
        collectOSInfo();

        // CPU相关信息
        collectCPUInfo();

        // 内存相关信息
        collectRAMInfo();

        // 设备信息
        collectDeviceInfo();

        // 屏幕信息
        collectScreenInfo();
    }

    void LinuxDeviceInfo::collectOSInfo()
    {
        FILE *fp = nullptr;

        do
        {
            fp = fopen("/proc/version", "r");
            if (fp == nullptr)
            {
                break;
            }

            while (!feof(fp))
            {
                char buf[128] = {0};
                fgets(buf, sizeof(buf)-1, fp);
                mOSVersion = buf;
                break;
            }
        } while(0);

        if (fp != nullptr)
        {
            fclose(fp);
        }
    }

    void LinuxDeviceInfo::collectCPUInfo()
    {
        FILE *fp = nullptr;

        do
        {
            fp = fopen("/proc/cpuinfo", "r");
            if (fp == nullptr)
            {
                break;
            }

            while (!feof(fp))
            {
                char buf[128] = {0};
                fgets(buf, sizeof(buf)-1, fp);
                String name = buf;
                if (name.find("model name") != String::npos)
                {
                    mCPUType = trim(name);
                }
                else if (name.find("cpu cores") != String::npos)
                {
                    String cores = trim(name);
                    mCPUCores = atoi(cores.c_str());
                }
            }
        } while(0);

        if (fp != nullptr)
        {
            fclose(fp);
        }
    }

    void LinuxDeviceInfo::collectRAMInfo()
    {
        FILE *fp = nullptr;

        do
        {
            fp = fopen("/proc/meminfo", "r");
            if (fp == nullptr)
            {
                break;
            }

            while (!feof(fp))
            {
                char buf[128] = {0};
                fgets(buf, sizeof(buf)-1, fp);
                String name = buf;
                if (name.find("MemTotal") != String::npos)
                {
                    String capacity = trim(name);
                    String total = capacity.substr(0, capacity.find("KB"));
                    int64_t memoryCapacity = atoi(total.c_str());
                    mSystemRAM = memoryCapacity / 1024;
                    break;
                }
            }
        } while(0);

        if (fp != nullptr)
        {
            fclose(fp);
        }
    }

    void LinuxDeviceInfo::collectDeviceInfo()
    {
        FILE *fp = nullptr;

        do
        {
            fp = fopen("/sys/class/dmi/id/product_uuid", "r");
            if (fp == nullptr)
            {
                break;
            }

            while (!feof(fp))
            {
                char buf[256] = {0};
                fgets(buf, sizeof(buf)-1, fp);
                mDeviceID = buf;
                size_t len = mDeviceID.length();
                mDeviceID.erase(len - 1);
                break;
            }
        } while(0);

        if (fp != nullptr)
        {
            fclose(fp);
        }
    }

    void LinuxDeviceInfo::collectScreenInfo()
    {
        // Screen Resolution
        Display *display;
        char *displayName = nullptr;
        display = XOpenDisplay(displayName);
        int w = DisplayWidth(display, 0);
        int h = DisplayHeight(display, 0);

        mScreenWidth = w;
        mScreenHeight = h;

        // DPI
        int W = DisplayWidthMM(display, 0);
        int H = DisplayHeightMM(display, 0);
        if (W != 0)
        {
            mScreenDPI = double(w) * 25.4 / double(W);
        }

        XCloseDisplay(display);
    }

    String LinuxDeviceInfo::trim(const String &text)
    {
        String name;

        do
        {
            size_t start = text.find(':') + 1;
            if (start == String::npos)
                break;

            while (text[start] == ' ')
            {
                start++;
            }

            size_t i = start;
            while (text[i] != '\n')
            {
                name.append(1, text[i]);
                i++;
            }
        } while(0);

        return name;
    }

    uint32_t LinuxDeviceInfo::getPlatform() const
    {
        return E_PLATFORM_LINUX;
    }

    const String &LinuxDeviceInfo::getSoftwareVersion() const
    {
        return mSWVersion;
    }

    void LinuxDeviceInfo::setSoftwareVersion(const char *version)
    {
        mSWVersion = version;
    }

    const String &LinuxDeviceInfo::getOSVersion() const
    {
        return mOSVersion;
    }

    const String &LinuxDeviceInfo::getDeviceVersion() const
    {
        return mHWVersion;
    }

    int32_t LinuxDeviceInfo::getScreenWidth() const
    {
        return mScreenWidth;
    }

    int32_t LinuxDeviceInfo::getScreenHeight() const
    {
        return mScreenHeight;
    }

    float LinuxDeviceInfo::getScreenDPI() const
    {
        return mScreenDPI;
    }

    const String &LinuxDeviceInfo::getCPUType() const
    {
        return mCPUType;
    }

    const String &LinuxDeviceInfo::getCPUArchitecture() const
    {
        return mCPUArchitecture;
    }

    int32_t LinuxDeviceInfo::getCPUCores() const
    {
        return mCPUCores;
    }

    uint32_t LinuxDeviceInfo::getSystemRAM() const
    {
        return mSystemRAM;
    }

    const String &LinuxDeviceInfo::getDeviceID() const
    {
        return mDeviceID;
    }
}
