﻿/*******************************************************************************
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


#ifndef __T3D_R3D_HARDWARE_BUFFER_MANAGER_H__
#define __T3D_R3D_HARDWARE_BUFFER_MANAGER_H__


#include "T3DR3DPrerequisites.h"


namespace Tiny3D
{
    class R3DHardwareBufferManager : public HardwareBufferManagerBase
    {
    public:
        /**
         * @brief 创建 Reference3D 渲染器相关的硬件缓冲区管理对象
         */
        static R3DHardwareBufferManagerPtr create();

        /**
         * @brief 析构函数
         */
        virtual ~R3DHardwareBufferManager();

        /**
         * @brief 创建顶点缓冲区
         * @remarks 继承自 HardwareBufferManagerBase
         * @see HardwareBufferManagerBase::createVertexBuffer()
         */
        virtual HardwareVertexBufferPtr createVertexBuffer(size_t vertexSize,
            size_t vertexCount, const void *vertices, 
            HardwareBuffer::Usage usage, uint32_t mode) override;

        /**
         * @brief 创建索引缓冲区
         * @remarks 继承自 HardwareBufferManagerBase
         * @see HardwareBufferManagerBase::createIndexBuffer()
         */
        virtual HardwareIndexBufferPtr createIndexBuffer(
            HardwareIndexBuffer::Type indexType, size_t indexCount,
            const void *indices, HardwareBuffer::Usage usage,
            uint32_t mode) override;

        /**
         * @brief 创建像素缓冲区
         * @remarks 继承自 HardwareBufferManagerBase
         * @see HardwareBufferManagerBase::createPixelBuffer()
         */
        virtual HardwarePixelBufferPtr createPixelBuffer(size_t width,
            size_t height, PixelFormat format, const void *pixels, 
            HardwareBuffer::Usage usage, uint32_t mode) override;

        /**
         * @brief 创建常量缓冲区
         * @remarks 继承自 HardwareBufferManagerBase
         * @see HardwareBufferManagerBase::createConstantBuffer()
         */
        virtual HardwareConstantBufferPtr createConstantBuffer(
            size_t bufSize, const void *buffer, HardwareBuffer::Usage usage,
            uint32_t mode) override;

        /**
         * @brief 创建顶点数组对象
         * @remarks 继承自 HardwareBufferManagerBase
         * @see HardwareBufferManagerBase::createVertexArrayObject()
         */
        virtual VertexArrayObjectPtr createVertexArrayObject(
            bool useIndices) override;

        /**
         * @brief 创建顶点声明
         * @remarks 继承自 HardwareBufferManagerBase
         * @see HardwareBufferManagerBase::createVertexDeclaration()
         */
        virtual VertexDeclarationPtr createVertexDeclaration(
            ShaderPtr vertexShader) override;

    protected:
        /**
         * @brief 构造函数
         */
        R3DHardwareBufferManager();
    };
}


#endif  /*__T3D_R3D_HARDWARE_BUFFER_MANAGER_H__*/
