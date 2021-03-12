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


#include "Component/T3DQuad.h"
#include "Render/T3DRenderQueue.h"
#include "Render/T3DHardwareBufferManager.h"
#include "Render/T3DHardwareVertexBuffer.h"
#include "Render/T3DHardwareIndexBuffer.h"
#include "Render/T3DVertexArrayObject.h"
#include "Resource/T3DMaterial.h"
#include "Resource/T3DMaterialManager.h"
#include "Resource/T3DGPUProgram.h"
#include "Resource/T3DGPUProgramManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Quad, Renderable);

    //--------------------------------------------------------------------------

    struct QuadVertex
    {
        QuadVertex()
            : position(Vector3::ZERO)
            , normal(Vector3::ZERO)
            , uv(Vector2::ZERO)
        {

        }

        Vector3     position;
        Vector3     normal;
        Vector2     uv;
    };

    //--------------------------------------------------------------------------

    QuadPtr Quad::create(const QuadData &quad, const String &materialName,
        ID uID /* = E_CID_AUTOMATIC */)
    {
        QuadPtr q = new Quad(uID);
        q->release();

        if (q->init(quad, materialName) != T3D_OK)
        {
            q = nullptr;
        }

        return q;
    }

    //--------------------------------------------------------------------------

    Quad::Quad(ID uID /* = E_CID_AUTOMATIC */)
        : Renderable(uID)
        , mMaterial(nullptr)
        , mVAO(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    Quad::~Quad()
    {

    }

    //--------------------------------------------------------------------------

    TResult Quad::init(const QuadData &quad, const String &materialName)
    {
        TResult ret = T3D_OK;

        QuadVertex vertices[VI_MAX_VERTICES];
        size_t i = 0;

        // 构建顶点法线
        Vector3 d0 = quad.vertices[VI_TOP_LEFT].position
            - quad.vertices[VI_TOP_RIGHT].position;
        Vector3 d1 = quad.vertices[VI_BOTTOM_LEFT].position
            - quad.vertices[VI_TOP_LEFT].position;

        Vector3 normal = d1 - d0;
        normal.normalize();

        // 构建顶点坐标和UV
        for (i = 0; i < VI_MAX_VERTICES; ++i)
        {
            vertices[i].position = quad.vertices[i].position;
            vertices[i].normal = normal;
            vertices[i].uv = quad.vertices[i].uv;
            mQuad.vertices[i].position = quad.vertices[i].position;
        }

        // 构建索引数据
        const size_t MAX_INDICES = 6;
        uint16_t indices[MAX_INDICES];
        indices[0] = 0, indices[1] = 2, indices[2] = 1;
        indices[3] = 1, indices[4] = 2, indices[5] = 3;

        // 加载材质
        mMaterial = T3D_MATERIAL_MGR.loadMaterial(materialName, 
            Material::E_MT_DEFAULT);

        do
        {
            mVAO = T3D_HARDWARE_BUFFER_MGR.createVertexArrayObject(true);
            if (mVAO == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Create VAO for Quad failed !");
                break;
            }

            ret = mVAO->beginBinding();
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Binding VAO for Quad failed !");
                break;
            }

            // 创建顶点声明
            VertexDeclarationPtr decl
                = T3D_HARDWARE_BUFFER_MGR.createVertexDeclaration();
            if (decl == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Create vertex declaration for \
                    Quad failed !");
                break;
            }

            decl->addAttribute(VertexAttribute(0, 0,
                VertexAttribute::Type::E_VAT_FLOAT3,
                VertexAttribute::Semantic::E_VAS_POSITION, 0));
            size_t offset = sizeof(Vector3);
            decl->addAttribute(VertexAttribute(0, offset,
                VertexAttribute::Type::E_VAT_FLOAT3,
                VertexAttribute::Semantic::E_VAS_NORMAL, 0));
            offset = sizeof(Vector3) + sizeof(Vector3);
            decl->addAttribute(VertexAttribute(0, offset,
                VertexAttribute::Type::E_VAT_FLOAT2,
                VertexAttribute::Semantic::E_VAS_TEXCOORD, 0));

            // 创建VBO
            HardwareVertexBufferPtr vbo
                = T3D_HARDWARE_BUFFER_MGR.createVertexBuffer(sizeof(QuadVertex),
                    VI_MAX_VERTICES, vertices, HardwareBuffer::Usage::STATIC, 
                    HardwareBuffer::AccessMode::CPU_WRITE);
            if (vbo == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Create vertex buffer for \
                    Quad failed !");
                break;
            }

            // 创建IBO
            HardwareIndexBufferPtr ibo
                = T3D_HARDWARE_BUFFER_MGR.createIndexBuffer(
                    HardwareIndexBuffer::Type::E_IT_16BITS, MAX_INDICES, indices,
                    HardwareBuffer::Usage::STATIC, 
                    HardwareBuffer::AccessMode::CPU_WRITE);
            if (ibo == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Create index buffer for Quad \
                    failed !");
                break;
            }

            mVAO->setVertexDeclaration(decl);
            mVAO->addVertexBuffer(vbo);
            mVAO->setIndexBuffer(ibo);
            mVAO->setPrimitiveType(RenderContext::PrimitiveType::E_PT_TRIANGLE_LIST);

            mVAO->endBinding();

            // 需要刷新碰撞体的世界变换
//             setDirty(true);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    ComponentPtr Quad::clone() const
    {
        QuadPtr quad = new Quad();
        quad->release();

        if (cloneProperties(quad) != T3D_OK)
        {
            quad = nullptr;
        }

        return quad;
    }

    //--------------------------------------------------------------------------

    TResult Quad::cloneProperties(ComponentPtr newObj) const
    {
        TResult ret = Renderable::cloneProperties(newObj);

        if (ret == T3D_OK)
        {
            QuadPtr quad = smart_pointer_cast<Quad>(newObj);
            ret = quad->init(mQuad, mMaterial->getName());
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    MaterialPtr Quad::getMaterial() const
    {
        return mMaterial;
    }

    //--------------------------------------------------------------------------

    VertexArrayObjectPtr Quad::getVertexArrayObject() const
    {
        return mVAO;
    }
}
