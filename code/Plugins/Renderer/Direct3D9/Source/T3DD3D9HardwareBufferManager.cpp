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


#include "T3DD3D9HardwareBufferManager.h"
#include "T3DD3D9HardwareVertexBuffer.h"
#include "T3DD3D9HardwareIndexBuffer.h"
#include "T3DD3D9HardwarePixelBuffer.h"
#include "T3DD3D9VertexDeclaration.h"
#include "T3DD3D9VertexArrayObject.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    D3D9HardwareBufferManagerPtr D3D9HardwareBufferManager::create()
    {
        D3D9HardwareBufferManagerPtr mgr = new D3D9HardwareBufferManager();
        mgr->release();
        return mgr;
    }

    //--------------------------------------------------------------------------

    D3D9HardwareBufferManager::D3D9HardwareBufferManager()
    {

    }

    //--------------------------------------------------------------------------

    D3D9HardwareBufferManager::~D3D9HardwareBufferManager()
    {

    }

    //--------------------------------------------------------------------------

    HardwareVertexBufferPtr D3D9HardwareBufferManager::createVertexBuffer(
        size_t vertexSize, size_t vertexCount, HardwareBuffer::Usage usage,
        bool useSystemMemory, bool useShadowBuffer)
    {
        return D3D9HardwareVertexBuffer::create(vertexSize, vertexCount, usage,
            useSystemMemory, useShadowBuffer);
    }

    //--------------------------------------------------------------------------

    HardwareIndexBufferPtr D3D9HardwareBufferManager::createIndexBuffer(
        HardwareIndexBuffer::Type indexType, size_t indexCount,
        HardwareBuffer::Usage usage, bool useSystemMemory, bool useShadowBuffer)
    {
        return D3D9HardwareIndexBuffer::create(indexType, indexCount, usage,
            useSystemMemory, useShadowBuffer);
    }

    //--------------------------------------------------------------------------

    HardwarePixelBufferPtr D3D9HardwareBufferManager::createPixelBuffer(
        size_t width, size_t height, PixelFormat format,
        HardwareBuffer::Usage usage, bool useSystemMemory, bool useShadowBuffer)
    {
        return D3D9HardwarePixelBuffer::create(width, height, format, usage,
            useSystemMemory, useShadowBuffer);
    }

    //--------------------------------------------------------------------------

    VertexArrayObjectPtr D3D9HardwareBufferManager::createVertexArrayObject(
        bool useIndices)
    {
        return D3D9VertexArrayObject::create(useIndices);
    }

    //--------------------------------------------------------------------------

    VertexDeclarationPtr D3D9HardwareBufferManager::createVertexDeclaration()
    {
        return D3D9VertexDeclaration::create();
    }
}

