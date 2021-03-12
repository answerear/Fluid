/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2020  Answer Wong
 * For latest info, see https://github.com/answerear/D3D11
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


#ifndef __T3D_D3D11_PIXEL_BUFFER_H__
#define __T3D_D3D11_PIXEL_BUFFER_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    /**
     * @class   D3D11HardwarePixelBuffer
     * @brief   DirectX 11 渲染器相关的像素缓冲区类
     */
    class D3D11PixelBuffer : public HardwarePixelBuffer
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static D3D11PixelBufferPtr 
         *      D3D11HardwarePixelBuffer::create(size_t width, size_t height, 
         *      PixelFormat format, const void *pixels, Usage usage, 
         *      uint32_t mode);
         * @brief   创建 DirectX 11 渲染器相关的像素缓冲区对象
         * @param [in]  width   像素缓冲区宽度.
         * @param [in]  height  像素缓冲区高度.
         * @param [in]  format  像素缓冲区格式.
         * @param [in]  pixels  像素数据.
         * @param [in]  usage   缓冲区用途.
         * @param [in]  mode    缓冲区访问方式.
         * @returns 返回一个 GPU 像素缓冲区对象.
         */
        static D3D11PixelBufferPtr create(size_t width, size_t height,
            PixelFormat format, const void *pixels, Usage usage, uint32_t mode,
            size_t mipmaps);

        /**
         * @fn  virtual D3D11HardwarePixelBuffer::~D3D11HardwarePixelBuffer();
         * @brief   析构函数
         */
        virtual ~D3D11PixelBuffer();

        /**
         * @fn  virtual TResult D3D11HardwarePixelBuffer::readImage(
         *      const Image &image, Rect *srcRect = nullptr, 
         *      Rect *dstRect = nullptr) override;
         * @brief   按照源区域从image读取数据到目标区域。 实现基类接口
         * @param [in]  image   要读取的图像对象.
         * @param [in]  srcRect 源数据区域，默认为nullptr的时候，
         *    表示整个源目标区域，会自动缩放匹配目标区域.
         * @param [in]  dstRect 目标数据区域，默认为nullptr的时候，
         *    表示整个目标区域，会自动缩放匹配源区域.
         * @returns 调用成功返回 T3D_OK.
         * @sa  TResult HardwarePixelBuffer::readImage(const Image &image, 
         *      Rect *srcRect = nullptr, Rect *dstRect = nullptr)
         */
        virtual TResult readImage(const Image &image, Rect *srcRect = nullptr,
            Rect *dstRect = nullptr) override;

        /**
         * @fn  virtual TResult D3D11HardwarePixelBuffer::writeImage(
         *      Image &image, Rect *dstRect = nullptr, 
         *      Rect *srcRect = nullptr) override;
         * @brief   把指定源区域范围数据写到image的目标区域。 实现基类接口
         * @param [in]  image   要写入的图像对象.
         * @param [in]  dstRect 目标区域，默认为nullptr的时候，
         *    表示整个目标区域，会自动缩放匹配源区域.
         * @param [in]  srcRect 源区域，默认为nullptr的时候，
         *    表示整个源目标区域，会自动缩放匹配目标区域.
         * @returns 调用成功返回 T3D_OK.
         * @sa  TResult HardwarePixelBuffer::writeImage(Image &image, 
         *      Rect *dstRect = nullptr, Rect *srcRect = nullptr)
         */
        virtual TResult writeImage(Image &image, Rect *dstRect = nullptr,
            Rect *srcRect = nullptr) override;

        /**
         * @fn  ID3D11Texture2D D3D11HardwarePixelBuffer::*getD3DTexture()
         * @brief   获取 ID3D11Texture2D 对象
         * @return  Null if it fails, else the d 3D texture.
         */
        ID3D11Texture2D *getD3DTexture() { return mD3DTexture2D; }

        /**
         * @fn  ID3D11ShaderResourceView 
         *      D3D11HardwarePixelBuffer::*getD3DSRView()
         * @brief   获取 ID3D11ShaderResourceView 对象
         * @return  Null if it fails, else the d 3D sr view.
         */
        ID3D11ShaderResourceView *getD3DSRView() { return mD3DSRView; }

    protected:
        /**
         * @fn  D3D11HardwarePixelBuffer::D3D11HardwarePixelBuffer(size_t width, 
         *      size_t height, PixelFormat format, Usage usage, uint32_t mode);
         * @brief   构造函数
         * @param [in]  width   像素缓冲区宽度.
         * @param [in]  height  像素缓冲区高度.
         * @param [in]  format  像素缓冲区格式.
         * @param [in]  usage   缓冲区用途.
         * @param [in]  mode    缓冲区访问方式.
         */
        D3D11PixelBuffer(size_t width, size_t height,
            PixelFormat format, Usage usage, uint32_t mode, size_t mipmaps);

        /**
         * @fn  virtual TResult D3D11HardwarePixelBuffer::init(
         *      const void *pixels);
         * @brief   初始化对象
         * @param [in]  pixels  像素数据.
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult init(const void *pixels);

        /**
         * @fn  virtual void D3D11HardwarePixelBuffer::*lockImpl(
         *      const Rect &rect, LockOptions options, 
         *      size_t &lockedPitch) override;
         * @brief   获取锁定硬件缓冲区不同渲染器实现接口。 实现基类接口
         * @param [in]      rect        要获取数据的区域.
         * @param [in]      options     获取数据选项.
         * @param [in, out] lockedPitch 返回锁定区域的行跨度.
         * @returns 返回锁定的硬件数据地址.
         * @sa  void *HardwarePixelBuffer::lockImpl(const Rect &rect, 
         *      LockOptions options, size_t &lockedPitch)
         */
        virtual void *lockImpl(const Rect &rect, LockOptions options,
            size_t &lockedPitch) override;

        /**
         * @fn  virtual TResult D3D11HardwarePixelBuffer::unlockImpl() override;
         * @brief   解锁缓冲区的具体实现接口
         * @returns 成功调用返回 T3D_OK.
         * @sa  TResult HardwarePixelBuffer::unlockImpl()
         */
        virtual TResult unlockImpl() override;

    protected:
        ID3D11Texture2D             *mD3DTexture2D;
        ID3D11ShaderResourceView    *mD3DSRView;
    };
}


#endif  /*__T3D_D3D11_PIXEL_BUFFER_H__*/