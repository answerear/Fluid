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

#ifndef __T3D_FRUSTUM_H__
#define __T3D_FRUSTUM_H__


#include "T3DMathPrerequisites.h"
#include "T3DPlane.h"


namespace Tiny3D
{
    template <typename T>
    class TFrustum
    {
    public:
        enum Face
        {
            E_FACE_TOP = 0,
            E_FACE_BOTTOM,
            E_FACE_LEFT,
            E_FACE_RIGHT,
            E_FACE_NEAR,
            E_FACE_FAR,
            E_MAX_FACE
        };

        TFrustum()
        {
        }

        void setFace(Face face, const TPlane<T> &plane)
        {
            T3D_ASSERT(face >= 0 && face < E_MAX_FACE);
            mFace[face] = plane;
        }

        const TPlane<T> &getFace(Face face) const
        {
            T3D_ASSERT(face >= 0 && face < E_MAX_FACE);
            return mFace[face];
        }

    protected:
        TPlane<T>   mFace[E_MAX_FACE];
    };
}


#endif  /*__T3D_FRUSTUM_H__*/
