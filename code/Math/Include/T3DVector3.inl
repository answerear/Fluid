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
    inline TVector3<T>::TVector3()
        : _x(0.0)
        , _y(0.0)
        , _z(0.0)
    {

    }

    template <typename T>
    inline TVector3<T>::TVector3(T x, T y, T z)
        : _x(x)
        , _y(y)
        , _z(z)
    {

    }

    template <typename T>
    inline TVector3<T>::TVector3(const TVector3 &other)
        : _x(other._x)
        , _y(other._y)
        , _z(other._z)
    {

    }

    template <typename T>
    inline TVector3<T>::operator const T *() const
    {
        return &_x;
    }

    template <typename T>
    inline TVector3<T>::operator T *()
    {
        return &_x;
    }

    template <typename T>
    inline T TVector3<T>::operator [](int32_t i) const
    {
        T3D_ASSERT(i < 3);
        return *(&_x+i);
    }

    template <typename T>
    inline T &TVector3<T>::operator [](int32_t i)
    {
        T3D_ASSERT(i < 3);
        return *(&_x+i);
    }

    template <typename T>
    inline T TVector3<T>::x() const
    {
        return _x;
    }

    template <typename T>
    inline T &TVector3<T>::x()
    {
        return _x;
    }

    template <typename T>
    inline T TVector3<T>::y() const
    {
        return _y;
    }

    template <typename T>
    inline T &TVector3<T>::y()
    {
        return _y;
    }

    template <typename T>
    inline T TVector3<T>::z() const
    {
        return _z;
    }

    template <typename T>
    inline T &TVector3<T>::z()
    {
        return _z;
    }

    template <typename T>
    inline TVector3<T> &TVector3<T>::operator =(const TVector3 &other)
    {
        _x = other._x;
        _y = other._y;
        _z = other._z;
        return *this;
    }

    template <typename T>
    inline bool TVector3<T>::operator ==(const TVector3 &other) const
    {
        return (_x == other._x && _y == other._y && _z == other._z);
    }

    template <typename T>
    inline bool TVector3<T>::operator !=(const TVector3 &other) const
    {
        return (_x != other._x || _y != other._y || _z != other._z);
    }

    template <typename T>
    inline int32_t TVector3<T>::compareArrays(const TVector3 &other) const
    {
        return memcmp(&_x, &other._x, 3*sizeof(T));
    }

    template <typename T>
    inline bool TVector3<T>::operator <(const TVector3 &other) const
    {
        return compareArrays(other) < 0;
    }

    template <typename T>
    inline bool TVector3<T>::operator <=(const TVector3 &other) const
    {
        return compareArrays(other) <= 0;
    }

    template <typename T>
    inline bool TVector3<T>::operator >(const TVector3 &other) const
    {
        return compareArrays(other) > 0;
    }

    template <typename T>
    inline bool TVector3<T>::operator >=(const TVector3 &other) const
    {
        return compareArrays(other) >= 0;
    }

    template <typename T>
    inline TVector3<T> TVector3<T>::operator +(const TVector3 &other) const
    {
        return TVector3(_x + other._x, _y + other._y, _z + other._z);
    }

    template <typename T>
    inline TVector3<T> TVector3<T>::operator -(const TVector3 &other) const
    {
        return TVector3(_x - other._x, _y - other._y, _z - other._z);
    }

    template <typename T>
    inline TVector3<T> TVector3<T>::operator *(T scalar) const
    {
        return TVector3(scalar * _x, scalar * _y, scalar * _z);
    }

    template <typename T>
    inline TVector3<T> TVector3<T>::operator /(T scalar) const
    {
        TVector3 result;

        if (scalar != TReal<T>::ZERO)
        {
            result._x = _x / scalar;
            result._y = _y / scalar;
            result._z = _z / scalar;
        }

        return result;
    }

    template <typename T>
    inline TVector3<T> TVector3<T>::operator *(const TVector3 &other) const
    {
        TVector3 v;
        v.x() = _x * other._x;
        v.y() = _y * other._y;
        v.z() = _z * other._z;
        return v;
    }

    template <typename T>
    inline TVector3<T> TVector3<T>::operator -() const
    {
        return TVector3(-_x, -_y, -_z);
    }

    template <typename T>
    inline TVector3<T> &TVector3<T>::operator +=(const TVector3 &other)
    {
        _x += other._x;
        _y += other._y;
        _z += other._z;
        return *this;
    }

    template <typename T>
    inline TVector3<T> &TVector3<T>::operator -=(const TVector3 &other)
    {
        _x -= other._x;
        _y -= other._y;
        _z -= other._z;
        return *this;
    }

    template <typename T>
    inline TVector3<T> &TVector3<T>::operator *=(T scalar)
    {
        _x *= scalar;
        _y *= scalar;
        _z *= scalar;
        return *this;
    }

    template <typename T>
    inline TVector3<T> &TVector3<T>::operator *=( const TVector3 &rkVector)
    {
        _x *= rkVector._x;
        _y *= rkVector._y;
        _z *= rkVector._z;
        return *this;
    }

    template <typename T>
    inline TVector3<T> &TVector3<T>::operator /=(T scalar)
    {
        if (scalar != TReal<T>::ZERO)
        {
            _x /= scalar;
            _y /= scalar;
            _z /= scalar;
        }
        else
        {
            _x = TReal<T>::ZERO;
            _y = TReal<T>::ZERO;
            _z = TReal<T>::ZERO;
        }

        return *this;
    }

    template <typename T>
    inline T TVector3<T>::length() const
    {
        return TMath<T>::sqrt(_x * _x + _y * _y + _z * _z);
    }

    template <typename T>
    inline T TVector3<T>::length2() const
    {
        return (_x * _x + _y * _y + _z * _z);
    }

    template <typename T>
    inline T TVector3<T>::distance(const TVector3 &other) const
    {
        return (*this - other).length();
    }

    template <typename T>
    inline T TVector3<T>::distance2(const TVector3 &other) const
    {
        return (*this - other).length2();
    }

    template <typename T>
    inline T TVector3<T>::dot(const TVector3 &other) const
    {
        return (_x * other._x + _y * other._y + _z * other._z);
    }

    template <typename T>
    inline TVector3<T> TVector3<T>::cross(const TVector3 &other) const
    {
        return TVector3(_y * other._z - _z * other._y,
            _z * other._x - _x * other._z,
            _x * other._y - _y * other._x);
    }

    template <typename T>
    inline T TVector3<T>::normalize()
    {
        T len = length();

        if (len > TReal<T>::ZERO)
        {
            _x /= len;
            _y /= len;
            _z /= len;
        }
        else
        {
            len = TReal<T>::ZERO;
            _x = TReal<T>::ZERO;
            _y = TReal<T>::ZERO;
            _z = TReal<T>::ZERO;
        }

        return len;
    }

    template <typename T>
    inline TVector3<T> operator *(T scalar, const TVector3<T> &rkV)
    {
        return TVector3<T>(scalar * rkV.x(), scalar * rkV.y(), scalar * rkV.z());
    }

    template <typename T>
    const TVector3<T> TVector3<T>::ZERO(0.0, 0.0, 0.0);

    template <typename T>
    const TVector3<T> TVector3<T>::UNIT_SCALE(1.0, 1.0, 1.0);

    template <typename T>
    const TVector3<T> TVector3<T>::UNIT_X(1.0, 0.0, 0.0);

    template <typename T>
    const TVector3<T> TVector3<T>::UNIT_Y(0.0, 1.0, 0.0);

    template <typename T>
    const TVector3<T> TVector3<T>::UNIT_Z(0.0, 0.0, 1.0);

    template <typename T>
    const TVector3<T> TVector3<T>::NEGATIVE_UNIT_X(-1.0, 0.0, 0.0);

    template <typename T>
    const TVector3<T> TVector3<T>::NEGATIVE_UNIT_Y(0.0, -1.0, 0.0);

    template <typename T>
    const TVector3<T> TVector3<T>::NEGATIVE_UNIT_Z(0.0, 0.0, -1.0);
}
