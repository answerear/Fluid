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


#ifndef __T3D_HARDWARE_PIXEL_BUFFER_H__
#define __T3D_HARDWARE_PIXEL_BUFFER_H__


#include "Render/T3DHardwareBuffer.h"
#include "Kernel/T3DCommon.h"
#include "ImageCodec/T3DImage.h"


namespace Tiny3D
{
    /**
     * @class   HardwarePixelBuffer
     * @brief   像素缓冲区
     * @sa  class HardwareBuffer
     */
    class T3D_ENGINE_API HardwarePixelBuffer : public HardwareBuffer
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  virtual HardwarePixelBuffer::~HardwarePixelBuffer();
         * @brief   析构函数
         */
        virtual ~HardwarePixelBuffer();

        /**
         * @fn  virtual void HardwarePixelBuffer::*lock(const Rect &rect, 
         *      LockOptions options, size_t &lockedPitch);
         * @brief   获取硬件缓冲区数据
         * @param [in]      rect        要获取数据的区域.
         * @param [in]      options     获取数据选项.
         * @param [in, out] lockedPitch 返回锁定区域的pitch.
         * @returns 返回锁定的硬件数据地址.
         * @sa  enum LockOptions
         */
        virtual void *lock(const Rect &rect, LockOptions options, 
            size_t &lockedPitch);

        /**
         * @fn  virtual void HardwarePixelBuffer::*lock(
         *      LockOptions options) override;
         * @brief   获取硬件缓冲区数据
         * @param [in]  options 获取数据选项.
         * @returns 返回数据指针地址
         * @remarks 这个是默认获取整个像素缓冲区区域的数据.
         * @sa  enum LockOptions
         * @sa  void *HardwareBuffer::lock(LockOptions options)
         */
        virtual void *lock(LockOptions options) override;

        /**
         * @fn  virtual TResult HardwarePixelBuffer::copyTo(
         *      HardwarePixelBufferPtr dst, Rect *dstRect = nullptr, 
         *      Rect *srcRect = nullptr);
         * @brief   复制数据到另外一个HardwarePixelBuffer
         * @param [in]  dst     目标pixel buffer.
         * @param [in]  dstRect 目标数据区域，默认为nullptr的时候，
         *    表示整个目标区域，会自动缩放匹配源区域.
         * @param [in]  srcRect 源数据区域，默认为nullptr的时候，
         *    表示整个源数据区域，会自动缩放匹配目标区域.
         * @returns 调用成功返回 T3D_OK.
         * @remarks dstRect 和 srcRect 均为nullptr的时候，
         *    会自动缩放匹配源和目标区域.
         */
        virtual TResult copyTo(HardwarePixelBufferPtr dst, 
            Rect *dstRect = nullptr, Rect *srcRect = nullptr);

        /**
         * @fn  virtual TResult HardwarePixelBuffer::readImage(
         *      const Image &image, Rect *srcRect = nullptr, 
         *      Rect *dstRect = nullptr) = 0;
         * @brief   按照源区域从image读取数据到目标区域
         * @param [in]  image   要读取的图像对象.
         * @param [in]  srcRect 源数据区域，默认为nullptr的时候，
         *    表示整个源目标区域，会自动缩放匹配目标区域.
         * @param [in]  dstRect 目标数据区域，默认为nullptr的时候，
         *    表示整个目标区域，会自动缩放匹配源区域.
         * @returns 调用成功返回 T3D_OK
         * @remarks dstRect和srcRect均为nullptr的时候，
         *    会自动缩放匹配源和目标区域.
         */
        virtual TResult readImage(const Image &image, Rect *srcRect = nullptr, 
            Rect *dstRect = nullptr) = 0;

        /**
         * @fn  virtual TResult HardwarePixelBuffer::writeImage(Image &image, 
         *      Rect *dstRect = nullptr, Rect *srcRect = nullptr) = 0;
         * @brief   把指定源区域范围数据写到image的目标区域
         * @param [in]  image   要写入的图像对象.
         * @param [in]  dstRect 目标区域，默认为nullptr的时候，
         *    表示整个目标区域，会自动缩放匹配源区域.
         * @param [in]  srcRect 源区域，默认为nullptr的时候，
         *    表示整个源目标区域，会自动缩放匹配目标区域.
         * @returns 调用成功返回 T3D_OK
         * @remarks dstRect和srcRect均为nullptr的时候，
         *    会自动缩放匹配源和目标区域.
         */
        virtual TResult writeImage(Image &image, Rect *dstRect = nullptr, 
            Rect *srcRect = nullptr) = 0;

        /**
         * @fn  size_t HardwarePixelBuffer::getWidth() const
         * @brief   获取像素缓冲区宽度
         * @returns 返回像素缓冲区宽度.
         */
        size_t getWidth() const { return mWidth; }

        /**
         * @fn  size_t HardwarePixelBuffer::getHeight() const
         * @brief   获取像素缓冲区高度
         * @returns 返回像素缓冲区高度.
         */
        size_t getHeight() const { return mHeight; }

        /**
         * @fn  size_t HardwarePixelBuffer::getPitch() const
         * @brief   获取像素缓冲区的行跨度
         * @returns 返回像素缓冲区的行跨度.
         */
        size_t getPitch() const { return mPitch; }

