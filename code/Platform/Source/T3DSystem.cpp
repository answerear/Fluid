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

#include "T3DSystem.h"
#include "Adapter/T3DFactoryInterface.h"
#include "Time/T3DTimerManager.h"
#include "IO/T3DDir.h"
#include "Console/T3DConsole.h"
#include "Device/T3DDeviceInfo.h"
#include "T3DCommonErrorDef.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(System);
    T3D_IMPLEMENT_CLASS_0(System);

    //--------------------------------------------------------------------------

    System::System()
        : mPlatformFactory(nullptr)
        , mConsole(nullptr)
        , mDeviceInfo(nullptr)
    {
        mPlatformFactory = createPlatformFactory();
        Dir::getNativeSeparator();
        mConsole = new Console();
        mDeviceInfo = new DeviceInfo();
        mTimerMgr = new TimerManager();
    }

    //--------------------------------------------------------------------------

    System::~System()
    {
        T3D_SAFE_DELETE(mTimerMgr);
        T3D_SAFE_DELETE(mDeviceInfo);
        T3D_SAFE_DELETE(mConsole);
        T3D_SAFE_DELETE(mPlatformFactory);
    }

    //--------------------------------------------------------------------------

    int32_t System::init()
    {
        int32_t ret = T3D_OK;

        do
        {
            String strCachePath = Dir::getCachePath();
            if (!Dir::exists(strCachePath))
            {
                if (!Dir::makeDir(strCachePath))
                    break;
            }
            
            ret  = mTimerMgr->init();
            if (T3D_FAILED(ret))
                break;
            
        } while (0);
        
        return ret;
    }

    //--------------------------------------------------------------------------

    void System::poll()
    {
        mTimerMgr->pollEvents();
    }
}
