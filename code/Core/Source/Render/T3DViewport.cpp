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


#include "Render/T3DViewport.h"
#include "Render/T3DRenderTarget.h"
#include "Component/T3DCamera.h"
#include "Scene/T3DSceneManager.h"
#include "Kernel/T3DAgent.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Viewport, Object);

    //--------------------------------------------------------------------------

    ViewportPtr Viewport::create(CameraPtr camera, RenderTargetPtr target,
        Real left, Real top, Real width, Real height, long_t nZOrder)
    {
        ViewportPtr viewport = new Viewport(camera, target, left, top, 
            width, height, nZOrder);
        viewport->release();
        return viewport;
    }

    //--------------------------------------------------------------------------

    Viewport::Viewport(CameraPtr camera, RenderTargetPtr target,
        Real left, Real top, Real width, Real height, long_t zOrder)
        : mCamera(camera)
        , mRenderTarget(target)
        , mLeft(left)
        , mTop(top)
        , mWidth(width)
        , mHeight(height)
        , mActualLeft(0)
        , mActualTop(0)
        , mActualWidth(0)
        , mActualHeight(0)
        , mClearFlags(0)
        , mClearZ(1.0f)
        , mBkgndColor(0, 0, 0)
        , mMatrix(false)
    {
        updateDimensions();
    }

    //--------------------------------------------------------------------------

    Viewport::~Viewport()
    {

    }

    //--------------------------------------------------------------------------

    void Viewport::render()
    {
        T3D_SCENE_MGR.render(this);
    }

    //--------------------------------------------------------------------------

    void Viewport::setDimensions(Real left, Real top, Real width, Real height)
    {
        mLeft = left;
        mTop = top;
        mWidth = width;
        mHeight = height;

        updateDimensions();
    }

    //--------------------------------------------------------------------------

    void Viewport::updateDimensions()
    {
        size_t nWidth = mRenderTarget->getWidth();
        size_t nHeight = mRenderTarget->getHeight();

        mActualLeft = size_t(nWidth * mLeft);
        mActualTop = size_t(nHeight * mTop);
        mActualWidth = size_t(nWidth * mWidth);
        mActualHeight = size_t(nHeight * mHeight);

        RenderContextPtr renderer = T3D_AGENT.getActiveRenderer();
        mMatrix = renderer->makeViewportMatrix(this);
    }
}

