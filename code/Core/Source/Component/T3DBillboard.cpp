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


#include "Component/T3DBillboard.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Billboard, Renderable);

    //--------------------------------------------------------------------------

    BillboardPtr Billboard::create(ID uID /* = E_CID_AUTOMATIC */)
    {
        BillboardPtr billboard = new Billboard(uID);
        billboard->release();
        return billboard;
    }

    //--------------------------------------------------------------------------

    Billboard::Billboard(ID uID /* = E_CID_AUTOMATIC */)
        : Renderable(uID)
    {

    }

    //--------------------------------------------------------------------------

    Billboard::~Billboard()
    {

    }

    //--------------------------------------------------------------------------

    ComponentPtr Billboard::clone() const
    {
        BillboardPtr newObj = Billboard::create();

        TResult ret = cloneProperties(newObj);

        if (T3D_FAILED(ret))
        {
            newObj = nullptr;
        }

        return newObj;
    }

    //--------------------------------------------------------------------------

    TResult Billboard::cloneProperties(ComponentPtr newObj) const
    {
        TResult ret = Renderable::cloneProperties(newObj);

        if (ret == T3D_OK)
        {

        }

        return ret;
    }

    //--------------------------------------------------------------------------

    MaterialPtr Billboard::getMaterial() const
    {
        return nullptr;
    }

    //--------------------------------------------------------------------------

    VertexArrayObjectPtr Billboard::getVertexArrayObject() const
    {
        return nullptr;
    }
}
