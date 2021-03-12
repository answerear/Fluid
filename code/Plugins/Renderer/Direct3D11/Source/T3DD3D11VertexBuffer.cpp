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


#include "T3DD3D11VertexBuffer.h"
#include "T3DD3D11Buffer.h"
#include "T3DD3D11Error.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11VertexBuffer, HardwareVertexBuffer);

    //--------------------------------------------------------------------------

    D3D11VertexBufferPtr D3D11VertexBuffer::create(
        size_t vertexSize, size_t vertexCount, const void *vertices, 
        Usage usage, uint32_t mode)
    {
        D3D11VertexBufferPtr vb = new D3D11VertexBuffer(
            vertexSize, vertexCount, usage, mode);
        vb->release();
        if (vb->init(vertices) != T3D_OK)
        {
            vb = nullptr;
        }
        return vb;
    }

    //--------------------------------------------------------------------------

    D3D11VertexBuffer::D3D11VertexBuffer(size_t vertexSize,
        size_t vertexCount, Usage usage, uint32_t mode)
        : HardwareVertexBuffer(vertexSize, vertexCount, usage, mode)
        , mBufferImpl(nullptr)
    {
    }

    //--------------------------------------------------------------------------

    D3D11VertexBuffer::~D3D11VertexBuffer()
    {
        mBufferImpl = nullptr;
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexBuffer::init(const void *vertices)
    {
        TResult ret = T3D_OK;

        do 
        {
            mBufferImpl = D3D11Buffer::create(
                D3D11Buffer::BufferType::VERTEX, mBufferSize, vertices,
                mUsage, mAccessMode, false);
            if (mBufferImpl == nullptr)
            {
                ret = T3D_ERR_D3D11_CREATE_BUFFER;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create vertex buffer failed !");
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    size_t D3D11VertexBuffer::readData(size_t offset, size_t size,
        void *dst)
    {
        if (mBufferImpl == nullptr)
            return 0;
        return mBufferImpl->readData(offset, size, dst);
    }

    //--------------------------------------------------------------------------

    size_t D3D11VertexBuffer::writeData(size_t offset, size_t size,
        const void *src, bool discardWholeBuffer /* = false */)
    {
        if (mBufferImpl == nullptr)
            return 0;
        return mBufferImpl->writeData(offset, size, src, discardWholeBuffer);
    }

    //--------------------------------------------------------------------------

    void *D3D11VertexBuffer::lockImpl(size_t offset, size_t size,
        LockOptions options)
    {
        return mBufferImpl->lockImpl(offset, size, options);
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexBuffer::unlockImpl()
    {
        return mBufferImpl->unlockImpl();
    }
}
