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


#include "T3DR3DHardwareIndexBuffer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    R3DHardwareIndexBufferPtr R3DHardwareIndexBuffer::create(Type indexType,
        size_t indexCount, const void *indices, HardwareBuffer::Usage usage, 
        uint32_t mode)
    {
        R3DHardwareIndexBufferPtr ib = new R3DHardwareIndexBuffer(indexType,
            indexCount, indices, usage, mode);
        ib->release();
        return ib;
    }

    //--------------------------------------------------------------------------

    R3DHardwareIndexBuffer::R3DHardwareIndexBuffer(Type indexType,
        size_t indexCount, const void *indices, HardwareBuffer::Usage usage, 
        uint32_t mode)
        : HardwareIndexBuffer(indexType, indexCount, usage, mode)
        , mBuffer(nullptr)
    {
        mBuffer = new uint8_t[mBufferSize];
        memcpy(mBuffer, indices, mBufferSize);
    }

    //--------------------------------------------------------------------------

    R3DHardwareIndexBuffer::~R3DHardwareIndexBuffer()
    {
        T3D_SAFE_DELETE_ARRAY(mBuffer);
    }

    //--------------------------------------------------------------------------

    size_t R3DHardwareIndexBuffer::readData(size_t offset, size_t size,
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

    size_t R3DHardwareIndexBuffer::writeData(size_t offset, size_t size,
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

    void *R3DHardwareIndexBuffer::lockImpl(size_t offset, size_t size,
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

    TResult R3DHardwareIndexBuffer::unlockImpl()
    {
        return T3D_OK;
    }
}
