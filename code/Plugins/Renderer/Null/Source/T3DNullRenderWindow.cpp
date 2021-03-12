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


#include "T3DD3D11RenderWindow.h"
#include "T3DD3D11Error.h"
#include "T3DD3D11Renderer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11RenderWindow, RenderWindow);

    //--------------------------------------------------------------------------

    D3D11RenderWindowPtr D3D11RenderWindow::create(const String &name)
    {
        D3D11RenderWindowPtr window = new D3D11RenderWindow(name);
        window->release();
        return window;
    }

    //--------------------------------------------------------------------------

    D3D11RenderWindow::D3D11RenderWindow(const String &name)
        : RenderWindow(name)
        , mWindow(nullptr)
        , mD3DSwapChain(nullptr)
        , mD3DRTView(nullptr)
        , mD3DDSView(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    D3D11RenderWindow::~D3D11RenderWindow()
    {
        D3D_SAFE_RELEASE(mD3DSwapChain);
        D3D_SAFE_RELEASE(mD3DRTView);
        D3D_SAFE_RELEASE(mD3DDSView);

        T3D_SAFE_DELETE(mWindow);
    }

    //--------------------------------------------------------------------------

    TResult D3D11RenderWindow::create(const RenderWindowCreateParam &param,
        const RenderWindowCreateParamEx &paramEx)
    {
        TResult ret = T3D_OK;

        do
        {
            if (mWindow != nullptr)
            {
                // 窗口已经创建
                ret = T3D_ERR_D3D11_WINDOW_ALREADY;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, 
                    "Render window already created !");
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
                    + D3D11_RENDERER.getName();
                ret = mWindow->create(title.c_str(),
                    param.windowLeft, param.windowTop,
                    param.windowWidth, param.windowHeight, flags);
                if (T3D_FAILED(ret))
                {
                    T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, 
                        "Create native window failed !");
                    break;
                }
            }

            // 加载图标
            ret = loadIcon(param.iconPath);
            if (T3D_FAILED(ret))
            {
                break;
            }

            mWidth = param.windowWidth;
            mHeight = param.windowHeight;
            mColorDepth = mWindow->getColorDepth();
            mPitch = Image::calcPitch(mWidth, mColorDepth);

            ret = setupD3D11Environment(param, paramEx);
            if (T3D_FAILED(ret))
            {
                break;
            }

            ret = T3D_OK;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11RenderWindow::destroy()
    {
        TResult ret = T3D_OK;

        do
        {
            if (mWindow == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, "Invalid window pointer !");
                break;
            }

            D3D_SAFE_RELEASE(mD3DDSView);
            D3D_SAFE_RELEASE(mD3DRTView);
            D3D_SAFE_RELEASE(mD3DSwapChain);

            mWindow->destroy();

            T3D_SAFE_DELETE(mWindow);

            ret = T3D_OK;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11RenderWindow::swapBuffers()
    {
        TResult ret = T3D_OK;

        do
        {
            HRESULT hr = S_OK;
            hr = mD3DSwapChain->Present(0, 0);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_PRESENT;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Present failed ! DX ERROR [%d]", hr);
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void D3D11RenderWindow::clear(const ColorRGB &clrFill, uint32_t clearFlags, 
        Real depth, uint32_t stencil)
    {
        do 
        {
            if (mD3DRTView == nullptr)
            {
                break;
            }

            if (mD3DDSView == nullptr)
            {
                break;
            }

            ID3D11DeviceContext *pD3DContext 
                = D3D11_RENDERER.getD3DDeviceContext();
            const float clr[4] = 
            { clrFill.red(), clrFill.green(), clrFill.blue(), 1.0f };
            pD3DContext->ClearRenderTargetView(mD3DRTView, clr);
            pD3DContext->ClearDepthStencilView(mD3DDSView, 
                D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
        } while (0);
    }

    //--------------------------------------------------------------------------

    TResult D3D11RenderWindow::loadIcon(const String &iconPath)
    {
        TResult ret = T3D_OK;

        do 
        {
            // 加载图标资源
            Image image;
            ret = image.load(iconPath);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, 
                    "Load icon image [%s] failed !", iconPath.c_str());
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
            case PixelFormat::E_PF_PALETTE8:
                icon.format = Window::PIXEL_FORMAT_INDEX8;
                break;
            case PixelFormat::E_PF_A1R5G5B5:
                icon.format = Window::PIXEL_FORMAT_ARGB1555;
                break;
            case PixelFormat::E_PF_A4R4G4B4:
                icon.format = Window::PIXEL_FORMAT_ARGB4444;
                break;
            case PixelFormat::E_PF_R5G6B5:
                icon.format = Window::PIXEL_FORMAT_RGB565;
                break;
            case PixelFormat::E_PF_R8G8B8:
                icon.format = Window::PIXEL_FORMAT_RGB24;
                break;
            case PixelFormat::E_PF_A8R8G8B8:
                icon.format = Window::PIXEL_FORMAT_ARGB8888;
                break;
            default:
                break;
            }

            if (T3D_FAILED(ret))
            {
                ret = T3D_ERR_D3D11_UNSUPPORT_FORMAT_ICON;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, 
                    "Do not support icon [%s] format !", iconPath.c_str());
                break;
            }

            mWindow->setWindowIcon(icon);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11RenderWindow::setupD3D11Environment(
        const RenderWindowCreateParam &param, 
        const RenderWindowCreateParamEx &paramEx)
    {
        TResult ret = T3D_OK;

        do 
        {
            UINT uMSAAQuality
                = (DWORD)paramEx.at("MultiSampleQuality").longValue();
            UINT uMSAACount = 4;

            if (uMSAAQuality < 2)
                uMSAAQuality = 0;
            else if (uMSAAQuality > 16)
                uMSAAQuality = 16;

            ID3D11Device *pD3DDevice = D3D11_RENDERER.getD3DDevice();
            DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
            HRESULT hr = S_OK;

            if (uMSAAQuality == 0)
            {
                uMSAACount = 1;
            }
            else
            {
                UINT uNumQuality = 0;
                hr = pD3DDevice->CheckMultisampleQualityLevels(format,
                    uMSAACount, &uNumQuality);
                if (FAILED(hr))
                {
                    ret = T3D_ERR_D3D11_CHECK_MULTISAMPLE;
                    T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                        "Check multiple sample quality levels failed ! "
                        "DX ERROR [%d]", hr);
                    break;
                }

                uMSAAQuality = uNumQuality - 1;
            }

            ret = createSwapChain((UINT)mWidth, (UINT)mHeight, param.fullscreen, 
                uMSAACount, uMSAAQuality, format);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create swap chain failed !");
                break;
            }

            ret = createRenderTargetView();
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create render target view failed !");
                break;
            }

            ret = createDepthStencilView((UINT)mWidth, (UINT)mHeight, 
                uMSAACount, uMSAAQuality);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create depth and stencil view failed !");
                break;
            }

            ID3D11DeviceContext *pD3DContext 
                = D3D11_RENDERER.getD3DDeviceContext();
            pD3DContext->OMSetRenderTargets(1, &mD3DRTView, mD3DDSView);

        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11RenderWindow::createSwapChain(UINT uWidth, UINT uHeight, 
        bool bFullscreen, UINT uMSAACount, UINT uMSAAQuality, DXGI_FORMAT format)
    {
        TResult ret = T3D_OK;

        IDXGIDevice *pDXGIDevice = nullptr;
        IDXGIAdapter *pDXGIAdapter = nullptr;
        IDXGIFactory *pDXGIFactory = nullptr;

        do 
        {
            SysWMInfo info;
            mWindow->getSystemInfo(info);
            HWND hWnd = (HWND)info.hWnd;

            ID3D11Device *pD3DDevice = D3D11_RENDERER.getD3DDevice();

            DXGI_SWAP_CHAIN_DESC desc;

            desc.BufferDesc.Width = (UINT)mWidth;
            desc.BufferDesc.Height = (UINT)mHeight;
            desc.BufferDesc.RefreshRate.Numerator = 60;
            desc.BufferDesc.RefreshRate.Denominator = 1;
            desc.BufferDesc.Format = format;
            desc.BufferDesc.ScanlineOrdering 
                = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

            desc.SampleDesc.Count = uMSAACount;
            desc.SampleDesc.Quality = uMSAAQuality;

            desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            desc.BufferCount = 1;
            desc.OutputWindow = hWnd;
            desc.Windowed = !bFullscreen;
            desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
            desc.Flags = 0;

            HRESULT hr = S_OK;

            hr = pD3DDevice->QueryInterface(__uuidof(IDXGIDevice), 
                (void **)&pDXGIDevice);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_CREATE_FAILED;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Query interface for IDXGIDevice failed ! DX ERROR [%d]",
                    hr);
                break;
            }

            hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), 
                (void **)&pDXGIAdapter);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_GET_INTERFACE;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Get COM for IDXGIAdapter failed ! DX ERROR [%d]", hr);
                break;
            }

            hr = pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), 
                (void **)&pDXGIFactory);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_GET_INTERFACE;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Get COM for IDXGIFactory failed ! DX ERROR [%d]", hr);
                break;
            }

            hr = pDXGIFactory->CreateSwapChain(pD3DDevice, &desc, 
                &mD3DSwapChain);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_CREATE_FAILED;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create swap chain failed ! DX ERROR [%d]", hr);
                break;
            }
        } while (0);

        D3D_SAFE_RELEASE(pDXGIFactory);
        D3D_SAFE_RELEASE(pDXGIAdapter);
        D3D_SAFE_RELEASE(pDXGIDevice);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11RenderWindow::createRenderTargetView()
    {
        TResult ret = T3D_OK;

        ID3D11Texture2D *pD3DBackBuffer = nullptr;

        do 
        {
            HRESULT hr = S_OK;
            ID3D11Device *pD3DDevice = D3D11_RENDERER.getD3DDevice();
            hr = mD3DSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                reinterpret_cast<void **>(&pD3DBackBuffer));
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_GET_INTERFACE;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Get COM for ID3D11Texture2D failed ! DX ERROR [%d]", hr);
                break;
            }

            hr = pD3DDevice->CreateRenderTargetView(pD3DBackBuffer, 0, 
                &mD3DRTView);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_CREATE_FAILED;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create render target view failed ! DX ERROR [%d]", hr);
                break;
            }
        } while (0);

        D3D_SAFE_RELEASE(pD3DBackBuffer);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11RenderWindow::createDepthStencilView(UINT uWidth, UINT uHeight,
        UINT uMSAACount, UINT uMSAAQuality)
    {
        TResult ret = T3D_OK;

        ID3D11Texture2D *pD3DTexture = nullptr;

        do 
        {
            ID3D11Device *pD3DDevice = D3D11_RENDERER.getD3DDevice();

            D3D11_TEXTURE2D_DESC desc;
            desc.Width = uWidth;
            desc.Height = uHeight;
            desc.MipLevels = 1;
            desc.ArraySize = 1;
            desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

            desc.SampleDesc.Count = uMSAACount;
            desc.SampleDesc.Quality = uMSAAQuality;

            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
            desc.CPUAccessFlags = 0;
            desc.MiscFlags = 0;

            HRESULT hr = S_OK;
            hr = pD3DDevice->CreateTexture2D(&desc, nullptr, &pD3DTexture);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_CREATE_FAILED;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create texture 2D failed ! DX ERROR [%d]", hr);
                break;
            }

            hr = pD3DDevice->CreateDepthStencilView(pD3DTexture, 0, &mD3DDSView);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_CREATE_FAILED;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create depth stencil view failed ! DX ERROR [%d]", hr);
                break;
            }
        } while (0);

        D3D_SAFE_RELEASE(pD3DTexture);

        return ret;
    }
}


