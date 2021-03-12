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

#ifndef __T3D_TIEMR_SERVICE_H__
#define __T3D_TIEMR_SERVICE_H__


#include "Adapter/T3DTimerInterface.h"
#include "T3DPlatformErrorDef.h"


namespace Tiny3D
{
    class TimerService : public ITimerService
    {
        T3D_DECLARE_CLASS();

    public:
        /** 构造函数 */
        TimerService();

        /** 析构函数 */
        virtual ~TimerService();

    protected:
        /**
         * @brief 启动定时器
         * @param [in] interval : 时间间隔
         * @param [in] repeat : 是否循环定时器
         * @param [in] listener : 定时器回调对象
         * @return 调用成功返回有效定时器ID，否则返回T3D_INVALID_TIMER_ID
         */
        virtual ID startTimer(uint32_t interval, bool repeat,
            ITimerListener *listener) override;

        /**
         * @brief 停止定时器
         * @param [in] timerID : 有效定时器ID，通过startTimer返回
         * @return 调用成功返回T3D_OK
         */
        virtual TResult stopTimer(ID timerID) override;

        /**
         * @brief 初始化定时器服务
         */
        virtual TResult init() override;

        /**
         * @brief 轮询是否有定时器事件触发
         */
        virtual TResult pollEvents() override;

        /** 线程函数，循环检测是否超时 */
        void update();

        struct Timer
        {
            int64_t         timestamp;  /**< 定时器启动时间戳 */
            int64_t         interval;   /**< 定时器触发间隔 */
            ITimerListener  *listener;  /**< 定时器触发的监听对象 */
            bool            repeat;     /**< 定时器是否循环 */
            bool            alive;      /**< 定时器是否有效 */
        };

        struct TimerEvent
        {
            ID              timerID;    /**< 定时器ID */
            int32_t         dt;         /**< 实际时间间隔 */
            ITimerListener  *listener;  /**< 定时器触发的监听对象 */
        };

        typedef TMap<uint32_t, Timer>       TimerList;
        typedef TimerList::iterator         TimerListItr;
        typedef TimerList::const_iterator   TimerListConstItr;
        typedef TimerList::value_type       TimerValue;

        typedef TList<TimerEvent>               TimerEventQueue;
        typedef TimerEventQueue::iterator       TimerEventQueueItr;
        typedef TimerEventQueue::const_iterator TimerEventQueueConstItr;


        TimerList       mTimerList;         /// 定时器对象列表
        TimerEventQueue mTimerEventQueue;   /// 定时器事件队列
        ID              mTimerID;           /// 当前定时器ID，用于下一个生成的ID

        bool            mIsRunning;         /// 轮询线程是否在运行

        TThread         mPollThread;        /// 轮询线程
        TMutex          mTimerListMutex;    /// 操作定时器对象列表的互斥量
        TRecursiveMutex mEventListMutex;    /// 操作事件队列的互斥量
    };
}


#endif  /*__T3D_TIEMR_SERVICE_H__*/