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


#ifndef __T3D_D3D11_PREREQUISITES_H__
#define __T3D_D3D11_PREREQUISITES_H__


#include <Tiny3D.h>
#include <d3d11.h>
#include <d3dcompiler.h>


#include <algorithm>
#undef min


#if defined D3D11RENDERER_EXPORT
    #define T3D_D3D11RENDERER_API        T3D_EXPORT_API
#else
    #define T3D_D3D11RENDERER_API        T3D_IMPORT_API
#endif


#define D3D_SAFE_RELEASE(p) \
    if ((p) != nullptr)   \
    {   \
        (p)->Release();   \
        (p) = nullptr;    \
    }


namespace Tiny3D
{
    #define LOG_TAG_D3D11RENDERER        "D3D11Renderer"

    class D3D11Renderer;
    class D3D11Capabilities;
    class D3D11RenderWindow;
    class D3D11HardwareBufferManager;
    class D3D11HardwareBuffer;
    class D3D11HardwareVertexBuffer;
    class D3D11HardwareIndexBuffer;
    class D3D11HardwarePixelBuffer;
    class D3D11HardwareConstantBuffer;
    class D3D11VertexDeclaration;
    class D3D11VertexArrayObject;
    class D3D11Shader;
    class D3D11VertexShader;
    class D3D11PixelShader;
    class D3D11ShaderCreator;
    class D3D11GPUProgram;
    class D3D11GPUProgramCreator;
    class D3D11Sampler;
    class D3D11SamplerCreator;

    T3D_DECLARE_SMART_PTR(D3D11Renderer);
    T3D_DECLARE_SMART_PTR(D3D11Capabilities);
    T3D_DECLARE_SMART_PTR(D3D11RenderWindow);
    T3D_DECLARE_SMART_PTR(D3D11HardwareBufferManager);
    T3D_DECLARE_SMART_PTR(D3D11HardwareBuffer);
    T3D_DECLARE_SMART_PTR(D3D11HardwareVertexBuffer);
    T3D_DECLARE_SMART_PTR(D3D11HardwareIndexBuffer);
    T3D_DECLARE_SMART_PTR(D3D11HardwarePixelBuffer);
    T3D_DECLARE_SMART_PTR(D3D11HardwareConstantBuffer);
    T3D_DECLARE_SMART_PTR(D3D11VertexDeclaration);
    T3D_DECLARE_SMART_PTR(D3D11VertexArrayObject);
    T3D_DECLARE_SMART_PTR(D3D11Shader);
    T3D_DECLARE_SMART_PTR(D3D11VertexShader);
    T3D_DECLARE_SMART_PTR(D3D11PixelShader);
    T3D_DECLARE_SMART_PTR(D3D11GPUProgram);
    T3D_DECLARE_SMART_PTR(D3D11Sampler);
    T3D_DECLARE_SMART_PTR(D3D11SamplerCreator);
}


#endif  /*__T3D_D3D11_PREREQUISITES_H__*/
