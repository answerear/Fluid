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


#include "Resource/T3DModelManager.h"
#include "Resource/T3DDylib.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(ModelManager);
    T3D_IMPLEMENT_CLASS_1(ModelManager, ResourceManager);

    //--------------------------------------------------------------------------

    ModelManagerPtr ModelManager::create()
    {
        ModelManagerPtr mgr = new ModelManager();
        mgr->release();
        return mgr;
    }

    //--------------------------------------------------------------------------

    ModelManager::ModelManager()
    {

    }

    //--------------------------------------------------------------------------

    ModelManager::~ModelManager()
    {

    }

    //--------------------------------------------------------------------------

    ModelPtr ModelManager::loadModel(const String &name)
    {
        return smart_pointer_cast<Model>(ResourceManager::load(name, 0));
    }

    //--------------------------------------------------------------------------

    ResourcePtr ModelManager::create(
        const String &name, int32_t argc, va_list args)
    {
        ModelPtr mesh;

        if (argc == 0)
        {
            mesh = Model::create(name);
        }

        return mesh;
    }

    //--------------------------------------------------------------------------

    TResult ModelManager::unloadModel(ModelPtr model)
    {
        return unload(model);
    }
}
