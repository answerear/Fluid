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

#include "T3DLinuxFactory.h"
#include "Adapter/Common/T3DSDLApplication.h"
#include "Adapter/Common/T3DTimerService.h"
#include "Adapter/Desktop/T3DSDLDesktopWindow.h"
#include "Adapter/Unix/T3DUnixTime.h"
#include "Adapter/Linux/T3DLinuxDir.h"
#include "Adapter/Linux/T3DLinuxConsole.h"
#include "Adapter/Linux/T3DLinuxDeviceInfo.h"

namespace Tiny3D
{
    LinuxFactory::LinuxFactory()
    {

    }

    LinuxFactory::~LinuxFactory()
    {

    }

    IApplication *LinuxFactory::createPlatformApplication()
    {
        return new SDLApplication();
    }

    IWindow *LinuxFactory::createPlatformWindow()
    {
        return new SDLDesktopWindow();
    }

    ITime *LinuxFactory::createPlatformTime()
    {
        return new UnixTime();
    }

    ITimerService *LinuxFactory::createPlatformTimerService()
    {
        return new TimerService();
    }

    IDir *LinuxFactory::createPlatformDir()
    {
        return new LinuxDir();
    }

    IDeviceInfo *LinuxFactory::createPlatformDeviceInfo()
    {
        return new LinuxDeviceInfo();
    }

    IConsole *LinuxFactory::createPlatformConsole()
    {
        return new LinuxConsole();
    }

    EPlatform LinuxFactory::getPlatform()
    {
        return E_PLATFORM_LINUX;
    }

    IFactory *createPlatformFactory()
    {
        return new LinuxFactory();
    }
}
