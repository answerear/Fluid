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


#include "T3DD3D9HardwarePixelBuffer.h"
#include "T3DD3D9Mappings.h"
#include "T3DD3D9Renderer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    D3D9HardwarePixelBufferPtr D3D9HardwarePixelBuffer::create(size_t width,
        size_t height, PixelFormat format, Usage usage, bool useSystemMemory,
        bool useShadowBuffer)
    {
        D3D9HardwarePixelBufferPtr pb = new D3D9HardwarePixelBuffer(width, 
            height, format, usage, useSystemMemory, useShadowBuffer);
        pb->release();

        if (pb->init() != T3D_OK)
        {
            pb = nullptr;
        }

        return pb;
    }

    //--------------------------------------------------------------------------

    D3D9HardwarePixelBuffer::D3D9HardwarePixelBuffer(size_t width,
        size_t height, PixelFormat format, Usage usage, bool useSystemMemory,
        bool useShadowBuffer)
        : HardwarePixelBuffer(width, height, format, usage, useSystemMemory,
            useShadowBuffer)
    {
    }

    //--------------------------------------------------------------------------

    D3D9HardwarePixelBuffer::~D3D9HardwarePixelBuffer()
    {
        D3D_SAFE_RELEASE(mD3DTexture);
    }

    //--------------------------------------------------------------------------

    TResult D3D9HardwarePixelBuffer::init()
    {
        TResult ret = T3D_OK;

        do 
        {
            LPDIRECT3DDEVICE9 D3DDevice = D3D9_RENDERER.getD3DDevice();

            D3DFORMAT format = D3D9Mappings::get(mFormat);
            HRESULT hr = D3DXCreateTexture(D3DDevice, mWidth, mHeight, 1, 0, 
                format, D3DPOOL_MANAGED, &mD3DTexture);

            if (FAILED(hr))
            {
                break;
            }

            D3DSURFACE_DESC desc;
            hr = mD3DTexture->GetLevelDesc(0, &desc);

            if (FAILED(hr))
            {
                D3D_SAFE_RELEASE(mD3DTexture);
                break;
            }

            mFormat = D3D9Mappings::get(desc.Format);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D9HardwarePixelBuffer::readImage(const Image &image,
        Rect *srcRect /* = nullptr */, Rect *dstRect /* = nullptr */)
    {
        TResult ret = T3D_OK;

        uint8_t *dst = nullptr;

        do
        {
            int32_t bpp = Image::getBPP(mFormat);
            Image temp;
            int32_t dstPitch = 0;
            Rect rtDst;

            if (dstRect == nullptr)
            {
                dst = (uint8_t *)lock(E_HBL_DISCARD);
                dstPitch = mPitch;
                rtDst = Rect(0, 0, mWidth - 1, mHeight - 1);
            }
            else
            {
                rtDst = *dstRect;
                dst = (uint8_t *)lock(rtDst, E_HBL_WRITE_ONLY, dstPitch);
            }

            // 临时构造一个图像对象，用于复制数据
            ret = temp.load(dst, rtDst.width(), rtDst.height(), bpp,
                dstPitch, mFormat);
            if (ret != T3D_OK)
            {
                T3D_LOG_ERROR(LOG_TAG_D3D9RENDERER, "Load temporary image \
                        for reading image failed !");
                break;
            }

            // 复制图像数据到纹理
            ret = temp.copy(image, srcRect);
            if (ret != T3D_OK)
            {
                T3D_LOG_ERROR(LOG_TAG_D3D9RENDERER, "Copy temporary image \
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

    TResult D3D9HardwarePixelBuffer::writeImage(Image &image,
        Rect *dstRect /* = nullptr */, Rect *srcRect /* = nullptr */)
    {
        TResult ret = T3D_OK;

        uint8_t *src = nullptr;

        do
        {
            int32_t bpp = Image::getBPP(mFormat);
            Image temp;
            int32_t srcPitch = 0;
            Rect rtSrc;

            if (srcRect == nullptr)
            {
                src = (uint8_t *)lock(E_HBL_READ_ONLY);
                srcPitch = mPitch;
                rtSrc = Rect(0, 0, mWidth - 1, mHeight - 1);
            }

            // 临时构造一个图像对象，用于复制数据
            ret = temp.load(src, mWidth, mHeight, bpp, mPitch, mFormat);
            if (ret != T3D_OK)
            {
                T3D_LOG_ERROR(LOG_TAG_D3D9RENDERER, "Load temporary image \
                        for writing image failed !");
                break;
            }

            // 复制图像数据到纹理
            ret = image.copy(temp, dstRect);
            if (ret != T3D_OK)
            {
                T3D_LOG_ERROR(LOG_TAG_D3D9RENDERER, "Copy temporary image \
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

    void *D3D9HardwarePixelBuffer::lockImpl(const Rect &rect,
        LockOptions options, int32_t &lockedPitch)
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
            D3DLOCKED_RECT d3dRect;
            RECT winRect = { rect.left, rect.top, rect.right, rect.bottom };
            HRESULT hr = mD3DTexture->LockRect(0, &d3dRect, &winRect, 0);
            if (FAILED(hr))
            {
                
            }

            lockedPitch = d3dRect.Pitch;
        } while (0);

        return lockedBuffer;
    }

    //--------------------------------------------------------------------------

    TResult D3D9HardwarePixelBuffer::unlockImpl()
    {
        TResult ret = T3D_OK;

        do 
        {
            HRESULT hr = mD3DTexture->UnlockRect(0);
            if (FAILED(hr))
            {

            }
        } while (0);

        return ret;
    }
}


