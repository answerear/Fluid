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

#ifndef __T3D_SYSTEM_H__
#define __T3D_SYSTEM_H__


#include "T3DSingleton.h"
#include "T3DPlatformPrerequisites.h"
#include "T3DClass.h"


namespace Tiny3D
{
    class IFactory;

    /**
     * @class System
     * @brief 系统类.
     * @note 该类对一些全局的单例创建和释放，为上层提供框架层和系统层统一接口.
     */
    class T3D_PLATFORM_API System : public Singleton<System>
    {
        T3D_DISABLE_COPY(System);

        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief Constructor for System.
         */
        System();

        /**
         * @brief Destructor for System.
         */
        ~System();

        /**
         * @brief 初始化系统
         * @note 没有调用初始化之前，部分功能无法使用
         */
        int32_t init();

        /**
         * @brief 每个程序循环调用处理.
         * @return void
         */
        void poll();

        /**
         * @brief 获取操作系统适配层工厂接口对象
         */
        IFactory &getPlatformFactory()
        {
            return (*mPlatformFactory);
        }

    private:
        IFactory        *mPlatformFactory;
        TimerManager    *mTimerMgr;
        Console         *mConsole;
        DeviceInfo      *mDeviceInfo;
    };

    #define T3D_SYSTEM              (System::getInstance())
    #define T3D_PLATFORM_FACTORY    (T3D_SYSTEM.getPlatformFactory())
}


#endif
