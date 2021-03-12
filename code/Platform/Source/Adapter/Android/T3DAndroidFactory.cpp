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

#include "Adapter/Android/T3DAndroidFactory.h"
#include "Adapter/Common/T3DSDLApplication.h"
#include "Adapter/Common/T3DTimerService.h"
#include "Adapter/Mobile/T3DSDLMobileWindow.h"
#include "Adapter/Unix/T3DUnixTime.h"
#include "Adapter/Android/T3DAndroidDir.h"
#include "Adapter/Android/T3DAndroidConsole.h"
#include "Adapter/Android/T3DAndroidDeviceInfo.h"


namespace Tiny3D
{
    AndroidFactory::AndroidFactory()
    {

    }

    AndroidFactory::~AndroidFactory()
    {

    }

    IApplication *AndroidFactory::createPlatformApplication()
    {
        return new SDLApplication();
    }

    IWindow *AndroidFactory::createPlatformWindow()
    {
        return new SDLMobileWindow();
    }

    ITime *AndroidFactory::createPlatformTime()
    {
        return new UnixTime();
    }

    ITimerService *AndroidFactory::createPlatformTimerService()
    {
        return new TimerService();
    }

    IDir *AndroidFactory::createPlatformDir()
    {
        return new AndroidDir();
    }

    IDeviceInfo *AndroidFactory::createPlatformDeviceInfo()
    {
        return new AndroidDeviceInfo();
    }

    IConsole *AndroidFactory::createPlatformConsole()
    {
        return new AndroidConsole();
    }

    EPlatform AndroidFactory::getPlatform()
    {
        return E_PLATFORM_ANDROID;
    }

    IFactory *createPlatformFactory()
    {
        return new AndroidFactory();
    }
}

