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


#ifndef __T3D_D3D9_VERTEX_DECLARATION_H__
#define __T3D_D3D9_VERTEX_DECLARATION_H__


#include "T3DD3D9Prerequisites.h"


namespace Tiny3D
{
    /**
     * @brief Direct3D9 渲染器相关的顶点声明类
     */
    class D3D9VertexDeclaration : public VertexDeclaration
    {
    public:
        /**
         * @brief 创建 Direct3D9 渲染器相关的顶点声明对象
         */
        static D3D9VertexDeclarationPtr create();

        /**
         * @brief 析构函数
         */
        virtual ~D3D9VertexDeclaration();

        /**
         * @brief 新增一个顶点属性
         * @param [in] stream : 数据流索引
         * @param [in] offset : 相对一个顶点数据开始位置的偏移
         * @param [in] type : 顶点数据类型
         * @param [in] semantic : 顶点语法解释
         * @return 返回一个新的顶点属性
         */
        virtual const VertexAttribute &addAttribute(size_t stream,
            size_t offset, VertexAttribute::Type type,
            VertexAttribute::Semantic semantic) override;

        /**
         * @brief 新增插入一个顶点属性
         * @param [in] pos : 插入位置
         * @param [in] stream : 数据流索引
         * @param [in] offset : 相对一个顶点数据开始位置的偏移
         * @param [in] type : 顶点数据类型
         * @param [in] semantic : 顶点语法解释
         * @return 返回一个新的顶点属性
         */
        virtual const VertexAttribute &insertAttribute(size_t pos,
            size_t stream, size_t offset, VertexAttribute::Type type,
            VertexAttribute::Semantic semantic) override;

        /**
         * @brief 添加一个顶点属性
         * @param [in] vertexAttribute : 顶点属性对象
         * @return 调用成功返回 T3D_OK
         */
        virtual TResult addAttribute(
            const VertexAttribute &vertexAttribute) override;

        /**
         * @brief 插入一个顶点属性
         * @param [in] pos : 插入的位置
         * @param [in] vertexAttribute : 顶点属性对象
         * @return 调用成功返回 T3D_OK
         */
        virtual TResult insertAttribute(size_t pos,
            const VertexAttribute &vertexAttribute) override;

        /**
         * @brief 移除指定位置的顶点属性
         * @param [in] pos : 数组位置
         * @return 调用成功返回 T3D_OK
         */
        virtual TResult removeAttribute(size_t pos) override;

        /**
         * @brief 移除对应语法解释的顶点属性
         * @param [in] semantic : 语法解释
         * @return 调用成功返回 T3D_OK
         */
        virtual TResult removeAttribute(
            VertexAttribute::Semantic semantic) override;

        /**
         * @brief 移除所有顶点属性
         * @return 调用成功返回 T3D_OK
         */
        virtual TResult removeAllAttributes() override;

        /**
         * @brief 更新顶点属性
         * @param [in] pos : 更新对应位置的顶点属性
         * @param [in] stream : 数据流索引
         * @param [in] type : 顶点数据类型
         * @param [in] semantic : 顶点语法解释
         * @return 调用成功返回 T3D_OK
         */
        virtual TResult updateAttribute(size_t pos, size_t stream,
            size_t offset, VertexAttribute::Type type,
            VertexAttribute::Semantic semantic) override;

        /**
         * @brief 克隆一个顶点声明对象
         * @return 返回一个新的顶点声明对象
         * @remarks 具体的渲染系统子类需要实现该接口
         */
        virtual VertexDeclarationPtr clone() const override;

        /**
         * @brief 获取 D3D9VertexDelaration9 对象
         */
        LPDIRECT3DVERTEXDECLARATION9 getD3D9VertexDeclaration();

    protected:
        /**
         * @brief 构造函数
         */
        D3D9VertexDeclaration();

    protected:
        LPDIRECT3DVERTEXDECLARATION9    mD3DVertexDecl;
        bool        mIsDirty;
    };
}


#endif  /*__T3D_D3D9_VERTEX_DECLARATION_H__*/
