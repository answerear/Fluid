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


#include "T3DD3D11Sampler.h"
#include "T3DD3D11Mappings.h"
#include "T3DD3D11Context.h"


namespace Tiny3D
{
#if 0
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11SamplerCreator, SamplerCreator);

    //--------------------------------------------------------------------------

    const char * const D3D11SamplerCreator::SAMPLER_TYPE = "Sampler";

    //--------------------------------------------------------------------------

    String D3D11SamplerCreator::getType() const
    {
        return SAMPLER_TYPE;
    }

    //--------------------------------------------------------------------------

    SamplerPtr D3D11SamplerCreator::createObject(int32_t argc, ...) const
    {
        va_list params;
        va_start(params, argc);
        String name = va_arg(params, char *);
        va_end(params);
        return D3D11Sampler::create(name);
    }

    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11Sampler, Sampler);

    //--------------------------------------------------------------------------

    D3D11SamplerPtr D3D11Sampler::create(const String &name)
    {
        D3D11SamplerPtr sampler = new D3D11Sampler(name);
        sampler->release();
        return sampler;
    }

    //--------------------------------------------------------------------------

    D3D11Sampler::D3D11Sampler(const String &name)
        : Sampler(name)
        , mD3DSampler(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    D3D11Sampler::~D3D11Sampler()
    {
        D3D_SAFE_RELEASE(mD3DSampler);
    }

    //--------------------------------------------------------------------------

    TResult D3D11Sampler::load()
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Sampler::unload()
    {
        D3D_SAFE_RELEASE(mD3DSampler);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    ResourcePtr D3D11Sampler::clone() const
    {
        D3D11SamplerPtr sampler = D3D11Sampler::create(getName());

        TResult ret = cloneProperties(sampler);
        if (T3D_FAILED(ret))
        {
            sampler = nullptr;
        }

        return sampler;
    }

    //--------------------------------------------------------------------------

    ID3D11SamplerState *D3D11Sampler::getD3DSamplerState()
    {
        if (mIsDirty)
        {
            D3D_SAFE_RELEASE(mD3DSampler);

            D3D11_SAMPLER_DESC d3dDesc;
            d3dDesc.AddressU = D3D11Mappings::get(mAddressMode.u);
            d3dDesc.AddressV = D3D11Mappings::get(mAddressMode.v);
            d3dDesc.AddressW = D3D11Mappings::get(mAddressMode.w);
            d3dDesc.Filter = D3D11Mappings::get(mMinFilter, mMagFilter, mMipFilter);
            d3dDesc.MipLODBias = mMipmapBias;
            d3dDesc.BorderColor[0] = mBorderColor.red();
            d3dDesc.BorderColor[1] = mBorderColor.green();
            d3dDesc.BorderColor[2] = mBorderColor.blue();
            d3dDesc.BorderColor[3] = mBorderColor.alpha();
            d3dDesc.ComparisonFunc = D3D11Mappings::get(mCompareFunc);
            d3dDesc.MaxAnisotropy = mAnisotropy;
            d3dDesc.MinLOD = 0;
            d3dDesc.MaxLOD = D3D11_FLOAT32_MAX;

            ID3D11Device *pD3DDevice = D3D11_CONTEXT.getD3DDevice();
            HRESULT hr = S_OK;
            hr = pD3DDevice->CreateSamplerState(&d3dDesc, &mD3DSampler);
            if (FAILED(hr))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create D3D11 Sampler State failed ! DX ERROR [%d]", hr);
            }

            mIsDirty = false;
        }

        return mD3DSampler;
    }
#endif
}
