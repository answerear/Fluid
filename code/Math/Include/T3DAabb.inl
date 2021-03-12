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
    inline TAabb<T>::TAabb()
        : mMinX(TReal<T>::ZERO)
        , mMaxX(TReal<T>::ZERO)
        , mMinY(TReal<T>::ZERO)
        , mMaxY(TReal<T>::ZERO)
        , mMinZ(TReal<T>::ZERO)
        , mMaxZ(TReal<T>::ZERO)
    {

    }

    template <typename T>
    inline TAabb<T>::TAabb(T fXMin, T fXMax, T fYMin, T fYMax, T fZMin, T fZMax)
        : mMinX(fXMin)
        , mMaxX(fXMax)
        , mMinY(fYMin)
        , mMaxY(fYMax)
        , mMinZ(fZMin)
        , mMaxZ(fZMax)
    {

    }

    template <typename T>
    void TAabb<T>::build(const TVector3<T> points[], size_t count)
    {
        mMaxX = TReal<T>::MINUS_INF;
        mMaxY = TReal<T>::MINUS_INF;
        mMaxZ = TReal<T>::MINUS_INF;
        mMinX = TReal<T>::INF;
        mMinY = TReal<T>::INF;
        mMinZ = TReal<T>::INF;

        size_t i = 0;
        for (i = 0; i < count; ++i)
        {
            if (points[i].x() > mMaxX)
                mMaxX = points[i].x();
            if (points[i].x() < mMinX)
                mMinX = points[i].x();
            if (points[i].y() > mMaxY)
                mMaxY = points[i].y();
            if (points[i].y() < mMinY)
                mMinY = points[i].y();
            if (points[i].z() > mMaxZ)
                mMaxZ = points[i].z();
            if (points[i].z() < mMinZ)
                mMinZ = points[i].z();
        }

        TVector3<T> center(
            (mMinX + mMaxX) * TReal<T>::HALF,
            (mMinY + mMaxY) * TReal<T>::HALF,
            (mMinZ + mMaxZ) * TReal<T>::HALF
            );
        mSphere.setCenter(center);
            
        TVector3<T> D(mMaxX - mMinX, mMaxY - mMinY, mMaxZ - mMinZ);
        mSphere.setRadius(D.length() * TReal<T>::HALF);
    }

    template <typename T>
    inline T TAabb<T>::getWidth() const
    {
        return mMaxX - mMinX;
    }

    template <typename T>
    inline T TAabb<T>::getHeight() const
    {
        return mMaxY - mMinY;
    }

    template <typename T>
    inline T TAabb<T>::getDepth() const
    {
        return mMaxZ - mMinZ;
    }

    template <typename T>
    inline T TAabb<T>::getMinX() const
    {
        return mMinX;
    }

    template <typename T>
    inline T TAabb<T>::getMaxX() const
    {
        return mMaxX;
    }

    template <typename T>
    inline T TAabb<T>::getMinY() const
    {
        return mMinY;
    }

    template <typename T>
    inline T TAabb<T>::getMaxY() const
    {
        return mMaxY;
    }

    template <typename T>
    inline T TAabb<T>::getMinZ() const
    {
        return mMinZ;
    }

    template <typename T>
    inline T TAabb<T>::getMaxZ() const
    {
        return mMaxZ;
    }

    template <typename T>
    inline const TVector3<T> &TAabb<T>::getCenter() const
    {
        return mSphere.getCenter();
    }

    template <typename T>
    inline T TAabb<T>::getRadius() const
    {
        return mSphere.getRadius();
    }

    template <typename T>
    inline const TSphere<T> &TAabb<T>::getSphere() const
    {
        return mSphere;
    }

    template <typename T>
    inline void TAabb<T>::setWidth(T fWidth)
    {
        T ex = fWidth * TReal<T>::HALF;
        mMinX = mSphere.getCenter().x() - ex;
        mMaxX = mSphere.getCenter().x() + ex;
    }

    template <typename T>
    inline void TAabb<T>::setHeight(T fHeight)
    {
        T ex = fHeight * TReal<T>::HALF;
        mMinY = mSphere.getCenter().y() - ex;
        mMaxY = mSphere.getCenter().y() + ex;
    }

    template <typename T>
    inline void TAabb<T>::setDepth(T fDepth)
    {
        T ex = fDepth * TReal<T>::HALF;
        mMinZ = mSphere.getCenter().z() - ex;
        mMaxZ = mSphere.getCenter().z() + ex;
    }

    template <typename T>
    inline void TAabb<T>::setMinX(T x)
    {
        mMinX = x;
        mSphere.getCenter().x() = (mMaxX + mMinX) * TReal<T>::HALF;
        T fWidth = mMaxX - mMinX;
        T fHeight = mMaxY - mMinY;
        T fDepth = mMaxZ - mMinZ;
        mSphere.getRadius() = TMath<T>::sqrt(fWidth * fWidth + fHeight * fHeight
            + fDepth * fDepth) * TReal<T>::HALF;
    }

    template <typename T>
    inline void TAabb<T>::setMaxX(T x)
    {
        mMaxX = x;
        mSphere.getCenter().x() = (mMaxX + mMinX) * TReal<T>::HALF;
        T fWidth = mMaxX - mMinX;
        T fHeight = mMaxY - mMinY;
        T fDepth = mMaxZ - mMinZ;
        mSphere.getRadius() = TMath<T>::sqrt(fWidth * fWidth + fHeight * fHeight
            + fDepth * fDepth) * TReal<T>::HALF;
    }

    template <typename T>
    inline void TAabb<T>::setMinY(T y)
    {
        mMinY = y;
        mSphere.getCenter().y() = (mMaxY + mMinY) * TReal<T>::HALF;
        T fWidth = mMaxX - mMinX;
        T fHeight = mMaxY - mMinY;
        T fDepth = mMaxZ - mMinZ;
        mSphere.getRadius() = TMath<T>::sqrt(fWidth * fWidth + fHeight * fHeight
            + fDepth * fDepth) * TReal<T>::HALF;
    }

    template <typename T>
    inline void TAabb<T>::setMaxY(T y)
    {
        mMaxY = y;
        mSphere.getCenter().y() = (mMaxY + mMinY) * TReal<T>::HALF;
        T fWidth = mMaxX - mMinX;
        T fHeight = mMaxY - mMinY;
        T fDepth = mMaxZ - mMinZ;
        mSphere.getRadius() = TMath<T>::sqrt(fWidth * fWidth + fHeight * fHeight
            + fDepth * fDepth) * TReal<T>::HALF;
    }

    template <typename T>
    inline void TAabb<T>::setMinZ(T z)
    {
        mMinZ = z;
        mSphere.getCenter().z() = (mMaxZ + mMinZ) * TReal<T>::HALF;
        T fWidth = mMaxX - mMinX;
        T fHeight = mMaxY - mMinY;
        T fDepth = mMaxZ - mMinZ;
        mSphere.getRadius() = TMath<T>::sqrt(fWidth * fWidth + fHeight * fHeight
            + fDepth * fDepth) * TReal<T>::HALF;
    }

    template <typename T>
    inline void TAabb<T>::setMaxZ(T z)
    {
        mMaxZ = z;
        mSphere.getCenter().z() = (mMaxZ + mMinZ) * TReal<T>::HALF;
        T fWidth = mMaxX - mMinX;
        T fHeight = mMaxY - mMinY;
        T fDepth = mMaxZ - mMinZ;
        mSphere.getRadius() = TMath<T>::sqrt(fWidth * fWidth + fHeight * fHeight
            + fDepth * fDepth) * TReal<T>::HALF;
    }

    template <typename T>
    inline void TAabb<T>::setParam(const TVector3<T> &vMin, const TVector3<T> &vMax)
    {
        mMinX = vMin.x();
        mMinY = vMin.y();
        mMinZ = vMin.z();
        mMaxX = vMax.x();
        mMaxY = vMax.y();
        mMaxZ = vMax.z();

        TVector3<T> temp = vMax - vMin;
        TVector3<T> center = temp * TReal<T>::HALF + vMin;
        T radius = temp.length();
        mSphere.setCenter(center);
        mSphere.setRadius(radius);
    }
}

