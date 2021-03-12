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


#ifndef __T3D_COMPONENT_H__
#define __T3D_COMPONENT_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Kernel/T3DObject.h"


namespace Tiny3D
{
    /**
     * @class   Component
     * @brief   组件类
     */
    class T3D_ENGINE_API Component : public Object
    {
        friend class SceneNode;

        T3D_DISABLE_COPY(Component);
        T3D_DECLARE_CLASS();

    public:
        /**
         * @enum    ComponentID
         * @brief   Values that represent component Identifiers
         */
        enum ComponentID : uint32_t
        {
            E_CID_AUTOMATIC = 0xFFFFFFFF,   /**< 自动生成ID */
            E_CID_INVALID = 0,              /**< 无效ID */
        };

        /**
         * @fn  virtual Component::~Component();
         * @brief   析构函数
         */
        virtual ~Component();

        /**
         * @fn  virtual ComponentPtr Component::clone() const = 0;
         * @brief   Makes a deep copy of this object
         * @return  A copy of this object.
         */
        virtual ComponentPtr clone() const = 0;

        /**
         * @fn  ID Component::getID() const
         * @brief   Gets the identifier
         * @return  The identifier.
         */
        ID getID() const { return mID; }

        /**
         * @fn  SceneNode Component::*getSceneNode() const
         * @brief   Gets scene node
         * @return  Null if it fails, else the scene node.
         */
        SceneNode *getSceneNode() const { return mSceneNode; }

    protected:
        /**
         * @fn  Component::Component();
         * @brief   构造函数
         */
        Component(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  ID Component::makeGlobalID() const;
         * @brief   Makes global identifier
         * @return  An ID.
         */
        ID makeGlobalID() const;

        /**
         * @fn  virtual TResult 
         *      Component::cloneProperties(ComponentPtr newObj) const;
         * @brief   Initializes this object from the given properties
         * @param   newObj  The new object.
         * @return  A TResult.
         */
        virtual TResult cloneProperties(ComponentPtr newObj) const;

        /**
         * @fn  virtual void Component::onAttachSceneNode(SceneNode *node);
         * @brief   Executes the attach scene node action
         * @param [in,out]  node    If non-null, the node.
         */
        virtual void onAttachSceneNode(SceneNode *node);

        /**
         * @fn  virtual void Component::onDetachSceneNode(SceneNode *node);
         * @brief   Executes the detach scene node action
         * @param [in,out]  node    If non-null, the node.
         */
        virtual void onDetachSceneNode(SceneNode *node);

        /**
         * @fn  virtual void Component::update();
         * @brief   Updates this object
         */
        virtual void update();

    protected:
        ID          mID;            /**< The identifier */
        SceneNode   *mSceneNode;    /**< The scene node */
    };
}


#endif  /*__T3D_COMPONENT_H__*/
