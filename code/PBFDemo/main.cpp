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

#ifndef __T3D_TYPE_H__
#define __T3D_TYPE_H__

#include <typeinfo>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string.h>
#include <memory.h>


typedef signed char         char_t;
typedef unsigned char       uchar_t;
typedef signed short        short_t;
typedef unsigned short      ushort_t;
typedef signed int          int_t;
typedef unsigned int        uint_t;

typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef signed short        int16_t;
typedef unsigned short      uint16_t;
typedef signed int          int32_t;
typedef unsigned int        uint32_t;

#if !defined (T3D_OS_ANDROID) && !defined (T3D_OS_LINUX)
    typedef signed long long    int64_t;
    typedef unsigned long long  uint64_t;
#endif

#if defined (T3D_OS_X64)
    typedef int64_t             long_t;
    typedef uint64_t            ulong_t;
#else
    typedef int32_t             long_t;
    typedef uint32_t            ulong_t;
#endif

typedef float               float32_t;
typedef double              float64_t;

typedef std::string         String;
typedef std::wstring        WString;

typedef std::string         UTF8String;
typedef std::u16string      UTF16String;
typedef std::u32string      UTF32String;

typedef void*               THandle;

typedef int32_t             TResult;

typedef uint32_t            ID;

#define T3D_INVALID_ID      0

typedef std::thread                     TThread;
typedef std::mutex                      TMutex;
typedef std::recursive_mutex            TRecursiveMutex;
typedef std::condition_variable         TCondVariable;

template <typename T>
using TAutoLock = std::unique_lock<T>;

template <typename T>
using TArray = std::vector<T>;

template <typename T>
using TList = std::list<T>;

template <typename T>
using TQueue = std::queue<T>;

template <typename T>
using TStack = std::stack<T>;

template <typename T>
using TSet = std::set<T>;

template <typename K, typename V>
using TMap = std::map<K, V>;

template <typename K, typename V>
using TMultimap = std::multimap<K, V>;

template <typename T1, typename T2>
using TPair = std::pair<T1, T2>;

#endif  /*__T3D_TYPE_H__*/
