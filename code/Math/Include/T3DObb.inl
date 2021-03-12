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
    inline TObb<T>::TObb()
        : mCenter(TVector3<T>::ZERO)
    {
        mAxis[0] = mAxis[1] = mAxis[2] = TVector3<T>::ZERO;
        mExtent[0] = mExtent[1] = mExtent[2] = 0.0;
    }

    template <typename T>
    inline TObb<T>::TObb(const TVector3<T> &rkCenter, const TVector3<T> *akAxis,
        const T *afExtent)
        : mCenter(rkCenter)
    {
        mAxis[0] = akAxis[0];
        mAxis[1] = akAxis[1];
        mAxis[2] = akAxis[2];
        mExtent[0] = afExtent[0];
        mExtent[1] = afExtent[1];
        mExtent[2] = afExtent[2];
    }

    template <typename T>
    inline TObb<T>::TObb(const TVector3<T> &rkCenter, 
        const TVector3<T> &rkAxis0,
        const TVector3<T> &rkAxis1, 
        const TVector3<T> &rkAxis2,
        T fExtent0, T fExtent1, T fExtent2)
        : mCenter(rkCenter)
    {
        mAxis[0] = rkAxis0;
        mAxis[1] = rkAxis1;
        mAxis[2] = rkAxis2;
        mExtent[0] = fExtent0;
        mExtent[1] = fExtent1;
        mExtent[2] = fExtent2;
    }

    template <typename T>
    inline void TObb<T>::build(const TVector3<T> points[], size_t count, 
        BuildOption option /* = E_BUILD_AABB */)
    {
        switch (option)
        {
        case E_BUILD_AABB:
            buildByAABB(points, count);
            break;
        case E_BUILD_COVARIANCE:
            buildByCovariance(points, count);
            break;
        }
    }

    template <typename T>
    inline void TObb<T>::computeVertices(TVector3<T> *akVertex) const
    {
        TVector3<T> akEAxis[3] =
        {
            mExtent[0] * mAxis[0], mExtent[1] * mAxis[1], mExtent[2] * mAxis[2]
        };

        akVertex[0] = mCenter - akEAxis[0] - akEAxis[1] - akEAxis[2];
        akVertex[1] = mCenter + akEAxis[0] - akEAxis[1] - akEAxis[2];
        akVertex[2] = mCenter + akEAxis[0] + akEAxis[1] - akEAxis[2];
        akVertex[3] = mCenter - akEAxis[0] + akEAxis[1] - akEAxis[2];
        akVertex[4] = mCenter - akEAxis[0] - akEAxis[1] + akEAxis[2];
        akVertex[5] = mCenter + akEAxis[0] - akEAxis[1] + akEAxis[2];
        akVertex[6] = mCenter + akEAxis[0] + akEAxis[1] + akEAxis[2];
        akVertex[7] = mCenter - akEAxis[0] + akEAxis[1] + akEAxis[2];
    }

    template <typename T>
    inline const TVector3<T> &TObb<T>::getCenter() const
    {
        return mCenter;
    }

    template <typename T>
    inline const TVector3<T> &TObb<T>::getAxis(int32_t idx) const
    {
        T3D_ASSERT(idx >= 0 && idx < 3);
        return mAxis[idx];
    }

    template <typename T>
    inline const TVector3<T> *TObb<T>::getAxis() const
    {
        return mAxis;
    }

    template <typename T>
    inline T TObb<T>::getExtent(int32_t idx) const
    {
        return mExtent[idx];
    }

    template <typename T>
    inline const T *TObb<T>::getExtent() const
    {
        return mExtent;
    }

    template <typename T>
    inline void TObb<T>::setCenter(const TVector3<T> &rkCenter)
    {
        mCenter = rkCenter;
    }

    template <typename T>
    inline void TObb<T>::setAxis(
        const TVector3<T> &rkAxis0, 
        const TVector3<T> &rkAxis1,
        const TVector3<T> &rkAxis2)
    {
        mAxis[0] = rkAxis0;
        mAxis[1] = rkAxis1;
        mAxis[2] = rkAxis2;
    }

    template <typename T>
    inline void TObb<T>::setExtent(int32_t idx, T fExtent)
    {
        T3D_ASSERT(idx >= 0 && idx < 3);
        mExtent[idx] = fExtent;
    }

    template <typename T>
    void TObb<T>::buildByAABB(const TVector3<T> points[], size_t count)
    {
        T maxX = TReal<T>::MINUS_INF;
        T maxY = TReal<T>::MINUS_INF;
        T maxZ = TReal<T>::MINUS_INF;
        T minX = TReal<T>::INF;
        T minY = TReal<T>::INF;
        T minZ = TReal<T>::INF;

        size_t i = 0;
        for (i = 0; i < count; ++i)
        {
            if (points[i].x() > maxX)
                maxX = points[i].x();
            if (points[i].x() < minX)
                minX = points[i].x();
            if (points[i].y() > maxY)
                maxY = points[i].y();
            if (points[i].y() < minY)
                minY = points[i].y();
            if (points[i].z() > maxZ)
                maxZ = points[i].z();
            if (points[i].z() < minZ)
                minZ = points[i].z();
        }

        mCenter[0] = (minX + maxX) * TReal<T>::HALF;
        mCenter[1] = (minY + maxY) * TReal<T>::HALF;
        mCenter[2] = (minZ + maxZ) * TReal<T>::HALF;

        mAxis[0] = TVector3<T>::UNIT_X;
        mAxis[1] = TVector3<T>::UNIT_Y;
        mAxis[2] = TVector3<T>::UNIT_Z;

        mExtent[0] = (maxX - minX) * TReal<T>::HALF;
        mExtent[1] = (maxY - minY) * TReal<T>::HALF;
        mExtent[2] = (maxZ - minZ) * TReal<T>::HALF;
    }

    template <typename T>
    void TObb<T>::buildByCovariance(const TVector3<T> points[], size_t count)
    {
        // 暂未实现
        T3D_ASSERT(0);
    }
}

