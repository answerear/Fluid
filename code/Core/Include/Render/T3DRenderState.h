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

#ifndef __T3D_RENDER_STATE_H__
#define __T3D_RENDER_STATE_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Kernel/T3DObject.h"
#include "Kernel/T3DCommon.h"
#include "Kernel/T3DBlendMode.h"


namespace Tiny3D
{
    class T3D_ENGINE_API BlendState : public Object
    {
    public:
        enum
        {
            MAX_RENDER_TARGET = 8
        };

        virtual ~BlendState();

        void setAlpha2CoverageEnabled(bool enabled);
        bool isAlpha2CoverageEnabled() const;

        void setIndependentBlendEnabled(bool enabled);
        bool isIndependentBlendEnabled() const;

        void setBlendEnabled(int32_t idx, bool enabled);
        bool isBlendEnabled(int32_t idx) const;

        void setSrcBlend(int32_t idx, BlendFactor factor);
        BlendFactor getSrcBlend(int32_t idx) const;

        void setDstBlend(int32_t idx, BlendFactor factor);
        BlendFactor getDstBlend(int32_t idx) const;

        void setBlendOp(int32_t idx, BlendOperation op);
        BlendOperation getBlendOp(int32_t idx) const;

        void setSrcBlendAlpha(int32_t idx, BlendFactor factor);
        BlendFactor getSrcBlendAlpha(int32_t idx) const;

        void setDstBlendAlpha(int32_t idx, BlendFactor factor);
        BlendFactor getDstBlendAlpha(int32_t idx) const;

        void setBlendOpAlpha(int32_t idx, BlendOperation op);
        BlendOperation getBlendOpAlpha(int32_t idx) const;

    protected:
        BlendState();

        struct RTBlendState
        {
            bool            mBlendEnable;
            BlendFactor     mSrcBlend;
            BlendFactor     mDestBlend;
            BlendOperation  mBlendOp;
            BlendFactor     mSrcBlendAlpha;
            BlendFactor     mDestBlendAlpha;
            BlendOperation  mBlendOpAlpha;
            uint8_t         mRenderTargetWriteMask;
        };

        bool    mIsDirty;
        bool    mAlphaToCoverageEnable;
        bool    mIndependentBlendEnable;

        RTBlendState    mRenderTargetState[MAX_RENDER_TARGET];
    };

    class T3D_ENGINE_API DepthStencilState : public Object
    {
    public:
        virtual ~DepthStencilState();

        void setDepthTestEnabled(bool enabled);
        bool isDepthTestEnabled() const;

        void setDepthWriteEnabled(bool enabled);
        bool isDepthWriteEnabled() const;

        void setDepthWriteMask(DepthWriteMask mask);
        DepthWriteMask getDepthWriteMask() const;

        void setDepthFunction(CompareFunction func);
        CompareFunction getDepthFunction() const;

        void setStencilEnabled(bool enabled);
        bool isStencilEnabled() const;

        void setStencilReadMask(uint8_t mask);
        uint8_t getStencilReadMask() const;

        void setStencilWriteMask(uint8_t mask);
        uint8_t getStencilWriteMask() const;

        void setStencilRef(uint8_t ref);
        uint8_t getStencilRef() const;

        void setStencilFunction(CompareFunction func);
        CompareFunction getStencilFunction() const;

        void setStencilOp(StencilOp stencilFail, StencilOp depthFail, StencilOp pass);
        void getStencilOp(StencilOp& stencilFail, StencilOp& depthFail, StencilOp& pass) const;

    protected:
        DepthStencilState();

        bool            mIsDirty;
        bool            mDepthTestEnable;
        bool            mDepthWriteEnable;
        DepthWriteMask  mDepthWriteMask;
        CompareFunction mDepthFunc;
        bool            mStencilEnable;
        uint8_t         mStencilReadMask;
        uint8_t         mStencilWriteMask;
        uint8_t         mStencilRef;
        CompareFunction mStencilFunc;
        StencilOp       mStencilFailOp;
        StencilOp       mDepthFailOp;
        StencilOp       mStencilPassOp;
    };

    class T3D_ENGINE_API RasterizerState : public Object
    {
    public:
        virtual ~RasterizerState();

        void setPolygonMode(PolygonMode mode);
        PolygonMode getPolygonMode() const;

        void setCullingMode(CullingMode mode);
        CullingMode getCullingMode() const;

        void setDepthBias(int32_t bias);
        int32_t getDepthBias() const;

        void setDepthBiasClamp(Real clamp);
        Real getDepthBiasClamp() const;

        void setSlopeScaledDepthBias(Real slope);
        Real getSlopeScaledDepthBias() const;

        void setDepthClipEnabled(bool enabled);
        bool isDepthClipEnabled() const;

