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
    inline TIntrAabbPlane<T>::TIntrAabbPlane()
        : mBox(nullptr)
        , mPlane(nullptr)
    {

    }

    template <typename T>
    inline TIntrAabbPlane<T>::TIntrAabbPlane(
        const TAabb<T> &box, 
        const TPlane<T> &plane)
        : mBox(&box)
        , mPlane(&plane)
    {

    }

    template <typename T>
    inline TIntrAabbPlane<T>::TIntrAabbPlane(
        const TAabb<T> *box,
        const TPlane<T> *plane)
        : mBox(box)
        , mPlane(plane)
    {

    }

    template <typename T>
    inline int32_t TIntrAabbPlane<T>::test()
    {
        if (mBox == nullptr || mPlane == nullptr)
            return -1;

        T minD, maxD;
        const TVector3<T> &n = mPlane->getNormal();

        if (n.x() > TReal<T>::ZERO)
        {
            minD = n.x() * mBox->getMinX();
            maxD = n.x() * mBox->getMaxX();
        }
        else
        {
            minD = n.x() * mBox->getMaxX();
            maxD = n.x() * mBox->getMinX();
        }

        if (n.y() > TReal<T>::ZERO)
        {
            minD += n.y() * mBox->getMinY();
            maxD += n.y() * mBox->getMaxY();
        }
        else
        {
            minD += n.y() * mBox->getMaxY();
            maxD += n.y() * mBox->getMinY();
        }

        if (n.z() > TReal<T>::ZERO)
        {
            minD += n.z() * mBox->getMinZ();
            maxD += n.z() * mBox->getMaxZ();
        }
        else
        {
            minD += n.z() * mBox->getMaxZ();
            maxD += n.z() * mBox->getMinZ();
        }

        if (minD >= -mPlane->getDistance())
            return 1;

        if (maxD <= -mPlane->getDistance())
            return -1;

        return 0;
    }
}

