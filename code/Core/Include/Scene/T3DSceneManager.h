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


#ifndef __T3D_SCENE_MANAGER_H__
#define __T3D_SCENE_MANAGER_H__


#include "Scene/T3DSceneManagerBase.h"


namespace Tiny3D
{
    /**
     * @class   SceneManager
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API SceneManager 
        : public SceneManagerBase
        , public Singleton<SceneManager>
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static SceneManagerPtr create(SceneManagerBase *impl);
         * @brief   创建场景管理器对象
         * @param [in]  impl    : 场景管理器具体实现的对象.
         * @return  返回一个场景管理器对象.
         */
        static SceneManagerPtr create(SceneManagerBase *impl);

        /**
         * @fn  virtual ~SceneManager();
         * @brief   析构函数
         */
        virtual ~SceneManager();

        /**
         * @fn  virtual TResult update() override;
         * @brief   更新场景树，实现基类接口
         * @return  A TResult.
         * @sa  TResult SceneManagerBase::update()
         */
        virtual TResult update() override;

        /**
         * @fn  virtual TResult render(ViewportPtr viewport) override;
         * @brief   实现基类接口
         * @param   viewport    The viewport.
         * @return  A TResult.
         * @sa  TResult SceneManagerBase::render(ViewportPtr viewport)
         */
        virtual TResult render(ViewportPtr viewport) override;

        /**
         * @fn  virtual SceneNodePtr getRoot() const override;
         * @brief   实现基类接口
         * @return  The root.
         * @sa  SceneNodePtr SceneManagerBase::getRoot() const
         */
        virtual SceneNodePtr getRoot() const override;

        /**
         * @fn  virtual SceneNodePtr createSceneNode(SceneNodePtr parent, 
         *      bool autoAddTransform = true, 
         *      ID uID = Node::E_NID_AUTOMATIC) override;
         * @brief   实现基类接口
         * @param   parent              The parent.
         * @param   autoAddTransform    (Optional) True to automatically add
         *  transform.
         * @param   uID                 (Optional) The identifier.
         * @return  The new scene node.
         * @sa  Transform3DPtr SceneManagerBase::createTransform3D(
         *      SceneNodePtr parent, ID uID = Node::E_NID_AUTOMATIC)
         */
        virtual SceneNodePtr createSceneNode(SceneNodePtr parent,
            ID uID = Node::E_NID_AUTOMATIC) override;

        /**
         * @fn  TResult addRenderable(RenderablePtr renderable);
         * @brief   添加可渲染对象到对应相机队列，用于视锥体剔除
         * @param [in]  renderable  : 可渲染对象.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult addSceneNode(SceneNode *node) override;

        /**
         * @fn  TResult removeRenderable(RenderablePtr renderable);
         * @brief   根据camera mask来移除可渲染对象
         * @param [in]  renderable  : 可渲染对象.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult removeSceneNode(SceneNode *node) override;

        virtual void setComponentOrder(const Class *cls, uint32_t order) override;

        virtual uint32_t getComponentOrder(const Class *cls) const override;

        virtual const OrderMap &getComponentOrders() const override;

    protected:
        /**
         * @fn  SceneManager(SceneManagerBase *impl);
         * @brief   Constructor
         * @param [in,out]  impl    If non-null, the implementation.
         */
        SceneManager(SceneManagerBase *impl);

    protected:
        SceneManagerBasePtr     mImpl;  /**< 具体场景管理器对象 */
    };

    #define T3D_SCENE_MGR       SceneManager::getInstance()
}


#endif  /*__T3D_SCENE_MANAGER_H__*/
