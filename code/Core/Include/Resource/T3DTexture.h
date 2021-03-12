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


#ifndef __T3D_TEXTURE_H__
#define __T3D_TEXTURE_H__


#include "Resource/T3DResource.h"
#include "Kernel/T3DCommon.h"
#include "Render/T3DHardwarePixelBuffer.h"


namespace Tiny3D
{
    /**
     * @enum    TextureType
     * @brief   纹理类型
     */
    enum TextureType
    {
        E_TEX_TYPE_1D = 1,      /**< 一维纹理 */
        E_TEX_TYPE_2D,          /**< 二维纹理 */
        E_TEX_TYPE_3D,          /**< 三位纹理 */
        E_TEX_TYPE_CUBE_MAP,    /**< CubeMap 纹理 */
        E_TEX_TYPE_2D_ARRAY,
        E_TEX_TYPE_2D_RECT
    };

    /**
     * @class   T3D_ENGINE_API
     * @brief   纹理资源
     */
    class T3D_ENGINE_API Texture : public Resource
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @enum    TexUsage
         * @brief   纹理用途
         */
        enum TexUsage
        {
            E_TU_DEFAULT = 0,       /**< 默认纹理，从图片加载数据填充纹理 */
            E_TU_RENDERTARGET,      /**< 渲染到纹理 */
            E_TU_BLANK,             /**< 空白纹理 */
        };

        /**
         * @fn  static TexturePtr Texture::create(const String &name, 
         *      HardwareBuffer::Usage usage, uint32_t access, size_t mipmaps, 
         *      size_t texWidth = 0, size_t texHeight = 0, 
         *      TexUsage texUsage = E_TU_DEFAULT, 
         *      TextureType texType = E_TEX_TYPE_2D, 
         *      PixelFormat format = PixelFormat::E_PF_A8R8G8B8);
         * @brief   创建 Texture 对象
         * @param [in]  name        : 纹理资源名称.
         * @param [in]  usage       : 硬件缓冲区使用方法.
         * @param [in]  access      : CPU 访问硬件缓冲区的权限.
         * @param [in]  mipmaps     : 纹理的 mipmap 层级数量.
         * @param [in]  texWidth    (Optional) : 纹理宽度，默认从文件读取.
         * @param [in]  texHeight   (Optional) : 纹理高度，默认从文件读取.
         * @param [in]  texUsage    (Optional) : 纹理用途，默认是从图片加载直接用于渲染的.
         * @param [in]  texType     (Optional) : 纹理类型，默认是2D纹理.
         * @param [in]  format      (Optional) : 纹理像素格式，默认是A8R8G8B8.
         * @return  返回一个 Texture 对象.
         * @sa  enum TexUsage
         * @sa  enum TexType
         */
        static TexturePtr create(const String &name,
            HardwareBuffer::Usage usage, uint32_t access, size_t mipmaps, 
            size_t texWidth = 0, size_t texHeight = 0, 
            TexUsage texUsage = E_TU_DEFAULT, 
            TextureType texType = E_TEX_TYPE_2D,
            PixelFormat format = PixelFormat::E_PF_A8R8G8B8);

        /**
         * @fn  virtual Texture::~Texture();
         * @brief   析构函数
         */
        virtual ~Texture();

        /**
         * @fn  virtual Type Texture::getType() const override;
         * @brief   重写 Resource::getType()
         * @return  The type.
         */
        virtual Type getType() const override;

        /**
         * @fn  virtual ResourcePtr Texture::clone() const override;
         * @brief   重写 Resource::clone()
         * @return  A copy of this object.
         */
        virtual ResourcePtr clone() const override;

        /**
         * @fn  TextureType Texture::getTexType() const
         * @brief   获取纹理类型
         * @return  The tex type.
         */
        TextureType getTexType() const { return mTexType; }

        /**
         * @fn  size_t Texture::getMipMaps() const
         * @brief   获取纹理层级
         * @return  The mip maps.
         */
        size_t getMipMaps() const { return mMipmaps; }

        /**
         * @fn  size_t Texture::getTexWidth() const
         * @brief   获取纹理宽度
         * @return  The tex width.
         */
        size_t getTexWidth() const { return mTexWidth; }

        /**
         * @fn  size_t Texture::getTexHeight() const
         * @brief   获取纹理高度
         * @return  The tex height.
         */
        size_t getTexHeight() const { return mTexHeight; }

