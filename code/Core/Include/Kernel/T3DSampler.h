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


#ifndef __T3D_SAMPLER_H__
#define __T3D_SAMPLER_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "T3DObject.h"
#include "Kernel/T3DCommon.h"


namespace Tiny3D
{
    /**
     * @class   Sampler
     * @brief   采样器
     */
    class T3D_ENGINE_API Sampler : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        static SamplerPtr create(const String &name);

        virtual ~Sampler();

        void setTextureUnit(TextureUnit *unit);

        /**
         * @fn  const UVWAddressMode Sampler::&getAddressMode() const;
         * @brief   Gets address mode
         * @return  The address mode.
         */
        const UVWAddressMode &getAddressMode() const;

        /**
         * @fn  void Sampler::setAddressMode(const UVWAddressMode &uvw);
         * @brief   Sets address mode
         * @param   uvw The uvw.
         */
        void setAddressMode(const UVWAddressMode &uvw);

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
        const ColorRGBA &getBorderColor() const;

        /**
         * @fn  void Sampler::setBorderColor(const ColorRGBA &color);
         * @brief   Sets border color
         * @param   color   The color.
         */
        void setBorderColor(const ColorRGBA &color);

        /**
         * @fn  FilterOptions Sampler::getFilter(FilterType type);
         * @brief   Gets a filter
         * @param   type    The type.
         * @return  The filter.
         */
        FilterOptions getFilter(FilterType type);

        /**
         * @fn  void Sampler::setFilter(FilterOptions opt, FilterType type);
         * @brief   Sets a filter
         * @param   opt     The option.
         * @param   type    The type.
         */
        void setFilter(FilterOptions opt, FilterType type);

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

        /**
         * @fn  void Sampler::setFilter(FilterType type);
         * @brief   Sets a filter
         * @param   type    The type.
         */
        void setFilter(TexFilterOptions type);

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

        bool isCompareEnabled() const;

        void setCompareEnabled(bool enabled);

    protected:
        /**
         * @fn  Sampler::Sampler(const String &name);
         * @brief   Constructor
         * @param   name    The name.
         */
        Sampler(const String &name);

    protected:
        TextureUnit     *mParent;

        UVWAddressMode  mAddressMode;   /**< The address mode */
        ColorRGBA       mBorderColor;   /**< The border color */
        FilterOptions   mMinFilter;     /**< A filter specifying the minimum */
        FilterOptions   mMagFilter;     /**< A filter specifying the magnitude */
        FilterOptions   mMipFilter;     /**< A filter specifying the mip */
        CompareFunction mCompareFunc;   /**< The compare function */
        uint32_t        mAnisotropy;    /**< The anisotropy */
        Real            mMipmapBias;    /**< The mipmap bias */
        bool            mCompareEnabled;/**< True if compare enabled */
        bool            mIsDirty;       /**< True if is dirty, false if not */
    };
}


#include "T3DSampler.inl"


#endif  /*__T3D_SAMPLER_H__*/
