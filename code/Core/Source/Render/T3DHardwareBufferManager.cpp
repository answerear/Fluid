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


#include "Render/T3DHardwareBufferManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(HardwareBufferManager);
    T3D_IMPLEMENT_CLASS_1(HardwareBufferManager, HardwareBufferManagerBase);

    //--------------------------------------------------------------------------

    HardwareBufferManagerPtr HardwareBufferManager::create(
        HardwareBufferManagerBase *impl)
    {
        HardwareBufferManagerPtr mgr = new HardwareBufferManager(impl);
        mgr->release();
        return mgr;
    }

    //--------------------------------------------------------------------------

    HardwareBufferManager::HardwareBufferManager(
        HardwareBufferManagerBase *impl)
        : mImpl(impl)
    {

    }

    //--------------------------------------------------------------------------

    HardwareBufferManager::~HardwareBufferManager()
    {
        mImpl = nullptr;
    }

    //--------------------------------------------------------------------------

    HardwareVertexBufferPtr HardwareBufferManager::createVertexBuffer(
        size_t vertexSize, size_t vertexCount, const void *vertices,
        HardwareBuffer::Usage usage, uint32_t mode)
    {
        return mImpl->createVertexBuffer(vertexSize, vertexCount, vertices, 
            usage, mode);
    }

    //--------------------------------------------------------------------------

    HardwareIndexBufferPtr HardwareBufferManager::createIndexBuffer(
        HardwareIndexBuffer::Type indexType, size_t indexCount, 
        const void *indices, HardwareBuffer::Usage usage, uint32_t mode)
    {
        return mImpl->createIndexBuffer(indexType, indexCount, indices, usage, 
            mode);
    }

    //--------------------------------------------------------------------------

    HardwarePixelBufferPtr HardwareBufferManager::createPixelBuffer(
        size_t width, size_t height, PixelFormat format, const void *pixels,
        HardwareBuffer::Usage usage, uint32_t mode, size_t mipmaps)
    {
        return mImpl->createPixelBuffer(width, height, format, pixels, usage, 
            mode, mipmaps);
    }

    //--------------------------------------------------------------------------

    HardwareConstantBufferPtr HardwareBufferManager::createConstantBuffer(
        size_t bufSize, const void *buffer, HardwareBuffer::Usage usage,
        uint32_t mode)
    {
        return mImpl->createConstantBuffer(bufSize, buffer, usage, mode);
    }

    //--------------------------------------------------------------------------

    VertexArrayObjectPtr HardwareBufferManager::createVertexArrayObject(
        bool useIndices)
    {
        return mImpl->createVertexArrayObject(useIndices);
    }

    //--------------------------------------------------------------------------

    VertexDeclarationPtr HardwareBufferManager::createVertexDeclaration()
    {
        return mImpl->createVertexDeclaration();
    }
}

