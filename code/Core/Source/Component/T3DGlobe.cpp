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


#include "Component/T3DGlobe.h"
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

    T3D_IMPLEMENT_CLASS_1(Globe, Renderable);

    //--------------------------------------------------------------------------

    struct SphereVertex
    {
        SphereVertex()
            : position(Vector3::ZERO)
            , color(ColorRGB::WHITE)
        {

        }

        Vector3     position;
        ColorRGBA   color;
    };

    //--------------------------------------------------------------------------

    const size_t MAX_STACKS = 18;
    const size_t MAX_SLICES = 18;
    const size_t MAX_VERTICES = (MAX_STACKS + 1) * (MAX_SLICES + 1);
    const size_t MAX_TRIANGLES = MAX_STACKS * MAX_SLICES * 2;

    //--------------------------------------------------------------------------

    GlobePtr Globe::create(const Vector3 &center, Real radius, 
        ID uID /* = E_CID_AUTOMATIC */)
    {
        GlobePtr sphere = new Globe(uID);
        sphere->release();

        if (sphere->init(center, radius) != T3D_OK)
        {
            sphere = nullptr;
        }

        return sphere;
    }

    //--------------------------------------------------------------------------

    Globe::Globe(ID uID /* = E_CID_AUTOMATIC */)
        : Renderable(uID)
        , mCenter(Vector3::ZERO)
        , mRadius(REAL_ONE)
        , mVAO(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    Globe::~Globe()
    {
        T3D_MATERIAL_MGR.unloadMaterial(mMaterial);
    }

    //--------------------------------------------------------------------------

    TResult Globe::init(const Vector3 &center, Real radius)
    {
        TResult ret = T3D_OK;

        mCenter = center;
        mRadius = radius;

        SphereVertex vertices[MAX_VERTICES];
        const size_t MAX_INDICES = MAX_TRIANGLES * 3;
        uint16_t indices[MAX_INDICES];

        setupSphere(vertices, MAX_VERTICES, indices, MAX_INDICES);

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
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Create VAO for Globe failed !");
                break;
            }

            // 绑定 VAO
            ret = mVAO->beginBinding();
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Binding VAO for Globe failed !");
                break;
            }

            // 创建顶点声明
            VertexDeclarationPtr decl
                = T3D_HARDWARE_BUFFER_MGR.createVertexDeclaration();
            if (decl == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, 
                    "Create vertex declaration for Globe failed !");
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
                = T3D_HARDWARE_BUFFER_MGR.createVertexBuffer(
                    sizeof(SphereVertex), MAX_VERTICES, vertices,
                    HardwareVertexBuffer::Usage::STATIC, 
                    HardwareBuffer::AccessMode::CPU_NONE);
            if (vbo == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, 
                    "Create vertex buffer for Globe failed !");
                break;
            }

            // 创建IBO
            HardwareIndexBufferPtr ibo
                = T3D_HARDWARE_BUFFER_MGR.createIndexBuffer(
                    HardwareIndexBuffer::Type::E_IT_16BITS, MAX_INDICES, indices,
                    HardwareBuffer::Usage::STATIC, 
                    HardwareBuffer::AccessMode::CPU_NONE);
            if (ibo == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, 
                    "Create index buffer for Globe failed !");
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

    void Globe::setupSphere(void *vertices, size_t vertexCount,
        uint16_t *indices, size_t indexCount)
    {
        SphereVertex *vert = (SphereVertex *)vertices;

        const ColorRGBA &color = ColorRGBA::WHITE;

        Radian alphaStep(Real(2.0) * Math::PI / MAX_STACKS);
        Radian betaStep(Math::PI / MAX_SLICES);
        Radian alpha(0.0);
        Radian beta;

        int32_t i = 0, j = 0, idx = 0;

        for (i = 0; i <= MAX_STACKS; ++i)
        {
            Real sinAlpha = Math::sin(alpha);
            Real cosAlpha = Math::cos(alpha);
            beta = -Math::PI * REAL_HALF;

            for (j = 0; j <= MAX_SLICES; ++j, ++idx)
            {
                Real sinBeta = Math::sin(beta);
                Real cosBeta = Math::cos(beta);

                vert[idx].position[0] 
                    = mCenter[0] + mRadius * cosBeta * cosAlpha;
                vert[idx].position[1] 
                    = mCenter[1] + mRadius * sinBeta;
                vert[idx].position[2] 
                    = mCenter[2] + mRadius * cosBeta * sinAlpha;

                vert[idx].color = color;

                beta += betaStep;
            }

            alpha += alphaStep;
        }

        uint16_t base = 0;
        idx = 0;

        for (i = 0; i < MAX_STACKS; ++i)
        {
            for (j = 0; j < MAX_SLICES; ++j)
            {
                indices[idx++] = base;
                indices[idx++] = base + 1;
                indices[idx++] = base + MAX_SLICES + 1;

                indices[idx++] = base + 1;
                indices[idx++] = base + MAX_SLICES + 2;
                indices[idx++] = base + MAX_SLICES + 1;

                base++;
            }

            base++;
        }
    }

    //--------------------------------------------------------------------------

    ComponentPtr Globe::clone() const
    {
        GlobePtr sphere = new Globe();
        sphere->release();

        if (cloneProperties(sphere) != T3D_OK)
        {
            sphere = nullptr;
        }

        return sphere;
    }

    //--------------------------------------------------------------------------

    TResult Globe::cloneProperties(ComponentPtr newObj) const
    {
        TResult ret = Renderable::cloneProperties(newObj);

        if (ret == T3D_OK)
        {
            GlobePtr sphere = smart_pointer_cast<Globe>(newObj);
            ret = sphere->init(mCenter, mRadius);
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    MaterialPtr Globe::getMaterial() const
    {
        return mMaterial;
    }

    //--------------------------------------------------------------------------

    VertexArrayObjectPtr Globe::getVertexArrayObject() const
    {
        return mVAO;
    }
}
