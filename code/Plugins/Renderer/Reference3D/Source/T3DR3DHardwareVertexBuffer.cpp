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


#include "T3DR3DHardwareVertexBuffer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    R3DHardwareVertexBufferPtr R3DHardwareVertexBuffer::create(
        size_t vertexSize, size_t vertexCount, const void *vertices, 
        Usage usage, uint32_t mode)
    {
        R3DHardwareVertexBufferPtr vb = new R3DHardwareVertexBuffer(vertexSize,
            vertexCount, vertices, usage, mode);
        vb->release();
        return vb;
    }

    //--------------------------------------------------------------------------

    R3DHardwareVertexBuffer::R3DHardwareVertexBuffer(size_t vertexSize, 
        size_t vertexCount, const void *vertices, Usage usage, uint32_t mode)
        : HardwareVertexBuffer(vertexSize, vertexCount, usage, mode)
        , mBuffer(nullptr)
    {
        mBuffer = new uint8_t[mBufferSize];
        memcpy(mBuffer, vertices, mBufferSize);
    }

    //--------------------------------------------------------------------------

    R3DHardwareVertexBuffer::~R3DHardwareVertexBuffer()
    {
        T3D_SAFE_DELETE_ARRAY(mBuffer);
    }

    //--------------------------------------------------------------------------

    size_t R3DHardwareVertexBuffer::readData(size_t offset, size_t size,
        void *dst)
    {
        if (mUsage == Usage::STATIC)
        {
            // 只写缓冲区，无法读取
            return 0;
        }

        // 实际读取的字节数不能超过缓冲区大小
        size_t bytesOfRead = offset + size;

        if (bytesOfRead > mBufferSize)
        {
            bytesOfRead = mBufferSize - offset;
        }

        // 复制数据
        memcpy(((uint8_t*)dst) + offset, mBuffer, bytesOfRead);

        return bytesOfRead;
    }

    //--------------------------------------------------------------------------

    size_t R3DHardwareVertexBuffer::writeData(size_t offset, size_t size,
        const void *src, bool discardWholeBuffer /* = false */)
    {
        // 实际写入的字节数不能超过缓冲区大小
        size_t bytesOfWritten = offset + size;

        if (bytesOfWritten > mBufferSize)
        {
            bytesOfWritten = mBufferSize - offset;
        }

        // 复制数据，忽略discardWholeBuffer参数
        memcpy(mBuffer + offset, src, bytesOfWritten);

        return bytesOfWritten;
    }

    //--------------------------------------------------------------------------

    void *R3DHardwareVertexBuffer::lockImpl(size_t offset, size_t size,
        LockOptions options)
    {
        size_t bytesOfLocked = offset + size;
        if (bytesOfLocked > mBufferSize)
        {
            // 超过缓冲区大小了，直接返回空
            return nullptr;
        }

        return (mBuffer + offset);
    }

    //--------------------------------------------------------------------------

    TResult R3DHardwareVertexBuffer::unlockImpl()
    {
        return T3D_OK;
    }
}
