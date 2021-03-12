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


#ifndef __T3D_D3D11_VERTEX_DECLARATION_H__
#define __T3D_D3D11_VERTEX_DECLARATION_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    /**
     * @class   D3D11VertexDeclaration
     * @brief   DirectX 11 渲染器相关的顶点声明类
     */
    class D3D11VertexDeclaration : public VertexDeclaration
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static D3D11VertexDeclarationPtr D3D11VertexDeclaration::create();
         * @brief   创建 DirectX 11 渲染器相关的顶点声明对象
         * @return  A D3D11VertexDeclarationPtr.
         */
        static D3D11VertexDeclarationPtr create();

        /**
         * @fn  virtual D3D11VertexDeclaration::~D3D11VertexDeclaration();
         * @brief   析构函数
         */
        virtual ~D3D11VertexDeclaration();

        /**
         * @fn  virtual const VertexAttribute 
         *      D3D11VertexDeclaration::&addAttribute(size_t stream, 
         *      size_t offset, VertexAttribute::Type type, 
         *      VertexAttribute::Semantic semantic, 
         *      size_t semanticIndex) override;
         * @brief   重写 VertexDeclaration::addAttribute() 接口
         * @param   stream          The stream.
         * @param   offset          The offset.
         * @param   type            The type.
         * @param   semantic        The semantic.
         * @param   semanticIndex   Zero-based index of the semantic.
         * @return  A reference to a const VertexAttribute.
         */
        virtual const VertexAttribute &addAttribute(size_t stream,
            size_t offset, VertexAttribute::Type type,
            VertexAttribute::Semantic semantic, size_t semanticIndex) override;

        /**
         * @fn  virtual const VertexAttribute 
         *      D3D11VertexDeclaration::&insertAttribute(size_t pos, 
         *      size_t stream, size_t offset, VertexAttribute::Type type, 
         *      VertexAttribute::Semantic semantic, 
         *      size_t semanticIndex) override;
         * @brief   重写 VertexDeclaration::insertAttribute() 接口
         * @param   pos             The position.
         * @param   stream          The stream.
         * @param   offset          The offset.
         * @param   type            The type.
         * @param   semantic        The semantic.
         * @param   semanticIndex   Zero-based index of the semantic.
         * @return  A reference to a const VertexAttribute.
         */
        virtual const VertexAttribute &insertAttribute(size_t pos,
            size_t stream, size_t offset, VertexAttribute::Type type,
            VertexAttribute::Semantic semantic, size_t semanticIndex) override;

        /**
         * @fn  virtual TResult D3D11VertexDeclaration::addAttribute(
         *      const VertexAttribute &vertexAttribute) override;
         * @brief   添加一个顶点属性
         * @param [in]  vertexAttribute : 顶点属性对象.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult addAttribute(
            const VertexAttribute &vertexAttribute) override;

        /**
         * @fn  virtual TResult D3D11VertexDeclaration::insertAttribute(
         *      size_t pos, const VertexAttribute &vertexAttribute) override;
         * @brief   插入一个顶点属性
         * @param [in]  pos             : 插入的位置.
         * @param [in]  vertexAttribute : 顶点属性对象.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult insertAttribute(size_t pos,
            const VertexAttribute &vertexAttribute) override;

        /**
         * @fn  virtual TResult 
         *      D3D11VertexDeclaration::removeAttribute(size_t pos) override;
         * @brief   移除指定位置的顶点属性
         * @param [in]  pos : 数组位置.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult removeAttribute(size_t pos) override;

        /**
         * @fn  virtual TResult D3D11VertexDeclaration::removeAttribute(
         *      VertexAttribute::Semantic semantic, 
         *      size_t semanticIndex) override;
         * @brief   移除对应语法解释的顶点属性
         * @param [in]  semantic        : 语法解释.
         * @param       semanticIndex   Zero-based index of the semantic.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult removeAttribute(
            VertexAttribute::Semantic semantic, size_t semanticIndex) override;

        /**
         * @fn  virtual TResult 
         *      D3D11VertexDeclaration::removeAllAttributes() override;
         * @brief   移除所有顶点属性
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult removeAllAttributes() override;

        /**
         * @fn  virtual TResult D3D11VertexDeclaration::updateAttribute(
         *      size_t pos, size_t stream, size_t offset, 
         *      VertexAttribute::Type type, VertexAttribute::Semantic semantic, 
         *      size_t semanticIndex) override;
         * @brief   更新顶点属性
         * @param [in]  pos             : 更新对应位置的顶点属性.
         * @param [in]  stream          : 数据流索引.
         * @param       offset          The offset.
         * @param [in]  type            : 顶点数据类型.
         * @param [in]  semantic        : 顶点语法解释.
         * @param       semanticIndex   Zero-based index of the semantic.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult updateAttribute(size_t pos, size_t stream,
            size_t offset, VertexAttribute::Type type,
            VertexAttribute::Semantic semantic, size_t semanticIndex) override;

        /**
         * @fn  virtual VertexDeclarationPtr 
         *      D3D11VertexDeclaration::clone() const override;
         * @brief   克隆一个顶点声明对象
         * @return  返回一个新的顶点声明对象.
         * @remarks  具体的渲染系统子类需要实现该接口.
         */
        virtual VertexDeclarationPtr clone() const override;

        /**
         * @fn  ID3D11InputLayout D3D11VertexDeclaration::*getD3DInputLayout(
         *      D3D11VertexShaderPtr shader);
         * @brief   获取 D3D11 顶点输入布局对象
         * @param   shader  The shader.
         * @return  Null if it fails, else the d 3D input layout.
         */
        ID3D11InputLayout *getD3DInputLayout(D3D11VertexShaderPtr shader);

    protected:
        /**
         * @fn  D3D11VertexDeclaration::D3D11VertexDeclaration();
         * @brief   构造函数
         */
        D3D11VertexDeclaration();

    protected:
        ID3D11InputLayout   *mD3DInputLayout;   /**< D3D11 输入布局 */
        bool                mIsDirty;           /**< True if is dirty, false if not */
    };
}


#endif  /*__T3D_D3D11_VERTEX_DECLARATION_H__*/
