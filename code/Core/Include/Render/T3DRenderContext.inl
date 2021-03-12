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

    inline const String &RenderContext::getName() const
    {
        return mName;
    }

    //--------------------------------------------------------------------------

    inline TResult RenderContext::setViewTransform(const Matrix4 &mat)
    {
        return setTransform(TransformState::VIEW, mat);
    }

    //--------------------------------------------------------------------------

    inline TResult RenderContext::setWorldTransform(const Matrix4 &mat)
    {
        return setTransform(TransformState::WORLD, mat);
    }

    //--------------------------------------------------------------------------

    inline TResult RenderContext::setProjectionTransform(const Matrix4 &mat)
    {
        return setTransform(TransformState::PROJECTION, mat);
    }

    //--------------------------------------------------------------------------

    inline ViewportPtr RenderContext::getViewport() const
    {
        return mViewport;
    }

    //--------------------------------------------------------------------------
// 
//     inline HardwareConstantBufferPtr Renderer::getConstantBuffer(size_t slot) const
//     {
//         T3D_ASSERT(slot < mConstBuffers.size());
//         return mConstBuffers[slot];
//     }
// 
//     //--------------------------------------------------------------------------
// 
//     inline GPUProgramPtr Renderer::getGPUProgram() const
//     {
//         return mGPUProgram;
//     }
}

