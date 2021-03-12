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

#ifndef __T3D_EVENT_MANAGER_H__
#define __T3D_EVENT_MANAGER_H__


#include "T3DEventPrerequisites.h"


namespace Tiny3D
{

    class T3D_FRAMEWORK_API EventManager : public Singleton<EventManager>
    {
        friend class EventHandler;

        T3D_DISABLE_COPY(EventManager);
        T3D_DECLARE_CLASS();

        /** 事件项 */
        struct EventItem
        {
            EventItem(EventID evid, EventParam *param,
                TINSTANCE receiver, TINSTANCE sender)
                : mEventID(evid)
                , mEventParam(param)
                , mReceiver(receiver)
                , mSender(sender)
            {}

            EventID         mEventID;       /// 事件ID
            EventParam      *mEventParam;   /// 事件参数对象
            TINSTANCE       mReceiver;      /// 事件接收者实例句柄
            TINSTANCE       mSender;        /// 事件发送者实例句柄
        };

    public:
        static const TINSTANCE INVALID_INSTANCE;    /// 无效实例句柄
        static const TINSTANCE BROADCAST_INSTANCE;  /// 全局广播实例句柄
        static const TINSTANCE MULTICAST_INSTANCE;  /// 面向事件多播实例句柄

        enum
        {
            MAX_EVENT_QUEUE = 2,            /// 最大事件队列数
            MAX_HANDLING_DURATION = 30,     /// 默认最大处理时间，30ms
            MAX_CALLSTACK_LEVEL = 10,       /// 最大事件嵌套调用栈层级，10层
        };

        /**
         * @brief 因为时间过长被中断后续未处理事件的处理方式，对于栈太深的情况，
         *      直接丢弃了
         */
        enum HandleEventMode
        {
            HEM_DISCARD = 0,    /// 处理不完倍打断后直接丢弃
            HEM_QUEUE,          /// 处理不完的放队列下次继续
        };

        /** 
         * @brief Constructor 
         * @param [in] maxEvents : 所有事件的数量
         * @param [in] maxHandlingDuration : 处理事件的最长事件
         * @param [in] maxCallStacks : 能嵌套处理事件调用栈的最大深度
         * @param [in] mode : 碰到事件无法处理完成时的处理方式，默认丢弃全部
         * @see
         *  - getMaxHandlingDuration()
         *  - getMaxCallStackLevel()
         */
        EventManager(uint32_t maxEvents, 
            int32_t maxHandlingDuration = MAX_HANDLING_DURATION,
            int32_t maxCallStacks = MAX_CALLSTACK_LEVEL, 
            HandleEventMode mode = HEM_DISCARD);

        /** Destructor */
        virtual ~EventManager();

        /**
         * @brief 发送同步事件，事件处理函数处理返回前，sendEvent是不会返回的。
         * @param [in] evid : 事件ID
         * @param [in] param : 事件附加参数
         * @param [in] receiver : 事件接收者实例。
         * @param [in] sender : 事件发送者实例
         * @return 
         *  - T3D_OK : 调用成功返回
         *  - T3D_ERR_FWK_INVALID_RECVER : 无效的接收者实例句柄。
         *  - T3D_ERR_FWK_INVALID_SENDER : 无效的发送者实例句柄。
         *  - T3D_ERR_FWK_HANDLING_TIMEOVER : 当receiver是T3D_BROADCAST_INSTANCE
         *      如果中间某个事件处理函数处理时间太长或者数量太多导致整体时间超出
         *      了通过getMaxHandlingDuration()返回的时间，则返回该值。
         *  - T3D_ERR_FWK_CALLSTACK_OVERFLOW : 当嵌套调用sendEvent多次后，导致
         *      调用栈超过通过getMaxCallStackLevel()获得的最大层次后则返回该值。
         *  - T3D_ERR_FWK_INVALID_EVID : 错误事件ID
         *  - 其他错误是事件处理函数内部返回的，需要具体事件来解析
         * @see
         *  - getMaxCallStackLevel()
         *  - getMaxHandlingDuration()
         */
        TResult sendEvent(EventID evid, EventParam *param,
            TINSTANCE receiver, TINSTANCE sender);

