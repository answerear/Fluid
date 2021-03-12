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

#ifndef __T3D_OBB_H__
#define __T3D_OBB_H__


#include "T3DMathPrerequisites.h"
#include "T3DVector3.h"


namespace Tiny3D
{
    /**
     * @brief 有向包围盒类（Oriented Bounding Box）
     */
    template <typename T>
    class TObb
    {
    public:
        enum BuildOption
        {
            E_BUILD_AABB = 0,       /**< 通过AABB直接构造 */
            E_BUILD_COVARIANCE = 1, /**< 利用协方差矩阵构造 */
        };

        /// 默认构造函数
        TObb();
        TObb(const TVector3<T> &rkCenter, const TVector3<T> *akAxis,
            const T *afExtent);
        TObb(const TVector3<T> &rkCenter, const TVector3<T> &rkAxis0,
            const TVector3<T> &rkAxis1, const TVector3<T> &rkAxis2,
            T fExtent0, T fExtent1, T fExtent2);

        void build(const TVector3<T> points[], size_t count, 
            BuildOption option = E_BUILD_AABB);

        void computeVertices(TVector3<T> *akVertex) const;

        const TVector3<T> &getCenter() const;

        const TVector3<T> &getAxis(int32_t idx) const;

        const TVector3<T> *getAxis() const;

        T getExtent(int32_t idx) const;

        const T *getExtent() const;

        void setCenter(const TVector3<T> &rkCenter);

        void setAxis(const TVector3<T> &rkAxis0, const TVector3<T> &rkAxis1,
            const TVector3<T> &rkAxis2);

        void setExtent(int32_t idx, T fExtent);

    protected:
        void buildByAABB(const TVector3<T> points[], size_t count);

        void buildByCovariance(const TVector3<T> points[], size_t count);

    private:
        TVector3<T> mCenter;
        TVector3<T> mAxis[3];
        T           mExtent[3];
    };
}

#include "T3DObb.inl"

#endif    /*__T3D_OBB_H__*/