        /**
         * @brief   获取像素缓冲区的 mipmaps 级别数
         * @returns 返回像素缓冲区的 mipmaps 级别数
         */
        size_t getMipmaps() const { return mMipmaps; }

        /**
         * @fn  PixelFormat HardwarePixelBuffer::getFormat() const
         * @brief   获取像素缓冲区的像素格式
         * @returns 返回像素缓冲区的像素格式.
         */
        PixelFormat getFormat() const { return mFormat; }

    protected:
        /**
         * @fn  HardwarePixelBuffer::HardwarePixelBuffer(size_t width, 
         *      size_t height, PixelFormat format, Usage usage, uint32_t mode);
         * @brief   构造函数
         * @param [in]  width   像素缓冲区宽度.
         * @param [in]  height  像素缓冲区高度.
         * @param [in]  format  像素缓冲区格式.
         * @param [in]  usage   缓冲区用途.
         * @param [in]  mode    缓冲区访问方式.
         */
        HardwarePixelBuffer(size_t width, size_t height, PixelFormat format,
            Usage usage, uint32_t mode, size_t mipmaps);

    private:
        /**
         * @fn  virtual void HardwarePixelBuffer::*lockImpl(const Rect &rect, 
         *      LockOptions options, size_t &lockedPitch) = 0;
         * @brief   获取锁定硬件缓冲区不同渲染器实现接口
         * @param [in]      rect        要获取数据的区域.
         * @param [in]      options     获取数据选项.
         * @param [in, out] lockedPitch 返回锁定区域的行跨度.
         * @returns 返回锁定的硬件数据地址.
         * @remarks 具体的渲染系统子类需要实现该接口.
         * @sa  enum LockOptions
         */
        virtual void *lockImpl(const Rect &rect, LockOptions options,
            size_t &lockedPitch) = 0;

        /**
         * @fn  virtual size_t HardwarePixelBuffer::readData(size_t offset, 
         *      size_t size, void *dst) override;
         * @brief   覆盖父类实现，像素缓冲区本接口失效
         * @param [in]      offset  要读取的相对缓冲区首地址的偏移位置.
         * @param [in]      size    要读取缓冲区大小.
         * @param [in,out]  dst     存储返回读取到数据的缓冲区首地址.
         * @returns 返回读取的字节数.
         * @remarks 对于像素缓冲区来说，本接口没有意义，请使用readImage来代替.
         * @sa  size_t HardwareBuffer::readData(size_t offset, size_t size, 
         *      void *dst)
         * @sa  TResult HardwarePixelBuffer::readImage(const Image &image, 
         *      Rect *srcRect = nullptr, Rect *dstRect = nullptr)
         */
        virtual size_t readData(size_t offset, size_t size, void *dst) override;

        /**
         * @fn  virtual size_t HardwarePixelBuffer::writeData(size_t offset, 
         *      size_t size, const void *src, 
         *      bool discardWholeBuffer ) override;
         * @brief   覆盖父类实现，像素缓冲区本接口失效
         * @param [in]  offset              要写入的相对缓冲区首地址的偏移位置.
         * @param [in]  size                要写入缓冲区大小.
         * @param [in]  src                 写入的数据地址.
         * @param [in]  discardWholeBuffer  是否丢弃原有数据，默认不丢弃.
         * @returns 返回写入的字节数.
         * @remarks 对于像素缓冲区来说，本接口没有意义，请使用writeImage来代替.
         * @sa  size_t HardwareBuffer::writeData(size_t offset, size_t size,
         *      const void *src, bool discardWholeBuffer = false)
         * @sa  TResult HardwarePixelBuffer::writeImage(Image &image, 
         *      Rect *dstRect = nullptr, Rect *srcRect = nullptr)
         */
        virtual size_t writeData(size_t offset, size_t size, const void *src, 
            bool discardWholeBuffer = false) override;

        /**
         * @fn  virtual void HardwarePixelBuffer::*lockImpl(size_t offset, 
         *      size_t size, LockOptions options) override;
         * @brief   覆盖父类实现，像素缓冲区本接口失效
         * @param [in]  offset  锁定区域相对缓冲区开始偏移位置.
         * @param [in]  size    锁定区域大小.
         * @param [in]  options 锁定选项.
         * @returns 返回锁定缓冲区区域首地址.
         * @remarks 对于像素缓冲区来说，本接口没有意义，请使用lockImpl来代替.
         * @sa  void *HardwarePixelBuffer::lockImpl(const Rect &rect, 
         *      LockOptions options, size_t &lockedPitch)
         */
        virtual void *lockImpl(size_t offset, size_t size, 
            LockOptions options) override;

    protected:
        size_t      mWidth;     /**< 像素缓冲区的宽度 */
        size_t      mHeight;    /**< 像素缓冲区的高度 */
        size_t      mPitch;     /**< 像素缓冲区的行跨度 */
        size_t      mMipmaps;   /**< mipmaps level */
        PixelFormat mFormat;    /**< 像素缓冲区的格式 */
    };
}


#endif  /*__T3D_HARDWARE_PIXEL_BUFFER_H__*/
