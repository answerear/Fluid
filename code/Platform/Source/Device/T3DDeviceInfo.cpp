/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2020  Answer Wong
 * For latest info, see https://github.com/answerear/Tiny3D
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

#include "Device/T3DDeviceInfo.h"
#include "Adapter/T3DDeviceInfoInterface.h"
#include "Adapter/T3DFactoryInterface.h"
#include "T3DSystem.h"

#include <sstream>


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(DeviceInfo);
    T3D_IMPLEMENT_CLASS_0(DeviceInfo);

    //--------------------------------------------------------------------------

    const uint32_t DeviceInfo::PLATFORM_UNKNOWN = E_PLATFORM_UNKNOWN;
    const uint32_t DeviceInfo::PLATFORM_WINDOWS = E_PLATFORM_WIN32;
    const uint32_t DeviceInfo::PLATFORM_MACOSX = E_PLATFORM_OSX;
    const uint32_t DeviceInfo::PLATFORM_LINUX = E_PLATFORM_LINUX;
    const uint32_t DeviceInfo::PLATFORM_IOS = E_PLATFORM_IOS;
    const uint32_t DeviceInfo::PLATFORM_ANDROID = E_PLATFORM_ANDROID;

    const char* DeviceInfo::Unknown = "Unknown";
    const char* DeviceInfo::Windows = "Windows";
    const char* DeviceInfo::MacOSX = "Mac OSX";
    const char* DeviceInfo::Linux = "Linux";
    const char* DeviceInfo::iOS = "iOS";
    const char* DeviceInfo::Android = "Android";

    //--------------------------------------------------------------------------

    DeviceInfo::DeviceInfo()
        : mDeviceInfo(nullptr)
    {
        mDeviceInfo = T3D_PLATFORM_FACTORY.createPlatformDeviceInfo();
    }

    //--------------------------------------------------------------------------

    DeviceInfo::~DeviceInfo()
    {
        T3D_SAFE_DELETE(mDeviceInfo);
    }

    //--------------------------------------------------------------------------

    uint32_t DeviceInfo::getPlatform() const
    {
        uint32_t unPlatform = PLATFORM_UNKNOWN;

        if (mDeviceInfo != nullptr)
        {
            unPlatform = mDeviceInfo->getPlatform();
        }

        return unPlatform;
    }

    //--------------------------------------------------------------------------

    String DeviceInfo::getPlatformString() const
    {
        String strPlatform = Unknown;

        if (mDeviceInfo != nullptr)
        {
            switch (mDeviceInfo->getPlatform())
            {
            case PLATFORM_WINDOWS:
                {
                    strPlatform = Windows;
                }
                break;
            case PLATFORM_MACOSX:
                {
                    strPlatform = MacOSX;
                }
                break;
            case PLATFORM_LINUX:
                {
                    strPlatform = Linux;
                }
                break;
            case PLATFORM_IOS:
                {
                    strPlatform = iOS;
                }
                break;
            case PLATFORM_ANDROID:
                {
                    strPlatform = Android;
                }
                break;
            }
        }

        return strPlatform;
    }

    //--------------------------------------------------------------------------

    String DeviceInfo::getSoftwareVersion() const
    {
        if (mDeviceInfo != nullptr)
        {
            return mDeviceInfo->getSoftwareVersion();
        }
        return "";
    }

    //--------------------------------------------------------------------------

    void DeviceInfo::setSoftwareVersion(const char *version)
    {
        if (mDeviceInfo != nullptr)
        {
            mDeviceInfo->setSoftwareVersion(version);
        }
    }

    //--------------------------------------------------------------------------

    String DeviceInfo::getOSVersion() const
    {
        if (mDeviceInfo != nullptr)
        {
            return mDeviceInfo->getOSVersion();
        }
        return "";
    }

    //--------------------------------------------------------------------------

    String DeviceInfo::getDeviceVersion() const
    {
        if (mDeviceInfo != nullptr)
        {
            return mDeviceInfo->getDeviceVersion();
        }
        return "";
    }

    //--------------------------------------------------------------------------

    String DeviceInfo::getSystemInfo() const
    {
        std::stringstream ss;

        // OS Version
        ss << "Operating System : " << getOSVersion() << std::endl;
        // Device Version
        ss << "Device Version : " << getDeviceVersion() << std::endl;
        // Device ID
        ss << "Device ID : " << getDeviceID() << std::endl;
        // CPU Type
        ss << "CPU Type : " << getCPUType() << std::endl;
        // CPU Architecture
        ss << "CPU Architecture : " << getCPUArchitecture() << std::endl;
        // CPU Cores
        ss << "CPU Cores : " << getCPUCores() << std::endl;
        // System RAM
        ss << "System RAM : " << getSystemRAM() << "MB" << std::endl;
        // Screen size & DPI
        ss << "Screen Size : " << getScreenWidth() << "x" << getScreenHeight() << std::endl;
        ss << "Screen DPI : " << getScreenDPI() << std::endl;

        return ss.str();
    }

    //--------------------------------------------------------------------------

    int32_t DeviceInfo::getScreenWidth() const
    {
        if (mDeviceInfo != nullptr)
        {
            return mDeviceInfo->getScreenWidth();
        }
        return 0;
    }

    //--------------------------------------------------------------------------

    int32_t DeviceInfo::getScreenHeight() const
    {
        if (mDeviceInfo != nullptr)
        {
            return mDeviceInfo->getScreenHeight();
        }
        return 0;
    }

    //--------------------------------------------------------------------------

    float DeviceInfo::getScreenDPI() const
    {
        if (mDeviceInfo != nullptr)
        {
            return mDeviceInfo->getScreenDPI();
        }
        return 0.0f;
    }

    //--------------------------------------------------------------------------

    String DeviceInfo::getCPUType() const
    {
        if (mDeviceInfo != nullptr)
        {
            return mDeviceInfo->getCPUType();
        }
        return "";
    }

    //--------------------------------------------------------------------------

    String DeviceInfo::getCPUArchitecture() const
    {
        if (mDeviceInfo != nullptr)
        {
            return mDeviceInfo->getCPUArchitecture();
        }

        return "";
    }

    //--------------------------------------------------------------------------

    int32_t DeviceInfo::getCPUCores() const
    {
        if (mDeviceInfo != nullptr)
        {
            return mDeviceInfo->getCPUCores();
        }
        return 1;
    }

    //--------------------------------------------------------------------------

    uint64_t DeviceInfo::getSystemRAM() const
    {
        if (mDeviceInfo != nullptr)
        {
            return mDeviceInfo->getSystemRAM();
        }
        return 0;
    }

    //--------------------------------------------------------------------------

    String DeviceInfo::getDeviceID() const
    {
        if (mDeviceInfo != nullptr)
        {
            return mDeviceInfo->getDeviceID();
        }
        return "";
    }
}
