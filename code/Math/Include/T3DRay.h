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

#ifndef __T3D_RAY_H__
#define __T3D_RAY_H__


#include "T3DMathPrerequisites.h"
#include "T3DVector3.h"


namespace Tiny3D
{
    /**
     * @brief 射线类
     * @remarks 这里使用 f(t) = P + t * D 的形式来表示。 其中P表示射线原点，D表示
     *      射线方向向量，|D|是射线长度，而 0 <= t <= 1。
     */
    template <typename T>
    class TRay
    {
    public:
        /// 默认构造函数
        TRay()
            : mOrigin(T(0), T(0), T(0))
            , mDirection(T(0), T(0), T(0))
        {
        }

        /// 初始化射线起点和方向的构造函数
        TRay(const TVector3<T> &rkOrigin, const TVector3<T> rkDirection)
            : mOrigin(rkOrigin)
            , mDirection(rkDirection)
        {
        }

        /// 获取射线原点位置
        const TVector3<T> &getOrigin() const
        {
            return mOrigin;
        }
        
        TVector3<T> &getOrigin()
        {
            return mOrigin;
        }

        /// 获取射线方向
        const TVector3<T> &getDirection() const
        {
            return mDirection;
        }

        TVector3<T> &getDirection()
        {
            return mDirection;
        }

        /// 设置射线原点
        void setOrigin(const TVector3<T> &origin)
        {
            mOrigin = origin;
        }

        /// 设置射线方向
        void setDirection(const TVector3<T> &direction)
        {
            mDirection = direction;
        }

    private:
        TVector3<T> mOrigin;        /// 原点
        TVector3<T> mDirection;     /// 方向
    };
}


#endif    /*__T3D_RAY_H__*/
