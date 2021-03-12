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

#ifndef __T3D_INTR_AABB_AABB_H__
#define __T3D_INTR_AABB_AABB_H__


#include "T3DMathPrerequisites.h"
#include "T3DAabb.h"


namespace Tiny3D
{
    template <typename T>
    class TIntrAabbAabb
    {
    public:
        TIntrAabbAabb();
        TIntrAabbAabb(const TAabb<T> *box0, const TAabb<T> *box1);
        TIntrAabbAabb(const TAabb<T> &box0, const TAabb<T> &box1);

        bool test();

        const TAabb<T> *getBox0() const
        {
            return mBox0;
        }

        const TAabb<T> *getBox1() const
        {
            return mBox1;
        }

        void setBox0(const TAabb<T> *box)
        {
            mBox0 = box;
        }

        void setBox1(const TAabb<T> *box)
        {
            mBox1 = box;
        }

    private:
        const TAabb<T>  *mBox0;
        const TAabb<T>  *mBox1;
    };
}


#include "T3DIntrAabbAabb.inl"


#endif  /*__T3D_INTR_AABB_AABB_H__*/
