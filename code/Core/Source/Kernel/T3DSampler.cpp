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


#include "Kernel/T3DSampler.h"
#include "Kernel/T3DTextureUnit.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Sampler, Object);

    //--------------------------------------------------------------------------

    SamplerPtr Sampler::create(const String& name)
    {
        SamplerPtr sampler = new Sampler(name);
        sampler->release();
        return sampler;
    }

    //--------------------------------------------------------------------------

    Sampler::Sampler(const String &name)
        : mParent(nullptr)
        , mAddressMode()
        , mBorderColor(ColorRGBA::WHITE)
        , mMinFilter(FilterOptions::LINEAR)
        , mMagFilter(FilterOptions::LINEAR)
        , mMipFilter(FilterOptions::LINEAR)
        , mCompareFunc(CompareFunction::ALWAYS_FAIL)
        , mAnisotropy(1)
        , mMipmapBias(0.0f)
        , mCompareEnabled(true)
        , mIsDirty(true)
    {

    }

    //--------------------------------------------------------------------------

    Sampler::~Sampler()
    {

    }
}

