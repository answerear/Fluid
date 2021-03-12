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


#ifndef __T3D_D3D9_RENDER_WINDOW_H__
#define __T3D_D3D9_RENDER_WINDOW_H__


#include "T3DD3D9Prerequisites.h"


namespace Tiny3D
{
    class D3D9RenderWindow : public RenderWindow
    {
    public:
        /**
         * @brief 创建渲染窗口对象
         * @param [in] name : 渲染窗口名字
         * @return 返回一个渲染窗口对象
         */
        static D3D9RenderWindowPtr create(const String &name);

        /**
         * @brief 析构函数
         */
        virtual ~D3D9RenderWindow();

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

    protected:
        D3D9RenderWindow(const String &name);

        bool checkMultiSampleQuality(LPDIRECT3D9 pD3D, D3DMULTISAMPLE_TYPE type,
            DWORD *outQuality, D3DFORMAT fBack, D3DFORMAT fDepth,
            UINT adapterNum, D3DDEVTYPE deviceType, BOOL fullScreen);

        TResult createD3D9Device(const RenderWindowCreateParam &param,
            const RenderWindowCreateParamEx &paramEx);

        Window  *mWindow;

        LPDIRECT3DDEVICE9   mD3DDevice;
    };
}



#endif  /*__T3D_D3D9_PLUGIN_H__*/
