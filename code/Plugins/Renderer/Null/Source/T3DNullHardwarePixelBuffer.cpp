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


#include "T3DD3D11HardwarePixelBuffer.h"
#include "T3DD3D11Mappings.h"
#include "T3DD3D11Renderer.h"
#include "T3DD3D11Error.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11HardwarePixelBuffer, HardwarePixelBuffer);

    //--------------------------------------------------------------------------

    D3D11HardwarePixelBufferPtr D3D11HardwarePixelBuffer::create(size_t width,
        size_t height, PixelFormat format, const void *pixels, Usage usage, 
        uint32_t mode, size_t mipmaps)
    {
        D3D11HardwarePixelBufferPtr pb = new D3D11HardwarePixelBuffer(width, 
            height, format, usage, mode, mipmaps);
        pb->release();

        if (pb->init(pixels) != T3D_OK)
        {
            pb = nullptr;
        }

        return pb;
    }

    //--------------------------------------------------------------------------

    D3D11HardwarePixelBuffer::D3D11HardwarePixelBuffer(size_t width,
        size_t height, PixelFormat format, Usage usage, uint32_t mode, 
        size_t mipmaps)
        : HardwarePixelBuffer(width, height, format, usage, mode, mipmaps)
        , mD3DTexture2D(nullptr)
        , mD3DSRView(nullptr)
    {
    }

    //--------------------------------------------------------------------------

    D3D11HardwarePixelBuffer::~D3D11HardwarePixelBuffer()
    {
        D3D_SAFE_RELEASE(mD3DSRView);
        D3D_SAFE_RELEASE(mD3DTexture2D);
    }

    //--------------------------------------------------------------------------

    TResult D3D11HardwarePixelBuffer::init(const void *pixels)
    {
        TResult ret = T3D_OK;

        do 
        {
            D3D11_USAGE d3dUsage;
            uint32_t d3dAccessFlag;
            D3D11Mappings::get(mUsage, mAccessMode, d3dUsage, d3dAccessFlag);

            DXGI_FORMAT d3dFmt = D3D11Mappings::get(mFormat);

            D3D11_TEXTURE2D_DESC d3dDesc;
            d3dDesc.Width = (UINT)mWidth;
            d3dDesc.Height = (UINT)mHeight;
            d3dDesc.MipLevels = (UINT)mMipmaps;
            d3dDesc.ArraySize = 1;
            d3dDesc.Format = d3dFmt;
            d3dDesc.SampleDesc.Count = 1;
            d3dDesc.SampleDesc.Quality = 0;
            d3dDesc.Usage = d3dUsage;
            d3dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            d3dDesc.CPUAccessFlags = d3dAccessFlag;
            d3dDesc.MiscFlags = 0;

            D3D11_SUBRESOURCE_DATA d3dData;
            d3dData.pSysMem = pixels;
            d3dData.SysMemPitch = (UINT)Image::calcPitch(mWidth, 32);
            d3dData.SysMemSlicePitch = 0;

            ID3D11Device *pD3DDevice = D3D11_RENDERER.getD3DDevice();
            HRESULT hr = pD3DDevice->CreateTexture2D(&d3dDesc, &d3dData,
                &mD3DTexture2D);
            if (FAILED(hr))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create texture 2D failed ! DX ERROR [%d]", hr);
                ret = T3D_ERR_D3D11_CREATE_TEXTURE2D;
                break;
            }

            D3D11_SHADER_RESOURCE_VIEW_DESC d3dResDesc;
            d3dResDesc.Format = d3dFmt;
            d3dResDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            d3dResDesc.Texture2D.MipLevels = (UINT)mMipmaps;
            d3dResDesc.Texture2D.MostDetailedMip = 0;
            hr = pD3DDevice->CreateShaderResourceView(mD3DTexture2D, 
                &d3dResDesc, &mD3DSRView);
            if (FAILED(hr))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create shader resource view failed ! DX ERROR [%d]", hr);
                ret = T3D_ERR_D3D11_CREATE_TEXTURE2D;
                break;
            }

//             if (mMipmaps != 1)
//             {
//                 ID3D11DeviceContext *pD3DContext 
//                     = D3D11_RENDERER.getD3DDeviceContext();
//                 pD3DContext->GenerateMips(mD3DSRView);
//             }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11HardwarePixelBuffer::readImage(const Image &image,
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
                dst = (uint8_t *)lock(rtDst, LockOptions::WRITE, 
                    dstPitch);
            }

            // 临时构造一个图像对象，用于复制数据
            ret = temp.load(dst, rtDst.width(), rtDst.height(), bpp,
                dstPitch, mFormat);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, "Load temporary image \
                        for reading image failed !");
                break;
            }

            // 复制图像数据到纹理
            ret = temp.copy(image, srcRect);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, "Copy temporary image \
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

    TResult D3D11HardwarePixelBuffer::writeImage(Image &image,
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
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, "Load temporary image \
                        for writing image failed !");
                break;
            }

            // 复制图像数据到纹理
            ret = image.copy(temp, dstRect);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, "Copy temporary image \
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

    void *D3D11HardwarePixelBuffer::lockImpl(const Rect &rect,
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
            
        } while (0);

        return lockedBuffer;
    }

    //--------------------------------------------------------------------------

    TResult D3D11HardwarePixelBuffer::unlockImpl()
    {
        TResult ret = T3D_OK;

        do 
        {
            
        } while (0);

        return ret;
    }
}


