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

#ifndef __T3D_TRIANGLE_H__
#define __T3D_TRIANGLE_H__


#include "T3DMathPrerequisites.h"
#include "T3DVector3.h"


namespace Tiny3D
{
    template <typename T>
    class TTriangle
    {
    public:
        TTriangle();
        TTriangle(const TVector3<T> *vertices);
        TTriangle(const T *vertices);
        
        const TVector3<T> *getVertices() const
        {
            return mVertices;
        }

        TVector3<T> *getVertices()
        {
            return mVertices;
        }

        void setVertices(const TVector3<T> *vertices);
        void setVertices(const T *vertices);

        const TVector3<T> &operator [](size_t idx) const;
        TVector3<T> &operator [](size_t idx);

    private:
        TVector3<T> mVertices[3];
    };
}

#include "T3DTriangle.inl"

#endif  /*__T3D_TRIANGLE_H__*/
