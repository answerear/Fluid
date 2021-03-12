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
    inline TIntrRayPlane<T>::TIntrRayPlane()
        : mRay(nullptr)
        , mPlane(nullptr)
    {

    }

    template <typename T>
    inline TIntrRayPlane<T>::TIntrRayPlane(
        const TRay<T> &ray, 
        const TPlane<T> &plane)
        : mRay(&ray)
        , mPlane(&plane)
    {

    }

    template <typename T>
    inline TIntrRayPlane<T>::TIntrRayPlane(
        const TRay<T> *ray,
        const TPlane<T> *plane)
        : mRay(ray)
        , mPlane(plane)
    {

    }

    template <typename T>
    bool TIntrRayPlane<T>::test()
    {
        if (mRay == nullptr || mPlane == nullptr)
            return false;

        T dot = mRay->getDirection().dot(mPlane->getNormal());

        if (dot >= TReal<T>::ZERO)
        {
            // 没有交点
            return false;
        }

        return true;
    }

    template <typename T>
    bool TIntrRayPlane<T>::test(TVector3<T> &intersection)
    {
        if (mRay == nullptr || mPlane == nullptr)
            return false;

        T dot = mRay->getDirection().dot(mPlane->getNormal());

        if (dot >= TReal<T>::ZERO)
        {
            // 没有交点
            return false;
        }

        // 求交点
        T t = (mPlane[3] - mRay->getOrigin().dot(mPlane->getNormal())) / dot;

        intersection = mRay->getOrigin() + t * mRay->getDirection();

        return true;
    }

    template <typename T>
    bool TIntrRayPlane<T>::test(T &distance)
    {
        if (mRay == nullptr || mPlane == nullptr)
            return false;

        T dot = mRay->getDirection().dot(mPlane->getNormal());

        if (dot >= TReal<T>::ZERO)
        {
            // 没有交点
            return false;
        }

        // 求交点
        T t = (mPlane[3] - mRay->getOrigin().dot(mPlane->getNormal())) / dot;

        TVector3<T> point = mRay->getOrigin() + t * mRay->getDirection();

        distance = (point - mRay->getOrigin()).length();

        return true;
    }
}

