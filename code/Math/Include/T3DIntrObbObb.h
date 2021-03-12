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

#ifndef __T3D_INTR_OBB_OBB_H__
#define __T3D_INTR_OBB_OBB_H__


#include "T3DMathPrerequisites.h"
#include "T3DObb.h"


namespace Tiny3D
{
    template <typename T>
    class TIntrObbObb
    {
    public:
        TIntrObbObb();
        TIntrObbObb(const TObb<T> *box0, const TObb<T> *box1);
        TIntrObbObb(const TObb<T> &box0, const TObb<T> &box1);

        bool test();

        const TObb<T> *getBox0() const
        {
            return mBox0;
        }

        const TObb<T> *getBox1() const
        {
            return mBox1;
        }

        void setBox0(const TObb<T> *box)
        {
            mBox0 = box;
        }

        void setBox1(const TObb<T> *box)
        {
            mBox1 = box;
        }

    private:
        const TObb<T>   *mBox0;
        const TObb<T>   *mBox1;
    };
}


#include "T3DIntrObbObb.inl"


#endif  /*__T3D_INTR_OBB_OBB_H__*/
