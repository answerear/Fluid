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

#ifndef __T3D_DATE_TIME_H__
#define __T3D_DATE_TIME_H__


#include "T3DPlatformPrerequisites.h"
#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DClass.h"


namespace Tiny3D
{
    class ITime;

    /**
    * @class DateTime
    * @brief 各种时间相关操作的类.
    */
    class T3D_PLATFORM_API DateTime
    {
        T3D_DECLARE_CLASS();

    public:
        enum class TimeFormat : uint32_t
        {
            HH_MM_SS_XXX = 0,        /// 转成字符串格式为：HH:MM:SS.XXX
            HH_MM_SS,
            HH_MM,
            HHMMSS,
        };

        enum class DateFormat : uint32_t
        {
            YY_MM_DD = 0,
            MM_DD,
            YY_MM,
            YYMMDD,
        };

    public:
        /**
        * @brief Default Constructor for QGDateTime.
        */
        DateTime();

        /**
        * @brief Constructor for QGDateTime.
        * @param [in] nYear : 年
        * @param [in] nMonth : 月
        * @param [in] nDay : 日
        * @param [in] nHour : 时
        * @param [in] nMin : 分
        * @param [in] nSecond : 秒
        * @param [in] millisecond : 毫秒
        */
        DateTime(int32_t year, int32_t month, int32_t day, 
            int32_t hour, int32_t minute, int32_t second, int32_t millisecond);

        /**
        * @brief 把QGDateTime中时间转换成从1970年1月1日开始的毫秒数.
        * @return 返回时间毫秒数.
        */
        int64_t toMSecsSinceEpoch() const;

        /**
        * @brief 把QGDataTime中时间转成字符串.
        * @note 字符串格式形如：YYYY-MM-DD HH:MM:SS.XXX
        * @return 返回String对象
        */
        String toString() const;

        /**
        * @brief 把QGDataTime中时间转成字符串.
        * @note 字符串格式形如：HH:MM:SS.XXX
        * @return 返回String对象
        */
        String timeToString(TimeFormat eFormat = TimeFormat::HH_MM_SS_XXX) const;

        /**
        * @brief 把QGDataTime中时间转成字符串.
        * @note 字符串格式形如：YYYY-MM-DD
        * @return 返回String对象
        */
        String dateToString(DateFormat eFormat = DateFormat::YY_MM_DD) const;

        /**
        * @brief 判断时间是否相等
        */
        bool operator ==(const DateTime &other) const;

        /**
        * @brief 判断时间是否相等
        */
        bool operator !=(const DateTime &other) const;

        /**
        * @brief 判断时间是否相等
        */
        bool operator <(const DateTime &other) const;

        /**
        * @brief 判断时间是否相等
        */
        bool operator <=(const DateTime &other) const;

        /**
        * @brief 判断时间是否相等
        */
        bool operator >(const DateTime &other) const;

        /**
        * @brief 判断时间是否相等
        */
        bool operator >=(const DateTime &other) const;

    public:
        /**
        * @brief 静态接口，获取当前时间的QGDateTime对象.
        * @return 返回当前时间的QGDateTime对象.
        */
        static DateTime currentDateTime();

        /**
        * @brief 静态接口，获取当前格林威治时间的QGDateTime对象.
        * @return 返回当前格林威治时间的QGDateTime对象.
        */
        static DateTime currentDateTimeUTC();

        /**
        * @brief 静态接口，获取从1970年1月1日到现在的时间秒数
        * @return 返回时间秒数
        */
        static int64_t currentSecsSinceEpoch();

        /**
        * @brief 静态接口，获取从1970年1月1日到现在的时间毫秒数.
        * @return 返回时间毫秒数.
        */
        static int64_t currentMSecsSinceEpoch();

        /**
        * @brief 静态接口，把从1970年1月1日开始的毫秒数转换成QGDateTime对象.
        * @param [in] msecs : 从1970年1月1日开始的毫秒数
        * @return 返回QGDateTime对象.
        */
        static DateTime fromMSecsSinceEpoch(int64_t msecs);

        /**
        * @brief 静态接口，把从1970年1月1日开始的秒数转换成QGDateTime对象.
        * @param [in] msecs : 从1970年1月1日开始的秒数
        * @return 返回QGDateTime对象.
        */
        static DateTime fromSecsSinceEpoch(int64_t sces);

    public:
        /** 返回年 */
        int32_t Year() const { return mYear; }
        /** 返回月 */
        int32_t Month() const { return mMonth; }
        /** 返回日 */
        int32_t Day() const { return mDay; }
        /** 返回时 */
        int32_t Hour() const { return mHour; }
        /** 返回分 */
        int32_t Minute() const { return mMinute; }
        /** 返回秒 */
        int32_t Second() const { return mSecond; }
        /** 返回毫秒 */
        int32_t Millisecond() const { return mMillisecond; }

    private:
        static ITime *getTime();

        int32_t mYear;
        int32_t mMonth;
        int32_t mDay;
        int32_t mHour;
        int32_t mMinute;
        int32_t mSecond;
        int32_t mMillisecond;

        static ITime    *mTime;
    };
}


#endif  /*__T3D_DATE_TIME_H__*/
