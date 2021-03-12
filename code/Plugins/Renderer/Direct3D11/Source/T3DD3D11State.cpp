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


#include "T3DD3D11State.h"
#include "T3DD3D11Error.h"
#include "T3DD3D11Mappings.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    D3D11BlendStatePtr D3D11BlendState::create()
    {
        D3D11BlendStatePtr state = new D3D11BlendState();
        state->release();
        return state;
    }

    //--------------------------------------------------------------------------

    D3D11BlendState::D3D11BlendState()
        : mD3DState(nullptr)
    {
        memset(&mD3DDesc, 0, sizeof(mD3DDesc));
    }

    //--------------------------------------------------------------------------

    D3D11BlendState::~D3D11BlendState()
    {
        D3D_SAFE_RELEASE(mD3DState);
    }

    //--------------------------------------------------------------------------

    TResult D3D11BlendState::update(ID3D11Device *device)
    {
        if (mIsDirty)
        {
            D3D_SAFE_RELEASE(mD3DState);

            memset(&mD3DDesc, 0, sizeof(mD3DDesc));
            D3D11Mappings::get(mD3DDesc, *this);

            HRESULT hr = device->CreateBlendState(&mD3DDesc, &mD3DState);
            if (FAILED(hr))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create ID3D11BlendState failed ! DX ERROR [%d]", hr);
                return T3D_ERR_D3D11_CREATE_FAILED;
            }

            mIsDirty = false;
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    D3D11DepthStencilStatePtr D3D11DepthStencilState::create()
    {
        D3D11DepthStencilStatePtr state = new D3D11DepthStencilState();
        state->release();
        return state;
    }

    //--------------------------------------------------------------------------

    D3D11DepthStencilState::D3D11DepthStencilState()
        : mD3DState(nullptr)
    {
        memset(&mD3DDesc, 0, sizeof(mD3DDesc));
    }

    //--------------------------------------------------------------------------

    D3D11DepthStencilState::~D3D11DepthStencilState()
    {
        D3D_SAFE_RELEASE(mD3DState);
    }

    //--------------------------------------------------------------------------

    TResult D3D11DepthStencilState::update(ID3D11Device* device)
    {
        if (mIsDirty)
        {
            D3D_SAFE_RELEASE(mD3DState);

            memset(&mD3DDesc, 0, sizeof(mD3DDesc));
            D3D11Mappings::get(mD3DDesc, *this);

            HRESULT hr = device->CreateDepthStencilState(&mD3DDesc, &mD3DState);
            if (FAILED(hr))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create ID3D11DepthStencilState failed ! DX ERROR [%d]", hr);
                return T3D_ERR_D3D11_CREATE_FAILED;
            }

            mIsDirty = false;
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    D3D11RasterizerStatePtr D3D11RasterizerState::create()
    {
        D3D11RasterizerStatePtr state = new D3D11RasterizerState();
        state->release();
        return state;
    }

    //--------------------------------------------------------------------------

    D3D11RasterizerState::D3D11RasterizerState()
        : mD3DState(nullptr)
    {
        memset(&mD3DDesc, 0, sizeof(mD3DDesc));
    }

    //--------------------------------------------------------------------------

    D3D11RasterizerState::~D3D11RasterizerState()
    {
        D3D_SAFE_RELEASE(mD3DState);
    }

    //--------------------------------------------------------------------------

    TResult D3D11RasterizerState::update(ID3D11Device* device)
    {
        if (mIsDirty)
        {
            D3D_SAFE_RELEASE(mD3DState);

            memset(&mD3DDesc, 0, sizeof(mD3DDesc));
            D3D11Mappings::get(mD3DDesc, *this);

            HRESULT hr = device->CreateRasterizerState(&mD3DDesc, &mD3DState);
            if (FAILED(hr))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create ID3D11RasterizerState failed ! DX ERROR [%d]", hr);
                return T3D_ERR_D3D11_CREATE_FAILED;
            }

            mIsDirty = false;
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    D3D11SamplerStatePtr D3D11SamplerState::create()
    {
        D3D11SamplerStatePtr state = new D3D11SamplerState();
        state->release();
        return state;
    }

    //--------------------------------------------------------------------------

    D3D11SamplerState::D3D11SamplerState()
        : mD3DState(nullptr)
    {
        memset(&mD3DDesc, 0, sizeof(mD3DDesc));
    }

    //--------------------------------------------------------------------------

    D3D11SamplerState::~D3D11SamplerState()
    {
        D3D_SAFE_RELEASE(mD3DState);
    }

    //--------------------------------------------------------------------------

    TResult D3D11SamplerState::update(ID3D11Device* device)
    {
        if (mIsDirty)
        {
            D3D_SAFE_RELEASE(mD3DState);

            memset(&mD3DDesc, 0, sizeof(mD3DDesc));
            D3D11Mappings::get(mD3DDesc, *this);

            HRESULT hr = device->CreateSamplerState(&mD3DDesc, &mD3DState);
            if (FAILED(hr))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create ID3D11SamplerState failed ! DX ERROR [%d]", hr);
                return T3D_ERR_D3D11_CREATE_FAILED;
            }

            mIsDirty = false;
        }

        return T3D_OK;
    }

}
