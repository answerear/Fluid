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


#include "Render/T3DVertexArrayObject.h"
#include "Render/T3DHardwareVertexBuffer.h"
#include "Render/T3DHardwareIndexBuffer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(VertexArrayObject, Object);

    //--------------------------------------------------------------------------

    VertexArrayObject::VertexArrayObject()
        : mPrimitiveCount(0)
        , mIsDirty(false)
    {

    }

    //--------------------------------------------------------------------------

    VertexArrayObject::~VertexArrayObject()
    {

    }

    //--------------------------------------------------------------------------

    size_t VertexArrayObject::getPrimitiveCount() const
    {
        if (mIsDirty)
        {
            mPrimitiveCount = calcPrimitiveCount();
            mIsDirty = false;
        }

        return mPrimitiveCount;
    }

    //--------------------------------------------------------------------------

    size_t VertexArrayObject::calcPrimitiveCount() const
    {
        size_t primCount = 0;
        HardwareIndexBufferPtr ibo = getIndexBuffer();
        HardwareVertexBufferPtr vbo = getVertexBuffer(0);

        if (ibo == nullptr && vbo == nullptr)
        {
            return 0;
        }

        switch (getPrimitiveType())
        {
        case RenderContext::PrimitiveType::E_PT_POINT_LIST:
            primCount = (isIndicesUsed() 
                ? ibo->getIndexCount() : vbo->getVertexCount());
            break;

        case RenderContext::PrimitiveType::E_PT_LINE_LIST:
            primCount = (isIndicesUsed() 
                ? ibo->getIndexCount() : vbo->getVertexCount()) / 2;
            break;

        case RenderContext::PrimitiveType::E_PT_LINE_STRIP:
            primCount = (isIndicesUsed() 
                ? ibo->getIndexCount() : vbo->getVertexCount()) - 1;
            break;

        case RenderContext::PrimitiveType::E_PT_TRIANGLE_LIST:
            primCount = (isIndicesUsed() 
                ? ibo->getIndexCount() : vbo->getVertexCount()) / 3;
            break;

        case RenderContext::PrimitiveType::E_PT_TRIANGLE_STRIP:
            primCount = (isIndicesUsed() 
                ? ibo->getIndexCount() : vbo->getVertexCount()) - 2;
            break;

        case RenderContext::PrimitiveType::E_PT_TRIANGLE_FAN:
            primCount = (isIndicesUsed() 
                ? ibo->getIndexCount() : vbo->getVertexCount()) - 2;
            break;
        }

        return primCount;
    }
}
