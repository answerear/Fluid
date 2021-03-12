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


#ifndef __T3D_LIGHT_H__
#define __T3D_LIGHT_H__


#include "Component/T3DTransform3D.h"


namespace Tiny3D
{
    /**
     * @class   Light
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API Light : public Component
    {
        T3D_DECLARE_CLASS();
    public:
        /**
         * @fn  static LightPtr Light::create(ID uID = E_CID_AUTOMATIC);
         * @brief   Creates a new LightPtr
         * @param   uID (Optional) The identifier.
         * @return  A LightPtr.
         */
        static LightPtr create(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual Light::~Light();
         * @brief   Destructor
         */
        virtual ~Light();

    protected:
        /**
         * @fn  Light::Light(ID uID = E_CID_AUTOMATIC);
         * @brief   Constructor
         * @param   uID (Optional) The identifier.
         */
        Light(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual ComponentPtr Light::clone() const override;
         * @brief   Makes a deep copy of this object
         * @return  A copy of this object.
         */
        virtual ComponentPtr clone() const override;

        /**
         * @fn  virtual TResult 
         *      Light::cloneProperties(ComponentPtr newObj) const override;
         * @brief   Initializes this object from the given properties
         * @param   newObj  The new object.
         * @return  A TResult.
         */
        virtual TResult cloneProperties(ComponentPtr newObj) const override;
    };
}


#endif  /*__T3D_LIGHT_H__*/
