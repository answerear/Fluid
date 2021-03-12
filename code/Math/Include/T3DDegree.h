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

#ifndef __T3D_DEGREE_H__
#define __T3D_DEGREE_H__


#include "T3DMathPrerequisites.h"


namespace Tiny3D
{
    /// 角度类，用于表示角度
    template <typename T>
    class TDegree
    {
    public:
        /// 指定实数角度值的构造函数
        explicit TDegree(T degree = TReal<T>::ZERO);
        /// 指定弧度对象的构造函数
        TDegree(const TRadian<T> &radian);
        /// 拷贝构造函数
        TDegree(const TDegree &other);

        /// 重载赋值操作符，从一个实数角度赋值
        TDegree &operator =(T degree);
        /// 重载赋值操作符，从另外一个角度对象赋值
        TDegree &operator =(const TDegree &other);
        /// 重载赋值操作符，从一个弧度对象赋值
        TDegree &operator =(const TRadian<T> &radian);

        /// 重载取正数操作符
        const TDegree &operator +() const;
        /// 重载取反操作符
        TDegree operator -() const;

        /// 重载相等操作符
        bool operator ==(const TDegree &other) const;
        /// 重载不等操作符
        bool operator !=(const TDegree &other) const;
        /// 重载小于操作符
        bool operator <(const TDegree &other) const;
        /// 重载小于等于操作符
        bool operator <=(const TDegree &other) const;
        /// 重载大于操作符
        bool operator >(const TDegree &other) const;
        /// 重载大于等于操作符
        bool operator >=(const TDegree &other) const;

        /// 重载加法操作符，跟另一个角度对象相加
        TDegree operator +(const TDegree &other) const;
        /// 重载减法操作符，跟另一个角度对象相减
        TDegree operator -(const TDegree &other) const;

        /// 重载加法操作符，跟另一个弧度对象相加
        TDegree operator +(const TRadian<T> &radian) const;
        /// 重载减法操作符，跟另一个弧度对象相减
        TDegree operator -(const TRadian<T> &radian) const;

        /// 重载加法赋值操作符，跟另一个角度对象相加
        TDegree &operator +=(const TDegree &other);
        /// 重载减法赋值操作符，跟另一个角度对象相减
        TDegree &operator -=(const TDegree &other);

        /// 重载加法赋值操作符，跟另一个弧度对象相加
        TDegree &operator +=(const TRadian<T> &radian);
        /// 重载减法赋值操作符，跟另一个弧度对象相减
        TDegree &operator -=(const TRadian<T> &radian);

        /// 重载乘法操作符，跟一个标量实数相乘
        TDegree operator *(T scalar) const;
        /// 重载除法操作符，跟一个标量实数相除
        TDegree operator /(T scalar) const;

        /// 重载乘法赋值操作符，跟一个标量实数相乘
        TDegree &operator *=(T scalar);
        /// 重载除法赋值操作符，跟一个标量实数相除
        TDegree &operator /=(T scalar);

        /// 获取真实的角度值，返回一个实数值
        T valueDegrees() const;
        /// 获取真实的弧度制，返回一个实数值
        T valueRadians() const;

    private:
        T    mDegree;
    };

    #include "T3DDegree.inl"

    /// 重载标量和角度乘法操作符
    template <typename T>
    inline TDegree<T> operator *(T scalar, const TDegree<T> &degree)
    {
        return TDegree<T>(scalar * degree.valueDegrees());
    }
}


#endif  /*__T3D_DEGREE_H__*/
