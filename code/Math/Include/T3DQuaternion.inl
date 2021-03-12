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

namespace Tiny3D
{
    template <typename T>
    inline void TQuaternion<T>::fromAngleAxis(const TRadian<T> &rkRadians, 
        const TVector3<T> &rkAxis)
    {
        TRadian<T> fHalfAngle(0.5f * rkRadians.valueRadians());
        T fSin = TMath<T>::sin(fHalfAngle);
        _w = TMath<T>::cos(fHalfAngle);
        _x = fSin * rkAxis.x();
        _y = fSin * rkAxis.y();
        _z = fSin * rkAxis.z();
    }

    template <typename T>
    inline void TQuaternion<T>::fromAxis(const TVector3<T> &rkXAxis, 
        const TVector3<T> &rkYAxis, const TVector3<T> &rkZAxis)
    {
        TMatrix3<T> kRot;

        kRot[0][0] = rkXAxis.x();
        kRot[1][0] = rkXAxis.y();
        kRot[2][0] = rkXAxis.z();

        kRot[0][1] = rkYAxis.x();
        kRot[1][1] = rkYAxis.y();
        kRot[2][1] = rkYAxis.z();

        kRot[0][2] = rkZAxis.x();
        kRot[1][2] = rkZAxis.y();
        kRot[2][2] = rkZAxis.z();

        fromRotationMatrix(kRot);
    }

    template <typename T>
    inline void TQuaternion<T>::fromAxis(const TVector3<T> *akAxis)
    {
        TMatrix3<T> kRot;

        kRot[0][0] = akAxis[0].x();
        kRot[1][0] = akAxis[0].y();
        kRot[2][0] = akAxis[0].z();

        kRot[0][1] = akAxis[1].x();
        kRot[1][1] = akAxis[1].y();
        kRot[2][1] = akAxis[1].z();

        kRot[0][2] = akAxis[2].x();
        kRot[1][2] = akAxis[2].y();
        kRot[2][2] = akAxis[2].z();

        fromRotationMatrix(kRot);
    }

    template <typename T>
    inline TQuaternion<T>::TQuaternion()
        : _w(0.0)
        , _x(0.0)
        , _y(0.0)
        , _z(0.0)
    {

    }

    template <typename T>
    inline TQuaternion<T>::TQuaternion(const TQuaternion &other)
    {
        _w = other._w;
        _x = other._x;
        _y = other._y;
        _z = other._z;
    }

    template <typename T>
    inline TQuaternion<T>::TQuaternion(T w, T x, T y, T z)
        : _w(w)
        , _x(x)
        , _y(y)
        , _z(z)
    {

    }

    template <typename T>
    inline TQuaternion<T>::TQuaternion(const TMatrix3<T> &rkRot)
    {
        fromRotationMatrix(rkRot);
    }

    template <typename T>
    inline TQuaternion<T>::TQuaternion(const TRadian<T> &rkAngle, 
        const TVector3<T> &rkAxis)
    {
        fromAngleAxis(rkAngle, rkAxis);
    }

    template <typename T>
    inline TQuaternion<T>::TQuaternion(const TVector3<T> &rkXAxis, 
        const TVector3<T> &rkYAxis, const TVector3<T> &rkZAxis)
    {
        fromAxis(rkXAxis, rkYAxis, rkZAxis);
    }

    template <typename T>
    inline TQuaternion<T>::TQuaternion(const TVector3<T> *akAxis)
    {
        fromAxis(akAxis);
    }

    template <typename T>
    inline TQuaternion<T>::TQuaternion(T *values)
        : _w(values[0])
        , _x(values[1])
        , _y(values[2])
        , _z(values[3])
    {
    }

    template <typename T>
    inline TQuaternion<T>::operator const T *() const
    {
        return &_w;
    }

    template <typename T>
    inline TQuaternion<T>::operator T *()
    {
        return &_w;
    }

    template <typename T>
    inline T TQuaternion<T>::operator [](int32_t i) const
    {
        T3D_ASSERT(i >= 0 && i < 4);
        return *(&_w + i);
    }

    template <typename T>
    inline T &TQuaternion<T>::operator [](int32_t i)
    {
        T3D_ASSERT(i >= 0 && i < 4);
        return *(&_w + i);
    }

    template <typename T>
    inline T TQuaternion<T>::x() const
    {
        return _x;
    }

    template <typename T>
    inline T &TQuaternion<T>::x()
    {
        return _x;
    }

    template <typename T>
    inline T TQuaternion<T>::y() const
    {
        return _y;
    }

    template <typename T>
    inline T &TQuaternion<T>::y()
    {
        return _y;
    }

