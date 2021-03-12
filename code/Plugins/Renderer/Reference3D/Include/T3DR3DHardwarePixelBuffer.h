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


#ifndef __T3D_R3D_HARDWARE_PIXEL_BUFFER_H__
#define __T3D_R3D_HARDWARE_PIXEL_BUFFER_H__


#include "T3DR3DPrerequisites.h"


namespace Tiny3D
{
    /**
     * @brief Reference3D 渲染器相关的像素缓冲区类
     */
    class R3DHardwarePixelBuffer : public HardwarePixelBuffer
    {
    public:
        /**
         * @brief 创建 Reference3D 渲染器相关的像素缓冲区对象
         */
        static R3DHardwarePixelBufferPtr create(size_t width, size_t height,
            PixelFormat format, const void *pixels, Usage usage, uint32_t mode);

        /**
         * @brief 析构函数
         */
        virtual ~R3DHardwarePixelBuffer();

        /**
         * @brief 按照源区域从image读取数据到目标区域。 实现基类接口
         */
        virtual TResult readImage(const Image &image, Rect *srcRect = nullptr,
            Rect *dstRect = nullptr) override;

        /**
        * @brief 把指定源区域范围数据写到image的目标区域。 实现基类接口
        */
        virtual TResult writeImage(Image &image, Rect *dstRect = nullptr,
            Rect *srcRect = nullptr) override;

    protected:
        /**
         * @brief 构造函数
         */
        R3DHardwarePixelBuffer(size_t width, size_t height,
            PixelFormat format, const void *pixels, Usage usage, uint32_t mode);

        /**
        * @brief 获取锁定硬件缓冲区不同渲染器实现接口。 实现基类接口
        */
        virtual void *lockImpl(const Rect &rect, LockOptions options,
            size_t &lockedPitch) override;

        /**
        * @brief 解锁缓冲区的具体实现接口，实现基类接口
        * @see TResult HardwareVertexBuffer::unlockImpl()
        */
        virtual TResult unlockImpl() override;

        /**
         * @brief 生成锁定缓冲区
         * @param [in] rect : 锁定缓冲区区域
         * @param [in] lockedPitch : 锁定缓冲区的行跨度
         * @return 调用成功返回 T3D_OK
         */
        TResult lockBuffer(const Rect &rect, size_t &lockedPitch);

        /**
         * @brief 解锁缓冲区，把返回出去的锁定缓冲区的数据回写到正是的缓冲区中
         * @return 调用成功返回 T3D_OK
         */
        TResult unlockBuffer();

    protected:
        uint8_t *mBuffer;       /**< 像素缓冲区 */
        uint8_t *mLockedBuffer; /**< 锁定的缓冲区 */
        Rect    mLockedRect;    /**< 锁定的区域 */
        bool    mNeedWriteBack; /**< 需要回写 */
    };
}


#endif  /*__T3D_R3D_HARDWARE_PIXEL_BUFFER_H__*/
