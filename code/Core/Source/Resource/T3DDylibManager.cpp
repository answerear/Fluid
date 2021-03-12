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


#include "Resource/T3DDylibManager.h"
#include "Resource/T3DDylib.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(DylibManager);
    T3D_IMPLEMENT_CLASS_1(DylibManager, ResourceManager);

    //--------------------------------------------------------------------------

    DylibManagerPtr DylibManager::create()
    {
        DylibManagerPtr mgr = new DylibManager();
        mgr->release();
        return mgr;
    }

    //--------------------------------------------------------------------------

    DylibManager::DylibManager()
    {

    }

    //--------------------------------------------------------------------------

    DylibManager::~DylibManager()
    {

    }

    //--------------------------------------------------------------------------

    DylibPtr DylibManager::loadDylib(const String &name)
    {
        return smart_pointer_cast<Dylib>(ResourceManager::load(name, 0));
    }

    //--------------------------------------------------------------------------

    ResourcePtr DylibManager::create(
        const String &name, int32_t argc, va_list args)
    {
        return Dylib::create(name);
    }

    //--------------------------------------------------------------------------

    TResult DylibManager::unloadDylib(DylibPtr dylib)
    {
        return unload(dylib);
    }
}
