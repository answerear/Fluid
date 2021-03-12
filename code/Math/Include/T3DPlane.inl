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
    inline TPlane<T>::TPlane()
    {
        mCoeff[0] = TReal<T>::ZERO;
        mCoeff[1] = TReal<T>::ONE;
        mCoeff[2] = TReal<T>::ZERO;
        mCoeff[3] = TReal<T>::ZERO;
    }

    template <typename T>
    inline TPlane<T>::TPlane(const TVector3<T> &rkNormal, T fDistance)
    {
        mCoeff[0] = rkNormal[0];
        mCoeff[1] = rkNormal[1];
        mCoeff[2] = rkNormal[2];
        mCoeff[3] = fDistance;
    }

    template <typename T>
    inline TPlane<T>::TPlane(const TVector3<T> &rkNormal, const TVector3<T> &rkPos)
    {
        mCoeff[0] = rkNormal[0];
        mCoeff[1] = rkNormal[1];
        mCoeff[2] = rkNormal[2];
        mCoeff[3] = -rkNormal.dot(rkPos);
    }

    template <typename T>
    inline TPlane<T>::TPlane(const TVector3<T> &rkPos1, const TVector3<T> &rkPos2, const TVector3<T> &rkPos3)
    {
        TVector3<T> normal = (rkPos2 - rkPos1).cross(rkPos3 - rkPos2);
        normal.normalize();

        mCoeff[0] = normal[0];
        mCoeff[1] = normal[1];
        mCoeff[2] = normal[2];

        mCoeff[3] = -normal.dot(rkPos1);
    }

    template <typename T>
    inline TPlane<T>::TPlane(const TPlane<T> &rkOther)
    {
        mCoeff[0] = rkOther.mCoeff[0];
        mCoeff[1] = rkOther.mCoeff[1];
        mCoeff[2] = rkOther.mCoeff[2];
        mCoeff[3] = rkOther.mCoeff[3];
    }

    template <typename T>
    inline TPlane<T> &TPlane<T>::operator =(const TPlane<T> &rkOther)
    {
        mCoeff[0] = rkOther.mCoeff[0];
        mCoeff[1] = rkOther.mCoeff[1];
        mCoeff[2] = rkOther.mCoeff[2];
        mCoeff[3] = rkOther.mCoeff[3];
        return *this;
    }

    template <typename T>
    inline bool TPlane<T>::operator ==(const TPlane<T> &rkOther) const
    {
        return (mCoeff[0] == rkOther.mCoeff[0] 
            && mCoeff[1] == rkOther.mCoeff[1]
            && mCoeff[2] == rkOther.mCoeff[2] 
            && mCoeff[3] == rkOther.mCoeff[3]);
    }

    template <typename T>
    inline bool TPlane<T>::operator !=(const TPlane<T> &rkOther) const
    {
        return !operator ==(rkOther);
    }

    template <typename T>
    inline const T TPlane<T>::operator [](int32_t idx) const
    {
        T3D_ASSERT(idx >= 0 && idx < 4);
        return mCoeff[idx];
    }

    template <typename T>
    inline T &TPlane<T>::operator [](int32_t idx)
    {
        T3D_ASSERT(idx >= 0 && idx < 4);
        return mCoeff[idx];
    }

    template <typename T>
    inline T TPlane<T>::distanceToPoint(const TVector3<T> &rkPos) const
    {
        TVector3<T> normal(mCoeff[0], mCoeff[1], mCoeff[2]);
        return normal.dot(rkPos) + mCoeff[3];
    }

    template <typename T>
    inline T TPlane<T>::fastDistanceToPoint(const TVector3<T> &rkPos) const
    {
        TVector3<T> normal(mCoeff[0], mCoeff[1], mCoeff[2]);
        return normal.dot(rkPos) + mCoeff[3];
    }

    template <typename T>
    inline typename TPlane<T>::Side TPlane<T>::sideForPoint(
        const TVector3<T> &rkPos) const
    {
        T distance = distanceToPoint(rkPos);
        TPlane<T>::Side side = E_SIDE_INTERSECT;

        if (distance < TReal<T>::ZERO)
            side = E_SIDE_NEGATIVE;
        else if (distance > TReal<T>::ZERO)
            side = E_SIDE_POSITIVE;

        return side;
    }

    template <typename T>
    inline typename TPlane<T>::Side TPlane<T>::fastSideForPoint(
        const TVector3<T> &rkPos) const
    {
        T distance = fastDistanceToPoint(rkPos);
        TPlane<T>::Side side = E_SIDE_INTERSECT;

        if (distance < TReal<T>::ZERO)
            side = E_SIDE_NEGATIVE;
        else if (distance > TReal<T>::ZERO)
            side = E_SIDE_POSITIVE;

        return side;
    }

    template <typename T>
    inline TVector3<T> TPlane<T>::getNormal() const
    {
        return TVector3<T>(mCoeff[0], mCoeff[1], mCoeff[2]);
    }

    template <typename T>
    inline T TPlane<T>::getDistance() const
    {
        return mCoeff[3];
    }

    template <typename T>
    inline void TPlane<T>::normalize()
    {
        T length = TMath<T>::sqrt(
            mCoeff[0] * mCoeff[0] 
            + mCoeff[1] * mCoeff[1] 
            + mCoeff[2] * mCoeff[2]);
        mCoeff[0] /= length;
        mCoeff[1] /= length;
        mCoeff[2] /= length;
        mCoeff[3] /= length;
    }
}
