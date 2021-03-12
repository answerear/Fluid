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


#ifndef __T3D_VERTEX_ARRAY_OBJECT_H__
#define __T3D_VERTEX_ARRAY_OBJECT_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Kernel/T3DObject.h"
#include "Render/T3DRenderContext.h"


namespace Tiny3D
{
    /**
     * @brief VAO，用于存储渲染操作
     * @remarks 具体渲染系统子类去实现里面的接口
     */
    class T3D_ENGINE_API VertexArrayObject : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 构造函数
         */
        VertexArrayObject();

        /**
         * @brief 析构函数
         */
        virtual ~VertexArrayObject();

        /**
         * @brief 开始绑定VAO
         */
        virtual TResult beginBinding() = 0;

        /**
         * @brief 结束绑定VAO
         */
        virtual TResult endBinding() = 0;

        /**
         * @brief 设置绘制图元类型
         */
        virtual TResult setPrimitiveType(RenderContext::PrimitiveType priType) = 0;

        /**
         * @brief 获取渲染图元类型
         * @return 返回渲染图元类型
         */
        virtual RenderContext::PrimitiveType getPrimitiveType() const = 0;

        /**
         * @brief 设置顶点声明
         * @param [in] decl : 顶点声明对象
         * @return 调用成功返回 T3D_OK
         */
        virtual TResult setVertexDeclaration(VertexDeclarationPtr decl) = 0;

        /**
         * @brief 获取顶点声明
         * @return 返回顶点声明对象
         */
        virtual VertexDeclarationPtr getVertexDeclaration() const = 0;

        /**
         * @brief 添加顶点缓冲区对象
         * @param [in] vbo : 顶点缓冲对象
         * @return 调用成功返回 T3D_OK
         */
        virtual TResult addVertexBuffer(HardwareVertexBufferPtr vbo) = 0;

        /**
         * @brief 获取顶点缓冲区对象数量
         */
        virtual size_t getVertexBufferCount() const = 0;

        /**
         * @brief 获取顶点缓冲区对象
         * @return 返回VBO对象
         */
        virtual HardwareVertexBufferPtr getVertexBuffer(size_t idx) const = 0;

        /**
         * @brief 设置索引缓冲对象
         * @param [in] ibo : 索引缓冲对象
         * @return 调用成功返回 T3D_OK
         */
        virtual TResult setIndexBuffer(HardwareIndexBufferPtr ibo) = 0;

        /**
         * @brief 获取索引缓冲对象
         */
        virtual HardwareIndexBufferPtr getIndexBuffer() const = 0;

        /**
         * @brief 获取是否使用索引缓冲区
         * @return 返回true表示使用索引缓冲区
         * @remarks 如果返回 false 
         */
        virtual bool isIndicesUsed() const = 0;

        /**
         * @brief 获取图元数量
         */
        size_t getPrimitiveCount() const;

    protected:
        /**
         * @brief 计算图元数量
         */
        size_t calcPrimitiveCount() const;

        /**
         * @brief 设置是否需要重新计算图元数量
         */
        void setDirty(bool dirty) { mIsDirty = dirty; }

        /**
         * @brief 获取图元数量是否需要重新计算
         */
        bool isDirty() const { return mIsDirty; }

    private:
        mutable size_t  mPrimitiveCount;    /**< 图元数量 */
        mutable bool    mIsDirty;           /**< 是否需要重新计算图元数量 */
    };
}


#endif  /*__T3D_VERTEX_ARRAY_OBJECT_H__*/
