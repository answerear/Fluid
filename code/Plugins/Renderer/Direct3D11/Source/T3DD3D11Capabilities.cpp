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


#include "T3DD3D11Prerequisites.h"
#include "T3DD3D11Capabilities.h"
#include "T3DD3D11Context.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11Capabilities, RenderCapabilities);

    //--------------------------------------------------------------------------

    D3D11CapabilitiesPtr D3D11Capabilities::create()
    {
        D3D11CapabilitiesPtr cap = new D3D11Capabilities();
        if (cap != nullptr && cap->init() == T3D_OK)
        {
            cap->release();
        }
        else
        {
            cap = nullptr;
        }
        return cap;
    }

    //--------------------------------------------------------------------------

    D3D11Capabilities::D3D11Capabilities()
    {

    }

    //--------------------------------------------------------------------------

    D3D11Capabilities::~D3D11Capabilities()
    {

    }

    //--------------------------------------------------------------------------

    TResult D3D11Capabilities::init()
    {
        TResult ret = T3D_OK;

        ID3D11Device *pD3DDevice = D3D11_CONTEXT.getD3DDevice();

        // 驱动信息
        mDriverVersion = D3D11_CONTEXT.getDriverVersion();
        mDeviceName = D3D11_CONTEXT.getDeviceName();
        mRendererName = D3D11_CONTEXT.getName();

        // 一些限定值
        mNumTextureUnits = 16;
        mNumVertexTextureUnits = 4;
        mStencilBufferBitDepth = 8;

#ifdef D3D_FEATURE_LEVEL_9_3
        int numMultiRenderTargets = (mFeatureLevel > D3D_FEATURE_LEVEL_9_3) ? D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT :      // 8
            (mFeatureLevel == D3D_FEATURE_LEVEL_9_3) ? 4/*D3D_FL9_3_SIMULTANEOUS_RENDER_TARGET_COUNT*/ :    // 4
            1/*D3D_FL9_1_SIMULTANEOUS_RENDER_TARGET_COUNT*/;
#else
        int numMultiRenderTargets = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; // 8
#endif

        mNumMultiRenderTargets = std::min(numMultiRenderTargets, 
            (int)T3D_MAX_MULTIPLE_RENDER_TARGETS);

        mNumVertexAttributes = D3D11_STANDARD_VERTEX_ELEMENT_COUNT;

        mVSConstantFloatCount = 512;
        mVSConstantIntCount = 16;
        mVSConstantBoolCount = 16;

        mGSConstantFloatCount = 512;
        mGSConstantIntCount = 16;
        mGSConstantBoolCount = 16;
        mGSNumOutputVertices = 1024;

        mPSConstantFloatCount = 512;
        mPSConstantIntCount = 16;
        mPSConstantBoolCount = 16;

        mCSConstantFloatCount = 512;
        mCSConstantIntCount = 16;
        mCSConstantBoolCount = 16;

        mMaxPointSize = 256.0f;

        mNPOTLimited = true;

        // 能力值
        D3D_FEATURE_LEVEL featureLevel = D3D11_CONTEXT.getFeatureLevel();

        uint32_t fmtSupport;
        HRESULT hr = S_OK;
        hr = pD3DDevice->CheckFormatSupport(DXGI_FORMAT_R32_UINT, &fmtSupport);
        if (featureLevel >= D3D_FEATURE_LEVEL_9_2 || SUCCEEDED(hr)
            && 0 != (fmtSupport & D3D11_FORMAT_SUPPORT_IA_INDEX_BUFFER))
        {
            setCapability(Capabilities::INDEX_32BITS);
        }

        if (featureLevel >= D3D_FEATURE_LEVEL_10_0)
        {
            setCapability(Capabilities::TWO_SIDED_STENCIL);
            setCapability(Capabilities::GEOMETRY_SHADER);
            setCapability(Capabilities::COMPUTE_SHADER);
            setCapability(Capabilities::HWRENDER_TO_VERTEX_BUFFER);
            setCapability(Capabilities::HWRENDER_TO_TEXTURE_3D);
            setCapability(Capabilities::TEXTURE_1D);
            setCapability(Capabilities::NON_POWER_OF_2_TEXTURES);
            setCapability(Capabilities::TEXTURE_COMPRESSION_BC4_BC5);
        }

        if (featureLevel >= D3D_FEATURE_LEVEL_11_0)
        {
            mHSConstantFloatCount = 512;
            mHSConstantIntCount = 16;
            mHSConstantBoolCount = 16;

            mDSConstantFloatCount = 512;
            mDSConstantIntCount = 16;
            mDSConstantBoolCount = 16;

            setCapability(Capabilities::SHADER_SUBROUTINE);

            setCapability(Capabilities::TESSELLATION_HULL_SHADER);
            setCapability(Capabilities::TESSELLATION_DOMAIN_SHADER);
            setCapability(Capabilities::TEXTURE_COMPRESSION_BC6_BC7);
        }

        setCapability(Capabilities::PRIMITIVE_RESTART);
        setCapability(Capabilities::ANISOTROPY);
        setCapability(Capabilities::WRAP_STENCIL);
        setCapability(Capabilities::HWSTENCIL);
        setCapability(Capabilities::HWOCCLUSION);
        setCapability(Capabilities::HWOCCLUSION_ASYNCHRONOUS);
        setCapability(Capabilities::HWRENDER_TO_TEXTURE);
        setCapability(Capabilities::TEXTURE_FLOAT);
        setCapability(Capabilities::TEXTURE_3D);
        setCapability(Capabilities::USER_CLIP_PLANES);
        setCapability(Capabilities::VERTEX_FORMAT_UBYTE4);
        setCapability(Capabilities::INFINITE_FAR_PLANE);
        setCapability(Capabilities::POINT_SPRITES);
        setCapability(Capabilities::POINT_EXTENDED_PARAMETERS);
        setCapability(Capabilities::VERTEX_TEXTURE_FETCH);
        setCapability(Capabilities::MIPMAP_LOD_BIAS);
        setCapability(Capabilities::MRT_DIFFERENT_BIT_DEPTHS);
        setCapability(Capabilities::ALPHA_TO_COVERAGE);
        setCapability(Capabilities::RTT_MAIN_DEPTHBUFFER_ATTACHABLE);
        setCapability(Capabilities::VERTEX_BUFFER_INSTANCE_DATA);
        setCapability(Capabilities::CAN_GET_COMPILED_SHADER_BUFFER);
        setCapability(Capabilities::VERTEX_SHADER);
        setCapability(Capabilities::PIXEL_SHADER);
        setCapability(Capabilities::TEXTURE_COMPRESSION);
        setCapability(Capabilities::TEXTURE_COMPRESSION_DXT);

        // unsetCapability(Capabilities::AUTOMIPMAP_COMPRESSED);
        // unsetCapability(Capabilities::WIDE_LINES);
        // unsetCapability(Capabilities::ATOMIC_COUNTERS);
        // unsetCapability(Capabilities::HW_GAMMA);
        // unsetCapability(Capabilities::RTT_DEPTHBUFFER_RESOLUTION_LESSEQUAL);
        // unsetCapability(Capabilityes::TEXTURE_COMPRESSION_VTC);
        // unsetCapability(Capabilityes::TEXTURE_COMPRESSION_PVRTC);
        // unsetCapability(Capabilityes::TEXTURE_COMPRESSION_ASTC);
        // unsetCapability(Capabilityes::TEXTURE_COMPRESSION_ATC);
        // unsetCapability(Capabilityes::TEXTURE_COMPRESSION_ETC1);
        // unsetCapability(Capabilityes::TEXTURE_COMPRESSION_ETC2);

        // 能力组
        mCategoryRelevant[CapabilitiesCategory::DIRECTX] = true;

        return ret;
    }
}
