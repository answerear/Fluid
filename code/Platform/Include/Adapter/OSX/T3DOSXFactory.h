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

#ifndef __T3D_OSX_FACTORY_H__
#define __T3D_OSX_FACTORY_H__


#include "Adapter/T3DFactoryInterface.h"


namespace Tiny3D
{
    class OSXFactory : public IFactory
    {
    public:
        OSXFactory();
        virtual ~OSXFactory();

		/**
		 * @brief 创建操作系统平台相关的应用程序对象
		 * @return 返回平台相关的应用程序对象，需要用户调用delete释放对象
		 */
		virtual IApplication *createPlatformApplication() override;
		
		/**
		 * @brief 创建操作系统平台相关的窗口.
		 * @return 返回平台相关的窗口操作对象，需要用户调用delete释放对象
		 */
		virtual IWindow *createPlatformWindow() override;
		
		/**
		 * @brief 创建操作系统平台相关的时间对象.
		 * @return 返回平台相关的时间对象，需要用户调用delete释放对象
		 */
		virtual ITime *createPlatformTime() override;
		
        /**
         * @brief 创建操作系统平台相关的定时器服务对象.
         * @return 返回平台相关的定时器服务对象，需要用户调用delete释放对象
         */
        virtual ITimerService *createPlatformTimerService() override;
        
		/**
		 * @brief 创建操作系统平台相关的路径搜索对象.
		 * @return 返回平台相关的路径搜索对象，需要用户调用delete释放对象
		 */
		virtual IDir *createPlatformDir() override;
		
		/**
		 * @brief 创建操作系统平台相关的设备信息对象.
		 * @return 返回平台相关的设备信息对象，需要用户调用delete释放对象
		 */
		virtual IDeviceInfo *createPlatformDeviceInfo() override;
		
		/**
		 * @brief 创建操作系统平台相关的控制台对象.
		 * @return 返回平台相关的控制台对象，需要用户调用delete释放对象
		 */
		virtual IConsole *createPlatformConsole() override;
		
		/**
		 * @brief 获取当前平台类型.
		 * @return 返回当前平台类型
		 */
		virtual EPlatform getPlatform() override;

    };
}


#endif  /*__T3D_OSX_FACTORY_H__*/
