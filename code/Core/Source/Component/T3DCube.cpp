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


#include "Component/T3DCube.h"
#include "Component/T3DTransform3D.h"
#include "Render/T3DRenderQueue.h"
#include "Render/T3DHardwareBufferManager.h"
#include "Render/T3DHardwareVertexBuffer.h"
#include "Render/T3DHardwareIndexBuffer.h"
#include "Render/T3DVertexArrayObject.h"
#include "Resource/T3DGPUProgram.h"
#include "Resource/T3DGPUProgramManager.h"
#include "Resource/T3DMaterial.h"
#include "Resource/T3DMaterialManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Cube, Renderable);

    //--------------------------------------------------------------------------

    /** 长方体顶点数据格式 */
    struct BoxVertex
    {
        BoxVertex()
            : position(Vector3::ZERO)
            , diffuse(ColorRGBA::WHITE)
        {

        }

        Vector3     position;
        ColorRGBA   diffuse;
    };

    //--------------------------------------------------------------------------

    CubePtr Cube::create(const Vector3 &center, const Vector3 &extent,
        ID uID /* = E_CID_AUTOMATIC */)
    {
        CubePtr box = new Cube(uID);
        box->release();
        
        if (box->init(center, extent) != T3D_OK)
        {
            box = nullptr;
        }

        return box;
    }

    //--------------------------------------------------------------------------

    Cube::Cube(ID uID /* = E_CID_AUTOMATIC */)
        : Renderable(uID)
        , mVAO(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    Cube::~Cube()
    {
        T3D_MATERIAL_MGR.unloadMaterial(mMaterial);
    }

    //--------------------------------------------------------------------------

    TResult Cube::init(const Vector3 &center, const Vector3 &extent)
    {
        TResult ret = T3D_OK;

        mCenter = center;
        mExtent = extent;

        const size_t MAX_VERTICES = 8;
        const size_t MAX_INDICES = 36;

        BoxVertex vertices[MAX_VERTICES];
        uint16_t indices[MAX_INDICES];
        setupBox(&vertices, MAX_VERTICES, indices, MAX_INDICES);

        do 
        {
            // 材质
            mMaterial = T3D_MATERIAL_MGR.loadMaterial("builtin/materials/BuiltinNoTexture.t3d",
                Material::E_MT_DEFAULT);

            // 创建 VAO
            mVAO = T3D_HARDWARE_BUFFER_MGR.createVertexArrayObject(true);
            if (mVAO == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Create VAO for Cube failed !");
                break;
            }

            // 绑定 VAO
            ret = mVAO->beginBinding();
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Binding VAO for Cube failed !");
                break;
            }

            // 创建顶点声明
            VertexDeclarationPtr decl
                = T3D_HARDWARE_BUFFER_MGR.createVertexDeclaration();
            if (decl == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, 
                    "Create vertex declaration for Cube failed !");
                break;
            }

            decl->addAttribute(VertexAttribute(0, 0,
                VertexAttribute::Type::E_VAT_FLOAT3,
                VertexAttribute::Semantic::E_VAS_POSITION, 0));
            decl->addAttribute(VertexAttribute(0, sizeof(Vector3),
                VertexAttribute::Type::E_VAT_COLOR,
                VertexAttribute::Semantic::E_VAS_DIFFUSE, 0));

            // 创建VBO
            HardwareVertexBufferPtr vbo
                = T3D_HARDWARE_BUFFER_MGR.createVertexBuffer(sizeof(BoxVertex),
                    MAX_VERTICES, vertices, 
                    HardwareBuffer::Usage::STATIC,
                    HardwareBuffer::AccessMode::CPU_NONE);
            if (vbo == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, 
                    "Create vertex buffer for Cube failed !");
                break;
            }

            // 创建IBO
            HardwareIndexBufferPtr ibo
                = T3D_HARDWARE_BUFFER_MGR.createIndexBuffer(
                    HardwareIndexBuffer::Type::E_IT_16BITS, MAX_INDICES, 
                    indices, HardwareBuffer::Usage::STATIC, 
                    HardwareBuffer::AccessMode::CPU_NONE);
            if (ibo == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, 
                    "Create index buffer for Cube failed !");
                break;
            }

            mVAO->setVertexDeclaration(decl);
            mVAO->addVertexBuffer(vbo);
            mVAO->setIndexBuffer(ibo);
            mVAO->setPrimitiveType(RenderContext::PrimitiveType::E_PT_TRIANGLE_LIST);

            mVAO->endBinding();
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void Cube::setupBox(void *vertices, size_t vertexCount, uint16_t *indices, 
        size_t indexCount)
    {
        // 
        // 正方体顶点定义如下：
        //
        //           v6-------v4
        //          /|       /|
        //         / |      / |
        //        v0-------v2 |
        //        |  v7----|--v5
        //        | /      | /
        //        |/       |/
        //        v1-------v3
        //

        BoxVertex *vert = (BoxVertex *)vertices;

        Vector3 offset;
        ColorRGBA color = ColorRGBA::WHITE;

        // V0
        offset[0] = -mExtent[0];
        offset[1] = mExtent[1];
        offset[2] = mExtent[2];
        vert[0].position = mCenter + offset;
        vert[0].diffuse = color;

        // V1
        offset[0] = -mExtent[0];
        offset[1] = -mExtent[1];
        offset[2] = mExtent[2];
        vert[1].position = mCenter + offset;
        vert[1].diffuse = color;

        // V2
        offset[0] = mExtent[0];
        offset[1] = mExtent[1];
        offset[2] = mExtent[2];
        vert[2].position = mCenter + offset;
        vert[2].diffuse = color;

        // V3
        offset[0] = mExtent[0];
        offset[1] = -mExtent[1];
        offset[2] = mExtent[2];
        vert[3].position = mCenter + offset;
        vert[3].diffuse = color;

        // V4
        offset[0] = mExtent[0];
        offset[1] = mExtent[1];
        offset[2] = -mExtent[2];
        vert[4].position = mCenter + offset;
        vert[4].diffuse = color;

        // V5
        offset[0] = mExtent[0];
        offset[1] = -mExtent[1];
        offset[2] = -mExtent[2];
        vert[5].position = mCenter + offset;
        vert[5].diffuse = color;

        // V6
        offset[0] = -mExtent[0];
        offset[1] = mExtent[1];
        offset[2] = -mExtent[2];
        vert[6].position = mCenter + offset;
        vert[6].diffuse = color;

        // V7
        offset[0] = -mExtent[0];
        offset[1] = -mExtent[1];
        offset[2] = -mExtent[2];
        vert[7].position = mCenter + offset;
        vert[7].diffuse = color;

        // Front face
        indices[0] = 0, indices[1] = 1, indices[2] = 2;
        indices[3] = 1, indices[4] = 3, indices[5] = 2;

        // Back
        indices[6] = 4, indices[7] = 5, indices[8] = 6;
        indices[9] = 5, indices[10] = 7, indices[11] = 6;

        // Left
        indices[12] = 0, indices[13] = 6, indices[14] = 7;
        indices[15] = 0, indices[16] = 7, indices[17] = 1;

        // Right
        indices[18] = 2, indices[19] = 3, indices[20] = 4;
        indices[21] = 3, indices[22] = 5, indices[23] = 4;

        // Top
        indices[24] = 0, indices[25] = 2, indices[26] = 4;
        indices[27] = 0, indices[28] = 4, indices[29] = 6;

        // Bottom
        indices[30] = 1, indices[31] = 7, indices[32] = 3;
        indices[33] = 3, indices[34] = 7, indices[35] = 5;
    }

    //--------------------------------------------------------------------------

    ComponentPtr Cube::clone() const
    {
        CubePtr box = new Cube();
        box->release();

        if (cloneProperties(box) != T3D_OK)
        {
            box = nullptr;
        }

        return box;
    }

    //--------------------------------------------------------------------------

    TResult Cube::cloneProperties(ComponentPtr newObj) const
    {
        TResult ret = Renderable::cloneProperties(newObj);

        if (ret == T3D_OK)
        {
            CubePtr box = smart_pointer_cast<Cube>(newObj);
            ret = box->init(mCenter, mExtent);
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    MaterialPtr Cube::getMaterial() const
    {
        return mMaterial;
    }

    //--------------------------------------------------------------------------

    VertexArrayObjectPtr Cube::getVertexArrayObject() const
    {
        return mVAO;
    }
}
