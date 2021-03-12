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


#include "T3DR3DHardwareBufferManager.h"
#include "T3DR3DHardwareVertexBuffer.h"
#include "T3DR3DHardwareIndexBuffer.h"
#include "T3DR3DHardwarePixelBuffer.h"
#include "T3DR3DHardwareConstantBuffer.h"
#include "T3DR3DVertexDeclaration.h"
#include "T3DR3DVertexArrayObject.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    R3DHardwareBufferManagerPtr R3DHardwareBufferManager::create()
    {
        R3DHardwareBufferManagerPtr mgr = new R3DHardwareBufferManager();
        mgr->release();
        return mgr;
    }

    //--------------------------------------------------------------------------

    R3DHardwareBufferManager::R3DHardwareBufferManager()
    {

    }

    //--------------------------------------------------------------------------

    R3DHardwareBufferManager::~R3DHardwareBufferManager()
    {

    }

    //--------------------------------------------------------------------------

    HardwareVertexBufferPtr R3DHardwareBufferManager::createVertexBuffer(
        size_t vertexSize, size_t vertexCount, const void *vertices, 
        HardwareBuffer::Usage usage, uint32_t mode)
    {
        return R3DHardwareVertexBuffer::create(vertexSize, vertexCount, 
            vertices, usage, mode);
    }

    //--------------------------------------------------------------------------

    HardwareIndexBufferPtr R3DHardwareBufferManager::createIndexBuffer(
        HardwareIndexBuffer::Type indexType, size_t indexCount, 
        const void *indices, HardwareBuffer::Usage usage, uint32_t mode)
    {
        return R3DHardwareIndexBuffer::create(indexType, indexCount, indices,
            usage, mode);
    }

    //--------------------------------------------------------------------------

    HardwarePixelBufferPtr R3DHardwareBufferManager::createPixelBuffer(
        size_t width, size_t height, PixelFormat format, const void *pixels,
        HardwareBuffer::Usage usage, uint32_t mode)
    {
        return R3DHardwarePixelBuffer::create(width, height, format, pixels, 
            usage, mode);
    }

    //--------------------------------------------------------------------------

    HardwareConstantBufferPtr R3DHardwareBufferManager::createConstantBuffer(
        size_t bufSize, const void *buffer, HardwareBuffer::Usage usage,
        uint32_t mode)
    {
        return R3DHardwareConstantBuffer::create(bufSize, buffer, usage, mode);
    }

    //--------------------------------------------------------------------------

    VertexArrayObjectPtr R3DHardwareBufferManager::createVertexArrayObject(
        bool useIndices)
    {
        return R3DVertexArrayObject::create(useIndices);
    }

    //--------------------------------------------------------------------------

    VertexDeclarationPtr R3DHardwareBufferManager::createVertexDeclaration(
        ShaderPtr vertexShader)
    {
        return R3DVertexDeclaration::create(vertexShader);
    }
}
