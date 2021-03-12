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

#include "T3DWin32Factory.h"
#include "Adapter/Common/T3DSDLApplication.h"
#include "Adapter/Common/T3DTimerService.h"
#include "Adapter/Desktop/T3DSDLDesktopWindow.h"
#include "Adapter/Windows/T3DWin32Time.h"
#include "Adapter/Windows/T3DWin32Dir.h"
#include "Adapter/Windows/T3DWin32DeviceInfo.h"
#include "Adapter/Windows/T3DWin32Console.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Win32Factory, IFactory);

    //--------------------------------------------------------------------------

    Win32Factory::Win32Factory()
    {

    }

    //--------------------------------------------------------------------------

    Win32Factory::~Win32Factory()
    {

    }

    //--------------------------------------------------------------------------

    IApplication *Win32Factory::createPlatformApplication()
    {
        return new SDLApplication();
    }

    //--------------------------------------------------------------------------

    IWindow *Win32Factory::createPlatformWindow()
    {
        return new SDLDesktopWindow();
    }

    //--------------------------------------------------------------------------

    ITime *Win32Factory::createPlatformTime()
    {
        return new Win32Time();
    }

    //--------------------------------------------------------------------------

    ITimerService *Win32Factory::createPlatformTimerService()
    {
        return new TimerService();
    }

    //--------------------------------------------------------------------------

    IDir *Win32Factory::createPlatformDir()
    {
        return new Win32Dir();
    }

    //--------------------------------------------------------------------------

    IDeviceInfo *Win32Factory::createPlatformDeviceInfo()
    {
        return new Win32DeviceInfo();
    }

    //--------------------------------------------------------------------------

    IConsole *Win32Factory::createPlatformConsole()
    {
        return new Win32Console();
    }

    //--------------------------------------------------------------------------

    EPlatform Win32Factory::getPlatform()
    {
        return E_PLATFORM_WIN32;
    }

    //--------------------------------------------------------------------------

    IFactory *createPlatformFactory()
    {
        return new Win32Factory();
    }
}
