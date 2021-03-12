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


#include "Render/T3DRenderQueue.h"
#include "Render/T3DVertexArrayObject.h"
#include "Render/T3DHardwareVertexBuffer.h"
#include "Render/T3DHardwareIndexBuffer.h"
#include "Component/T3DRenderable.h"
#include "Component/T3DCamera.h"
#include "Kernel/T3DTechnique.h"
#include "Kernel/T3DPass.h"
#include "Kernel/T3DTextureUnit.h"
#include "Resource/T3DGPUProgram.h"
#include "Scene/T3DSceneNode.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(RenderGroup, Object);

    //--------------------------------------------------------------------------

    RenderGroupPtr RenderGroup::create()
    {
        RenderGroupPtr group = new RenderGroup();
        group->release();
        return group;
    }

    //--------------------------------------------------------------------------

    RenderGroup::RenderGroup()
    {

    }

    //--------------------------------------------------------------------------

    RenderGroup::~RenderGroup()
    {

    }

    //--------------------------------------------------------------------------

    TResult RenderGroup::addRenderable(RenderablePtr renderable)
    {
        TResult ret = T3D_OK;

        do 
        {
            MaterialPtr material = renderable->getMaterial();
            if (material == nullptr)
            {
                break;
            }

            auto itr = mRenderables.find(material);

            if (itr != mRenderables.end())
            {
                // 有相同的材质，放到相同材质渲染对象列表
                RenderableList &renderables = itr->second;
                renderables.push_back(renderable);
            }
            else
            {
                // 没有相同材质，新增一个材质渲染对象列表
                RenderableList renderables(1, renderable);
                mRenderables.insert(RenderablesValue(material, renderables));
            }
        } while (0);

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    void RenderGroup::clear()
    {
        mRenderables.clear();
    }

    //--------------------------------------------------------------------------

    TResult RenderGroup::render(ID groupID, RenderContextPtr renderer)
    {
        PolygonMode renderMode;

        ViewportPtr vp = renderer->getViewport();
        if (vp == nullptr)
        {
            return T3D_OK;
        }

        CameraPtr camera = vp->getCamera();

//         if (RenderQueue::E_GRPID_INDICATOR == groupID
//             || RenderQueue::E_GRPID_WIREFRAME == groupID)
//         {
//             // 指示器或者线框渲染，渲染模式需要改成线框模式
//             renderMode = renderer->getPolygonMode();
//             renderer->setPolygonMode(PolygonMode::WIREFRAME);
//         }

        if (RenderQueue::E_GRPID_LIGHT != groupID)
        {
            // 不是灯光分组
            RenderablesItr itr = mRenderables.begin();

            while (itr != mRenderables.end())
            {
                MaterialPtr material = itr->first;
                TechniquePtr tech = material->getBestTechnique();

                // 渲染该 Technique 下所有 Pass
                size_t idx = 0;
                for (idx = 0; idx < tech->getPassCount(); ++idx)
                {
                    PassPtr pass = tech->getPass(idx);

                    renderer->setPolygonMode(pass->getPolygonMode());

                    GPUProgramPtr program = pass->getGPUProgram();
                    renderer->bindGPUProgram(program);

                    TextureUnitPtr unit = pass->getTextureUnit(0);
                    renderer->bindTexture(unit);

                    RenderableList &renderables = itr->second;

                    RenderableListItr i = renderables.begin();

                    while (i != renderables.end())
                    {
                        RenderablePtr renderable = *i;

                        // 设置渲染物体的世界变换
                        const Transform &xform = renderable->getSceneNode()->getTransform3D()->getLocalToWorldTransform();
                        const Matrix4 &m = xform.getAffineMatrix();
                        renderer->setWorldTransform(m);

                        // 根据VAO数据渲染
                        renderer->renderObject(renderable->getVertexArrayObject());

                        ++i;
                    }
                }

                ++itr;
            }
        }

//         if (RenderQueue::E_GRPID_INDICATOR == groupID
//             || RenderQueue::E_GRPID_WIREFRAME == groupID)
//         {
//             // 恢复渲染模式
//             renderer->setPolygonMode(renderMode);
//         }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    size_t RenderGroup::calcPrimitiveCount(VertexArrayObjectPtr vao) const
    {
        RenderContext::PrimitiveType priType = vao->getPrimitiveType();
        bool useIndex = vao->isIndicesUsed();
        size_t indexCount 
            = (useIndex ? vao->getIndexBuffer()->getIndexCount() : 0);
        size_t vertexCount = vao->getVertexBuffer(0)->getVertexCount();

        size_t primCount = 0;

        switch (priType)
        {
        case RenderContext::PrimitiveType::E_PT_POINT_LIST:
            primCount = (useIndex ? indexCount : vertexCount);
            break;

        case RenderContext::PrimitiveType::E_PT_LINE_LIST:
            primCount = (useIndex ? indexCount : vertexCount) / 2;
            break;

        case RenderContext::PrimitiveType::E_PT_LINE_STRIP:
            primCount = (useIndex ? indexCount : vertexCount) - 1;
            break;

        case RenderContext::PrimitiveType::E_PT_TRIANGLE_LIST:
            primCount = (useIndex ? indexCount : vertexCount) / 3;
            break;

        case RenderContext::PrimitiveType::E_PT_TRIANGLE_STRIP:
            primCount = (useIndex ? indexCount : vertexCount) - 2;
            break;

        case RenderContext::PrimitiveType::E_PT_TRIANGLE_FAN:
            primCount = (useIndex ? indexCount : vertexCount) - 2;
            break;
        }

        return primCount;
    }

    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(RenderQueue, Object);

    //--------------------------------------------------------------------------

    RenderQueuePtr RenderQueue::create()
    {
        RenderQueuePtr rq = new RenderQueue();
        rq->release();
        return rq;
    }

    //--------------------------------------------------------------------------

    RenderQueue::RenderQueue()
    {

    }

    //--------------------------------------------------------------------------

    RenderQueue::~RenderQueue()
    {

    }

    //--------------------------------------------------------------------------

    TResult RenderQueue::addRenderable(uint32_t groupID, 
        RenderablePtr renderable)
    {
        RenderableGroupItr itr = mGroups.find(groupID);

        if (itr != mGroups.end())
        {
            /// 已经有这组渲染对象
            RenderGroupPtr &group = itr->second;
            group->addRenderable(renderable);
        }
        else
        {
            /// 不存在这组渲染对象
            RenderGroupPtr group = RenderGroup::create();
            group->addRenderable(renderable);
            mGroups.insert(RenderableGroupValue(groupID, group));
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    void RenderQueue::clear()
    {
        mGroups.clear();
    }

    //--------------------------------------------------------------------------

    TResult RenderQueue::render(RenderContextPtr renderer)
    {
        RenderableGroupItr itr = mGroups.begin();

        while (itr != mGroups.end())
        {
            itr->second->render(itr->first, renderer);
            ++itr;
        }

        return T3D_OK;
    }
}
