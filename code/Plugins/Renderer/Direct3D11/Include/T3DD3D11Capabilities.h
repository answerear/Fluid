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


#ifndef __T3D_D3D11_CAPABILITIES_H__
#define __T3D_D3D11_CAPABILITIES_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    /**
     * @class   D3D11Capabilities
     * @brief   DirectX 11 渲染器渲染能力组
     */
    class D3D11Capabilities : public RenderCapabilities
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief   创建一个 D3D11 渲染器相关能力组对象
         * @returns 调用成功返回新建 D3D11 能力组对象
         */
        static D3D11CapabilitiesPtr create();

        /**
         * @fn  virtual D3D11Capabilities::~D3D11Capabilities();
         * @brief   Destructor
         */
        virtual ~D3D11Capabilities();

    protected:
        /**
         * @fn  D3D11Capabilities::D3D11Capabilities();
         * @brief   Default constructor
         */
        D3D11Capabilities();

        /**
         * @fn  virtual TResult D3D11Capabilities::init() override;
         * @brief   Initializes this object
         * @return  A TResult.
         */
        virtual TResult init() override;
    };
}


#endif  /*__T3D_D3D11_CAPABILITIES_H__*/
