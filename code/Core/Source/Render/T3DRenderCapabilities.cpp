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


#include "Render/T3DRenderCapabilities.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(RenderCapabilities, Object);

    //--------------------------------------------------------------------------

    String RenderCapabilities::GPUVendorStrings[GPUVendor::GPU_VENDOR_COUNT];

    //--------------------------------------------------------------------------

    void RenderCapabilities::initVendorStrings()
    {
        if (GPUVendorStrings[0].empty())
        {
            // Always lower case!
            GPUVendorStrings[GPUVendor::UNKNOWN] = "unknown";
            GPUVendorStrings[GPUVendor::NVIDIA] = "nvidia";
            GPUVendorStrings[GPUVendor::AMD] = "amd";
            GPUVendorStrings[GPUVendor::INTEL] = "intel";
            GPUVendorStrings[GPUVendor::IMAGINATION_TECHNOLOGIES] = "imagination technologies";
            GPUVendorStrings[GPUVendor::APPLE] = "apple";    // iOS Simulator
            GPUVendorStrings[GPUVendor::NOKIA] = "nokia";
            GPUVendorStrings[GPUVendor::MS_SOFTWARE] = "microsoft"; // Microsoft software device
            GPUVendorStrings[GPUVendor::MS_WARP] = "ms warp";
            GPUVendorStrings[GPUVendor::ARM] = "arm";
            GPUVendorStrings[GPUVendor::QUALCOMM] = "qualcomm";
            GPUVendorStrings[GPUVendor::MOZILLA] = "mozilla";
            GPUVendorStrings[GPUVendor::WEBKIT] = "webkit";
        }
    }

    //--------------------------------------------------------------------------

    GPUVendor RenderCapabilities::vendorFromString(const String &str)
    {
        initVendorStrings();
        GPUVendor vendor = GPUVendor::UNKNOWN;
        String lowerStr = str;
        StringUtil::toLowerCase(lowerStr);
        for (int i = 0; i < GPU_VENDOR_COUNT; ++i)
        {
            // 大小写无关
            if (GPUVendorStrings[i] == lowerStr)
            {
                vendor = static_cast<GPUVendor>(i);
                break;
            }
        }

        return vendor;
    }

    //--------------------------------------------------------------------------

    String RenderCapabilities::vendorToString(GPUVendor vendor)
    {
        initVendorStrings();
        return GPUVendorStrings[vendor];
    }

    //--------------------------------------------------------------------------

    RenderCapabilities::RenderCapabilities()
        : mDriverVersion()
        , mVendor(GPUVendor::UNKNOWN)
        , mNumTextureUnits(0)
        , mNumVertexTextureUnits(0)
        , mStencilBufferBitDepth(0)
        , mNumVertexBlendMatrices(0)
        , mNumMultiRenderTargets(0)
        , mNumVertexAttributes(0)
        , mVSConstantFloatCount(0)
        , mVSConstantIntCount(0)
        , mVSConstantBoolCount(0)
        , mGSConstantFloatCount(0)
        , mGSConstantIntCount(0)
        , mGSConstantBoolCount(0)
        , mPSConstantFloatCount(0)
        , mPSConstantIntCount(0)
        , mPSConstantBoolCount(0)
        , mHSConstantFloatCount(0)
        , mHSConstantIntCount(0)
        , mHSConstantBoolCount(0)
        , mDSConstantFloatCount(0)
        , mDSConstantIntCount(0)
        , mDSConstantBoolCount(0)
        , mCSConstantFloatCount(0)
        , mCSConstantIntCount(0)
        , mCSConstantBoolCount(0)
        , mGSNumOutputVertices(0)
        , mMaxPointSize(0.0f)
        , mMaxAnisotropy(0.0f)
        , mNPOTLimited(false)
    {
        for (int i = 0; i < CapabilitiesCategory::CATEGORY_COUNT; i++)
        {
            mCapabilities[i] = 0;
        }

        mCategoryRelevant[CapabilitiesCategory::COMMON_1] = true;
        mCategoryRelevant[CapabilitiesCategory::COMMON_2] = true;
        // 每个平台相关渲染器自己开启以下的分组
        mCategoryRelevant[CapabilitiesCategory::DIRECTX] = false;
        mCategoryRelevant[CapabilitiesCategory::OPENGL] = false;
        mCategoryRelevant[CapabilitiesCategory::OPENGLES] = false;
        mCategoryRelevant[CapabilitiesCategory::VULKAN] = false;
        mCategoryRelevant[CapabilitiesCategory::METAL] = false;
    }

    //--------------------------------------------------------------------------

    RenderCapabilities::~RenderCapabilities()
    {

    }
}
