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


namespace Tiny3D
{
    template <typename T>
    inline TIntrSphereSphere<T>::TIntrSphereSphere()
        : mSphere0(nullptr)
        , mSphere1(nullptr)
    {

    }

    template <typename T>
    inline TIntrSphereSphere<T>::TIntrSphereSphere(
        const TSphere<T> &s0,
        const TSphere<T> &s1)
        : mSphere0(&s0)
        , mSphere1(&s1)
    {

    }

    template <typename T>
    inline TIntrSphereSphere<T>::TIntrSphereSphere(
        const TSphere<T> *s0,
        const TSphere<T> *s1)
        : mSphere0(s0)
        , mSphere1(s1)
    {

    }

    template <typename T>
    bool TIntrSphereSphere<T>::test()
    {
        if (mSphere0 == nullptr || mSphere1 == nullptr)
            return false;

        T r = mSphere0->getRadius() + mSphere1->getRadius();
        T r2 = r * r;

        return ((mSphere0->getCenter() - mSphere1->getCenter()).length2() < r2); 
    }
}

