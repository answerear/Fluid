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
    //--------------------------------------------------------------------------

    inline bool Variant::isValid() const
    {
        return (mType != Type::E_NONE);
    }

    //--------------------------------------------------------------------------

    inline Variant::Variant()
        : mType(Type::E_NONE)
        , mValueSize(0)
    {
        memset(mValue, 0, sizeof(mValue));
    }

    inline Variant::Variant(bool value)
        : mType(Type::E_BOOL)
        , mValueSize(sizeof(bool))
    {
        memset(mValue, 0, sizeof(mValue));
        mBoolValue = value;
    }

    inline Variant::Variant(int8_t value)
        : mType(Type::E_INT8)
        , mValueSize(sizeof(int8_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mInt8Value = value;
    }

    inline Variant::Variant(uint8_t value)
        : mType(Type::E_UINT8)
        , mValueSize(sizeof(uint8_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mUInt8Value = value;
    }

    inline Variant::Variant(int16_t value)
        : mType(Type::E_INT16)
        , mValueSize(sizeof(int16_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mInt16Value = value;
    }

    inline Variant::Variant(uint16_t value)
        : mType(Type::E_UINT16)
        , mValueSize(sizeof(uint16_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mUInt16Value = value;
    }

    inline Variant::Variant(int32_t value)
        : mType(Type::E_INT32)
        , mValueSize(sizeof(int32_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mInt32Value = value;
    }

    inline Variant::Variant(uint32_t value)
        : mType(Type::E_UINT32)
        , mValueSize(sizeof(uint32_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mUInt32Value = value;
    }

    inline Variant::Variant(int64_t value)
        : mType(Type::E_INT64)
        , mValueSize(sizeof(int64_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mInt64Value = value;
    }

    inline Variant::Variant(uint64_t value)
        : mType(Type::E_UINT64)
        , mValueSize(sizeof(uint64_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mUInt64Value = value;
    }

    inline Variant::Variant(float32_t value)
        : mType(Type::E_FLOAT32)
        , mValueSize(sizeof(float32_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mFloat32Value = value;
    }

    inline Variant::Variant(float64_t value)
        : mType(Type::E_FLOAT64)
        , mValueSize(sizeof(float64_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mFloat64Value = value;
    }

    inline Variant::Variant(const fix32_t &value)
        : mType(Type::E_FIX32)
        , mValueSize(sizeof(fix32_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mFix32Value = value;
    }

    inline Variant::Variant(const fix64_t &value)
        : mType(Type::E_FIX64)
        , mValueSize(sizeof(fix64_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mFix64Value = value;
    }

    inline Variant::Variant(char value)
        : mType(Type::E_CHAR)
        , mValueSize(sizeof(char))
    {
        memset(mValue, 0, sizeof(mValue));
        mCharValue = value;
    }

    inline Variant::Variant(wchar_t value)
        : mType(Type::E_WCHAR)
        , mValueSize(sizeof(wchar_t))
    {
        memset(mValue, 0, sizeof(mValue));
        mWCharValue = value;
    }

    inline Variant::Variant(const char *value)
        : mType(Type::E_STRING)
        , mValueSize(0)
    {
        memset(mValue, 0, sizeof(mValue));
        size_t len = strlen(value);
        mValueSize = (len > 0 ? len + 1 : 1);
        mStrValue = new char[mValueSize];
        memcpy(mStrValue, value, mValueSize - 1);
        mStrValue[mValueSize - 1] = 0;
    }

    inline Variant::Variant(const String &value)
        : mType(Type::E_STRING)
        , mValueSize(0)
    {
        memset(mValue, 0, sizeof(mValue));
        mValueSize = (value.length() > 0 ? value.length() + 1 : 1);
        mStrValue = new char[mValueSize];
        memcpy(mStrValue, value.c_str(), mValueSize - 1);
        mStrValue[mValueSize - 1] = 0;
    }

    inline Variant::Variant(const VariantArray &value)
        : mType(Type::E_ARRAY)
        , mValueSize(sizeof(VariantArray))
    {
        memset(mValue, 0, sizeof(mValue));
        mArrayValue = new VariantArray(value);
    }

    inline Variant::Variant(const VariantList &value)
        : mType(Type::E_LIST)
        , mValueSize(sizeof(VariantList))
    {
        memset(mValue, 0, sizeof(mValue));
        mListValue = new VariantList(value);
    }

    inline Variant::Variant(const VariantMap &value)
        : mType(Type::E_MAP)
        , mValueSize(sizeof(VariantMap))
    {
        memset(mValue, 0, sizeof(mValue));
        mMapValue = new VariantMap(value);
    }

    //--------------------------------------------------------------------------

    inline Variant::Variant(const Variant &other)
    {
        copy(other);
    }

    inline Variant &Variant::operator =(const Variant &other)
    {
        copy(other);
        return *this;
    }

    //--------------------------------------------------------------------------

    inline Variant::~Variant()
    {
        releaseMemory();
    }

    //--------------------------------------------------------------------------

    inline void Variant::setBool(bool value)
    {
        releaseMemory();
        mType = Type::E_BOOL;
        mValueSize = sizeof(bool);
        mBoolValue = value;
    }

    inline void Variant::setInt8(int8_t value)
    {
        releaseMemory();
        mType = Type::E_INT8;
        mValueSize = sizeof(int8_t);
        mInt8Value = value;
    }

    inline void Variant::setUInt8(uint8_t value)
    {
        releaseMemory();
        mType = Type::E_UINT8;
        mValueSize = sizeof(uint8_t);
        mUInt8Value = value;
    }

    inline void Variant::setInt16(int16_t value)
    {
        releaseMemory();
        mType = Type::E_INT16;
        mValueSize = sizeof(int16_t);
        mInt16Value = value;
    }

    inline void Variant::setUInt16(uint16_t value)
    {
        releaseMemory();
        mType = Type::E_UINT16;
        mValueSize = sizeof(uint16_t);
        mUInt16Value = value;
    }

    inline void Variant::setInt32(int32_t value)
    {
        releaseMemory();
        mType = Type::E_INT32;
        mValueSize = sizeof(int32_t);
        mInt32Value = value;
    }

    inline void Variant::setUInt32(uint32_t value)
    {
        releaseMemory();
        mType = Type::E_UINT32;
        mValueSize = sizeof(uint32_t);
        mUInt32Value = value;
    }

    inline void Variant::setInt64(int64_t value)
    {
        releaseMemory();
        mType = Type::E_INT64;
        mValueSize = sizeof(int64_t);
        mInt64Value = value;
    }

    inline void Variant::setUInt64(uint64_t value)
    {
        releaseMemory();
        mType = Type::E_UINT64;
        mValueSize = sizeof(uint64_t);
        mUInt64Value = value;
    }

    inline void Variant::setLong(long_t value)
    {
        releaseMemory();
        mType = Type::E_LONG;
        mValueSize = sizeof(long_t);
        mLongValue = value;
    }

    inline void Variant::setULong(ulong_t value)
    {
        releaseMemory();
        mType = Type::E_ULONG;
        mValueSize = sizeof(ulong_t);
        mULongValue = value;
    }

    inline void Variant::setFloat32(float32_t value)
    {
        releaseMemory();
        mType = Type::E_FLOAT32;
        mValueSize = sizeof(float32_t);
        mFloat32Value = value;
    }

    inline void Variant::setFloat64(float64_t value)
    {
        releaseMemory();
        mType = Type::E_FLOAT64;
        mValueSize = sizeof(float64_t);
        mFloat64Value = value;
    }

    inline void Variant::setFix32(const fix32_t &value)
    {
        releaseMemory();
        mType = Type::E_FIX32;
        mValueSize = sizeof(fix32_t);
        mFix32Value = value;
    }

    inline void Variant::setFix64(const fix64_t &value)
    {
        releaseMemory();
        mType = Type::E_FIX64;
        mValueSize = sizeof(fix64_t);
        mFix64Value = value;
    }

    inline void Variant::setChar(char value)
    {
        releaseMemory();
        mType = Type::E_CHAR;
        mValueSize = sizeof(char);
        mCharValue = value;
    }

    inline void Variant::setWChar(wchar_t value)
    {
        releaseMemory();
        mType = Type::E_WCHAR;
        mValueSize = sizeof(wchar_t);
        mWCharValue = value;
    }

    inline void Variant::setString(const String &value)
    {
        releaseMemory();
        mType = Type::E_STRING;
        mValueSize = (value.length() > 0 ? value.length() + 1 : 1);
        mStrValue = new char[mValueSize];
        memcpy(mStrValue, value.c_str(), mValueSize - 1);
        mStrValue[mValueSize - 1] = 0;
    }

    inline void Variant::setArray(const VariantArray &value)
    {
        if (mType != Type::E_ARRAY)
        {
            releaseMemory();
            mType = Type::E_ARRAY;
            mValueSize = sizeof(VariantArray);
            mArrayValue = new VariantArray(value);
        }
        else
        {
            mArrayValue->assign(value.begin(), value.end());
        }
    }

    inline void Variant::setList(const VariantList &value)
    {
        if (mType != Type::E_LIST)
        {
            releaseMemory();
            mType = Type::E_LIST;
            mValueSize = sizeof(VariantList);
            mListValue = new VariantList(value);
        }
        else
        {
            mListValue->assign(value.begin(), value.end());
        }
    }

    inline void Variant::setMap(const VariantMap &value)
    {
        if (mType != Type::E_MAP)
        {
            releaseMemory();
            mType = Type::E_MAP;
            mValueSize = sizeof(VariantMap);
            mMapValue = new VariantMap(value);
        }
        else
        {
            mMapValue->clear();
            mMapValue->insert(value.begin(), value.end());
        }
    }

    //--------------------------------------------------------------------------

    inline bool Variant::isNumber() const
    {
        return (Type::E_INT8 == mType || Type::E_UINT8 == mType
            || Type::E_INT16 == mType || Type::E_UINT16 == mType
            || Type::E_INT32 == mType || Type::E_UINT32 == mType
            || Type::E_INT64 == mType || Type::E_UINT64 == mType
            || Type::E_LONG == mType || Type::E_ULONG == mType
            || Type::E_FLOAT32 == mType || Type::E_FLOAT64 == mType
            || Type::E_FIX32 == mType || Type::E_FIX64 == mType
            || Type::E_CHAR == mType || Type::E_WCHAR == mType
            || Type::E_BOOL == mType);
    }

    //--------------------------------------------------------------------------

    inline bool Variant::boolValue(bool *ok /* = nullptr */) const
    {
        bool val = false;
        bool ret = false;

        if (isNumber())
        {
            val = mBoolValue;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline int8_t Variant::int8Value(bool *ok /* = nullptr */) const
    {
        int8_t val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mInt8Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline uint8_t Variant::uint8Value(bool *ok /* = nullptr */) const
    {
        uint8_t val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mUInt8Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline int16_t Variant::int16Value(bool *ok /* = nullptr */) const
    {
        int16_t val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mInt16Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline uint16_t Variant::uint16Value(bool *ok /* = nullptr */) const
    {
        uint16_t val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mUInt16Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;

    }

    inline int32_t Variant::int32Value(bool *ok /* = nullptr */) const
    {
        int32_t val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mInt32Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline uint32_t Variant::uint32Value(bool *ok /* = nullptr */) const
    {
        uint32_t val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mUInt32Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline int64_t Variant::int64Value(bool *ok /* = nullptr */) const
    {
        int64_t val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mInt64Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline uint64_t Variant::uint64Value(bool *ok /* = nullptr */) const
    {
        uint64_t val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mUInt64Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline long_t Variant::longValue(bool *ok /* = nullptr */) const
    {
        long_t val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mLongValue;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline ulong_t Variant::ulongValue(bool *ok /* = nullptr */) const
    {
        ulong_t val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mULongValue;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline float32_t Variant::float32Value(bool *ok /* = nullptr */) const
    {
        float32_t val = 0.0f;
        bool ret = false;

        if (isNumber())
        {
            val = mFloat32Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline float64_t Variant::float64Value(bool *ok /* = nullptr */) const
    {
        float64_t val = 0.0;
        bool ret = false;

        if (isNumber())
        {
            val = mFloat64Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline fix32_t Variant::fix32Value(bool *ok /* = nullptr */) const
    {
        fix32_t val = fix32_t::ZERO;
        bool ret = false;

        if (isNumber())
        {
            val = mFix32Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline fix64_t Variant::fix64Value(bool *ok /* = nullptr */) const
    {
        fix64_t val = fix64_t::ZERO;
        bool ret = false;

        if (isNumber())
        {
            val = mFix64Value;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline char Variant::charValue(bool *ok /* = nullptr */) const
    {
        char val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mCharValue;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline wchar_t Variant::wcharValue(bool *ok /* = nullptr */) const
    {
        wchar_t val = 0;
        bool ret = false;

        if (isNumber())
        {
            val = mWCharValue;
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline String Variant::stringValue(bool *ok /* = nullptr */) const
    {
        String val;
        bool ret = false;

        if (Type::E_STRING == mType)
        {
            val.assign(mStrValue);
            ret = true;
        }

        if (ok != nullptr)
            *ok = ret;

        return val;
    }

    inline const VariantArray &Variant::arrayValue(bool *ok /* = nullptr */) const
    {
        if (Type::E_ARRAY == mType)
        {
            if (ok != nullptr)
                *ok = true;

            return *mArrayValue;
        }

        if (ok != nullptr)
            *ok = false;

        return INVALID_ARRAY;
    }

    inline const VariantList &Variant::listValue(bool *ok /* = nullptr */) const
    {
        if (Type::E_LIST == mType)
        {
            if (ok != nullptr)
                *ok = true;

            return *mListValue;
        }

        if (ok != nullptr)
            *ok = false;

        return INVALID_LIST;
    }

    inline const VariantMap &Variant::mapValue(bool *ok /* = nullptr */) const
    {
        if (Type::E_MAP == mType)
        {
            if (ok != nullptr)
                *ok = true;

            return *mMapValue;
        }

        if (ok != nullptr)
            *ok = false;

        return INVALID_MAP;
    }

    inline VariantArray &Variant::arrayValue(bool *ok /* = nullptr */)
    {
        if (Type::E_ARRAY == mType)
        {
            if (ok != nullptr)
                *ok = true;

            return *mArrayValue;
        }

        if (ok != nullptr)
            *ok = false;

        return INVALID_ARRAY;
    }

    inline VariantList &Variant::listValue(bool *ok /* = nullptr */)
    {
        if (Type::E_LIST == mType)
        {
            if (ok != nullptr)
                *ok = true;

            return *mListValue;
        }

        if (ok != nullptr)
            *ok = false;

        return INVALID_LIST;
    }

    inline VariantMap &Variant::mapValue(bool *ok /* = nullptr */)
    {
        if (Type::E_MAP == mType)
        {
            if (ok != nullptr)
                *ok = true;

            return *mMapValue;
        }

        if (ok != nullptr)
            *ok = false;

        return INVALID_MAP;
    }

    //--------------------------------------------------------------------------

    inline bool Variant::operator ==(const Variant &other) const
    {
        return (compare(other) == 0);
    }

    inline bool Variant::operator !=(const Variant &other) const
    {
        return (compare(other) != 0);
    }

    inline bool Variant::operator <(const Variant &other) const
    {
        return (compare(other) < 0);
    }

    inline bool Variant::operator <=(const Variant &other) const
    {
        return (compare(other) <= 0);
    }

    inline bool Variant::operator >(const Variant &other) const
    {
        return (compare(other) > 0);
    }

    inline bool Variant::operator >=(const Variant &other) const
    {
        return (compare(other) >= 0);
    }

    //--------------------------------------------------------------------------

    inline Variant::Type Variant::valueType() const
    {
        return mType;
    }

    inline size_t Variant::valueSize() const
    {
        return mValueSize;
    }
}
