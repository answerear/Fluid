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


#include "Kernel/T3DObject.h"
#include "Memory/T3DSmartPtr.h"
#include "Component/T3DComponentCreator.h"
#include "T3DErrorDef.h"
#include "Component/T3DTransform3D.h"
#include "Component/T3DCamera.h"
#include "Component/T3DCube.h"
#include "Component/T3DGlobe.h"
#include "Component/T3DMesh.h"
#include "Bound/T3DAabbBound.h"
#include "Bound/T3DFrustumBound.h"
#include "Bound/T3DObbBound.h"
#include "Bound/T3DSphereBound.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    ComponentCreatorPtr ComponentCreator::create()
    {
        ComponentCreatorPtr creator = new ComponentCreator();
        creator->release();
        return creator;
    }

    //--------------------------------------------------------------------------

    ComponentCreator::ComponentCreator()
    {

    }

    //--------------------------------------------------------------------------

    ComponentCreator::~ComponentCreator()
    {
    }

    //--------------------------------------------------------------------------

    String ComponentCreator::getType() const
    {
        return "Component";
    }

    //--------------------------------------------------------------------------

    ComponentPtr ComponentCreator::createObject(int32_t argc, ...) const
    {
        ComponentPtr component;

        do 
        {
            va_list params;
            va_start(params, argc);
            const Class *cls = va_arg(params, const Class *);
            va_list args = va_arg(params, va_list);

            if (cls == T3D_CLASS(Transform3D))
            {
                component = Transform3D::create();
            }
            else if (cls == T3D_CLASS(Camera))
            {
                component = Camera::create();
            }
            else if (cls == T3D_CLASS(AabbBound))
            {
                component = AabbBound::create();
            }
            else if (cls == T3D_CLASS(FrustumBound))
            {
                component = FrustumBound::create();
            }
            else if (cls == T3D_CLASS(ObbBound))
            {
                component = ObbBound::create();
            }
            else if (cls == T3D_CLASS(SphereBound))
            {
                component = SphereBound::create();
            }
            else if (cls == T3D_CLASS(Cube))
            {
                Vector3 center = va_arg(args, Vector3);
                Vector3 extent = va_arg(args, Vector3);
                component = Cube::create(center, extent);
            }
            else if (cls == T3D_CLASS(Globe))
            {
                Vector3 center = va_arg(args, Vector3);
                Real *radius = va_arg(args, Real*);
                component = Globe::create(center, *radius);
            }
            else if (cls == T3D_CLASS(Mesh))
            {
                component = Mesh::create();
            }

            va_end(params);

        } while (0);

        return component;
    }
}
