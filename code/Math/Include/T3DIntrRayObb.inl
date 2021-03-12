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
#include "T3DIntrRayAabb.h"


namespace Tiny3D
{
    template <typename T>
    inline TIntrRayObb<T>::TIntrRayObb()
        : mRay(nullptr)
        , mObb(nullptr)
    {

    }

    template <typename T>
    inline TIntrRayObb<T>::TIntrRayObb(const TRay<T> *ray, const TObb<T> *obb)
        : mRay(ray)
        , mObb(obb)
    {

    }

    template <typename T>
    inline TIntrRayObb<T>::TIntrRayObb(const TRay<T> &ray, const TObb<T> &obb)
        : mRay(&ray)
        , mObb(&obb)
    {

    }

    template <typename T>
    bool TIntrRayObb<T>::test()
    {
        // 先把射线变换到OBB空间

        // 构造变换矩阵
        TMatrix3<T> m(mObb->getAxis(0), mObb->getAxis(1), mObb->getAxis(2), true);
        m = m.inverse();

        // 构造变换后射线
        TVector3<T> origin = m * mRay->getOrigin();
        TVector3<T> dir = m * mRay->getDirection();

        TRay<T> ray(origin, dir);

        // 构造一个AABB
        T minX = mObb->getCenter().x() - mObb->getExtent(0) * TReal<T>::HALF;
        T maxX = mObb->getCenter().x() + mObb->getExtent(0) * TReal<T>::HALF;
        T minY = mObb->getCenter().y() - mObb->getExtent(1) * TReal<T>::HALF;
        T maxY = mObb->getCenter().y() + mObb->getExtent(1) * TReal<T>::HALF;
        T minZ = mObb->getCenter().z() - mObb->getExtent(2) * TReal<T>::HALF;
        T maxZ = mObb->getCenter().z() + mObb->getExtent(2) * TReal<T>::HALF;

        TAabb<T> aabb(minX, maxX, minY, maxY, minZ, maxZ);

        // 构造一个射线和AABB检测器对象
        TIntrRayAabb<T> intr(ray, aabb);

        return intr.test();
    }

    template <typename T>
    bool TIntrRayObb<T>::test(TVector3<T> &intersection)
    {
        // 先把射线变换到OBB空间

        // 构造变换矩阵
        TMatrix3<T> m(mObb->getAxis(0), mObb->getAxis(1), mObb->getAxis(2), true);
        m = m.inverse();

        // 构造变换后射线
        T origin = m * mRay->getOrigin();
        T dir = m * mRay->getDirection();

        TRay<T> ray(origin, dir);

        // 构造一个AABB
        T minX = -mObb->getExtent(0) * TReal<T>::HALF;
        T maxX = mObb->getExtent(0) * TReal<T>::HALF;
        T minY = -mObb->getExtent(1) * TReal<T>::HALF;
        T maxY = mObb->getExtent(1) * TReal<T>::HALF;
        T minZ = -mObb->getExtent(2) * TReal<T>::HALF;
        T maxZ = mObb->getExtent(2) * TReal<T>::HALF;

        TAabb<T> aabb(minX, maxX, minY, maxY, minZ, maxZ);

        // 构造一个射线和AABB检测器对象
        TIntrRayAabb<T> intr(ray, aabb);

        return intr.test(intersection);
    }

    template <typename T>
    bool TIntrRayObb<T>::test(T &distance)
    {
        // 先把射线变换到OBB空间

        // 构造变换矩阵
        TMatrix3<T> m(mObb->getAxis(0), mObb->getAxis(1), mObb->getAxis(2), true);
        m = m.inverse();

        // 构造变换后射线
        T origin = m * mRay->getOrigin();
        T dir = m * mRay->getDirection();

        TRay<T> ray(origin, dir);

        // 构造一个AABB
        T minX = -mObb->getExtent(0) * TReal<T>::HALF;
        T maxX = mObb->getExtent(0) * TReal<T>::HALF;
        T minY = -mObb->getExtent(1) * TReal<T>::HALF;
        T maxY = mObb->getExtent(1) * TReal<T>::HALF;
        T minZ = -mObb->getExtent(2) * TReal<T>::HALF;
        T maxZ = mObb->getExtent(2) * TReal<T>::HALF;

        TAabb<T> aabb(minX, maxX, minY, maxY, minZ, maxZ);

        // 构造一个射线和AABB检测器对象
        TIntrRayAabb<T> intr(ray, aabb);

        return intr.test(distance);
    }
}

