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

#ifndef __T3D_SPHERE_H__
#define __T3D_SPHERE_H__


#include "T3DMathPrerequisites.h"
#include "T3DVector3.h"
#include "T3DMatrix3.h"
#include "T3DReal.h"


namespace Tiny3D
{
    /// 球类
    template <typename T>
    class TSphere
    {
    public:
        enum class BuildOption : uint32_t
        {
            WELZL = 0,      /// Welzl最小包围球算法
            RITTER = 1,     /// Ritter包围球算法
            AVERAGE = 2,    /// 均值法
        };

        /// 默认构造函数
        TSphere();
        /// 通过空间一个点构造包围球
        TSphere(const TVector3<T> &p0);
        /// 通过空间两点构造包围球
        TSphere(const TVector3<T> &p0, const TVector3<T> &p1);
        /// 通过空间三点构造包围球
//         TSphere(const TVector3<T> &p0, const TVector3<T> &p1,
//             const TVector3<T> &p2);
//         /// 通过空间四点构造包围球
//         TSphere(const TVector3<T> &p0, const TVector3<T> &p1,
//             const TVector3<T> &p2, const TVector3<T> &p3);
        /// 初始化原点和半径的构造函数
        TSphere(const TVector3<T> &center, const T &radius);

        /// 拷贝构造函数
        TSphere(const TSphere &sphere);

        /// 重载赋值运算符
        TSphere &operator =(const TSphere &sphere);

        /// 通过多个点构造包围球
        void build(const TVector3<T> points[], size_t count, 
            BuildOption option = BuildOption::RITTER);

        /// 通过空间三点构造包围球
        bool build(const TVector3<T> &p0, const TVector3<T> &p1,
            const TVector3<T> &p2);

        /// 通过空间四点构造包围球
        bool build(const TVector3<T> &p0, const TVector3<T> &p1,
            const TVector3<T> &p2, const TVector3<T> &p3);
        
        /// 获取球心
        const TVector3<T> &getCenter() const;
        TVector3<T> &getCenter();

        /// 获取半径
        const T &getRadius() const;
        T &getRadius();

            /// 设置球心
        void setCenter(const TVector3<T> &center);

        /// 设置半径
        void setRadius(const T &radius);

        /// 检测指定点是否在球内部
        bool contains(const TVector3<T> &point) const;

    protected:
        /// Welzl最小包围球算法生成包围球
        void buildByWelzl(const TVector3<T> points[], size_t count);

        TSphere recurseMinSphere(TVector3<T> *points[], size_t count, size_t b = 0);

        /// Ritter逼近修正算法生成包围球
        void buildByRitter(const TVector3<T> points[], size_t count);

        /// 简单粗暴的均值法生成包围球
        void buildByAverage(const TVector3<T> points[], size_t count);

    private:
        TVector3<T> mCenter;    /// 球心
        T           mRadius;    /// 半径
    };
}

#include "T3DSphere.inl"

#endif    /*__T3D_SPHERE_H__*/
