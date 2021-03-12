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


#include "T3DEventManager.h"
#include "T3DEventMacro.h"
#include "T3DEventErrorDef.h"
#include "T3DEventInstance.h"
#include "T3DEventHandler.h"
#include "T3DEventParam.h"

namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(EventManager);
    T3D_IMPLEMENT_CLASS_0(EventManager);

    //--------------------------------------------------------------------------

    const TINSTANCE EventManager::INVALID_INSTANCE = nullptr;
    const TINSTANCE EventManager::BROADCAST_INSTANCE = (const TINSTANCE)-1;
    const TINSTANCE EventManager::MULTICAST_INSTANCE = (const TINSTANCE)1;

    //--------------------------------------------------------------------------

    EventManager::EventManager(uint32_t maxEvents, int32_t maxHandlingDuration,
        int32_t maxCallStacks, HandleEventMode mode)
        : mCurrentQueue(0)
		, mMaxHandlingDuration(maxHandlingDuration)
        , mStartHandleTime(0)
        , mMaxCallStackLevel(maxCallStacks)
        , mCurrentCallStack(0)
        , mHandlingMode(mode)
        , mIsDispatchPaused(false)
    {
        mEventHandlers.reserve(128);
        mEventHandlers.resize(128);

        mEventFilters.reserve(maxEvents);
        mEventFilters.resize(maxEvents);
    }

    EventManager::~EventManager()
    {
        mEventHandlers.clear();
        clearEventQueue();
    }

    //--------------------------------------------------------------------------

    TResult EventManager::sendEvent(EventID evid, EventParam *param,
        TINSTANCE receiver, TINSTANCE sender)
    {
        TResult ret = T3D_OK;

        do
        {
            if (evid >= mEventFilters.size())
            {
                // 无效事件ID
                ret = T3D_ERR_FWK_INVALID_EVID;
                break;
            }

            if (T3D_INVALID_INSTANCE == receiver)
            {
                // 无效接收者
                ret = T3D_ERR_FWK_INVALID_RECVER;
                break;
            }

            if (T3D_INVALID_INSTANCE == sender)
            {
                // 无效发送者
                ret = T3D_ERR_FWK_INVALID_SENDER;
                break;
            }

            if (T3D_BROADCAST_INSTANCE == receiver)
            {
                // 广播
                ret = broadcastEvent(evid, param, sender);
            }
            else if (T3D_MULTICAST_INSTANCE == receiver)
            {
                // 多播
                ret = multicastEvent(evid, param, sender);
            }
            else
            {
                // 单播
                ret = singlecastEvent(evid, param, receiver, sender);
            }

        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult EventManager::broadcastEvent(EventID evid, EventParam *param,
        TINSTANCE sender)
    {
        TResult ret = T3D_ERR_FWK_NONE_HANDLER;

        if (mIsDispatchPaused)
        {
            // 被暂停了派发了，只能全部cache起来，留到恢复再派发
            auto itr = mEventHandlers.begin();

            while (itr != mEventHandlers.end())
            {
                TINSTANCE receiver = (*itr)->getInstance();
                EventItem item(evid, param->clone(), receiver, sender);
                mEventCache.push_back(item);
                ret = T3D_ERR_FWK_SUSPENDED;
                ++itr;
            }
        }
        else
        {
            mCurrentCallStack++;

            do 
            {
                if (mCurrentCallStack > mMaxCallStackLevel)
                {
                    // 栈太深了，不处理后续的事件了
                    ret = T3D_ERR_FWK_CALLSTACK_OVERFLOW;
                    break;
                }

                // 直接广播给全局所有注册的对象
                auto itr = mEventHandlers.begin();

                while (itr != mEventHandlers.end())
                {
                    EventHandler *handler = *itr;
                    // 没有暂停，那全部给派发吧
                    handler->processEvent(evid, param, sender);
                    ret = T3D_OK;
                    ++itr;
                }
            } while (0);

            mCurrentCallStack--;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult EventManager::multicastEvent(EventID evid, EventParam *param,
        TINSTANCE sender)
    {
        TResult ret = T3D_ERR_FWK_NONE_HANDLER;

        if (mIsDispatchPaused)
        {
            // 被暂停了派发，只能全部cache起来，留到恢复再派发
            const EventInstSet &instSet = mEventFilters[evid];
            auto itr = instSet.begin();

            while (itr != instSet.end())
            {
                TINSTANCE receiver = *itr;
                EventHandler *handler = nullptr;

                // 这里通过getEventHandler调用是为了找到合法的对象
                if (getEventHandler(receiver, handler))
                {
                    EventItem item(evid, param->clone(), receiver, sender);
                    mEventCache.push_back(item);
                    ret = T3D_ERR_FWK_SUSPENDED;
                }

                ++itr;
            }
        }
        else
        {
            mCurrentCallStack++;

            do 
            {
                if (mCurrentCallStack > mMaxCallStackLevel)
                {
                    ret = T3D_ERR_FWK_CALLSTACK_OVERFLOW;
                    break;
                }

                // 找到广播给关注事件的对象
                const EventInstSet &instSet = mEventFilters[evid];
                auto itr = instSet.begin();

                while (itr != instSet.end())
                {
                    TINSTANCE receiver = *itr;
                    EventHandler *handler = nullptr;

                    // 这里通过getEventHandler调用是为了找到合法的对象
                    if (getEventHandler(receiver, handler))
                    {
                        handler->processEvent(evid, param, sender);
                        ret = T3D_OK;
                    }

                    ++itr;
                }
            } while (0);

            mCurrentCallStack--;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult EventManager::singlecastEvent(EventID evid, EventParam *param,
        TINSTANCE receiver, TINSTANCE sender)
    {
        TResult ret = T3D_ERR_FWK_NONE_HANDLER;

        if (mIsDispatchPaused)
        {
            EventItem item(evid, param->clone(), receiver, sender);
            mEventCache.push_back(item);
            ret = T3D_ERR_FWK_SUSPENDED;
        }
        else
        {
            mCurrentCallStack++;

            do 
            {
                if (mCurrentCallStack > mMaxCallStackLevel)
                {
                    ret = T3D_ERR_FWK_CALLSTACK_OVERFLOW;
                    break;
                }

                // 找到对应对象，只给指定对象发送事件
                EventHandler *handler = nullptr;
                if (getEventHandler(receiver, handler))
                {
                    ret = handler->processEvent(evid, param, sender);
                }
            } while (0);

            mCurrentCallStack--;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult EventManager::postEvent(EventID evid, EventParam *param,
        TINSTANCE receiver, TINSTANCE sender)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (evid >= mEventFilters.size())
            {
                // 无效事件ID
                ret = T3D_ERR_FWK_INVALID_EVID;
                break;
            }

            if (T3D_INVALID_INSTANCE == receiver)
            {
                // 无效接收者
                ret = T3D_ERR_FWK_INVALID_RECVER;
                break;
            }

            if (T3D_INVALID_INSTANCE == sender)
            {
                // 无效发送者
                ret = T3D_ERR_FWK_INVALID_SENDER;
                break;
            }

            if (T3D_BROADCAST_INSTANCE == receiver)
            {
                // 广播
                ret = pushBroadcastEvent(evid, param, sender);
            }
            else if (T3D_MULTICAST_INSTANCE == receiver)
            {
                // 多播
                ret = pushMulticastEvent(evid, param, sender);
            }
            else
            {
                // 单播
                ret = pushSinglecastEvent(evid, param, receiver, sender);
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult EventManager::pushBroadcastEvent(EventID evid, EventParam *param,
        TINSTANCE sender)
    {
        TResult ret = T3D_ERR_FWK_NONE_HANDLER;

        if (mIsDispatchPaused)
        {
            auto itr = mEventHandlers.begin();

            while (itr != mEventHandlers.end())
            {
                EventHandler *handler = *itr;
                EventParam *para = param->clone();
                EventItem item(evid, para, handler->getInstance(), sender);
                mEventCache.push_back(item);
                ret = T3D_ERR_FWK_SUSPENDED;
                ++itr;
            }
        }
        else
        {
            auto itr = mEventHandlers.begin();

            while (itr != mEventHandlers.end())
            {
                EventHandler *handler = *itr;
                EventParam *para = param->clone();
                EventItem item(evid, para, handler->getInstance(), sender);
                mEventQueue[mCurrentQueue].push_back(item);
                ret = T3D_OK;
                ++itr;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult EventManager::pushMulticastEvent(EventID evid, EventParam *param,
        TINSTANCE sender)
    {
        TResult ret = T3D_ERR_FWK_NONE_HANDLER;

        if (mIsDispatchPaused)
        {
            const EventInstSet &instSet = mEventFilters[evid];
            auto itr = instSet.begin();

            while (itr != instSet.end())
            {
                TINSTANCE recv = *itr;
                EventParam *para = param->clone();
                EventItem item(evid, para, recv, sender);
                mEventCache.push_back(item);
                ret = T3D_ERR_FWK_SUSPENDED;
                ++itr;
            }
        }
        else
        {
            const EventInstSet &instSet = mEventFilters[evid];
            auto itr = instSet.begin();

            while (itr != instSet.end())
            {
                TINSTANCE recv = *itr;
                EventParam *para = param->clone();
                EventItem item(evid, para, recv, sender);
                mEventQueue[mCurrentQueue].push_back(item);
                ret = T3D_OK;
                ++itr;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult EventManager::pushSinglecastEvent(EventID evid, EventParam *param,
        TINSTANCE receiver, TINSTANCE sender)
    {
        TResult ret = T3D_OK;

        if (mIsDispatchPaused)
        {
            EventParam *para = param->clone();
            EventItem item(evid, para, receiver, sender);
            mEventCache.push_back(item);
            ret = T3D_ERR_FWK_SUSPENDED;
        }
        else
        {
            EventParam *para = param->clone();
            EventItem item(evid, para, receiver, sender);
            mEventQueue[mCurrentQueue].push_back(item);
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool EventManager::getEventHandler(TINSTANCE instance, 
        EventHandler *&handler)
    {
        if (instance == T3D_INVALID_INSTANCE)
            return false;

        bool ret = false;
        void *obj = instance->obj;

        if (instance->slot >= 0)
        {
            size_t idx = instance->slot;
            if (idx < mEventHandlers.size()
                && mEventHandlers[idx] != nullptr
                && mEventHandlers[idx] == (EventHandler *)obj)
            {
                handler = (EventHandler *)obj;
                ret = true;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool EventManager::isValidHandler(EventHandler *handler)
    {
        if (nullptr == handler)
            return false;

        bool ret = false;
        TINSTANCE instance = handler->getInstance();
        void *obj = instance->obj;

        if (instance->slot >= 0)
        {
            size_t idx = instance->slot;
            if (idx < mEventHandlers.size()
                && mEventHandlers[idx] != nullptr
                && mEventHandlers[idx] == (EventHandler *)obj)
            {
                ret = true;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult EventManager::dispatchEvent()
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mIsDispatchPaused)
                break;

            int32_t index = mCurrentQueue;
            mCurrentQueue = (++mCurrentQueue) % MAX_EVENT_QUEUE;

            if (mEventQueue[index].empty())
                break;

            while (!mEventQueue[index].empty())
            {
                const EventItem &item = mEventQueue[index].front();

                mCurrentCallStack++;
                if (mCurrentCallStack > mMaxCallStackLevel)
                {
                    ret = T3D_ERR_FWK_CALLSTACK_OVERFLOW;
                    break;
                }

                if (ret != T3D_ERR_FWK_CALLSTACK_OVERFLOW)
                {
                    EventHandler *handler = nullptr;
                    if (getEventHandler(item.mReceiver, handler))
                    {
                        handler->processEvent(item.mEventID, item.mEventParam,
                            item.mSender);
                    }
                    mCurrentCallStack--;
                }                

                delete item.mEventParam;
                mEventQueue[index].pop_front();
            }

        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void EventManager::pauseDispatching()
    {
        mIsDispatchPaused = true;
    }

    //--------------------------------------------------------------------------

    TResult EventManager::resumeDispatching(bool dispatchImmdiately)
    {
        TResult ret = T3D_OK;

        mIsDispatchPaused = false;

        if (dispatchImmdiately)
        {
            // 马上派发缓存中的所有事件
            auto itr = mEventCache.begin();

            while (itr != mEventCache.end())
            {
                mCurrentCallStack++;

                if (mCurrentCallStack > mMaxCallStackLevel)
                {
                    ret = T3D_ERR_FWK_CALLSTACK_OVERFLOW;
                    break;
                }

                if (ret != T3D_ERR_FWK_CALLSTACK_OVERFLOW)
                {
                    EventHandler *handler = nullptr;

                    if (getEventHandler(itr->mReceiver, handler))
                    {
                        handler->processEvent(itr->mEventID, itr->mEventParam,
                            itr->mSender);
                    }

                    mCurrentCallStack--;
                }

                delete itr->mEventParam;
                ++itr;
            }

            mEventCache.clear();
        }
        else
        {
            // 不马上派发，重新放回事件队列里
            auto itr = mEventCache.begin();

            while (itr != mEventCache.end())
            {
                const EventItem &item = *itr;
                mEventQueue[mCurrentQueue].push_back(item);
                ++itr;
            }

            mEventCache.clear();
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TINSTANCE EventManager::registerHandler(EventHandler *handler)
    {
        bool found = false;
        size_t slot = 0;
        auto itr = mEventHandlers.begin();

        // 查找一个空闲的slot
        while (itr != mEventHandlers.end())
        {
            if (nullptr == *itr)
            {
                mEventHandlers[slot] = handler;
                found = true;
                break;
            }

            ++itr;
            ++slot;
        }

        if (!found)
        {
            // 没有空闲的slot，只能扩展一个
            slot = mEventHandlers.size();
            mEventHandlers.push_back(handler);
        }

        return new _TINSTANCE(handler, (int32_t)slot);
    }

    //--------------------------------------------------------------------------

    TResult EventManager::unregisterHandler(TINSTANCE instance)
    {
        TResult ret = T3D_ERR_FWK_INVALID_INSTANCE;

        do 
        {
            if (T3D_INVALID_INSTANCE == instance)
            {
                ret = T3D_ERR_FWK_INVALID_INSTANCE;
                break;
            }

            int32_t idx = instance->slot;
            void *obj = instance->obj;
            if (mEventHandlers[idx] == (EventHandler *)obj)
            {
                mEventHandlers[idx] = nullptr;
                ret = T3D_OK;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult EventManager::registerEvent(EventID evid, TINSTANCE instance)
    {
        TResult ret = T3D_ERR_FWK_INVALID_INSTANCE;

        do 
        {
            if (evid >= mEventFilters.size())
            {
                ret = T3D_ERR_FWK_INVALID_EVID;
                break;
            }

            if (T3D_INVALID_INSTANCE == instance)
            {
                ret = T3D_ERR_FWK_INVALID_INSTANCE;
                break;
            }

            EventInstSet &instSet = mEventFilters[evid];
            std::pair<EventInstSetItr, bool> r = instSet.insert(instance);
            if (r.second)
            {
                ret = T3D_OK;
            }
            else
            {
                ret = T3D_ERR_FWK_DUPLICATE_INSTANCE;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult EventManager::unregisterEvent(EventID evid, TINSTANCE instance)
    {
        TResult ret = T3D_ERR_FWK_INVALID_INSTANCE;

        do 
        {
            if (evid >= mEventFilters.size())
            {
                ret = T3D_ERR_FWK_INVALID_EVID;
                break;
            }

            if (T3D_INVALID_INSTANCE == instance)
            {
                ret = T3D_ERR_FWK_INVALID_INSTANCE;
                break;
            }

            EventInstSet &instSet = mEventFilters[evid];
            instSet.erase(instance);
            ret = T3D_OK;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void EventManager::clearEventQueue()
    {
        int32_t i = 0;

        for (i = 0; i < MAX_EVENT_QUEUE; ++i)
        {
            EventListItr itr = mEventQueue[i].begin();
            while (itr != mEventQueue[i].end())
            {
                EventItem &item = *itr;
                delete item.mEventParam;
                ++itr;
            }

            mEventQueue[i].clear();
        }
    }
}
