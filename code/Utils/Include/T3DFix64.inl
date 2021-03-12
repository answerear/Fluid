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
    inline fix64::fix64() : m(0)
    {

    }

    inline fix64::fix64(const fix32 &fx)
    {
        float32_t value = (float32_t)fx;
        m = (int64_t)(value * (1 << DECIMAL_BITS));
    }

    inline fix64::fix64(float32_t value)
    {
//         float a = MIN_FLOAT_VALUE;
//         float b = MAX_FLOAT_VALUE;
        T3D_ASSERT(value <= MAX_FLOAT_VALUE && value >= MIN_FLOAT_VALUE);
        m = (int64_t)(value * (1 << DECIMAL_BITS));
    }

    inline fix64::fix64(float64_t value)
    {
        T3D_ASSERT(value <= MAX_FLOAT_VALUE && value >= MIN_FLOAT_VALUE);
        m = (int64_t)(value * (1 << DECIMAL_BITS));
    }

    inline fix64::fix64(int32_t value)
    {
        m = (((int64_t)value) << DECIMAL_BITS);
    }

    inline fix64::fix64(int64_t value)
    {
        T3D_ASSERT(value <= MAX_INT_VALUE && value >= MIN_INT_VALUE);
        m = (value << DECIMAL_BITS);
    }

    inline fix64::fix64(int64_t value, int32_t r)
    {
        m = value;
    }

    inline fix64::fix64(const fix64 &value)
    {
        m = value.m;
    }

    //--------------------------------------------------------------------------

    inline int64_t fix64::mantissa() const
    {
        return m;
    }

    inline int64_t &fix64::mantissa()
    {
        return m;
    }

    inline fix64 fix64::operator +() const
    {
        return fix64(m, 0);
    }

    inline fix64 fix64::operator -() const
    {
        return fix64(-m, 0);
    }

    //--------------------------------------------------------------------------

    inline bool fix64::eq_0() const
    {
        return (m == 0);
    }

    inline bool fix64::ne_0() const
    {
        return (m != 0);
    }

    inline bool fix64::gt_0() const
    {
        return (m > 0);
    }

    inline bool fix64::ge_0() const
    {
        return (m >= 0);
    }

    inline bool fix64::lt_0() const
    {
        return (m < 0);
    }

    inline bool fix64::le_0() const
    {
        return (m <= 0);
    }

    inline bool fix64::eq_1() const
    {
        return (m == (1LL << DECIMAL_BITS));
    }

    inline bool fix64::is_INF() const
    {
        return (m == 0x7FFFFFFFFFFFFFFFLL);
    }

    inline bool fix64::is_MINUSINF() const
    {
        return (m == 0x8000000000000000LL || m == 0x800000000000001LL);
    }

    inline bool fix64::is_integer() const
    {
        return ((m & ((1 << DECIMAL_BITS) - 1)) == 0);
    }

    //--------------------------------------------------------------------------

    inline fix64 &fix64::operator =(const fix64 &value)
    {
        m = value.m;
        return *this;
    }

    inline fix64 operator +(const fix64 &fx, const fix64 &gx)
    {
        T3D_ASSERT(((fx.m ^ -gx.m) & 0x8000000000000000LL)
            || !((fx.m ^ (fx.m + gx.m)) & 0x8000000000000000LL));
        return fix64(fx.m + gx.m, 0);
    }

    inline fix64 operator -(const fix64 &fx, const fix64 &gx)
    {
        T3D_ASSERT(((fx.m ^ -gx.m) & 0x8000000000000000LL)
            || !((fx.m ^ (fx.m + gx.m)) & 0x8000000000000000LL));
        return fix64(fx.m - gx.m, 0);
    }

    inline fix64 operator *(const fix64 &fx, const fix64 &gx)
    {
        if (fx.eq_0() || gx.eq_0())
            return fix64::ZERO;
        if (fx.eq_1())
            return gx;
        if (gx.eq_1())
            return fx;

        int64_t value = fx.m;
        value *= gx.m;

        T3D_ASSERT(value <= fix64::MAX_INT_VALUE
            && value >= fix64::MIN_INT_VALUE);
        return fix64(value, 0);
    }

    inline fix64 operator /(const fix64 &fx, const fix64 &gx)
    {
        if (fx.eq_0())
            return fix64::ZERO;
        if (gx.eq_1())
            return fx;
        if (gx.eq_0())
            return fix64::INF;

        int64_t value = fx.m;
        value <<= fix64::DECIMAL_BITS;
        value /= gx.m;

        T3D_ASSERT(value <= fix64::MAX_INT_VALUE
            && value >= fix64::MIN_INT_VALUE);
        return fix64(value, 0);
    }

    //--------------------------------------------------------------------------

    inline fix64 &fix64::operator +=(const fix64 &value)
    {
        return *this = *this + value;
    }

    inline fix64 &fix64::operator -=(const fix64 &value)
    {
        return *this = *this - value;
    }

    inline fix64 &fix64::operator *=(const fix64 &value)
    {
        return *this = *this * value;
    }

    inline fix64 &fix64::operator /=(const fix64 &value)
    {
        return *this = *this / value;
    }

    inline bool operator ==(const fix64 &fx, const fix64 &gx)
    {
        return fx.m == gx.m;
    }

    inline bool operator !=(const fix64 &fx, const fix64 &gx)
    {
        return fx.m != gx.m;
    }

    inline bool operator >=(const fix64 &fx, const fix64 &gx)
    {
        return fx.m >= gx.m;
    }

    inline bool operator <=(const fix64 &fx, const fix64 &gx)
    {
        return fx.m <= gx.m;
    }

    inline bool operator >(const fix64 &fx, const fix64 &gx)
    {
        return fx.m > gx.m;
    }

    inline bool operator <(const fix64 &fx, const fix64 &gx)
    {
        return fx.m < gx.m;
    }

    //--------------------------------------------------------------------------

    inline fix64 &fix64::operator =(int32_t value)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= MAX_INT_VALUE && i64 >= MIN_INT_VALUE);
        m = (i64 << DECIMAL_BITS);
        return *this;
    }

    inline fix64 operator +(const fix64 &fx, int32_t value)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(((fx.m ^ (i64 << fix64::DECIMAL_BITS))
            & 0x8000000000000000LL)
            || !((fx.m ^ (fx.m + (i64 << fix64::DECIMAL_BITS)))
                & 0x8000000000000000LL));
        return fix64(fx.m + (i64 << fix64::DECIMAL_BITS), 0);
    }

    inline fix64 operator +(int32_t value, const fix64 &fx)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(((fx.m ^ (i64 << fix64::DECIMAL_BITS))
            & 0x8000000000000000LL)
            || !((fx.m ^ (fx.m + (i64 << fix64::DECIMAL_BITS)))
                & 0x8000000000000000LL));
        return fix64(fx.m + (i64 << fix64::DECIMAL_BITS), 0);
    }

    inline fix64 operator - (const fix64 &fx, int32_t value)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(((fx.m ^ (i64 << fix64::DECIMAL_BITS))
            & 0x8000000000000000LL)
            || !((fx.m ^ (fx.m + (i64 << fix64::DECIMAL_BITS)))
                & 0x8000000000000000LL));
        return fix64(fx.m - (i64 << fix64::DECIMAL_BITS), 0);
    }

    inline fix64 operator -(int32_t value, const fix64 &fx)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(((fx.m ^ (i64 << fix64::DECIMAL_BITS)) 
            & 0x8000000000000000LL)
            || !((fx.m ^ (fx.m + (i64 << fix64::DECIMAL_BITS))) 
                & 0x8000000000000000LL));
        return fix64((i64 << fix64::DECIMAL_BITS) - fx.m, 0);
    }

    inline fix64 operator *(const fix64 &fx, int32_t value)
    {
        return fix64(fx.m * value, 0);
    }

    inline fix64 operator *(int32_t value, const fix64 &fx)
    {
        return fix64(fx.m * value, 0);
    }

    inline fix64 operator /(const fix64 &fx, int32_t value)
    {
        T3D_ASSERT(value <= fix64::MAX_INT_VALUE 
            && value >= fix64::MIN_INT_VALUE);

        if (value == 0)
        {
            return (fx.lt_0() ? fix64::MINUSINF : fix64::INF);
        }

        return fix64(fx.m / value, 0);
    }

    inline fix64 operator /(int32_t value, const fix64 &fx)
    {
        T3D_ASSERT(fx.ne_0());

        if (fx.eq_0())
        {
            T3D_ASSERT(value == 0);
            return (value < 0 ? fix64::MINUSINF : fix64::INF);
        }

        return fix64((((int64_t)value << fix64::DECIMAL_BITS) / fx.m), 0);
    }

    inline fix64 &fix64::operator +=(int32_t value)
    {
        return *this = *this + value;
    }

    inline fix64 &fix64::operator -=(int32_t value)
    {
        return *this = *this - value;
    }

    inline fix64 &fix64::operator *=(int32_t value)
    {
        return *this = *this * value;
    }

    inline fix64 &fix64::operator /=(int32_t value)
    {
        return *this = *this / value;
    }

    inline bool operator ==(const fix64 &fx, int32_t value)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return (fx.m == (i64 << fix64::DECIMAL_BITS));
    }

    inline bool operator ==(int32_t value, const fix64 &fx)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return (fx.m == (i64 << fix64::DECIMAL_BITS));
    }

    inline bool operator !=(const fix64 &fx, int32_t value)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return (fx.m != (i64 << fix64::DECIMAL_BITS));
    }

    inline bool operator !=(int32_t value, const fix64 &fx)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return (fx.m != (i64 << fix64::DECIMAL_BITS));
    }

    inline bool operator >=(const fix64 &fx, int32_t value)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return (fx.m >= (i64 << fix64::DECIMAL_BITS));
    }

    inline bool operator >=(int32_t value, const fix64 &fx)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return ((i64 << fix64::DECIMAL_BITS) >= fx.m);
    }

    inline bool operator <=(const fix64 &fx, int32_t value)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return (fx.m <= (i64 << fix64::DECIMAL_BITS));
    }

    inline bool operator <=(int32_t value, const fix64 &fx)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return ((i64 << fix64::DECIMAL_BITS) <= fx.m);
    }

    inline bool operator >(const fix64 &fx, int32_t value)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return (fx.m > (i64 << fix64::DECIMAL_BITS));
    }

    inline bool operator >(int32_t value, const fix64 &fx)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return ((i64 << fix64::DECIMAL_BITS) > fx.m);
    }

    inline bool operator <(const fix64 &fx, int32_t value)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return (fx.m < (i64 << fix64::DECIMAL_BITS));
    }

    inline bool operator <(int32_t value, const fix64 &fx)
    {
        int64_t i64 = (int64_t)value;
        T3D_ASSERT(i64 <= fix64::MAX_INT_VALUE && i64 >= fix64::MIN_INT_VALUE);
        return ((i64 << fix64::DECIMAL_BITS) < fx.m);
    }

    inline fix64::operator int32_t() const
    {
        return (int32_t)(m >> DECIMAL_BITS);
    }

    //--------------------------------------------------------------------------

    inline fix64 &fix64::operator =(float32_t value)
    {
        T3D_ASSERT(value <= MAX_INT_VALUE && value >= MIN_INT_VALUE);
        m = (int64_t)(value * (1 << DECIMAL_BITS));
        return *this;
    }

    inline fix64 operator +(const fix64 &fx, float32_t value)
    {
        return fx + fix64(value);
    }

    inline fix64 operator +(float32_t value, const fix64 &fx)
    {
        return fx + fix64(value);
    }

    inline fix64 operator -(const fix64 &fx, float32_t value)
    {
        return fx - fix64(value);
    }

    inline fix64 operator -(float32_t value, const fix64 &fx)
    {
        return fix64(value) - fx;
    }

    inline fix64 operator *(const fix64 &fx, float32_t value)
    {
        return fx * fix64(value);
    }

    inline fix64 operator *(float32_t value, const fix64 &fx)
    {
        return fx * fix64(value);
    }

    inline fix64 operator /(const fix64 &fx, float32_t value)
    {
        return fx / fix64(value);
    }

    inline fix64 operator /(float32_t value, const fix64 &fx)
    {
        return fix64(value) / fx;
    }

    inline fix64 &fix64::operator +=(float32_t value)
    {
        return *this = *this + value;
    }

    inline fix64 &fix64::operator -=(float32_t value)
    {
        return *this = *this - value;
    }

    inline fix64 &fix64::operator *=(float32_t value)
    {
        return *this = *this * value;
    }

    inline fix64 &fix64::operator /=(float32_t value)
    {
        return *this = *this / value;
    }

    inline bool operator ==(const fix64 &fx, float32_t value)
    {
        return (fx == fix64(value));
    }

    inline bool operator ==(float32_t value, const fix64 &fx)
    {
        return (fx == fix64(value));
    }

    inline bool operator !=(const fix64 &fx, float32_t value)
    {
        return (fx != fix64(value));
    }

    inline bool operator !=(float32_t value, const fix64 &fx)
    {
        return (fx != fix64(value));
    }

    inline bool operator >=(const fix64 &fx, float32_t value)
    {
        return (fx >= fix64(value));
    }

    inline bool operator >=(float32_t value, const fix64 &fx)
    {
        return (fix64(value) >= fx);
    }

    inline bool operator <=(const fix64 &fx, float32_t value)
    {
        return (fx <= fix64(value));
    }

    inline bool operator <=(float32_t value, const fix64 &fx)
    {
        return (fix64(value) <= fx);
    }

    inline bool operator >(const fix64 &fx, float32_t value)
    {
        return (fx > fix64(value));
    }

    inline bool operator >(float32_t value, const fix64 &fx)
    {
        return (fix64(value) > fx);
    }

    inline bool operator <(const fix64 &fx, float32_t value)
    {
        return (fx < fix64(value));
    }

    inline bool operator <(float32_t value, const fix64 &fx)
    {
        return (fix64(value) < fx);
    }

    inline fix64::operator float32_t() const
    {
        return (float32_t)m / 16777216.0f;
    }

    //--------------------------------------------------------------------------

    inline fix64 operator <<(const fix64 &a, int32_t b)
    {
        T3D_ASSERT(b >= 0);
        return fix64((a.m << b), 0);
    }

    inline fix64 operator >> (const fix64 &a, int32_t b)
    {
        T3D_ASSERT(b >= 0);
        return fix64((a.m >> b), 0);
    }

    inline fix64 &fix64::operator <<=(int32_t b)
    {
        return *this = *this << b;
    }

    inline fix64 &fix64::operator >>=(int32_t b)
    {
        return *this = *this >> b;
    }

    //--------------------------------------------------------------------------

    inline fix64::operator int64_t() const
    {
        return (m << DECIMAL_BITS);
    }

    //--------------------------------------------------------------------------

    inline fix64 &fix64::operator =(const fix32 &fx)
    {
        float32_t value = (float32_t)fx;
        m = (int64_t)(value * (1 << DECIMAL_BITS));
        return *this;
    }

    inline fix64::operator fix32() const
    {
        float32_t value = (float32_t)m / 16777216.0f;
        return fix32(value);
    }
}