    template <typename T>
    inline T TQuaternion<T>::z() const
    {
        return _z;
    }

    template <typename T>
    inline T &TQuaternion<T>::z()
    {
        return _z;
    }

    template <typename T>
    inline T TQuaternion<T>::w() const
    {
        return _w;
    }

    template <typename T>
    inline T &TQuaternion<T>::w()
    {
        return _w;
    }

    template <typename T>
    inline bool TQuaternion<T>::operator ==(const TQuaternion &other) const
    {
        return (_w == other._w 
            && _x == other._x 
            && _y == other._y 
            && _z == other._z);
    }

    template <typename T>
    inline bool TQuaternion<T>::operator !=(const TQuaternion &other) const
    {
        return !operator ==(other);
    }

    template <typename T>
    inline TQuaternion<T> &TQuaternion<T>::operator =(const TQuaternion &other)
    {
        _w = other._w;
        _x = other._x;
        _y = other._y;
        _z = other._z;
        return *this;
    }

    template <typename T>
    inline TQuaternion<T> TQuaternion<T>::operator +(
        const TQuaternion &other) const
    {
        return TQuaternion(
            _w + other._w, 
            _x + other._x,
            _y + other._y, 
            _z + other._z
        );
    }

    template <typename T>
    inline TQuaternion<T> TQuaternion<T>::operator -(
        const TQuaternion &other) const
    {
        return TQuaternion(
            _w - other._w, 
            _x - other._x, 
            _y - other._y, 
            _z - other._z
        );
    }

    template <typename T>
    inline TQuaternion<T> TQuaternion<T>::operator *(
        const TQuaternion &other) const
    {
        return TQuaternion
        (
            _w * other._w - _x * other._x - _y * other._y - _z * other._z,
            _w * other._x + _x * other._w + _y * other._z - _z * other._y,
            _w * other._y + _y * other._w + _z * other._x - _x * other._z,
            _w * other._z + _z * other._w + _x * other._y - _y * other._x
        );
    }

    template <typename T>
    inline TQuaternion<T> TQuaternion<T>::operator *(T scalar) const
    {
        return TQuaternion(_w*scalar, _x*scalar, _y*scalar, _z*scalar);
    }

    template <typename T>
    inline TQuaternion<T> TQuaternion<T>::operator /(T scalar) const
    {
        T fInvertScalar = 0.0f;
        if (scalar != TReal<T>::ZERO)
            fInvertScalar = TReal<T>::ONE / scalar;
        return TQuaternion(_w * fInvertScalar, 
            _x * fInvertScalar, 
            _y * fInvertScalar, 
            _z * fInvertScalar);
    }

    template <typename T>
    inline TQuaternion<T> &TQuaternion<T>::operator +=(const TQuaternion &other)
    {
        _w += other._w;
        _x += other._x;
        _y += other._y;
        _z += other._z;
        return *this;
    }

    template <typename T>
    inline TQuaternion<T> &TQuaternion<T>::operator -=(const TQuaternion &other)
    {
        _w -= other._w;
        _x -= other._x;
        _y -= other._y;
        _z -= other._z;
        return *this;
    }

    template <typename T>
    inline TQuaternion<T> &TQuaternion<T>::operator *=(const TQuaternion &other)
    {
        T w = _w * other._w - _x * other._x - _y * other._y - _z * other._z;
        T x = _w * other._x + _x * other._w + _y * other._z - _z * other._y;
        T y = _w * other._y + _y * other._w + _z * other._x - _x * other._z;
        T z = _w * other._z + _z * other._w + _x * other._y - _y * other._x;
        _w = w, _x = x, _y = y, _z = z;
        return *this;
    }

    template <typename T>
    inline TQuaternion<T> &TQuaternion<T>::operator *=(T scalar)
    {
        _w *= scalar;
        _x *= scalar;
        _y *= scalar;
        _z *= scalar;
        return *this;
    }

    template <typename T>
    inline TQuaternion<T> &TQuaternion<T>::operator /=(T scalar)
    {
        T fInvertScalar = TReal<T>::ZERO;
        if (scalar != TReal<T>::ZERO)
            fInvertScalar = TReal<T>::ONE / scalar;
        _w *= fInvertScalar;
        _x *= fInvertScalar;
        _y *= fInvertScalar;
        _z *= fInvertScalar;
        return *this;
    }

    template <typename T>
    inline TQuaternion<T> TQuaternion<T>::operator -() const
    {
        return TQuaternion(-_w, -_x, -_y, -_z);
    }

