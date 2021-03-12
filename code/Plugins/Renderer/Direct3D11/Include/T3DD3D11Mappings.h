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


#ifndef __T3D_D3D11_MAPPINGS_H__
#define __T3D_D3D11_MAPPINGS_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    /**
     * @class   D3D11Mappings
     * @brief   Tiny3D 和 DirectX 11 之间常量的映射转换
     */
    class D3D11Mappings
    {
    public:
        static const char * const POSITION;     /**< The position */
        static const char * const BLENDWEIGHT;  /**< The blendweight */
        static const char * const BLENDINDICES; /**< The blendindices */
        static const char * const NORMAL;       /**< The normal */
        static const char * const COLOR;        /**< The color */
        static const char * const TEXCOORD;     /**< The texcoord */
        static const char * const TANGENT;      /**< The tangent */
        static const char * const BINORMAL;     /**< The binormal */

        /**
         * @fn  static D3D11_FILL_MODE D3D11Mappings::get(PolygonMode mode);
         * @brief   把 Tiny3D 的多边形渲染模式转换成 D3D11 的多边形渲染模式
         * @param [in]  mode    Tiny3D 多边形渲染模式.
         * @returns 返回 D3D11 定义的多边形渲染模式.
         */
        static D3D11_FILL_MODE get(PolygonMode mode);

        /**
         * @fn  static D3D11_CULL_MODE D3D11Mappings::get(CullingMode mode);
         * @brief   把 Tiny3D 的面剔除模式转换成 D3D11 面剔除模式
         * @param [in]  mode    Tiny3D 面剔除模式.
         * @returns 返回 D3D11 定义的面剔除模式.
         */
        static D3D11_CULL_MODE get(CullingMode mode);

        /**
         * @fn  static const char D3D11Mappings::*get(
         *      VertexAttribute::Semantic semantic);
         * @brief   把 Tiny3D 的语义定义转换成 D3D11 的语义名称
         * @param [in]  semantic    Tiny3D 语义.
         * @returns 调用成功返回 D3D11 对应的语义名称.
         * @sa  enum class VertexAttribute::Semantic
         */
        static const char *get(VertexAttribute::Semantic semantic);

        /**
         * @fn  static DXGI_FORMAT D3D11Mappings::get(
         *      VertexAttribute::Type type);
         * @brief   把 Tiny3D 的顶点数据类型转换成 D3D11 的顶点数据类型
         * @param [in]  type    Tiny3D 顶点数据类型.
         * @returns 调用成功返回 D3D11 对应的顶点数据类型.
         * @sa  enum class VertexAttribute::Type
         */
        static DXGI_FORMAT get(VertexAttribute::Type type);

        /**
         * @fn  static D3D11_PRIMITIVE_TOPOLOGY D3D11Mappings::get(
         *      Renderer::PrimitiveType primitive);
         * @brief   把 Tiny3D 的渲染图元类型转换成 D3D11 的图元类型
         * @param [in]  primitive   Tiny3D 的渲染图元类型.
         * @returns 返回 D3D11 渲染图元类型.
         */
        static D3D11_PRIMITIVE_TOPOLOGY get(RenderContext::PrimitiveType primitive);

        /**
         * @fn  static DXGI_FORMAT D3D11Mappings::get(
         *      HardwareIndexBuffer::Type idxType);
         * @brief   把 Tiny3D 的索引类型转换成 D3D11 的索引类型
         * @param [in]  idxType Tiny3d 的索引类型.
         * @returns 返回 D3D11 索引类型.
         */
        static DXGI_FORMAT get(HardwareIndexBuffer::Type idxType);

        /**
         * @fn  static TResult D3D11Mappings::get(HardwareBuffer::Usage usage, 
         *      uint32_t mode, D3D11_USAGE &d3dUsage, uint32_t &d3dAccessFlag);
         * @brief   把 Tiny3D 的缓冲区用法和CPU访问权限转换成 D3D11 对应的值
         * @param [in]      usage           Tiny3D 的用法.
         * @param [in]      mode            Tiny3D 的访问方式.
         * @param [in, out] d3dUsage        返回的 D3D11 的用法.
         * @param [in, out] d3dAccessFlag   返回的 D3D11 的访问方式.
         * @returns 调用成功返回 T3D_OK.
         */
        static TResult get(HardwareBuffer::Usage usage, uint32_t mode,
            D3D11_USAGE &d3dUsage, uint32_t &d3dAccessFlag);
        /**
         * @fn  static D3D11_MAP D3D11Mappings::get(
         *      HardwareBuffer::LockOptions options);
         * @brief   把 Tiny3D 映射缓冲区标签转换成 D3D11 对应的值
         * @param [in]  options Tiny3D 锁定标签.
         * @returns 返回 D3D11 对应的映射标签.
         */
        static D3D11_MAP get(HardwareBuffer::LockOptions options);

        /**
         * @brief   把 Tiny3D 纹理格式转换成 D3D11 对应的值
         * @param [in]  format  Tiny3D 纹理格式.
         * @returns 返回 D3D11 对应的纹理格式.
         */
        static DXGI_FORMAT get(PixelFormat format);

        /**
         * @brief   把 Tiny3D 的过滤方式转换成 D3D11 对应的值
         * @param [in]  minFilter   Tiny3D 纹理缩小过滤方式.
         * @param [in]  magFilter   Tiny3D 纹理放大过滤方式.
         * @param [in]  mipFilter   Tiny3D 纹理 mipmaps 过滤方式.
         * @returns 返回 D3D11 对应的纹理过滤方式.
         */
        static D3D11_FILTER get(FilterOptions min, FilterOptions mag,
            FilterOptions mip, bool comparison = false);

        /**
         * @brief   把 Tiny3D 的纹理寻址方式转换成 D3D11 对应的值
         * @param [in]  mode    Tiny3D 纹理寻址方式
         * @returns 返回 D3D11 对应的纹理寻址方式.
         */
        static D3D11_TEXTURE_ADDRESS_MODE get(TextureAddressMode mode);

        /**
         * @brief   把 Tiny3D 的比较函数转换成 D3D11 比较函数
         * @param [in] func     Tiny3D 比较函数
         * @returns 返回 D3D11 对应的比较函数值
         */
        static D3D11_COMPARISON_FUNC get(CompareFunction func);
    };
}


#endif  /*__T3D_D3D11_MAPPINGS_H__*/