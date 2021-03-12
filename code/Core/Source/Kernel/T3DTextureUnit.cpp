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


#include "Kernel/T3DTextureUnit.h"
#include "Kernel/T3DPass.h"
#include "Kernel/T3DSampler.h"
#include "Resource/T3DTexture.h"
#include "Resource/T3DTextureManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(TextureUnit, Object);

    //--------------------------------------------------------------------------

    TextureUnitPtr TextureUnit::create(const String &name, Pass *pass)
    {
        TextureUnitPtr unit = new TextureUnit(name, pass);
        unit->release();
        return unit;
    }

    //--------------------------------------------------------------------------

    TextureUnit::TextureUnit(const String &name, Pass *pass)
        : mParent(pass)
        , mName(name)
        , mSampler(nullptr)
        , mCurrentFrame(0)
    {

    }

    //--------------------------------------------------------------------------

    TextureUnit::~TextureUnit()
    {

    }

    //--------------------------------------------------------------------------

    const String &TextureUnit::getTextureName() const
    {
        if (mCurrentFrame < mFrames.size() && mFrames[mCurrentFrame] != nullptr)
        {
            return mFrames[mCurrentFrame]->getName();
        }

        return BLANKSTRING;
    }

    //--------------------------------------------------------------------------

    void TextureUnit::setTextureName(const String &name)
    {
        do 
        {
            TexturePtr texture = T3D_TEXTURE_MGR.loadTexture(name);
            if (texture == nullptr)
            {
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Load texture [%s] for texture unit failed !", 
                    name.c_str());
                break;
            }

            mFrames.resize(1);
            mFrames[0] = texture;
            mCurrentFrame = 0;
        } while (0);
    }
}
