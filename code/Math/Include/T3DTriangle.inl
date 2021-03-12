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
    inline TTriangle<T>::TTriangle()
    {
        mVertices[0] = TReal<T>::ZERO;
        mVertices[1] = TReal<T>::ZERO;
        mVertices[2] = TReal<T>::ZERO;
    }

    template <typename T>
    inline TTriangle<T>::TTriangle(const TVector3<T> *vertices)
    {
        mVertices[0] = vertices[0];
        mVertices[1] = vertices[1];
        mVertices[2] = vertices[2];
    }

    template <typename T>
    inline TTriangle<T>::TTriangle(const T *vertices)
    {
        mVertices[0] = TVector3<T>(vertices[0], vertices[1], vertices[2]);
        mVertices[1] = TVector3<T>(vertices[3], vertices[4], vertices[5]);
        mVertices[2] = TVector3<T>(vertices[6], vertices[7], vertices[8]);
    }

    template <typename T>
    inline void TTriangle<T>::setVertices(const TVector3<T> *vertices)
    {
        mVertices[0] = vertices[0];
        mVertices[1] = vertices[1];
        mVertices[2] = vertices[2];
    }

    template <typename T>
    inline void TTriangle<T>::setVertices(const T *vertices)
    {
        mVertices[0] = TVector3<T>(vertices[0], vertices[1], vertices[2]);
        mVertices[1] = TVector3<T>(vertices[3], vertices[4], vertices[5]);
        mVertices[2] = TVector3<T>(vertices[6], vertices[7], vertices[8]);
    }

    template <typename T>
    inline const TVector3<T> &TTriangle<T>::operator [](size_t idx) const
    {
        T3D_ASSERT(idx < 3);
        return mVertices[idx];
    }

    template <typename T>
    inline TVector3<T> &TTriangle<T>::operator [](size_t idx)
    {
        T3D_ASSERT(idx < 3);
        return mVertices[idx];
    }
}

