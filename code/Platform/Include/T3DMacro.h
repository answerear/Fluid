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

#ifndef __T3D_MACRO_H__
#define __T3D_MACRO_H__

#include "T3DType.h"
#include <assert.h>


#if defined T3D_OS_WINDOWS      // Win32

    #ifdef _DEBUG   // debug
        #define T3D_DEBUG
    #else           // release
        #undef T3D_DEBUG
    #endif

//     #pragma warning(disable:4996)
    #pragma warning(disable:4251)
    #pragma warning(disable:4819)   // UTF-8 encode will trigger warning

    #define snprintf    _snprintf
    #define vsnprintf   _vsnprintf

	#define T3D_EXPORT_API      __declspec(dllexport)
	#define T3D_IMPORT_API      __declspec(dllimport)

#elif defined T3D_OS_IOS || defined T3D_OS_OSX || defined T3D_OS_LINUX  // iOS or Mac OS x or Linux

    #ifdef DEBUG    // debug
        #define T3D_DEBUG
    #else           // release
        #undef T3D_DEBUG
    #endif

	#define T3D_EXPORT_API
	#define T3D_IMPORT_API

#elif defined T3D_OS_ANDROID    // Android

    #ifdef NDK_DEBUG    // debug
        #define T3D_DEBUG
    #else               // release
        #undef T3D_DEBUG
    #endif

	#define T3D_EXPORT_API      __attribute__ ((visibility ("default")))
	#define T3D_IMPORT_API

#endif


#ifndef T3D_ASSERT
    #ifdef T3D_DEBUG
        #define T3D_ASSERT(x)   assert(x)
    #else
        #define T3D_ASSERT(x)
    #endif
#endif


#define MK_DWORD(h, l)      (((h<<16)&0xFFFF0000)|(0xFFFF&l))
#define LO_WORD(x)          (x&0xFFFF)
#define HI_WORD(x)          ((x>>16)&0xFFFF)
#define MK_WORD(h, l)       (((h<<8)&0xFF00)|(0xFF&l))
#define LO_BYTE(x)          (x&0xFF)
#define HI_BYTE(x)          ((x&>>8)&0xFF)


#define T3D_DECLARE_INTERFACE(T)    \
    public:     \
        virtual ~T()    {}

#define T3D_DISABLE_COPY(T) \
    private:    \
        T(const T &);   \
        T &operator =(const T &);

#define T3D_SAFE_DELETE(p)  \
    if (p != nullptr)   \
    {   \
        delete p;   \
        p = nullptr;    \
    }

#define T3D_SAFE_DELETE_ARRAY(p)    \
    if (p != nullptr)   \
    {   \
        delete []p; \
        p = nullptr;    \
    }

#define T3D_SAFE_RELEASE(p) \
    if (p != nullptr)   \
    {   \
        p->release();   \
        p = nullptr;    \
    }

#define T3D_SAFE_ACQUIRE(p) \
    if (p != nullptr)   \
    {   \
        p->acquire();   \
    }


#endif  /*__T3D_MACRO_H__*/
