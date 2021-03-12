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


#ifndef __T3D_D3D11_ERROR_H__
#define __T3D_D3D11_ERROR_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    enum R3DErrorCode : int32_t
    {
        T3D_ERR_D3D11_WINDOW_ALREADY = T3D_ERR_RENDERER, /**< 窗口已经创建 */
        T3D_ERR_D3D11_UNSUPPORT_FORMAT_ICON,             /**< 不支持的图标文件格式 */
        T3D_ERR_D3D11_IMAGE_SIZE_NOT_EQL,                /**< 图片大小不一致 */
        T3D_ERR_D3D11_INVALID_TARGET,                    /**< 错误的渲染目标 */
        T3D_ERR_D3D11_CREATE_FAILED,                     /**< 创建 D3D11 对象失败 */
        T3D_ERR_D3D11_CREATE_VERTEX_SHADER,              /**< 创建顶点着色器失败 */
        T3D_ERR_D3D11_CREATE_PIXEL_SHADER,               /**< 创建像素着色器失败 */
        T3D_ERR_D3D11_SHADER_NOT_COMPILED,               /**< Shader 没有编译 */
        T3D_ERR_D3D11_SHADER_COMPILED,                   /**< Shader 编译失败 */
        T3D_ERR_D3D11_CREATE_INPUT_LAYOUT,               /**< 创建输入布局失败 */
        T3D_ERR_D3D11_CREATE_BUFFER,                     /**< 创建缓冲区失败 */
        T3D_ERR_D3D11_CREATE_TEXTURE2D,                  /**< 创建 2D 纹理失败 */
        T3D_ERR_D3D11_LOCK_BUFFER,                       /**< 锁定缓冲区失败 */
        T3D_ERR_D3D11_MISMATCH_CALLING,                  /**< 接口调用不配对 */
        T3D_ERR_D3D11_CHECK_MULTISAMPLE,                 /**< 获取 Multiple Sample Quality 失败 */
        T3D_ERR_D3D11_PRESENT,                           /**< Present 失败 */
        T3D_ERR_D3D11_GET_INTERFACE,                     /**< 获取 COM 对象失败 */
        T3D_ERR_D3D11_CHECK_INTERFACE_SUPPORT,           /**< 获取 D3D 版本失败 */
        T3D_ERR_D3D11_GET_DRIVER_DESC,                   /**< 获取驱动描述失败 */
    };
}



#endif  /*__T3D_D3D11_ERROR_H__*/
