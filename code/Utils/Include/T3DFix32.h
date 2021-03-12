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

#ifndef __T3D_FIX32_H__
#define __T3D_FIX32_H__

#include "T3DUtilsPrerequisites.h"

namespace Tiny3D
{
    /**
     * @brief 32位定点数类
     * @remarks 32位定点数构成是用高20位作为整数部分，低12位用来做小数部分
     */
    class T3D_UTILS_API fix32
    {
    public:
        static const int32_t INTEGER_BITS;      // 整数位数
        static const int32_t DECIMAL_BITS;      // 小数位数

        static const int32_t MAX_INT_VALUE;     // 最大的整型数
        static const int32_t MIN_INT_VALUE;     // 最小的整型数

        static const float32_t MAX_FLOAT_VALUE; // 最大的浮点数
        static const float32_t MIN_FLOAT_VALUE; // 最小的浮点数

        static const fix32 ZERO;        // fix32(0.0f)
        static const fix32 HALF;        // fix32(0.5f)
        static const fix32 ONE;         // fix32(1.0f)
        static const fix32 MINUS_ONE;   // fix32(-1.0f)
        static const fix32 INF;         // fix32(Infinity)
        static const fix32 MINUSINF;    // fix32(-Infinity)
        static const fix32 EPSILON;     // fix32(1, 0)

        /// 默认构造函数
        fix32();
        /// 单精度浮点数参数的构造函数
        fix32(float32_t value);
        /// 双精度浮点数参数的构造函数
        fix32(float64_t value);
        /// 用32位整数构造定点数，32位分配：20.12
        fix32(int32_t value);
        /// 用64位整数构造定点数，64位分配：40.24
        fix32(int64_t value);

        /// 用32位整数直接赋值定点数来构造
        fix32(int32_t value, int32_t r);

        /// 拷贝构造函数
        fix32(const fix32 &value);
        
        /// 获取定点数的整型值
        int32_t mantissa() const;

        /// 获取定点数的整型值 
        int32_t &mantissa();

        /// 重载取正数操作符
        fix32 operator +() const;
        /// 重载取反操作符
        fix32 operator -() const;

        /// fix32和fix32之间的运算符重载
        fix32 &operator =(const fix32 &value);

        fix32 &operator +=(const fix32 &value);
        fix32 &operator -=(const fix32 &value);
        fix32 &operator *=(const fix32 &value);
        fix32 &operator /=(const fix32 &value);

        friend fix32 operator +(const fix32 &fx, const fix32 &gx);
        friend fix32 operator -(const fix32 &fx, const fix32 &gx);
        friend fix32 operator *(const fix32 &fx, const fix32 &gx);
        friend fix32 operator /(const fix32 &fx, const fix32 &gx);

        friend bool operator ==(const fix32 &fx, const fix32 &gx);
        friend bool operator !=(const fix32 &fx, const fix32 &gx);
        friend bool operator >=(const fix32 &fx, const fix32 &gx);
        friend bool operator <=(const fix32 &fx, const fix32 &gx);
        friend bool operator >(const fix32 &fx, const fix32 &gx);
        friend bool operator <(const fix32 &fx, const fix32 &gx);

        /// fix32和int32_t之间的运算符重载
        fix32 &operator =(int32_t value);

        fix32 &operator +=(int32_t value);
        fix32 &operator -=(int32_t value);
        fix32 &operator *=(int32_t value);
        fix32 &operator /=(int32_t value);

        friend fix32 operator +(const fix32 &fx, int32_t value);
        friend fix32 operator +(int32_t value, const fix32 &fx);
        friend fix32 operator -(const fix32 &fx, int32_t value);
        friend fix32 operator -(int32_t value, const fix32 &fx);
        friend fix32 operator *(const fix32 &fx, int32_t value);
        friend fix32 operator *(int32_t value, const fix32 &fx);
        friend fix32 operator /(const fix32 &fx, int32_t value);
        friend fix32 operator /(int32_t value, const fix32 &fx);

        friend bool operator ==(const fix32 &fx, int32_t value);
        friend bool operator ==(int32_t value, const fix32 &fx);
        friend bool operator !=(const fix32 &fx, int32_t value);
        friend bool operator !=(int32_t value, const fix32 &fx);
        friend bool operator >=(const fix32 &fx, int32_t value);
        friend bool operator >=(int32_t value, const fix32 &fx);
        friend bool operator <=(const fix32 &fx, int32_t value);
        friend bool operator <=(int32_t value, const fix32 &fx);
        friend bool operator >(const fix32 &fx, int32_t value);
        friend bool operator >(int32_t value, const fix32 &fx);
        friend bool operator <(const fix32 &fx, int32_t value);
        friend bool operator <(int32_t value, const fix32 &fx);

        /// 强转成32位整型
        operator int32_t() const;

        /// fix32和float32_t之间的运算符重载
        fix32 &operator =(float32_t value);

        fix32 &operator +=(float32_t value);
        fix32 &operator -=(float32_t value);
        fix32 &operator *=(float32_t value);
        fix32 &operator /=(float32_t value);

        friend fix32 operator +(const fix32 &fx, float32_t value);
        friend fix32 operator +(float32_t value, const fix32 &fx);
        friend fix32 operator -(const fix32 &fx, float32_t value);
        friend fix32 operator -(float32_t value, const fix32 &fx);
        friend fix32 operator *(const fix32 &fx, float32_t value);
        friend fix32 operator *(float32_t value, const fix32 &fx);
        friend fix32 operator /(const fix32 &fx, float32_t value);
        friend fix32 operator /(float32_t value, const fix32 &fx);

        friend bool operator ==(const fix32 &fx, float32_t value);
        friend bool operator ==(float32_t value, const fix32 &fx);
        friend bool operator !=(const fix32 &fx, float32_t value);
        friend bool operator !=(float32_t value, const fix32 &fx);
        friend bool operator >=(const fix32 &fx, float32_t value);
        friend bool operator >=(float32_t value, const fix32 &fx);
        friend bool operator <=(const fix32 &fx, float32_t value);
        friend bool operator <=(float32_t value, const fix32 &fx);
        friend bool operator >(const fix32 &fx, float32_t value);
        friend bool operator >(float32_t value, const fix32 &fx);
        friend bool operator <(const fix32 &fx, float32_t value);
        friend bool operator <(float32_t value, const fix32 &fx);

        /// 转成32位单精度浮点型
        operator float32_t() const;

        /// 位移运算符重载
        friend fix32 operator <<(const fix32 &a, int32_t b);
        friend fix32 operator >>(const fix32 &a, int32_t b);

        fix32 &operator <<=(int32_t b);
        fix32 &operator >>=(int32_t b);

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

    private:
        int32_t m;
    };

    typedef fix32 fix32_t;
}

#include "T3DFix32.inl"


#endif  /*__T3D_FIX32_H__*/