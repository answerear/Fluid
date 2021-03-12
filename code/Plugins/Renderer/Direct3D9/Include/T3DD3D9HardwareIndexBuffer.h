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


#ifndef __T3D_D3D9_HARDWARE_INDEX_BUFFER_H__
#define __T3D_D3D9_HARDWARE_INDEX_BUFFER_H__


#include "T3DD3D9Prerequisites.h"


namespace Tiny3D
{
    /**
     * @brief Direct3D9 渲染器相关的索引缓冲区类
     */
    class D3D9HardwareIndexBuffer : public HardwareIndexBuffer
    {
    public:
        /**
         * @brief 创建 Direct3D9 渲染器相关的索引缓冲区对象
         */
        static D3D9HardwareIndexBufferPtr create(Type indexType,
            size_t indexCount, HardwareBuffer::Usage usage,
            bool useSystemMemory, bool useShadowBuffer);

        /**
         * @brief 析构函数
         */
        virtual ~D3D9HardwareIndexBuffer();

        /**
         * @brief 从缓冲区读取数据出来，实现基类接口
         * @see size_t HardwareVertexBuffer::readData(size_t offset,
         *          size_t size, void *dst)
         */
        virtual size_t readData(size_t offset, size_t size, void *dst) override;

        /**
         * @brief 向缓冲区写数据，实现基类接口
         * @see size_t HardwareVertexBuffer::writeData(size_t offset,
         *          size_t size, const void *src, bool discardWholeBuffer)
         */
        virtual size_t writeData(size_t offset, size_t size, const void *src,
            bool discardWholeBuffer = false) override;

        /**
         * @brief 获取D3D索引缓冲对象
         */
        LPDIRECT3DINDEXBUFFER9 getD3DIndexBuffer()
        {
            return mD3DIndexBuffer;
        }

    protected:
        /**
         * @brief 构造函数
         */
        D3D9HardwareIndexBuffer(Type indexType, size_t indexCount,
            HardwareBuffer::Usage usage, bool useSystemMemory,
            bool useShadowBuffer);

        /**
         * @brief 初始化对象
         */
        virtual TResult init();

        /**
         * @brief 锁定缓冲区的具体实现接口，实现基类接口
         * @see void *HardwareVertexBuffer::lockImpl(size_t offset, size_t size,
         *          LockOptions options)
         */
        virtual void *lockImpl(size_t offset, size_t size,
            LockOptions options) override;

        /**
         * @brief 解锁缓冲区的具体实现接口，实现基类接口
         * @see TResult HardwareVertexBuffer::unlockImpl()
         */
        virtual TResult unlockImpl() override;

    protected:
        LPDIRECT3DINDEXBUFFER9  mD3DIndexBuffer;
        D3DINDEXBUFFER_DESC     mBufferDesc;
    };
}


#endif  /*__T3D_D3D9_HARDWARE_INDEX_BUFFER_H__*/
