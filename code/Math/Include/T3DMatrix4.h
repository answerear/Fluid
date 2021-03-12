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

#ifndef __T3D_MATRIX4_H__
#define __T3D_MATRIX4_H__


#include "T3DMathPrerequisites.h"
#include "T3DMath.h"
#include "T3DMatrix3.h"
#include "T3DQuaternion.h"
#include "T3DVector4.h"


namespace Tiny3D
{
    template <typename T>
    class TMatrix4
    {
    public:
        /// 默认构造函数.
        TMatrix4(bool isZero = false);
        /// 拷贝构造函数.
        TMatrix4(const TMatrix4 &other);
        /// 指定各行各列具体数值构造对象.
        TMatrix4(T m00, T m01, T m02, T m03,
                T m10, T m11, T m12, T m13,
                T m20, T m21, T m22, T m23,
                T m30, T m31, T m32, T m33);
        /// 通过一个旋转矩阵或者缩放矩阵构造对象，其中平移部分为0.
        TMatrix4(const TMatrix3<T> &rkMat);
        /// 通过一个旋转或者缩放计算的四元数构造对象，其中平移部分为0.
        TMatrix4(const TQuaternion<T> &rkRot);
        /// 通过位移向量构造对象.
        TMatrix4(const TVector3<T> &rkPos);
        /// 构造对角矩阵.
        TMatrix4(T m00, T m11, T m22, T m33);
        /// 通过三正交向量构造对象
        TMatrix4(const TVector3<T> &X, const TVector3<T> &Y, const TVector3<T> &Z);

        /// 构造零矩阵.
        void makeZero();
        /// 构造单位矩阵.
        void makeIdentity();

        /// 返回成员变量的数组首地址.
        operator const T *() const;
        operator T *();

        /// 根据获取矩阵对应行的元素值.
        const T *operator [](size_t row) const;
        T *operator [](size_t row);

        /// 通过指定行和列获取对应的元素.
        T operator ()(size_t row, size_t col) const;
        T &operator ()(size_t row, size_t col);

        /// 重载赋值运算符，相同类型对象赋值.
        TMatrix4 &operator =(const TMatrix4 &other);
        /// 重载赋值运算符，从一个3x3方针赋值.
        void operator =(const TMatrix3<T> &rkMat);

        /// 重载相等运算符.
        bool operator ==(const TMatrix4 &other) const;
        /// 重载不等运算符.
        bool operator !=(const TMatrix4 &other) const;
        /// 重载小于运算符.
        bool operator <(const TMatrix4 &other) const;
        /// 重载小于等于运算符.
        bool operator <=(const TMatrix4 &other) const;
        /// 重载大于运算符.
        bool operator >(const TMatrix4 &other) const;
        /// 重载大于等于运算符.
        bool operator >=(const TMatrix4 &other) const;

        /// 重载加法运算符.
        TMatrix4 operator +(const TMatrix4 &other) const;
        /// 重载减法运算符.
        TMatrix4 operator -(const TMatrix4 &other) const;

        /// 重载乘法运算符，实现两个矩阵相乘.
        TMatrix4 operator *(const TMatrix4 &other) const;

        /// 重载乘法运算符，实现矩阵跟一个标量相乘 M1 = M * scalar.
        TMatrix4 operator *(T scalar) const;
        /// 重载除法运算符，实现矩阵跟一个标量相除 M1 = M / scalar.
        TMatrix4 operator /(T scalar) const;

        /// 重载取反运算符.
        TMatrix4 operator -() const;

        /// 重载加法赋值运算符.
        TMatrix4 &operator +=(const TMatrix4 &other);
        /// 重载减法赋值运算符.
        TMatrix4 &operator -=(const TMatrix4 &other);
        /// 重载乘法赋值运算符，实现矩阵跟一个标量相乘 M = M * scalar.
        TMatrix4 &operator *=(T scalar);
        /// 重载除法赋值运算符，实现矩阵跟一个标量相除 M = M / scalar.
        TMatrix4 &operator /=(T scalar);

        /// 重载乘法运算符，实现矩阵左乘向量 M = M * V.
        TVector4<T> operator *(const TVector4<T> &rkV) const;
        TVector3<T> operator *(const TVector3<T> &rkV) const;

        /// 矩阵转置 M = (M ^ T).
        TMatrix4 transpose() const;

        /// 计算矩阵的逆.
        TMatrix4 inverse() const;
        /// 计算仿射变换矩阵的逆.
        TMatrix4 inverseAffine() const;

        /// 返回是否仿射变换矩阵判断.
        bool isAffine() const;

        ///  返回是否缩放变换判断.
        bool hasScale() const;

        /// 计算矩阵的伴随矩阵.
        TMatrix4 adjoint() const;

        /// 计算矩阵行列式.
        T determinant() const;

        /// 连接两个仿射变换矩阵.
        TMatrix4 concatenateAffine(const TMatrix4 &other) const;

        /// 分解成一个3-D向量表示的位移、一个3-D向量表示的缩放、
        /// 一个四元数表示的旋转.
        void decomposition(TVector3<T> &position, TVector3<T> &scale, 
            TQuaternion<T> &orientation) const;

        /// 提取出一个表示其旋转或者缩放的3x3矩阵.
        void extractMatrix(TMatrix3<T> &rkMat) const;
        /// 提取出一个表示其旋转或者缩放的四元数.
        TQuaternion<T> extractQuaternion() const;
        /// 提取出一个3-D位移向量.
        TVector3<T> extractTranslation() const;

        /// 通过一个3-D位移向量、一个3-D缩放向量和一个旋转四元数构造矩阵.
        void makeTransform(const TVector3<T> &position, 
            const TVector3<T> &scale, const TQuaternion<T> &orientation);
        /// 通过一个3-D位移向量、一个3-D缩放向量和一个旋转四元数构造逆矩阵.
        void makeInverseTransform(const TVector3<T> &position, 
            const TVector3<T> &scale, const TQuaternion<T> &orientation);

        /// 通过指定的一个3-D向量构造位移矩阵.
        void makeTranslate(const TVector3<T> &position);
        /// 通过指定的3-D位移值构造位移矩阵.
        void makeTranslate(T tx, T ty, T tz);

        /// 设置矩阵缩放值.
        void setScale(const TVector3<T> &scale);

        /// 设置矩阵位移部分.
        void setTranslate(const TVector3<T> &position);

        /// 变换一个3-D向量.
        TVector3<T> transformAffine(const TVector3<T> &v) const;
        /// 变换一个4-D向量.
        TVector4<T> transformAffine(const TVector4<T> &v) const;

        static const TMatrix4 ZERO;      /// 零矩阵
        static const TMatrix4 IDENTITY;  /// 单位矩阵

    protected:
        int32_t compareArrays(const TMatrix4 &other) const;

    private:
        union
        {
            T m4x4[4][4];
            T mTuples[16];
        };
    };

    /// 重载乘法运算符，实现一个标量跟矩阵相乘
    template <typename T>
    TMatrix4<T> operator *(T scalar, const TMatrix4<T> &rkM);

    /// 重载乘法运算符，实现一个向量跟矩阵相乘.
    template <typename T>
    TVector4<T> operator *(const TVector4<T> &rkV, const TMatrix4<T> &rkM);
}


#include "T3DMatrix4.inl"


#endif  /*__T3D_MATRIX4_H__*/
