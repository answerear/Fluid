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


#ifndef __T3D_D3D11_HARDWARE_BUFFER_MANAGER_H__
#define __T3D_D3D11_HARDWARE_BUFFER_MANAGER_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    /**
     * @class   D3D11HardwareBufferManager
     * @brief   DirectX 11 GPU 缓冲区管理器.
     */
    class D3D11HardwareBufferManager : public HardwareBufferManagerBase
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static D3D11HardwareBufferManagerPtr 
         *      D3D11HardwareBufferManager::create();
         * @brief   创建 DirectX 11 渲染器相关的 GPU 缓冲区管理对象
         * @returns 返回一个 DirectX 11 渲染器相关 GPU 缓冲区管理对象.
         */
        static D3D11HardwareBufferManagerPtr create();

        /**
         * @fn  virtual 
         *      D3D11HardwareBufferManager::~D3D11HardwareBufferManager();
         * @brief   析构函数
         */
        virtual ~D3D11HardwareBufferManager();

        /**
         * @fn  virtual HardwareVertexBufferPtr 
         *      D3D11HardwareBufferManager::createVertexBuffer(
         *      size_t vertexSize, size_t vertexCount, const void *vertices, 
         *      HardwareBuffer::Usage usage, uint32_t mode) override;
         * @brief   创建顶点缓冲区
         * @param [in]  vertexSize  顶点字节大小.
         * @param [in]  vertexCount 顶点数量.
         * @param [in]  vertices    顶点数据，可以为nullptr.
         * @param [in]  usage       缓冲区用法.
         * @param [in]  mode        缓冲区访问方式.
         * @returns 调用成功返回一个新的硬件顶点缓冲区.
         * @remarks 继承自 HardwareBufferManagerBase.
         * @sa  HardwareVertexBufferPtr 
         *      HardwareBufferManagerBase::createVertexBuffer(size_t vertexSize,
         *      size_t vertexCount, const void *vertices, 
         *      HardwareBuffer::Usage usage, uint32_t mode)
         */
        virtual HardwareVertexBufferPtr createVertexBuffer(size_t vertexSize,
            size_t vertexCount, const void *vertices,
            HardwareBuffer::Usage usage, uint32_t mode) override;

        /**
         * @fn  virtual HardwareIndexBufferPtr 
         *      D3D11HardwareBufferManager::createIndexBuffer(
         *      HardwareIndexBuffer::Type indexType, size_t indexCount, 
         *      const void *indices, HardwareBuffer::Usage usage, 
         *      uint32_t mode) override;
         * @brief   创建索引缓冲区
         * @param [in]  indexType   索引类型.
         * @param [in]  indexCount  索引数量.
         * @param [in]  indices     索引数据，可以为nullptr.
         * @param [in]  usage       缓冲区使用方式.
         * @param [in]  mode        缓冲区访问方式.
         * @returns 调用成功返回一个新的硬件索引缓冲区.
         * @remarks 继承自 HardwareBufferManagerBase.
         * @sa  HardwareIndexBufferPtr 
         *      HardwareBufferManagerBase::createIndexBuffer(
         *      HardwareIndexBuffer::Type indexType, size_t indexCount,
         *      const void *indices, HardwareBuffer::Usage usage, uint32_t mode)
         */
        virtual HardwareIndexBufferPtr createIndexBuffer(
            HardwareIndexBuffer::Type indexType, size_t indexCount,
            const void *indices, HardwareBuffer::Usage usage,
            uint32_t mode) override;

        /**
         * @fn  virtual HardwarePixelBufferPtr 
         *      D3D11HardwareBufferManager::createPixelBuffer(size_t width, 
         *      size_t height, PixelFormat format, const void *pixels, 
         *      HardwareBuffer::Usage usage, uint32_t mode) override;
         * @brief   创建像素缓冲区
         * @param [in]  width   图像宽度.
         * @param [in]  height  图像高度.
         * @param [in]  format  像素格式.
         * @param [in]  pixels  像素数据，可以为nullptr.
         * @param [in]  usage   缓冲区使用方式.
         * @param [in]  mode    缓冲区访问方式.
         * @returns 调用成功返回一个新的硬件像素缓冲区.
         * @remarks 继承自 HardwareBufferManagerBase.
         * @sa  HardwarePixelBufferPtr 
         *      HardwareBufferManagerBase::createPixelBuffer(size_t width,
         *      size_t height, PixelFormat format, const void *pixels,
         *      HardwareBuffer::Usage usage, uint32_t mode)
         */
        virtual HardwarePixelBufferPtr createPixelBuffer(size_t width,
            size_t height, PixelFormat format, const void *pixels, 
            HardwareBuffer::Usage usage, uint32_t mode, size_t mipmaps) override;

        /**
         * @fn  virtual HardwareConstantBufferPtr 
         *      D3D11HardwareBufferManager::createConstantBuffer(
         *      size_t bufSize, const void *buffer, HardwareBuffer::Usage usage, 
         *      uint32_t mode) override;
         * @brief   创建常量缓冲区
         * @param [in]  bufSize 缓冲区大小.
         * @param [in]  buffer  缓冲区数据.
         * @param [in]  usage   缓冲区使用方式.
         * @param [in]  mode    缓冲区访问方式.
         * @returns 调用成功返回一个新的硬件常量缓冲区.
         * @remarks 继承自 HardwareBufferManagerBase.
         * @sa  HardwareConstantBufferPtr 
         *      HardwareBufferManagerBase::createConstantBuffer(size_t bufSize, 
         *      const void *buffer, HardwareBuffer::Usage usage, uint32_t mode)
         */
        virtual HardwareConstantBufferPtr createConstantBuffer(
            size_t bufSize, const void *buffer, HardwareBuffer::Usage usage,
            uint32_t mode) override;

        /**
         * @fn  virtual VertexArrayObjectPtr 
         *      D3D11HardwareBufferManager::createVertexArrayObject(
         *      bool useIndices) override;
         * @brief   创建顶点数组对象
         * @param [in]  useIndices  是否使用索引缓冲.
         * @returns 调用成功返回一个新的顶点数组对象.
         * @remarks  继承自 HardwareBufferManagerBase.
         * @sa  VertexArrayObjectPtr 
         *      HardwareBufferManagerBase::createVertexArrayObject(
         *      bool useIndices)
         */
        virtual VertexArrayObjectPtr createVertexArrayObject(
            bool useIndices) override;

        /**
         * @fn  virtual VertexDeclarationPtr 
         *      D3D11HardwareBufferManager::createVertexDeclaration() override;
         * @brief   创建顶点声明
         * @param [in]  vertexShader    顶点着色器.
         * @returns 返回一个渲染系统对应的顶点声明对象.
         * @remarks  继承自 HardwareBufferManagerBase.
         * @sa  VertexDeclarationPtr 
         *      HardwareBufferManagerBase::createVertexDeclaration()
         */
        virtual VertexDeclarationPtr createVertexDeclaration() override;

    protected:
        /**
         * @fn  D3D11HardwareBufferManager::D3D11HardwareBufferManager();
         * @brief   构造函数
         */
        D3D11HardwareBufferManager();
    };
}


#endif  /*__T3D_D3D11_HARDWARE_BUFFER_MANAGER_H__*/
