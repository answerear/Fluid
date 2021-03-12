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

#ifndef __T3D_MATRIX3_H__
#define __T3D_MATRIX3_H__


#include "T3DMathPrerequisites.h"
#include "T3DMath.h"
#include "T3DVector3.h"


namespace Tiny3D
{
    /// 行优先存储构成的3x3方阵.
    template <typename T>
    class TMatrix3
    {
    public:
        /// 构造一个零矩阵或者单位矩阵.
        TMatrix3(bool isZero = true);
        /// 拷贝构造函数.
        TMatrix3(const TMatrix3 &other);
        /// 通过指定行列值构造矩阵.
        TMatrix3(T m00, T m01, T m02, T m10, T m11, T m12, 
            T m20, T m21, T m22);
        /// 通过一个指定行优先或者列优先的数组指定矩阵值来构造对象.
        TMatrix3(T tuple[9], bool isRowMajor);
        /// 通过指定三个行向量或者列向量构造对象.
        TMatrix3(const TVector3<T> &rkU, const TVector3<T> &rkV, 
            const TVector3<T> &rkW, bool isColumns);
        /// 通过指定指定一个行向量或者列向量数组构造对象.
        TMatrix3(const TVector3<T> *akV, bool isColumns);
        /// 通过指定对角元素值构造对角矩阵.
        TMatrix3(T m00, T m11, T m22);
        /// 通过指定旋转轴和弧度值构造一个旋转矩阵.
        TMatrix3(const TVector3<T> &rkAxis, const TRadian<T> &rkRadians);
        /// 通过两个向量张量积构造矩阵 M = U * (V ^ T).
        TMatrix3(const TVector3<T> &rkU, const TVector3<T> &rkV);

        /// 构造零矩阵.
        void makeZero();
        /// 构造单位矩阵.
        void makeIdentity();
        /// 构造对角矩阵.
        void makeDiagonal(T m00, T m11, T m22);
        /// 通过两个向量张量积构造矩阵 M = U * (V ^ T).
        void makeTensorProduct(const TVector3<T> &rkU, const TVector3<T> &rkV);

        /// 通过指定旋转轴和弧度值构造一个旋转矩阵.
        void fromAxisAngle(const TVector3<T> &rkAxis, const TRadian<T> &radians);
        /// 从矩阵中提取出旋转轴和旋转角弧度.
        void toAxisAngle(TVector3<T> &rAxis, TRadian<T> &rRadians) const;

        /// 获取矩阵元素数组首地址.
        operator const T *() const;
        operator T *();

        /// 根据获取矩阵对应行的元素值.
        const T *operator [](size_t row) const;
        T *operator [](size_t row);

        /// 通过指定行和列获取对应的元素.
        T operator ()(size_t row, size_t col) const;
        T &operator ()(size_t row, size_t col);

        /// 设置矩阵指定行向量.
        void setRow(size_t row, const TVector3<T> &rkV);
        /// 获取矩阵指定行向量.
        TVector3<T> getRow(size_t row) const;

        /// 设置矩阵指定列向量.
        void setColumn(size_t col, const TVector3<T> &rkV);
        /// 获取矩阵指定列向量.
        TVector3<T> getColumn(size_t col) const;

        /// 按照列向量优先获取矩阵数据.
        void getColumnMajor(T *columns) const;

        /// 重载赋值运算符.
        TMatrix3 &operator =(const TMatrix3 &other);

        /// 重载相等运算符.
        bool operator ==(const TMatrix3 &other) const;
        /// 重载不等运算符.
        bool operator !=(const TMatrix3 &other) const;
        /// 重载小于运算符.
        bool operator <(const TMatrix3 &other) const;
        /// 重载小于等于运算符.
        bool operator <=(const TMatrix3 &other) const;
        /// 重载大于运算符.
        bool operator >(const TMatrix3 &other) const;
        /// 重载大于等于运算符.
        bool operator >=(const TMatrix3 &other) const;

        /// 重载加法运算符.
        TMatrix3 operator +(const TMatrix3 &other) const;
        /// 重载减法运算符.
        TMatrix3 operator -(const TMatrix3 &other) const;

        /// 重载乘法运算符，实现两个矩阵相乘.
        TMatrix3 operator *(const TMatrix3 &other) const;

        /// 重载乘法运算符，实现矩阵跟一个标量相乘 M1 = M * scalar.
        TMatrix3 operator *(T scalar) const;
        /// 重载除法运算符，实现矩阵跟一个标量相除 M1 = M / scalar.
        TMatrix3 operator /(T scalar) const;

        /// 重载取反运算符.
        TMatrix3 operator -() const;

        /// 重载加法赋值运算符.
        TMatrix3 &operator +=(const TMatrix3 &other);
        /// 重载减法赋值运算符.
        TMatrix3 &operator -=(const TMatrix3 &other);
        /// 重载乘法赋值运算符，实现矩阵跟一个标量相乘 M = M * scalar.
        TMatrix3 &operator *=(T scalar);
        /// 重载除法赋值运算符，实现矩阵跟一个标量相除 M = M / scalar.
        TMatrix3 &operator /=(T scalar);

        /// 重载乘法运算符，实现矩阵左乘向量 M = M * V.
        TVector3<T> operator *(const TVector3<T> &rkV) const;

        /// 矩阵转置 M = (M ^ T).
        TMatrix3 transpose() const;
        /// 矩阵转置后乘以另外一个矩阵 M2 = (M ^ T) * M1.
        TMatrix3 transposeTimes(const TMatrix3 &other) const;
        /// 矩阵乘以另一个矩阵的转置矩阵 M2 = M * (M1 ^ T).
        TMatrix3 timesTranspose(const TMatrix3 &other) const;

