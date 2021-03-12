﻿/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2019  Answer Wong
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


#ifndef __T3D_R3D_PLUGIN_H__
#define __T3D_R3D_PLUGIN_H__


#include "T3DR3DPrerequisites.h"


namespace Tiny3D
{
    class R3DPlugin : public Plugin
    {
    public:
        /**
         * @brief 默认构造函数
         */
        R3DPlugin();

        /**
         * @brief 析构函数
         */
        virtual ~R3DPlugin();

        /**
         * @brief 获取插件名称
         */
        virtual const String &getName() const override;

        /**
         * @brief 安装插件
         */
        virtual TResult install() override;

        /**
         * @brief 启动插件
         */
        virtual TResult startup() override;

        /**
         * @brief 关闭插件
         */
        virtual TResult shutdown() override;

        /**
         * @brief 卸载插件
         */
        virtual TResult uninstall() override;

    protected:
        String      mName;
        RendererPtr mRenderer;
    };
}


#endif  /*__T3D_R3D_PLUGIN_H__*/
