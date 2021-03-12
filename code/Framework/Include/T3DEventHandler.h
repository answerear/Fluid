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

#ifndef __T3D_EVENT_HANDLER_H__
#define __T3D_EVENT_HANDLER_H__


#include "T3DEventPrerequisites.h"


namespace Tiny3D
{
    class T3D_FRAMEWORK_API EventHandler
    {
        friend class EventManager;

        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief Constructor
         * @param [in] canAutoRegister : 是否自动注册启动事件收发功能
         */
        EventHandler(bool canAutoRegister = true);

        /**
         * @brief Destructor
         */
        virtual ~EventHandler();

        /**
         * @brief 发送同步事件给指定对象
         */
        TResult sendEvent(EventID evid, EventParam *param, TINSTANCE receiver);

        /**
         * @brief 发送异步事件给指定对象
         */
        TResult postEvent(EventID evid, EventParam *param, TINSTANCE receiver);

        /**
         * @brief 发送同步事件给关注事件的对象
         */
        TResult sendEvent(EventID evid, EventParam *param);

        /**
         * @brief 发送异步事件给关注事件的对象
         */
        TResult postEvent(EventID evid, EventParam *param);

        /**
         * @brief 获取实例句柄
         */
        TINSTANCE getInstance() const { return mInstance; }

        /**
        * @brief 统一处理事件函数
        * @param [in] evid : 事件ID
        * @param [in] param : 事件附加参数对象
        * @param [in] sender : 事件发送实例句柄
        * @return 有处理事件返回true，否则返回false。
        */
        virtual TResult processEvent(EventID evid, EventParam *param,
            TINSTANCE sender);

    protected:
        /**
         * @brief 注册对象，返回实例句柄，只有注册才能有效收发事件
         */
        TINSTANCE registerHandler();

        /**
         * @brief 反注册对象，调用后无法再继续收发事件
         */
        TResult unregisterHandler();

        /**
         * @brief 建立事件过滤器，只有在过滤器里面的才会收到不定对象的事件通知
         */
        TResult setupEventFilter();

        /**
         * @brief 注册关注的事件到过滤器里面
         * @param [in] evid : 事件ID 
         */
        TResult registerEvent(EventID evid);

        /**
         * @brief 反注册关注的事件，反注册后，过滤器里面没有该事件
         * @param [in] evid : 事件ID
         */
        TResult unregisterEvent(EventID evid);

        /**
         * @brief 反注册所有关注的事件
         */
        void unregisterAllEvent();

    private:
        typedef TList<uint32_t>             EventList;
        typedef EventList::iterator         EventListItr;
        typedef EventList::const_iterator   EventListConstItr;

        TINSTANCE   mInstance;      /// 实例句柄

        EventList   mEventList;     /// 本实例关注的事件列表
    };
}


#endif  /*__T3D_EVENT_HANDLER_H__*/
