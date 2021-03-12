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


#ifndef __T3D_HARDWARE_BUFFER_MANAGER_BASE_H__
#define __T3D_HARDWARE_BUFFER_MANAGER_BASE_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Render/T3DHardwareVertexBuffer.h"
#include "Render/T3DHardwareIndexBuffer.h"
#include "Kernel/T3DCommon.h"


namespace Tiny3D
{
    /**
     * @class   HardwareBufferManagerBase
     * @brief   硬件缓冲区管理器基类
     */
    class T3D_ENGINE_API HardwareBufferManagerBase : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  virtual HardwareBufferManagerBase::~HardwareBufferManagerBase();
         * @brief   析构函数
         */
        virtual ~HardwareBufferManagerBase();

        /**
         * @fn  virtual HardwareVertexBufferPtr 
         *      HardwareBufferManagerBase::createVertexBuffer(size_t vertexSize, 
         *      size_t vertexCount, const void *vertices,
         *      HardwareBuffer::Usage usage, uint32_t mode) = 0;
         * @brief   创建顶点缓冲区
         * @param [in]  vertexSize  顶点字节大小.
         * @param [in]  vertexCount 顶点数量.
         * @param [in]  vertices    顶点数据，可以为nullptr.
         * @param [in]  usage       缓冲区用法.
         * @param [in]  mode        缓冲区访问方式.
         * @returns 调用成功返回一个新的硬件顶点缓冲区.
         * @remarks 具体子类实现该接口创建对应的具体顶点缓冲区实例.
         */
        virtual HardwareVertexBufferPtr createVertexBuffer(size_t vertexSize, 
            size_t vertexCount, const void *vertices,
            HardwareBuffer::Usage usage, uint32_t mode) = 0;

        /**
         * @fn  virtual HardwareIndexBufferPtr 
         *      HardwareBufferManagerBase::createIndexBuffer(
         *      HardwareIndexBuffer::Type indexType, size_t indexCount, 
         *      const void *indices, HardwareBuffer::Usage usage, 
         *      uint32_t mode) = 0;
         * @brief   创建索引缓冲区
         * @param [in]  indexType   索引类型.
         * @param [in]  indexCount  索引数量.
         * @param [in]  indices     索引数据，可以为nullptr.
         * @param [in]  usage       缓冲区使用方式.
         * @param [in]  mode        缓冲区访问方式.
         * @returns 调用成功返回一个新的硬件索引缓冲区.
         * @remarks 具体子类实现该接口创建对应的具体顶点缓冲区实例.
         */
        virtual HardwareIndexBufferPtr createIndexBuffer(
            HardwareIndexBuffer::Type indexType, size_t indexCount, 
            const void *indices, HardwareBuffer::Usage usage, 
            uint32_t mode) = 0;

        /**
         * @fn  virtual HardwarePixelBufferPtr 
         *      HardwareBufferManagerBase::createPixelBuffer(size_t width, 
         *      size_t height, PixelFormat format, const void *pixels, 
         *      HardwareBuffer::Usage usage, uint32_t mode) = 0;
         * @brief   创建像素缓冲区
         * @param [in]  width   图像宽度.
         * @param [in]  height  图像高度.
         * @param [in]  format  像素格式.
         * @param [in]  pixels  像素数据，可以为nullptr.
         * @param [in]  usage   缓冲区使用方式.
         * @param [in]  mode    缓冲区访问方式.
         * @returns 调用成功返回一个新的硬件像素缓冲区.
         * @remarks 具体子类实现该接口创建对应的具体顶点缓冲区实例.
         */
        virtual HardwarePixelBufferPtr createPixelBuffer(size_t width, 
            size_t height, PixelFormat format, const void *pixels,
            HardwareBuffer::Usage usage, uint32_t mode, size_t mipmaps) = 0;

        /**
         * @fn  virtual HardwareConstantBufferPtr 
         *      HardwareBufferManagerBase::createConstantBuffer(size_t bufSize, 
         *      const void *buffer, HardwareBuffer::Usage usage, 
         *      uint32_t mode) = 0;
         * @brief   创建常量缓冲区
         * @param [in]  bufSize 缓冲区大小.
         * @param [in]  buffer  缓冲区数据.
         * @param [in]  usage   缓冲区使用方式.
         * @param [in]  mode    缓冲区访问方式.
         * @returns 调用成功返回一个新的硬件常量缓冲区.
         * @remarks 具体子类实现该接口创建对应的具体常量缓冲区实例.
         */
        virtual HardwareConstantBufferPtr createConstantBuffer(
            size_t bufSize, const void *buffer, HardwareBuffer::Usage usage,
            uint32_t mode) = 0;

        /**
         * @fn  virtual VertexArrayObjectPtr 
         *      HardwareBufferManagerBase::createVertexArrayObject(
         *      bool useIndices) = 0;
         * @brief   创建顶点数组对象
         * @param [in]  useIndices  是否使用索引缓冲.
         * @returns 调用成功返回一个新的顶点数组对象.
         * @remarks 具体子类实现该接口创建对应的具体顶点缓冲区实例.
         */
        virtual VertexArrayObjectPtr createVertexArrayObject(
            bool useIndices) = 0;

        /**
         * @fn  virtual VertexDeclarationPtr 
         *      HardwareBufferManagerBase::createVertexDeclaration();
         * @brief   创建顶点声明对象
         * @param [in]  vertexShader    顶点着色器.
         * @returns 返回一个渲染系统对应的顶点声明对象.
         */
        virtual VertexDeclarationPtr createVertexDeclaration();

    protected:
        /**
         * @fn  HardwareBufferManagerBase::HardwareBufferManagerBase();
         * @brief   构造函数
         */
        HardwareBufferManagerBase();

    protected:
        typedef std::set<HardwareVertexBufferPtr>   VertexBufferList;
        typedef VertexBufferList::iterator          VertexBufferListItr;
        typedef VertexBufferList::const_iterator    VertexBufferListConstItr;

        typedef std::set<HardwareIndexBufferPtr>    IndexBufferList;
        typedef IndexBufferList::iterator           IndexBufferListItr;
        typedef IndexBufferList::const_iterator     IndexBufferListConstItr;

        typedef std::set<HardwarePixelBufferPtr>    PixelBufferList;
        typedef PixelBufferList::iterator           PixelBufferListItr;
        typedef PixelBufferList::const_iterator     PixelBufferListConstItr;

        typedef std::set<HardwareConstantBufferPtr> ConstBufferList;
        typedef ConstBufferList::iterator           ConstBufferListItr;
        typedef ConstBufferList::const_iterator     ConstBufferListConstItr;

        VertexBufferList    mVertexBuffers;     /**< 顶点缓冲区列表 */
        IndexBufferList     mIndexBuffers;      /**< 索引缓冲区列表 */
        PixelBufferList     mPixelBuffers;      /**< 像素缓冲区列表 */
        ConstBufferList     mConstBuffers;      /**< 常量缓冲区列表 */
    };
}


#endif  /*__T3D_HARDWARE_BUFFER_MANAGER_BASE_H__*/
