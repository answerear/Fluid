/***********************************************D3D11HardwareBuffer********************************
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


#include "T3DD3D11Buffer.h"
#include "T3DD3D11Context.h"
#include "T3DD3D11Mappings.h"
#include "T3DD3D11Error.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11Buffer, HardwareBuffer);

    //--------------------------------------------------------------------------

    D3D11BufferPtr D3D11Buffer::create(BufferType type, 
        size_t dataSize, const void *data, Usage usage, uint32_t mode, 
        bool streamOut)
    {
        D3D11BufferPtr buffer 
            = new D3D11Buffer(usage, mode);
        buffer->release();
        if (buffer->init(type, dataSize, data, streamOut) != T3D_OK)
        {
            buffer = nullptr;
        }
        return buffer;
    }

    //--------------------------------------------------------------------------

    D3D11Buffer::D3D11Buffer(Usage usage, 
        uint32_t mode)
        : HardwareBuffer(usage, mode)
        , mD3DBuffer(nullptr)
        , mStageBuffer(nullptr)
    {
    }

    //--------------------------------------------------------------------------

    D3D11Buffer::~D3D11Buffer()
    {
        D3D_SAFE_RELEASE(mD3DBuffer);
    }

    //--------------------------------------------------------------------------

    TResult D3D11Buffer::init(BufferType type, size_t dataSize, 
        const void *data, bool streamOut)
    {
        TResult ret = T3D_OK;

        do 
        {
            D3D11_USAGE d3dUsage;
            uint32_t d3dAccess = 0;

            ret = D3D11Mappings::get(mUsage, mAccessMode, d3dUsage, d3dAccess);
            if (T3D_FAILED(ret))
            {
                break;
            }

            // 初始化数据
            D3D11_SUBRESOURCE_DATA d3dData;
            memset(&d3dData, 0, sizeof(d3dData));

            if (data != nullptr)
            {
                d3dData.pSysMem = data;
            }

            uint32_t bindFlags = 0;

            if (d3dUsage != D3D11_USAGE_STAGING)
            {
                switch (type)
                {
                case BufferType::VERTEX:
                    bindFlags = D3D11_BIND_VERTEX_BUFFER;
                    break;
                case BufferType::INDEX:
                    bindFlags = D3D11_BIND_INDEX_BUFFER;
                    break;
                case BufferType::CONSTANT:
                    bindFlags = D3D11_BIND_CONSTANT_BUFFER;
                    break;
                default:
                    {
                        ret = T3D_ERR_INVALID_PARAM;
                        T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                            "Invalid buffer type for D3D11HardwareBuffer !");
                    }
                    break;
                }
            }

            if (T3D_FAILED(ret))
            {
                break;
            }

            if (streamOut)
                bindFlags |= D3D11_BIND_STREAM_OUTPUT;

            // 创建 ID3D11Buffer
            D3D11_BUFFER_DESC desc;
            memset(&desc, 0, sizeof(desc));
            desc.Usage = d3dUsage;
            desc.ByteWidth = (UINT)dataSize;
            desc.BindFlags = bindFlags;
            desc.CPUAccessFlags = d3dAccess;

            ID3D11Device *pD3DDevice = D3D11_CONTEXT.getD3DDevice();
            HRESULT hr = S_OK;
            hr = pD3DDevice->CreateBuffer(&desc, &d3dData, &mD3DBuffer);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_CREATE_BUFFER;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, 
                    "Create ID3DBuffer object failed ! DX ERROR [%d]", hr);
                break;
            }

            mD3DUsage = d3dUsage;

            if (mUsage == Usage::STATIC
                && mAccessMode == AccessMode::CPU_WRITE)
            {
                // 需要借助 stage 缓冲区更新 default 缓冲区
                mStageBuffer = D3D11Buffer::create(type, dataSize, data,
                    Usage::STREAM, AccessMode::GPU_COPY, streamOut);

                if (mStageBuffer == nullptr)
                {
                    // 出错了，没有创建出来 :(
                    ret = T3D_ERR_D3D11_CREATE_BUFFER;
                    T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                        "Create staging buffer for default updating failed !");
                    break;
                }
            }

            mBufferSize = dataSize;
        } while (0);
        return ret;
    }

    //--------------------------------------------------------------------------

    size_t D3D11Buffer::readData(size_t offset, size_t size,
        void *dst)
    {
        size_t bytesOfRead = 0;

        do 
        {
            // 锁定 GPU 缓冲区，准备读数据
            void *src = lock(offset, size, LockOptions::READ);
            if (src == nullptr)
            {
                // 出错了:(
                break;
            }

            // 读数据
            memcpy(dst, src, size);
            bytesOfRead = size;

            // 解锁，把访问权还给 GPU
            unlock();
        } while (0);

        return bytesOfRead;
    }

    //--------------------------------------------------------------------------

    size_t D3D11Buffer::writeData(size_t offset, size_t size,
        const void *src, bool discardWholeBuffer /* = false */)
    {
        size_t bytesOfWritten = 0;

        do 
        {
            // 锁定 GPU 缓冲区，准备写数据
            LockOptions lockOpt;
            if (discardWholeBuffer)
            {
                if (mD3DUsage != D3D11_USAGE_STAGING)
                    lockOpt = LockOptions::WRITE_DISCARD;
                else
                    lockOpt = LockOptions::WRITE;
            }
            else
            {
                lockOpt = LockOptions::WRITE_NO_OVERWRITE;
            }

            void *dst = lock(offset, size, lockOpt);
            if (dst == nullptr)
            {
                //  出错了:(
                break;
            }

            // 写数据
            memcpy(dst, src, size);
            bytesOfWritten = size;

            // 解锁，把访问权还给 GPU
            unlock();
        } while (0);

        return bytesOfWritten;
    }

    //--------------------------------------------------------------------------

    size_t D3D11Buffer::copyData(HardwareBufferPtr srcBuffer, 
        size_t srcOffset, size_t dstOffset, size_t size, 
        bool discardWholeBuffer)
    {
        size_t sizeOfCopied = 0;

        if (srcOffset == 0 && dstOffset == 0
            && size == mBufferSize && mBufferSize == srcBuffer->getBufferSize())
        {
            ID3D11DeviceContext *pContext = D3D11_CONTEXT.getD3DDeviceContext();
            D3D11BufferPtr src 
                = smart_pointer_cast<D3D11Buffer>(srcBuffer);
            pContext->CopyResource(mD3DBuffer, src->getD3DBuffer());
            sizeOfCopied = size;
        }
        else
        {
            D3D11_BOX srcBox;
            srcBox.left = (UINT)srcOffset;
            srcBox.right = (UINT)(srcOffset + size);
            srcBox.top = 0;
            srcBox.bottom = 0;
            srcBox.front = 0;
            srcBox.back = 1;

            ID3D11DeviceContext *pContext = D3D11_CONTEXT.getD3DDeviceContext();
            D3D11BufferPtr src
                = smart_pointer_cast<D3D11Buffer>(srcBuffer);
            pContext->CopySubresourceRegion(mD3DBuffer, 0, (UINT)dstOffset, 0, 0,
                src->getD3DBuffer(), 0, &srcBox);
            sizeOfCopied = size;
        }

        return sizeOfCopied;
    }

    //--------------------------------------------------------------------------

    void *D3D11Buffer::lockImpl(size_t offset, size_t size,
        LockOptions options)
    {
        uint8_t *pLockedData = nullptr;

        do 
        {
            TResult ret = checkLockOptions(options);
            if (T3D_FAILED(ret))
            {
                break;
            }

            ID3D11DeviceContext *pContext = D3D11_CONTEXT.getD3DDeviceContext();

            D3D11_MAP d3dMapType = D3D11Mappings::get(options);
            D3D11_MAPPED_SUBRESOURCE d3dMappedData;

            if (mStageBuffer != nullptr)
            {
                // 先操作 Stage Buffer ，解锁时再 copy 回去 Default
                if (options == LockOptions::WRITE_DISCARD)
                    options = LockOptions::WRITE;
                pLockedData = (uint8_t*)mStageBuffer->lock(offset, size, options);
            }
            else
            {
                HRESULT hr = S_OK;
                hr = pContext->Map(mD3DBuffer, 0, d3dMapType, 0, &d3dMappedData);
                if (FAILED(hr))
                {
                    T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                        "Mapped D3D11 buffer failed ! DX ERROR[%d]", hr);
                    break;
                }

                pLockedData = (uint8_t*)d3dMappedData.pData + offset;
            }
        } while (0);

        return pLockedData;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Buffer::unlockImpl()
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mStageBuffer != nullptr)
            {
                ret = mStageBuffer->unlock();
                if (T3D_FAILED(ret))
                {
                    break;
                }

                HardwareBuffer::copyData(mStageBuffer);
            }
            else
            {
                ID3D11DeviceContext *pContext 
                    = D3D11_CONTEXT.getD3DDeviceContext();
                pContext->Unmap(mD3DBuffer, 0);
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Buffer::checkLockOptions(LockOptions options)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mUsage == Usage::STATIC)
            {
                // 静态缓冲
                // 1. CPU 不读写
                // 2. CPU 只写
                if (mAccessMode == AccessMode::CPU_WRITE
                    && (options == LockOptions::WRITE
                        || options == LockOptions::WRITE_DISCARD
                        || options == LockOptions::WRITE_NO_OVERWRITE))
                {
                    // CPU 只写
                    break;
                }
                else
                {
                    ret = T3D_ERR_INVALID_PARAM;
                }
            }
            else if (mUsage == Usage::DYNAMIC || mUsage == Usage::STREAM)
            {
                // 动态缓冲
                // 1. CPU 不读写
                // 2. CPU 读写
                // 3. CPU 只写
                // 4. CPU 只读
                // 4. GPU之间传送数据
                if ((mAccessMode == (AccessMode::CPU_READ | AccessMode::CPU_WRITE))
                    || (mAccessMode == AccessMode::CPU_WRITE)
                    || (mAccessMode == AccessMode::CPU_READ)
                    || (mAccessMode == AccessMode::GPU_COPY))
                {
                    // CPU 读写
                    // CPU 只写
                    // CPU 只读
                    // GPU之间传送数据
                    break;
                }
                else
                {
                    ret = T3D_ERR_INVALID_PARAM;
                }
            }
            else
            {
                ret = T3D_ERR_INVALID_PARAM;
            }

            T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                "Usage [%d], AccessMode [%d] and LockOptions isn't "
                "correspondent with LockOptions [%d]!",
                mUsage, mAccessMode, options);
        } while (0);

        return ret;
    }
}
