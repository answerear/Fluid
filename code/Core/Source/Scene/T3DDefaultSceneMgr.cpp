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


#include "Scene/T3DDefaultSceneMgr.h"
#include "Render/T3DRenderQueue.h"
#include "Render/T3DViewport.h"
#include "Component/T3DTransform3D.h"
#include "Component/T3DCamera.h"
#include "Component/T3DLight.h"
#include "Component/T3DMesh.h"
#include "Component/T3DAxis.h"
#include "Component/T3DBillboard.h"
#include "Component/T3DQuad.h"
#include "Component/T3DCube.h"
#include "Component/T3DGlobe.h"
#include "Kernel/T3DAgent.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    int32_t bitcount(uint32_t x)
    {
        x = (x & 0x55555555UL) + ((x >> 1) & 0x55555555UL); // 0-2 in 2 bits
        x = (x & 0x33333333UL) + ((x >> 2) & 0x33333333UL); // 0-4 in 4 bits
        x = (x & 0x0f0f0f0fUL) + ((x >> 4) & 0x0f0f0f0fUL); // 0-8 in 8 bits
        x = (x & 0x00ff00ffUL) + ((x >> 8) & 0x00ff00ffUL); // 0-16 in 16 bits
        x = (x & 0x0000ffffUL) + ((x >> 16) & 0x0000ffffUL); // 0-31 in 32 bits
        return x;
    }

    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(DefaultSceneMgr);
    T3D_IMPLEMENT_CLASS_1(DefaultSceneMgr, SceneManagerBase);

    //--------------------------------------------------------------------------

    DefaultSceneMgrPtr DefaultSceneMgr::create()
    {
        DefaultSceneMgrPtr mgr = new DefaultSceneMgr();
        mgr->release();

        if (mgr->init() != T3D_OK)
        {
            mgr = nullptr;
        }

        return mgr;
    }

    //--------------------------------------------------------------------------

    DefaultSceneMgr::DefaultSceneMgr()
        : mRoot(nullptr)
        , mRenderQueue(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    DefaultSceneMgr::~DefaultSceneMgr()
    {
        if (mRoot != nullptr)
        {
            mRoot->removeAllChildren();
            mRoot = nullptr;
        }

        mRenderQueue = nullptr;
    }

    //--------------------------------------------------------------------------

    TResult DefaultSceneMgr::init()
    {
        TResult ret = T3D_OK;

        // 设置组件更新顺序
        setComponentOrder(T3D_CLASS(Transform3D), ComponentOrder::TRANSFORM);
        setComponentOrder(T3D_CLASS(Camera), ComponentOrder::CAMERA);
        setComponentOrder(T3D_CLASS(Bound), ComponentOrder::COLLIDER);
        setComponentOrder(T3D_CLASS(Renderable), ComponentOrder::RENDERABLE);

        mRenderQueue = RenderQueue::create();

        // 预分配32个槽给存放要剔除的可渲染对象
        mSceneNodes.resize(32, Slot());

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult DefaultSceneMgr::update()
    {
        TResult ret = T3D_OK;

        if (mRoot != nullptr)
        {
            mRoot->visit();
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult DefaultSceneMgr::render(ViewportPtr viewport)
    {
        TResult ret = T3D_OK;

        RenderContextPtr renderer = T3D_AGENT.getActiveRenderer();

        // 设置当前视口
        if (renderer->getViewport() != viewport)
        {
            renderer->setViewport(viewport);
        }

        // 清空渲染队列
        mRenderQueue->clear();

        CameraPtr camera = viewport->getCamera();

        // 做视锥体裁剪
        frustumCulling(camera);

        // 直接对渲染队列的对象渲染
        Point pos(viewport->getActualLeft(), viewport->getActualTop());
        Size size(viewport->getActualWidth(), viewport->getActualHeight());
        Rect rect(pos, size);
        
        renderer->clear(viewport->getBkgndColor(), viewport->getClearFlags(),
            viewport->getClearZ(), 0);
        mRenderQueue->render(renderer);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult DefaultSceneMgr::frustumCulling(CameraPtr camera)
    {
        TResult ret = T3D_OK;

        BoundPtr bound = camera->getBound();

        uint32_t mask = camera->getObjectMask();

        uint32_t count = bitcount(mask);
        uint32_t i = 0;
        uint32_t idx = 0;

        for (i = 0; i < sizeof(mask) && idx < count; ++i)
        {
            if (mask & (1 << i))
            {
                idx++;

                Slot &slot = mSceneNodes[i];
                
                SceneNodePtr node = slot.first;
                while (node != nullptr)
                {
                    if (node->isEnabled() && node->isVisible())
                    {
                        node->frustumCulling(bound, mRenderQueue);
                    }

                    node = node->mNext;
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    SceneNodePtr DefaultSceneMgr::getRoot() const
    {
        return mRoot;
    }

    //--------------------------------------------------------------------------

    SceneNodePtr DefaultSceneMgr::createSceneNode(SceneNodePtr parent, 
        ID uID /* = Node::E_NID_AUTOMATIC */)
    {
        if (mRoot == nullptr)
        {
            // 创建根节点
            mRoot = SceneNode::create();
            mRoot->setName("Root");
            mRoot->addComponent(T3D_CLASS(Transform3D));
        }

        if (parent == nullptr)
        {
            parent = mRoot;
        }

        SceneNodePtr node = SceneNode::create(uID);

        if (node != nullptr)
        {
            if (parent != nullptr)
            {
                parent->addChild(node);
            }

            node->addComponent(T3D_CLASS(Transform3D));
        }

        return node;
    }

    //--------------------------------------------------------------------------

    TResult DefaultSceneMgr::addSceneNode(SceneNode *node)
    {
        TResult ret = T3D_OK;

        do 
        {
            uint32_t mask = node->getCameraMask() - 1;

            if (mask >= sizeof(mask))
            {
                // 最多支持32个，这里已经越界了
                ret = T3D_ERR_OUT_OF_BOUND;
                T3D_LOG_ERROR(LOG_TAG_SCENE, 
                    "Culling renderable mask is out of bound !");
                break;
            }

            Slot &slot = mSceneNodes[mask];

            if (slot.first == nullptr)
            {
                // 空链表
                slot.first = node;
                slot.last = node;
                node->mPrev = node->mNext = nullptr;
            }
            else
            {
                // 非空链表，插入最后
                slot.last->mNext = node;
                node->mPrev = slot.last;
                node->mNext = nullptr;
                slot.last = node;
            }

            slot.count++;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult DefaultSceneMgr::removeSceneNode(SceneNode *node)
    {
        TResult ret = T3D_OK;

        do 
        {
            uint32_t mask = node->getCameraMask() - 1;

            if (mask >= sizeof(mask))
            {
                // 最多支持32个，这里已经越界了
                ret = T3D_ERR_OUT_OF_BOUND;
                T3D_LOG_ERROR(LOG_TAG_SCENE, 
                    "Culling renderable mask is out of bound !");
                break;
            }

            if (node->mPrev != nullptr)
                node->mPrev->mNext = node->mNext;
            if (node->mNext != nullptr)
                node->mNext->mPrev = node->mPrev;

            Slot &slot = mSceneNodes[mask];
            slot.count--;

            if (slot.count == 0)
            {
                slot.first = slot.last = nullptr;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void DefaultSceneMgr::setComponentOrder(const Class *cls, uint32_t order)
    {
        mOrders.insert(OrderMapValue(cls, order));
    }

    //--------------------------------------------------------------------------

    uint32_t DefaultSceneMgr::getComponentOrder(const Class *cls) const
    {
        uint32_t order = ComponentOrder::INVALID;

        auto itr = mOrders.find(cls);
        if (itr != mOrders.end())
        {
            order = itr->second;
        }

        return order;
    }

    //--------------------------------------------------------------------------

    const DefaultSceneMgr::OrderMap &DefaultSceneMgr::getComponentOrders() const
    {
        return mOrders;
    }
}

