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
    inline TIntrRaySphere<T>::TIntrRaySphere()
        : mRay(nullptr)
        , mSphere(nullptr)
    {

    }

    template <typename T>
    inline TIntrRaySphere<T>::TIntrRaySphere(
        const TRay<T> &ray, 
        const TSphere<T> &sphere)
        : mRay(&ray)
        , mSphere(&sphere)
    {

    }

    template <typename T>
    inline TIntrRaySphere<T>::TIntrRaySphere(
        const TRay<T> *ray, 
        const TSphere<T> *sphere)
        : mRay(ray)
        , mSphere(sphere)
    {

    }

    template <typename T>
    bool TIntrRaySphere<T>::test()
    {
        if (mRay == nullptr || mSphere == nullptr)
            return false;

        // 计算射线起点到球心的向量
        TVector3<T> OC = mSphere->getCenter() - mRay->getOrigin();

        // 计算oc射线方向上的投影
        TVector3<T> dir = mRay->getDirection();
        dir.normalize();
        T proj = OC.dot(dir);

        if (proj < TReal<T>::ZERO)
        {
            return false;
        }

        T OC2 = OC.dot(OC);

        // 计算出球心到射线的距离
        T d = OC2 - proj * proj;

        T radiusSqr = mSphere->getRadius() * mSphere->getRadius();

        if (d > radiusSqr)
        {
            // 球心到射线的距离大于半径，则射线跟球没有相交
            return false;
        }

        return true;
    }

    template <typename T>
    bool TIntrRaySphere<T>::test(TVector3<T> &intersection)
    {
        if (mRay == nullptr || mSphere == nullptr)
            return false;

        // 计算射线起点到球心的向量
        TVector3<T> OC = mSphere->getCenter() - mRay->getOrigin();

        // 计算oc射线方向上的投影
        TVector3<T> dir = mRay->getDirection();
        dir.normalize();
        T proj = OC.dot(dir);

        if (proj < TReal<T>::ZERO)
        {
            return false;
        }

        T OC2 = OC.dot(OC);

        // 计算出球心到射线的距离
        T d2 = OC2 - proj * proj;

        T radiusSqr = mSphere->getRadius() * mSphere->getRadius();

        if (d2 > radiusSqr)
        {
            // 球心到射线的距离大于半径，则射线跟球没有相交
            return false;
        }

        T t0, t1;

        if (mSphere->getRadius() - d2 < TReal<T>::EPSILON)
        {
            t0 = t1 = proj;
        }
        else
        {
            T d = TMath<T>::sqrt(d2);
            t0 = proj - d;
            t1 = proj + d;
        }

        intersection = mRay->getOrigin() + t0 * dir;

        return true;
    }

    template <typename T>
    bool TIntrRaySphere<T>::test(T &distance)
    {
        // 计算射线起点到球心的向量
        TVector3<T> OC = mSphere->getCenter() - mRay->getOrigin();

        // 计算oc射线方向上的投影
        TVector3<T> dir = mRay->getDirection();
        dir.normalize();
        T proj = OC.dot(dir);

        if (proj < TReal<T>::ZERO)
        {
            return false;
        }

        T OC2 = OC.dot(OC);

        // 计算出球心到射线的距离
        T d2 = OC2 - proj * proj;

        T radiusSqr = mSphere->getRadius() * mSphere->getRadius();

        if (d2 > radiusSqr)
        {
            // 球心到射线的距离大于半径，则射线跟球没有相交
            return false;
        }

        distance = TMath<T>::sqrt(d2);

        return true;
    }
}

