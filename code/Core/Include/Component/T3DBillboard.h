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


#ifndef __T3D_BILLBOARD_H__
#define __T3D_BILLBOARD_H__


#include "Component/T3DRenderable.h"


namespace Tiny3D
{
    /**
     * @class   Billboard
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API Billboard : public Renderable
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static BillboardPtr Billboard::create(ID uID = E_CID_AUTOMATIC);
         * @brief   Creates a new BillboardPtr
         * @param   uID (Optional) The identifier.
         * @return  A BillboardPtr.
         */
        static BillboardPtr create(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual Billboard::~Billboard();
         * @brief   Destructor
         */
        virtual ~Billboard();

    protected:
        /**
         * @fn  Billboard::Billboard(ID uID = E_CID_AUTOMATIC);
         * @brief   Constructor
         * @param   uID (Optional) The identifier.
         */
        Billboard(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual ComponentPtr Billboard::clone() const override;
         * @brief   Makes a deep copy of this object
         * @return  A copy of this object.
         */
        virtual ComponentPtr clone() const override;

        /**
         * @fn  virtual TResult 
         *      Billboard::cloneProperties(ComponentPtr newObj) const override;
         * @brief   Initializes this object from the given properties
         * @param   newObj  The new object.
         * @return  A TResult.
         */
        virtual TResult cloneProperties(ComponentPtr newObj) const override;

        /**
         * @fn  virtual MaterialPtr Billboard::getMaterial() const override;
         * @brief   Gets the material
         * @return  The material.
         */
        virtual MaterialPtr getMaterial() const override;

        /**
         * @fn  virtual VertexArrayObjectPtr 
         *      Billboard::getVertexArrayObject() const override;
         * @brief   Gets vertex array object
         * @return  The vertex array object.
         */
        virtual VertexArrayObjectPtr getVertexArrayObject() const override;
    };
}


#endif  /*__T3D_BILLBOARD_H__*/
