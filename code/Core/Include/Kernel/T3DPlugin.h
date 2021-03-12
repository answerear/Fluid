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


#ifndef __T3D_PLUGIN_H__
#define __T3D_PLUGIN_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Kernel/T3DObject.h"


namespace Tiny3D
{
    /**
     * @class   Plugin
     * @brief   插件基类，所有插件均需从此类派生并实现其接口
     */
    class T3D_ENGINE_API Plugin : public Object
    {
        T3D_DECLARE_INTERFACE(Plugin);
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  virtual const String Plugin::&getName() const = 0;
         * @brief   获取插件名称
         * @return  The name.
         */
        virtual const String &getName() const = 0;

        /**
         * @fn  virtual TResult Plugin::install() = 0;
         * @brief   安装插件
         * @return  A TResult.
         */
        virtual TResult install() = 0;

        /**
         * @fn  virtual TResult Plugin::startup() = 0;
         * @brief   启动插件
         * @return  A TResult.
         */
        virtual TResult startup() = 0;

        /**
         * @fn  virtual TResult Plugin::shutdown() = 0;
         * @brief   关闭插件
         * @return  A TResult.
         */
        virtual TResult shutdown() = 0;

        /**
         * @fn  virtual TResult Plugin::uninstall() = 0;
         * @brief   卸载插件
         * @return  A TResult.
         */
        virtual TResult uninstall() = 0;
    };
}


#endif  /*__T3D_PLUGIN_H__*/
