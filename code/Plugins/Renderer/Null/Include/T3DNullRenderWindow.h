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


#ifndef __T3D_D3D11_RENDER_WINDOW_H__
#define __T3D_D3D11_RENDER_WINDOW_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    /**
     * @class   D3D11RenderWindow
     * @brief   DirectX 11 渲染窗口.
     */
    class D3D11RenderWindow : public RenderWindow
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 创建渲染窗口对象
         * @param [in] name : 渲染窗口名字
         * @return 返回一个渲染窗口对象
         */
        static D3D11RenderWindowPtr create(const String &name);

        /**
         * @fn  virtual D3D11RenderWindow::~D3D11RenderWindow();
         * @brief   析构函数
         */
        virtual ~D3D11RenderWindow();

        /**
         * @fn  virtual TResult D3D11RenderWindow::create(
         *      const RenderWindowCreateParam &param, 
         *      const RenderWindowCreateParamEx &paramEx) override;
         * @brief   创建渲染窗口实体
         * @param [in]  param   : 渲染窗口需要必要参数.
         * @param [in]  paramEx : 渲染窗口需要的额外参数，不同平台的额外信息可以
         *   通过这里传递.
         * @return  调用成功返回 T3D_OK.
         * @remarks  具体渲染系统子类实现本接口.
         */
        virtual TResult create(
            const RenderWindowCreateParam &param,
            const RenderWindowCreateParamEx &paramEx) override;

        /**
         * @fn  virtual TResult D3D11RenderWindow::destroy() override;
         * @brief   销毁窗口
         * @return  调用成功返回 T3D_OK.
         * @remarks  具体渲染系统子类实现本接口.
         */
        virtual TResult destroy() override;

        /**
         * @fn  virtual TResult D3D11RenderWindow::swapBuffers() override;
         * @brief   双缓冲中交换离屏缓存到显示缓存，显示出图像
         * @return  调用成功返回 T3D_OK.
         * @remarks  具体渲染系统子类实现本接口.
         */
        virtual TResult swapBuffers() override;

        /**
         * @fn  virtual void D3D11RenderWindow::clear(const ColorRGB &clrFill, 
         *      uint32_t clearFlags, Real depth, uint32_t stencil) override;
         * @brief   Clears this object to its blank/initial state
         * @param   clrFill     The color fill.
         * @param   clearFlags  The clear flags.
         * @param   depth       The depth.
         * @param   stencil     The stencil.
         */
        virtual void clear(const ColorRGB &clrFill, uint32_t clearFlags, 
            Real depth, uint32_t stencil) override;

    protected:
        /**
         * @fn  D3D11RenderWindow::D3D11RenderWindow(const String &name);
         * @brief   Constructor
         * @param   name    The name.
         */
        D3D11RenderWindow(const String &name);

        /**
         * @fn  TResult D3D11RenderWindow::loadIcon(const String &iconPath);
         * @brief   加载图标
         * @param   iconPath    Full pathname of the icon file.
         * @return  The icon.
         */
        TResult loadIcon(const String &iconPath);

        /**
         * @fn  TResult D3D11RenderWindow::setupD3D11Environment(
         *      const RenderWindowCreateParam &param, 
         *      const RenderWindowCreateParamEx &paramEx);
         * @brief   建立 D3D11 相关环境
         * @param   param   The parameter.
         * @param   paramEx The parameter exception.
         * @return  A TResult.
         */
        TResult setupD3D11Environment(
            const RenderWindowCreateParam &param,
            const RenderWindowCreateParamEx &paramEx);

        /**
         * @fn  TResult D3D11RenderWindow::createSwapChain(UINT uWidth, 
         *      UINT uHeight, bool bFullscreen, UINT uMSAACount, 
         *      UINT uMSAAQuality, DXGI_FORMAT format);
         * @brief   创建 D3D11 交换链
         * @param   uWidth          The width.
         * @param   uHeight         The height.
         * @param   bFullscreen     True to fullscreen.
         * @param   uMSAACount      Number of msaas.
         * @param   uMSAAQuality    The msaa quality.
         * @param   format          Describes the format to use.
         * @return  The new swap chain.
         */
        TResult createSwapChain(UINT uWidth, UINT uHeight, bool bFullscreen,
            UINT uMSAACount, UINT uMSAAQuality, DXGI_FORMAT format);

        /**
         * @fn  TResult D3D11RenderWindow::createRenderTargetView();
         * @brief   创建渲染目标视图
         * @return  The new render target view.
         */
        TResult createRenderTargetView();

        /**
         * @fn  TResult D3D11RenderWindow::createDepthStencilView(UINT uWidth, 
         *      UINT uHeight, UINT uMSAACount, UINT uMSAAQuality);
         * @brief   创建深度和模板缓冲区视图
         * @param   uWidth          The width.
         * @param   uHeight         The height.
         * @param   uMSAACount      Number of msaas.
         * @param   uMSAAQuality    The msaa quality.
         * @return  The new depth stencil view.
         */
        TResult createDepthStencilView(UINT uWidth, UINT uHeight,
            UINT uMSAACount, UINT uMSAAQuality);

    protected:
        Window                  *mWindow;       /**< The window */

        IDXGISwapChain          *mD3DSwapChain; /**< The d 3D swap chain */
        ID3D11RenderTargetView  *mD3DRTView;    /**< The d 3D right view */
        ID3D11DepthStencilView  *mD3DDSView;    /**< The d 3D ds view */
    };
}



#endif  /*__T3D_D3D11_RENDER_WINDOW_H__*/
