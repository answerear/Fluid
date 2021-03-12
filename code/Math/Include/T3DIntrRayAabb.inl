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
    inline TIntrRayAabb<T>::TIntrRayAabb()
        : mRay(nullptr)
        , mAabb(nullptr)
    {

    }

    template <typename T>
    inline TIntrRayAabb<T>::TIntrRayAabb(
        const TRay<T> *ray, 
        const TAabb<T> *aabb)
        : mRay(ray)
        , mAabb(aabb)
    {

    }

    template <typename T>
    inline TIntrRayAabb<T>::TIntrRayAabb(
        const TRay<T> &ray,
        const TAabb<T> &aabb)
        : mRay(&ray)
        , mAabb(&aabb)
    {

    }

    template <typename T>
    bool TIntrRayAabb<T>::test()
    {
        // 这里使用平板层相交法检测

        if (mRay == nullptr || mAabb == nullptr)
        {
            return false;
        }

        T ox = mRay->getOrigin().x();
        T oy = mRay->getOrigin().y();
        T oz = mRay->getOrigin().z();
        T dx = mRay->getDirection().x();
        T dy = mRay->getDirection().y();
        T dz = mRay->getDirection().z();

        T minX = TReal<T>::MINUS_INF;
        T minY = TReal<T>::MINUS_INF;
        T minZ = TReal<T>::MINUS_INF;
        T maxX = TReal<T>::INF;
        T maxY = TReal<T>::INF;
        T maxZ = TReal<T>::INF;

        if (TMath<T>::abs(dx) < TReal<T>::EPSILON)
        {
            if (ox < mAabb->getMinX() 
                || ox > mAabb->getMaxX())
            {
                // 若射线方向矢量的x轴分量为0且原点不在盒体内
                return false;
            }
        }
        else
        {
            if (dx >= TReal<T>::ZERO)
            {
                minX = (mAabb->getMinX() - ox) / dx;
                maxX = (mAabb->getMaxX() - ox) / dx;
            }
            else
            {
                minX = (mAabb->getMaxX() - ox) / dx;
                maxX = (mAabb->getMinX() - ox) / dx;
            }
        }

        if (TMath<T>::abs(dy) < TReal<T>::EPSILON)
        {
            if (oy < mAabb->getMinY()
                || oy > mAabb->getMaxY())
            {
                // 若射线方向矢量的y轴分量为0且原点不在盒体内
                return false;
            }
        }
        else
        {
            if (dy >= TReal<T>::ZERO)
            {
                minY = (mAabb->getMinY() - oy) / dy;
                maxY = (mAabb->getMaxY() - oy) / dy;
            }
            else
            {
                minY = (mAabb->getMaxY() - oy) / dy;
                maxY = (mAabb->getMinY() - oy) / dy;
            }
        }

        if (TMath<T>::abs(dz) < TReal<T>::EPSILON)
        {
            if (oz < mAabb->getMinZ()
                || oz > mAabb->getMaxZ())
            {
                // 若射线方向矢量的z轴分量为0且原点不在盒体内
                return false;
            }
        }
        else
        {
            if (dz >= TReal<T>::ZERO)
            {
                minZ = (mAabb->getMinZ() - oz) / dz;
                maxZ = (mAabb->getMaxZ() - oz) / dz;
            }
            else
            {
                minZ = (mAabb->getMaxZ() - oz) / dz;
                maxZ = (mAabb->getMinZ() - oz) / dz;
            }
        }

        T t0, t1;

        // 射线进入平面处（最靠近的平面）的最大t值 
        t0 = TMath<T>::max(minZ, TMath<T>::max(minX, minY));

        // 射线离开平面处（最远离的平面）的最小t值
        t1 = TMath<T>::min(maxZ, TMath<T>::min(maxX, maxY));

        return (t0 < t1);
    }

    template <typename T>
    bool TIntrRayAabb<T>::test(TVector3<T> &intersection)
    {
        if (mRay == nullptr || mAabb == nullptr)
        {
            return false;
        }

        bool inside = true;

        T xt, xn;

        if (mRay->getOrigin().x() < mAabb->getMinX())
        {
            xt = mAabb->getMinX() - mRay->getOrigin().x();
            
            if (xt > mRay->getDirection().x())
                return false;

            xt /= mRay->getDirection().x();
            inside = false;
            xn = TReal<T>::MINUS_ONE;
        }
        else if (mRay->getOrigin().x() > mAabb->getMaxX())
        {
            xt = mAabb->getMaxX() - mRay->getOrigin().x();

            if (xt < mRay->getDirection().x())
                return false;

            xt /= mRay->getDirection().x();
            inside = false;
            xn = TReal<T>::ONE;
        }
        else
        {
            xt = TReal<T>::MINUS_ONE;
        }

        T yt, yn;

        if (mRay->getOrigin().y() < mAabb->getMinY())
        {
            yt = mAabb->getMinY() - mRay->getOrigin().y();

            if (yt > mRay->getDirection().y())
                return false;

            yt /= mRay->getDirection().y();
            inside = false;
            yn = TReal<T>::MINUS_ONE;
        }
        else if (mRay->getOrigin().y() > mAabb->getMaxY())
        {
            yt = mAabb->getMaxY() - mRay->getOrigin().y();

            if (yt < mRay->getDirection().y())
                return false;

            yt /= mRay->getDirection().y();
            inside = false;
            yn = TReal<T>::ONE;
        }
        else
        {
            yt = TReal<T>::MINUS_ONE;
        }

        T zt, zn;

        if (mRay->getOrigin().z() < mAabb->getMinZ())
        {
            zt = mAabb->getMinY() - mRay->getOrigin().z();

            if (zt > mRay->getDirection().z())
                return false;

            zt /= mRay->getDirection().z();
            inside = false;
            zn = TReal<T>::MINUS_ONE;
        }
        else if (mRay->getOrigin().z() > mAabb->getMaxZ())
        {
            zt = mAabb->getMaxY() - mRay->getOrigin().z();

            if (zt < mRay->getDirection().z())
                return false;

            zt /= mRay->getDirection().z();
            inside = false;
            zn = TReal<T>::ONE;
        }
        else
        {
            zt = TReal<T>::MINUS_ONE;
        }

        // 是否在AABB内
        if (inside)
        {
            intersection = TVector3<T>::ZERO;
            return true;
        }

        // 选择最远平面——发生相交的地方
        int which = 0;
        T t = xt;
        if (yt > t)
        {
            which = 1;
            t = yt;
        }

        if (zt > t)
        {
            which = 2;
            t = zt;
        }

        switch (t)
        {
        case 0: // 和yz平面相交
            {
                T y = mRay->getOrigin().y() + mRay->getDirection().y() * t;
                if (y < mAabb->getMinY() || y > mAabb->getMaxY())
                    return false;

                T z = mRay->getOrigin().z() + mRay->getDirection().z() * t;
                if (z < mAabb->getMinZ() || z > mAabb->getMaxZ())
                    return false;

                T x;

                if (xn == TReal<T>::MINUS_ONE)
                    x = mAabb->getMinX();
                else if (xn == TReal<T>::ONE)
                    x = mAabb->getMaxX();

                intersection[0] = x;
                intersection[1] = y;
                intersection[2] = z;
            }
            break;
        case 1: // 和xz平面相交
            {
                T x = mRay->getOrigin().x() + mRay->getDirection().x() * t;
                if (x < mAabb->getMinX() || x > mAabb->getMaxX())
                    return false;

                T z = mRay->getOrigin().z() + mRay->getDirection().z() * t;
                if (z < mAabb->getMinZ() || z > mAabb->getMaxZ())
                    return false;

                T y;

                if (yn == TReal<T>::MINUS_ONE)
                    y = mAabb->getMinY();
                else if (yn == TReal<T>::ONE)
                    y = mAabb->getMaxY();

                intersection[0] = x;
                intersection[1] = y;
                intersection[2] = z;
            }
            break;
        case 2: // 和xy平面相交
            {
                T x = mRay->getOrigin().x() + mRay->getDirection().x() * t;
                if (x < mAabb->getMinX() || x > mAabb->getMaxX())
                    return false;

                T y = mRay->getOrigin().y() + mRay->getDirection().y() * t;
                if (y < mAabb->getMinY() || y > mAabb->getMaxY())
                    return false;

                T z;

                if (zn == TReal<T>::MINUS_ONE)
                    z = mAabb->getMinY();
                else if (zn == TReal<T>::ONE)
                    z = mAabb->getMaxY();

                intersection[0] = x;
                intersection[1] = y;
                intersection[2] = z;
            }
            break;
        }

        return true;
    }

    template <typename T>
    bool TIntrRayAabb<T>::test(T &distance)
    {
        if (mRay == nullptr || mAabb == nullptr)
        {
            return false;
        }

        bool inside = true;

        T xt, xn;

        if (mRay->getOrigin().x() < mAabb->getMinX())
        {
            xt = mAabb->getMinX() - mRay->getOrigin().x();

            if (xt > mRay->getDirection().x())
                return false;

            xt /= mRay->getDirection().x();
            inside = false;
            xn = TReal<T>::MINUS_ONE;
        }
        else if (mRay->getOrigin().x() > mAabb->getMaxX())
        {
            xt = mAabb->getMaxX() - mRay->getOrigin().x();

            if (xt < mRay->getDirection().x())
                return false;

            xt /= mRay->getDirection().x();
            inside = false;
            xn = TReal<T>::ONE;
        }
        else
        {
            xt = TReal<T>::MINUS_ONE;
        }

        T yt, yn;

        if (mRay->getOrigin().y() < mAabb->getMinY())
        {
            yt = mAabb->getMinY() - mRay->getOrigin().y();

            if (yt > mRay->getDirection().y())
                return false;

            yt /= mRay->getDirection().y();
            inside = false;
            yn = TReal<T>::MINUS_ONE;
        }
        else if (mRay->getOrigin().y() > mAabb->getMaxY())
        {
            yt = mAabb->getMaxY() - mRay->getOrigin().y();

            if (yt < mRay->getDirection().y())
                return false;

            yt /= mRay->getDirection().y();
            inside = false;
            yn = TReal<T>::ONE;
        }
        else
        {
            yt = TReal<T>::MINUS_ONE;
        }

        T zt, zn;

        if (mRay->getOrigin().z() < mAabb->getMinZ())
        {
            zt = mAabb->getMinY() - mRay->getOrigin().z();

            if (zt > mRay->getDirection().z())
                return false;

            zt /= mRay->getDirection().z();
            inside = false;
            zn = TReal<T>::MINUS_ONE;
        }
        else if (mRay->getOrigin().z() > mAabb->getMaxZ())
        {
            zt = mAabb->getMaxY() - mRay->getOrigin().z();

            if (zt < mRay->getDirection().z())
                return false;

            zt /= mRay->getDirection().z();
            inside = false;
            zn = TReal<T>::ONE;
        }
        else
        {
            zt = TReal<T>::MINUS_ONE;
        }

        // 是否在AABB内
        if (inside)
        {
            distance = TReal<T>::ZERO;
            return true;
        }

        // 选择最远平面——发生相交的地方
        int which = 0;
        T t = xt;
        if (yt > t)
        {
            which = 1;
            t = yt;
        }

        if (zt > t)
        {
            which = 2;
            t = zt;
        }

        switch (t)
        {
        case 0: // 和yz平面相交
            {
                T y = mRay->getOrigin().y() + mRay->getDirection().y() * t;
                if (y < mAabb->getMinY() || y > mAabb->getMaxY())
                    return false;

                T z = mRay->getOrigin().z() + mRay->getDirection().z() * t;
                if (z < mAabb->getMinZ() || z > mAabb->getMaxZ())
                    return false;

                T x;

                if (xn == TReal<T>::MINUS_ONE)
                    x = mAabb->getMinX();
                else if (xn == TReal<T>::ONE)
                    x = mAabb->getMaxX();

                TVector3<T> intersection(x, y, z);
                distance = (intersection - mRay->getOrigin()).length();
            }
            break;
        case 1: // 和xz平面相交
            {
                T x = mRay->getOrigin().x() + mRay->getDirection().x() * t;
                if (x < mAabb->getMinX() || x > mAabb->getMaxX())
                    return false;

                T z = mRay->getOrigin().z() + mRay->getDirection().z() * t;
                if (z < mAabb->getMinZ() || z > mAabb->getMaxZ())
                    return false;

                T y;

                if (yn == TReal<T>::MINUS_ONE)
                    y = mAabb->getMinY();
                else if (yn == TReal<T>::ONE)
                    y = mAabb->getMaxY();

                TVector3<T> intersection(x, y, z);
                distance = (intersection - mRay->getOrigin()).length();
            }
            break;
        case 2: // 和xy平面相交
            {
                T x = mRay->getOrigin().x() + mRay->getDirection().x() * t;
                if (x < mAabb->getMinX() || x > mAabb->getMaxX())
                    return false;

                T y = mRay->getOrigin().y() + mRay->getDirection().y() * t;
                if (y < mAabb->getMinY() || y > mAabb->getMaxY())
                    return false;

                T z;

                if (zn == TReal<T>::MINUS_ONE)
                    z = mAabb->getMinY();
                else if (zn == TReal<T>::ONE)
                    z = mAabb->getMaxY();

                TVector3<T> intersection(x, y, z);
                distance = (intersection - mRay->getOrigin()).length();
            }
            break;
        }

        return true;
    }
}

