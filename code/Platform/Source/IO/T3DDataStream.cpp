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

#include "IO/T3DDataStream.h"
#include <string.h>
#include <memory.h>


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_0(DataStream);

    //--------------------------------------------------------------------------

    String DataStream::readLine(bool trim)
    {
        char c;
        size_t nNumberOfRead = 0;
        String str;

        do
        {
            size_t nBytes = read(&c, sizeof(c));
            if (nBytes > 0 && c != '\r' && c != '\n')
            {
                str += c;
                nNumberOfRead += nBytes;
            }
            else if (nBytes == 0)
            {
                break;
            }
        } while (c != '\n');

        if (trim)
        {
            str.erase(str.find_last_not_of(" \t\r\n") + 1); // trim right
            str.erase(0, str.find_first_not_of(" \t\r\n")); // trim left
        }

        return str;
    }

    //--------------------------------------------------------------------------

    size_t DataStream::writeLine(const String &strLine)
    {
        size_t bytesOfWritten = 0;
        size_t length = strLine.find_first_not_of("\r\n");

        if (length > 0)
        {
            bytesOfWritten = write((void *)strLine.c_str(), length);
        }
        else if (length == String::npos)
        {
            length = strLine.length();
            bytesOfWritten = write((void *)strLine.c_str(), length);
        }

        return bytesOfWritten;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(bool val)
    {
        write(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(int8_t val)
    {
        write(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(uint8_t val)
    {
        write(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(int16_t val)
    {
        write(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(uint16_t val)
    {
        write(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(int32_t val)
    {
        write(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(uint32_t val)
    {
        write(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(int64_t val)
    {
        write(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(uint64_t val)
    {
        write(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(float val)
    {
        write(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(double val)
    {
        write(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(const char *s)
    {
        size_t nLen = strlen(s);
        if (nLen > 0)
        {
            write((void*)s, nLen);
        }
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator<<(const String &s)
    {
        size_t nLength = s.length();
        if (nLength > 0)
        {
            write((void*)s.c_str(), nLength);
        }
        char c = 0;
        write(&c, sizeof(c));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(bool &val)
    {
        read(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(int8_t &val)
    {
        read(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(uint8_t &val)
    {
        read(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(int16_t &val)
    {
        read(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(uint16_t &val)
    {
        read(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(int32_t &val)
    {
        read(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(uint32_t &val)
    {
        read(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(int64_t &val)
    {
        read(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(uint64_t &val)
    {
        read(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(float &val)
    {
        read(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(double &val)
    {
        read(&val, sizeof(val));
        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(char *&s)
    {
        char c;
        String str;
        size_t nNumberOfRead = 0;
        size_t nSize = 0;

        do
        {
            size_t nBytes = read(&c, sizeof(c));
            str += c;
            nNumberOfRead += nBytes;
            nSize++;
        }
        while (!eof() && c != 0);

        s = new char[nSize+1];
        memcpy(s, str.c_str(), nSize);

        return *this;
    }

    //--------------------------------------------------------------------------

    DataStream &DataStream::operator>>(String &s)
    {
        char c;
        size_t nNumberOfRead = 0;
        s.clear();

        do
        {
            size_t nBytes = read(&c, sizeof(c));
            s += c;
            nNumberOfRead += nBytes;
        }
        while (!eof() && c != 0);

        return *this;
    }
}
