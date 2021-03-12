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


#include "T3DIntrObbPlane.h"


namespace Tiny3D
{
    template <typename T>
    inline TIntrFrustumObb<T>::TIntrFrustumObb()
        : mFrustum(nullptr)
        , mBox(nullptr)
    {

    }

    template <typename T>
    inline TIntrFrustumObb<T>::TIntrFrustumObb(
        const TFrustum<T> &frustum,
        const TObb<T> &box)
        : mFrustum(&frustum)
        , mBox(&box)
    {

    }

    template <typename T>
    inline TIntrFrustumObb<T>::TIntrFrustumObb(
        const TFrustum<T> *frustum,
        const TObb<T> *box)
        : mFrustum(frustum)
        , mBox(box)
    {

    }

    template <typename T>
    inline bool TIntrFrustumObb<T>::test()
    {
        if (mFrustum == nullptr || mBox == nullptr)
            return false;

        TIntrObbPlane<T> intr;
        int32_t result;

        intr.setBox(mBox);

        intr.setPlane(&mFrustum->getFace(TFrustum<T>::E_FACE_NEAR));
        result = intr.test();
        if (result < 0)
            return false;

        intr.setPlane(&mFrustum->getFace(TFrustum<T>::E_FACE_FAR));
        result = intr.test();
        if (result < 0)
            return false;

        intr.setPlane(&mFrustum->getFace(TFrustum<T>::E_FACE_LEFT));
        result = intr.test();
        if (result < 0)
            return false;

        intr.setPlane(&mFrustum->getFace(TFrustum<T>::E_FACE_RIGHT));
        result = intr.test();
        if (result < 0)
            return false;

        intr.setPlane(&mFrustum->getFace(TFrustum<T>::E_FACE_TOP));
        result = intr.test();
        if (result < 0)
            return false;

        intr.setPlane(&mFrustum->getFace(TFrustum<T>::E_FACE_BOTTOM));
        result = intr.test();
        if (result < 0)
            return false;

        return true;
    }
}

