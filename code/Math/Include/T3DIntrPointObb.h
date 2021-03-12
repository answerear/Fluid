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

#ifndef __T3D_INTR_POINT_OBB_H__
#define __T3D_INTR_POINT_OBB_H__


#include "T3DMathPrerequisites.h"
#include "T3DVector3.h"
#include "T3DObb.h"


namespace Tiny3D
{
    template <typename T>
    class TIntrPointObb
    {
    public:
        TIntrPointObb();
        TIntrPointObb(const TVector3<T> *point, const TObb<T> *box);
        TIntrPointObb(const TVector3<T> &point, const TObb<T> &box);

        bool test();

        const TVector3<T> *getPoint() const
        {
            return mPoint;
        }

        const TObb<T> *getBox() const
        {
            return mBox;
        }

        void setPoint(const TVector3<T> *point)
        {
            mPoint = point;
        }

        void setBox(const TObb<T> *box)
        {
            mBox = box;
        }

    private:
        const TVector3<T>   *mPoint;
        const TObb<T>       *mBox;
    };
}


#include "T3DIntrPointObb.inl"


#endif  /*__T3D_INTR_POINT_OBB_H__*/