        /**
         * @brief 发送异步事件，事件处理函数会再后面统一派发，这里不会触发。
         * @param [in] evid : 事件ID
         * @param [in] param : 事件附加参数
         * @param [in] receiver : 事件接收者实例
         * @param [in] sender : 事件发送者实例
         * @return 
         *  - T3D_OK : 只要事件ID没错误，都返回该值
         *  - T3D_ERR_INVALID_EVID : 无效事件ID
         * @note 需要注意一点就是调用返回T3D_OK也不代表接收者一定能接收到。
         *      因为这个接口是把所有事件存放到事件队列，然后在dispatchEvent()
         *      调用的地方统一派发，但是如果事件队列事件太多导致处理时间太长，
         *      或者某一个事件影响处理时间太长影响到整个队列处理时间，则后续的
         *      事件会被丢弃或者下一次调用dispatchEvent()接口再次派发。 详细的派
         *      发事件整体时间可以通过调用getMaxHandlingDuration()接口查询获得。
         *      对于被中断的处理，会根据构造函数传入的flags来决定后续事件的处理
         *      方式。 
         * @see
         *  - getMaxHandlingDuration()
         *  - getHandlingEventMode()
         */
        TResult postEvent(EventID evid, EventParam *param,
            TINSTANCE receiver, TINSTANCE sender);

        /**
         * @brief 通过传入instance实例句柄获取回对象指针。
         * @param [in] instance : 对象实例句柄
         * @param [in][out] handler : 返回的对象指针
         * @return instance是有效合法句柄返回true，否则返回false。
         */
        bool getEventHandler(TINSTANCE instance, EventHandler *&handler);

        /**
         * @brief 判断传入的事件对象指针是否有效收发事件实例。
         * @param [in] handler : 事件处理对象指针
         * @return 有效收发事件实例则返回true，否则返回false。
         */
        bool isValidHandler(EventHandler *handler);

        /**
         * @brief 派发事件，用于派发事件队列里面的事件
         * @return 
         *  - T3D_OK : 当事件全部派发完或者没有事件要派发时返回本值
         *  - T3D_ERR_FWK_HANDLING_TIMEOVER : 事件处理时间过长返回本值
         *  - T3D_ERR_FWK_CALLSTACK_OVERFLOW : 事件嵌套栈溢出返回本值
         * @see
         *  - getMaxHandlingDuration()
         *  - getMaxCallStackLevel()
         */
        TResult dispatchEvent();

        /**
         * @brief 暂停事件派发
         * @note 在暂停派发期间，任何sendEvent和postEvent调用都会让所有事件排队，
         *  即不管sendEvent还是postEvent都会被当成postEvent处理。 
         * @see
         *  - resumeDispatching();
         */
        void pauseDispatching();

        /**
         * @brief 继续事件派发
         * @param [in] dispatchImmdiately : 是否马上派发队列里所有事件
         * @return
         *  - T3D_OK : 当dispatchImmdiately是false的时候，一定返回本值；当
         *              dispatchImmdiately是true的时候，只有所有堆积的事件都派发
         *              完了，才返回本值
         *  - T3D_ERR_FWK_HANDLING_TIMEOVER : 当dispatchImmdiately是true的时候，
         *              事件处理时间过长返回本值。
         *  - T3D_ERR_FWK_CALLSTACK_OVERFLOW : 当dispatchImmdiately是true的时候，
         *              事件嵌套栈溢出返回本值。
         * @note 当dispatchImmdiately为true的时候，会马上派发事件，但是如果事件
         *  处理事件太长，超过了getMaxHandlingDuration()返回值，则会直接中断派发
         *  并且返回false。 同样的，如果嵌套事件处理调用栈超过了
         *  getMaxCallStackLevel()返回值，也会中断处理返回
         * @see
         *  - pauseDispatching()
         *  - getMaxHandlingDuration()
         *  - getMaxCallStackLevel()
         */
        TResult resumeDispatching(bool dispatchImmdiately);

        /**
         * @brief 事件派发是否被暂停
         */
        bool isPaused() { return mIsDispatchPaused; }

        /**
         * @brief 获取当前处理事件时间的限制。
         */
        int32_t getMaxHandlingDuration() { return mMaxHandlingDuration; }

        /**
         * @brief 获取当前处理事件嵌套的调用栈层次深度。
         */
        int32_t getMaxCallStackLevel() { return mMaxCallStackLevel; }

        /**
         * @brief 获取当前待超时没有处理完后续事件处理模式
         */
        HandleEventMode getHandlingEventMode() { return mHandlingMode; }

