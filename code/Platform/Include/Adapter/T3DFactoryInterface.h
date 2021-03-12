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

#ifndef __T3D_FACTORY_INTERFACE_H__
#define __T3D_FACTORY_INTERFACE_H__


#include "T3DPlatformPrerequisites.h"
#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DClass.h"


namespace Tiny3D
{
    class IWindow;
    class IApplication;
    class ITime;
    class ITimerService;
    class IDir;
    class IDeviceInfo;
    class IConsole;

    enum EPlatform
    {
        E_PLATFORM_UNKNOWN = 0,
        E_PLATFORM_WIN32,
        E_PLATFORM_OSX,
        E_PLATFORM_LINUX,
        E_PLATFORM_IOS,
        E_PLATFORM_ANDROID,
    };

    /**
     * @class IFactory
     * @brief 操作系统适配层工厂接口.
     * @note 不同操作系统平台需要实现继承该类实现具体平台接口
     */
    class IFactory
    {
        T3D_DECLARE_INTERFACE(IFactory);
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 创建操作系统平台相关的应用程序对象
         * @return 返回平台相关的应用程序对象，需要用户调用delete释放对象
         */
        virtual IApplication *createPlatformApplication() = 0;

        /**
         * @brief 创建操作系统平台相关的窗口.
         * @return 返回平台相关的窗口操作对象，需要用户调用delete释放对象
         */
        virtual IWindow *createPlatformWindow() = 0;

        /**
         * @brief 创建操作系统平台相关的时间对象.
         * @return 返回平台相关的时间对象，需要用户调用delete释放对象
         */
        virtual ITime *createPlatformTime() = 0;

        /**
         * @brief 创建操作系统平台相关的定时器服务对象.
         * @return 返回平台相关的定时器服务对象，需要用户调用delete释放对象
         */
        virtual ITimerService *createPlatformTimerService() = 0;

        /**
         * @brief 创建操作系统平台相关的路径搜索对象.
         * @return 返回平台相关的路径搜索对象，需要用户调用delete释放对象
         */
        virtual IDir *createPlatformDir() = 0;

        /**
         * @brief 创建操作系统平台相关的设备信息对象.
         * @return 返回平台相关的设备信息对象，需要用户调用delete释放对象
         */
        virtual IDeviceInfo *createPlatformDeviceInfo() = 0;

        /**
         * @brief 创建操作系统平台相关的控制台对象.
         * @return 返回平台相关的控制台对象，需要用户调用delete释放对象
         */
        virtual IConsole *createPlatformConsole() = 0;

        /**
         * @brief 获取当前平台类型.
         * @return 返回当前平台类型
         */
        virtual EPlatform getPlatform() = 0;
    };

    /**
     * @brief 创建操作系统相关的适配层工厂对象.
     * @note 不同操作系统平台需要实现该接口以返回操作系统适配层工厂对象
     * @return 返回适配层工厂对象，需要用户调用delete释放资源
     */
    IFactory *createPlatformFactory();
}


#endif  /*__T3D_FACTORY_INTERFACE_H__*/
