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


#include "T3DPlane.h"
#include "T3DReal.h"


namespace Tiny3D
{
    template <typename T>
    inline TIntrPointFrustum<T>::TIntrPointFrustum()
        : mPoint(nullptr)
        , mFrustum(nullptr)
    {

    }

    template <typename T>
    inline TIntrPointFrustum<T>::TIntrPointFrustum(
        const TVector3<T> &point,
        const TFrustum<T> &frustum)
        : mPoint(&point)
        , mFrustum(&frustum)
    {

    }

    template <typename T>
    inline TIntrPointFrustum<T>::TIntrPointFrustum(
        const TVector3<T> *point,
        const TFrustum<T> *frustum)
        : mPoint(point)
        , mFrustum(frustum)
    {

    }

    template <typename T>
    inline bool TIntrPointFrustum<T>::test()
    {
        if (mPoint == nullptr || mFrustum == nullptr)
            return false;

        const TVector3<T> &point = *mPoint;

        // 近平面
        const TPlane<T> &nearPlane = mFrustum->getFace(TFrustum<T>::E_FACE_NEAR);
        typename TPlane<T>::Side side = nearPlane.fastSideForPoint(point);
        if (side == TPlane<T>::E_SIDE_NEGATIVE)
            return false;

        // 远平面
        const TPlane<T> &farPlane = mFrustum->getFace(TFrustum<T>::E_FACE_FAR);
        side = farPlane.fastSideForPoint(point);
        if (side == TPlane<T>::E_SIDE_NEGATIVE)
            return false;

        // 左平面
        const TPlane<T> &leftPlane = mFrustum->getFace(TFrustum<T>::E_FACE_LEFT);
        side = farPlane.fastSideForPoint(point);
        if (side == TPlane<T>::E_SIDE_NEGATIVE)
            return false;

        // 右平面
        const TPlane<T> &rightPlane = mFrustum->getFace(TFrustum<T>::E_FACE_RIGHT);
        side = farPlane.fastSideForPoint(point);
        if (side == TPlane<T>::E_SIDE_NEGATIVE)
            return false;

        // 上平面
        const TPlane<T> &topPlane = mFrustum->getFace(TFrustum<T>::E_FACE_TOP);
        side = topPlane.fastSideForPoint(point);
        if (side == TPlane<T>::E_SIDE_NEGATIVE)
            return false;

        // 下平面
        const TPlane<T> &bottomPlane = mFrustum->getFace(TFrustum<T>::E_FACE_BOTTOM);
        side = bottomPlane.fastSideForPoint(point);
        if (side == TPlane<T>::E_SIDE_NEGATIVE)
            return false;

        return true;
    }
}

