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

#ifndef __T3D_INTR_SPHERE_PLANE_H__
#define __T3D_INTR_SPHERE_PLANE_H__


#include "T3DMathPrerequisites.h"
#include "T3DSphere.h"
#include "T3DPlane.h"


namespace Tiny3D
{
    template <typename T>
    class TIntrSpherePlane
    {
    public:
        TIntrSpherePlane();
        TIntrSpherePlane(const TSphere<T> *sphere, const TPlane<T> *plane);
        TIntrSpherePlane(const TSphere<T> &sphere, const TPlane<T> &plane);

        /**
         * @brief 相交检测
         * @return 
         *  -  1 : 表示球与平面不相交且位于平面正面
         *  -  0 : 表示球与平面相交
         *  - -1 : 表示球与平面不相交且位于平面的背面
         */
        int32_t test();

        const TSphere<T> *getSphere() const
        {
            return mSphere;
        }

        const TPlane<T> *getPlane() const
        {
            return mPlane;
        }

        void setSphere(const TSphere<T> *sphere)
        {
            mSphere = sphere;
        }

        void setPlane(const TPlane<T> *plane)
        {
            mPlane = plane;
        }

    private:
        const TSphere<T>    *mSphere;
        const TPlane<T>     *mPlane;
    };
}


#include "T3DIntrSpherePlane.inl"


#endif  /*__T3D_INTR_SPHERE_PLANE_H__*/
