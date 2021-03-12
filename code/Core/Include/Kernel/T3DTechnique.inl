﻿/*******************************************************************************
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

    inline const String &Technique::getName() const
    {
        return mName;
    }

    //--------------------------------------------------------------------------

    inline uint32_t Technique::getRenderQueue() const
    {
        return mRenderQueue;
    }

    //--------------------------------------------------------------------------

    inline void Technique::setRenderQueue(uint32_t queue)
    {
        mRenderQueue = queue;
    }

    //--------------------------------------------------------------------------

    inline Material *Technique::getMaterial() const
    { 
        return mParent; 
    }

    //--------------------------------------------------------------------------

    inline PassPtr Technique::getPass(size_t index) const
    {
        T3D_ASSERT(index < mPasses.size());
        return mPasses[index];
    }

    //--------------------------------------------------------------------------

    inline const Technique::Passes &Technique::getPasses() const 
    { 
        return mPasses; 
    }

    //--------------------------------------------------------------------------

    inline size_t Technique::getPassCount() const 
    { 
        return mPasses.size(); 
    }
}
