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


#include "Resource/T3DTexture.h"
#include "Resource/T3DArchive.h"
#include "Resource/T3DArchiveManager.h"
#include "ImageCodec/T3DImage.h"
#include "Render/T3DHardwareBufferManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Texture, Resource);

    //--------------------------------------------------------------------------

    TexturePtr Texture::create(const String &name, HardwareBuffer::Usage usage, 
        uint32_t access, size_t mipmaps, size_t texWidth /* = 0 */, 
        size_t texHeight /* = 0 */, TexUsage texUsage /* = E_TU_DEFAULT */, 
        TextureType texType /* = E_TEX_TYPE_2D */, 
        PixelFormat format /* = PixelFormat::E_PF_A8R8G8B8 */)
    {
        TexturePtr texture = new Texture(name, usage, access, mipmaps, 
            texWidth, texHeight, texUsage, texType, format);
        texture->release();
        return texture;
    }

    //----------------------------------------------------------------- ---------

    Texture::Texture(const String &name, HardwareBuffer::Usage usage, 
        uint32_t access, size_t mipmaps, size_t texWidth, size_t texHeight, 
        TexUsage texUsage, TextureType texType, PixelFormat format)
        : Resource(name)
        , mTexType(texType)
        , mTexUsage(texUsage)
        , mMipmaps(mipmaps)
        , mTexWidth(texWidth)
        , mTexHeight(texHeight)
        , mImgWidth(texWidth)
        , mImgHeight(texHeight)
        , mFormat(format)
        , mHasAlpha(false)
        , mUsage(usage)
        , mAccessMode(access)
        , mPBO(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    Texture::~Texture()
    {
        mPBO = nullptr;
    }

    //--------------------------------------------------------------------------

    Resource::Type Texture::getType() const
    {
        return Type::E_RT_TEXTURE;
    }

    //--------------------------------------------------------------------------

    ResourcePtr Texture::clone() const
    {
        TexturePtr texture = Texture::create(mName, mUsage, mAccessMode, 
            mMipmaps, mTexWidth, mTexHeight, mTexUsage, mTexType, mFormat);

        if (texture != nullptr)
        {
            TResult ret = texture->load();
            if (T3D_FAILED(ret))
            {
                texture = nullptr;
            }
        }

        return texture;
    }

    //--------------------------------------------------------------------------

    TResult Texture::load()
    {
        TResult ret = T3D_OK;

        do 
        {
            if (E_TU_DEFAULT == mTexUsage)
            {
                // 加载纹理数据
                Image image;
                ret = image.load(mName);
                if (T3D_FAILED(ret))
                {
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Load image %s failed !",
                        mName.c_str());
                    break;
                }

                if (mTexWidth == 0)
                {
                    mTexWidth = image.getWidth();
                }

                if (mTexHeight == 0)
                {
                    mTexHeight = image.getHeight();
                }

                // 创建硬件缓冲区
                mPBO = T3D_HARDWARE_BUFFER_MGR.createPixelBuffer(mTexWidth, 
                    mTexHeight, mFormat, image.getData(), mUsage, mAccessMode, 
                    mMipmaps);

                if (mPBO == nullptr)
                {
                    ret = T3D_ERR_INVALID_POINTER;
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Create pixel buffer "
                        "failed !");
                    break;
                }
            }
            else
            {
                // 创建硬件缓冲区
                mPBO = T3D_HARDWARE_BUFFER_MGR.createPixelBuffer(mTexWidth, 
                    mTexHeight, mFormat, nullptr, mUsage, mAccessMode, mMipmaps);

                if (mPBO == nullptr)
                {
                    ret = T3D_ERR_INVALID_POINTER;
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Create pixel buffer "
                        "failed !");
                    break;
                }
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Texture::unload()
    {
        mPBO = nullptr;
        return Resource::unload();
    }

    //--------------------------------------------------------------------------

    TResult Texture::saveToFile(const String &path, uint32_t fileType) const
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mPBO == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Not initialize !");
                break;
            }

            Image image;
            ret = mPBO->writeImage(image);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Write to image failed !");
                break;
            }

            ret = image.save(path, fileType);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Save to file failed !");
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Texture::copyTo(TexturePtr texture, Rect *dstRect /* = nullptr */,
        Rect *srcRect /* = nullptr */)
    {
        if (!texture->isLoaded())
        {
            texture->load();
        }

        return mPBO->copyTo(texture->getPixelBuffer(), dstRect, srcRect);
    }
}