        /// 计算矩阵的逆.
        TMatrix3 inverse() const;

        /// 计算矩阵的伴随矩阵.
        TMatrix3 adjoint() const;

        /// 计算矩阵行列式.
        T determinant() const;

        /// 二次型 ret = (U ^ T) * M * V.
        T qform(const TVector3<T> &rkU, const TVector3<T> &rkV) const;

        /// 计算本矩阵跟对角矩阵相乘 M1 = M * D
        TMatrix3 timesDiagonal(const TVector3<T> &rkDiag) const;

        /// 计算对角矩阵跟本矩阵相乘 M1 = D * M
        TMatrix3 diagonalTimes(const TVector3<T> &rkDiag) const;

        /// 矩阵标准正交化，使用 Gram-Schmidt 算法
        void orthonormalize();

        /// 这个矩阵必须是正交矩阵. 它分解为 Yaw * Pitch * Roll 
        /// 其中 Yaw 是绕向上的向量(Y轴)旋转；Pitch 是绕向右的向量(X轴)旋转； 
        /// Roll 是绕向前的向量(Z轴)旋转.
        ///
        ///        +-                       -+
        ///        |    1       0       0    |
        /// R(x) = |    0     cos(x) -sin(x) |
        ///        |    0     sin(x)  cos(x) |
        ///        +-                       -+
        ///
        ///        +-                       -+
        ///        |  cos(y)    0     sin(y) |
        /// R(y) = |    0       1       0    |
        ///        | -sin(y)    0     cos(y) |
        ///        +-                       -+
        ///
        ///        +-                       -+
        ///        |  cos(z) -sin(z)    0    |
        /// R(z) = |  sin(z)  cos(z)    0    |
        ///        |    0       0       1    |
        ///        +-                       -+

        /// 先绕X轴旋转，再绕Y轴旋转，最后绕Z轴旋转获得一个欧拉角旋转矩阵
        void fromEulerAnglesXYZ(
            const TRadian<T> &rkPitch, 
            const TRadian<T> &rkYaw, 
            const TRadian<T> &rkRoll);
        /// 先绕X轴旋转，再绕Z轴旋转，最后绕Z轴旋转获得一个欧拉角旋转矩阵
        void fromEulerAnglesXZY(
            const TRadian<T> &rkPitch, 
            const TRadian<T> &rkRoll, 
            const TRadian<T> &rkYaw);
        /// 先绕Y轴旋转，再绕X轴旋转，最后绕Z轴旋转获得一个欧拉角旋转矩阵
        void fromEulerAnglesYXZ(
            const TRadian<T> &rkYaw, 
            const TRadian<T> &rkPitch, 
            const TRadian<T> &rkRoll);
        /// 先绕Y轴旋转，再绕Z轴旋转，最后绕X轴旋转获得一个欧拉角旋转矩阵
        void fromEulerAnglesYZX(
            const TRadian<T> &rkYaw, 
            const TRadian<T> &rkRoll, 
            const TRadian<T> &rkPitch);
        /// 先绕Z轴旋转，再绕X轴旋转，最后绕Y轴旋转获得一个欧拉角旋转矩阵
        void fromEulerAnglesZXY(
            const TRadian<T> &rkRoll, 
            const TRadian<T> &rkPitch, 
            const TRadian<T> &rkYaw);
        /// 先绕Z轴旋转，再绕Y轴旋转，最后绕X轴旋转获得一个欧拉角旋转矩阵
        void fromEulerAnglesZYX(
            const TRadian<T> &krRoll, 
            const TRadian<T> &rkYaw, 
            const TRadian<T> &rkPitch);

        /// 从一个欧拉角旋转矩阵获取出三个轴的旋转弧度
        bool toEulerAnglesXYZ(TRadian<T> &rPitch, TRadian<T> &rYaw, TRadian<T> &rRoll) const;
        bool toEulerAnglesXZY(TRadian<T> &rPitch, TRadian<T> &rRoll, TRadian<T> &rYaw) const;
        bool toEulerAnglesYXZ(TRadian<T> &rYaw, TRadian<T> &rPitch, TRadian<T> &rRoll) const;
        bool toEulerAnglesYZX(TRadian<T> &rYaw, TRadian<T> &rRoll, TRadian<T> &rPitch) const;
        bool toEulerAnglesZXY(TRadian<T> &rRoll, TRadian<T> &rPitch, TRadian<T> &rYaw) const;
        bool toEulerAnglesZYX(TRadian<T> &rRoll, TRadian<T> &rYaw, TRadian<T> &rPitch) const;

        /// 矩阵分解成一个旋转矩阵、一个缩放矩阵、一个切变矩阵
        /// 其中 
        ///   rQ 表示分解出来的旋转矩阵
        ///   rD 表示分解出来的缩放对角矩阵中对角线上元素构成的向量
        ///   rU 表示分解出来的切变矩阵中上三角矩阵的元素构成的向量
        void QDUDecomposition(TMatrix3 &rQ, TVector3<T> &rD, TVector3<T> &rU) const;

    public:
        static const TMatrix3 ZERO;
        static const TMatrix3 IDENTITY;

    private:
        int32_t compareArrays(const TMatrix3 &other) const;

    private:
        union
        {
            T    mTuples[9];
            T    m3x3[3][3];
        };
    };

    /// 重载乘法运算符，实现一个标量跟矩阵相乘.
    template <typename T>
    TMatrix3<T> operator *(T scalar, const TMatrix3<T> &rkM);

    /// 重载乘法运算符，实现一个向量跟矩阵相乘.
    template <typename T>
    TVector3<T> operator *(const TVector3<T> &rkV, const TMatrix3<T> &rkM);
}


#include "T3DMatrix3.inl"


#endif  /*__T3D_MATRIX3_H__*/
