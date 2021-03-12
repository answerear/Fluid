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

#ifndef __T3D_INTR_FRUSTUM_AABB_H__
#define __T3D_INTR_FRUSTUM_AABB_H__


#include "T3DMathPrerequisites.h"
#include "T3DFrustum.h"
#include "T3DAabb.h"


namespace Tiny3D
{
    template <typename T>
    class TIntrFrustumAabb
    {
    public:
        TIntrFrustumAabb();
        TIntrFrustumAabb(const TFrustum<T> *frustum, const TAabb<T> *box);
        TIntrFrustumAabb(const TFrustum<T> &frustum, const TAabb<T> &box);

        bool test();

        const TFrustum<T> *getFrustum() const
        {
            return mFrustum;
        }

        const TAabb<T> *getBox() const
        {
            return mBox;
        }

        void setFrustum(const TFrustum<T> *frustum)
        {
            mFrustum = frustum;
        }

        void setBox(const TAabb<T> *box)
        {
            mBox = box;
        }

    private:
        const TFrustum<T>   *mFrustum;
        const TAabb<T>      *mBox;
    };
}


#include "T3DIntrFrustumAabb.inl"


#endif  /*__T3D_INTR_FRUSTUM_AABB_H__*/
