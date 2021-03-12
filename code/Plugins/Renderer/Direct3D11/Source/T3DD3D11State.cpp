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


#include "T3DD3D11State.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    D3D11BlendStatePtr D3D11BlendState::create()
    {
        D3D11BlendStatePtr state = new D3D11BlendState();
        state->release();
        return state;
    }

    D3D11BlendState::D3D11BlendState()
    {

    }

    D3D11BlendState::~D3D11BlendState()
    {

    }

    void D3D11BlendState::setAlpha2CoverageEnabled(bool enabled)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    bool D3D11BlendState::isAlpha2CoverageEnabled() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11BlendState::setIndependentBlendEnabled(bool enabled)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    bool D3D11BlendState::isIndependentBlendEnabled() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11BlendState::setBlendEnabled(int32_t idx)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    bool D3D11BlendState::isBlendEnabled(int32_t idx)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11BlendState::setSrcBlend(int32_t idx, BlendFactor factor)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    BlendFactor D3D11BlendState::getSrcBlend(int32_t idx) const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11BlendState::setDstBlend(int32_t idx, BlendFactor factor)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    BlendFactor D3D11BlendState::getDstBlend(int32_t idx) const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11BlendState::setBlendOp(int32_t idx, BlendOperation op)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    BlendOperation D3D11BlendState::getBlendOp(int32_t idx) const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11BlendState::setSrcBlendAlpha(int32_t idx, BlendFactor factor)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    BlendFactor D3D11BlendState::getSrcBlendAlpha(int32_t idx) const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11BlendState::setDstBlendAlpha(int32_t idx, BlendFactor factor)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    Tiny3D::BlendFactor D3D11BlendState::getDstBlendAlpha(int32_t idx) const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11BlendState::setBlendOpAlpha(int32_t idx, BlendOperation op)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    BlendOperation D3D11BlendState::getBlendOpAlpha(int32_t idx) const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    //--------------------------------------------------------------------------

    D3D11DepthStencilStatePtr D3D11DepthStencilState::create()
    {
        D3D11DepthStencilStatePtr state = new D3D11DepthStencilState();
        state->release();
        return state;
    }

    D3D11DepthStencilState::D3D11DepthStencilState()
    {
    }

    D3D11DepthStencilState::~D3D11DepthStencilState()
    {
    }

    void D3D11DepthStencilState::setDepthTestEnabled(bool enabled)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    bool D3D11DepthStencilState::isDepthTestEnabled() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11DepthStencilState::setDepthWriteEnabled(bool enabled)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    bool D3D11DepthStencilState::isDepthWriteEnabled() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11DepthStencilState::setDepthFunction(CompareFunction func)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    Tiny3D::CompareFunction D3D11DepthStencilState::getDepthFunction() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11DepthStencilState::setStencilEnabled(bool enabled)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    bool D3D11DepthStencilState::isStencilEnabled() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11DepthStencilState::setStencilReadMask(uint8_t mask)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    uint8_t D3D11DepthStencilState::getStencilReadMask() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11DepthStencilState::setStencilWriteMask(uint8_t mask)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    uint8_t D3D11DepthStencilState::getStencilWriteMask() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11DepthStencilState::setStencilRef(uint8_t ref)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    uint8_t D3D11DepthStencilState::getStencilRef() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11DepthStencilState::setStencilFunction(CompareFunction func)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    CompareFunction D3D11DepthStencilState::getStencilFunction() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11DepthStencilState::setStencilOp(StencilOp stencilFail, StencilOp depthFail, StencilOp pass)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    //--------------------------------------------------------------------------

    D3D11RasterizerStatePtr D3D11RasterizerState::create()
    {
        D3D11RasterizerStatePtr state = new D3D11RasterizerState();
        state->release();
        return state;
    }

    D3D11RasterizerState::D3D11RasterizerState()
    {

    }

    D3D11RasterizerState::~D3D11RasterizerState()
    {

    }

    void D3D11RasterizerState::setPolygonMode(PolygonMode mode)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    Tiny3D::PolygonMode D3D11RasterizerState::getPolygonMode() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11RasterizerState::setCullingMode(CullingMode mode)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    Tiny3D::CullingMode D3D11RasterizerState::getCullingMode() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11RasterizerState::setManualCullingMode(ManualCullingMode mode)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    Tiny3D::ManualCullingMode D3D11RasterizerState::getManualCullingMode() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11RasterizerState::setDepthBias(int32_t bias)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    int32_t D3D11RasterizerState::getDepthBias() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11RasterizerState::setDepthBiasClamp(Real clamp)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    Tiny3D::Real D3D11RasterizerState::getDepthBiasClamp() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11RasterizerState::setSlopeScaledDepthBias(Real slope)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    Tiny3D::Real D3D11RasterizerState::getSlopeScaledDepthBias() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11RasterizerState::setDepthClipEnabled(bool enabled)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    bool D3D11RasterizerState::isDepthClipEnabled() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11RasterizerState::setScissorEnabled(bool enabled)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    bool D3D11RasterizerState::isScissorEnabled() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11RasterizerState::setMSAAEnabled(bool enabled)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    bool D3D11RasterizerState::isMSAAEnabled() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    //--------------------------------------------------------------------------

    D3D11SamplerStatePtr D3D11SamplerState::create()
    {
        D3D11SamplerStatePtr state = new D3D11SamplerState();
        state->release();
        return state;
    }

    D3D11SamplerState::D3D11SamplerState()
    {

    }

    D3D11SamplerState::~D3D11SamplerState()
    {

    }

    const UVWAddressMode& D3D11SamplerState::getAddressMode() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11SamplerState::setAddressMode(const UVWAddressMode& uvw)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11SamplerState::setAddressMode(TextureAddressMode u, TextureAddressMode v, TextureAddressMode w)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11SamplerState::setAddressMode(TextureAddressMode mode)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    const ColorRGBA& D3D11SamplerState::getBorderColor() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11SamplerState::setBorderColor(const ColorRGBA& color)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    FilterOptions D3D11SamplerState::getFilter(FilterType type)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11SamplerState::setFilter(FilterOptions opt, FilterType type)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11SamplerState::setFilter(FilterOptions minFilter, FilterOptions magFilter, FilterOptions mipFilter)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11SamplerState::setFilter(TexFilterOptions type)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    Tiny3D::CompareFunction D3D11SamplerState::getCompareFunction() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11SamplerState::setCompareFunction(CompareFunction func)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    uint32_t D3D11SamplerState::getAnisotropy() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11SamplerState::setAnisotropy(uint32_t aniso)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    Real D3D11SamplerState::getMipmapBias() const
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    void D3D11SamplerState::setMipmapBias(Real bias)
    {
        throw std::logic_error("The method or operation is not implemented.");
    }
}
