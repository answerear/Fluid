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
    inline TIntrAabbAabb<T>::TIntrAabbAabb()
        : mBox0(nullptr)
        , mBox1(nullptr)
    {

    }

    template <typename T>
    inline TIntrAabbAabb<T>::TIntrAabbAabb(
        const TAabb<T> &box0, 
        const TAabb<T> &box1)
        : mBox0(&box0)
        , mBox1(&box1)
    {

    }

    template <typename T>
    inline TIntrAabbAabb<T>::TIntrAabbAabb(
        const TAabb<T> *box0,
        const TAabb<T> *box1)
        : mBox0(box0)
        , mBox1(box1)
    {

    }

    template <typename T>
    bool TIntrAabbAabb<T>::test()
    {
        if (mBox0 == nullptr || mBox1 == nullptr)
            return false;


        return true;
    }
}

