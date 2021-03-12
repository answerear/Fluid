﻿/*******************************************************************************
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


#ifndef __T3D_D3D11_HARDWARE_INDEX_BUFFER_H__
#define __T3D_D3D11_HARDWARE_INDEX_BUFFER_H__


#include "T3DD3D11Prerequisites.h"
#include "T3DD3D11HardwareBuffer.h"


namespace Tiny3D
{
    /**
     * @class   D3D11HardwareIndexBuffer.
     * @brief   DirectX 11 渲染器相关的索引缓冲区类
     */
    class D3D11HardwareIndexBuffer : public HardwareIndexBuffer
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static D3D11HardwareIndexBufferPtr 
         *      D3D11HardwareIndexBuffer::create(Type indexType, 
         *      size_t indexCount, const void *indices, 
         *      HardwareBuffer::Usage usage, uint32_t mode);
         * @brief   创建 Direct3D9 渲染器相关的索引缓冲区对象
         * @param [in]  indexType   索引类型.
         * @param [in]  indexCount  索引数量.
         * @param [in]  indices     索引数据.
         * @param [in]  usage       缓冲区使用方式.
         * @param [in]  mode        缓冲区访问方式.
         * @returns 返回 DirectX 11 相关的 GPU 索引缓冲区对象.
         */
        static D3D11HardwareIndexBufferPtr create(Type indexType,
            size_t indexCount, const void *indices, HardwareBuffer::Usage usage,
            uint32_t mode);

        /**
         * @fn  virtual D3D11HardwareIndexBuffer::~D3D11HardwareIndexBuffer();
         * @brief   析构函数
         */
        virtual ~D3D11HardwareIndexBuffer();

        /**
         * @fn  virtual size_t D3D11HardwareIndexBuffer::readData(size_t offset, 
         *      size_t size, void *dst) override;
         * @brief   从缓冲区读取数据出来。 实现基类接口
         * @param [in]  offset  要读取的相对缓冲区首地址的偏移位置.
         * @param [in]  size    要读取缓冲区大小.
         * @param [in]  dst     存储返回读取到数据的缓冲区首地址.
         * @returns 返回读取的字节数.
         * @sa  size_t HardwareBuffer::readData(size_t offset, size_t size, 
         *      void *dst)
         */
        virtual size_t readData(size_t offset, size_t size, void *dst) override;

        /**
         * @fn  virtual size_t D3D11HardwareIndexBuffer::writeData(
         *      size_t offset, size_t size, const void *src, 
         *      bool discardWholeBuffer = false) override;
         * @brief   向缓冲区写数据。 实现基类接口
         * @param [in]  offset              要写入的相对缓冲区首地址的偏移位置.
         * @param [in]  size                要写入缓冲区大小.
         * @param [in]  src                 写入的数据地址.
         * @param [in]  discardWholeBuffer  是否丢弃原有数据，默认不丢弃.
         * @returns 返回写入的字节数.
         * @sa  size_t HardwareBuffer::writeData(size_t offset, size_t size, 
         *      const void *src, bool discardWholeBuffer)
         */
        virtual size_t writeData(size_t offset, size_t size, const void *src,
            bool discardWholeBuffer = false) override;

        /**
         * @fn  ID3D11Buffer D3D11HardwareVertexBuffer::*getD3D11Buffer()
         * @brief   获取 ID3D11Buffer 对象
         * @returns 返回 ID3D11Buffer 对象.
         */
        ID3D11Buffer *getD3D11Buffer() { return mBufferImpl->getD3DBuffer(); }

    protected:
        /**
         * @fn  D3D11HardwareIndexBuffer::D3D11HardwareIndexBuffer(
         *      Type indexType, size_t indexCount, HardwareBuffer::Usage usage, 
         *      bool useSystemMemory, bool useShadowBuffer);
         * @brief   构造函数
         * @param [in]  indexType   索引类型.
         * @param [in]  indexCount  索引数量.
         * @param [in]  usage       缓冲区使用方式.
         * @param [in]  mode        缓冲区访问方式.
         */
        D3D11HardwareIndexBuffer(Type indexType, size_t indexCount,
            HardwareBuffer::Usage usage, uint32_t mode);

        /**
         * @fn  virtual TResult 
         *      D3D11HardwareIndexBuffer::init(const void *indices);
         * @brief   初始化对象
         * @param [in]  indices 索引数据.
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult init(const void *indices);

        /**
         * @fn  virtual void D3D11HardwareIndexBuffer::*lockImpl(size_t offset, 
         *      size_t size, LockOptions options) override;
         * @brief   锁定缓冲区的具体实现接口，实现基类接口
         * @param [in]  offset  锁定区域相对缓冲区开始偏移位置.
         * @param [in]  size    锁定区域大小.
         * @param [in]  options 锁定选项.
         * @returns 返回锁定缓冲区区域首地址.
         * @sa  void *HardwareBuffer::lockImpl(size_t offset, size_t size,
         *      LockOptions options)
         */
        virtual void *lockImpl(size_t offset, size_t size,
            LockOptions options) override;

        /**
         * @fn  virtual TResult D3D11HardwareIndexBuffer::unlockImpl() override;
         * @brief   解锁缓冲区的具体实现接口，实现基类接口
         * @returns 成功调用返回 T3D_OK.
         * @sa  TResult HardwareBuffer::unlockImpl()
         */
        virtual TResult unlockImpl() override;

    protected:
        D3D11HardwareBufferPtr  mBufferImpl;    /**< D3D11 Buffer 具体实现 */
    };
}


#endif  /*__T3D_D3D11_HARDWARE_INDEX_BUFFER_H__*/
