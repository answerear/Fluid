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
    //--------------------------------------------------------------------------

    inline void Transform::makeAffineMatrix()
    {
        Matrix3 R;
        mOrientation.toRotationMatrix(R);
        Matrix3 S(mScaling.x(), mScaling.y(), mScaling.z());
        mAffineMatrix = R * S;
        mAffineMatrix.setTranslate(mTranslation);
    }

    //--------------------------------------------------------------------------

    inline Transform::Transform()
        : mTranslation(Vector3::ZERO)
        , mScaling(Vector3::UNIT_SCALE)
        , mOrientation(Quaternion::IDENTITY)
        , mAffineMatrix(false)
    {

    }

    //--------------------------------------------------------------------------

    inline Transform::Transform(const Vector3 &translation, 
        const Vector3 &scaling, const Quaternion &orientation)
        : mTranslation(translation)
        , mScaling(scaling)
        , mOrientation(orientation)
    {
        makeAffineMatrix();
    }

    //--------------------------------------------------------------------------

    inline Transform::Transform(const Transform &other)
    {
        mTranslation = other.mTranslation;
        mOrientation = other.mOrientation;
        mScaling = other.mScaling;
        mAffineMatrix = other.mAffineMatrix;
    }

    //--------------------------------------------------------------------------

    inline Transform &Transform::operator =(const Transform &other)
    {
        mTranslation = other.mTranslation;
        mOrientation = other.mOrientation;
        mScaling = other.mScaling;
        mAffineMatrix = other.mAffineMatrix;
        return *this;
    }

    //--------------------------------------------------------------------------

    inline void Transform::setTranslation(const Vector3 &translation)
    {
        mTranslation = translation;
    }

    //--------------------------------------------------------------------------

    inline const Vector3 &Transform::getTranslation() const
    {
        return mTranslation;
    }

    //--------------------------------------------------------------------------

    inline Vector3 &Transform::getTranslation()
    {
        return mTranslation;
    }

    //--------------------------------------------------------------------------

    inline void Transform::setScaling(const Vector3 &scaling)
    {
        mScaling = scaling;
    }

    //--------------------------------------------------------------------------

    inline const Vector3 &Transform::getScaling() const
    {
        return mScaling;
    }

    //--------------------------------------------------------------------------

    inline Vector3 &Transform::getScaling()
    {
        return mScaling;
    }

    //--------------------------------------------------------------------------

    inline void Transform::setOrientation(const Quaternion &orientation)
    {
        mOrientation = orientation;
    }

    //--------------------------------------------------------------------------

    inline const Quaternion &Transform::getOrientation() const
    {
        return mOrientation;
    }

    //--------------------------------------------------------------------------

    inline Quaternion &Transform::getOrientation()
    {
        return mOrientation;
    }

    //--------------------------------------------------------------------------

    inline const Matrix4 &Transform::getAffineMatrix() const
    {
        return mAffineMatrix;
    }

    //--------------------------------------------------------------------------

    inline void Transform::update()
    {
        makeAffineMatrix();
    }
}