    template <typename T>
    inline TVector3<T> TQuaternion<T>::operator* (const TVector3<T>& v) const
    {
        // nVidia SDK implementation
        TVector3<T> uv, uuv;
        TVector3<T> qvec(_x, _y, _z);
        uv = qvec.cross(v);
        uuv = qvec.cross(uv);
        uv *= (T(2.0f) * _w);
        uuv *= T(2.0f);

        return v + uv + uuv;
    }

    template <typename T>
    inline T TQuaternion<T>::dot(const TQuaternion &other) const
    {
        return (_x * other._x + _y * other._y + _z * other._z + _w * other._w);
    }

    template <typename T>
    inline T TQuaternion<T>::norm() const
    {
        return _w * _w + _x * _x + _y * _y + _z * _z;
    }

    template <typename T>
    inline T TQuaternion<T>::normalize()
    {
        T len = norm();
        T factor = TReal<T>::ONE / TMath<T>::sqrt(len);
        *this = *this * factor;
        return len;
    }

    template <typename T>
    inline TQuaternion<T> TQuaternion<T>::inverse() const
    {
        T fNorm = _w * _w + _x * _x + _y * _y + _z * _z;
        if (fNorm > TReal<T>::ZERO)
        {
            T fInvNorm = TReal<T>::ONE / fNorm;
            return TQuaternion(
                 _w * fInvNorm,
                -_x * fInvNorm, 
                -_y * fInvNorm, 
                -_z * fInvNorm);
        }
        else
        {
            // return an invalid result to flag the error
            return ZERO;
        }
    }

    template <typename T>
    inline void TQuaternion<T>::toAngleAxis(TDegree<T> &rDegree, 
        TVector3<T> &rAxis) const
    {
        TRadian<T> rAngle;
        toAngleAxis(rAngle, rAxis);
        rDegree = rAngle;
    }

    template <typename T>
    inline TRadian<T> TQuaternion<T>::getPitch(
        bool reprojectAxis /* = true */) const
    {
        if (reprojectAxis)
        {
            // pitch = atan2(localy.z, localy.y)
            // pick parts of yAxis() implementation that we need
            T fTx = T(2.0f) * _x;
            //          T fTy  = 2.0f*y;
            T fTz = T(2.0f) * _z;
            T fTwx = fTx * _w;
            T fTxx = fTx * _x;
            T fTyz = fTz * _y;
            T fTzz = fTz * _z;

            // TVector3<T>(fTxy-fTwz, 1.0-(fTxx+fTzz), fTyz+fTwx);
            return TRadian<T>(TMath<T>::atan2(fTyz + fTwx, 
                TReal<T>::ONE - (fTxx + fTzz)));
        }
        else
        {
            // internal version
            return TRadian<T>(TMath<T>::atan2(2 * (_y * _z + _w * _x),
                _w * _w - _x * _x - _y * _y + _z * _z));
        }
    }

    template <typename T>
    inline TRadian<T> TQuaternion<T>::getYaw(bool reprojectAxis) const
    {
        if (reprojectAxis)
        {
            // yaw = atan2(localz.x, localz.z)
            // pick parts of zAxis() implementation that we need
            T fTx = T(2.0f) * _x;
            T fTy = T(2.0f) * _y;
            T fTz = T(2.0f) * _z;
            T fTwy = fTy * _w;
            T fTxx = fTx * _x;
            T fTxz = fTz * _x;
            T fTyy = fTy * _y;

            // TVector3<T>(fTxz+fTwy, fTyz-fTwx, 1.0-(fTxx+fTyy));

            return TRadian<T>(TMath<T>::atan2(fTxz + fTwy, 
                TReal<T>::ONE - (fTxx + fTyy)));
        }
        else
        {
            // internal version
            return TRadian<T>(TMath<T>::asin(-2 * (_x * _z - _w * _y)));
        }
    }

    template <typename T>
    inline TRadian<T> TQuaternion<T>::getRoll(bool reprojectAxis) const
    {
        if (reprojectAxis)
        {
            // roll = atan2(localx.y, localx.x)
            // pick parts of xAxis() implementation that we need
            //          T fTx  = 2.0*x;
            T fTy = T(2.0f) * _y;
            T fTz = T(2.0f) * _z;
            T fTwz = fTz * _w;
            T fTxy = fTy * _x;
            T fTyy = fTy * _y;
            T fTzz = fTz * _z;

            // TVector3<T>(1.0-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);

            return TRadian<T>(TMath<T>::atan2(fTxy + fTwz, 
                TMath<T>::ONE - (fTyy + fTzz)));
        }
        else
        {
            return TRadian<T>(TMath<T>::atan2(
                2 * (_x * _y + _w * _z),
                _w * _w + _x * _x - _y * _y - _z * _z));
        }
    }

