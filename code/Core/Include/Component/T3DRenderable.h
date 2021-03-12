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


#ifndef __T3D_RENDERABLE_H__
#define __T3D_RENDERABLE_H__


#include "Component/T3DComponent.h"
#include "Render/T3DRenderContext.h"
#include "Render/T3DVertexArrayObject.h"
#include "Resource/T3DMaterial.h"


namespace Tiny3D
{
    /**
     * @class   Renderable
     * @brief   场景中 3D 可渲染对象基类，用于渲染 3D 物体
     */
    class T3D_ENGINE_API Renderable : public Component
    {
        friend class DefaultSceneMgr;

        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  virtual Renderable::~Renderable();
         * @brief   析构函数
         */
        virtual ~Renderable();

        /**
         * @fn  virtual MaterialPtr Renderable::getMaterial() const = 0;
         * @brief   获取渲染使用的材质
         * @return  返回渲染用的材质对象.
         */
        virtual MaterialPtr getMaterial() const = 0;

        /**
         * @fn  virtual VertexArrayObjectPtr 
         *      Renderable::getVertexArrayObject() const = 0;
         * @brief   获取渲染使用的VAO对象
         * @return  返回渲染数据的VAO对象.
         */
        virtual VertexArrayObjectPtr getVertexArrayObject() const = 0;

    protected:
        /**
         * @fn  Renderable::Renderable(ID uID = E_CID_AUTOMATIC);
         * @brief   构造函数
         * @param   uID (Optional) The identifier.
         */
        Renderable(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual TResult 
         *      Renderable::cloneProperties(ComponentPtr newObj) const;
         * @brief   Initializes this object from the given properties
         * @param   newObj  The new object.
         * @return  A TResult.
         */
        virtual TResult cloneProperties(ComponentPtr newObj) const;
    };
}


#endif  /*__T3D_RENDERABLE_H__*/
