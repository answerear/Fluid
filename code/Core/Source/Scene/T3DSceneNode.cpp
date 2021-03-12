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


#include "Scene/T3DSceneNode.h"
#include "Component/T3DCamera.h"
#include "Component/T3DCube.h"
#include "Component/T3DGlobe.h"
#include "Kernel/T3DAgent.h"
#include "Kernel/T3DCommon.h"
#include "Kernel/T3DTechnique.h"
#include "Component/T3DComponent.h"
#include "Component/T3DComponentCreator.h"
#include "Component/T3DRenderable.h"
#include "Scene/T3DSceneManager.h"
#include "Render/T3DRenderQueue.h"



namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(SceneNode, Node);

    //--------------------------------------------------------------------------

    SceneNodePtr SceneNode::create(ID uID /* = E_NID_AUTOMATIC */)
    {
        SceneNodePtr node = new SceneNode(uID);
        node->release();
        return node;
    }

    //--------------------------------------------------------------------------

    SceneNode::SceneNode(ID uID /* = E_NID_AUTOMATIC */)
        : Node(uID)
        , mIsVisible(true)
        , mIsEnabled(true)
        , mIsDirty(true)
        , mCameraMask(0)
        , mTransform3D(nullptr)
        , mCollider(nullptr)
        , mRenderable(nullptr)
        , mPrev(nullptr)
        , mNext(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    SceneNode::~SceneNode()
    {
        removeAllComponents();
    }

    //--------------------------------------------------------------------------

    Node::Type SceneNode::getNodeType() const
    {
        return Type::SCENE_NODE;
    }

    //--------------------------------------------------------------------------

    NodePtr SceneNode::clone() const
    {
        SceneNodePtr node = SceneNode::create();
        TResult ret = cloneProperties(node);

        if (T3D_FAILED(ret))
        {
            node = nullptr;
        }

        return node;
    }

    //--------------------------------------------------------------------------

    TResult SceneNode::cloneProperties(NodePtr node) const
    {
        TResult ret = Node::cloneProperties(node);

        if (ret == T3D_OK)
        {
            SceneNodePtr newNode = smart_pointer_cast<SceneNode>(node);
            newNode->mIsEnabled = mIsEnabled;
            newNode->mIsVisible = mIsVisible;

            ComponentPtr component;
            auto itr = mComponentQueue.begin();
            while (itr != mComponentQueue.end())
            {
                component = itr->second->clone();

                if (component != nullptr)
                {
                    newNode->mComponentQueue.insert(ComponentQueueValue(itr->first, component));
                    newNode->mComponents.insert(ComponentsValue(component->getClass(), component));

                    if (ComponentOrder::TRANSFORM == itr->first)
                    {
                        newNode->mTransform3D = smart_pointer_cast<Transform3D>(component);
                    }
                    else if (ComponentOrder::COLLIDER == itr->first)
                    {
                        newNode->mCollider = smart_pointer_cast<Bound>(component);
                    }
                    else if (ComponentOrder::RENDERABLE == itr->first)
                    {
                        newNode->mRenderable = smart_pointer_cast<Renderable>(component);
                    }

                    component->onAttachSceneNode(newNode);
                }
            }

            if (mCameraMask != 0)
            {
                newNode->setCameraMask(mCameraMask);
            }
        }

        return ret;
    }


    //--------------------------------------------------------------------------

    void SceneNode::update()
    {
        auto itr = mComponentQueue.begin();

        while (itr != mComponentQueue.end())
        {
            itr->second->update();
            ++itr;
        }
    }

    //--------------------------------------------------------------------------

    void SceneNode::frustumCulling(BoundPtr bound, RenderQueuePtr queue)
    {
        Technique *tech = mRenderable->getMaterial()->getBestTechnique();

        if (mCollider != nullptr)
        {
            if (mCollider->test(bound))
            {
                queue->addRenderable(tech->getRenderQueue(), mRenderable);
            }
        }
        else
        {
            queue->addRenderable(tech->getRenderQueue(), mRenderable);
        }
    }


    //--------------------------------------------------------------------------

    void SceneNode::setVisible(bool visible)
    {
        if (mIsVisible != visible)
        {
            mIsVisible = visible;

            NodePtr node = getFirstChild();

            while (node != nullptr)
            {
                SceneNodePtr child = smart_pointer_cast<SceneNode>(node);
                child->setVisible(visible);
                node = node->getNextSibling();
            }
        }
    }

    //--------------------------------------------------------------------------

    void SceneNode::setEnabled(bool enabled)
    {
        if (mIsEnabled != enabled)
        {
            mIsEnabled = enabled;

            NodePtr node = getFirstChild();

            while (node != nullptr)
            {
                SceneNodePtr child = smart_pointer_cast<SceneNode>(node);
                child->setEnabled(enabled);
                node = node->getNextSibling();
            }
        }
    }

    //--------------------------------------------------------------------------

    void SceneNode::setCameraMask(uint32_t mask)
    {
        if (mCameraMask == 0)
        {
            // 之前没有设置过，直接添加到默认场景里面
            mCameraMask = mask;

            if (getParent() != nullptr && mRenderable != nullptr)
            {
                T3D_SCENE_MGR.addSceneNode(this);
            }
        }
        else if (mCameraMask != mask)
        {
            if (getParent() != nullptr && mRenderable != nullptr)
            {
                T3D_SCENE_MGR.removeSceneNode(this);
                mCameraMask = mask;
                T3D_SCENE_MGR.addSceneNode(this);
            }
            else
            {
                mCameraMask = mask;
            }
        }

        NodePtr node = getFirstChild();

        while (node != nullptr)
        {
            SceneNodePtr child = smart_pointer_cast<SceneNode>(node);
            child->setCameraMask(mask);
            node = node->getNextSibling();
        }
    }

    //--------------------------------------------------------------------------

    void SceneNode::visit()
    {
        // 先调用更新
        if (isEnabled())
        {
            update();

            // 再遍历子结点
            NodePtr node = getFirstChild();

            while (node != nullptr)
            {
                SceneNodePtr child = smart_pointer_cast<SceneNode>(node);
                child->visit();
                node = node->getNextSibling();
            }
        }
    }

    //--------------------------------------------------------------------------

    uint32_t SceneNode::getComponentOrder(const Class *cls) const
    {
        uint32_t order = 0;

        if (cls->isKindOf(T3D_CLASS(Transform3D)))
        {
            order = T3D_SCENE_MGR.getComponentOrder(T3D_CLASS(Transform3D));
        }
        else if (cls->isKindOf(T3D_CLASS(Camera)))
        {
            order = T3D_SCENE_MGR.getComponentOrder(T3D_CLASS(Camera));
        }
        else if (cls->isKindOf(T3D_CLASS(Bound)))
        {
            order = T3D_SCENE_MGR.getComponentOrder(T3D_CLASS(Bound));
        }
        else if (cls->isKindOf(T3D_CLASS(Renderable)))
        {
            order = T3D_SCENE_MGR.getComponentOrder(T3D_CLASS(Renderable));
        }

        return order;
    }

    //--------------------------------------------------------------------------

    ComponentPtr SceneNode::addComponent(const Class *cls, ...)
    {
        ComponentPtr component;

        do 
        {
            // 获取组件执行顺序
            uint32_t order = getComponentOrder(cls);

            if (ComponentOrder::INVALID == order)
            {
                T3D_LOG_ERROR(LOG_TAG_COMPONENT, "Invalid component order !");
                break;
            }

            // 看看是否有同样功能的组件
            auto itr = mComponentQueue.find(order);
            if (itr != mComponentQueue.end())
            {
                T3D_LOG_ERROR(LOG_TAG_COMPONENT,
                    "Duplicated component for class %s", cls->getName());
                break;
            }

            // 创建组件对象
            ComponentCreatorPtr creator = T3D_AGENT.getComponentCreator();
            va_list args;
            va_start(args, cls);
            component = creator->createObject(1, cls, args);
            va_end(args);

            if (component == nullptr)
            {
                T3D_LOG_ERROR(LOG_TAG_COMPONENT, "Create component failed !");
                break;
            }

            // 根据顺序插入执行队列
            auto ret0 = mComponentQueue.insert(ComponentQueueValue(order, component));
            if (!ret0.second)
            {
                component = nullptr;
                T3D_LOG_ERROR(LOG_TAG_COMPONENT, 
                    "Insert component executing queue failed !");
                break;
            }

            // 缓存组件
            auto ret = mComponents.insert(ComponentsValue(cls, component));
            if (!ret.second)
            {
                component = nullptr;
                T3D_LOG_ERROR(LOG_TAG_COMPONENT, "Cache component failed !");
                break;
            }

            // 记录下几个特殊组件，方便后续快速访问，不用每次查字典
            if (ComponentOrder::TRANSFORM == order)
            {
                mTransform3D = smart_pointer_cast<Transform3D>(component);
            }
            else if (ComponentOrder::COLLIDER == order)
            {
                mCollider = smart_pointer_cast<Bound>(component);
            }
            else if (ComponentOrder::RENDERABLE == order)
            {
                mRenderable = smart_pointer_cast<Renderable>(component);

                if (mCameraMask != 0)
                {
                    if (getParent() != nullptr && mRenderable != nullptr)
                    {
                        T3D_SCENE_MGR.addSceneNode(this);
                    }
                }
            }
        } while (0);

        if (component != nullptr)
        {
            component->onAttachSceneNode(this);
        }

        return component;
    }

    //--------------------------------------------------------------------------

    ComponentPtr SceneNode::getComponent(const Class *cls) const
    {
        ComponentPtr component;
        auto itr = mComponents.find(cls);

        if (itr != mComponents.end())
        {
            component = itr->second;
        }

        return component;
    }

    //--------------------------------------------------------------------------

    void SceneNode::removeComponent(const Class *cls)
    {
        auto itr = mComponents.find(cls);

        if (itr != mComponents.end())
        {
            ComponentPtr component = itr->second;

            if (component == mRenderable)
            {
                T3D_SCENE_MGR.removeSceneNode(this);
                mRenderable = nullptr;
            }
            else if (component == mTransform3D)
            {
                mTransform3D = nullptr;
            }

            component->onDetachSceneNode(this);
            mComponents.erase(itr);
        }
    }

    //--------------------------------------------------------------------------

    void SceneNode::removeAllComponents()
    {
        auto itr = mComponents.begin();

        while (itr != mComponents.end())
        {
            if (itr->second == mRenderable)
            {
                T3D_SCENE_MGR.removeSceneNode(this);
            }

            itr->second->onDetachSceneNode(this);
            ++itr;
        }

        mComponents.clear();
    }
}
