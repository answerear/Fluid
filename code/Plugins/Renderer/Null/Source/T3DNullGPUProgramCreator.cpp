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


#include "T3DD3D11GPUProgramCreator.h"
#include "T3DD3D11VertexShader.h"
#include "T3DD3D11PixelShader.h"
#include "T3DD3D11GPUProgram.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11ShaderCreator, ShaderCreator);

    //--------------------------------------------------------------------------

    const char * const D3D11ShaderCreator::SHADER_TYPE = "D3D11Shader";

    //--------------------------------------------------------------------------

    String D3D11ShaderCreator::getType() const
    {
        return SHADER_TYPE;
    }

    //--------------------------------------------------------------------------

    ShaderPtr D3D11ShaderCreator::createObject(int32_t argc, ...) const
    {
        va_list params;
        va_start(params, argc);
        Shader::ShaderType shaderType = va_arg(params, Shader::ShaderType);
        String name = va_arg(params, char *);
        String content;
        
        if (argc == 3)
        {
            content = va_arg(params, char *);
        }

        va_end(params);

        ShaderPtr shader;

        if (shaderType == Shader::ShaderType::VERTEX_SHADER)
        {
            shader = D3D11VertexShader::create(name, content);
        }
        else if (shaderType == Shader::ShaderType::PIXEL_SHADER)
        {
            shader = D3D11PixelShader::create(name, content);
        }

        return shader;
    }

    //--------------------------------------------------------------------------

    const char * const D3D11GPUProgramCreator::GPUPROGRAM_TYPE = "D3D11GPUProgram";

    //--------------------------------------------------------------------------

    String D3D11GPUProgramCreator::getType() const
    {
        return GPUPROGRAM_TYPE;
    }

    //--------------------------------------------------------------------------

    GPUProgramPtr D3D11GPUProgramCreator::createObject(int32_t argc, ...) const
    {
        va_list params;
        va_start(params, argc);
        String name = va_arg(params, char *);
        va_end(params);
        return D3D11GPUProgram::create(name);
    }

}