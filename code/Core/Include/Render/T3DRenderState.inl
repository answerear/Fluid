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

    inline void BlendState::setAlpha2CoverageEnabled(bool enabled)
    {
        mAlphaToCoverageEnable = enabled;
    }

    //--------------------------------------------------------------------------

    inline bool BlendState::isAlpha2CoverageEnabled() const
    {
        return mAlphaToCoverageEnable;
    }

    //--------------------------------------------------------------------------

    inline void BlendState::setIndependentBlendEnabled(bool enabled)
    {
        mIndependentBlendEnable = enabled;
    }

    //--------------------------------------------------------------------------

    inline bool BlendState::isIndependentBlendEnabled() const
    {
        return mIndependentBlendEnable;
    }

    //--------------------------------------------------------------------------

    inline void BlendState::setBlendEnabled(int32_t idx, bool enabled)
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        mRenderTargetState[idx].mBlendEnable = enabled;
    }

    //--------------------------------------------------------------------------

    inline bool BlendState::isBlendEnabled(int32_t idx)
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        return mRenderTargetState[idx].mBlendEnable;
    }

    //--------------------------------------------------------------------------

    inline void BlendState::setSrcBlend(int32_t idx, BlendFactor factor)
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        mRenderTargetState[idx].mSrcBlend = factor;
    }

    //--------------------------------------------------------------------------

    inline BlendFactor BlendState::getSrcBlend(int32_t idx) const
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        return mRenderTargetState[idx].mSrcBlend;
    }

    //--------------------------------------------------------------------------

    inline void BlendState::setDstBlend(int32_t idx, BlendFactor factor)
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        mRenderTargetState[idx].mDestBlend = factor;
    }

    //--------------------------------------------------------------------------

    inline BlendFactor BlendState::getDstBlend(int32_t idx) const
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        return mRenderTargetState[idx].mDestBlend;
    }

    //--------------------------------------------------------------------------

    inline void BlendState::setBlendOp(int32_t idx, BlendOperation op)
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        mRenderTargetState[idx].mBlendOp = op;
    }

    //--------------------------------------------------------------------------

    inline BlendOperation BlendState::getBlendOp(int32_t idx) const
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        return mRenderTargetState[idx].mBlendOp;
    }

    //--------------------------------------------------------------------------

    inline void BlendState::setSrcBlendAlpha(int32_t idx, BlendFactor factor)
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        mRenderTargetState[idx].mSrcBlendAlpha = factor;
    }

    //--------------------------------------------------------------------------

    inline BlendFactor BlendState::getSrcBlendAlpha(int32_t idx) const
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        return mRenderTargetState[idx].mSrcBlendAlpha;
    }

    //--------------------------------------------------------------------------

    inline void BlendState::setDstBlendAlpha(int32_t idx, BlendFactor factor)
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        mRenderTargetState[idx].mDestBlendAlpha = factor;
    }

    //--------------------------------------------------------------------------

    inline BlendFactor BlendState::getDstBlendAlpha(int32_t idx) const
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        return mRenderTargetState[idx].mDestBlendAlpha;
    }

    //--------------------------------------------------------------------------

    inline void BlendState::setBlendOpAlpha(int32_t idx, BlendOperation op)
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        mRenderTargetState[idx].mBlendOpAlpha = op;
    }

    //--------------------------------------------------------------------------

    inline BlendOperation BlendState::getBlendOpAlpha(int32_t idx) const
    {
        T3D_ASSERT(idx >= 0 && idx < MAX_RENDER_TARGET);
        return mRenderTargetState[idx].mBlendOpAlpha;
    }

    //--------------------------------------------------------------------------

    inline void DepthStencilState::setDepthTestEnabled(bool enabled)
    {
        mDepthTestEnable = enabled;
    }

    //--------------------------------------------------------------------------

    inline bool DepthStencilState::isDepthTestEnabled() const
    {
        return mDepthTestEnable;
    }

    //--------------------------------------------------------------------------

    inline void DepthStencilState::setDepthWriteEnabled(bool enabled)
    {
        mDepthWriteEnable = enabled;
    }

    //--------------------------------------------------------------------------

    inline bool DepthStencilState::isDepthWriteEnabled() const
    {
        return mDepthWriteEnable;
    }

    //--------------------------------------------------------------------------

    inline void DepthStencilState::setDepthFunction(CompareFunction func)
    {
        mDepthFunc = func;
    }

    //--------------------------------------------------------------------------

    inline CompareFunction DepthStencilState::getDepthFunction() const
    {
        return mDepthFunc;
    }

    //--------------------------------------------------------------------------

    inline void DepthStencilState::setStencilEnabled(bool enabled)
    {
        mStencilEnable = enabled;
    }

    //--------------------------------------------------------------------------

    inline bool DepthStencilState::isStencilEnabled() const
    {
        return mStencilEnable;
    }

    //--------------------------------------------------------------------------

    inline void DepthStencilState::setStencilReadMask(uint8_t mask)
    {
        mStencilReadMask = mask;
    }

    //--------------------------------------------------------------------------

    inline uint8_t DepthStencilState::getStencilReadMask() const
    {
        return mStencilReadMask;
    }

    //--------------------------------------------------------------------------

    inline void DepthStencilState::setStencilWriteMask(uint8_t mask)
    {
        mStencilWriteMask = mask;
    }

    //--------------------------------------------------------------------------

    inline uint8_t DepthStencilState::getStencilWriteMask() const
    {
        return mStencilWriteMask;
    }

    //--------------------------------------------------------------------------

    inline void DepthStencilState::setStencilRef(uint8_t ref)
    {
        mStencilRef = ref;
    }

    //--------------------------------------------------------------------------

    inline uint8_t DepthStencilState::getStencilRef() const
    {
        return mStencilRef;
    }

    //--------------------------------------------------------------------------

    inline void DepthStencilState::setStencilFunction(CompareFunction func)
    {
        mStencilFunc = func;
    }

    //--------------------------------------------------------------------------

    inline CompareFunction DepthStencilState::getStencilFunction() const
    {
        return mStencilFunc;
    }

    //--------------------------------------------------------------------------

    inline void DepthStencilState::setStencilOp(
        StencilOp stencilFail, StencilOp depthFail, StencilOp pass)
    {
        mStencilFailOp = stencilFail;
        mDepthFailOp = depthFail;
        mStencilPassOp = pass;
    }

    //--------------------------------------------------------------------------

    inline void RasterizerState::setPolygonMode(PolygonMode mode)
    {
        mPolygonMode = mode;
    }

    //--------------------------------------------------------------------------

    inline PolygonMode RasterizerState::getPolygonMode() const
    {
        return mPolygonMode;
    }

    //--------------------------------------------------------------------------

    inline void RasterizerState::setCullingMode(CullingMode mode)
    {
        mCullingMode = mode;
    }

    //--------------------------------------------------------------------------

    inline CullingMode RasterizerState::getCullingMode() const
    {
        return mCullingMode;
    }

    //--------------------------------------------------------------------------

    inline void RasterizerState::setManualCullingMode(ManualCullingMode mode)
    {
        mManualCullingMode = mode;
    }

    //--------------------------------------------------------------------------

    inline ManualCullingMode RasterizerState::getManualCullingMode() const
    {
        return mManualCullingMode;
    }

    //--------------------------------------------------------------------------

    inline void RasterizerState::setDepthBias(int32_t bias)
    {
        mDepthBias = bias;
    }

    //--------------------------------------------------------------------------

    inline int32_t RasterizerState::getDepthBias() const
    {
        return mDepthBias;
    }

    //--------------------------------------------------------------------------

    inline void RasterizerState::setDepthBiasClamp(Real clamp)
    {
        mDepthBiasClamp = clamp;
    }

    //--------------------------------------------------------------------------

    inline Real RasterizerState::getDepthBiasClamp() const
    {
        return mDepthBiasClamp;
    }

    //--------------------------------------------------------------------------

    inline void RasterizerState::setSlopeScaledDepthBias(Real slope)
    {
        mSlopeScaledDepthBias = slope;
    }

    //--------------------------------------------------------------------------

    inline Real RasterizerState::getSlopeScaledDepthBias() const
    {
        return mSlopeScaledDepthBias;
    }

    //--------------------------------------------------------------------------

    inline void RasterizerState::setDepthClipEnabled(bool enabled)
    {
        mDepthClipEnable = enabled;
    }

    //--------------------------------------------------------------------------

    inline bool RasterizerState::isDepthClipEnabled() const
    {
        return mDepthClipEnable;
    }

    //--------------------------------------------------------------------------

    inline void RasterizerState::setScissorEnabled(bool enabled)
    {
        mScissorEnable = enabled;
    }

    //--------------------------------------------------------------------------

    inline bool RasterizerState::isScissorEnabled() const
    {
        return mScissorEnable;
    }

    //--------------------------------------------------------------------------

    inline void RasterizerState::setMSAAEnabled(bool enabled)
    {
        mMSAAEnable = enabled;
    }

    //--------------------------------------------------------------------------

    inline bool RasterizerState::isMSAAEnabled() const
    {
        return mMSAAEnable;
    }

    //--------------------------------------------------------------------------

    inline const UVWAddressMode& SamplerState::getAddressMode() const
    {
        return mAddressMode;
    }

    //--------------------------------------------------------------------------

    inline void SamplerState::setAddressMode(const UVWAddressMode& uvw)
    {
        if (mAddressMode.u != uvw.u || mAddressMode.v != uvw.v
            || mAddressMode.w != uvw.w)
        {
            mAddressMode = uvw;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline void SamplerState::setAddressMode(TextureAddressMode u,
        TextureAddressMode v, TextureAddressMode w)
    {
        if (mAddressMode.u != u)
        {
            mAddressMode.u = u;
            mIsDirty = true;
        }

        if (mAddressMode.v != v)
        {
            mAddressMode.v = v;
            mIsDirty = true;
        }

        if (mAddressMode.w != w)
        {
            mAddressMode.w = w;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline void SamplerState::setAddressMode(TextureAddressMode mode)
    {
        if (mAddressMode.u != mode || mAddressMode.v != mode
            || mAddressMode.w != mode)
        {
            mAddressMode.u = mAddressMode.v = mAddressMode.w = mode;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline const ColorRGBA& SamplerState::getBorderColor() const
    {
        return mBorderColor;
    }

    //--------------------------------------------------------------------------

    inline void SamplerState::setBorderColor(const ColorRGBA& color)
    {
        if (color != mBorderColor)
        {
            mBorderColor = color;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline void SamplerState::setFilter(FilterOptions minFilter,
        FilterOptions magFilter, FilterOptions mipFilter)
    {
        if (mMinFilter != minFilter)
        {
            mMinFilter = minFilter;
            mIsDirty = true;
        }

        if (mMagFilter != mMagFilter)
        {
            mMagFilter = magFilter;
            mIsDirty = true;
        }

        if (mMipFilter != mMinFilter)
        {
            mMipFilter = mipFilter;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline void SamplerState::getFilter(FilterOptions& minFilter,
        FilterOptions& magFilter, FilterOptions& mipFilter)
    {
        minFilter = mMinFilter;
        magFilter = mMagFilter;
        mMipFilter = mMipFilter;
    }

    //--------------------------------------------------------------------------

    inline CompareFunction SamplerState::getCompareFunction() const
    {
        return mCompareFunc;
    }

    //--------------------------------------------------------------------------

    inline void SamplerState::setCompareFunction(CompareFunction func)
    {
        if (mCompareFunc != func)
        {
            mCompareFunc = func;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline uint32_t SamplerState::getAnisotropy() const
    {
        return mAnisotropy;
    }

    //--------------------------------------------------------------------------

    inline void SamplerState::setAnisotropy(uint32_t aniso)
    {
        if (aniso != mAnisotropy)
        {
            mAnisotropy = aniso;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline Real SamplerState::getMipmapBias() const
    {
        return mMipmapBias;
    }

    //--------------------------------------------------------------------------

    inline void SamplerState::setMipmapBias(Real bias)
    {
        if (bias != mMipmapBias)
        {
            mMipmapBias = bias;
            mIsDirty = true;
        }
    }
}
