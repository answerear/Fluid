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


#ifndef __T3D_D3D11_HARDWARE_BUFFER_H__
#define __T3D_D3D11_HARDWARE_BUFFER_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    /**
     * @class   D3D11HardwareBuffer
     * @brief   DirectX 11 渲染器相關的緩沖類
     */
    class D3D11HardwareBuffer : public HardwareBuffer
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @enum    BufferType
         * @brief   缓冲区类型
         */
        enum class BufferType : uint32_t
        {
            VERTEX = 0,  /**< 顶点缓冲区 */
            INDEX,       /**< 索引缓冲区 */
            CONSTANT,    /**< 常量缓冲区 */
        };

        /**
         * @fn  static D3D11HardwareBufferPtr D3D11HardwareBuffer::create(
         *      BufferType type, size_t dataSize, const void *data, 
         *      Usage usage, uint32_t mode, bool streamOut);
         * @brief   創建 DirectX 11 渲染器相關的頂點緩沖對象
         * @param [in]  type        缓冲区类型.
         * @param [in]  dataSize    数据大小.
         * @param [in]  data        缓冲区初始化用的数据.
         * @param [in]  usage       緩沖區用法.
         * @param [in]  mode        緩沖區訪問方式.
         * @param [in]  streamOut   是否绑定到流输出阶段.
         * @returns 返回一個 DirectX 11 緩沖區對象.
         */
        static D3D11HardwareBufferPtr create(BufferType type, size_t dataSize, 
            const void *data, Usage usage, uint32_t mode, bool streamOut);

        /**
         * @fn  virtual D3D11HardwareVertexBuffer::~D3D11HardwareVertexBuffer();
         * @brief   析構函數
         */
        virtual ~D3D11HardwareBuffer();

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
         * @fn  virtual size_t D3D11HardwareBuffer::copyData(
         *      HardwareBufferPtr srcBuffer, size_t srcOffset, size_t dstOffset, 
         *      size_t size, bool discardWholeBuffer) override;
         * @brief   复制数据，实现基类接口
         * @param [in]  srcBuffer           源缓冲区对象.
         * @param [in]  srcOffset           源数据偏移.
         * @param [in]  dstOffset           目标数据偏移.
         * @param [in]  size                数据大小.
         * @param [in]  discardWholeBuffer  是否丟棄原有數據，默認不丟棄.
         * @returns 调用成功返回复制的字节数.
         * @sa  size_t HardwareBuffer::copyData(HardwareBufferPtr srcBuffer,
         *      size_t srcOffset, size_t dstOffset, size_t size,
         *      bool discardWholeBuffer = false)
         */
        virtual size_t copyData(HardwareBufferPtr srcBuffer, size_t srcOffset, 
            size_t dstOffset, size_t size, bool discardWholeBuffer) override;

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

        /**
         * @fn  ID3D11Buffer D3D11HardwareBuffer::*getD3DBuffer()
         * @brief   获取 ID3D11Buffer 对象
         * @returns 返回 ID3D11Buffer 对象.
         */
        ID3D11Buffer *getD3DBuffer() { return mD3DBuffer; }

    protected:
        /**
         * @fn  D3D11HardwareBuffer::D3D11HardwareBuffer(size_t bufSize, 
         *      Usage usage, uint32_t mode);
         * @brief   構造函數
         * @param [in]  usage   緩沖區用法.
         * @param [in]  mode    緩沖區訪問方式.
         */
        D3D11HardwareBuffer(Usage usage, uint32_t mode);

        /**
         * @fn  virtual TResult D3D11HardwareBuffer::init(BufferType type, 
         *      size_t dataSize, const void *data, bool streamOut);
         * @brief   初始化對象
         * @param [in]  type        缓冲区类型.
         * @param [in]  dataSize    数据大小.
         * @param [in]  data        缓冲区數據.
         * @param [in]  streamOut   是否绑定到流输出阶段.
         * @returns 調用成功返回 T3D_OK.
         */
        virtual TResult init(BufferType type, size_t dataSize, const void *data,
            bool streamOut);

        /**
         * @fn  TResult D3D11HardwareBuffer::check(LockOptions opt);
         * @brief   检查缓冲区使用方式、访问方式和锁定方式是否一致
         * @param [in]  options 锁定选项.
         * @returns 三者一致返回 T3D_OK.
         */
        TResult checkLockOptions(LockOptions options);

    protected:
        ID3D11Buffer            *mD3DBuffer;    /**< D3D11 緩沖區對象 */
        D3D11HardwareBufferPtr  mStageBuffer;   /**< 给 D3D11_USAGE_DEFAULT 更新用 */
        D3D11_USAGE             mD3DUsage;      /**< D3D11 缓冲区用法 */
    };
}


#endif  /*__T3D_D3D11_HARDWARE_BUFFER_H__*/

