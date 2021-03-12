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


#include "T3DD3D11HardwareBufferManager.h"
#include "T3DD3D11HardwareVertexBuffer.h"
#include "T3DD3D11HardwareIndexBuffer.h"
#include "T3DD3D11HardwarePixelBuffer.h"
#include "T3DD3D11HardwareConstantBuffer.h"
#include "T3DD3D11VertexDeclaration.h"
#include "T3DD3D11VertexArrayObject.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11HardwareBufferManager, HardwareBufferManagerBase);

    //--------------------------------------------------------------------------

    D3D11HardwareBufferManagerPtr D3D11HardwareBufferManager::create()
    {
        D3D11HardwareBufferManagerPtr mgr = new D3D11HardwareBufferManager();
        mgr->release();
        return mgr;
    }

    //--------------------------------------------------------------------------

    D3D11HardwareBufferManager::D3D11HardwareBufferManager()
    {

    }

    //--------------------------------------------------------------------------

    D3D11HardwareBufferManager::~D3D11HardwareBufferManager()
    {

    }

    //--------------------------------------------------------------------------

    HardwareVertexBufferPtr D3D11HardwareBufferManager::createVertexBuffer(
        size_t vertexSize, size_t vertexCount, const void *vertices,
        HardwareBuffer::Usage usage, uint32_t mode)
    {
        return D3D11HardwareVertexBuffer::create(vertexSize, vertexCount, 
            vertices, usage, mode);
    }

    //--------------------------------------------------------------------------

    HardwareIndexBufferPtr D3D11HardwareBufferManager::createIndexBuffer(
        HardwareIndexBuffer::Type indexType, size_t indexCount, 
        const void *indices, HardwareBuffer::Usage usage, uint32_t mode)
    {
        return D3D11HardwareIndexBuffer::create(indexType, indexCount, indices,
            usage, mode);
    }

    //--------------------------------------------------------------------------

    HardwarePixelBufferPtr D3D11HardwareBufferManager::createPixelBuffer(
        size_t width, size_t height, PixelFormat format, const void *pixels,
        HardwareBuffer::Usage usage, uint32_t mode, size_t mipmaps)
    {
        return D3D11HardwarePixelBuffer::create(width, height, format, pixels, 
            usage, mode, mipmaps);
    }

    //--------------------------------------------------------------------------

    HardwareConstantBufferPtr D3D11HardwareBufferManager::createConstantBuffer(
        size_t bufSize, const void *buffer,
        HardwareBuffer::Usage usage, uint32_t mode)
    {
        return D3D11HardwareConstantBuffer::create(bufSize, buffer, usage,
            mode);
    }

    //--------------------------------------------------------------------------

    VertexArrayObjectPtr D3D11HardwareBufferManager::createVertexArrayObject(
        bool useIndices)
    {
        return D3D11VertexArrayObject::create(useIndices);
    }

    //--------------------------------------------------------------------------

    VertexDeclarationPtr D3D11HardwareBufferManager::createVertexDeclaration()
    {
        return D3D11VertexDeclaration::create();
    }
}

