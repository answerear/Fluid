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

#ifndef __T3D_INTR_AABB_OBB_H__
#define __T3D_INTR_AABB_OBB_H__


#include "T3DMathPrerequisites.h"
#include "T3DAabb.h"
#include "T3DObb.h"


namespace Tiny3D
{
    template <typename T>
    class TIntrAabbObb
    {
    public:
        TIntrAabbObb();
        TIntrAabbObb(const TAabb<T> *aabb, const TObb<T> *obb);
        TIntrAabbObb(const TAabb<T> &aabb, const TObb<T> &obb);

        bool test();

        const TAabb<T> *getAabb() const
        {
            return mAabb;
        }

        const TObb<T> *getObb() const
        {
            return mObb;
        }

        void setAabb(const TAabb<T> *aabb)
        {
            mAabb = aabb;
        }

        void setObb(const TObb<T> *obb)
        {
            mObb = obb;
        }

    private:
        const TAabb<T>  *mAabb;
        const TObb<T>   *mObb;
    };
}


#include "T3DIntrAabbObb.inl"


#endif  /*__T3D_INTR_AABB_OBB_H__*/
