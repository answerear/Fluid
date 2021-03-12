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


#include "T3DD3D9VertexDeclaration.h"
#include "T3DD3D9Mappings.h"
#include "T3DD3D9Renderer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    D3D9VertexDeclarationPtr D3D9VertexDeclaration::create()
    {
        D3D9VertexDeclarationPtr decl = new D3D9VertexDeclaration();
        decl->release();
        return decl;
    }

    //--------------------------------------------------------------------------

    D3D9VertexDeclaration::D3D9VertexDeclaration()
        : VertexDeclaration()
        , mD3DVertexDecl(nullptr)
        , mIsDirty(false)
    {

    }

    //--------------------------------------------------------------------------

    D3D9VertexDeclaration::~D3D9VertexDeclaration()
    {

    }

    //--------------------------------------------------------------------------

    const VertexAttribute &D3D9VertexDeclaration::addAttribute(size_t stream,
        size_t offset, VertexAttribute::Type type,
        VertexAttribute::Semantic semantic)
    {
        mIsDirty = true;
        return VertexDeclaration::addAttribute(stream, offset, type, semantic);
    }

    //--------------------------------------------------------------------------

    const VertexAttribute &D3D9VertexDeclaration::insertAttribute(size_t pos,
        size_t stream, size_t offset, VertexAttribute::Type type,
        VertexAttribute::Semantic semantic)
    {
        mIsDirty = true;
        return VertexDeclaration::insertAttribute(pos, stream, offset, type, 
            semantic);
    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexDeclaration::addAttribute(
        const VertexAttribute &vertexAttribute)
    {
        mIsDirty = true;
        return VertexDeclaration::addAttribute(vertexAttribute);
    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexDeclaration::insertAttribute(size_t pos,
        const VertexAttribute &vertexAttribute)
    {
        mIsDirty = true;
        return VertexDeclaration::insertAttribute(pos, vertexAttribute);
    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexDeclaration::removeAttribute(size_t pos)
    {
        mIsDirty = true;
        return VertexDeclaration::removeAttribute(pos);
    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexDeclaration::removeAttribute(
        VertexAttribute::Semantic semantic)
    {
        mIsDirty = true;
        return VertexDeclaration::removeAttribute(semantic);
    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexDeclaration::removeAllAttributes()
    {
        mIsDirty = true;
        return VertexDeclaration::removeAllAttributes();
    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexDeclaration::updateAttribute(size_t pos, size_t stream,
        size_t offset, VertexAttribute::Type type,
        VertexAttribute::Semantic semantic)
    {
        mIsDirty = true;
        return VertexDeclaration::updateAttribute(pos, stream, offset, type, 
            semantic);
    }

    //--------------------------------------------------------------------------

    VertexDeclarationPtr D3D9VertexDeclaration::clone() const
    {
        VertexDeclarationPtr ptr = VertexDeclaration::clone();
        D3D9VertexDeclarationPtr decl 
            = smart_pointer_cast<D3D9VertexDeclaration>(ptr);
        decl->mIsDirty = true;

        return ptr;
    }

    //--------------------------------------------------------------------------

    LPDIRECT3DVERTEXDECLARATION9 
        D3D9VertexDeclaration::getD3D9VertexDeclaration()
    {
        if (mIsDirty)
        {
            D3D_SAFE_RELEASE(mD3DVertexDecl);

            D3DVERTEXELEMENT9 *d3dve 
                = new D3DVERTEXELEMENT9[mVertexAttributes.size() + 1];

            size_t i = 0;
            auto itr = mVertexAttributes.begin();
            while (itr != mVertexAttributes.end())
            {
                d3dve[i].Usage = D3D9Mappings::get(itr->getSemantic());
                d3dve[i].Type = D3D9Mappings::get(itr->getType());
                d3dve[i].Offset = itr->getOffset();
                d3dve[i].Stream = itr->getStream();
                d3dve[i].UsageIndex = 0;
                d3dve[i].Method = D3DDECLMETHOD_DEFAULT;
                ++itr;
                ++i;
            }

            d3dve[i].Usage = 0;
            d3dve[i].Type = D3DDECLTYPE_UNUSED;
            d3dve[i].Offset = 0;
            d3dve[i].Stream = 0xff;
            d3dve[i].UsageIndex = 0;
            d3dve[i].Method = 0;

            LPDIRECT3DDEVICE9 pD3DDevice = D3D9_RENDERER.getD3DDevice();
            HRESULT hr 
                = pD3DDevice->CreateVertexDeclaration(d3dve, &mD3DVertexDecl);
            if (FAILED(hr))
            {

            }

            delete[]d3dve;
            d3dve = nullptr;

            mIsDirty = false;
        }

        return mD3DVertexDecl;
    }
}
