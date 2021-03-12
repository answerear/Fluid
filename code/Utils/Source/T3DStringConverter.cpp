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


#include "T3DStringConverter.h"
#include "T3DStringUtil.h"
#include <sstream>


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    String StringConverter::toString(float32_t val,
        uint16_t precision /* = 6 */,
        uint16_t width /* = 0 */,
        char fill /* = ' ' */,
        std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
    {
        std::stringstream ss;
        ss.precision(precision);
        ss.width(width);
        ss.fill(fill);
        if (flags)
            ss.setf(flags);
        ss << val;
        return ss.str();
    }

    //--------------------------------------------------------------------------

    String StringConverter::toString(float64_t val,
        uint16_t precision /* = 6 */,
        uint16_t width /* = 0 */,
        char fill /* = ' ' */,
        std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
    {
        std::stringstream ss;
        ss.precision(precision);
        ss.width(width);
        ss.fill(fill);
        if (flags)
            ss.setf(flags);
        ss << val;
        return ss.str();
    }

    //--------------------------------------------------------------------------

    String StringConverter::toString(fix32_t val,
        uint16_t precision /* = 6 */,
        uint16_t width /* = 0 */,
        char fill /* = ' ' */,
        std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
    {
        std::stringstream ss;
        ss.precision(precision);
        ss.width(width);
        ss.fill(fill);
        if (flags)
            ss.setf(flags);
        ss << (float32_t)val;
        return ss.str();
    }

    //--------------------------------------------------------------------------

    String StringConverter::toString(fix64_t val,
        uint16_t precision /* = 6 */,
        uint16_t width /* = 0 */,
        char fill /* = ' ' */,
        std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
    {
        std::stringstream ss;
        ss.precision(precision);
        ss.width(width);
        ss.fill(fill);
        if (flags)
            ss.setf(flags);
        ss << (float32_t)val;
        return ss.str();
    }

    //--------------------------------------------------------------------------

    String StringConverter::toString(int32_t val,
        uint16_t width /* = 0 */, char fill /* = ' ' */,
        std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
    {
        std::stringstream ss;
        ss.width(width);
        ss.fill(fill);
        if (flags)
            ss.setf(flags);
        ss << val;
        return ss.str();
    }

    //--------------------------------------------------------------------------

    String StringConverter::toString(uint32_t val,
        uint16_t width /* = 0 */, char fill /* = ' ' */,
        std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
    {
        std::stringstream ss;
        ss.width(width);
        ss.fill(fill);
        if (flags)
            ss.setf(flags);
        ss << val;
        return ss.str();
    }

    //--------------------------------------------------------------------------

//     String StringConverter::toString(size_t val,
//         uint16_t width /* = 0 */, char fill /* = ' ' */,
//         std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
//     {
//         std::stringstream ss;
//         ss.width(width);
//         ss.fill(fill);
//         if (flags)
//             ss.setf(flags);
//         ss << val;
//         return ss.str();
//     }

    //--------------------------------------------------------------------------

    String StringConverter::toString(long_t val,
        uint16_t width /* = 0 */, char fill /* = ' ' */,
        std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
    {
        std::stringstream ss;
        ss.width(width);
        ss.fill(fill);
        if (flags)
            ss.setf(flags);
        ss << val;
        return ss.str();
    }

    //--------------------------------------------------------------------------

    String StringConverter::toString(ulong_t val,
        uint16_t width /* = 0 */, char fill /* = ' ' */,
        std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
    {
        std::stringstream ss;
        ss.width(width);
        ss.fill(fill);
        if (flags)
            ss.setf(flags);
        ss << val;
        return ss.str();
    }

    //--------------------------------------------------------------------------

    String StringConverter::toString(bool val,
        uint16_t width /* = 0 */, char fill /* = ' ' */,
        std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
    {
        std::stringstream ss;
        ss.width(width);
        ss.fill(fill);
        if (flags)
            ss.setf(flags);
        ss << val;
        return ss.str();
    }

    //--------------------------------------------------------------------------

    float32_t StringConverter::parseSingle(const String &val,
        float32_t defaultValue /* = 0.0f */)
    {
        std::stringstream ss(val);
        float32_t ret = defaultValue;
        if (!(ss >> ret))
            return defaultValue;

        return ret;
    }

    //--------------------------------------------------------------------------

    float64_t StringConverter::parseDouble(const String &val,
        float64_t defaultValue /* = 0.0 */)
    {
        std::stringstream ss(val);
        float64_t ret = defaultValue;
        if (!(ss >> ret))
            return defaultValue;

        return ret;
    }

    //--------------------------------------------------------------------------

    int32_t StringConverter::parseInt32(const String &val,
        int32_t defaultValue /* = 0 */)
    {
        std::stringstream ss(val);
        int32_t ret = defaultValue;
        if (!(ss >> ret))
            return defaultValue;

        return ret;
    }

    //--------------------------------------------------------------------------

    uint32_t StringConverter::parseUInt32(const String &val,
        uint32_t defaultValue /* = 0 */)
    {
        std::stringstream ss(val);
        uint32_t ret = defaultValue;
        if (!(ss >> ret))
            return defaultValue;

        return ret;
    }

    //--------------------------------------------------------------------------

    long_t StringConverter::parseLong(const String &val,
        long_t defaultValue /* = 0 */)
    {
        std::stringstream ss(val);
        long_t ret = defaultValue;
        if (!(ss >> ret))
            return defaultValue;

        return ret;
    }

    //--------------------------------------------------------------------------

    ulong_t StringConverter::parseULong(const String &val,
        ulong_t defaultValue /* = 0 */)
    {
        std::stringstream ss(val);
        ulong_t ret = defaultValue;
        if (!(ss >> ret))
            return defaultValue;

        return ret;
    }

    //--------------------------------------------------------------------------

    size_t StringConverter::parseSizeT(const String &val,
        size_t defaultValue /* = 0 */)
    {
        std::stringstream ss(val);
        size_t ret = defaultValue;
        if (!(ss >> ret))
            return defaultValue;

        return ret;
    }

    //--------------------------------------------------------------------------

    bool StringConverter::parseBool(const String &val,
        bool defaultValue /* = false */)
    {
        if ((StringUtil::startsWith(val, "true") || StringUtil::startsWith(val, "yes")
            || StringUtil::startsWith(val, "1") || StringUtil::startsWith(val, "on")))
            return true;
        else if ((StringUtil::startsWith(val, "false") || StringUtil::startsWith(val, "no")
            || StringUtil::startsWith(val, "0") || StringUtil::startsWith(val, "off")))
            return false;
        else
            return defaultValue;
    }

    //--------------------------------------------------------------------------

    bool StringConverter::isNumber(const String& val)
    {
        char* end;
        strtod(val.c_str(), &end);
        return end == (val.c_str() + val.size());
    }
}

