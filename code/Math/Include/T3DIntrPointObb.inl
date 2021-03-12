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
    inline TIntrPointObb<T>::TIntrPointObb()
        : mPoint(nullptr)
        , mBox(nullptr)
    {

    }

    template <typename T>
    inline TIntrPointObb<T>::TIntrPointObb(
        const TVector3<T> &point,
        const TObb<T> &box)
        : mPoint(&point)
        , mBox(&box)
    {

    }

    template <typename T>
    inline TIntrPointObb<T>::TIntrPointObb(
        const TVector3<T> *point,
        const TObb<T> *box)
        : mPoint(point)
        , mBox(box)
    {

    }

    template <typename T>
    inline bool TIntrPointObb<T>::test()
    {
        if (mPoint == nullptr || mBox == nullptr)
            return false;

        const TVector3<T> &point = *mPoint;

        // 相当于将点坐标从世界坐标系中转换到了OBB包围盒的物体坐标系中
        TVector3<T> pos = point - mBox->getCenter();

        // 求点在 X 轴上的投影
        float val = pos.dot(mBox->getAxis(0));

        // 判断投影是否大于x正方向的半长或小于x负方向半长
        if (val > mBox->getExtent(0) || val < -mBox->getExtent(0))
            return false;

        // 同理判断 Y 轴
        val = pos.dot(mBox->getAxis(1));
        if (val > mBox->getExtent(1) || val < -mBox->getExtent(1))
            return false;

        // 同理判断 Z 轴
        val = pos.dot(mBox->getAxis(2));
        if (val > mBox->getExtent(2) || val < -mBox->getExtent(2))
            return false;

        return true;
    }
}

