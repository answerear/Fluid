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

#ifndef __T3D_FIX64_H__
#define __T3D_FIX64_H__

#include "T3DUtilsPrerequisites.h"
#include "T3DFix32.h"

namespace Tiny3D
{
    /**
     * @brief 64位定点数类
     * @remarks 64位定点数构成是用高40位作为整数部分，低24位用来做小数部分
     */
    class T3D_UTILS_API fix64
    {
    public:
        static const int32_t INTEGER_BITS;      // 整数位数
        static const int32_t DECIMAL_BITS;      // 小数位数

        static const int64_t MAX_INT_VALUE;     // 最大的整型数
        static const int64_t MIN_INT_VALUE;     // 最小的整型数

        static const float32_t MAX_FLOAT_VALUE; // 最大的浮点数
        static const float32_t MIN_FLOAT_VALUE; // 最小的浮点数

        static const fix64 ZERO;        // fix64(0.0f)
        static const fix64 HALF;        // fix64(0.5f)
        static const fix64 ONE;         // fix64(1.0f)
        static const fix64 MINUS_ONE;   // fix64(-1.0f)
        static const fix64 INF;         // fix64(Infinity)
        static const fix64 MINUSINF;    // fix64(-Infinity)
        static const fix64 EPSILON;     // fix64(16, 0);

        /// 默认构造函数
        fix64();
        /// 用32位定点数构造64位定点数
        fix64(const fix32 &fx);
        /// 单精度浮点数参数的构造函数
        fix64(float32_t value);
        /// 双精度浮点数参数的构造函数
        fix64(float64_t value);
        /// 用32位整数构造定点数，32位分配：20.12
        fix64(int32_t value);
        /// 用64位整数构造定点数，64位分配：40.24
        fix64(int64_t value);
        /// 用64位整数直接赋值定点数来构造
        fix64(int64_t value, int32_t r);
        /// 拷贝构造函数
        fix64(const fix64 &value);
        
        /// 获取定点数的整型值
        int64_t mantissa() const;
        /// 获取定点数的整型值
        int64_t &mantissa();

        /// 重载取正数操作符
        fix64 operator +() const;
        /// 重载取反操作符
        fix64 operator -() const;

        /// fix64和fix64之间的运算符重载
        fix64 &operator =(const fix64 &value);

        fix64 &operator +=(const fix64 &value);
        fix64 &operator -=(const fix64 &value);
        fix64 &operator *=(const fix64 &value);
        fix64 &operator /=(const fix64 &value);

        friend fix64 operator +(const fix64 &fx, const fix64 &gx);
        friend fix64 operator -(const fix64 &fx, const fix64 &gx);
        friend fix64 operator *(const fix64 &fx, const fix64 &gx);
        friend fix64 operator /(const fix64 &fx, const fix64 &gx);

        friend bool operator ==(const fix64 &fx, const fix64 &gx);
        friend bool operator !=(const fix64 &fx, const fix64 &gx);
        friend bool operator >=(const fix64 &fx, const fix64 &gx);
        friend bool operator <=(const fix64 &fx, const fix64 &gx);
        friend bool operator >(const fix64 &fx, const fix64 &gx);
        friend bool operator <(const fix64 &fx, const fix64 &gx);

        /// fix64和int32_t之间的运算符重载
        fix64 &operator =(int32_t value);

        fix64 &operator +=(int32_t value);
        fix64 &operator -=(int32_t value);
        fix64 &operator *=(int32_t value);
        fix64 &operator /=(int32_t value);

        friend fix64 operator +(const fix64 &fx, int32_t value);
        friend fix64 operator +(int32_t value, const fix64 &fx);
        friend fix64 operator -(const fix64 &fx, int32_t value);
        friend fix64 operator -(int32_t value, const fix64 &fx);
        friend fix64 operator *(const fix64 &fx, int32_t value);
        friend fix64 operator *(int32_t value, const fix64 &fx);
        friend fix64 operator /(const fix64 &fx, int32_t value);
        friend fix64 operator /(int32_t value, const fix64 &fx);

        friend bool operator ==(const fix64 &fx, int32_t value);
        friend bool operator ==(int32_t value, const fix64 &fx);
        friend bool operator !=(const fix64 &fx, int32_t value);
        friend bool operator !=(int32_t value, const fix64 &fx);
        friend bool operator >=(const fix64 &fx, int32_t value);
        friend bool operator >=(int32_t value, const fix64 &fx);
        friend bool operator <=(const fix64 &fx, int32_t value);
        friend bool operator <=(int32_t value, const fix64 &fx);
        friend bool operator >(const fix64 &fx, int32_t value);
        friend bool operator >(int32_t value, const fix64 &fx);
        friend bool operator <(const fix64 &fx, int32_t value);
        friend bool operator <(int32_t value, const fix64 &fx);

        /// 转成32位整型
        operator int32_t() const;

        /// fix64和float32_t之间的运算符重载
        fix64 &operator =(float32_t value);

        fix64 &operator +=(float32_t value);
        fix64 &operator -=(float32_t value);
        fix64 &operator *=(float32_t value);
        fix64 &operator /=(float32_t value);

        friend fix64 operator +(const fix64 &fx, float32_t value);
        friend fix64 operator +(float32_t value, const fix64 &fx);
        friend fix64 operator -(const fix64 &fx, float32_t value);
        friend fix64 operator -(float32_t value, const fix64 &fx);
        friend fix64 operator *(const fix64 &fx, float32_t value);
        friend fix64 operator *(float32_t value, const fix64 &fx);
        friend fix64 operator /(const fix64 &fx, float32_t value);
        friend fix64 operator /(float32_t value, const fix64 &fx);

        friend bool operator ==(const fix64 &fx, float32_t value);
        friend bool operator ==(float32_t value, const fix64 &fx);
        friend bool operator !=(const fix64 &fx, float32_t value);
        friend bool operator !=(float32_t value, const fix64 &fx);
        friend bool operator >=(const fix64 &fx, float32_t value);
        friend bool operator >=(float32_t value, const fix64 &fx);
        friend bool operator <=(const fix64 &fx, float32_t value);
        friend bool operator <=(float32_t value, const fix64 &fx);
        friend bool operator >(const fix64 &fx, float32_t value);
        friend bool operator >(float32_t value, const fix64 &fx);
        friend bool operator <(const fix64 &fx, float32_t value);
        friend bool operator <(float32_t value, const fix64 &fx);

        operator float32_t() const;

        /// 位移运算符重载
        friend fix64 operator <<(const fix64 &a, int32_t b);
        friend fix64 operator >> (const fix64 &a, int32_t b);

        fix64 &operator <<=(int32_t b);
        fix64 &operator >>=(int32_t b);

        /// 是否等于0
        bool eq_0() const;
        /// 是否不等于0
        bool ne_0() const;
        /// 是否大于0
        bool gt_0() const;
        /// 是否大于等于0
        bool ge_0() const;
        /// 是否小于0
        bool lt_0() const;
        /// 是否小于等于0
        bool le_0() const;
        /// 是否等于1
        bool eq_1() const;
        /// 是否无限大
        bool is_INF() const;
        /// 是否无限小
        bool is_MINUSINF() const;
        /// 是否整数
        bool is_integer() const;

        /// 转换64位整型
        operator int64_t() const;

        /// 64位精度的定点数fix64与32位精度的定点数fix32之间的转换重载
        fix64 &operator =(const fix32 &fx);
        operator fix32() const;

    private:
        int64_t	m;
    };

    typedef fix64 fix64_t;
}

#include "T3DFix64.inl"


#endif  /*__T3D_FIX64_H__*/