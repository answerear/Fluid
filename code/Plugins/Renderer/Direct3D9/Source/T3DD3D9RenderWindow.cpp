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


#include "T3DD3D9RenderWindow.h"
#include "T3DD3D9Error.h"
#include "T3DD3D9Renderer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    D3D9RenderWindowPtr D3D9RenderWindow::create(const String &name)
    {
        D3D9RenderWindowPtr window = new D3D9RenderWindow(name);
        window->release();
        return window;
    }

    //--------------------------------------------------------------------------

    D3D9RenderWindow::D3D9RenderWindow(const String &name)
        : RenderWindow(name)
        , mWindow(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    D3D9RenderWindow::~D3D9RenderWindow()
    {
    }

    //--------------------------------------------------------------------------

    TResult D3D9RenderWindow::create(const RenderWindowCreateParam &param,
        const RenderWindowCreateParamEx &paramEx)
    {
        TResult ret = T3D_OK;

        do
        {
            if (mWindow != nullptr)
            {
                // 窗口已经创建
                ret = T3D_ERR_D3D9_WINDOW_ALREADY;
                T3D_LOG_ERROR(LOG_TAG_D3D9RENDERER, "Render window already \
                     created !");
                break;
            }

            mWindow = new Window();

            // 创建窗口
            void *externalWnd = nullptr;
            auto itr = paramEx.find("externalHandle");
            if (itr != paramEx.end())
            {
                externalWnd = (void *)itr->second.uint64Value();
            }

            if (externalWnd != nullptr)
            {
                // 外部创建的窗口，这里关联上
                ret = mWindow->createFrom(externalWnd);
            }
            else
            {
                // 自己创建窗口对象
                uint32_t flags = Window::WINDOW_SHOWN;
                if (param.fullscreen)
                {
                    flags |= Window::WINDOW_FULLSCREEN;
                }

                String title = param.windowTitle + " - " 
                    + D3D9_RENDERER.getName();
                ret = mWindow->create(title.c_str(),
                    param.windowLeft, param.windowTop,
                    param.windowWidth, param.windowHeight, flags);
                if (ret != T3D_OK)
                {
                    T3D_LOG_ERROR(LOG_TAG_D3D9RENDERER, "Create native window\
                        failed !");
                    break;
                }
            }

            // 加载图标资源
            Image image;
            ret = image.load(param.iconPath);
            if (ret != T3D_OK)
            {
                T3D_LOG_ERROR(LOG_TAG_D3D9RENDERER, "Load icon image [%s] \
                    failed !", param.iconPath.c_str());
                break;
            }

            // 设置窗口图标
            Window::WindowIcon icon;
            icon.pixels = image.getData();
            icon.width = image.getWidth();
            icon.height = image.getHeight();
            icon.depth = image.getBPP();
            icon.pitch = image.getPitch();

            switch (image.getFormat())
            {
            case E_PF_PALETTE8:
                icon.format = Window::PIXEL_FORMAT_INDEX8;
                break;
            case E_PF_A1R5G5B5:
                icon.format = Window::PIXEL_FORMAT_ARGB1555;
                break;
            case E_PF_A4R4G4B4:
                icon.format = Window::PIXEL_FORMAT_ARGB4444;
                break;
            case E_PF_R5G6B5:
                icon.format = Window::PIXEL_FORMAT_RGB565;
                break;
            case E_PF_R8G8B8:
                icon.format = Window::PIXEL_FORMAT_RGB24;
                break;
            case E_PF_A8R8G8B8:
                icon.format = Window::PIXEL_FORMAT_ARGB8888;
                break;
            default:
                break;
            }

            if (ret != T3D_OK)
            {
                ret = T3D_ERR_D3D9_UNSUPPORT_FORMAT_ICON;
                T3D_LOG_ERROR(LOG_TAG_D3D9RENDERER, "Do not support icon [%s] \
                    format !", param.iconPath.c_str());
                break;
            }

            mWindow->setWindowIcon(icon);

            mWidth = param.windowWidth;
            mHeight = param.windowHeight;
            mColorDepth = mWindow->getColorDepth();
            mPitch = Image::calcPitch(mWidth, mColorDepth);

            ret = createD3D9Device(param, paramEx);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D9RenderWindow::destroy()
    {
        TResult ret = T3D_OK;

        do
        {
            if (mWindow == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_D3D9RENDERER, "Invalid window pointer !");
                break;
            }

            D3D_SAFE_RELEASE(mD3DDevice);

            mWindow->destroy();

            T3D_SAFE_DELETE(mWindow);

            ret = T3D_OK;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D9RenderWindow::swapBuffers()
    {
        TResult ret = T3D_OK;

        do
        {
            if (mD3DDevice == nullptr)
            {
                T3D_LOG_ERROR(LOG_TAG_D3D9RENDERER, "Direct3DDevice9 has not \
                    created !");
                break;
            }

            HRESULT hr = mD3DDevice->Present(NULL, NULL, 0, NULL);
            if (FAILED(hr))
            {

            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool D3D9RenderWindow::checkMultiSampleQuality(LPDIRECT3D9 pD3D,
        D3DMULTISAMPLE_TYPE type, DWORD *outQuality, D3DFORMAT fBack,
        D3DFORMAT fDepth, UINT adapterNum, D3DDEVTYPE deviceType,
        BOOL fullScreen)
    {
        if (SUCCEEDED(pD3D->CheckDeviceMultiSampleType(
            adapterNum,
            deviceType, fBack,
            fullScreen, type, outQuality)))
            return true;
        else
            return false;
    }

    //--------------------------------------------------------------------------

    TResult D3D9RenderWindow::createD3D9Device(
        const RenderWindowCreateParam &param,
        const RenderWindowCreateParamEx &paramEx)
    {
        TResult ret = T3D_OK;

        do 
        {
            LPDIRECT3D9 pD3D = D3D9_RENDERER.getD3D();
            UINT uAdapter = 0;
            D3DADAPTER_IDENTIFIER9 d3dai;
            D3DDISPLAYMODE d3ddm;
            pD3D->GetAdapterIdentifier(uAdapter, 0, &d3dai);
            pD3D->GetAdapterDisplayMode(uAdapter, &d3ddm);

            D3DPRESENT_PARAMETERS d3dpp;
            memset(&d3dpp, 0, sizeof(d3dpp));

            D3DDEVTYPE devType = D3DDEVTYPE_HAL;

            d3dpp.BackBufferCount = 1;
            d3dpp.EnableAutoDepthStencil = TRUE;

            bool vsync = paramEx.at("VSync").boolValue();
            if (vsync)
                d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
            else
                d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

            d3dpp.Windowed = !param.fullscreen;
            d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

            int32_t width, height;
            mWindow->getWindowSize(width, height);

            if (param.fullscreen)
            {
                d3dpp.BackBufferWidth = width;
                d3dpp.BackBufferHeight = height;
                d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

                if (mWindow->getColorDepth() > 16)
                    d3dpp.BackBufferFormat = D3DFMT_X8B8G8R8;
                else
                    d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
            }
            else
            {
                d3dpp.BackBufferWidth = width;
                d3dpp.BackBufferHeight = height;
                d3dpp.BackBufferFormat = d3ddm.Format;
            }

            if (mWindow->getColorDepth() > 16)
            {
                // Try to create a 32-bit depth, 8-bit stencil
                if (FAILED(pD3D->CheckDeviceFormat(uAdapter,
                    devType, d3dpp.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
                    D3DRTYPE_SURFACE, D3DFMT_D24S8)))
                {
                    // Bugger, no 8-bit hardware stencil, just try 32-bit zbuffer 
                    if (FAILED(pD3D->CheckDeviceFormat(uAdapter,
                        devType, d3dpp.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
                        D3DRTYPE_SURFACE, D3DFMT_D32)))
                    {
                        // Jeez, what a naff card. Fall back on 16-bit depth buffering
                        d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
                    }
                    else
                        d3dpp.AutoDepthStencilFormat = D3DFMT_D32;
                }
                else
                {
                    // Woohoo!
                    if (SUCCEEDED(pD3D->CheckDepthStencilMatch(uAdapter, 
                        devType, d3dpp.BackBufferFormat, 
                        d3dpp.BackBufferFormat, D3DFMT_D24X8)))
                    {
                        d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
                    }
                    else
                        d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
                }
            }
            else
            {
                // 16-bit depth, software stencil
                d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
            }

            DWORD dwMultiSampleQuality
                = (DWORD)paramEx.at("MultiSampleQuality").longValue();

            if (dwMultiSampleQuality < 2) // NONE
                dwMultiSampleQuality = 0;
            if (dwMultiSampleQuality > 16) // MAX
                dwMultiSampleQuality = 16;

            if (dwMultiSampleQuality &&
                checkMultiSampleQuality(
                    pD3D,
                    D3DMULTISAMPLE_NONMASKABLE,
                    &dwMultiSampleQuality,
                    d3dpp.BackBufferFormat,
                    d3dpp.AutoDepthStencilFormat,
                    uAdapter,
                    devType,
                    param.fullscreen))
            {
                d3dpp.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
                d3dpp.MultiSampleQuality
                    = dwMultiSampleQuality ? dwMultiSampleQuality - 1 : NULL;
            }
            else
            {
                d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
                d3dpp.MultiSampleQuality = NULL;
            }

            SysWMInfo info;
            mWindow->getSystemInfo(info);
            HWND hWnd = (HWND)info.hWnd;
            HRESULT hr = pD3D->CreateDevice(uAdapter, devType, hWnd,
                D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &mD3DDevice);
            if (SUCCEEDED(hr))
            {
//             mD3DDevice->GetRenderTarget(0, &mpRenderSurface);
//             mD3DDevice->GetDepthStencilSurface( &mpRenderZBuffer );
            }
            else
            {
                hr = pD3D->CreateDevice(uAdapter, devType, hWnd,
                    D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &mD3DDevice);
                if (SUCCEEDED(hr))
                {
//                 mpD3DDevice->GetRenderTarget( 0, &mpRenderSurface );
//                 mpD3DDevice->GetDepthStencilSurface( &mpRenderZBuffer );
                }
                else
                {
                    hr = pD3D->CreateDevice(uAdapter, devType, hWnd,
                        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mD3DDevice);
                    if (SUCCEEDED(hr))
                    {
//                     mpD3DDevice->GetRenderTarget( 0, &mpRenderSurface );
//                     mpD3DDevice->GetDepthStencilSurface( &mpRenderZBuffer );
                    }
                }
            }

            // TODO: make this a bit better e.g. go from pure vertex processing to software
            D3D9_RENDERER.setD3DDevice(mD3DDevice);

        } while (0);

        return ret;
    }
}


