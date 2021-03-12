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


#include "T3DMatrix4.h"
#include "T3DIntrAabbPlane.h"


namespace Tiny3D
{
    template <typename T>
    inline TIntrObbPlane<T>::TIntrObbPlane()
        : mBox(nullptr)
        , mPlane(nullptr)
    {

    }

    template <typename T>
    inline TIntrObbPlane<T>::TIntrObbPlane(
        const TObb<T> &box,
        const TPlane<T> &plane)
        : mBox(&box)
        , mPlane(&plane)
    {

    }

    template <typename T>
    inline TIntrObbPlane<T>::TIntrObbPlane(
        const TObb<T> *box,
        const TPlane<T> *plane)
        : mBox(box)
        , mPlane(plane)
    {

    }

    template <typename T>
    int32_t TIntrObbPlane<T>::test()
    {
        if (mBox == nullptr || mPlane == nullptr)
            return -1;

        // 先把平面变换到OBB空间

        // 构造变换矩阵
        TMatrix3<T> m(mBox->getAxis(0), mBox->getAxis(1), mBox->getAxis(2), true);
        m = m.inverse();

        // 构造变换后平面
        TVector3<T> n = m * mPlane->getNormal();
        n.normalize();
        TPlane<T> plane(n, mPlane->getDistance());

        // 构造一个AABB
        T minX = -mBox->getExtent(0) * TReal<T>::HALF;
        T maxX = mBox->getExtent(0) * TReal<T>::HALF;
        T minY = -mBox->getExtent(1) * TReal<T>::HALF;
        T maxY = mBox->getExtent(1) * TReal<T>::HALF;
        T minZ = -mBox->getExtent(2) * TReal<T>::HALF;
        T maxZ = mBox->getExtent(2) * TReal<T>::HALF;

        TAabb<T> aabb(minX, maxX, minY, maxY, minZ, maxZ);

        // 构造一个平面和AABB检测器对象
        TIntrAabbPlane<T> intr(aabb, plane);

        return intr.test();
    }
}

