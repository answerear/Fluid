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


#ifndef __T3D_SCENE_MANAGER_BASE_H__
#define __T3D_SCENE_MANAGER_BASE_H__


#include "Scene/T3DSceneNode.h"
#include "Component/T3DQuad.h"


namespace Tiny3D
{
    /**
     * @class   SceneManagerBase
     * @brief   场景管理基类
     * @remarks 可以根据不同场景管理算法实现各自的场景插件.
     */
    class T3D_ENGINE_API SceneManagerBase : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        typedef TMap<const Class *, uint32_t>   OrderMap;
        typedef OrderMap::iterator              OrderMapItr;
        typedef OrderMap::const_iterator        OrderMapConstItr;
        typedef OrderMap::value_type            OrderMapValue;


        /**
         * @fn  virtual SceneManagerBase::~SceneManagerBase();
         * @brief   析构函数
         */
        virtual ~SceneManagerBase();

        /**
         * @fn  virtual TResult SceneManagerBase::update() = 0;
         * @brief   更新场景树
         * @return  调用成功返回 T3D_OK.
         * @remarks 场景插件实现本接口，实现自己的更新逻辑.
         */
        virtual TResult update() = 0;

        /**
         * @fn  virtual TResult 
         *      SceneManagerBase::render(ViewportPtr viewport) = 0;
         * @brief   渲染场景
         * @param [in]  viewport    : 渲染的视口对象.
         * @return  调用成功返回 T3D_OK.
         * @remarks 场景插件实现本接口，实现自己的渲染逻辑.
         */
        virtual TResult render(ViewportPtr viewport) = 0;

        /**
         * @fn  virtual SceneNodePtr SceneManagerBase::getRoot() const = 0;
         * @brief   获取场景根结点
         * @return  返回场景根结点对象.
         * @remarks 场景插件实现本接口，实现自己的更新和渲染逻辑.
         */
        virtual SceneNodePtr getRoot() const = 0;

        /**
         * @fn  virtual SceneNodePtr SceneManagerBase::createSceneNode(
         *      SceneNodePtr parent, bool autoAddTransform = true, ID 
         *      uID = Node::E_NID_AUTOMATIC) = 0;
         * @brief   Creates scene node
         * @param   parent              The parent.
         * @param   autoAddTransform    (Optional) True to automatically add
         *  transform.
         * @param   uID                 (Optional) The identifier.
         * @return  The new scene node.
         */
        virtual SceneNodePtr createSceneNode(SceneNodePtr parent,
            ID uID = Node::E_NID_AUTOMATIC) = 0;

        /**
         * @fn  TResult addRenderable(RenderablePtr renderable);
         * @brief   添加可渲染对象到对应相机队列，用于视锥体剔除
         * @param [in]  renderable  : 可渲染对象.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult addSceneNode(SceneNode *node) = 0;

        /**
         * @fn  TResult removeRenderable(RenderablePtr renderable);
         * @brief   根据camera mask来移除可渲染对象
         * @param [in]  renderable  : 可渲染对象.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult removeSceneNode(SceneNode *node) = 0;

        virtual void setComponentOrder(const Class *cls, uint32_t order) = 0;

        virtual uint32_t getComponentOrder(const Class *cls) const = 0;

        virtual const OrderMap &getComponentOrders() const = 0;

    protected:
        /**
         * @fn  SceneManagerBase::SceneManagerBase();
         * @brief   构造函数
         */
        SceneManagerBase();
    };
}


#endif  /*__T3D_SCENE_MANAGER_BASE_H__*/
