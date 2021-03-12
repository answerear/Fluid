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

    inline const DriverVersion &RenderCapabilities::getDriverVersion() const
    {
        return mDriverVersion;
    }

    //--------------------------------------------------------------------------

    inline GPUVendor RenderCapabilities::getVendor() const
    {
        return mVendor;
    }

    //--------------------------------------------------------------------------

    inline const String &RenderCapabilities::getDeviceName() const
    {
        return mDeviceName;
    }

    //--------------------------------------------------------------------------

    inline const String &RenderCapabilities::getRendererName() const
    {
        return mRendererName;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getNumTextureUnits() const
    {
        return mNumTextureUnits;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getNumVertexTextureUnits() const
    {
        return mNumVertexTextureUnits;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getStencilBufferBitDepth() const
    {
        return mStencilBufferBitDepth;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getNumVertexBlendMatrices() const
    {
        return mNumVertexBlendMatrices;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getNumMultiRenderTargets() const
    {
        return mNumMultiRenderTargets;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getNumVertexAttributes() const
    {
        return mNumVertexAttributes;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getVSConstantFloatCount() const
    {
        return mVSConstantFloatCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getVSConstantIntCount() const
    {
        return mVSConstantIntCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getVSConstantBoolCount() const
    {
        return mVSConstantBoolCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getGSConstantFloatCount() const
    {
        return mGSConstantFloatCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getGSConstantIntCount() const
    {
        return mGSConstantIntCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getGSConstantBoolCount() const
    {
        return mGSConstantBoolCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getPSConstantFloatCount() const
    {
        return mPSConstantFloatCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getPSConstantIntCount() const
    {
        return mPSConstantIntCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getPSConstantBoolCount() const
    {
        return mPSConstantBoolCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getHSConstantFloatCount() const
    {
        return mHSConstantFloatCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getHSConstantIntCount() const
    {
        return mHSConstantIntCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getHSConstantBoolCount() const
    {
        return mHSConstantBoolCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getDSConstantFloatCount() const
    {
        return mDSConstantFloatCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getDSConstantIntCount() const
    {
        return mDSConstantIntCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getDSConstantBoolCount() const
    {
        return mDSConstantBoolCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getCSConstantFloatCount() const
    {
        return mCSConstantFloatCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getCSConstantIntCount() const
    {
        return mCSConstantIntCount;
    }

    //--------------------------------------------------------------------------

    inline uint16_t RenderCapabilities::getCSConstantBoolCount() const
    {
        return mCSConstantBoolCount;
    }

    //--------------------------------------------------------------------------

    inline int32_t RenderCapabilities::getGSNumOutputVertices() const
    {
        return mGSNumOutputVertices;
    }

    //--------------------------------------------------------------------------

    inline Real RenderCapabilities::getMaxPointSize() const
    {
        return mMaxPointSize;
    }

    //--------------------------------------------------------------------------

    inline Real RenderCapabilities::getMaxAnisotropy() const
    {
        return mMaxAnisotropy;
    }

    //--------------------------------------------------------------------------

    inline bool RenderCapabilities::isNPOTLimited() const
    {
        return mNPOTLimited;
    }

    //--------------------------------------------------------------------------

    inline bool RenderCapabilities::hasCapabilities(Capabilities cap) const
    {
        bool ret = false;
        int32_t idx = (CAPS_CATEGORY_MASK & cap) >> CAPS_BITSHIFT;
        if (mCapabilities[idx] & (cap & ~CAPS_CATEGORY_MASK))
            ret = true;
        return ret;
    }

    //--------------------------------------------------------------------------

    inline bool RenderCapabilities::isCapabilityRendererSpecific(
        Capabilities cap) const
    {
        int cat = cap >> CAPS_BITSHIFT;
        if (cat == CapabilitiesCategory::DIRECTX 
            || cat == CapabilitiesCategory::OPENGL
            || cat == CapabilitiesCategory::OPENGLES
            || cat == CapabilitiesCategory::VULKAN
            || cat == CapabilitiesCategory::METAL)
            return true;
        return false;
    }

    //--------------------------------------------------------------------------

    inline void RenderCapabilities::setCapability(Capabilities cap)
    {
        int index = (CAPS_CATEGORY_MASK & cap) >> CAPS_BITSHIFT;
        mCapabilities[index] |= (cap & ~CAPS_CATEGORY_MASK);
    }

    //--------------------------------------------------------------------------

    inline void RenderCapabilities::unsetCapability(Capabilities cap)
    {
        int index = (CAPS_CATEGORY_MASK & cap) >> CAPS_BITSHIFT;
        mCapabilities[index] &= (~cap | CAPS_CATEGORY_MASK);
    }
}

