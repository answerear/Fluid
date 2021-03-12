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

#ifndef __T3D_INTR_SHPERE_SPHERE_H__
#define __T3D_INTR_SHPERE_SPHERE_H__


#include "T3DMathPrerequisites.h"
#include "T3DMath.h"
#include "T3DSphere.h"


namespace Tiny3D
{
    template <typename T>
    class TIntrSphereSphere
    {
    public:
        TIntrSphereSphere();
        TIntrSphereSphere(const TSphere<T> *s0, const TSphere<T> *s1);
        TIntrSphereSphere(const TSphere<T> &s0, const TSphere<T> &s1);

        bool test();

        const TSphere<T> *getSphere0() const
        {
            return mSphere0;
        }

        const TSphere<T> *getSphere1() const
        {
            return mSphere1;
        }

        void setSphere0(const TSphere<T> *sphere)
        {
            mSphere0 = sphere;
        }

        void setSphere1(const TSphere<T> *sphere)
        {
            mSphere1 = sphere;
        }

    private:
        const TSphere<T>    *mSphere0;
        const TSphere<T>    *mSphere1;
    };
}


#include "T3DIntrSphereSphere.inl"


#endif  /*__T3D_INTR_SHPERE_SPHERE_H__*/
