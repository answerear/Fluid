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


#ifndef __T3D_D3D11_VERTEX_ARRAY_OBJECT_H__
#define __T3D_D3D11_VERTEX_ARRAY_OBJECT_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    /**
     * @class   D3D11VertexArrayObject
     * @brief   Direct3D9 渲染器相关的VAO类
     */
    class D3D11VertexArrayObject : public VertexArrayObject
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static D3D11VertexArrayObjectPtr 
         *      D3D11VertexArrayObject::create(bool useIndices);
         * @brief   创建 Direct3D9 渲染器相关的 VAO 对象
         * @param   useIndices  True to use indices.
         * @return  A D3D11VertexArrayObjectPtr.
         */
        static D3D11VertexArrayObjectPtr create(bool useIndices);

        /**
         * @fn  virtual D3D11VertexArrayObject::~D3D11VertexArrayObject();
         * @brief   析构函数
         */
        virtual ~D3D11VertexArrayObject();

        /**
         * @fn  virtual TResult D3D11VertexArrayObject::beginBinding() override;
         * @brief   开始绑定VAO，实现基类接口
         * @return  A TResult.
         */
        virtual TResult beginBinding() override;

        /**
         * @fn  virtual TResult D3D11VertexArrayObject::endBinding() override;
         * @brief   结束绑定VAO，实现基类接口
         * @return  A TResult.
         */
        virtual TResult endBinding() override;

        /**
         * @fn  virtual TResult D3D11VertexArrayObject::setPrimitiveType(
         *      Renderer::PrimitiveType priType) override;
         * @brief   设置绘制图元类型，实现基类接口
         * @param   priType Type of the pri.
         * @return  A TResult.
         */
        virtual TResult setPrimitiveType(
            Renderer::PrimitiveType priType) override;

        /**
         * @fn  virtual Renderer::PrimitiveType 
         *      D3D11VertexArrayObject::getPrimitiveType() const override;
         * @brief   获取渲染图元类型，实现基类接口
         * @return  The primitive type.
         */
        virtual Renderer::PrimitiveType getPrimitiveType() const override;

        /**
         * @fn  virtual TResult D3D11VertexArrayObject::setVertexDeclaration(
         *      VertexDeclarationPtr decl) override;
         * @brief   设置顶点声明，实现基类接口
         * @param   decl    The declaration.
         * @return  A TResult.
         */
        virtual TResult setVertexDeclaration(VertexDeclarationPtr decl) override;

        /**
         * @fn  virtual VertexDeclarationPtr 
         *      D3D11VertexArrayObject::getVertexDeclaration() const override;
         * @brief   获取顶点声明，实现基类接口
         * @return  The vertex declaration.
         */
        virtual VertexDeclarationPtr getVertexDeclaration() const override;

        /**
         * @fn  virtual TResult D3D11VertexArrayObject::addVertexBuffer(
         *      HardwareVertexBufferPtr vbo) override;
         * @brief   添加顶点缓冲区对象，实现基类接口
         * @param   vbo The vbo.
         * @return  A TResult.
         */
        virtual TResult addVertexBuffer(HardwareVertexBufferPtr vbo) override;

        /**
         * @fn  virtual size_t 
         *      D3D11VertexArrayObject::getVertexBufferCount() const override;
         * @brief   获取顶点缓冲区对象数量，实现基类接口
         * @return  The vertex buffer count.
         */
        virtual size_t getVertexBufferCount() const override;

        /**
         * @fn  virtual HardwareVertexBufferPtr 
         *      D3D11VertexArrayObject::getVertexBuffer(size_t idx) const override;
         * @brief   获取顶点缓冲区对象，实现基类接口
         * @param   idx Zero-based index of the.
         * @return  The vertex buffer.
         */
        virtual HardwareVertexBufferPtr getVertexBuffer(size_t idx) const override;

        /**
         * @fn  virtual TResult D3D11VertexArrayObject::setIndexBuffer(
         *      HardwareIndexBufferPtr ibo) override;
         * @brief   设置索引缓冲对象，实现基类接口
         * @param   ibo The ibo.
         * @return  A TResult.
         */
        virtual TResult setIndexBuffer(HardwareIndexBufferPtr ibo) override;

        /**
         * @fn  virtual HardwareIndexBufferPtr 
         *      D3D11VertexArrayObject::getIndexBuffer() const override;
         * @brief   获取索引缓冲对象，实现基类接口
         * @return  The index buffer.
         */
        virtual HardwareIndexBufferPtr getIndexBuffer() const override;

        /**
         * @fn  virtual bool 
         *      D3D11VertexArrayObject::isIndicesUsed() const override;
         * @brief   获取是否使用索引缓冲区，实现基类接口
         * @return  True if indices used, false if not.
         */
        virtual bool isIndicesUsed() const override;

        /**
         * @fn  ID3D11Buffer * const D3D11VertexArrayObject::*getD3D11Buffers()
         * @brief   获取 ID3D11Buffer 对象数组
         * @return  返回 ID3D11Buffer 对象数组.
         */
        ID3D11Buffer * const *getD3D11Buffers() { return mD3D11Buffers; }

        /**
         * @fn  UINT D3D11VertexArrayObject::*getD3D11BufferStrides()
         * @brief   获取 ID3D11Buffer 每个缓冲区的顶点步长
         * @return  返回 ID3D11Buffer 每个缓冲区的顶点步长.
         */
        UINT *getD3D11BufferStrides() { return mD3D11BufferStrides; }

        /**
         * @fn  UINT D3D11VertexArrayObject::*getD3D11BufferOffsets()
         * @brief   获取 ID3D11Buffer 每个缓冲区的偏移
         * @return  返回 ID3D11Buffer 每个缓冲区的偏移.
         */
        UINT *getD3D11BufferOffsets() { return mD3D11BufferOffsets; }

        /**
         * @fn  size_t D3D11VertexArrayObject::getVertexCount() const;
         * @brief   获取顶点数量
         * @return  返回顶点数量.
         */
        size_t getVertexCount() const;

    protected:
        /**
         * @fn  D3D11VertexArrayObject::D3D11VertexArrayObject(bool useIndices);
         * @brief   构造函数
         * @param   useIndices  True to use indices.
         */
        D3D11VertexArrayObject(bool useIndices);

    protected:
        typedef TList<HardwareVertexBufferPtr>      VBOList;
        typedef VBOList::iterator                   VBOListItr;
        typedef VBOList::const_iterator             VBOListConstItr;

        Renderer::PrimitiveType mPrimitiveType; /**< 渲染图元 */

        VertexDeclarationPtr    mDecl;          /**< 顶点声明对象 */
        VBOList                 mVBOList;       /**< 顶点缓冲区对象集合 */
        HardwareIndexBufferPtr  mIBO;           /**< *索引缓冲区对象 */

        bool            mUseIndices;            /**< 是否使用索引缓冲 */

        ID3D11Buffer    **mD3D11Buffers;        /**< D3D11Buffer 数组 */
        UINT            *mD3D11BufferStrides;   /**< 每个缓冲区的顶点步长 */
        UINT            *mD3D11BufferOffsets;   /**< 每个缓冲区的偏移 */
    };
}


#endif  /*__T3D_D3D11_VERTEX_ARRAY_OBJECT_H__*/

