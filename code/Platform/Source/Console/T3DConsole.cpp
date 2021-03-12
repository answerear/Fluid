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

#include "Console/T3DConsole.h"
#include "Adapter/T3DConsoleInterface.h"
#include "Adapter/T3DFactoryInterface.h"
#include "T3DSystem.h"
#include <stdarg.h>

namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(Console);
    T3D_IMPLEMENT_CLASS_0(Console);

    //--------------------------------------------------------------------------

    const uint32_t Console::MAX_CONTENT_SIZE = 4096;

    //--------------------------------------------------------------------------

    Console::Console()
        : mConsole(nullptr)
    {
        mConsole = T3D_PLATFORM_FACTORY.createPlatformConsole();
    }

    //--------------------------------------------------------------------------

    Console::~Console()
    {
        T3D_SAFE_DELETE(mConsole);
    }

    //--------------------------------------------------------------------------

    void Console::print(const char *pszFmt, ...)
    {
        if (nullptr != mConsole)
        {
            char szBuffer[MAX_CONTENT_SIZE] = {0};

            va_list vl;
            va_start(vl, pszFmt);
            vsnprintf(szBuffer, MAX_CONTENT_SIZE, pszFmt, vl);
            va_end(vl);

            mConsole->print(szBuffer);
        }
    }
}
