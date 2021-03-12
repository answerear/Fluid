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

#include "T3DOSXFactory.h"
#include "Adapter/Common/T3DSDLApplication.h"
#include "Adapter/Common/T3DTimerService.h"
#include "Adapter/Desktop/T3DSDLDesktopWindow.h"
#include "Adapter/Unix/T3DUnixTime.h"
#include "Adapter/OSX/T3DOSXDir.h"
#include "Adapter/OSX/T3DOSXDeviceInfo.h"
#include "Adapter/OSX/T3DOSXConsole.h"

namespace Tiny3D
{
    OSXFactory::OSXFactory()
    {
		
    }

    OSXFactory::~OSXFactory()
    {

    }

    IApplication *OSXFactory::createPlatformApplication()
    {
        return new SDLApplication();
    }

    IWindow *OSXFactory::createPlatformWindow()
    {
        return new SDLDesktopWindow();
    }
	
	ITime *OSXFactory::createPlatformTime()
	{
		return new UnixTime();
	}
    
    ITimerService *OSXFactory::createPlatformTimerService()
    {
        return new TimerService();
    }
	
	IDir *OSXFactory::createPlatformDir()
	{
		return new OSXDir();
	}
	
	IDeviceInfo *OSXFactory::createPlatformDeviceInfo()
	{
		return new OSXDeviceInfo();
	}
	
	IConsole *OSXFactory::createPlatformConsole()
	{
		return new OSXConsole();
	}

    EPlatform OSXFactory::getPlatform()
    {
        return E_PLATFORM_OSX;
    }

    IFactory *createPlatformFactory()
    {
        return new OSXFactory();
    }
}