    protected:
        /**
         * @brief 注册事件处理对象
         * @param [in] handler : 需要收发事件处理对象
         * @return 注册成功返回事件实例句柄，否则返回T3D_INVALID_INSTANCE。
         * @note 只有调用了本接口才能收发事件。
         * @see
         *  - unregisterHandler()
         */
        TINSTANCE registerHandler(EventHandler *handler);

        /**
         * @brief 反注册事件处理对象
         * @param [in] instance : 实例句柄
         * @return
         *  - T3D_OK : 反注册成功返回本值
         *  - T3D_ERR_FWK_INVALID_INSTANCE : 无效实例句柄
         */
        TResult unregisterHandler(TINSTANCE instance);

        /**
        * @brief 注册事件
        * @note 注册事件后，可以只接收到关注的事件，不关注的事件无法接收到
        * @param [in] evid : 事件ID
        * @param [in] instance : 关注该事件ID的实例句柄
        * @return
        *   - T3D_OK : 注册成功返回该值
        *   - T3D_ERR_FWK_INVALID_EVID : 无效的事件ID返回该值
        *   - T3D_ERR_FWK_DUPLICATE_INSTANCE : 该instance已经注册过了返回该值
        *   - T3D_INVALID_INSTANCE : 无效实例句柄返回该值
        */
        TResult registerEvent(EventID evid, TINSTANCE instance);

        /**
        * @brief 反注册事件
        * @note 反注册事件后，事件处理对象无法收到该事件
        * @param [in] evid : 事件ID
        * @param [in] instance : 关注该事件ID的处理对象
        * @return
        *   - T3D_OK : 反注册成功返回该值
        *   - T3D_ERR_FWK_INVALID_EVID : 无效的事件ID返回该值
        *   - T3D_INVALID_INSTANCE : 无效实例句柄返回该值
        */
        TResult unregisterEvent(EventID evid, TINSTANCE instance);

        /**
        * @brief 清除所有事件队列中的事件.
        * @return void
        */
        void clearEventQueue();

    private:
        /**
         * @brief 广播事件
         */
        TResult broadcastEvent(EventID evid, EventParam *param,
            TINSTANCE sender);

        /**
         * @brief 多播事件
         */
        TResult multicastEvent(EventID evid, EventParam *param,
            TINSTANCE sender);

        /**
         * @brief 单播事件
         */
        TResult singlecastEvent(EventID evid, EventParam *param,
            TINSTANCE receiver, TINSTANCE sender);

        TResult pushBroadcastEvent(EventID evid, EventParam *param,
            TINSTANCE sender);

        TResult pushMulticastEvent(EventID evid, EventParam *param,
            TINSTANCE sender);

        TResult pushSinglecastEvent(EventID evid, EventParam *param,
            TINSTANCE receiver, TINSTANCE sender);

    private:
        typedef TArray<EventHandler*>       HandlerList;
        typedef HandlerList::iterator       HandlerListItr;
        typedef HandlerList::const_iterator HandlerListConstItr;

        typedef TList<EventItem>            EventList;
        typedef EventList::iterator         EventListItr;
        typedef EventList::const_iterator   EventListConstItr;

        typedef TSet<TINSTANCE>             EventInstSet;
        typedef EventInstSet::iterator      EventInstSetItr;
        typedef EventInstSet::value_type	EventInstSetValue;

        typedef TArray<EventInstSet>        EventFilterList;
        typedef EventFilterList::iterator   EventFilterListItr;

        HandlerList	mEventHandlers;                 /// 事件处理对象链表
        EventList   mEventQueue[MAX_EVENT_QUEUE];   /// 待处理事件队列

        EventFilterList	mEventFilters;              /// 事件过滤表

        int32_t         mCurrentQueue;              /// 当前待处理事件队列
        uint32_t        mMaxHandlingDuration;       /// 处理事件持续最大时间
        int64_t         mStartHandleTime;           /// 开始处理事件时间
        uint32_t        mMaxCallStackLevel;         /// 处理事件嵌套调用栈层级
        uint32_t        mCurrentCallStack;          /// 当前栈深度

        HandleEventMode mHandlingMode;              /// 被打断后续事件处理方式

        bool            mIsDispatchPaused;          /// 暂停派发事件标识
        EventList       mEventCache;                /// 暂存事件缓存
    };

    #define T3D_EVENT_MGR   (EventManager::getInstance())
}


#endif  /*__T3D_EVENT_MANAGER_H__*/
