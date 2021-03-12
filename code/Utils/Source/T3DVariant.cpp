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

#include "T3DVariant.h"


namespace Tiny3D
{
    VariantArray    Variant::INVALID_ARRAY;
    VariantList     Variant::INVALID_LIST;
    VariantMap      Variant::INVALID_MAP;

    void Variant::copy(const Variant &other)
    {
        mType = other.mType;
        mValueSize = other.mValueSize;

        switch (mType)
        {
        case Type::E_BOOL:
        case Type::E_INT8:
        case Type::E_UINT8:
        case Type::E_INT16:
        case Type::E_UINT16:
        case Type::E_INT32:
        case Type::E_UINT32:
        case Type::E_INT64:
        case Type::E_UINT64:
        case Type::E_LONG:
        case Type::E_ULONG:
        case Type::E_FLOAT32:
        case Type::E_FLOAT64:
        case Type::E_FIX32:
        case Type::E_FIX64:
        case Type::E_CHAR:
        case Type::E_WCHAR:
            {
                memcpy(mValue, other.mValue, mValueSize);
            }
            break;
        case Type::E_STRING:
            {
                mStrValue = new char[mValueSize];
                memcpy(mStrValue, other.mStrValue, mValueSize);
            }
            break;
        case Type::E_ARRAY:
            {
                mArrayValue = new VariantArray(*other.mArrayValue);
            }
            break;
        case Type::E_LIST:
            {
                mListValue = new VariantList(*other.mListValue);
            }
            break;
        case Type::E_MAP:
            {
                mMapValue = new VariantMap(*other.mMapValue);
            }
            break;
        default:
            break;
        }
    }

    void Variant::releaseMemory()
    {
        switch (mType)
        {
        case Type::E_STRING:
            {
                delete[]mStrValue;
                mStrValue = nullptr;
            }
            break;
        case Type::E_ARRAY:
            {
                delete mArrayValue;
                mArrayValue = nullptr;
            }
            break;
        case Type::E_LIST:
            {
                delete mListValue;
                mListValue = nullptr;
            }
            break;
        case Type::E_MAP:
            {
                delete mMapValue;
                mMapValue = nullptr;
            }
            break;
        default:
            break;
        }

        memset(mValue, 0, sizeof(mValue));
    }

    int32_t Variant::compare(const Variant &other) const
    {
        int32_t ret = 0;
        if (mType == other.mType)
        {
            if (mType == Type::E_STRING)
            {
                size_t size = std::max(mValueSize, other.mValueSize);
                ret = strncmp(mStrValue, other.mStrValue, size);
            }
            else if (mType == Type::E_ARRAY)
            {
                if (*mArrayValue < *other.mArrayValue)
                    ret = -1;
                else if (*mArrayValue > *other.mArrayValue)
                    ret = 1;
                else
                    ret = 0;
            }
            else if (mType == Type::E_LIST)
            {
                if (*mListValue < *other.mListValue)
                    ret = -1;
                else if (*mListValue > *other.mListValue)
                    ret = 1;
                else
                    ret = 0;
            }
            else if (mType == Type::E_MAP)
            {
                if (*mMapValue < *other.mMapValue)
                    ret = -1;
                else if (*mMapValue > *other.mMapValue)
                    ret = 1;
                else
                    ret = 0;
            }
            else
            {
                ret = memcmp(mValue, other.mValue, mValueSize);
            }
        }
        else
        {
            ret = (static_cast<int32_t>(mType) 
                - static_cast<int32_t>(other.mType));
        }

        return ret;
    }
}
