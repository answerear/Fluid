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

#ifndef __T3D_DEVICE_INFO_INTERFACE_H__
#define __T3D_DEVICE_INFO_INTERFACE_H__


#include "T3DPlatformPrerequisites.h"
#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DClass.h"


namespace Tiny3D
{
    class IDeviceInfo
    {
        T3D_DECLARE_INTERFACE(IDeviceInfo);
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 獲取平台類型
         */
        virtual uint32_t getPlatform() const = 0;

        /**
         * @brief 獲取軟件版本號字符串
         */
        virtual const String &getSoftwareVersion() const = 0;

        /**
         * @brief 設置軟件版本號字符串
         */
        virtual void setSoftwareVersion(const char *version) = 0;

        /**
         * @brief 獲取操作系統版本號字符串
         */
        virtual const String &getOSVersion() const = 0;

        /**
         * @brief 獲取設備機型版本信息字符串
         */
        virtual const String &getDeviceVersion() const = 0;

        /**
         * @brief 獲取屏幕寬度
         */
        virtual int32_t getScreenWidth() const = 0;

        /**
         * @brief 獲取屏幕高度
         */
        virtual int32_t getScreenHeight() const = 0;

        /**
         * @brief 獲取屏幕像素密度
         */
        virtual float getScreenDPI() const = 0;

        /**
         * @brief 獲取CPU類型信息
         */
        virtual const String &getCPUType() const = 0;

        /**
         * @brief 獲取CPU架構
         */
        virtual const String &getCPUArchitecture() const = 0;

        /**
         * @brief 獲取CPU核數
         */
        virtual int32_t getCPUCores() const = 0;

        /**
         * @brief 獲取系統內存總數
         */
        virtual uint64_t getSystemRAM() const = 0;

        /**
         * @brief 獲取設備ID
         */
        virtual const String &getDeviceID() const = 0;
    };
}


#endif  /*__T3D_DEVICE_INFO_INTERFACE_H__*/
