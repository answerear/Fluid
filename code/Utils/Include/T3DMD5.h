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

#ifndef __T3D_MD5_H__
#define __T3D_MD5_H__


#include "T3DUtilsPrerequisites.h"
#include <fstream>


namespace Tiny3D
{
    class T3D_UTILS_API MD5
    {
    public:
        MD5();
        MD5(const void *input, size_t length);
        MD5(const String &str);
        MD5(std::ifstream &in);
        void update(const void *input, size_t length);
        void update(const String &str);
        void update(std::ifstream &in);
        const uint8_t *digest();
        String toString();
        void reset();
    private:
        void update(const uint8_t *input, size_t length);
        void final();
        void transform(const uint8_t block[64]);
        void encode(const uint32_t *input, uint8_t *output, size_t length);
        void decode(const uint8_t *input, uint32_t *output, size_t length);
        String bytesToHexString(const uint8_t *input, size_t length);

        /* class uncopyable */
        MD5(const MD5&);
        MD5& operator=(const MD5&);
    private:
        uint32_t _state[4];	/* state (ABCD) */
        uint32_t _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
        uint8_t _buffer[64];	/* input buffer */
        uint8_t _digest[16];	/* message digest */
        bool _finished;		/* calculate finished ? */

        static const uint8_t PADDING[64];	/* padding for calculate */
        static const char HEX[16];
        static const size_t BUFFER_SIZE = 1024;
    };
}


#endif  /*__T3D_UTILS_PREREQUISITES_H__*/
