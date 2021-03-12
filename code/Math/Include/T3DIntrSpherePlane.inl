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
    inline TIntrSpherePlane<T>::TIntrSpherePlane()
        : mSphere(nullptr)
        , mPlane(nullptr)
    {

    }

    template <typename T>
    inline TIntrSpherePlane<T>::TIntrSpherePlane(
        const TSphere<T> &sphere,
        const TPlane<T> &plane)
        : mSphere(&sphere)
        , mPlane(&plane)
    {

    }

    template <typename T>
    inline TIntrSpherePlane<T>::TIntrSpherePlane(
        const TSphere<T> *sphere,
        const TPlane<T> *plane)
        : mSphere(sphere)
        , mPlane(plane)
    {

    }

    template <typename T>
    inline int32_t TIntrSpherePlane<T>::test()
    {
        if (mSphere == nullptr || mPlane == nullptr)
            return -1;

        T d = mPlane->fastDistanceToPoint(mSphere->getCenter());

        // 完全在平面正面
        if (d >= mSphere->getRadius())
            return 1;

        // 完全在平面背面
        if (d <= -mSphere->getRadius())
            return -1;

        return 0;
    }
}

