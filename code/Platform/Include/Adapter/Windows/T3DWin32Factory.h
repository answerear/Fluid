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

#ifndef __T3D_WIN32_FACTORY_H__
#define __T3D_WIN32_FACTORY_H__


#include "Adapter/T3DFactoryInterface.h"


namespace Tiny3D
{
    class Win32Factory : public IFactory
    {
        T3D_DECLARE_CLASS();

    public:
        Win32Factory();
        virtual ~Win32Factory();

        virtual IApplication *createPlatformApplication() override;

        virtual IWindow *createPlatformWindow() override;

        virtual ITime *createPlatformTime() override;

        virtual ITimerService *createPlatformTimerService() override;

        virtual IDir *createPlatformDir() override;

        virtual IDeviceInfo *createPlatformDeviceInfo() override;

        virtual IConsole *createPlatformConsole() override;

        virtual EPlatform getPlatform() override;

    protected:

    };
}


#endif  /*__T3D_WIN32_FACTORY_H__*/