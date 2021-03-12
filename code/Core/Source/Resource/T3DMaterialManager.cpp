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


#include "Resource/T3DMaterialManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(MaterialManager);
    T3D_IMPLEMENT_CLASS_1(MaterialManager, ResourceManager);

    //--------------------------------------------------------------------------

    MaterialManagerPtr MaterialManager::create()
    {
        MaterialManagerPtr mgr = new MaterialManager();
        mgr->release();
        return mgr;
    }

    //--------------------------------------------------------------------------

    MaterialManager::MaterialManager()
    {

    }

    //--------------------------------------------------------------------------

    MaterialManager::~MaterialManager()
    {

    }

    //--------------------------------------------------------------------------

    MaterialPtr MaterialManager::loadMaterial(const String &name, 
        Material::MaterialType matType)
    {
        return smart_pointer_cast<Material>(ResourceManager::load(name, 1, 
            matType));
    }

    //--------------------------------------------------------------------------

    TResult MaterialManager::unloadMaterial(MaterialPtr material)
    {
        return unload(material);
    }

    //--------------------------------------------------------------------------

    ResourcePtr MaterialManager::create(const String &name, int32_t argc, 
        va_list args)
    {
        MaterialPtr material;

        if (argc == 1)
        {
            Material::MaterialType matType 
                = va_arg(args, Material::MaterialType);
            material = Material::create(name, matType);
        }

        return material;
    }
}
