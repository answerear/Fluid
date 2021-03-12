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
    class T3D_ENGINE_API HWBlendState : public Object
    {
    public:
        virtual ~HWBlendState();

        virtual void setAlpha2CoverageEnabled(bool enabled) = 0;
        virtual bool isAlpha2CoverageEnabled() const = 0;

        virtual void setIndependentBlendEnabled(bool enabled) = 0;
        virtual bool isIndependentBlendEnabled() const = 0;

        virtual void setBlendEnabled(int32_t idx) = 0;
        virtual bool isBlendEnabled(int32_t idx) = 0;

        virtual void setSrcBlend(int32_t idx, BlendFactor factor) = 0;
        virtual BlendFactor getSrcBlend(int32_t idx) const = 0;

        virtual void setDstBlend(int32_t idx, BlendFactor factor) = 0;
        virtual BlendFactor getDstBlend(int32_t idx) const = 0;

        virtual void setBlendOp(int32_t idx, BlendOperation op) = 0;
        virtual BlendOperation getBlendOp(int32_t idx) const = 0;

        virtual void setSrcBlendAlpha(int32_t idx, BlendFactor factor) = 0;
        virtual BlendFactor getSrcBlendAlpha(int32_t idx) const = 0;

        virtual void setDstBlendAlpha(int32_t idx, BlendFactor factor) = 0;
        virtual BlendFactor getDstBlendAlpha(int32_t idx) const = 0;

        virtual void setBlendOpAlpha(int32_t idx, BlendOperation op) = 0;
        virtual BlendOperation getBlendOpAlpha(int32_t idx) const = 0;

    protected:
        HWBlendState();
    };

    class T3D_ENGINE_API HWDepthStencilState : public Object
    {
    public:
        virtual ~HWDepthStencilState();

        virtual void setDepthTestEnabled(bool enabled) = 0;
        virtual bool isDepthTestEnabled() const = 0;

        virtual void setDepthWriteEnabled(bool enabled) = 0;
        virtual bool isDepthWriteEnabled() const = 0;

        virtual void setDepthFunction(CompareFunction func) = 0;
        virtual CompareFunction getDepthFunction() const = 0;

        virtual void setStencilEnabled(bool enabled) = 0;
        virtual bool isStencilEnabled() const = 0;

        virtual void setStencilReadMask(uint8_t mask) = 0;
        virtual uint8_t getStencilReadMask() const = 0;

        virtual void setStencilWriteMask(uint8_t mask) = 0;
        virtual uint8_t getStencilWriteMask() const = 0;

        virtual void setStencilRef(uint8_t ref) = 0;
        virtual uint8_t getStencilRef() const = 0;

        virtual void setStencilFunction(CompareFunction func) = 0;
        virtual CompareFunction getStencilFunction() const = 0;

        virtual void setStencilOp(StencilOp stencilFail, StencilOp depthFail, StencilOp pass) = 0;

    protected:
        HWDepthStencilState();
    };

    class T3D_ENGINE_API HWRasterizerState : public Object
    {
    public:
        virtual ~HWRasterizerState();

        virtual void setPolygonMode(PolygonMode mode) = 0;
        virtual PolygonMode getPolygonMode() const = 0;

        virtual void setCullingMode(CullingMode mode) = 0;
        virtual CullingMode getCullingMode() const = 0;

        virtual void setManualCullingMode(ManualCullingMode mode) = 0;
        virtual ManualCullingMode getManualCullingMode() const = 0;

        virtual void setDepthBias(int32_t bias) = 0;
        virtual int32_t getDepthBias() const = 0;

        virtual void setDepthBiasClamp(Real clamp) = 0;
        virtual Real getDepthBiasClamp() const = 0;

        virtual void setSlopeScaledDepthBias(Real slope) = 0;
        virtual Real getSlopeScaledDepthBias() const = 0;

        virtual void setDepthClipEnabled(bool enabled) = 0;
        virtual bool isDepthClipEnabled() const = 0;

        virtual void setScissorEnabled(bool enabled) = 0;
        virtual bool isScissorEnabled() const = 0;

        virtual void setMSAAEnabled(bool enabled) = 0;
        virtual bool isMSAAEnabled() const = 0;

    protected:
        HWRasterizerState();
    };

    class T3D_ENGINE_API HWSamplerState : public Object
    {
    public:
        virtual ~HWSamplerState();

        /**
         * @fn  const UVWAddressMode Sampler::&getAddressMode() const;
         * @brief   Gets address mode
         * @return  The address mode.
         */
        virtual const UVWAddressMode& getAddressMode() const = 0;

        /**
         * @fn  void Sampler::setAddressMode(const UVWAddressMode &uvw);
         * @brief   Sets address mode
         * @param   uvw The uvw.
         */
        virtual void setAddressMode(const UVWAddressMode& uvw) = 0;

        /**
         * @fn  void Sampler::setAddressMode(TextureAddressMode u,
         *      TextureAddressMode v, TextureAddressMode w);
         * @brief   Sets address mode
         * @param   u   A TextureAddressMode to process.
         * @param   v   A TextureAddressMode to process.
         * @param   w   A TextureAddressMode to process.
         */
        virtual void setAddressMode(TextureAddressMode u, TextureAddressMode v,
            TextureAddressMode w) = 0;

        /**
         * @fn  void Sampler::setAddressMode(TextureAddressMode mode);
         * @brief   Sets address mode
         * @param   mode    The mode.
         */
        virtual void setAddressMode(TextureAddressMode mode) = 0;

        /**
         * @fn  const ColorRGBA Sampler::&getBorderColor() const;
         * @brief   Gets border color
         * @return  The border color.
         */
        virtual const ColorRGBA& getBorderColor() const = 0;

        /**
         * @fn  void Sampler::setBorderColor(const ColorRGBA &color);
         * @brief   Sets border color
         * @param   color   The color.
         */
        virtual void setBorderColor(const ColorRGBA& color) = 0;

        /**
         * @fn  FilterOptions Sampler::getFilter(FilterType type);
         * @brief   Gets a filter
         * @param   type    The type.
         * @return  The filter.
         */
        virtual FilterOptions getFilter(FilterType type) = 0;

        /**
         * @fn  void Sampler::setFilter(FilterOptions opt, FilterType type);
         * @brief   Sets a filter
         * @param   opt     The option.
         * @param   type    The type.
         */
        virtual void setFilter(FilterOptions opt, FilterType type) = 0;

        /**
         * @fn  void Sampler::setFilter(FilterOptions minFilter,
         *      FilterOptions magFilter, FilterOptions mipFilter);
         * @brief   Sets a filter
         * @param   minFilter   A filter specifying the minimum.
         * @param   magFilter   A filter specifying the magnitude.
         * @param   mipFilter   A filter specifying the mip.
         */
        virtual void setFilter(FilterOptions minFilter, FilterOptions magFilter,
            FilterOptions mipFilter) = 0;

        /**
         * @fn  void Sampler::setFilter(FilterType type);
         * @brief   Sets a filter
         * @param   type    The type.
         */
        virtual void setFilter(TexFilterOptions type) = 0;

        /**
         * @fn  CompareFunction Sampler::getCompareFunction() const;
         * @brief   Gets compare function
         * @return  The compare function.
         */
        virtual CompareFunction getCompareFunction() const = 0;

        /**
         * @fn  void Sampler::setCompareFunction(CompareFunction func);
         * @brief   Sets compare function
         * @param   func    The function.
         */
        virtual void setCompareFunction(CompareFunction func) = 0;

        /**
         * @fn  uint32_t Sampler::getAnisotropy() const;
         * @brief   Gets the anisotropy
         * @return  The anisotropy.
         */
        virtual uint32_t getAnisotropy() const = 0;

        /**
         * @fn  void Sampler::setAnisotropy(uint32_t aniso);
         * @brief   Sets an anisotropy
         * @param   aniso   The aniso.
         */
        virtual void setAnisotropy(uint32_t aniso) = 0;

        /**
         * @fn  Real Sampler::getMipmapBias() const;
         * @brief   Gets mipmap bias
         * @return  The mipmap bias.
         */
        virtual Real getMipmapBias() const = 0;

        /**
         * @fn  void Sampler::setMipmapBias(Real bias);
         * @brief   Sets mipmap bias
         * @param   bias    The bias.
         */
        virtual void setMipmapBias(Real bias) = 0;

    protected:
        HWSamplerState();
    };
}


#endif  /*__T3D_RENDER_STATE_H__*/
