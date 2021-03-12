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


#include "T3DD3D11VertexArrayObject.h"
#include "T3DD3D11VertexBuffer.h"
#include "T3DD3D11Error.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11VertexArrayObject, VertexArrayObject);

    //--------------------------------------------------------------------------

    D3D11VertexArrayObjectPtr D3D11VertexArrayObject::create(bool useIndices)
    {
        D3D11VertexArrayObjectPtr vao = new D3D11VertexArrayObject(useIndices);
        vao->release();
        return vao;
    }

    //--------------------------------------------------------------------------

    D3D11VertexArrayObject::D3D11VertexArrayObject(bool useIndices)
        : mPrimitiveType(RenderContext::PrimitiveType::E_PT_TRIANGLE_LIST)
        , mDecl(nullptr)
        , mIBO(nullptr)
        , mUseIndices(useIndices)
        , mD3D11Buffers(nullptr)
        , mD3D11BufferStrides(nullptr)
        , mD3D11BufferOffsets(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    D3D11VertexArrayObject::~D3D11VertexArrayObject()
    {
        T3D_SAFE_DELETE_ARRAY(mD3D11Buffers);
        T3D_SAFE_DELETE_ARRAY(mD3D11BufferStrides);
        T3D_SAFE_DELETE_ARRAY(mD3D11BufferOffsets);
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexArrayObject::beginBinding()
    {
        T3D_SAFE_DELETE_ARRAY(mD3D11Buffers);
        T3D_SAFE_DELETE_ARRAY(mD3D11BufferStrides);
        T3D_SAFE_DELETE_ARRAY(mD3D11BufferOffsets);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexArrayObject::endBinding()
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mD3D11Buffers != nullptr)
            {
                ret = T3D_ERR_D3D11_MISMATCH_CALLING;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Mismatch calling ! It should call beginBinding() first !");
                break;
            }

            // 构造 ID3D11Buffer 对象数组、顶点步长数组、顶点偏移数组
            mD3D11Buffers = new ID3D11Buffer*[mVBOList.size()];
            mD3D11BufferStrides = new UINT[mVBOList.size()];
            mD3D11BufferOffsets = new UINT[mVBOList.size()];

            size_t i = 0;
            auto itr = mVBOList.begin();

            while (itr != mVBOList.end())
            {
                D3D11VertexBufferPtr vbo =
                    smart_pointer_cast<D3D11VertexBuffer>(*itr);
                mD3D11Buffers[i] = vbo->getD3D11Buffer();
                mD3D11BufferStrides[i] = (UINT)vbo->getVertexSize();
                mD3D11BufferOffsets[i] = 0;
                ++itr;
            }
        } while (0);

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexArrayObject::setPrimitiveType(
        RenderContext::PrimitiveType priType)
    {
        mPrimitiveType = priType;
        setDirty(true);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    RenderContext::PrimitiveType D3D11VertexArrayObject::getPrimitiveType() const
    {
        return mPrimitiveType;
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexArrayObject::setVertexDeclaration(
        VertexDeclarationPtr decl)
    {
        mDecl = decl;
        setDirty(true);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    VertexDeclarationPtr D3D11VertexArrayObject::getVertexDeclaration() const
    {
        return mDecl;
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexArrayObject::addVertexBuffer(HardwareVertexBufferPtr vbo)
    {
        mVBOList.push_back(vbo);
        setDirty(true);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    size_t D3D11VertexArrayObject::getVertexBufferCount() const
    {
        return mVBOList.size();
    }

    //--------------------------------------------------------------------------

    HardwareVertexBufferPtr D3D11VertexArrayObject::getVertexBuffer(size_t idx) const
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

    TResult D3D11VertexArrayObject::setIndexBuffer(HardwareIndexBufferPtr ibo)
    {
        mIBO = ibo;
        setDirty(true);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    HardwareIndexBufferPtr D3D11VertexArrayObject::getIndexBuffer() const
    {
        return mIBO;
    }

    //--------------------------------------------------------------------------

    bool D3D11VertexArrayObject::isIndicesUsed() const
    {
        return mUseIndices;
    }

    //--------------------------------------------------------------------------

    size_t D3D11VertexArrayObject::getVertexCount() const
    {
        return mVBOList.front()->getVertexCount();
    }
}
