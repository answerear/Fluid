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

#ifndef __T3D_AABB_H__
#define __T3D_AABB_H__


#include "T3DMathPrerequisites.h"
#include "T3DSphere.h"


namespace Tiny3D
{
    /// 轴对齐包围盒类（Axis Aligned Bounding Box）
    template <typename T>
    class TAabb
    {
    public:
        /// 默认构造函数
        TAabb();
        TAabb(T fXMin, T fXMax, T fYMin, T fYMax, T fZMin, T fZMax);

        void build(const TVector3<T> points[], size_t count);

        T getWidth() const;
        T getHeight() const;
        T getDepth() const;

        T getMinX() const;
        T getMaxX() const;

        T getMinY() const;
        T getMaxY() const;

        T getMinZ() const;
        T getMaxZ() const;

        const TVector3<T> &getCenter() const;
        T getRadius() const;

        const TSphere<T> &getSphere() const;
        
        void setWidth(T fWidth);
        void setHeight(T fHeight);
        void setDepth(T fDepth);

        void setMinX(T x);
        void setMaxX(T x);

        void setMinY(T y);
        void setMaxY(T y);

        void setMinZ(T z);
        void setMaxZ(T z);

        void setParam(const TVector3<T> &vMin, const TVector3<T> &vMax);

    private:
        T   mMinX;
        T   mMaxX;

        T   mMinY;
        T   mMaxY;

        T   mMinZ;
        T   mMaxZ;

        TSphere<T>  mSphere;
    };
}

#include "T3DAabb.inl"

#endif    /*__T3D_AABB_H__*/
