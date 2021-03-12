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


#include "T3DTimerManager.h"
#include "Adapter/Common/T3DTimerService.h"
#include "Adapter/T3DFactoryInterface.h"
#include "T3DSystem.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(TimerManager);
    T3D_IMPLEMENT_CLASS_0(TimerManager);

    //--------------------------------------------------------------------------

    const ID TimerManager::INVALID_TIMER_ID = ITimerService::INVALID_TIMER_ID;

    //--------------------------------------------------------------------------


    TimerManager::TimerManager()
        : mTimerService(nullptr)
    {
        mTimerService = T3D_PLATFORM_FACTORY.createPlatformTimerService();
    }

    //--------------------------------------------------------------------------

    TimerManager::~TimerManager()
    {
        T3D_SAFE_DELETE(mTimerService);
    }

    //--------------------------------------------------------------------------

    ID TimerManager::startTimer(uint32_t interval, bool repeat,
        ITimerListener *listener)
    {
        if (mTimerService != nullptr)
        {
            return mTimerService->startTimer(interval, repeat, listener);
        }

        return INVALID_TIMER_ID;
    }

    //--------------------------------------------------------------------------

    TResult TimerManager::stopTimer(ID timerID)
    {
        if (mTimerService != nullptr)
        {
            return mTimerService->stopTimer(timerID);
        }

        return T3D_ERR_INVALID_POINTER;
    }

    //--------------------------------------------------------------------------

    TResult TimerManager::init()
    {
        if (mTimerService != nullptr)
        {
            return mTimerService->init();
        }

        return T3D_ERR_INVALID_POINTER;
    }

    //--------------------------------------------------------------------------

    TResult TimerManager::pollEvents()
    {
        if (mTimerService != nullptr)
        {
            return mTimerService->pollEvents();
        }

        return T3D_ERR_INVALID_POINTER;
    }
}

