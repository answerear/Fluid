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


#ifndef __T3D_D3D11_HARDWARE_VERTEX_BUFFER_H__
#define __T3D_D3D11_HARDWARE_VERTEX_BUFFER_H__


#include "T3DD3D11Prerequisites.h"
#include "T3DD3D11HardwareBuffer.h"


namespace Tiny3D
{
    /**
     * @class   D3D11HardwareVertexBuffer
     * @brief   DirectX 11 渲染器相關的頂點緩沖類
     */
    class D3D11HardwareVertexBuffer : public HardwareVertexBuffer
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static D3D11HardwareVertexBufferPtr
         *      D3D11HardwareVertexBuffer::create(size_t vertexSize,
         *      size_t vertexCount, const void *vertices, Usage usage,
         *      uint32_t mode);
         * @brief   創建 DirectX 11 渲染器相關的頂點緩沖對象
         * @param [in]  vertexSize  頂點字節數大小.
         * @param [in]  vertexCount 頂點數量.
         * @param [in]  vertices    頂點數據.
         * @param [in]  usage       緩沖區用法.
         * @param [in]  mode        緩沖區訪問方式.
         * @returns 返回一個 DirectX 11 頂點緩沖區對象.
         */
        static D3D11HardwareVertexBufferPtr create(size_t vertexSize,
            size_t vertexCount, const void *vertices, Usage usage,
            uint32_t mode);

        /**
         * @fn  virtual D3D11HardwareVertexBuffer::~D3D11HardwareVertexBuffer();
         * @brief   析構函數
         */
        virtual ~D3D11HardwareVertexBuffer();

        /**
         * @fn  virtual size_t D3D11HardwareVertexBuffer::readData(
         *      size_t offset, size_t size, void *dst) override;
         * @brief   從緩沖區讀取數據出來，實現基類接口.
         * @param [in]  offset  要讀取的相對緩沖區首地址的偏移位置.
         * @param [in]  size    要讀取緩沖區大小.
         * @param [in]  dst     存儲返回讀取到數據的緩沖區首地址.
         * @returns 返回讀取的字節數.
         * @sa  size_t HardwareBuffer::readData(size_t offset, size_t size,
         *      void *dst)
         */
        virtual size_t readData(size_t offset, size_t size, void *dst) override;

        /**
         * @fn  virtual size_t D3D11HardwareVertexBuffer::writeData(
         *      size_t offset, size_t size, const void *src,
         *      bool discardWholeBuffer = false) override;
         * @brief   向緩沖區寫數據，實現基類接口
         * @param [in]  offset              要寫入的相對緩沖區首地址的偏移位置.
         * @param [in]  size                要寫入緩沖區大小.
         * @param [in]  src                 寫入的數據地址.
         * @param [in]  discardWholeBuffer  是否丟棄原有數據，默認不丟棄.
         * @returns 返回寫入的字節數.
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
         * @fn  D3D11HardwareVertexBuffer::D3D11HardwareVertexBuffer(
         *      size_t vertexSize, size_t vertexCount, Usage usage,
         *      uint32_t mode);
         * @brief   構造函數
         * @param [in]  vertexSize  頂點字節數大小.
         * @param [in]  vertexCount 頂點數量.
         * @param [in]  usage       緩沖區用法.
         * @param [in]  mode        緩沖區訪問方式.
         */
        D3D11HardwareVertexBuffer(size_t vertexSize, size_t vertexCount,
            Usage usage, uint32_t mode);

        /**
         * @fn  virtual TResult D3D11HardwareVertexBuffer::init(
         *      const void *vertices);
         * @brief   初始化對象
         * @param [in]  vertices    頂點數據.
         * @returns 調用成功返回 T3D_OK.
         */
        virtual TResult init(const void *vertices);

        /**
         * @fn  virtual void D3D11HardwareVertexBuffer::*lockImpl(size_t offset,
         *      size_t size, LockOptions options) override;
         * @brief   鎖定緩沖區的具體實現接口，實現基類接口
         * @param [in]  offset  鎖定區域相對緩沖區開始偏移位置.
         * @param [in]  size    鎖定區域大小.
         * @param [in]  options 鎖定選項.
         * @returns 返回鎖定緩沖區區域首地址.
         * @sa  void *HardwareBuffer::lockImpl(size_t offset, size_t size,
         *      LockOptions options)
         */
        virtual void *lockImpl(size_t offset, size_t size,
            LockOptions options) override;

        /**
         * @fn  virtual TResult D3D11HardwareVertexBuffer::unlockImpl() override;
         * @brief   解鎖緩沖區的具體實現接口，實現基類接口
         * @returns 成功調用返回 T3D_OK.
         * @sa  TResult HardwareVertexBuffer::unlockImpl()
         */
        virtual TResult unlockImpl() override;

    protected:
        D3D11HardwareBufferPtr  mBufferImpl;    /**< D3D11 Buffer 具体实现 */
    };
}


#endif  /*__T3D_D3D11_HARDWARE_VERTEX_BUFFER_H__*/

