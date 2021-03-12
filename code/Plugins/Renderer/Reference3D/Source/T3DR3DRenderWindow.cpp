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


#include "T3DR3DRenderWindow.h"
#include "T3DR3DError.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    R3DRenderWindowPtr R3DRenderWindow::create(const String &name)
    {
        R3DRenderWindowPtr window = new R3DRenderWindow(name);
        window->release();
        return window;
    }

    //--------------------------------------------------------------------------

    R3DRenderWindow::R3DRenderWindow(const String &name)
        : RenderWindow(name)
        , mWindow(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    R3DRenderWindow::~R3DRenderWindow()
    {
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderWindow::create(const RenderWindowCreateParam &param,
        const RenderWindowCreateParamEx &paramEx)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mWindow != nullptr)
            {
                // 窗口已经创建
                ret = T3D_ERR_R3D_WINDOW_ALREADY;
                T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Render window already \
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

                ret = mWindow->create(param.windowTitle.c_str(), 
                    param.windowLeft, param.windowTop, 
                    param.windowWidth, param.windowHeight, flags);
                if (ret != T3D_OK)
                {
                    T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Create native window\
                        failed !");
                    break;
                }
            }

            // 加载图标资源
            Image image;
            ret = image.load(param.iconPath);
            if (ret != T3D_OK)
            {
                T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Load icon image [%s] \
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

            if (ret != T3D_OK)
            {
                ret = T3D_ERR_R3D_UNSUPPORT_FORMAT_ICON;
                T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Do not support icon [%s] \
                    format !", param.iconPath.c_str());
                break;
            }

            mWindow->setWindowIcon(icon);

            mWidth = param.windowWidth;
            mHeight = param.windowHeight;
            mColorDepth = mWindow->getColorDepth();
            mPitch = Image::calcPitch(mWidth, mColorDepth);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderWindow::destroy()
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mWindow == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Invalid window pointer !");
                break;
            }

            mWindow->destroy();

            T3D_SAFE_DELETE(mWindow);

            ret = T3D_OK;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderWindow::swapBuffers()
    {
        TResult ret = T3D_OK;

        do
        {
            if (mWindow == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Invalid window pointer !");
                break;
            }

            ret = mWindow->updateWindow();
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void R3DRenderWindow::clear(const ColorRGB &clrFill, uint32_t clearFlags, 
        Real depth, uint32_t stencil)
    {

    }
}

