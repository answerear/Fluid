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

#ifndef __T3D_MATH_H__
#define __T3D_MATH_H__


#include "T3DMathPrerequisites.h"
#include <math.h>
#include "T3DFix32.h"
#include "T3DFix64.h"
#include "T3DRadian.h"
#include "T3DDegree.h"


namespace Tiny3D
{
    template <typename T>
    class TMath
    {
    public:
        /// 求平方.
        static T sqr(T value);
        /// 求平方根.
        static T sqrt(T value);
        /// 求平方根倒数.
        static T invSqrt(T value);

        /// 求绝对值
        static T abs(T value);
        static TDegree<T> abs(const TDegree<T>& value);
        static TRadian<T> abs(const TRadian<T>& value);

        /// 根据误差值判断两个实数是否相等.
        static bool realEqual(T a, T b, 
            T tolerance = std::numeric_limits<T>::epsilon());

        /// 通过角度求正弦值.
        static T sin(const TDegree<T> &degrees);
        /// 通过弧度求正弦值.
        static T sin(const TRadian<T> &radians);
        /// 通过角度求余弦值.
        static T cos(const TDegree<T> &degrees);
        /// 通过弧度求余弦值.
        static T cos(const TRadian<T> &radians);
        /// 通过角度求正切值.
        static T tan(const TDegree<T> &degrees);
        /// 通过弧度求正切值.
        static T tan(const TRadian<T> &radians);

        /// 求反正弦.
        static TRadian<T> asin(T value);
        /// 求反余弦.
        static TRadian<T> acos(T value);
        /// 求反正切.
        static TRadian<T> atan(T value);
        /// 通过 y/x 求反正切
        static TRadian<T> atan2(T y, T x);

        static T degreesToRadians(T degrees);
        static T radiansToDegrees(T radians);

        static T max(T a, T b);
        static T min(T a, T b);

    public:
        static const T POS_INFINITY;
        static const T NEG_INFINITY;
        static const T PI;
        static const T TWO_PI;
        static const T HALF_PI;
        static const T DEGREES_TO_RADIANS;
        static const T RADIANS_TO_DEGREES;
    };
}


#include "T3DMath.inl"


#endif  /*__T3D_MATH_H__*/
