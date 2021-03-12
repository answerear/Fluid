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


#ifndef __T3D_D3D9_MAPPINGS_H__
#define __T3D_D3D9_MAPPINGS_H__


#include "T3DD3D9Prerequisites.h"


namespace Tiny3D
{
    /**
     * @brief Tiny3D 和 Direct3D9 之间常量的映射转换
     */
    class D3D9Mappings
    {
    public:
        /**
         * @brief 把Tiny3D的图元类型转换成D3D9的图元类型
         */
        static D3DPRIMITIVETYPE get(Renderer::PrimitiveType primitive);

        /**
         * @brief 把Tiny3D的硬件缓冲使用方式常量转换成D3D9硬件缓冲使用方式常量
         */
        static DWORD get(HardwareBuffer::Usage usage);

        /**
         * @brief 根据Tiny3D的硬件缓冲使用方式常量和缓冲锁定选项获取D3D9对应的
         *      使用方式常量
         */
        static DWORD get(HardwareBuffer::Usage usage,
            HardwareBuffer::LockOptions options);

        /**
         * @brief 把Tiny3D索引缓冲区类型转换成D3D9索引格式
         */
        static D3DFORMAT get(HardwareIndexBuffer::Type type);

        /**
         * @brief 把Tiny3D顶点属性类型转换成D3D9声明类型
         */
        static D3DDECLTYPE get(VertexAttribute::Type type);

        /**
         * @brief 把Tiny3D的顶点语法转换成D3D9顶点声明语法类型
         */
        static D3DDECLUSAGE get(VertexAttribute::Semantic semantic);

        /**
         * @brief 把Tiny3D的像素格式转换成D3D9像素格式
         */
        static D3DFORMAT get(PixelFormat format);

        /**
         * @brief 把D3D9像素格式转换成Tiny3D像素格式
         */
        static PixelFormat get(D3DFORMAT d3dfmt);

        /**
         * @brief 把Tiny3D颜色格式转换成D3D9颜色格式
         */
        static D3DCOLORVALUE get(const ColorARGB &color);

        /**
         * @brief 转换成D3D矩阵
         */
        static D3DMATRIX toD3DMatrix(const Matrix4 &mat);

        /**
         * @brief 转换成T3D矩阵
         */
        static Matrix4 toT3DMatrix(const D3DMATRIX &mat);
    };
}


#endif  /*__T3D_D3D9_MAPPINGS_H__*/