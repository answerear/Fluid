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


#include "T3DR3DVertexDeclaration.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    R3DVertexDeclarationPtr R3DVertexDeclaration::create(ShaderPtr vertexShader)
    {
        R3DVertexDeclarationPtr decl = new R3DVertexDeclaration(vertexShader);
        decl->release();
        return decl;
    }

    //--------------------------------------------------------------------------

    R3DVertexDeclaration::R3DVertexDeclaration(ShaderPtr vertexShader)
        : VertexDeclaration(vertexShader)
    {

    }

    //--------------------------------------------------------------------------

    R3DVertexDeclaration::~R3DVertexDeclaration()
    {

    }
}
