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


#ifndef __T3D_SCENE_NODE_H__
#define __T3D_SCENE_NODE_H__


#include "Kernel/T3DNode.h"


namespace Tiny3D
{
    /**
     * @class   SceneNode
     * @brief   Scene Graph 中的结点基类
     */
    class T3D_ENGINE_API SceneNode : public Node
    {
        friend class DefaultSceneMgr;

        T3D_DISABLE_COPY(SceneNode);
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static SceneNodePtr SceneNode::create(ID uID = E_NID_AUTOMATIC);
         * @brief   Creates a new SceneNodePtr
         * @param   uID (Optional) The identifier.
         * @return  A SceneNodePtr.
         */
        static SceneNodePtr create(ID uID = E_NID_AUTOMATIC);

        /**
         * @fn  virtual SceneNode::~SceneNode();
         * @brief   析构函数
         */
        virtual ~SceneNode();

        /**
         * @fn  virtual Node::Type SceneNode::getNodeType() const override;
         * @brief   Gets node type
         * @return  The node type.
         */
        virtual Node::Type getNodeType() const override;

        /**
         * @fn  virtual NodePtr SceneNode::clone() const override;
         * @brief   Makes a deep copy of this object
         * @return  A copy of this object.
         */
        virtual NodePtr clone() const override;

        /**
         * @fn  virtual void SceneNode::setVisible(bool visible);
         * @brief   设置结点是否可见
         * @param [in]  visible : 可见标记.
         * @sa  bool isVisible() const
         * @remarks 通过本接口设置了不可见，则会直接在渲染流水线上移除该结点以及 
         *          所有子结点，不参与渲染，但是update更新还是有效的。.
         */
        virtual void setVisible(bool visible);

        /**
         * @fn  bool SceneNode::isVisible() const;
         * @brief   获取结点可见性
         * @return  返回结点可见性.
         * @sa  void setVisible(bool visible)
         */
        bool isVisible() const;

        /**
         * @fn  virtual void SceneNode::setEnabled(bool enabled);
         * @brief   设置结点是否可用
         * @param [in]  enabled : 可用标记.
         * @sa  bool isEnabled() const
         * @remarks 不可用的结点，update是不会调用的，同时不可用的结点也看不见.
         */
        virtual void setEnabled(bool enabled);

        /**
         * @fn  bool SceneNode::isEnabled() const;
         * @brief   获取结点可用性
         * @return  返回结点可用性.
         * @sa  void setEnabled(bool enabled)
         */
        bool isEnabled() const;

        /**
         * @fn  virtual void SceneNode::setCameraMask(uint32_t mask);
         * @brief   设置结点使用对应相机的掩码
         * @param   mask    The mask.
         * @sa  uint32_t getCameraMask() const
         * @remarks 只有跟相机掩码一致的结点才能在对应相机中渲染。 相机掩码可以 
         *          通过“或”操作同时设置多个。.
         */
        virtual void setCameraMask(uint32_t mask);

        /**
         * @fn  uint32_t SceneNode::getCameraMask() const;
         * @brief   获取结点对应相机的掩码
         * @return  返回相机掩码.
         * @sa  void setCameraMask(uint32_t mask)
         */
        uint32_t getCameraMask() const;

        /**
         * @fn  virtual void SceneNode::visit();
         * @brief   递归遍历
         * @remarks 递归遍历，遍历到的结点会调用 updateTransform() 接口.
         */
        virtual void visit();

        /**
         * @fn  virtual void SceneNode::frustumCulling(BoundPtr bound, 
         *      RenderQueuePtr queue);
         * @brief   视景体外物体剔除，递归调用所有子结点
         * @param [in]  bound   : 视锥体碰撞体.
         * @param [in]  queue   : 渲染队列.
         * @note
         *  - 如果本身不在视景体内，则所有子结点上的物体都会被剔除，不参与渲染；
         *  - 如果本身在视景体内，则会递归调用子结点判断；
         *  - 如果不是可渲染结点，则无法加入的RenderQueue中；.
         */
        virtual void frustumCulling(BoundPtr bound, RenderQueuePtr queue);

        /**
         * @fn  ComponentPtr SceneNode::addComponent(const String &type);
         * @brief   Adds a component
         * @param   type    The type.
         * @return  A ComponentPtr.
         */
        ComponentPtr addComponent(const Class *cls, ...);

        /**
         * @fn  ComponentPtr SceneNode::getComponent(const String &type) const;
         * @brief   Gets a component
         * @param   type    The type.
         * @return  The component.
         */
        ComponentPtr getComponent(const Class *cls) const;

        /**
         * @fn  void SceneNode::removeComponent(const String &type);
         * @brief   Removes the component described by type
         * @param   type    The type.
         */
        void removeComponent(const Class *cls);

        /**
         * @fn  void SceneNode::removeAllComponents();
         * @brief   Removes all components
         */
        void removeAllComponents();

        typedef TMap<const Class*, ComponentPtr>    Components;
        typedef Components::iterator                ComponentsItr;
        typedef Components::const_iterator          ComponentsConstItr;
        typedef Components::value_type              ComponentsValue;

        /**
         * @fn  const Components SceneNode::&getComponents() const
         * @brief   Gets the components
         * @return  The components.
         */
        const Components &getComponents() const { return mComponents; }

        Transform3D *getTransform3D() const { return mTransform3D; }

        Renderable *getRenderable() const { return mRenderable; }

    protected:
        /**
         * @fn  SceneNode::SceneNode(ID uID = E_NID_AUTOMATIC);
         * @brief   默认构造函数
         * @param [in]  uID (Optional) : 标识结点的唯一ID，默认值是由引擎自动
         *              生成唯一ID
         * @note 这里构造函数是protected访问权限，主要是为了防止外部直接new来构
         *       造对象， 本类是无法构造直接对象，请使用各派生类的 create 代替
         *       new 来构造对象.
         */
        SceneNode(ID uID = E_NID_AUTOMATIC);

        /**
         * @fn  virtual void SceneNode::update();
         * @brief   更新本身的变换
         * @note 派生类重写本函数以实现具体的变换更新策略.
         */
        virtual void update();

        /**
         * @fn  virtual TResult 
         *      SceneNode::cloneProperties(NodePtr node) const override;
         * @brief   克隆结点属性
         * @param [in]  node    : 目标结点.
         * @return  void
         * @note 复制本结点所有属性给目标结点node.
         */
        virtual TResult cloneProperties(NodePtr node) const override;

        uint32_t getComponentOrder(const Class *cls) const;

    private:
        typedef TMap<uint32_t, Component*>      ComponentQueue;
        typedef ComponentQueue::iterator        ComponentQueueItr;
        typedef ComponentQueue::const_iterator  ComponentQueueConstItr;
        typedef ComponentQueue::value_type      ComponentQueueValue;

        bool        mIsVisible;     /**< 结点可见性 */
        bool        mIsEnabled;     /**< 结点可用性 */
        bool        mIsDirty;
        uint32_t    mCameraMask;    /**< 相机掩码 */

        ComponentQueue  mComponentQueue;/**< The components */
        Components      mComponents;    /**< */
        Transform3D     *mTransform3D;  /**< The transform 3D */
        Bound           *mCollider;
        Renderable      *mRenderable;   /**< The renderable */

        SceneNode       *mPrev;
        SceneNode       *mNext;
    };
}


#include "T3DSceneNode.inl"


#endif  /*__T3D_SCENE_NODE_H__*/
