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
    inline TVector2<T>::TVector2()
        : _x(0.0)
        , _y(0.0)
    {

    }

    template <typename T>
    inline TVector2<T>::TVector2(T x, T y)
        : _x(x)
        , _y(y)
    {

    }

    template <typename T>
    inline TVector2<T>::TVector2(const TVector2 &other)
        : _x(other._x)
        , _y(other._y)
    {

    }

    template <typename T>
    inline TVector2<T>::operator const T *() const
    {
        return &_x;
    }

    template <typename T>
    inline TVector2<T>::operator T *()
    {
        return &_x;
    }

    template <typename T>
    inline T TVector2<T>::operator [](int32_t i) const
    {
        T3D_ASSERT(i < 2);
        return *(&_x+i);
    }

    template <typename T>
    inline T &TVector2<T>::operator [](int32_t i)
    {
        T3D_ASSERT(i < 2);
        return *(&_x+i);
    }

    template <typename T>
    inline T TVector2<T>::x() const
    {
        return _x;
    }

    template <typename T>
    inline T &TVector2<T>::x()
    {
        return _x;
    }

    template <typename T>
    inline T TVector2<T>::y() const
    {
        return _y;
    }

    template <typename T>
    inline T &TVector2<T>::y()
    {
        return _y;
    }

    template <typename T>
    inline TVector2<T> &TVector2<T>::operator =(const TVector2 &other)
    {
        _x = other._x;
        _y = other._y;
        return *this;
    }

    template <typename T>
    inline bool TVector2<T>::operator ==(const TVector2 &other) const
    {
        return (_x == other._x && _y == other._y);
    }

    template <typename T>
    inline bool TVector2<T>::operator !=(const TVector2 &other) const
    {
        return (_x != other._x || _y != other._y);
    }

    template <typename T>
    inline int32_t TVector2<T>::compareArrays(const TVector2 &other) const
    {
        return memcmp(&_x, &other._x, 2*sizeof(T));
    }

    template <typename T>
    inline bool TVector2<T>::operator <(const TVector2 &other) const
    {
        return compareArrays(other) < 0;
    }

    template <typename T>
    inline bool TVector2<T>::operator <=(const TVector2 &other) const
    {
        return compareArrays(other) <= 0;
    }

    template <typename T>
    inline bool TVector2<T>::operator >(const TVector2 &other) const
    {
        return compareArrays(other) > 0;
    }

    template <typename T>
    inline bool TVector2<T>::operator >=(const TVector2 &other) const
    {
        return compareArrays(other) >= 0;
    }

    template <typename T>
    inline TVector2<T> TVector2<T>::operator +(const TVector2 &other) const
    {
        return TVector2(_x + other._x, _y + other._y);
    }

    template <typename T>
    inline TVector2<T> TVector2<T>::operator -(const TVector2 &other) const
    {
        return TVector2(_x - other._x, _y - other._y);
    }

    template <typename T>
    inline TVector2<T> TVector2<T>::operator *(T scalar) const
    {
        return TVector2(scalar * _x, scalar * _y);
    }

    template <typename T>
    inline TVector2<T> TVector2<T>::operator /(T scalar) const
    {
        TVector2 result;

        if (scalar != TReal<T>::ZERO)
        {
            result._x = _x / scalar;
            result._y = _y / scalar;
        }

        return result;
    }

    template <typename T>
    inline TVector2<T> TVector2<T>::operator *(const TVector2 &other) const
    {
        TVector2 v;
        v.x() = _x * other._x;
        v.y() = _y * other._y;
        return v;
    }

    template <typename T>
    inline TVector2<T> TVector2<T>::operator -() const
    {
        return TVector2(-_x, -_y);
    }

    template <typename T>
    inline TVector2<T> &TVector2<T>::operator +=(const TVector2 &other)
    {
        _x += other._x;
        _y += other._y;
        return *this;
    }

    template <typename T>
    inline TVector2<T> &TVector2<T>::operator -=(const TVector2 &other)
    {
        _x -= other._x;
        _y -= other._y;
        return *this;
    }

    template <typename T>
    inline TVector2<T> &TVector2<T>::operator *=(T scalar)
    {
        _x *= scalar;
        _y *= scalar;
        return *this;
    }

    template <typename T>
    inline TVector2<T> &TVector2<T>::operator *=(const TVector2 &other)
    {
        _x *= other._x;
        _y *= other._y;
        return *this;
    }

    template <typename T>
    inline TVector2<T> &TVector2<T>::operator /=(T scalar)
    {
        if (scalar != TReal<T>::ZERO)
        {
            _x = _x / scalar;
            _y = _y / scalar;
        }
        else
        {
            _x = TReal<T>::ZERO;
            _y = TReal<T>::ZERO;
        }

        return *this;
    }

    template <typename T>
    inline T TVector2<T>::length() const
    {
        return TMath<T>::sqrt(_x * _x + _y * _y);
    }

    template <typename T>
    inline T TVector2<T>::squaredLength() const
    {
        return _x * _x + _y * _y;
    }

    template <typename T>
    inline T TVector2<T>::distance(const TVector2 &other) const
    {
        return (*this - other).length();
    }

    template <typename T>
    inline T TVector2<T>::squaredDistance(const TVector2 &other) const
    {
        return (*this - other).squaredLength();
    }

    template <typename T>
    inline T TVector2<T>::dot(const TVector2 &other) const
    {
        return (_x * other._x + _y * other._y);
    }

    template <typename T>
    inline T TVector2<T>::cross(const TVector2 &other) const
    {
        return (_x * other._y - _y * other._x);
    }

    template <typename T>
    inline T TVector2<T>::normalize()
    {
        T len = length();

        if (len > TReal<T>::ZERO)
        {
            _x /= len;
            _y /= len;
        }
        else
        {
            len = TReal<T>::ZERO;
            _x = TReal<T>::ZERO;
            _y = TReal<T>::ZERO;
        }

        return len;
    }

    template <typename T>
    inline TVector2<T> TVector2<T>::perp() const
    {
        return TVector2(_x, -_y);
    }

    template <typename T>
    const TVector2<T> TVector2<T>::ZERO(0.0, 0.0);

    template <typename T>
    const TVector2<T> TVector2<T>::UNIT_X(1.0, 0.0);

    template <typename T>
    const TVector2<T> TVector2<T>::UNIT_Y(0.0, 1.0);

    template <typename T>
    const TVector2<T> TVector2<T>::NEGATIVE_UNIT_X(-1.0, 0.0);

    template <typename T>
    const TVector2<T> TVector2<T>::NEGATIVE_UNIT_Y(0.0, -1.0);
}
