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


#ifndef __T3D_RENDER_WINDOW_H__
#define __T3D_RENDER_WINDOW_H__


#include "Render/T3DRenderTarget.h"


namespace Tiny3D
{
    /**
     * @brief 创建窗口需要的必要数据
     */
    struct RenderWindowCreateParam
    {
        int32_t windowLeft;     /**< 窗口横向坐标位置，全屏窗口忽略该参数 */
        int32_t windowTop;      /**< 窗口纵向坐标位置，全屏窗口忽略该参数 */
        int32_t windowWidth;    /**< 窗口宽度 */
        int32_t windowHeight;   /**< 窗口高度 */
        int32_t colorDepth;     /**< 窗口色深 */
        String  windowTitle;    /**< 窗口标题 */
        String  iconPath;       /**< 图标文件路径 */
        bool    fullscreen;     /**< 是否全屏，终端平台忽略该参数 */
    };


    /**
     * @brief 创建窗口需要的额外数据
     */
    typedef VariantMap  RenderWindowCreateParamEx;


    /**
     * @brief 渲染窗口
     */
    class T3D_ENGINE_API RenderWindow : public RenderTarget
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 析构函数
         */
        virtual ~RenderWindow();

        /**
         * @brief 获取渲染目标类型
         * @remarks 实现基类接口
         */
        virtual Type getType() const override;

        /**
         * @brief 渲染
         * @remarks 重写RenderTarget::update()
         * @see RenderTarget::update()
         */
        virtual void render() override;

        /**
         * @brief 创建渲染窗口实体
         * @param [in] name : 渲染目标名称
         * @param [in] param : 渲染窗口需要必要参数
         * @param [in] paramEx : 渲染窗口需要的额外参数，不同平台的额外信息可以
         *                      通过这里传递
         * @return 调用成功返回 T3D_OK
         * @remarks 具体渲染系统子类实现本接口
         */
        virtual TResult create(
            const RenderWindowCreateParam &param,
            const RenderWindowCreateParamEx &paramEx) = 0;

        /**
         * @brief 销毁窗口
         * @return 调用成功返回 T3D_OK
         * @remarks 具体渲染系统子类实现本接口
         */
        virtual TResult destroy() = 0;

        /**
         * @brief 双缓冲中交换离屏缓存到显示缓存，显示出图像
         * @return 调用成功返回 T3D_OK
         * @remarks 具体渲染系统子类实现本接口
         */
        virtual TResult swapBuffers() = 0;

        /**
         * @brief 获取是否全屏窗口
         */
        virtual bool isFullscreen() const;

    protected:
        /**
         * @brief 构造函数
         */
        RenderWindow(const String &name);
    };
}


#endif  /*__T3D_RENDER_WINDOW_H__*/
