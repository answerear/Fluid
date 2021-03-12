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


#ifndef __T3D_MODEL_DATA_H__
#define __T3D_MODEL_DATA_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Kernel/T3DObject.h"
#include "Render/T3DRenderContext.h"
#include "Render/T3DHardwareVertexBuffer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    class T3D_ENGINE_API NodeData : public Object
    {
        T3D_DISABLE_COPY(NodeData);

    public:
        static NodeDataPtr create(const String &name);

        String      mName;          /**< 结点名称 */
        uint16_t    mParent;        /**< 父节点索引 */
        Matrix4     mLocalMatrix;   /**< 结点本地变换 */

        bool        mHasLink;       /**< 是否有挂渲染网格 */
        String      mLinkMesh;      /**< 本结点下挂接的网格 */
        String      mLinkSubMesh;   /**< 网格下挂接的子网格 */

    protected:
        NodeData(const String &name);
    };

    //--------------------------------------------------------------------------

    class T3D_ENGINE_API KeyFrameData : public Object
    {
        T3D_DISABLE_COPY(KeyFrameData);

    public:
        enum class Type : uint32_t
        {
            UNKNOWN = 0,
            TRANSLATION,
            ROTATION,
            SCALING
        };

        virtual ~KeyFrameData();

        virtual Type getType() const = 0;

        int64_t mTimestamp;     /**< 当前关键帧时间戳 */

    protected:
        KeyFrameData(int64_t timestamp);
    };

    class T3D_ENGINE_API KeyFrameDataT : public KeyFrameData
    {
        T3D_DISABLE_COPY(KeyFrameDataT);

    public:
        static KeyFrameDataTPtr create(int64_t timestamp, 
            const Vector3 &translation);

        virtual Type getType() const override;

        Vector3 mTranslation;   /**< 平移向量 */

    protected:
        KeyFrameDataT(int64_t timestamp, const Vector3 &translation);
    };

    class T3D_ENGINE_API KeyFrameDataR : public KeyFrameData
    {
        T3D_DISABLE_COPY(KeyFrameDataR);

    public:
        static KeyFrameDataRPtr create(int64_t timestamp, 
            const Quaternion &orientation);

        virtual Type getType() const override;

        Quaternion  mOrientation;   /**< 旋转四元数 */

    protected:
        KeyFrameDataR(int64_t timestamp, const Quaternion &orientation);
    };

    class T3D_ENGINE_API KeyFrameDataS : public KeyFrameData
    {
        T3D_DISABLE_COPY(KeyFrameDataS);

    public:
        static KeyFrameDataSPtr create(int64_t timestamp, 
            const Vector3 &scaling);

        virtual Type getType() const override;

        Vector3 mScaling;   /**< 每个轴的缩放值 */

    protected:
        KeyFrameDataS(int64_t timestamp, const Vector3 &scaling);
    };

    class T3D_ENGINE_API ActionData : public Object
    {
        T3D_DISABLE_COPY(ActionData);

    public:
        static ActionDataPtr create(const String &name, int32_t duration);

        typedef TArray<KeyFrameDataPtr>     KeyFrames;
        typedef KeyFrames::iterator         KeyFramesItr;
        typedef KeyFrames::const_iterator   KeyFramesConstItr;

        typedef TMap<String, KeyFrames>     Bones;
        typedef Bones::iterator             BonesItr;
        typedef Bones::const_iterator       BonesConstItr;
        typedef Bones::value_type           BonesValue;

        String  mName;              /**< 动作名称 */
        int32_t mDuration;          /**< 动作时长，单位：毫秒 */
        Bones   mBonesTranslation;  /**< 骨骼平移变换的关键帧数据 */
        Bones   mBonesRotation;     /**< 骨骼旋转变换的关键帧数据 */
        Bones   mBonesScaling;      /**< 骨骼缩放变换的关键帧数据 */

    protected:
        ActionData(const String &name, int32_t duration);
    };

    //--------------------------------------------------------------------------

    class T3D_ENGINE_API SubMeshData : public Object
    {
        T3D_DISABLE_COPY(SubMeshData);

    public:
        typedef TArray<uint8_t>         Indices;
        typedef Indices::iterator       IndicesItr;
        typedef Indices::const_iterator IndicesConstItr;

        static SubMeshDataPtr create(const String &name, 
            const String &materialName, RenderContext::PrimitiveType priType, 
            bool is16Bits, size_t indexCount);

        String                  mName;
        String                  mMaterialName;
        RenderContext::PrimitiveType mPrimitiveType;
        bool                    mIs16Bits;
        Indices                 mIndices;

    protected:
        SubMeshData(const String &name, const String &materialName, 
            RenderContext::PrimitiveType priType, bool is16Bits, size_t indexCount);
    };

    //--------------------------------------------------------------------------

    class T3D_ENGINE_API VertexData : public Object
    {
        T3D_DISABLE_COPY(VertexData);

    public:
        typedef TList<VertexAttribute>      Attributes;
        typedef Attributes::iterator        AttributesItr;
        typedef Attributes::const_iterator  AttributesConstItr;

        typedef TArray<uint8_t>             Vertices;
        typedef Vertices::iterator          VerticesItr;
        typedef Vertices::const_iterator    VerticesConstItr;

        static VertexDataPtr create(const String &name);

        String      mName;          /**< 顶点缓冲区名称 */
        Attributes  mAttributes;    /**< 顶点属性 */
        Vertices    mVertices;      /**< 顶点数据 */
        size_t      mVertexSize;    /**< 每个顶点大小，单位：字节 */

    protected:
        VertexData(const String &name);
    };

    class T3D_ENGINE_API MeshData : public Object
    {
        T3D_DISABLE_COPY(MeshData);

    public:
        typedef TList<VertexDataPtr>            VertexBuffers;
        typedef VertexBuffers::iterator         VertexBuffersItr;
        typedef VertexBuffers::const_iterator   VertexBuffersConstItr;

        typedef TList<SubMeshDataPtr>           SubMeshDataList;
        typedef SubMeshDataList::iterator       SubMeshDataListItr;
        typedef SubMeshDataList::const_iterator SubMeshDataListConstItr;

        static MeshDataPtr create(const String &name);

        String          mName;      /**< Mesh 名称 */
        VertexBuffers   mBuffers;   /**< Mesh 顶点数据列表 */
        SubMeshDataList mSubMeshes; /**< 子网格列表 */

    protected:
        MeshData(const String &name);
    };
}


#endif  /*__T3D_MODEL_DATA_H__*/
