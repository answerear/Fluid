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


#include "T3DD3D9HardwareVertexBuffer.h"
#include "T3DD3D9Renderer.h"
#include "T3DD3D9Mappings.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    D3D9HardwareVertexBufferPtr D3D9HardwareVertexBuffer::create(
        size_t vertexSize, size_t vertexCount, Usage usage,
        bool useSystemMemory, bool useShadowBuffer)
    {
        D3D9HardwareVertexBufferPtr vb = new D3D9HardwareVertexBuffer(
            vertexSize, vertexCount, usage, useSystemMemory, useShadowBuffer);
        vb->release();
        if (vb->init() != T3D_OK)
        {
            vb = nullptr;
        }
        return vb;
    }

    //--------------------------------------------------------------------------

    D3D9HardwareVertexBuffer::D3D9HardwareVertexBuffer(size_t vertexSize,
        size_t vertexCount, Usage usage, bool useSystemMemory,
        bool useShadowBuffer)
        : HardwareVertexBuffer(vertexSize, vertexCount, usage, useSystemMemory,
            useSystemMemory)
    {
    }

    //--------------------------------------------------------------------------

    D3D9HardwareVertexBuffer::~D3D9HardwareVertexBuffer()
    {
        D3D_SAFE_RELEASE(mD3DVertexBuffer);
    }

    //--------------------------------------------------------------------------

    TResult D3D9HardwareVertexBuffer::init()
    {
        TResult ret = T3D_OK;

        LPDIRECT3DDEVICE9 pD3DDevice = D3D9_RENDERER.getD3DDevice();

        D3DPOOL d3dpool 
            = (mUseSystemMemory ? D3DPOOL_SYSTEMMEM : D3DPOOL_DEFAULT);
        HRESULT hr = pD3DDevice->CreateVertexBuffer(
            mBufferSize,
            D3D9Mappings::get(mUsage),
            0,
            d3dpool,
            &mD3DVertexBuffer,
            nullptr);
        if (FAILED(hr))
        {

        }
        else
        {
            hr = mD3DVertexBuffer->GetDesc(&mBufferDesc);
            if (FAILED(hr))
            {

            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    size_t D3D9HardwareVertexBuffer::readData(size_t offset, size_t size,
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

    size_t D3D9HardwareVertexBuffer::writeData(size_t offset, size_t size,
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

    void *D3D9HardwareVertexBuffer::lockImpl(size_t offset, size_t size,
        LockOptions options)
    {
        char *pLockedData = nullptr;

        do 
        {
            if (mD3DVertexBuffer == nullptr)
            {
                break;
            }

            HRESULT hr = mD3DVertexBuffer->Lock(offset, size, 
                (void **)&pLockedData, D3D9Mappings::get(mUsage, options));
            if (FAILED(hr))
            {
                break;
            }
        } while (0);

        return pLockedData;
    }

    //--------------------------------------------------------------------------

    TResult D3D9HardwareVertexBuffer::unlockImpl()
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mD3DVertexBuffer == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                break;
            }

            HRESULT hr = mD3DVertexBuffer->Unlock();
            if (FAILED(hr))
            {

            }
        } while (0);

        return ret;
    }
}
