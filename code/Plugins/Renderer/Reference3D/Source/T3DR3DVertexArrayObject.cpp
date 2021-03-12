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


#include "T3DR3DVertexArrayObject.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    R3DVertexArrayObjectPtr R3DVertexArrayObject::create(bool useIndices)
    {
        R3DVertexArrayObjectPtr vao = new R3DVertexArrayObject(useIndices);
        vao->release();
        return vao;
    }

    //--------------------------------------------------------------------------

    R3DVertexArrayObject::R3DVertexArrayObject(bool useIndices)
        : mPrimitiveType(Renderer::E_PT_TRIANGLE_LIST)
        , mDecl(nullptr)
        , mIBO(nullptr)
        , mUseIndices(useIndices)
    {

    }

    //--------------------------------------------------------------------------

    R3DVertexArrayObject::~R3DVertexArrayObject()
    {

    }

    //--------------------------------------------------------------------------

    TResult R3DVertexArrayObject::beginBinding()
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DVertexArrayObject::endBinding()
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DVertexArrayObject::setPrimitiveType(
        Renderer::PrimitiveType priType)
    {
        mPrimitiveType = priType;
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    Renderer::PrimitiveType R3DVertexArrayObject::getPrimitiveType() const
    {
        return mPrimitiveType;
    }

    //--------------------------------------------------------------------------

    TResult R3DVertexArrayObject::setVertexDeclaration(
        VertexDeclarationPtr decl)
    {
        mDecl = decl;
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    VertexDeclarationPtr R3DVertexArrayObject::getVertexDeclaration() const
    {
        return mDecl;
    }

    //--------------------------------------------------------------------------

    TResult R3DVertexArrayObject::addVertexBuffer(HardwareVertexBufferPtr vbo)
    {
        mVBOList.push_back(vbo);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    size_t R3DVertexArrayObject::getVertexBufferCount() const
    {
        return mVBOList.size();
    }

    //--------------------------------------------------------------------------

    HardwareVertexBufferPtr R3DVertexArrayObject::getVertexBuffer(size_t idx) const
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

    TResult R3DVertexArrayObject::setIndexBuffer(HardwareIndexBufferPtr ibo)
    {
        mIBO = ibo;
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    HardwareIndexBufferPtr R3DVertexArrayObject::getIndexBuffer() const
    {
        return mIBO;
    }

    //--------------------------------------------------------------------------

    bool R3DVertexArrayObject::isIndicesUsed() const
    {
        return mUseIndices;
    }
}
