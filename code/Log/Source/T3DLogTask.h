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

#ifndef __T3D_LOG_TASK_H__
#define __T3D_LOG_TASK_H__


#include "T3DLogPrerequisites.h"


namespace Tiny3D
{
    class LogItem;

    class LogTask
    {
    public:
        enum Type
        {
            E_TYPE_NONE = 0,        /// 没有类型
            E_TYPE_CHECK_EXPIRED,   /// 检查过期日志文件
            E_TYPE_FLUSH_CACHE,     /// 把缓存日志写回文件
            E_TYPE_MAX
        };

        T3D_DECLARE_INTERFACE(LogTask);

        virtual Type getType() const = 0;
    };

    class LogTaskCheckExpired : public LogTask
    {
    public:
        LogTaskCheckExpired(uint32_t unExpired);

        virtual Type getType() const override;

        uint32_t getExpired() const
        {
            return mExpired;
        }

    protected:
        uint32_t mExpired;
    };

    class LogTaskFlushCache : public LogTask
    {
    public:
        LogTaskFlushCache(size_t nCacheSize)
            : mItemCache(nCacheSize)
        {

        }

        virtual Type getType() const override;

        typedef TArray<LogItem *>           ItemCache;
        typedef ItemCache::iterator         ItemCacheItr;
        typedef ItemCache::const_iterator   ItemCacheConstItr;

        ItemCache   mItemCache;
    };
}


#endif  /*__T3D_LOG_TASK_H__*/
