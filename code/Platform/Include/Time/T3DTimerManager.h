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

#ifndef __T3D_TIMER_MANAGER_H__
#define __T3D_TIMER_MANAGER_H__


#include "T3DPlatformPrerequisites.h"
#include "T3DSingleton.h"
#include "T3DPlatformErrorDef.h"
#include "T3DClass.h"


namespace Tiny3D
{
    class ITimerListener;
    class ITimerService;

    class T3D_PLATFORM_API TimerManager : public Singleton<TimerManager>
    {
        friend class System;

        T3D_DECLARE_CLASS();

    private:
        /**
         * @brief 构造函数
         */
        TimerManager();

    public:
        static const ID INVALID_TIMER_ID;

        /**
         * @brief 析构函数
         */
        virtual ~TimerManager();

        /**
         * @brief 启动定时器
         * @param [in] interval : 时间间隔
         * @param [in] repeat : 是否循环定时器
         * @param [in] listener : 定时器回调对象
         * @return 调用成功返回有效定时器ID，否则返回T3D_INVALID_TIMER_ID
         */
        ID startTimer(uint32_t interval, bool repeat, ITimerListener *listener);

        /**
         * @brief 停止定时器
         * @param [in] timerID : 有效定时器ID，通过startTimer返回
         * @return 调用成功返回T3D_OK
         */
        TResult stopTimer(ID timerID);

    protected:
        /**
         * @brief 初始化定时器服务
         */
        TResult init();

        /**
         * @brief 轮询是否有定时器事件触发
         */
        TResult pollEvents();

    protected:
        ITimerService   *mTimerService;
    };

    #define T3D_TIMER_MGR       TimerManager::getInstance()

    #define T3D_INVALID_TIMER_ID    TimerManager::INVALID_TIMER_ID
}


#endif  /*__T3D_TIMER_MANAGER_H__*/
