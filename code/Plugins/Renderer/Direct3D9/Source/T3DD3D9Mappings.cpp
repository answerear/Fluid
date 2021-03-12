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


#include "T3DD3D9Mappings.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    D3DPRIMITIVETYPE D3D9Mappings::get(Renderer::PrimitiveType primitive)
    {
        D3DPRIMITIVETYPE d3dtype = D3DPT_TRIANGLESTRIP;

        switch (primitive)
        {
        case Renderer::E_PT_POINT_LIST:
            d3dtype = D3DPT_POINTLIST;
            break;
        case Renderer::E_PT_LINE_LIST:
            d3dtype = D3DPT_LINELIST;
            break;
        case Renderer::E_PT_TRIANGLE_LIST:
            d3dtype = D3DPT_TRIANGLELIST;
            break;
        case Renderer::E_PT_TRIANGLE_STRIP:
            d3dtype = D3DPT_TRIANGLESTRIP;
            break;
        case Renderer::E_PT_TRIANGLE_FAN:
            d3dtype = D3DPT_TRIANGLEFAN;
        }

        return d3dtype;
    }

    //--------------------------------------------------------------------------

    DWORD D3D9Mappings::get(HardwareBuffer::Usage usage)
    {
        DWORD ret = 0;

        if (usage & HardwareBuffer::E_HBU_DYNAMIC)
        {
            ret |= D3DUSAGE_DYNAMIC;
        }

        if (usage & HardwareBuffer::E_HBU_WRITE_ONLY)
        {
            ret |= D3DUSAGE_WRITEONLY;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    DWORD D3D9Mappings::get(HardwareBuffer::Usage usage, 
        HardwareBuffer::LockOptions options)
    {
        DWORD ret = 0;

        if (options == HardwareBuffer::E_HBL_DISCARD)
        {
            if (usage & HardwareBuffer::E_HBU_DYNAMIC)
                ret |= D3DLOCK_DISCARD;
        }

        if (options == HardwareBuffer::E_HBL_READ_ONLY)
        {
            if (!(usage & HardwareBuffer::E_HBU_WRITE_ONLY))
                ret |= D3DLOCK_READONLY;
        }

        if (options == HardwareBuffer::E_HBL_NO_OVERWRITE)
        {
            if (usage & HardwareBuffer::E_HBU_DYNAMIC)
                ret |= D3DLOCK_NOOVERWRITE;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    D3DFORMAT D3D9Mappings::get(HardwareIndexBuffer::Type type)
    {
        if (type == HardwareIndexBuffer::E_IT_16BITS)
        {
            return D3DFMT_INDEX16;
        }
        
        return D3DFMT_INDEX32;
    }

    //--------------------------------------------------------------------------

    D3DDECLTYPE D3D9Mappings::get(VertexAttribute::Type type)
    {
        D3DDECLTYPE d3dtype = D3DDECLTYPE_FLOAT3;

        switch (type)
        {
        case VertexAttribute::E_VAT_COLOR:
            d3dtype = D3DDECLTYPE_D3DCOLOR;
            break;
        case VertexAttribute::E_VAT_FLOAT1:
            d3dtype = D3DDECLTYPE_FLOAT1;
            break;
        case VertexAttribute::E_VAT_FLOAT2:
            d3dtype = D3DDECLTYPE_FLOAT2;
            break;
        case VertexAttribute::E_VAT_FLOAT3:
            d3dtype = D3DDECLTYPE_FLOAT3;
            break;
        case VertexAttribute::E_VAT_FLOAT4:
            d3dtype = D3DDECLTYPE_FLOAT4;
            break;
        case VertexAttribute::E_VAT_SHORT2:
            d3dtype = D3DDECLTYPE_SHORT2;
            break;
        case VertexAttribute::E_VAT_SHORT4:
            d3dtype = D3DDECLTYPE_SHORT4;
            break;
        case VertexAttribute::E_VAT_UBYTE4:
            d3dtype = D3DDECLTYPE_UBYTE4;
            break;
        }

        return d3dtype;
    }

    //--------------------------------------------------------------------------

    D3DDECLUSAGE D3D9Mappings::get(VertexAttribute::Semantic semantic)
    {
        D3DDECLUSAGE usage = D3DDECLUSAGE_POSITION;

        switch (semantic)
        {
        case VertexAttribute::E_VAS_POSITION:
            usage = D3DDECLUSAGE_POSITION;
            break;
        case VertexAttribute::E_VAS_BLENDWEIGHT:
            usage = D3DDECLUSAGE_BLENDWEIGHT;
            break;
        case VertexAttribute::E_VAS_BLENDINDICES:
            usage = D3DDECLUSAGE_BLENDINDICES;
            break;
        case VertexAttribute::E_VAS_NORMAL:
            usage = D3DDECLUSAGE_NORMAL;
            break;
        case VertexAttribute::E_VAS_DIFFUSE:
        case VertexAttribute::E_VAS_SPECULAR:
            usage = D3DDECLUSAGE_COLOR;
            break;
        case VertexAttribute::E_VAS_TEXCOORD:
            usage = D3DDECLUSAGE_TEXCOORD;
            break;
        case VertexAttribute::E_VAS_TANGENT:
            usage = D3DDECLUSAGE_TANGENT;
            break;
        case VertexAttribute::E_VAS_BINORMAL:
            usage = D3DDECLUSAGE_BINORMAL;
            break;
        }

        return usage;
    }

    //--------------------------------------------------------------------------

    D3DFORMAT D3D9Mappings::get(PixelFormat format)
    {
        D3DFORMAT d3dfmt = D3DFMT_A8B8G8R8;

        switch (format)
        {
        case E_PF_R5G6B5:
            d3dfmt = D3DFMT_R5G6B5;
            break;
        case E_PF_A1R5G5B5:
            d3dfmt = D3DFMT_A1R5G5B5;
            break;
        case E_PF_A4R4G4B4:
            d3dfmt = D3DFMT_A4R4G4B4;
            break;
        case E_PF_R8G8B8:
            d3dfmt = D3DFMT_R8G8B8;
            break;
        case E_PF_A8R8G8B8:
            d3dfmt = D3DFMT_A8R8G8B8;
            break;
        case E_PF_X8R8G8B8:
            d3dfmt = D3DFMT_X8R8G8B8;
            break;
        case E_PF_B8G8R8X8:
            d3dfmt = D3DFMT_X8B8G8R8;
            break;
        case E_PF_B8G8R8A8:
            d3dfmt = D3DFMT_A8B8G8R8;
            break;
        }

        return d3dfmt;
    }

    //--------------------------------------------------------------------------

    PixelFormat D3D9Mappings::get(D3DFORMAT d3dfmt)
    {
        PixelFormat format = E_PF_A8R8G8B8;

        switch (d3dfmt)
        {
        case D3DFMT_R5G6B5:
            format = E_PF_R5G6B5;
            break;
        case D3DFMT_A1R5G5B5:
            format = E_PF_A1R5G5B5;
            break;
        case D3DFMT_A4R4G4B4:
            format = E_PF_A4R4G4B4;
            break;
        case D3DFMT_R8G8B8:
            format = E_PF_R8G8B8;
            break;
        case D3DFMT_A8R8G8B8:
            format = E_PF_A8R8G8B8;
            break;
        case D3DFMT_X8R8G8B8:
            format = E_PF_X8R8G8B8;
            break;
        case D3DFMT_A8B8G8R8:
            format = E_PF_B8G8R8A8;
            break;
        case D3DFMT_X8B8G8R8:
            format = E_PF_B8G8R8X8;
            break;
        }

        return format;
    }

    //--------------------------------------------------------------------------

    D3DCOLORVALUE D3D9Mappings::get(const ColorARGB &color)
    {
        D3DCOLORVALUE d3dcolor;
        d3dcolor.a = color.alpha();
        d3dcolor.r = color.red();
        d3dcolor.g = color.green();
        d3dcolor.b = color.blue();
        return d3dcolor;
    }

    //--------------------------------------------------------------------------

    D3DMATRIX D3D9Mappings::toD3DMatrix(const Matrix4 &mat)
    {
        // 转置矩阵
        // D3D9 使用行向量 i.e. V*M
        // Tiny3D, OpenGL 等用列向量 i.e. M*V
        D3DXMATRIX d3dMat;
        d3dMat.m[0][0] = mat[0][0];
        d3dMat.m[0][1] = mat[1][0];
        d3dMat.m[0][2] = mat[2][0];
        d3dMat.m[0][3] = mat[3][0];

        d3dMat.m[1][0] = mat[0][1];
        d3dMat.m[1][1] = mat[1][1];
        d3dMat.m[1][2] = mat[2][1];
        d3dMat.m[1][3] = mat[3][1];

        d3dMat.m[2][0] = mat[0][2];
        d3dMat.m[2][1] = mat[1][2];
        d3dMat.m[2][2] = mat[2][2];
        d3dMat.m[2][3] = mat[3][2];

        d3dMat.m[3][0] = mat[0][3];
        d3dMat.m[3][1] = mat[1][3];
        d3dMat.m[3][2] = mat[2][3];
        d3dMat.m[3][3] = mat[3][3];

        return d3dMat;
    }

    //--------------------------------------------------------------------------

    Matrix4 D3D9Mappings::toT3DMatrix(const D3DMATRIX &mat)
    {
        Matrix4 t3dMat;
        t3dMat[0][0] = mat.m[0][0];
        t3dMat[1][0] = mat.m[0][1];
        t3dMat[2][0] = mat.m[0][2];
        t3dMat[3][0] = mat.m[0][3];

        t3dMat[0][1] = mat.m[1][0];
        t3dMat[1][1] = mat.m[1][1];
        t3dMat[2][1] = mat.m[1][2];
        t3dMat[3][1] = mat.m[1][3];

        t3dMat[0][2] = mat.m[2][0];
        t3dMat[1][2] = mat.m[2][1];
        t3dMat[2][2] = mat.m[2][2];
        t3dMat[3][2] = mat.m[2][3];

        t3dMat[0][3] = mat.m[3][0];
        t3dMat[1][3] = mat.m[3][1];
        t3dMat[2][3] = mat.m[3][2];
        t3dMat[3][3] = mat.m[3][3];

        return t3dMat;
    }
}