        /**
         * @fn  size_t Texture::getOriginalWidth() const
         * @brief   获取原图宽度
         * @return  The original width.
         */
        size_t getOriginalWidth() const { return mImgWidth; }

        /**
         * @fn  size_t Texture::getOriginalHeight() const
         * @brief   获取原图高度
         * @return  The original height.
         */
        size_t getOriginalHeight() const { return mImgHeight; }

        /**
         * @fn  PixelFormat Texture::getPixelFormat() const
         * @brief   获取纹理像素格式
         * @return  The pixel format.
         */
        PixelFormat getPixelFormat() const { return mFormat; }

        /**
         * @fn  bool Texture::hasAlpha() const
         * @brief   获取是否带Alpha通道
         * @return  True if alpha, false if not.
         */
        bool hasAlpha() const { return mHasAlpha; }

        /**
         * @fn  HardwarePixelBufferPtr Texture::getPixelBuffer() const
         * @brief   获取像素缓冲对象
         * @return  The pixel buffer.
         */
        HardwarePixelBufferPtr getPixelBuffer() const { return mPBO; }

        /**
         * @fn  TResult Texture::saveToFile(const String &path, 
         *      uint32_t fileType) const;
         * @brief   保存到文件
         * @param [in]  path        : 文件名和路径.
         * @param [in]  fileType    : 文件类型.
         * @return  A TResult.
         */
        TResult saveToFile(const String &path, uint32_t fileType) const;

        /**
         * @fn  TResult Texture::copyTo(TexturePtr texture, 
         *      Rect *dstRect = nullptr, Rect *srcRect = nullptr);
         * @brief   从源纹理复制纹理数据过来
         * @param [in]  texture : 目标纹理.
         * @param [in]  dstRect : 指定目标纹理区域，默认nullptr为复制到整个纹理上.
         * @param [in]  srcRect : 指定源纹理区域，默认nullptr为整个纹理复制.
         * @return  调用成功返回 T3D_OK.
         * @remarks  如果源纹理区域和目标纹理区域不一致，则会自动做缩放处理，
         *           但是这个会导致性能有一定程序的下降.
         */
        TResult copyTo(TexturePtr texture, Rect *dstRect = nullptr, 
            Rect *srcRect = nullptr);

    protected:
        /**
         * @fn  Texture::Texture(const String &name, 
         *      HardwareBuffer::Usage usage, uint32_t access, size_t mipmaps, 
         *      size_t texWidth, size_t texHeight, TexUsage texUsage, 
         *      TextureType texType, PixelFormat format);
         * @brief   构造函数
         * @param   name        The name.
         * @param   usage       The usage.
         * @param   access      The access.
         * @param   mipmaps     The mipmaps.
         * @param   texWidth    Width of the tex.
         * @param   texHeight   Height of the tex.
         * @param   texUsage    The tex usage.
         * @param   texType     Type of the tex.
         * @param   format      Describes the format to use.
         */
        Texture(const String &name, HardwareBuffer::Usage usage,
            uint32_t access, size_t mipmaps, size_t texWidth, size_t texHeight, 
            TexUsage texUsage, TextureType texType, PixelFormat format);

        /**
         * @fn  virtual TResult Texture::load() override;
         * @brief   重写 Resource::load()
         * @return  A TResult.
         */
        virtual TResult load() override;

        /**
         * @fn  virtual TResult Texture::unload() override;
         * @brief   重写 Resource::unlaod()
         * @return  A TResult.
         */
        virtual TResult unload() override;

    protected:
        TextureType             mTexType;       /**< 纹理类型 */
        TexUsage                mTexUsage;      /**< 纹理用途 */

        size_t                  mMipmaps;       /**< 纹理LOD层数 */

        size_t                  mTexWidth;      /**< 纹理宽度 */
        size_t                  mTexHeight;     /**< 纹理高度 */
        size_t                  mImgWidth;      /**< 图像宽度 */
        size_t                  mImgHeight;     /**< 图像高度 */

        PixelFormat             mFormat;        /**< 像素格式 */

        bool                    mHasAlpha;      /**< 是否有 Alpha 通道 */

        HardwareBuffer::Usage   mUsage;         /**< 硬件缓冲区使用方法 */
        uint32_t                mAccessMode;    /**< CPU 访问硬件缓冲方式 */
        HardwarePixelBufferPtr  mPBO;           /**< 像素数据对象 */
    };
}


#endif  /*__T3D_TEXTURE_H__*/
