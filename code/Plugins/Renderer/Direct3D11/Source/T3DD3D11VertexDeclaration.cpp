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


#include "T3DD3D11VertexDeclaration.h"
#include "T3DD3D11Mappings.h"
#include "T3DD3D11Context.h"
#include "T3DD3D11VertexShader.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11VertexDeclaration, VertexDeclaration);

    //--------------------------------------------------------------------------

    D3D11VertexDeclarationPtr D3D11VertexDeclaration::create()
    {
        D3D11VertexDeclarationPtr decl = new D3D11VertexDeclaration();
        decl->release();
        return decl;
    }

    //--------------------------------------------------------------------------

    D3D11VertexDeclaration::D3D11VertexDeclaration()
        : VertexDeclaration()
        , mD3DInputLayout(nullptr)
        , mIsDirty(false)
    {

    }

    //--------------------------------------------------------------------------

    D3D11VertexDeclaration::~D3D11VertexDeclaration()
    {
        D3D_SAFE_RELEASE(mD3DInputLayout);
    }

    //--------------------------------------------------------------------------

    const VertexAttribute &D3D11VertexDeclaration::addAttribute(size_t stream,
        size_t offset, VertexAttribute::Type type,
        VertexAttribute::Semantic semantic, size_t semanticIndex)
    {
        mIsDirty = true;
        return VertexDeclaration::addAttribute(stream, offset, type, semantic, 
            semanticIndex);
    }

    //--------------------------------------------------------------------------

    const VertexAttribute &D3D11VertexDeclaration::insertAttribute(size_t pos,
        size_t stream, size_t offset, VertexAttribute::Type type,
        VertexAttribute::Semantic semantic, size_t semanticIndex)
    {
        mIsDirty = true;
        return VertexDeclaration::insertAttribute(pos, stream, offset, type, 
            semantic, semanticIndex);
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexDeclaration::addAttribute(
        const VertexAttribute &vertexAttribute)
    {
        mIsDirty = true;
        return VertexDeclaration::addAttribute(vertexAttribute);
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexDeclaration::insertAttribute(size_t pos,
        const VertexAttribute &vertexAttribute)
    {
        mIsDirty = true;
        return VertexDeclaration::insertAttribute(pos, vertexAttribute);
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexDeclaration::removeAttribute(size_t pos)
    {
        mIsDirty = true;
        return VertexDeclaration::removeAttribute(pos);
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexDeclaration::removeAttribute(
        VertexAttribute::Semantic semantic, size_t semanticIndex)
    {
        mIsDirty = true;
        return VertexDeclaration::removeAttribute(semantic, semanticIndex);
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexDeclaration::removeAllAttributes()
    {
        mIsDirty = true;
        return VertexDeclaration::removeAllAttributes();
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexDeclaration::updateAttribute(size_t pos, size_t stream,
        size_t offset, VertexAttribute::Type type,
        VertexAttribute::Semantic semantic, size_t semanticIndex)
    {
        mIsDirty = true;
        return VertexDeclaration::updateAttribute(pos, stream, offset, type, 
            semantic, semanticIndex);
    }

    //--------------------------------------------------------------------------

    VertexDeclarationPtr D3D11VertexDeclaration::clone() const
    {
        VertexDeclarationPtr ptr = VertexDeclaration::clone();
        D3D11VertexDeclarationPtr decl 
            = smart_pointer_cast<D3D11VertexDeclaration>(ptr);
        decl->mIsDirty = true;

        return ptr;
    }

    //--------------------------------------------------------------------------

    ID3D11InputLayout *D3D11VertexDeclaration::getD3DInputLayout(
        D3D11VertexShaderPtr shader)
    {
        if (mIsDirty)
        {
            D3D_SAFE_RELEASE(mD3DInputLayout);

            do 
            {
                const size_t nNumElements = mVertexAttributes.size();
                D3D11_INPUT_ELEMENT_DESC *desc =
                    new D3D11_INPUT_ELEMENT_DESC[nNumElements];

                size_t i = 0;
                auto itr = mVertexAttributes.begin();

                while (itr != mVertexAttributes.end())
                {
                    const VertexAttribute &attrib = *itr;
                    desc[i].SemanticName 
                        = D3D11Mappings::get(attrib.getSemantic());
                    desc[i].SemanticIndex = (UINT)attrib.getSemanticIndex();
                    desc[i].Format = D3D11Mappings::get(attrib.getType());
                    desc[i].InputSlot = (UINT)attrib.getStream();
                    desc[i].AlignedByteOffset = (UINT)attrib.getOffset();
                    desc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
                    desc[i].InstanceDataStepRate = 0;
                    ++i;
                    ++itr;
                }

                ID3D11Device *pD3DDevice = D3D11_CONTEXT.getD3DDevice();

                const char *bytecode = nullptr;
                size_t bytecodeLength = 0;
                shader->getBytecode(bytecode, bytecodeLength);

                HRESULT hr = S_OK;
                hr = pD3DDevice->CreateInputLayout(desc, (UINT)nNumElements,
                    bytecode, bytecodeLength, &mD3DInputLayout);
                if (FAILED(hr))
                {
                    T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, "Create input layout \
                        failed ! DX ERROR [%d]", hr);
                    break;
                }

                mIsDirty = false;
            } while (0);
            
        }

        return mD3DInputLayout;
    }
}
