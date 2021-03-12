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

#ifndef __T3D_INTR_RAY_PLANE_H__
#define __T3D_INTR_RAY_PLANE_H__


#include "T3DMathPrerequisites.h"
#include "T3DRay.h"
#include "T3DPlane.h"


namespace Tiny3D
{
    template <typename T>
    class TIntrRayPlane
    {
    public:
        TIntrRayPlane();
        TIntrRayPlane(const TRay<T> *ray, const TPlane<T> *plane);
        TIntrRayPlane(const TRay<T> &ray, const TPlane<T> &plane);

        bool test();
        bool test(TVector3<T> &intersection);
        bool test(T &distance);

        const TRay<T> *getRay() const
        {
            return mRay;
        }

        const TPlane<T> *getPlane() const
        {
            return mPlane;
        }

        void setRay(const TRay<T> *ray)
        {
            mRay = ray;
        }

        void setPlane(const TPlane<T> *plane)
        {
            mPlane = plane;
        }

    private:
        const TRay<T>       *mRay;
        const TPlane<T>     *mPlane;
    };
}


#include "T3DIntrRayPlane.inl"


#endif  /*__T3D_INTR_RAY_PLANE_H__*/
