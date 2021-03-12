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


#include "Render/T3DRenderTarget.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(RenderTarget, Object);

    //--------------------------------------------------------------------------

    RenderTarget::RenderTarget(const String &name)
        : mWidth(0)
        , mHeight(0)
        , mColorDepth(0)
        , mIsActive(true)
        , mName(name)
    {

    }

    RenderTarget::~RenderTarget()
    {

    }

    //--------------------------------------------------------------------------

    void RenderTarget::render()
    {
        auto itr = mViewportList.begin();

        while (itr != mViewportList.end())
        {
            itr->second->render();
            ++itr;
        }
    }

    //--------------------------------------------------------------------------

    ViewportPtr RenderTarget::addViewport(CameraPtr camera, long_t zOrder,
        Real left, Real top, Real width, Real height)
    {
        ViewportPtr viewport;

        auto itr = mViewportList.find(zOrder);

        if (itr == mViewportList.end())
        {
            viewport = Viewport::create(camera, this, left, top, 
                width, height, zOrder);
            mViewportList.insert(ViewportValue(zOrder, viewport));
        }

        return viewport;
    }

    //--------------------------------------------------------------------------

    TResult RenderTarget::removeViewport(long_t nZOrder)
    {
        TResult ret = T3D_OK;

        do 
        {
            auto itr = mViewportList.find(nZOrder);

            if (itr == mViewportList.end())
            {
                ret = T3D_ERR_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_RENDER,
                    "RenderTarget remove viewport but not found !!!");
                break;
            }

            mViewportList.erase(itr);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult RenderTarget::removeAllViewports()
    {
        mViewportList.clear();
        return T3D_OK;
    }
}

