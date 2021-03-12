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

#include "Kernel/T3DModelData.h"
#include "Memory/T3DSmartPtr.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    NodeDataPtr NodeData::create(const String &name)
    {
        NodeDataPtr data = new NodeData(name);
        data->release();
        return data;
    }

    //--------------------------------------------------------------------------

    NodeData::NodeData(const String &name)
        : mName(name)
        , mParent(0xFFFF)
        , mLocalMatrix(false)
        , mHasLink(false)
    {

    }

    //--------------------------------------------------------------------------

    KeyFrameData::KeyFrameData(int64_t timestamp)
        : mTimestamp(timestamp)
    {

    }

    //--------------------------------------------------------------------------

    KeyFrameData::~KeyFrameData()
    {

    }

    //--------------------------------------------------------------------------

    KeyFrameDataTPtr KeyFrameDataT::create(int64_t timestamp, 
        const Vector3 &translation)
    {
        KeyFrameDataTPtr keyframe = new KeyFrameDataT(timestamp, translation);
        keyframe->release();
        return keyframe;
    }

    //--------------------------------------------------------------------------

    KeyFrameDataT::KeyFrameDataT(int64_t timestamp, const Vector3 &translation)
        : KeyFrameData(timestamp)
        , mTranslation(translation)
    {

    }

    //--------------------------------------------------------------------------

    KeyFrameData::Type KeyFrameDataT::getType() const
    {
        return Type::TRANSLATION;
    }

    //--------------------------------------------------------------------------

    KeyFrameDataRPtr KeyFrameDataR::create(int64_t timestamp,
        const Quaternion &orientation)
    {
        KeyFrameDataRPtr keyframe = new KeyFrameDataR(timestamp, orientation);
        keyframe->release();
        return keyframe;
    }

    //--------------------------------------------------------------------------

    KeyFrameDataR::KeyFrameDataR(int64_t timestamp, 
        const Quaternion &orientation)
        : KeyFrameData(timestamp)
        , mOrientation(orientation)
    {

    }

    //--------------------------------------------------------------------------

    KeyFrameData::Type KeyFrameDataR::getType() const
    {
        return Type::ROTATION;
    }

    //--------------------------------------------------------------------------

    KeyFrameDataSPtr KeyFrameDataS::create(int64_t timestamp,
        const Vector3 &scaling)
    {
        KeyFrameDataSPtr keyframe = new KeyFrameDataS(timestamp, scaling);
        keyframe->release();
        return keyframe;
    }

    //--------------------------------------------------------------------------

    KeyFrameDataS::KeyFrameDataS(int64_t timestamp, const Vector3 &scaling)
        : KeyFrameData(timestamp)
        , mScaling(scaling)
    {

    }

    //--------------------------------------------------------------------------

    KeyFrameData::Type KeyFrameDataS::getType() const
    {
        return Type::SCALING;
    }

    //--------------------------------------------------------------------------

    ActionDataPtr ActionData::create(const String &name, int32_t duration)
    {
        ActionDataPtr action = new ActionData(name, duration);
        action->release();
        return action;
    }

    //--------------------------------------------------------------------------

    ActionData::ActionData(const String &name, int32_t duration)
        : mName(name)
        , mDuration(duration)
    {

    }

    //--------------------------------------------------------------------------

    SubMeshDataPtr SubMeshData::create(const String &name,
        const String &materialName, RenderContext::PrimitiveType priType,
        bool is16Bits, size_t indexCount)
    {
        SubMeshDataPtr submesh = new SubMeshData(name, materialName, priType, 
            is16Bits, indexCount);
        submesh->release();
        return submesh;
    }

    //--------------------------------------------------------------------------

    SubMeshData::SubMeshData(const String &name, const String &materialName,
        RenderContext::PrimitiveType priType, bool is16Bits, size_t indexCount)
        : mName(name)
        , mMaterialName(materialName)
        , mPrimitiveType(priType)
        , mIs16Bits(is16Bits)
        , mIndices(is16Bits ? indexCount * sizeof(uint16_t) : indexCount * sizeof(uint32_t))
    {

    }

    //--------------------------------------------------------------------------

    VertexDataPtr VertexData::create(const String &name)
    {
        VertexDataPtr data = new VertexData(name);
        data->release();
        return data;
    }

    //--------------------------------------------------------------------------

    VertexData::VertexData(const String &name)
        : mName(name)
        , mAttributes()
        , mVertices()
        , mVertexSize(0)
    {

    }

    //--------------------------------------------------------------------------

    MeshDataPtr MeshData::create(const String &name)
    {
        MeshDataPtr mesh = new MeshData(name);
        mesh->release();
        return mesh;
    }

    //--------------------------------------------------------------------------

    MeshData::MeshData(const String &name)
        : mName(name)
        , mBuffers()
        , mSubMeshes()
    {

    }
}
