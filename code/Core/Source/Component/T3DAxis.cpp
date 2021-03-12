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


#include "Component/T3DAxis.h"
#include "Component/T3DTransform3D.h"
#include "Render/T3DRenderQueue.h"
#include "Render/T3DHardwareBufferManager.h"
#include "Render/T3DHardwareVertexBuffer.h"
#include "Render/T3DHardwareIndexBuffer.h"
#include "Render/T3DVertexArrayObject.h"
#include "Resource/T3DGPUProgram.h"
#include "Resource/T3DGPUProgramManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Axis, Renderable);

    //--------------------------------------------------------------------------

    /** 坐标轴顶点数据格式 */
    struct AxisVertex
    {
        AxisVertex()
            : position(Vector3::ZERO)
            , diffuse(ColorRGB::WHITE)
        {
            
        }

        Vector3     position;   /**< 位置 */
        ColorRGB     diffuse;    /**< 颜色 */
    };

    //--------------------------------------------------------------------------

    AxisPtr Axis::create(Real X, Real Y, Real Z, 
        ID uID /* = E_NID_AUTOMATIC */)
    {
        AxisPtr axis = new Axis(uID);
        axis->release();

        if (axis->init(X, Y, Z) != T3D_OK)
        {
            axis = nullptr;
        }

        return axis;
    }

    //--------------------------------------------------------------------------

    Axis::Axis(ID uID /* = E_NID_AUTOMATIC */)
        : Renderable(uID)
        , mVAO(nullptr)
//         , mBound(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    Axis::~Axis()
    {
        mVAO = nullptr;
    }

    //--------------------------------------------------------------------------

    TResult Axis::init(Real X, Real Y, Real Z)
    {
        TResult ret = T3D_OK;

        const size_t MAX_VERTICES = 6;

        AxisVertex vertices[MAX_VERTICES];

        // 设置三个坐标轴顶点数据
        vertices[0].diffuse = ColorRGB::RED;
        vertices[1].diffuse = ColorRGB::RED;

        vertices[2].diffuse = ColorRGB::GREEN;
        vertices[3].diffuse = ColorRGB::GREEN;

        vertices[4].diffuse = ColorRGB::BLUE;
        vertices[5].diffuse = ColorRGB::BLUE;

        vertices[1].position[0] = X;
        vertices[3].position[1] = Y;
        vertices[5].position[3] = Z;

        do 
        {
            mVAO = T3D_HARDWARE_BUFFER_MGR.createVertexArrayObject(false);
            if (mVAO == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Create VAO for Axis failed !");
                break;
            }

            ret = mVAO->beginBinding();
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Binding VAO for Axis failed !");
                break;
            }

            // 创建顶点声明
            VertexDeclarationPtr decl
                = T3D_HARDWARE_BUFFER_MGR.createVertexDeclaration();
            if (decl == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Create vertex declaration for \
                    Axis failed !");
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
                = T3D_HARDWARE_BUFFER_MGR.createVertexBuffer(sizeof(AxisVertex),
                    MAX_VERTICES, vertices, 
                    HardwareBuffer::Usage::STATIC, 
                    HardwareBuffer::AccessMode::CPU_WRITE);
            if (vbo == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_SCENE, "Create vertex buffer for \
                    Axis failed !");
                break;
            }

            mVAO->setVertexDeclaration(decl);
            mVAO->addVertexBuffer(vbo);
            mVAO->setPrimitiveType(RenderContext::PrimitiveType::E_PT_LINE_LIST);

            mVAO->endBinding();

            // 构建碰撞球，以三个轴最短边作为半径
//             Real radius = REAL_INF;
//             radius = Math::min(radius, X);
//             radius = Math::min(radius, Y);
//             radius = Math::min(radius, Z);
//             mBound = SphereBound::create();
//             mBound->setParams(Vector3::ZERO, radius);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    Real Axis::getAxisLength(Axis::Type axis) const
    {
        Real length = 0.0f;

        switch (axis)
        {
        case Type::AXIS_X:
            length = mAxisX;
            break;
        case Type::AXIS_Y:
            length = mAxisY;
            break;
        case Type::AXIS_Z:
            length = mAxisZ;
            break;
        default:
            break;
        }

        return length;
    }

    //--------------------------------------------------------------------------

    ComponentPtr Axis::clone() const
    {
        AxisPtr axis = new Axis();
        axis->release();

        if (cloneProperties(axis) != T3D_OK)
        {
            axis = nullptr;
        }

        return axis;
    }

    //--------------------------------------------------------------------------

    TResult Axis::cloneProperties(ComponentPtr newObj) const
    {
        TResult ret = Renderable::cloneProperties(newObj);

        if (ret == T3D_OK)
        {
            AxisPtr axis = smart_pointer_cast<Axis>(newObj);
            ret = axis->init(getAxisLength(Type::AXIS_X), 
                getAxisLength(Type::AXIS_Y),
                getAxisLength(Type::AXIS_Z));
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    MaterialPtr Axis::getMaterial() const
    {
        return nullptr;
    }

    //--------------------------------------------------------------------------

    VertexArrayObjectPtr Axis::getVertexArrayObject() const
    {
        return mVAO;
    }
}

