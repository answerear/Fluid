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

#ifndef __T3D_LOG_ITEM_H__
#define __T3D_LOG_ITEM_H__


#include "T3DLogPrerequisites.h"
#include "T3DLogger.h"
#include <sstream>


namespace Tiny3D
{
    class LogItem
    {
        friend class Logger;

    public:
        LogItem(Logger::Level level, const char *filename, int32_t line, 
            const char *tag, const char *content)
        {
            DateTime dt = DateTime::currentDateTime();
            mHour = dt.Hour();
            formatContent(dt, filename, line, level, tag, content);
        }

        void outputFile(FileDataStream &fs) const
        {
            // 日志格式
            // YYYY-MM-DD HH:MM:SS.XXX|Level|ThreadID|FineName|Line|Content
            fs.write((void *)mContent, mContentSize);
        }

        void outputConsole() const
        {
            T3D_CONSOLE.print(mContent);
        }

        uint32_t getContentSize() const    { return mContentSize; }

        int32_t getHour() const    { return mHour; }

    protected:
        uint32_t formatContent(const DateTime &dt, const char *filename, 
            int32_t line, Logger::Level level, const char *tag, 
            const char *content)
        {
            std::thread::id threadID = std::this_thread::get_id();
            String strDateTime = dt.toString();
            std::stringstream ss;
            ss << strDateTime
                << "|" << level 
                << "|" << threadID
                << "|" << filename
                << "|" << line
                << "|" << tag
                << "|" << content
                <<"\n";
            mContentSize = (uint32_t)ss.str().length();
            mContentSize = (uint32_t)(mContentSize > sizeof(mContent) - 1 
                ? sizeof(mContent) - 1 : ss.str().length());
            memcpy(mContent, ss.str().c_str(), mContentSize);
            mContent[mContentSize] = 0;
            return mContentSize;
        }

    private:
        uint32_t        mContentSize;
        int32_t         mHour;
        char            mContent[2048];
    };
}


#endif  /*__T3D_LOG_ITEM_H__*/
