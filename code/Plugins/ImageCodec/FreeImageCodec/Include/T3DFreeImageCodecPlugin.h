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


#ifndef __T3D_FREEIMAGE_CODEC_PLUGIN_H__
#define __T3D_FREEIMAGE_CODEC_PLUGIN_H__


#include "T3DFreeImageCodecPrerequisites.h"


namespace Tiny3D
{
    /**
     * @brief 通用图片编解码插件
     */
    class FreeImageCodecPlugin : public Plugin
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 默认构造函数
         */
        FreeImageCodecPlugin();

        /**
         * @brief 析构函数
         */
        virtual ~FreeImageCodecPlugin();

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
        String              mName;          /**< 插件名称 */
        FreeImageCodecPtr   mImageCodec;    /**< 图像编解码器 */
    };

}


#endif  /*__T3D_FREEIMAGE_CODEC_PLUGIN_H__*/
