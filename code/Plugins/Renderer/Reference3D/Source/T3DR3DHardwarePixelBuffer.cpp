/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2019  Answer Wong
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


#include "T3DR3DHardwarePixelBuffer.h"
#include "T3DR3DError.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    R3DHardwarePixelBufferPtr R3DHardwarePixelBuffer::create(size_t width,
        size_t height, PixelFormat format, const void *pixels, Usage usage, 
        uint32_t mode)
    {
        R3DHardwarePixelBufferPtr pb = new R3DHardwarePixelBuffer(width, height,
            format, pixels, usage, mode);
        pb->release();
        return pb;
    }

    //--------------------------------------------------------------------------

    R3DHardwarePixelBuffer::R3DHardwarePixelBuffer(size_t width, size_t height, 
        PixelFormat format, const void *pixels, Usage usage, uint32_t mode)
        : HardwarePixelBuffer(width, height, format, usage, mode)
        , mBuffer(nullptr)
        , mLockedBuffer(nullptr)
        , mNeedWriteBack(false)
    {
        mBuffer = new uint8_t[mBufferSize];
        mLockedBuffer = new uint8_t[mBufferSize];
        memcpy(mBuffer, pixels, mBufferSize);
    }

    //--------------------------------------------------------------------------

    R3DHardwarePixelBuffer::~R3DHardwarePixelBuffer()
    {
        T3D_SAFE_DELETE_ARRAY(mLockedBuffer);
        T3D_SAFE_DELETE_ARRAY(mBuffer);
    }

    //--------------------------------------------------------------------------

    TResult R3DHardwarePixelBuffer::readImage(const Image &image, 
        Rect *srcRect /* = nullptr */, Rect *dstRect /* = nullptr */)
    {
        TResult ret = T3D_OK;

        uint8_t *dst = nullptr;

        do
        {
            size_t bpp = Image::getBPP(mFormat);
            Image temp;
            size_t dstPitch = 0;
            Rect rtDst;

            if (dstRect == nullptr)
            {
                dst = (uint8_t *)lock(LockOptions::WRITE_DISCARD);
                dstPitch = mPitch;
                rtDst = Rect(0, 0, mWidth - 1, mHeight - 1);
            }
            else
            {
                rtDst = *dstRect;
                dst = (uint8_t *)lock(rtDst, LockOptions::WRITE, dstPitch);
            }

            // 临时构造一个图像对象，用于复制数据
            ret = temp.load(dst, rtDst.width(), rtDst.height(), bpp,
                dstPitch, mFormat);
            if (ret != T3D_OK)
            {
                T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Load temporary image \
                        for reading image failed !");
                break;
            }

            // 复制图像数据到纹理
            ret = temp.copy(image, srcRect);
            if (ret != T3D_OK)
            {
                T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Copy temporary image \
                        for reading image failed !");
                break;
            }

            unlock();
            dst = nullptr;

            ret = true;
        } while (0);

        if (dst != nullptr)
        {
            unlock();
            dst = nullptr;
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DHardwarePixelBuffer::writeImage(Image &image,
        Rect *dstRect /* = nullptr */, Rect *srcRect /* = nullptr */)
    {
        TResult ret = T3D_OK;

        uint8_t *src = nullptr;

        do
        {
            size_t bpp = Image::getBPP(mFormat);
            Image temp;
            size_t srcPitch = 0;
            Rect rtSrc;

            if (srcRect == nullptr)
            {
                src = (uint8_t *)lock(LockOptions::READ);
                srcPitch = mPitch;
                rtSrc = Rect(0, 0, mWidth - 1, mHeight - 1);
            }

            // 临时构造一个图像对象，用于复制数据
            ret = temp.load(src, mWidth, mHeight, bpp, mPitch, mFormat);
            if (ret != T3D_OK)
            {
                T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Load temporary image \
                        for writing image failed !");
                break;
            }

            // 复制图像数据到纹理
            ret = image.copy(temp, dstRect);
            if (ret != T3D_OK)
            {
                T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Copy temporary image \
                        for writing image failed !");
                break;
            }

            unlock();
            src = nullptr;

            ret = true;
        } while (0);

        if (src != nullptr)
        {
            unlock();
            src = nullptr;
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    void *R3DHardwarePixelBuffer::lockImpl(const Rect &rect,
        LockOptions options, size_t &lockedPitch)
    {
        if (rect.left < 0 || rect.right < 0
            || rect.right >= getWidth() || rect.bottom >= getHeight())
        {
            // 越界了
            return nullptr;
        }

        TResult ret = T3D_OK;
        uint8_t *lockedBuffer = nullptr;

        do 
        {
            if (LockOptions::READ == options)
            {
                if (mUsage != Usage::STATIC)
                {
                    ret = lockBuffer(rect, lockedPitch);

                    if (ret != T3D_OK)
                    {
                        break;
                    }

                    mNeedWriteBack = true;
                    mLockedRect = rect;
                    lockedBuffer = mLockedBuffer;
                }
            }
            else
            {
                if (rect.width() == mWidth && rect.height() == mHeight)
                {
                    // 获取整个纹理数据，则直接返回地址，不用再复制了
                    mNeedWriteBack = false;
                    mLockedRect = rect;
                    lockedBuffer = mBuffer;
                }
                else
                {
                    // 不是，那就要费点功夫了，只能先拷贝出来了
                    ret = lockBuffer(rect, lockedPitch);

                    if (ret != T3D_OK)
                    {
                        break;
                    }

                    mNeedWriteBack = true;
                    mLockedRect = rect;
                    lockedBuffer = mLockedBuffer;
                }
            }
        } while (0);

        return lockedBuffer;
    }

    //--------------------------------------------------------------------------

    TResult R3DHardwarePixelBuffer::unlockImpl()
    {
        TResult ret = T3D_OK;

        if (mNeedWriteBack)
        {
            // 需要回写的才复制一遍，不需要的就直接跳过了
            ret = unlockBuffer();
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DHardwarePixelBuffer::lockBuffer(const Rect &rect,
        size_t &lockedPitch)
    {
        TResult ret = T3D_OK;

        do 
        {
            // 借助 Image 对象来复制图像数据
            size_t bpp = Image::getBPP(mFormat);

            // 源数据构建源图像
            Image srcImage;
            ret = srcImage.load(mBuffer, mWidth, mHeight, bpp, mPitch,
                mFormat);

            if (ret != T3D_OK)
            {
                break;
            }

            // 目标数据构建目标图像
            Image dstImage;
            size_t pitch
                = Image::calcPitch(rect.width(), rect.height());
            ret = dstImage.load(mLockedBuffer, (int32_t)rect.width(),
                (int32_t)rect.height(), bpp, pitch, mFormat);

            if (ret != T3D_OK)
            {
                break;
            }

            ret = dstImage.copy(srcImage, &rect);
            if (ret != T3D_OK)
            {
                break;
            }

            lockedPitch = pitch;
        } while (0);
        
        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DHardwarePixelBuffer::unlockBuffer()
    {
        TResult ret = T3D_OK;

        do
        {
            // 借助 Image 对象来复制图像数据
            size_t bpp = Image::getBPP(mFormat);

            // 源数据构建源图像
            Image srcImage;
            size_t pitch
                = Image::calcPitch(mLockedRect.width(), mLockedRect.height());
            ret = srcImage.load(mLockedBuffer, mLockedRect.width(),
                mLockedRect.height(), bpp, pitch,
                mFormat);

            if (ret != T3D_OK)
            {
                break;
            }

            // 目标数据构建目标图像
            Image dstImage;
            ret = dstImage.load(mLockedBuffer, mWidth, mHeight,
                bpp, mPitch, mFormat);

            if (ret != T3D_OK)
            {
                break;
            }

            ret = dstImage.copy(srcImage, nullptr, &mLockedRect);
            if (ret != T3D_OK)
            {
                break;
            }
        } while (0);

        return ret;
    }
}
