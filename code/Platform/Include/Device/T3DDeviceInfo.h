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

#ifndef __T3D_DEVICE_INFO_H__
#define __T3D_DEVICE_INFO_H__


#include "T3DSingleton.h"
#include "T3DPlatformPrerequisites.h"
#include "T3DClass.h"


namespace Tiny3D
{
    class IDeviceInfo;

    class T3D_PLATFORM_API DeviceInfo : public Singleton<DeviceInfo>
    {
        T3D_DISABLE_COPY(DeviceInfo);
        T3D_DECLARE_CLASS();

    public:
        static const uint32_t PLATFORM_UNKNOWN;
        static const uint32_t PLATFORM_WINDOWS;
        static const uint32_t PLATFORM_MACOSX;
        static const uint32_t PLATFORM_LINUX;
        static const uint32_t PLATFORM_IOS;
        static const uint32_t PLATFORM_ANDROID;

        static const char* Unknown;
        static const char* Windows;
        static const char* MacOSX;
        static const char* Linux;
        static const char* iOS;
        static const char* Android;

    public:
        DeviceInfo();
        virtual ~DeviceInfo();

        /**
         * @brief 獲取平台類型
         */
        uint32_t getPlatform() const;

        /**
         * @brief 獲取平台類型字符串
         */
        String getPlatformString() const;

        /**
         * @brief 獲取軟件版本號字符串
         */
        String getSoftwareVersion() const;

        /**
         * @brief 設置軟件版本號字符串
         */
        void setSoftwareVersion(const char *version);

        /**
         * @brief 獲取操作系統版本號字符串
         */
        String getOSVersion() const;

        /**
         * @brief 獲取設備機型版本信息字符串
         */
        String getDeviceVersion() const;

        /**
         * @brief 獲取系統詳細信息
         */
        String getSystemInfo() const;

        /**
         * @brief 獲取屏幕寬度.
         */
        int32_t getScreenWidth() const;

        /**
         * @brief 獲取屏幕高度.
         */
        int32_t getScreenHeight() const;

        /**
         * @brief 獲取屏幕像素密度.
         */
        float getScreenDPI() const;

        /**
         * @brief 獲取CPU類型信息
         */
        String getCPUType() const;

        /**
         * @brief 獲取CPU架構
         */
        String getCPUArchitecture() const;

        /**
         * @brief 獲取CPU核數
         */
        int32_t getCPUCores() const;

        /**
         * @brief 獲取系統內存總數.
         */
        uint64_t getSystemRAM() const;
        
        /**
         * @brief 獲取設備ID.
         */
        String getDeviceID() const;

    protected:
        IDeviceInfo *mDeviceInfo;
    };

    #define T3D_DEVICE_INFO     DeviceInfo::getInstance()
}


#endif  /*__T3D_DEVICE_INFO_H__*/
