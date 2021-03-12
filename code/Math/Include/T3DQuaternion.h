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

#ifndef __T3D_QUATERNION_H__
#define __T3D_QUATERNION_H__


#include "T3DMathPrerequisites.h"
#include "T3DMath.h"
#include "T3DMatrix3.h"


namespace Tiny3D
{
    template <typename T>
    class TQuaternion
    {
    public:
        /// 默认构造函数，构造一个单位四元数(1,0,0,0)对象.
        TQuaternion();
        /// 拷贝构造函数.
        TQuaternion(const TQuaternion &other);
        /// 指定四元数四个值构造对象.
        TQuaternion(T w, T x, T y, T z);
        /// 通过一个旋转矩阵构造一个四元数对象.
        TQuaternion(const TMatrix3<T> &rkRot);
        /// 指定旋转轴和旋转弧度构造一个四元数对象.
        TQuaternion(const TRadian<T> &rkAngle, const TVector3<T> &rkAxis);
        /// 通过指定3个正交轴构造一个四元数对象.
        TQuaternion(
            const TVector3<T> &rkXAxis, 
            const TVector3<T> &rkYAxis, 
            const TVector3<T> &rkZAxis);
        /// 通过指定3个正交向量数组首地址构造一个四元数对象(XYZ顺序).
        TQuaternion(const TVector3<T> *akAxis);
        /// 通过指定4个元素的数组首地址构造一个四元数对象(w, x, y, z).
        TQuaternion(T *values);

        /// 获取四元数元素数值数组首地址，按照w, x, y, z顺序返回.
        operator const T *() const;
        operator T *();

        /// 根据下标获取四元数元素数值.
        T operator [](int32_t i) const;
        T &operator [](int32_t i);

        /// 获取X元素值.
        T x() const;
        T &x();

        /// 获取Y元素值.
        T y() const;
        T &y();

        /// 获取Z元素值.
        T z() const;
        T &z();

        /// 获取W元素值.
        T w() const;
        T &w();

        /// 重载相等运算符.
        bool operator ==(const TQuaternion &other) const;
        /// 重载不等运算符.
        bool operator !=(const TQuaternion &other) const;

        /// 重载赋值运算符.
        TQuaternion &operator =(const TQuaternion &other);

        /// 重载加法运算符.
        TQuaternion operator +(const TQuaternion &other) const;
        /// 重载减法运算符.
        TQuaternion operator -(const TQuaternion &other) const;
        /// 重载乘法运算符，实现跟另一个四元数的叉乘.
        TQuaternion operator *(const TQuaternion &other) const;
        /// 重载乘法运算符，实现跟一个标量相乘.
        TQuaternion operator *(T scalar) const;
        /// 重载除法运算符，实现跟一个标量相除.
        TQuaternion operator /(T scalar) const;

        /// 重载加法赋值运算符.
        TQuaternion &operator +=(const TQuaternion &other);
        /// 重载减法赋值运算符.
        TQuaternion &operator -=(const TQuaternion &other);
        /// 重载乘法赋值运算符，实现跟另一个四元数的叉乘.
        TQuaternion &operator *=(const TQuaternion &other);
        /// 重载乘法赋值运算符，实现跟一个标量相乘.
        TQuaternion &operator *=(T scalar);
        /// 重载除法赋值运算符，实现跟一个标量相乘.
        TQuaternion &operator /=(T scalar);

        /// 重载取反运算符.
        TQuaternion operator -() const;

        /// 通过四元数旋转一个向量.
        TVector3<T> operator* (const TVector3<T> &rkVector) const;

        /// 计算四元数点积.
        T dot(const TQuaternion &other) const;

        /// 计算四元数的范数的平方.
        T norm() const;
        /// 规范化四元数，返回四元数长度.
        T normalize();

        /// 计算四元数的逆.
        TQuaternion inverse() const;

        /// 根据指定旋转弧度和旋转轴构造一个四元数.
        void fromAngleAxis(const TRadian<T> &rkRadians, const TVector3<T> &rkAxis);
        /// 根据指定三个正交向量构造一个四元数.
        void fromAxis(
            const TVector3<T> &rkXAxis, 
            const TVector3<T> &rkYAxis, 
            const TVector3<T> &rkZAxis);
        /// 根据指定三个正交向量数组首地址构造一个四元数.
        void fromAxis(const TVector3<T> *akAxis);
        /// 根据一个旋转矩阵构造一个四元数.
        void fromRotationMatrix(const TMatrix3<T> &rkRot);

        /// 把四元数转成一个旋转角(弧度)和一个单位向量表示的旋转轴.
        void toAngleAxis(TRadian<T> &rAngle, TVector3<T> &rAxis) const;
        /// 把四元数转成一个旋转角(角度)和一个单位向量表示的旋转轴.
        void toAngleAxis(TDegree<T> &rAngle, TVector3<T> &rAxis) const;
        /// 把四元数转成三个正交单位向量.
        void toAngleAxis(TVector3<T> *aAxis) const;
        /// 把四元数转成一个旋转矩阵.
        void toRotationMatrix(TMatrix3<T> &rRot) const;

        /// 获取绕X轴旋转(俯仰角)的角度(单位：弧度).
        TRadian<T> getPitch(bool reprojectAxis = true) const;
        /// 获取绕Z轴旋转(翻滚角)的角度(单位：弧度).
        TRadian<T> getRoll(bool reprojectAxis = true) const;
        /// 获取绕Y轴旋转(偏航角)的角度(单位：弧度).
        TRadian<T> getYaw(bool reprojectAxis = true) const;

        /// 获取X正交轴.
        TVector3<T> xAxis() const;
        /// 获取Y正交轴.
        TVector3<T> yAxis() const;
        /// 获取Z正交轴.
        TVector3<T> zAxis() const;

        /// 两个四元数球面插值构造一个四元数.
        TQuaternion &slerp(const TQuaternion &rkP, const TQuaternion &rkQ, 
            T times, bool shortestPath = true, T epsilon = TReal<T>::EPSILON);

        static const TQuaternion IDENTITY;       /// 单位四元数
        static const TQuaternion ZERO;           /// 零四元数

    private:
        T    _w;
        T    _x;
        T    _y;
        T    _z;
    };

    /// 重载乘法运算符，实现一个标量跟四元数相乘
    template <typename T>
    TQuaternion<T> operator *(T scalar, const TQuaternion<T> &rkQ);
}


#include "T3DQuaternion.inl"


#endif  /*__T3D_QUATERNION_H__*/
