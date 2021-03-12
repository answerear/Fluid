﻿/*******************************************************************************
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

#ifndef __T3D_INTR_OBB_PLANE_H__
#define __T3D_INTR_OBB_PLANE_H__


#include "T3DMathPrerequisites.h"
#include "T3DObb.h"
#include "T3DPlane.h"


namespace Tiny3D
{
    template <typename T>
    class TIntrObbPlane
    {
    public:
        TIntrObbPlane();
        TIntrObbPlane(const TObb<T> *box, const TPlane<T> *plane);
        TIntrObbPlane(const TObb<T> &box, const TPlane<T> &plane);

        int32_t test();

        const TObb<T> *getBox0() const
        {
            return mBox;
        }

        const TPlane<T> *getBox1() const
        {
            return mPlane;
        }

        void setBox(const TObb<T> *box)
        {
            mBox = box;
        }

        void setPlane(const TPlane<T> *plane)
        {
            mPlane = plane;
        }

    private:
        const TObb<T>   *mBox;
        const TPlane<T> *mPlane;
    };
}


#include "T3DIntrObbPlane.inl"


#endif  /*__T3D_INTR_OBB_PLANE_H__*/
