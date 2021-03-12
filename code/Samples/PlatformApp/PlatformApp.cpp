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

#include "PlatformApp.h"


using namespace Tiny3D;


PlatformApp theApp;


PlatformApp::PlatformApp()
    : SampleApp()
    , mOnceTimerID(T3D_INVALID_TIMER_ID)
    , mLoopTimerID(T3D_INVALID_TIMER_ID)
{
}

PlatformApp::~PlatformApp()
{
}

bool PlatformApp::applicationDidFinishLaunching()
{
    T3D_LOG_INFO(LOG_TAG_APP, "System Information : \n%s", 
        T3D_DEVICE_INFO.getSystemInfo().c_str());

    mOnceTimerID = T3D_TIMER_MGR.startTimer(5000, false, this);
    mLoopTimerID = T3D_TIMER_MGR.startTimer(1000, true, this);

    return true;
}

void PlatformApp::onTimer(uint32_t timerID, int32_t dt)
{
    if (timerID == mOnceTimerID)
    {
        T3D_LOG_INFO(LOG_TAG_APP, "Once timer [%u] interval : %d", timerID, dt);
    }
    else if (timerID == mLoopTimerID)
    {
        T3D_LOG_INFO(LOG_TAG_APP, "Loop timer [%u] interval : %d", timerID, dt);
    }
}

