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

#ifndef __T3D_CONVERTER_PREREQUISITES_H__
#define __T3D_CONVERTER_PREREQUISITES_H__


#include <Tiny3D.h>

#include <fbxsdk.h>


namespace Tiny3D
{
    #define TAG_MESH_CONVERTER      "MeshConverter"

    #define MCONV_LOG_ERROR(fmt, ...)   \
        T3D_LOG_ERROR(TAG_MESH_CONVERTER, fmt, ##__VA_ARGS__);  \
        printf(fmt, ##__VA_ARGS__); \
        printf("\n");

    #define MCONV_LOG_WARNING(fmt, ...) \
        T3D_LOG_WARNING(TAG_MESH_CONVERTER, fmt, ##__VA_ARGS__);    \
        printf(fmt, ##__VA_ARGS__); \
        printf("\n");

    #define MCONV_LOG_INFO(fmt, ...)    \
        T3D_LOG_INFO(TAG_MESH_CONVERTER, fmt, ##__VA_ARGS__);   \
        printf(fmt, ##__VA_ARGS__); \
        printf("\n");

    #define MCONV_LOG_DEBUG(fmt, ...)   \
        T3D_LOG_DEBUG(TAG_MESH_CONVERTER, fmt, ##__VA_ARGS__);  \
        printf(fmt, ##__VA_ARGS__); \
        printf("\n");

    enum MeshFileType
    {
        AUTO = 0,       /**< 根据扩展名自动判断文件格式 */
        FBX = 0x10,     /**< FBX 格式 */
        OGRE = 0x20,    /**< OGRE 格式 */
        T3B = 0x40,     /**< Tiny3D 二进制格式 */
        T3T = 0x41,     /**< Tiny3D 文本格式 */
    };

    enum class BoundType : uint32_t
    {
        SPHERE = 0,
        AABB
    };
}


#endif  /*__T3D_CONVERTER_PREREQUISITES_H__*/