    template <typename T>
    inline TVector3<T> TQuaternion<T>::xAxis() const
    {
        //T fTx  = 2.0*x;
        T fTy = T(2.0f) * _y;
        T fTz = T(2.0f) * _z;
        T fTwy = fTy * _w;
        T fTwz = fTz * _w;
        T fTxy = fTy * _x;
        T fTxz = fTz * _x;
        T fTyy = fTy * _y;
        T fTzz = fTz * _z;

        return TVector3<T>(TReal<T>::ONE - (fTyy + fTzz), fTxy + fTwz, fTxz - fTwy);
    }

    template <typename T>
    inline TVector3<T> TQuaternion<T>::yAxis() const
    {
        T fTx = T(2.0f) * _x;
        T fTy = T(2.0f) * _y;
        T fTz = T(2.0f) * _z;
        T fTwx = fTx * _w;
        T fTwz = fTz * _w;
        T fTxx = fTx * _x;
        T fTxy = fTy * _x;
        T fTyz = fTz * _y;
        T fTzz = fTz * _z;

        return TVector3<T>(fTxy - fTwz, 1.0f - (fTxx + fTzz), fTyz + fTwx);
    }

    template <typename T>
    inline TVector3<T> TQuaternion<T>::zAxis() const
    {
        T fTx = T(2.0f) * _x;
        T fTy = T(2.0f) * _y;
        T fTz = T(2.0f) * _z;
        T fTwx = fTx * _w;
        T fTwy = fTy * _w;
        T fTxx = fTx * _x;
        T fTxz = fTz * _x;
        T fTyy = fTy * _y;
        T fTyz = fTz * _y;

        return TVector3<T>(fTxz + fTwy, fTyz - fTwx, 1.0f - (fTxx + fTyy));
    }

    template <typename T>
    inline TQuaternion<T> operator *(T scalar, const TQuaternion<T> &rkQ)
    {
        return TQuaternion<T>(
            scalar * rkQ.x(), 
            scalar * rkQ.y(), 
            scalar * rkQ.z(), 
            scalar * rkQ.w());
    }

    template <typename T>
    const TQuaternion<T> TQuaternion<T>::IDENTITY(1.0, 0.0, 0.0, 0.0);

    template <typename T>
    const TQuaternion<T> TQuaternion<T>::ZERO(0.0, 0.0, 0.0, 0.0);

    template <typename T>
    void TQuaternion<T>::fromRotationMatrix(const TMatrix3<T> &rkRot)
    {
        // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
        // article "TQuaternion Calculus and Fast Animation".

        T fTrace = rkRot[0][0] + rkRot[1][1] + rkRot[2][2];
        T fRoot;

        if (fTrace > TReal<T>::ZERO)
        {
            // |w| > 1/2, may as well choose w > 1/2
            fRoot = TMath<T>::sqrt(fTrace + TReal<T>::ONE);  // 2w
            _w = TReal<T>::HALF * fRoot;
            fRoot = TReal<T>::HALF / fRoot;  // 1/(4w)
            _x = (rkRot[2][1] - rkRot[1][2]) * fRoot;
            _y = (rkRot[0][2] - rkRot[2][0]) * fRoot;
            _z = (rkRot[1][0] - rkRot[0][1]) * fRoot;
        }
        else
        {
            // |w| <= 1/2
            static size_t s_iNext[3] = { 1, 2, 0 };
            size_t i = 0;
            if (rkRot[1][1] > rkRot[0][0])
                i = 1;
            if (rkRot[2][2] > rkRot[i][i])
                i = 2;
            size_t j = s_iNext[i];
            size_t k = s_iNext[j];

            fRoot = TMath<T>::sqrt(rkRot[i][i] - rkRot[j][j] - rkRot[k][k] + TReal<T>::ONE);
            T* apkQuat[3] = { &_x, &_y, &_z };
            *apkQuat[i] = TReal<T>::HALF * fRoot;
            fRoot = TReal<T>::HALF / fRoot;
            _w = (rkRot[k][j] - rkRot[j][k]) * fRoot;
            *apkQuat[j] = (rkRot[j][i] + rkRot[i][j]) * fRoot;
            *apkQuat[k] = (rkRot[k][i] + rkRot[i][k]) * fRoot;
        }
    }

