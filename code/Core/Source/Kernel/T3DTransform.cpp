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


#include "Kernel/T3DTransform.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    void Transform::applyTransform(const Transform &xform,
        const Vector3 &translation, const Quaternion &orientation,
        const Vector3 &scaling)
    {
        mOrientation = xform.getOrientation() * orientation;
        mScaling = xform.getScaling() * scaling;
        mTranslation = xform.getOrientation() * translation;
        mTranslation = mTranslation * xform.getScaling();
        mTranslation = xform.getTranslation() + mTranslation;
        makeAffineMatrix();
    }

    //--------------------------------------------------------------------------

    void Transform::applyTransform(const Transform &xform1,
        const Transform &xform2)
    {
        applyTransform(xform1, xform2.getTranslation(), xform2.getOrientation(),
            xform2.getScaling());
    }
}
