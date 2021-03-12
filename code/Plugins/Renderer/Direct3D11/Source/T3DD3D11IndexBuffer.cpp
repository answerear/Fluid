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


#include "T3DD3D11IndexBuffer.h"
#include "T3DD3D11Buffer.h"
#include "T3DD3D11Error.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11IndexBuffer, HardwareIndexBuffer);

    //--------------------------------------------------------------------------

    D3D11IndexBufferPtr D3D11IndexBuffer::create(
        Type indexType, size_t indexCount, const void *indices, 
        HardwareBuffer::Usage usage, uint32_t mode)
    {
        D3D11IndexBufferPtr ibo = new D3D11IndexBuffer(
            indexType, indexCount, usage, mode);
        ibo->release();

        if (ibo->init(indices) != T3D_OK)
        {
            ibo = nullptr;
        }

        return ibo;
    }

    //--------------------------------------------------------------------------

    D3D11IndexBuffer::D3D11IndexBuffer(Type indexType,
        size_t indexCount, HardwareBuffer::Usage usage, uint32_t mode)
        : HardwareIndexBuffer(indexType, indexCount, usage, mode)
    {

    }

    //--------------------------------------------------------------------------

    D3D11IndexBuffer::~D3D11IndexBuffer()
    {
    }

    //--------------------------------------------------------------------------

    TResult D3D11IndexBuffer::init(const void *indices)
    {
        TResult ret = T3D_OK;

        do 
        {
            mBufferImpl = D3D11Buffer::create(
                D3D11Buffer::BufferType::INDEX, mBufferSize, indices, 
                mUsage, mAccessMode,  false);
            if (mBufferImpl == nullptr)
            {
                ret = T3D_ERR_D3D11_CREATE_BUFFER;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create index buffer failed !");
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    size_t D3D11IndexBuffer::readData(size_t offset, size_t size, 
        void *dst)
    {
        if (mBufferImpl == nullptr)
            return 0;
        return mBufferImpl->readData(offset, size, dst);
    }

    //--------------------------------------------------------------------------

    size_t D3D11IndexBuffer::writeData(size_t offset, size_t size,
        const void *src, bool discardWholeBuffer /* = false */)
    {
        if (mBufferImpl == nullptr)
            return 0;
        return mBufferImpl->writeData(offset, size, src, discardWholeBuffer);
    }

    //--------------------------------------------------------------------------

    void *D3D11IndexBuffer::lockImpl(size_t offset, size_t size,
        LockOptions options)
    {
        return mBufferImpl->lockImpl(offset, size, options);
    }

    //--------------------------------------------------------------------------

    TResult D3D11IndexBuffer::unlockImpl()
    {
        return mBufferImpl->unlockImpl();
    }
}
