/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2017  Answer Wong
 * For latest info, see https://github.com/asnwerear/Tiny3D
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

#ifndef __T3D_WINDOW_INTERFACE_H__
#define __T3D_WINDOW_INTERFACE_H__


#include "Adapter/Unix/T3DUnixTime.h"
#include <sys/time.h>


namespace Tiny3D
{
    UnixTime::UnixTime()
    {

    }

    UnixTime::~UnixTime()
    {

    }

    int64_t UnixTime::currentSecsSinceEpoch()
    {
        struct timeval val;
        gettimeofday(&val, nullptr);
        return val.tv_sec;
    }

    int64_t UnixTime::currentMSecsSinceEpoch()
    {
        struct timeval val;
        gettimeofday(&val, nullptr);
        return val.tv_sec * 1000 + val.tv_usec / 1000;
    }
}


#endif  /*__T3D_WINDOW_INTERFACE_H__*/