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


#include "T3DD3D9VertexArrayObject.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    D3D9VertexArrayObjectPtr D3D9VertexArrayObject::create(bool useIndices)
    {
        D3D9VertexArrayObjectPtr vao = new D3D9VertexArrayObject(useIndices);
        vao->release();
        return vao;
    }

    //--------------------------------------------------------------------------

    D3D9VertexArrayObject::D3D9VertexArrayObject(bool useIndices)
        : mPrimitiveType(Renderer::E_PT_TRIANGLE_LIST)
        , mDecl(nullptr)
        , mIBO(nullptr)
        , mUseIndices(useIndices)
    {

    }

    //--------------------------------------------------------------------------

    D3D9VertexArrayObject::~D3D9VertexArrayObject()
    {

    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexArrayObject::beginBinding()
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexArrayObject::endBinding()
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexArrayObject::setPrimitiveType(
        Renderer::PrimitiveType priType)
    {
        mPrimitiveType = priType;
        setDirty(true);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    Renderer::PrimitiveType D3D9VertexArrayObject::getPrimitiveType() const
    {
        return mPrimitiveType;
    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexArrayObject::setVertexDeclaration(
        VertexDeclarationPtr decl)
    {
        mDecl = decl;
        setDirty(true);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    VertexDeclarationPtr D3D9VertexArrayObject::getVertexDeclaration() const
    {
        return mDecl;
    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexArrayObject::addVertexBuffer(HardwareVertexBufferPtr vbo)
    {
        mVBOList.push_back(vbo);
        setDirty(true);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    size_t D3D9VertexArrayObject::getVertexBufferCount() const
    {
        return mVBOList.size();
    }

    //--------------------------------------------------------------------------

    HardwareVertexBufferPtr D3D9VertexArrayObject::getVertexBuffer(size_t idx) const
    {
        HardwareVertexBufferPtr vbo;
        size_t i = 0;
        auto itr = mVBOList.begin();

        while (itr != mVBOList.end())
        {
            if (idx == i)
            {
                vbo = *itr;
                break;
            }

            ++itr;
            ++i;
        }
        return vbo;
    }

    //--------------------------------------------------------------------------

    TResult D3D9VertexArrayObject::setIndexBuffer(HardwareIndexBufferPtr ibo)
    {
        mIBO = ibo;
        setDirty(true);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    HardwareIndexBufferPtr D3D9VertexArrayObject::getIndexBuffer() const
    {
        return mIBO;
    }

    //--------------------------------------------------------------------------

    bool D3D9VertexArrayObject::isIndicesUsed() const
    {
        return mUseIndices;
    }
}
