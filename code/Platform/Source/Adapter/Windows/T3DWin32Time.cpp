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


#include "Adapter/Windows/T3DWin32Time.h"
#include <windows.h>
#include <time.h>


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Win32Time, ITime);

    const uint64_t Win32Time::EPOCH = ((uint64_t)116444736000000000ULL);

    //--------------------------------------------------------------------------

    Win32Time::Win32Time()
    {

    }

    //--------------------------------------------------------------------------

    Win32Time::~Win32Time()
    {

    }

    //--------------------------------------------------------------------------

    int64_t Win32Time::currentSecsSinceEpoch()
    {
//         LARGE_INTEGER liTime, liFreq;
//         ::QueryPerformanceFrequency(&liFreq);
//         ::QueryPerformanceCounter(&liTime);
//         return (int64_t)(liTime.QuadPart / liFreq.QuadPart);
        FILETIME    file_time;
        SYSTEMTIME  system_time;
        ULARGE_INTEGER ularge;

        GetSystemTime(&system_time);
        SystemTimeToFileTime(&system_time, &file_time);
        ularge.LowPart = file_time.dwLowDateTime;
        ularge.HighPart = file_time.dwHighDateTime;

        return (int64_t)((ularge.QuadPart - EPOCH) / 10000000L);
    }

    //--------------------------------------------------------------------------

    int64_t Win32Time::currentMSecsSinceEpoch()
    {
//         LARGE_INTEGER liTime, liFreq;
//         ::QueryPerformanceFrequency(&liFreq);
//         ::QueryPerformanceCounter(&liTime);
//         int64_t sec = (int64_t)(liTime.QuadPart / liFreq.QuadPart);
//         int64_t sec = (int64_t)(liTime.QuadPart * 1000000.0 / liFreq.QuadPart);
//         int64_t msec = (int64_t)(liTime.QuadPart * 1000.0 / liFreq.QuadPart 
//             - sec * 1000.0);
//         return (sec * 1000 + msec);
//         return liTime.QuadPart / 1000;
        FILETIME    file_time;
        SYSTEMTIME  system_time;
        ULARGE_INTEGER ularge;

        GetSystemTime(&system_time);
        SystemTimeToFileTime(&system_time, &file_time);
        ularge.LowPart = file_time.dwLowDateTime;
        ularge.HighPart = file_time.dwHighDateTime;

        int64_t sec = (int64_t)((ularge.QuadPart - EPOCH) / 10000000L);
        return sec * 1000 + system_time.wMilliseconds;
    }
}
