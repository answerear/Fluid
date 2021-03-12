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
    inline TVector4<T>::TVector4()
        : _x(0.0)
        , _y(0.0)
        , _z(0.0)
        , _w(0.0)
    {

    }

    template <typename T>
    inline TVector4<T>::TVector4(T x, T y, T z, T w)
        : _x(x)
        , _y(y)
        , _z(z)
        , _w(w)
    {

    }

    template <typename T>
    inline TVector4<T>::TVector4(const TVector3<T> &v, T w)
        : _x(v.x())
        , _y(v.y())
        , _z(v.z())
        , _w(w)
    {

    }

    template <typename T>
    inline TVector4<T>::TVector4(const TVector4 &other)
        : _x(other._x)
        , _y(other._y)
        , _z(other._z)
        , _w(other._w)
    {

    }

    template <typename T>
    inline TVector4<T>::operator const T *() const
    {
        return &_x;
    }

    template <typename T>
    inline TVector4<T>::operator T *()
    {
        return &_x;
    }

    template <typename T>
    inline T TVector4<T>::operator [](int32_t i) const
    {
        T3D_ASSERT(i < 4);
        return *(&_x+i);
    }

    template <typename T>
    inline T &TVector4<T>::operator [](int32_t i)
    {
        T3D_ASSERT(i < 4);
        return *(&_x+i);
    }

    template <typename T>
    inline T TVector4<T>::x() const
    {
        return _x;
    }

    template <typename T>
    inline T &TVector4<T>::x()
    {
        return _x;
    }

    template <typename T>
    inline T TVector4<T>::y() const
    {
        return _y;
    }

    template <typename T>
    inline T &TVector4<T>::y()
    {
        return _y;
    }

    template <typename T>
    inline T TVector4<T>::z() const
    {
        return _z;
    }

    template <typename T>
    inline T &TVector4<T>::z()
    {
        return _z;
    }

    template <typename T>
    inline T TVector4<T>::w() const
    {
        return _w;
    }

    template <typename T>
    inline T &TVector4<T>::w()
    {
        return _w;
    }

    template <typename T>
    inline TVector4<T> &TVector4<T>::operator =(const TVector4 &other)
    {
        _x = other._x;
        _y = other._y;
        _z = other._z;
        _w = other._w;
        return *this;
    }

    template <typename T>
    inline bool TVector4<T>::operator ==(const TVector4 &other) const
    {
        return (_x == other._x && _y == other._y && _z == other._z && _w == other._w);
    }

    template <typename T>
    inline bool TVector4<T>::operator !=(const TVector4 &other) const
    {
        return (_x != other._x || _y != other._y || _z != other._z || _w != other._w);
    }

    template <typename T>
    inline TVector4<T> TVector4<T>::operator +(const TVector4 &other) const
    {
        return TVector4(_x + other._x, _y + other._y, _z + other._z, _w + other._w);
    }

    template <typename T>
    inline TVector4<T> TVector4<T>::operator -(const TVector4 &other) const
    {
        return TVector4(_x - other._x, _y - other._y, _z - other._z, _w - other._w);
    }

    template <typename T>
    inline TVector4<T> TVector4<T>::operator *(T scalar) const
    {
        return TVector4(scalar * _x, scalar * _y, scalar * _z, scalar * _w);
    }

    template <typename T>
    inline TVector4<T> TVector4<T>::operator /(T scalar) const
    {
        TVector4 result;

        if (scalar != TReal<T>::ZERO)
        {
            result._x = _x / scalar;
            result._y = _y / scalar;
            result._z = _z / scalar;
            result._w = _w / scalar;
        }

        return result;
    }

    template <typename T>
    inline TVector4<T> TVector4<T>::operator -() const
    {
        return TVector4(-_x, -_y, -_z, -_w);
    }

    template <typename T>
    inline TVector4<T> &TVector4<T>::operator +=(const TVector4 &other)
    {
        _x += other._x;
        _y += other._y;
        _z += other._z;
        _w += other._w;
        return *this;
    }

    template <typename T>
    inline TVector4<T> &TVector4<T>::operator -=(const TVector4 &other)
    {
        _x -= other._x;
        _y -= other._y;
        _z -= other._z;
        _w -= other._w;
        return *this;
    }

    template <typename T>
    inline TVector4<T> &TVector4<T>::operator *=(T fScalar)
    {
        _x *= fScalar;
        _y *= fScalar;
        _z *= fScalar;
        _w *= fScalar;
        return *this;
    }

    template <typename T>
    inline TVector4<T> &TVector4<T>::operator /=(T fScalar)
    {
        if (fScalar != TReal<T>::ZERO)
        {
            _x /= fScalar;
            _y /= fScalar;
            _z /= fScalar;
            _w /= fScalar;
        }
        else
        {
            _x = TReal<T>::ZERO;
            _y = TReal<T>::ZERO;
            _z = TReal<T>::ZERO;
            _w = TReal<T>::ZERO;
        }
        return *this;
    }

    template <typename T>
    inline T TVector4<T>::length() const
    {
        return TMath<T>::sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
    }

    template <typename T>
    inline T TVector4<T>::squaredLength() const
    {
        return _x * _x + _y * _y + _z * _z + _w * _w;
    }

    template <typename T>
    inline T TVector4<T>::distance(const TVector4 &other) const
    {
        return (*this - other).length();
    }

    template <typename T>
    inline T TVector4<T>::squaredDistance(const TVector4 &other) const
    {
        return (*this - other).squaredLength();
    }

    template <typename T>
    inline T TVector4<T>::dot(const TVector4 &other) const
    {
        return (_x * other._x + _y * other._y + _z * other._z + _w * other._w);
    }

    template <typename T>
    inline TVector4<T> TVector4<T>::cross(const TVector4 &other) const
    {
        return TVector4(_y * other._z - _z * other._y,
            _z * other._w - _w * other._z,
            _w * other._x - _x * other._w,
            _x * other._y - _y * other._x);
    }

    template <typename T>
    inline T TVector4<T>::normalize()
    {
        T fLength = length();

        if (fLength > TReal<T>::ZERO)
        {
            _x /= fLength;
            _y /= fLength;
            _z /= fLength;
            _w /= fLength;
        }
        else
        {
            fLength = TReal<T>::ZERO;
            _x = TReal<T>::ZERO;
            _y = TReal<T>::ZERO;
            _z = TReal<T>::ZERO;
            _w = TReal<T>::ZERO;
        }

        return fLength;
    }

    template <typename T>
    const TVector4<T> TVector4<T>::ZERO(0.0, 0.0, 0.0, 0.0);
}
