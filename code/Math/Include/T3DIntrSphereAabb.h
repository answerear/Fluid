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

#ifndef __T3D_INTR_SPHERE_AABB_H__
#define __T3D_INTR_SPHERE_AABB_H__


#include "T3DMathPrerequisites.h"
#include "T3DSphere.h"
#include "T3DAabb.h"


namespace Tiny3D
{
    template <typename T>
    class TIntrSphereAabb
    {
    public:
        TIntrSphereAabb();
        TIntrSphereAabb(const TSphere<T> *sphere, const TAabb<T> *box);
        TIntrSphereAabb(const TSphere<T> &sphere, const TAabb<T> &box);

        bool test();

        const TSphere<T> *getSphere() const
        {
            return mSphere;
        }

        const TAabb<T> *getBox() const
        {
            return mBox;
        }

        void setSphere(const TSphere<T> *sphere)
        {
            mSphere = sphere;
        }

        void setBox(const TAabb<T> *box)
        {
            mBox = box;
        }

    private:
        const TSphere<T>    *mSphere;
        const TAabb<T>      *mBox;
    };
}


#include "T3DIntrSphereAabb.inl"


#endif  /*__T3D_INTR_SPHERE_AABB_H__*/
