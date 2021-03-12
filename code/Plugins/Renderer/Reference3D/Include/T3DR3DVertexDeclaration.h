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


#ifndef __T3D_R3D_VERTEX_DECLARATION_H__
#define __T3D_R3D_VERTEX_DECLARATION_H__


#include "T3DR3DPrerequisites.h"


namespace Tiny3D
{
    /**
     * @brief Reference3D 渲染器相关的顶点声明类
     */
    class R3DVertexDeclaration : public VertexDeclaration
    {
    public:
        /**
         * @brief 创建 Reference3D 渲染器相关的顶点声明对象
         */
        static R3DVertexDeclarationPtr create(ShaderPtr vertexShader);

        /**
         * @brief 析构函数
         */
        virtual ~R3DVertexDeclaration();

    protected:
        /**
         * @brief 构造函数
         */
        R3DVertexDeclaration(ShaderPtr vertexShader);
    };
}


#endif  /*__T3D_R3D_VERTEX_DECLARATION_H__*/