    template <typename T>
    void TQuaternion<T>::toAngleAxis(TRadian<T> &rAngle, TVector3<T> &rAxis) const
    {
        // The quaternion representing the rotation is
        //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

        T fSqrLength = _x * _x + _y * _y + _z * _z;
        if (fSqrLength > TReal<T>::ZERO)
        {
            rAngle = T(2.0f) * TMath<T>::acos(_w).valueRadians();
            T fInvLength = TReal<T>::ONE / TMath<T>::sqrt(fSqrLength);
            rAxis.x() = _x * fInvLength;
            rAxis.y() = _y * fInvLength;
            rAxis.z() = _z * fInvLength;
        }
        else
        {
            // angle is 0 (mod 2*pi), so any axis will do
            rAngle = TRadian<T>(0.0);
            rAxis.x() = TReal<T>::ONE;
            rAxis.y() = TReal<T>::ZERO;
            rAxis.z() = TReal<T>::ZERO;
        }
    }

    template <typename T>
    void TQuaternion<T>::toRotationMatrix(TMatrix3<T> &rRot) const
    {
        T fTx = _x + _x;
        T fTy = _y + _y;
        T fTz = _z + _z;
        T fTwx = fTx * _w;
        T fTwy = fTy * _w;
        T fTwz = fTz * _w;
        T fTxx = fTx * _x;
        T fTxy = fTy * _x;
        T fTxz = fTz * _x;
        T fTyy = fTy * _y;
        T fTyz = fTz * _y;
        T fTzz = fTz * _z;

        rRot[0][0] = TReal<T>::ONE - (fTyy + fTzz);
        rRot[0][1] = fTxy - fTwz;
        rRot[0][2] = fTxz + fTwy;
        rRot[1][0] = fTxy + fTwz;
        rRot[1][1] = TReal<T>::ONE - (fTxx + fTzz);
        rRot[1][2] = fTyz - fTwx;
        rRot[2][0] = fTxz - fTwy;
        rRot[2][1] = fTyz + fTwx;
        rRot[2][2] = TReal<T>::ONE - (fTxx + fTyy);
    }

    template <typename T>
    TQuaternion<T> &TQuaternion<T>::slerp(const TQuaternion &rkP, 
        const TQuaternion &rkQ, T times, bool shortestPath /* = true */, 
        T epsilon /* = TReal<T>::EPSILON */)
    {
        // 理论上的四元数 slerp 形式：
        //
        //      slerp(q0, q1, t) = (q1 * q0^(-1))^t q0
        //
        // 实际程序中使用的 slerp 形式：
        // 
        //                          sin((1 - t)ω)          sin(tω)
        //      slerp(q0, q1, t) = --------------- * q0 + --------- * q1
        //                              sin(ω)             sin(ω)
        //
        // 其中 cos(ω) 由以下求得：
        //      
        //                q0 * q1
        //      cos(ω) = ---------
        //               |q0|*|q1|
        //
        // 这里存在两个问题：
        // 
        //  * 当结果是负值时，我们将2个四元数的其中一个取反，取反它的系数和向量
        //    部分，并不会改变它代表的朝向。而经过这一步操作，可以保证这个旋转走
        //    的是最短路径
        //  * 当 q0 和 q1 的角度差非常小，小到导致 sin(ω) = 0 时，会出现第二个
        //    问题。如果这个情况出现了，当我们除以 sin(ω) 时就会得到一个
        //    未定义的记过。在这个情况下，我们可以回退回去使用q0和q1的线性插值。

        T fCos = rkP.dot(rkQ);
        TQuaternion rkT;

        // Do we need to invert rotation?
        if (fCos < TReal<T>::ZERO && shortestPath)
        {
            fCos = -fCos;
            rkT = -rkQ;
        }
        else
        {
            rkT = rkQ;
        }

        if (TMath<T>::abs(fCos) < TReal<T>::ONE - epsilon)
        {
            // Standard case (slerp)
            T fSin = TMath<T>::sqrt(1 - TMath<T>::sqr(fCos));
            TRadian<T> fAngle = TMath<T>::atan2(fSin, fCos);
            T fInvSin = TReal<T>::ONE / fSin;
            T fCoeff0 = TMath<T>::sin((TReal<T>::ONE - times) * fAngle) * fInvSin;
            T fCoeff1 = TMath<T>::sin(times * fAngle) * fInvSin;
            *this = fCoeff0 * rkP + fCoeff1 * rkT;
        }
        else
        {
            // There are two situations:
            // 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a 
            //    linear interpolation safely.
            // 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), 
            //    there are an infinite number of possibilities interpolation. 
            //    but we haven't have method to fix this case, so just use 
            //    linear interpolation here.
            TQuaternion t = (TReal<T>::ONE - times) * rkP + times * rkT;
            // taking the complement requires renormalisation
            t.normalize();
            *this = t;
        }

        return *this;
    }
}
