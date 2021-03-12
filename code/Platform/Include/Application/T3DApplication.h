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


#ifndef __T3D_APPLICATION_H__
#define __T3D_APPLICATION_H__


#include "T3DPlatformPrerequisites.h"
#include "T3DSingleton.h"
#include "T3DClass.h"


namespace Tiny3D
{
    class System;
    class IApplication;

    class T3D_PLATFORM_API Application : public Singleton<Application>
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * Constructor
         */
        Application();

        /**
         * Destructor
         */
        virtual ~Application();

        /**
         * @brief 应用初始化，这个由具体平台来调用，用户不需要调用
         * @return 调用成功返回T3D_OK
         */
        TResult init();

        /**
         * @brief 应用事件处理
         */
        bool pollEvents();

        /**
         * @brief 应用程序退出释放资源
         * @return void
         */
        void release();

        void *getNativeAppObject();

        virtual bool applicationDidFinishLaunching() = 0;

        virtual void applicationDidEnterBackground() = 0;

        virtual void applicationWillEnterForeground() = 0;

        virtual void applicationWillTerminate() = 0;

        virtual void applicationLowMemory() = 0;

    private:
        System          *mSystem;       /// 具体平台系统对象
        IApplication    *mApp;          /// 具体平台应用程序对象
    };

    #define T3D_APPLICATION     (Application::getInstance())
}



#endif  /*__T3D_APPLICATION_H__*/
