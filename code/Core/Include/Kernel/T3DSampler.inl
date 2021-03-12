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

    inline void Sampler::setTextureUnit(TextureUnit *unit)
    {
        mParent = unit;
    }

    //--------------------------------------------------------------------------

    inline const UVWAddressMode &Sampler::getAddressMode() const
    {
        return mAddressMode;
    }

    //--------------------------------------------------------------------------

    inline void Sampler::setAddressMode(const UVWAddressMode &uvw)
    {
        if (mAddressMode.u != uvw.u || mAddressMode.v != uvw.v
            || mAddressMode.w != uvw.w)
        {
            mAddressMode = uvw;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline void Sampler::setAddressMode(TextureAddressMode u,
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

    inline void Sampler::setAddressMode(TextureAddressMode mode)
    {
        if (mAddressMode.u != mode || mAddressMode.v != mode 
            || mAddressMode.w != mode)
        {
            mAddressMode.u = mAddressMode.v = mAddressMode.w = mode;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline const ColorRGBA &Sampler::getBorderColor() const
    {
        return mBorderColor;
    }

    //--------------------------------------------------------------------------

    inline void Sampler::setBorderColor(const ColorRGBA &color)
    {
        if (color != mBorderColor)
        {
            mBorderColor = color;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline FilterOptions Sampler::getFilter(FilterType type)
    {
        FilterOptions opt = FilterOptions::NONE;
        if (type == FilterType::MIN)
            opt = mMinFilter;
        else if (type == FilterType::MAG)
            opt = mMagFilter;
        else if (type == FilterType::MIP)
            opt = mMinFilter;
        return opt;
    }

    //--------------------------------------------------------------------------

    inline void Sampler::setFilter(FilterOptions opt, FilterType type)
    {
        if (type == FilterType::MIN && mMinFilter != opt)
        {
            mMinFilter = opt;
            mIsDirty = true;
        }
        else if (type == FilterType::MAG && mMagFilter != opt)
        {
            mMagFilter = opt;
            mIsDirty = true;
        }
        else if (type == FilterType::MIP)
        {
            mMipFilter = opt;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline void Sampler::setFilter(FilterOptions minFilter,
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

    inline void Sampler::setFilter(TexFilterOptions type)
    {
        if (type == TexFilterOptions::NONE)
        {
            setFilter(FilterOptions::POINT, FilterOptions::POINT, FilterOptions::NONE);
        }
        else if (type == TexFilterOptions::BILINEAR)
        {
            setFilter(FilterOptions::LINEAR, FilterOptions::LINEAR, FilterOptions::POINT);
        }   
        else if (type == TexFilterOptions::TRILINEAR)
        {
            setFilter(FilterOptions::LINEAR, FilterOptions::LINEAR, FilterOptions::LINEAR);
        }   
        else if (type == TexFilterOptions::ANISOTROPIC)
        {
            setFilter(FilterOptions::ANISOTROPIC, FilterOptions::ANISOTROPIC, FilterOptions::ANISOTROPIC);
        }
    }

    //--------------------------------------------------------------------------

    inline CompareFunction Sampler::getCompareFunction() const
    {
        return mCompareFunc;
    }

    //--------------------------------------------------------------------------

    inline void Sampler::setCompareFunction(CompareFunction func)
    {
        if (mCompareFunc != func)
        {
            mCompareFunc = func;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline uint32_t Sampler::getAnisotropy() const
    {
        return mAnisotropy;
    }

    //--------------------------------------------------------------------------

    inline void Sampler::setAnisotropy(uint32_t aniso)
    {
        if (aniso != mAnisotropy)
        {
            mAnisotropy = aniso;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline Real Sampler::getMipmapBias() const
    {
        return mMipmapBias;
    }

    //--------------------------------------------------------------------------

    inline void Sampler::setMipmapBias(Real bias)
    {
        if (bias != mMipmapBias)
        {
            mMipmapBias = bias;
            mIsDirty = true;
        }
    }

    //--------------------------------------------------------------------------

    inline bool Sampler::isCompareEnabled() const
    {
        return mCompareEnabled;
    }

    //--------------------------------------------------------------------------

    inline void Sampler::setCompareEnabled(bool enabled)
    {
        if (enabled != mCompareEnabled)
        {
            mCompareEnabled = enabled;
            mIsDirty = true;
        }
    }
}

