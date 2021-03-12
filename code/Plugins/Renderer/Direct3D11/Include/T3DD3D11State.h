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


namespace Tiny3D
{
    class D3D11BlendState : public HWBlendState
    {
    public:
        static D3D11BlendStatePtr create();

        virtual ~D3D11BlendState();

        virtual void setAlpha2CoverageEnabled(bool enabled) override;

        virtual bool isAlpha2CoverageEnabled() const override;

        virtual void setIndependentBlendEnabled(bool enabled) override;

        virtual bool isIndependentBlendEnabled() const override;

        virtual void setBlendEnabled(int32_t idx) override;

        virtual bool isBlendEnabled(int32_t idx) override;

        virtual void setSrcBlend(int32_t idx, BlendFactor factor) override;

        virtual BlendFactor getSrcBlend(int32_t idx) const override;

        virtual void setDstBlend(int32_t idx, BlendFactor factor) override;

        virtual BlendFactor getDstBlend(int32_t idx) const override;

        virtual void setBlendOp(int32_t idx, BlendOperation op) override;

        virtual BlendOperation getBlendOp(int32_t idx) const override;

        virtual void setSrcBlendAlpha(int32_t idx, BlendFactor factor) override;

        virtual BlendFactor getSrcBlendAlpha(int32_t idx) const override;

        virtual void setDstBlendAlpha(int32_t idx, BlendFactor factor) override;

        virtual BlendFactor getDstBlendAlpha(int32_t idx) const override;

        virtual void setBlendOpAlpha(int32_t idx, BlendOperation op) override;

        virtual BlendOperation getBlendOpAlpha(int32_t idx) const override;

    protected:
        D3D11BlendState();

    protected:
        ID3D11BlendState *mD3D11BlendState;
    };

    class D3D11DepthStencilState : public HWDepthStencilState
    {
    public:
        static D3D11DepthStencilStatePtr create();

        virtual ~D3D11DepthStencilState();

        virtual void setDepthTestEnabled(bool enabled) override;

        virtual bool isDepthTestEnabled() const override;

        virtual void setDepthWriteEnabled(bool enabled) override;

        virtual bool isDepthWriteEnabled() const override;

        virtual void setDepthFunction(CompareFunction func) override;

        virtual CompareFunction getDepthFunction() const override;

        virtual void setStencilEnabled(bool enabled) override;

        virtual bool isStencilEnabled() const override;

        virtual void setStencilReadMask(uint8_t mask) override;

        virtual uint8_t getStencilReadMask() const override;

        virtual void setStencilWriteMask(uint8_t mask) override;

        virtual uint8_t getStencilWriteMask() const override;

        virtual void setStencilRef(uint8_t ref) override;

        virtual uint8_t getStencilRef() const override;

        virtual void setStencilFunction(CompareFunction func) override;

        virtual CompareFunction getStencilFunction() const override;

        virtual void setStencilOp(StencilOp stencilFail, StencilOp depthFail, StencilOp pass) override;

    protected:
        D3D11DepthStencilState();

    protected:
        ID3D11DepthStencilState *mD3D11DepthStencilState;
    };

    class D3D11RasterizerState : public HWRasterizerState
    {
    public:
        static D3D11RasterizerStatePtr create();

        virtual ~D3D11RasterizerState();

        virtual void setPolygonMode(PolygonMode mode) override;

        virtual PolygonMode getPolygonMode() const override;

        virtual void setCullingMode(CullingMode mode) override;

        virtual CullingMode getCullingMode() const override;

        virtual void setManualCullingMode(ManualCullingMode mode) override;

        virtual ManualCullingMode getManualCullingMode() const override;

        virtual void setDepthBias(int32_t bias) override;

        virtual int32_t getDepthBias() const override;

        virtual void setDepthBiasClamp(Real clamp) override;

        virtual Real getDepthBiasClamp() const override;

        virtual void setSlopeScaledDepthBias(Real slope) override;

        virtual Real getSlopeScaledDepthBias() const override;

        virtual void setDepthClipEnabled(bool enabled) override;

        virtual bool isDepthClipEnabled() const override;

        virtual void setScissorEnabled(bool enabled) override;

        virtual bool isScissorEnabled() const override;

        virtual void setMSAAEnabled(bool enabled) override;

        virtual bool isMSAAEnabled() const override;

    protected:
        D3D11RasterizerState();

    protected:
        ID3D11RasterizerState *mD3D11RasterizerState;
    };

    class D3D11SamplerState : public HWSamplerState
    {
    public:
        static D3D11SamplerStatePtr create();

        virtual ~D3D11SamplerState();

        virtual const UVWAddressMode& getAddressMode() const override;

        virtual void setAddressMode(const UVWAddressMode& uvw) override;

        virtual void setAddressMode(TextureAddressMode u, TextureAddressMode v, TextureAddressMode w) override;

        virtual void setAddressMode(TextureAddressMode mode) override;

        virtual const ColorRGBA& getBorderColor() const override;

        virtual void setBorderColor(const ColorRGBA& color) override;

        virtual FilterOptions getFilter(FilterType type) override;

        virtual void setFilter(FilterOptions opt, FilterType type) override;

        virtual void setFilter(FilterOptions minFilter, FilterOptions magFilter, FilterOptions mipFilter) override;

        virtual void setFilter(TexFilterOptions type) override;

        virtual CompareFunction getCompareFunction() const override;

        virtual void setCompareFunction(CompareFunction func) override;

        virtual uint32_t getAnisotropy() const override;

        virtual void setAnisotropy(uint32_t aniso) override;

        virtual Real getMipmapBias() const override;

        virtual void setMipmapBias(Real bias) override;

    protected:
        D3D11SamplerState();

    protected:
        ID3D11SamplerState *mD3D11SamplerState;
    };
}


#endif  /*__T3D_D3D11_STATE_H__*/
