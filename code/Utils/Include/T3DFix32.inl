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
    inline fix32::fix32() : m(0)
    {

    }

    inline fix32::fix32(float32_t value)
    {
        T3D_ASSERT(value <= MAX_FLOAT_VALUE &&value >= MIN_FLOAT_VALUE);
        m = (int32_t)(value * (1 << DECIMAL_BITS));
    }

    inline fix32::fix32(float64_t value)
    {
        T3D_ASSERT(value <= MAX_FLOAT_VALUE &&value >= MIN_FLOAT_VALUE);
        m = (int32_t)(value * (1 << DECIMAL_BITS));
    }

    inline fix32::fix32(int32_t value)
    {
        T3D_ASSERT(value <= MAX_INT_VALUE && value >= MIN_INT_VALUE);
        m = (value << DECIMAL_BITS);
    }

    inline fix32::fix32(int64_t value)
    {
        T3D_ASSERT(value <= 8796093022207 && value >= -8796093022208);
        m = (int32_t)((value + 2048) >> DECIMAL_BITS);
    }

    inline fix32::fix32(int32_t value, int32_t r)
    {
        m = value;
    }

    inline fix32::fix32(const fix32 &value)
    {
        m = value.m;
    }

    //--------------------------------------------------------------------------

    inline int32_t fix32::mantissa() const
    {
        return m;
    }

    inline int32_t &fix32::mantissa()
    {
        return m;
    }

    inline fix32 fix32::operator +() const
    {
        return fix32(m, 0);
    }

    inline fix32 fix32::operator -() const
    {
        return fix32(-m, 0);
    }

    //--------------------------------------------------------------------------

    inline bool fix32::eq_0() const
    {
        return (m == 0);
    }

    inline bool fix32::ne_0() const
    {
        return (m != 0);
    }

    inline bool fix32::gt_0() const
    {
        return (m > 0);
    }

    inline bool fix32::ge_0() const
    {
        return (m >= 0);
    }

    inline bool fix32::lt_0() const
    {
        return (m < 0);
    }

    inline bool fix32::le_0() const
    {
        return (m <= 0);
    }

    inline bool fix32::eq_1() const
    {
        return (m == (1 << DECIMAL_BITS));
    }

    inline bool fix32::is_INF() const
    {
        return (m == 0x7FFFFFFF);
    }

    inline bool fix32::is_MINUSINF() const
    {
        return (m == 0x80000000 || m == 0x80000001);
    }

    inline bool fix32::is_integer() const
    {
        return ((m & ((1 << DECIMAL_BITS) - 1)) == 0);
    }

    //--------------------------------------------------------------------------

    inline fix32 &fix32::operator =(const fix32 &value)
    {
        m = value.m;
        return *this;
    }

    inline fix32 operator +(const fix32 &fx, const fix32 &gx)
    {
        T3D_ASSERT(((fx.m ^ -gx.m) & 0x80000000) 
            || !((fx.m ^ (fx.m + gx.m)) & 0x80000000));
        return fix32(fx.m + gx.m, 0);
    }

    inline fix32 operator -(const fix32 &fx, const fix32 &gx)
    {
        T3D_ASSERT(((fx.m ^ -gx.m) & 0x80000000) 
            || !((fx.m ^ (fx.m + gx.m)) & 0x80000000));
        return fix32(fx.m - gx.m, 0);
    }

    inline fix32 operator *(const fix32 &fx, const fix32 &gx)
    {
        if (fx.eq_0() || gx.eq_0())
            return fix32::ZERO;
        if (fx.eq_1())
            return gx;
        if (gx.eq_1())
            return fx;

        int64_t value = fx.m;
        value *= gx.m;

        T3D_ASSERT(value <= 8796093022207LL && value >= -8796093022208LL);
        return fix32(value);
    }

    inline fix32 operator /(const fix32 &fx, const fix32 &gx)
    {
        if (fx.eq_0())
            return fix32::ZERO;
        if (gx.eq_1())
            return fx;
        if (gx.eq_0())
            return fix32::INF;

        int64_t value = fx.m;
        value <<= fix32::DECIMAL_BITS;
        value /= gx.m;

        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return fix32((int32_t)value, 0);
    }

    //--------------------------------------------------------------------------

    inline fix32 &fix32::operator +=(const fix32 &value)
    {
        return *this = *this + value;
    }

    inline fix32 &fix32::operator -=(const fix32 &value)
    {
        return *this = *this - value;
    }

    inline fix32 &fix32::operator *=(const fix32 &value)
    {
        return *this = *this * value;
    }

    inline fix32 &fix32::operator /=(const fix32 &value)
    {
        return *this = *this / value;
    }

    inline bool operator ==(const fix32 &fx, const fix32 &gx)
    {
        return fx.m == gx.m;
    }

    inline bool operator !=(const fix32 &fx, const fix32 &gx)
    {
        return fx.m != gx.m;
    }

    inline bool operator >=(const fix32 &fx, const fix32 &gx)
    {
        return fx.m >= gx.m;
    }

    inline bool operator <=(const fix32 &fx, const fix32 &gx)
    {
        return fx.m <= gx.m;
    }

    inline bool operator >(const fix32 &fx, const fix32 &gx)
    {
        return fx.m > gx.m;
    }

    inline bool operator <(const fix32 &fx, const fix32 &gx)
    {
        return fx.m < gx.m;
    }

    //--------------------------------------------------------------------------

    inline fix32 &fix32::operator =(int32_t value)
    {
        T3D_ASSERT(value <= MAX_INT_VALUE && value >= MIN_INT_VALUE);
        m = (value << DECIMAL_BITS);
        return *this;
    }

    inline fix32 operator +(const fix32 &fx, int32_t value)
    {
        T3D_ASSERT(((fx.m ^ (value << fix32::DECIMAL_BITS)) & 0x80000000)
            || !((fx.m ^ (fx.m + (value << fix32::DECIMAL_BITS))) & 0x80000000));
        return fix32(fx.m + (value << fix32::DECIMAL_BITS), 0);
    }

    inline fix32 operator +(int32_t value, const fix32 &fx)
    {
        T3D_ASSERT(((fx.m ^ (value << fix32::DECIMAL_BITS)) & 0x80000000)
            || !((fx.m ^ (fx.m + (value << fix32::DECIMAL_BITS))) & 0x80000000));
        return fix32(fx.m + (value << fix32::DECIMAL_BITS), 0);
    }

    inline fix32 operator - (const fix32 &fx, int32_t value)
    {
        T3D_ASSERT(((fx.m ^ (value << fix32::DECIMAL_BITS)) & 0x80000000)
            || !((fx.m ^ (fx.m + (value << fix32::DECIMAL_BITS))) & 0x80000000));
        return fix32(fx.m - (value << fix32::DECIMAL_BITS), 0);
    }

    inline fix32 operator -(int32_t value, const fix32 &fx)
    {
        T3D_ASSERT(((fx.m ^ (value << fix32::DECIMAL_BITS)) & 0x80000000)
            || !((fx.m ^ (fx.m + (value << fix32::DECIMAL_BITS))) & 0x80000000));
        return fix32((value << fix32::DECIMAL_BITS) - fx.m, 0);
    }

    inline fix32 operator *(const fix32 &fx, int32_t value)
    {
#ifdef T3D_DEBUG
        int32_t result = (int32_t)(((int64_t)fx.m * value) >> 44);
        T3D_ASSERT(result == 0 || result == -1);
#endif
        return fix32(fx.m * value, 0);
    }

    inline fix32 operator *(int32_t value, const fix32 &fx)
    {
#ifdef T3D_DEBUG
        int32_t result = (int32_t)(((int64_t)fx.m * value) >> 44);
        T3D_ASSERT(result == 0 || result == -1);
#endif
        return fix32(fx.m * value, 0);
    }

    inline fix32 operator /(const fix32 &fx, int32_t value)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        
        if (value == 0)
        {
            return (fx.lt_0() ? fix32::MINUSINF : fix32::INF);
        }
        
        return fix32(fx.m / value, 0);
    }

    inline fix32 operator /(int32_t value, const fix32 &fx)
    {
        T3D_ASSERT(fx.ne_0());
        
        if (fx.eq_0()) 
        {
            T3D_ASSERT(value == 0);
            return (value < 0 ? fix32::MINUSINF : fix32::INF);
        }
        
        return fix32((int32_t)(((int64_t)value << fix32::DECIMAL_BITS) 
            / fx.m), 0);
    }

    inline fix32 &fix32::operator +=(int32_t value)
    {
        return *this = *this + value;
    }

    inline fix32 &fix32::operator -=(int32_t value)
    {
        return *this = *this - value;
    }

    inline fix32 &fix32::operator *=(int32_t value)
    {
        return *this = *this * value;
    }

    inline fix32 &fix32::operator /=(int32_t value)
    {
        return *this = *this / value;
    }

    inline bool operator ==(const fix32 &fx, int32_t value)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return (fx.m == (value << fix32::DECIMAL_BITS));
    }

    inline bool operator ==(int32_t value, const fix32 &fx)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return (fx.m == (value << fix32::DECIMAL_BITS));
    }

    inline bool operator !=(const fix32 &fx, int32_t value)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return (fx.m != (value << fix32::DECIMAL_BITS));
    }

    inline bool operator !=(int32_t value, const fix32 &fx)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return (fx.m != (value << fix32::DECIMAL_BITS));
    }

    inline bool operator >=(const fix32 &fx, int32_t value)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return (fx.m >= (value << fix32::DECIMAL_BITS));
    }

    inline bool operator >=(int32_t value, const fix32 &fx)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return ((value << fix32::DECIMAL_BITS) >= fx.m);
    }

    inline bool operator <=(const fix32 &fx, int32_t value)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return (fx.m <= (value << fix32::DECIMAL_BITS));
    }

    inline bool operator <=(int32_t value, const fix32 &fx)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return ((value << fix32::DECIMAL_BITS) <= fx.m);
    }

    inline bool operator >(const fix32 &fx, int32_t value)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return (fx.m > (value << fix32::DECIMAL_BITS));
    }

    inline bool operator >(int32_t value, const fix32 &fx)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return ((value << fix32::DECIMAL_BITS) > fx.m);
    }

    inline bool operator <(const fix32 &fx, int32_t value)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return (fx.m < (value << fix32::DECIMAL_BITS));
    }

    inline bool operator <(int32_t value, const fix32 &fx)
    {
        T3D_ASSERT(value <= fix32::MAX_INT_VALUE 
            && value >= fix32::MIN_INT_VALUE);
        return ((value << fix32::DECIMAL_BITS) < fx.m);
    }

    inline fix32::operator int32_t() const
    {
        return (m >> 12);
    }

    //--------------------------------------------------------------------------

    inline fix32 &fix32::operator =(float32_t value)
    {
        T3D_ASSERT(value <= fix32::MAX_FLOAT_VALUE 
            && value >= fix32::MIN_FLOAT_VALUE);
        m = (int32_t)(value * (1 << fix32::DECIMAL_BITS));
        return *this;
    }

    inline fix32 operator +(const fix32 &fx, float32_t value)
    {
        return fx + fix32(value);
    }

    inline fix32 operator +(float32_t value, const fix32 &fx)
    {
        return fx + fix32(value);
    }

    inline fix32 operator -(const fix32 &fx, float32_t value)
    {
        return fx - fix32(value);
    }

    inline fix32 operator -(float32_t value, const fix32 &fx)
    {
        return fix32(value) - fx;
    }

    inline fix32 operator *(const fix32 &fx, float32_t value)
    {
        return fx * fix32(value);
    }

    inline fix32 operator *(float32_t value, const fix32 &fx)
    {
        return fx * fix32(value);
    }

    inline fix32 operator /(const fix32 &fx, float32_t value)
    {
        return fx / fix32(value);
    }

    inline fix32 operator /(float32_t value, const fix32 &fx)
    {
        return fix32(value) / fx;
    }

    inline fix32 &fix32::operator +=(float32_t value)
    {
        return *this = *this + value;
    }

    inline fix32 &fix32::operator -=(float32_t value)
    {
        return *this = *this - value;
    }

    inline fix32 &fix32::operator *=(float32_t value)
    {
        return *this = *this * value;
    }

    inline fix32 &fix32::operator /=(float32_t value)
    {
        return *this = *this / value;
    }

    inline bool operator ==(const fix32 &fx, float32_t value)
    {
        return (fx == fix32(value));
    }

    inline bool operator ==(float32_t value, const fix32 &fx)
    {
        return (fx == fix32(value));
    }

    inline bool operator !=(const fix32 &fx, float32_t value)
    {
        return (fx != fix32(value));
    }

    inline bool operator !=(float32_t value, const fix32 &fx)
    {
        return (fx != fix32(value));
    }

    inline bool operator >=(const fix32 &fx, float32_t value)
    {
        return (fx >= fix32(value));
    }

    inline bool operator >=(float32_t value, const fix32 &fx)
    {
        return (fix32(value) >= fx);
    }

    inline bool operator <=(const fix32 &fx, float32_t value)
    {
        return (fx <= fix32(value));
    }

    inline bool operator <=(float32_t value, const fix32 &fx)
    {
        return (fix32(value) <= fx);
    }

    inline bool operator >(const fix32 &fx, float32_t value)
    {
        return (fx > fix32(value));
    }

    inline bool operator >(float32_t value, const fix32 &fx)
    {
        return (fix32(value) > fx);
    }

    inline bool operator <(const fix32 &fx, float32_t value)
    {
        return (fx < fix32(value));
    }

    inline bool operator <(float32_t value, const fix32 &fx)
    {
        return (fix32(value) < fx);
    }

    inline fix32::operator float32_t() const
    {
        return (float32_t)m / float32_t(1 << DECIMAL_BITS);
    }

    //--------------------------------------------------------------------------

    inline fix32 operator <<(const fix32 &a, int32_t b)
    {
        T3D_ASSERT(b >= 0);
        return fix32((a.m << b), 0);
    }

    inline fix32 operator >> (const fix32 &a, int32_t b)
    {
        T3D_ASSERT(b >= 0);
        return fix32((a.m >> b), 0);
    }

    inline fix32 &fix32::operator <<=(int32_t b)
    {
        return *this = *this << b;
    }

    inline fix32 &fix32::operator >>=(int32_t b)
    {
        return *this = *this >> b;
    }

    //--------------------------------------------------------------------------

    inline fix32::operator int64_t() const
    {
        return ((int64_t)m << DECIMAL_BITS);
    }
}
