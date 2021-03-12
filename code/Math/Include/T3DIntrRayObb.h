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

#ifndef __T3D_INTR_RAY_OBB_H__
#define __T3D_INTR_RAY_OBB_H__


#include "T3DMathPrerequisites.h"
#include "T3DMath.h"
#include "T3DObb.h"
#include "T3DRay.h"


namespace Tiny3D
{
    template <typename T>
    class TIntrRayObb
    {
    public:
        TIntrRayObb();
        TIntrRayObb(const TRay<T> *ray, const TObb<T> *obb);
        TIntrRayObb(const TRay<T> &ray, const TObb<T> &obb);

        bool test();
        bool test(TVector3<T> &intersection);
        bool test(T &distance);

        const TRay<T> *getRay() const
        {
            return mRay;
        }

        const TAabb<T> *getObb() const
        {
            return mObb;
        }

        void setRay(const TRay<T> *ray)
        {
            mRay = ray;
        }

        void setObb(const TObb<T> *obb)
        {
            mObb = obb;
        }

    protected:
        const TRay<T>   *mRay;
        const TObb<T>   *mObb;
    };
}


#include "T3DIntrRayObb.inl"


#endif  /*__T3D_INTR_RAY_OBB_H__*/