        void setScissorEnabled(bool enabled);
        bool isScissorEnabled() const;

        void setMSAAEnabled(bool enabled);
        bool isMSAAEnabled() const;

    protected:
        RasterizerState();

        PolygonMode         mPolygonMode;
        CullingMode         mCullingMode;
        int32_t             mDepthBias;
        Real                mDepthBiasClamp;
        Real                mSlopeScaledDepthBias;
        bool                mDepthClipEnable;
        bool                mScissorEnable;
        bool                mMSAAEnable;
        bool                mIsDirty;
    };

    class T3D_ENGINE_API SamplerState : public Object
    {
    public:
        virtual ~SamplerState();

        /**
         * @fn  const UVWAddressMode Sampler::&getAddressMode() const;
         * @brief   Gets address mode
         * @return  The address mode.
         */
        const UVWAddressMode& getAddressMode() const;

        /**
         * @fn  void Sampler::setAddressMode(const UVWAddressMode &uvw);
         * @brief   Sets address mode
         * @param   uvw The uvw.
         */
        void setAddressMode(const UVWAddressMode& uvw);

        /**
         * @fn  void Sampler::setAddressMode(TextureAddressMode u,
         *      TextureAddressMode v, TextureAddressMode w);
         * @brief   Sets address mode
         * @param   u   A TextureAddressMode to process.
         * @param   v   A TextureAddressMode to process.
         * @param   w   A TextureAddressMode to process.
         */
        void setAddressMode(TextureAddressMode u, TextureAddressMode v,
            TextureAddressMode w);

        /**
         * @fn  void Sampler::setAddressMode(TextureAddressMode mode);
         * @brief   Sets address mode
         * @param   mode    The mode.
         */
        void setAddressMode(TextureAddressMode mode);

        /**
         * @fn  const ColorRGBA Sampler::&getBorderColor() const;
         * @brief   Gets border color
         * @return  The border color.
         */
        const ColorRGBA& getBorderColor() const;

        /**
         * @fn  void Sampler::setBorderColor(const ColorRGBA &color);
         * @brief   Sets border color
         * @param   color   The color.
         */
        void setBorderColor(const ColorRGBA& color);

        /**
         * @fn  void Sampler::setFilter(FilterOptions minFilter,
         *      FilterOptions magFilter, FilterOptions mipFilter);
         * @brief   Sets a filter
         * @param   minFilter   A filter specifying the minimum.
         * @param   magFilter   A filter specifying the magnitude.
         * @param   mipFilter   A filter specifying the mip.
         */
        void setFilter(FilterOptions minFilter, FilterOptions magFilter,
            FilterOptions mipFilter);

        void getFilter(FilterOptions& minFilter, FilterOptions& magFilter,
            FilterOptions& mipFilter) const;

        /**
         * @fn  CompareFunction Sampler::getCompareFunction() const;
         * @brief   Gets compare function
         * @return  The compare function.
         */
        CompareFunction getCompareFunction() const;

        /**
         * @fn  void Sampler::setCompareFunction(CompareFunction func);
         * @brief   Sets compare function
         * @param   func    The function.
         */
        void setCompareFunction(CompareFunction func);

        /**
         * @fn  uint32_t Sampler::getAnisotropy() const;
         * @brief   Gets the anisotropy
         * @return  The anisotropy.
         */
        uint32_t getAnisotropy() const;

        /**
         * @fn  void Sampler::setAnisotropy(uint32_t aniso);
         * @brief   Sets an anisotropy
         * @param   aniso   The aniso.
         */
        void setAnisotropy(uint32_t aniso);

        /**
         * @fn  Real Sampler::getMipmapBias() const;
         * @brief   Gets mipmap bias
         * @return  The mipmap bias.
         */
        Real getMipmapBias() const;

        /**
         * @fn  void Sampler::setMipmapBias(Real bias);
         * @brief   Sets mipmap bias
         * @param   bias    The bias.
         */
        void setMipmapBias(Real bias);

    protected:
        SamplerState();

        UVWAddressMode  mAddressMode;   /**< The address mode */
        ColorRGBA       mBorderColor;   /**< The border color */
        FilterOptions   mMinFilter;     /**< A filter specifying the minimum */
        FilterOptions   mMagFilter;     /**< A filter specifying the magnitude */
        FilterOptions   mMipFilter;     /**< A filter specifying the mip */
        CompareFunction mCompareFunc;   /**< The compare function */
        uint32_t        mAnisotropy;    /**< The anisotropy */
        Real            mMipmapBias;    /**< The mipmap bias */
        bool            mIsDirty;       /**< True if is dirty, false if not */
    };
}

#include "T3DRenderState.inl"


#endif  /*__T3D_RENDER_STATE_H__*/
