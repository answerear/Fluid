/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2017  Answer Wong
 * For latest info, see https://github.com/asnwerear/Tiny3D
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

#ifndef __T3D_SDL_MOBILE_WINDOW_H__
#define __T3D_SDL_MOBILE_WINDOW_H__


#include "Adapter/T3DWindowInterface.h"
#include <SDL.h>

namespace Tiny3D
{
    class IWindow;

    class SDLMobileWindow : public IWindow
    {
        T3D_DISABLE_COPY(SDLMobileWindow);

    public:
        SDLMobileWindow();

        virtual ~SDLMobileWindow();

        /**
         * @brief 创建窗口.
         * @param [in] x : 窗口位置
         * @param [in] y : 窗口位置
         * @param [in] w : 窗口宽度
         * @param [in] h : 窗口高度
         * @param [in] flags : 创建窗口需要的一些标记位，可使用或操作合并标记
         * @return 创建成功返回T3D_OK.
         */
        virtual TResult create(const char *title, int32_t x, int32_t y,
                               int32_t w, int32_t h, uint32_t flags) override;

        /**
         * @brief 根据传入数据创建窗口
         * @param [in] data : 窗口依赖的数据指针
         * @param [in] needFramebuffer : 是否创建帧缓冲
         * @return 成功返回 T3D_OK
         */
        virtual TResult createFrom(const void *data) override;

        /**
         * @brief 销毁窗口
         * @return void
         */
        virtual void destroy() override;

        /**
         * @brief 获取窗口系统相关信息
         * @param [in][out] info : 返回的窗口系统相关信息
         * @return 获取成功返回true
         */
        virtual bool getSystemInfo(SysWMInfo &info) const override;

        /**
         * @brief 设置窗口图标
         * @param [in] pixels : 图标数据
         * @param [in] width : 图标宽度
         * @param [in] height : 图标高度
         * @param [in] depth : 图标色深
         * @param [in] pitch : 图标数据跨度
         * @param [in] format : 图标数据格式
         */
        virtual void setWindowIcon(void *pixels, int32_t width, int32_t height,
            int32_t depth, int32_t pitch, uint32_t format) override;

        /**
         * @brief 获取窗口宽度和高度
         */
        virtual void getWindowSize(int32_t &width, int32_t &height) const override;

        /**
         * @brief 获取色深
         */
        virtual uint32_t getColorDepth() const override;

        /**
         * @brief 获取窗口显示帧缓冲
         */
        virtual uint8_t *getFramebuffer() override;

        /**
         * @brief 获取窗口显示帧缓冲大小
         */
        virtual size_t getFramebufferSize() const override;

        /**
         * @brief 更新窗口，把帧缓冲数据更新到窗口里
         */
        virtual TResult updateWindow() override;

    protected:
        SDL_Window  *mSDLWindow;
        SDL_Surface *mSDLIconSurface;   /**< SDL 窗口图标对象 */

        uint8_t     *mFramebuffer;      /**< 窗口显示缓冲区 */
        size_t      mFramebufferSize;   /**< 帧缓冲大小 */
    };
}


#endif  /*__T3D_SDL_MOBILE_WINDOW_H__*/
