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

#ifndef __T3D_D3D11_STATE_H__
#define __T3D_D3D11_STATE_H__


#include "T3DD3D11Prerequisites.h"
#include "T3DD3D11Error.h"


namespace Tiny3D
{
    class D3D11BlendState : public BlendState
    {
    public:
        static D3D11BlendStatePtr create();

        virtual ~D3D11BlendState();

        ID3D11BlendState* getD3DState();

    protected:
        D3D11BlendState();

        D3D11_BLEND_DESC    mD3DDesc;
        ID3D11BlendState    *mD3DState;
    };

    class D3D11DepthStencilState : public DepthStencilState
    {
    public:
        static D3D11DepthStencilStatePtr create();

        virtual ~D3D11DepthStencilState();

        ID3D11DepthStencilState* getD3DState();

    protected:
        D3D11DepthStencilState();

        D3D11_DEPTH_STENCIL_DESC    mD3DDesc;
        ID3D11DepthStencilState     *mD3DState;
    };

    class D3D11RasterizerState : public RasterizerState
    {
    public:
        static D3D11RasterizerStatePtr create();

        virtual ~D3D11RasterizerState();

        ID3D11RasterizerState* getD3DState();

    protected:
        D3D11RasterizerState();

        D3D11_RASTERIZER_DESC   mD3DDesc;
        ID3D11RasterizerState   *mD3DState;
    };

    class D3D11SamplerState : public SamplerState
    {
    public:
        static D3D11SamplerStatePtr create();

        virtual ~D3D11SamplerState();

        ID3D11SamplerState* getD3DState();

    protected:
        D3D11SamplerState();

        D3D11_SAMPLER_DESC  mD3DDesc;
        ID3D11SamplerState  *mD3DState;
    };
}

#endif  /*__T3D_D3D11_STATE_H__*/
