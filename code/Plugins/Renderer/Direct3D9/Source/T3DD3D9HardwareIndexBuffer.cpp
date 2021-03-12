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


#include "T3DD3D9HardwareIndexBuffer.h"
#include "T3DD3D9Mappings.h"
#include "T3DD3D9Renderer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    D3D9HardwareIndexBufferPtr D3D9HardwareIndexBuffer::create(
        Type indexType, size_t indexCount, HardwareBuffer::Usage usage,
        bool useSystemMemory, bool useShadowBuffer)
    {
        D3D9HardwareIndexBufferPtr ibo = new D3D9HardwareIndexBuffer(indexType, 
            indexCount, usage, useSystemMemory, useShadowBuffer);
        ibo->release();

        if (ibo->init() != T3D_OK)
        {
            ibo = nullptr;
        }

        return ibo;
    }

    //--------------------------------------------------------------------------

    D3D9HardwareIndexBuffer::D3D9HardwareIndexBuffer(Type indexType,
        size_t indexCount, HardwareBuffer::Usage usage, bool useSystemMemory,
        bool useShadowBuffer)
        : HardwareIndexBuffer(indexType, indexCount, usage, useSystemMemory, 
            useShadowBuffer)
    {

    }

    //--------------------------------------------------------------------------

    D3D9HardwareIndexBuffer::~D3D9HardwareIndexBuffer()
    {
        D3D_SAFE_RELEASE(mD3DIndexBuffer);
    }

    //--------------------------------------------------------------------------

    TResult D3D9HardwareIndexBuffer::init()
    {
        TResult ret = T3D_OK;

        do 
        {
            LPDIRECT3DDEVICE9 pD3DDevice = D3D9_RENDERER.getD3DDevice();

            D3DPOOL d3dpool 
                = (mUseSystemMemory ? D3DPOOL_SYSTEMMEM : D3DPOOL_DEFAULT);
            HRESULT hr = pD3DDevice->CreateIndexBuffer(
                mBufferSize,
                D3D9Mappings::get(mUsage),
                D3D9Mappings::get(mType),
                d3dpool,
                &mD3DIndexBuffer,
                nullptr);
            if (FAILED(hr))
            {

            }
            else
            {
                hr = mD3DIndexBuffer->GetDesc(&mBufferDesc);
                if (FAILED(hr))
                {

                }
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    size_t D3D9HardwareIndexBuffer::readData(size_t offset, size_t size, 
        void *dst)
    {
        size_t bytesOfRead = 0;

        do 
        {
            void *src = lock(offset, size, HardwareBuffer::E_HBL_READ_ONLY);
            if (src == nullptr)
            {
                break;
            }

            memcpy(dst, src, size);
            bytesOfRead = size;

            unlock();
        } while (0);

        return bytesOfRead;
    }

    //--------------------------------------------------------------------------

    size_t D3D9HardwareIndexBuffer::writeData(size_t offset, size_t size,
        const void *src, bool discardWholeBuffer /* = false */)
    {
        size_t bytesOfWritten = 0;

        do 
        {
            void *dst = lock(offset, size, discardWholeBuffer 
                ? HardwareBuffer::E_HBL_DISCARD : HardwareBuffer::E_HBL_NORMAL);
            if (dst == nullptr)
            {
                break;
            }

            memcpy(dst, src, size);
            bytesOfWritten = size;

            unlock();
        } while (0);

        return bytesOfWritten;
    }

    //--------------------------------------------------------------------------

    void *D3D9HardwareIndexBuffer::lockImpl(size_t offset, size_t size,
        LockOptions options)
    {
        char *pLockedData = nullptr;

        do 
        {
            HRESULT hr = mD3DIndexBuffer->Lock(offset, size, 
                (void **)&pLockedData, D3D9Mappings::get(mUsage, options));
            if (FAILED(hr))
            {
                break;
            }
        } while (0);

        return pLockedData;
    }

    //--------------------------------------------------------------------------

    TResult D3D9HardwareIndexBuffer::unlockImpl()
    {
        TResult ret = T3D_OK;

        do 
        {
            HRESULT hr = mD3DIndexBuffer->Unlock();
            if (FAILED(hr))
            {

            }
        } while (0);

        return ret;
    }
}
