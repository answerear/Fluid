/*******************************************************************************
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


#ifndef __T3D_R3D_RENDER_WINDOW_H__
#define __T3D_R3D_RENDER_WINDOW_H__


#include "T3DR3DPrerequisites.h"
#include "T3DR3DFramebuffer.h"


namespace Tiny3D
{
    class R3DRenderWindow : public RenderWindow
    {
    public:
        /**
         * @brief 创建渲染窗口对象
         * @param [in] name : 渲染窗口名字
         * @return 返回一个渲染窗口对象
         */
        static R3DRenderWindowPtr create(const String &name);

        /**
         * @brief 析构函数
         */
        virtual ~R3DRenderWindow();

        /**
         * @brief 创建渲染窗口实体
         * @param [in] param : 渲染窗口需要必要参数
         * @param [in] paramEx : 渲染窗口需要的额外参数，不同平台的额外信息可以
         *                      通过这里传递
         * @return 调用成功返回 T3D_OK
         * @remarks 具体渲染系统子类实现本接口
         */
        virtual TResult create(
            const RenderWindowCreateParam &param,
            const RenderWindowCreateParamEx &paramEx) override;

        /**
         * @brief 销毁窗口
         * @return 调用成功返回 T3D_OK
         * @remarks 具体渲染系统子类实现本接口
         */
        virtual TResult destroy() override;

        /**
         * @brief 双缓冲中交换离屏缓存到显示缓存，显示出图像
         * @return 调用成功返回 T3D_OK
         * @remarks 具体渲染系统子类实现本接口
         */
        virtual TResult swapBuffers() override;

        /**
         * @fn  virtual void R3DRenderWindow::clear(const ColorRGB &clrFill, 
         *      uint32_t clearFlags, Real depth, uint32_t stencil) override;
         * @brief   Clears this object to its blank/initial state
         * @param   clrFill     The color fill.
         * @param   clearFlags  The clear flags.
         * @param   depth       The depth.
         * @param   stencil     The stencil.
         */
        virtual void clear(const ColorRGB &clrFill, uint32_t clearFlags, 
            Real depth, uint32_t stencil) override;

        /**
         * @brief 获取帧缓冲
         * @return 返回帧缓冲地址
         */
        uint8_t *getFramebuffer() { return mWindow->getFramebuffer(); }

        /**
         * @brief 获取帧缓冲大小
         * @return 返回帧缓冲大小
         */
        size_t getFramebufferSize() const 
        { 
            return mWindow->getFramebufferSize(); 
        }

    protected:
        /**
         * @brief 构造函数
         */
        R3DRenderWindow(const String &name);

        Window  *mWindow;
    };
}


#endif  /*__T3D_R3D_RENDER_WINDOW_H__*/
