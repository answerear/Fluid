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
    inline const String &RenderTarget::getName() const
    {
        return mName;
    }

    inline void RenderTarget::getMetrics(size_t &width, size_t &height, 
        size_t &clrDepth) const
    {
        width = mWidth;
        height = mHeight;
        clrDepth = mColorDepth;
    }

    inline size_t RenderTarget::getWidth() const
    {
        return mWidth;
    }

    inline size_t RenderTarget::getHeight() const
    {
        return mHeight;
    }

    inline size_t RenderTarget::getColorDepth() const
    {
        return mColorDepth;
    }

    inline size_t RenderTarget::getPitch() const
    {
        return mPitch;
    }

    inline bool RenderTarget::isActive() const
    {
        return mIsActive;
    }

    inline void RenderTarget::setActive(bool active)
    {
        mIsActive = active;
    }

    inline size_t RenderTarget::getNumViewports() const
    {
        return mViewportList.size();
    }

    inline ViewportPtr RenderTarget::getViewport(long_t zOrder) const
    {
        auto itr = mViewportList.find(zOrder);

        if (itr != mViewportList.end())
        {
            return itr->second;
        }

        return nullptr;
    }
}

