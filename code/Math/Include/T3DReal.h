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

#ifndef __T3D_REAL_H__
#define __T3D_REAL_H__


#include "T3DMathPrerequisites.h"
#include "T3DFix32.h"
#include "T3DFix64.h"

namespace Tiny3D
{
    template <typename T>
    class TReal
    {
    public:
        static const T ZERO;
        static const T ONE;
        static const T HALF;
        static const T MINUS_ONE;
        static const T INF;
        static const T MINUS_INF;
        static const T EPSILON;
    };

    template <typename T> const T TReal<T>::ZERO;
    template <typename T> const T TReal<T>::ONE;
    template <typename T> const T TReal<T>::HALF;
    template <typename T> const T TReal<T>::MINUS_ONE;
    template <typename T> const T TReal<T>::INF;
    template <typename T> const T TReal<T>::MINUS_INF;
    template <typename T> const T TReal<T>::EPSILON;

    template <>
    class T3D_MATH_API TReal<float32_t>
    {
    public:
        static const float32_t ZERO;
        static const float32_t ONE;
        static const float32_t HALF;
        static const float32_t MINUS_ONE;
        static const float32_t INF;
        static const float32_t MINUS_INF;
        static const float32_t EPSILON;
    };

    template <>
    class T3D_MATH_API TReal<float64_t>
    {
    public:
        static const float64_t ZERO;
        static const float64_t ONE;
        static const float64_t HALF;
        static const float64_t MINUS_ONE;
        static const float64_t INF;
        static const float64_t MINUS_INF;
        static const float64_t EPSILON;
    };

    template <>
    class T3D_MATH_API TReal<fix32_t>
    {
    public:
        static const fix32_t ZERO;
        static const fix32_t ONE;
        static const fix32_t HALF;
        static const fix32_t MINUS_ONE;
        static const fix32_t INF;
        static const fix32_t MINUS_INF;
        static const fix32_t EPSILON;
    };

    template <>
    class T3D_MATH_API TReal<fix64_t>
    {
    public:
        static const fix64_t ZERO;
        static const fix64_t ONE;
        static const fix64_t HALF;
        static const fix64_t MINUS_ONE;
        static const fix64_t INF;
        static const fix64_t MINUS_INF;
        static const fix64_t EPSILON;
    };
}

// #include "T3DReal.inl"

#endif    /*__T3D_REAL_H__*/
