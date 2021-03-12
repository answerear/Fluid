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

    inline void Camera::setObjectMask(uint32_t mask)
    {
        mObjectMask = mask;
    }

    //--------------------------------------------------------------------------

    inline uint32_t Camera::getObjectMask() const
    {
        return mObjectMask;
    }

    //--------------------------------------------------------------------------

    inline BoundPtr Camera::getBound() const
    {
        return mBound;
    }

    //--------------------------------------------------------------------------

    inline void Camera::setProjectionType(Type type)
    {
        if (mProjType != type)
        {
            mProjType = type;
            mIsFrustumDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline Camera::Type Camera::getProjectionType() const
    {
        return mProjType;
    }

    //--------------------------------------------------------------------------

    inline void Camera::setPerspectiveParams(const Radian &fovY, Real aspect,
        Real nearDist, Real farDist)
    {
        if (mFovY != fovY)
        {
            mFovY = fovY;
            mIsFrustumDirty = true;
        }

        if (mAspectRatio != aspect)
        {
            mAspectRatio = aspect;
            mIsFrustumDirty = true;
        }

        if (nearDist != mNear)
        {
            mNear = nearDist;
            mIsFrustumDirty = true;
        }

        if (farDist != mFar)
        {
            mFar = farDist;
            mIsFrustumDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline void Camera::setOrthographicParams(Real width, Real height,
        Real nearDist, Real farDist)
    {
        if (width != mWidth)
        {
            mWidth = width;
            mIsFrustumDirty = true;
        }

        if (height != mHeight)
        {
            mHeight = height;
            mIsFrustumDirty = true;
        }

        if (nearDist != mNear)
        {
            mNear = nearDist;
            mIsFrustumDirty = true;
        }

        if (farDist != mFar)
        {
            mFar = farDist;
            mIsFrustumDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline Real Camera::getAspectRatio() const
    {
        return mAspectRatio;
    }

    //--------------------------------------------------------------------------

    inline const Radian &Camera::getFovY() const
    {
        return mFovY;
    }

    //--------------------------------------------------------------------------

    inline Real Camera::getNearPlaneDistance() const
    {
        return mNear;
    }

    //--------------------------------------------------------------------------

    inline Real Camera::getFarPlaneDistance() const
    {
        return mFar;
    }
}
