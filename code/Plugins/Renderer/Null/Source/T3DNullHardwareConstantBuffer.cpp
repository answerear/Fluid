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


#include "T3DD3D11HardwareConstantBuffer.h"
#include "T3DD3D11HardwareBuffer.h"
#include "T3DD3D11Mappings.h"
#include "T3DD3D11Renderer.h"
#include "T3DD3D11Error.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11HardwareConstantBuffer, HardwareConstantBuffer);

    //--------------------------------------------------------------------------

    D3D11HardwareConstantBufferPtr D3D11HardwareConstantBuffer::create(
        size_t bufSize, const void *buffer, Usage usage, uint32_t mode)
    {
        D3D11HardwareConstantBufferPtr ubo = new D3D11HardwareConstantBuffer(
            bufSize, usage, mode);
        ubo->release();

        if (ubo->init(buffer) != T3D_OK)
        {
            ubo = nullptr;
        }

        return ubo;
    }

    //--------------------------------------------------------------------------

    D3D11HardwareConstantBuffer::D3D11HardwareConstantBuffer(
        size_t bufSize, HardwareBuffer::Usage usage, uint32_t mode)
        : HardwareConstantBuffer(bufSize, usage, mode)
    {

    }

    //--------------------------------------------------------------------------

    D3D11HardwareConstantBuffer::~D3D11HardwareConstantBuffer()
    {
    }

    //--------------------------------------------------------------------------

    TResult D3D11HardwareConstantBuffer::init(const void *buffer)
    {
        TResult ret = T3D_OK;

        do 
        {
            mBufferImpl = D3D11HardwareBuffer::create(
                D3D11HardwareBuffer::BufferType::CONSTANT, mBufferSize, buffer,
                mUsage, mAccessMode, false);
            if (mBufferImpl == nullptr)
            {
                ret = T3D_ERR_D3D11_CREATE_BUFFER;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create constant buffer failed !");
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    size_t D3D11HardwareConstantBuffer::readData(size_t offset, size_t size, 
        void *dst)
    {
        if (mBufferImpl == nullptr)
            return 0;
        return mBufferImpl->readData(offset, size, dst);
    }

    //--------------------------------------------------------------------------

    size_t D3D11HardwareConstantBuffer::writeData(size_t offset, size_t size,
        const void *src, bool discardWholeBuffer /* = false */)
    {
        if (mBufferImpl == nullptr)
            return 0;
        return mBufferImpl->writeData(offset, size, src, discardWholeBuffer);
    }

    //--------------------------------------------------------------------------

    void *D3D11HardwareConstantBuffer::lockImpl(size_t offset, size_t size,
        LockOptions options)
    {
        return mBufferImpl->lockImpl(offset, size, options);
    }

    //--------------------------------------------------------------------------

    TResult D3D11HardwareConstantBuffer::unlockImpl()
    {
        return mBufferImpl->unlockImpl();
    }
}
