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


#include "Render/T3DHardwareBuffer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(HardwareBuffer, Object);

    //--------------------------------------------------------------------------

    HardwareBuffer::HardwareBuffer(Usage usage, uint32_t mode)
        : mBufferSize(0)
        , mLockSize(0)
        , mLockOffset(0)
        , mUsage(usage)
        , mAccessMode(mode)
        , mIsLocked(false)
    {

    }

    //--------------------------------------------------------------------------

    HardwareBuffer::~HardwareBuffer()
    {

    }

    //--------------------------------------------------------------------------

    void *HardwareBuffer::lock(size_t offset, size_t size, LockOptions options)
    {
        T3D_ASSERT(!isLocked());

        void *buffer = nullptr;

        do 
        {
            if (offset + size > mBufferSize)
            {
                // 越界了 :(
                break;
            }

            buffer = lockImpl(offset, size, options);
            if (buffer == nullptr)
            {
                break;
            }

            mIsLocked = true;
            mLockOffset = offset;
            mLockSize = size;
        } while (0);

        return buffer;
    }

    //--------------------------------------------------------------------------

    void *HardwareBuffer::lock(LockOptions options)
    {
        return lock(0, mBufferSize, options);
    }

    //--------------------------------------------------------------------------

    TResult HardwareBuffer::unlock()
    {
        T3D_ASSERT(isLocked());

        TResult ret = T3D_OK;

        do 
        {
            ret = unlockImpl();
            if (T3D_FAILED(ret))
            {
                break;
            }

            mIsLocked = false;
            mLockOffset = 0;
            mLockSize = 0;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    size_t HardwareBuffer::copyData(HardwareBufferPtr srcBuffer, 
        size_t srcOffset, size_t dstOffset, size_t size, 
        bool discardWholeBuffer /* = false */)
    {
        size_t len = 0;

        do 
        {
            if (srcBuffer == nullptr)
            {
                T3D_LOG_ERROR(LOG_TAG_RENDER,
                    "Copy data failed ! Source buffer is nullptr !");
                break;
            }

            const void *src = srcBuffer->lock(srcOffset, size,
                LockOptions::READ);
            if (src != nullptr)
            {
                len = writeData(dstOffset, size, src, discardWholeBuffer);
                srcBuffer->unlock();
            }
        } while (0);

        return len;
    }

    //--------------------------------------------------------------------------

    size_t HardwareBuffer::copyData(HardwareBufferPtr srcBuffer)
    {
        size_t size = std::min(getBufferSize(), srcBuffer->getBufferSize());
        return copyData(srcBuffer, 0, 0, size, true);
    }
}

