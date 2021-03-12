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


#include "Render/T3DRenderState.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    BlendStatePtr BlendState::create()
    {
        BlendStatePtr state = new BlendState();
        state->release();
        return state;
    }

    //--------------------------------------------------------------------------

    BlendState::BlendState()
    {

    }

    //--------------------------------------------------------------------------

    BlendState::~BlendState()
    {

    }

    //--------------------------------------------------------------------------

    DepthStencilStatePtr DepthStencilState::create()
    {
        DepthStencilStatePtr state = new DepthStencilState();
        state->release();
        return state;
    }

    //--------------------------------------------------------------------------

    DepthStencilState::DepthStencilState()
    {

    }

    //--------------------------------------------------------------------------

    DepthStencilState::~DepthStencilState()
    {

    }

    //--------------------------------------------------------------------------

    RasterizerStatePtr RasterizerState::create()
    {
        RasterizerStatePtr state = new RasterizerState();
        state->release();
        return state;
    }

    //--------------------------------------------------------------------------

    RasterizerState::RasterizerState()
    {

    }

    //--------------------------------------------------------------------------

    RasterizerState::~RasterizerState()
    {

    }

    //--------------------------------------------------------------------------

    SamplerStatePtr SamplerState::create()
    {
        SamplerStatePtr state = new SamplerState();
        state->release();
        return state;
    }

    //--------------------------------------------------------------------------

    SamplerState::SamplerState()
    {

    }

    //--------------------------------------------------------------------------

    SamplerState::~SamplerState()
    {

    }
}
