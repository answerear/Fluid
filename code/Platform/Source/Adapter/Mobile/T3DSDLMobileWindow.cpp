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

#include <SDL_video.h>
#include "Adapter/Mobile/T3DSDLMobileWindow.h"
#include "T3DPlatformErrorDef.h"
#include <SDL_syswm.h>


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    SDLMobileWindow::SDLMobileWindow()
        : mSDLWindow(nullptr)
        , mSDLIconSurface(nullptr)
        , mFramebuffer(nullptr)
        , mFramebufferSize(0)
    {

    }

    SDLMobileWindow::~SDLMobileWindow()
    {

    }

    //--------------------------------------------------------------------------

    TResult SDLMobileWindow::create(const char *title, int32_t x, int32_t y,
        int32_t w, int32_t h, uint32_t flags)
    {
        TResult ret = T3D_ERR_FAIL;

        do
        {
            if (SDL_WasInit(SDL_INIT_VIDEO) != SDL_INIT_VIDEO)
            {
                break;
            }
            
            SDL_DisplayMode dm;
            if (SDL_GetCurrentDisplayMode(0, &dm) == 0)
            {
                w = dm.w;
                h = dm.h;
            }
            
            mSDLWindow = SDL_CreateWindow(title, x, y, w, h, flags);
            if (mSDLWindow == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                std::string str = SDL_GetError();
                break;
            }
            
            ret = T3D_OK;
        } while (0);

        return ret;
    }

    TResult SDLMobileWindow::createFrom(const void *data)
    {
        TResult ret = T3D_ERR_FAIL;

        do
        {
            if (SDL_WasInit(SDL_INIT_VIDEO) != SDL_INIT_VIDEO)
            {
                ret = T3D_ERR_SYS_NOT_INIT;
                break;
            }

            mSDLWindow = SDL_CreateWindowFrom(data);
            if (mSDLWindow == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                std::string str = SDL_GetError();
                break;
            }

            ret = T3D_OK;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void SDLMobileWindow::destroy()
    {
        SDL_Surface *buffer = SDL_GetWindowSurface(mSDLWindow);

        if (SDL_MUSTLOCK(buffer))
        {
            T3D_SAFE_DELETE_ARRAY(mFramebuffer);
        }

        if (mSDLIconSurface != nullptr)
        {
            SDL_FreeSurface(mSDLIconSurface);
            mSDLIconSurface = nullptr;
        }

        if (mSDLWindow != nullptr)
        {
            SDL_DestroyWindow(mSDLWindow);
            mSDLWindow = nullptr;
        }
    }

    //--------------------------------------------------------------------------

    bool SDLMobileWindow::getSystemInfo(SysWMInfo &info) const
    {
        SDL_SysWMinfo sdlInfo;

        bool ret = SDL_GetWindowWMInfo(mSDLWindow, &sdlInfo);

        if (ret)
        {
#if defined (T3D_OS_WINDOWS)
            info.hWnd = sdlInfo.info.win.window;
            info.hDC = sdlInfo.info.win.hdc;
            info.hInstance = sdlInfo.info.win.hinstance;
#elif defined (T3D_OS_LINUX)
            // Linux X11
            info.display = sdlInfo.info.x11.display;
            info.window = sdlInfo.info.x11.window;
#elif defined (T3D_OS_OSX)
            // Mac OS X cocoa
            info.window = sdlInfo.info.cocoa.window;
#elif defined (T3D_OS_IOS)
            // iOS UIKit
            info.window = sdlInfo.info.uikit.window;
            info.framebuffer = sdlInfo.info.uikit.framebuffer;
            info.colorbuffer = sdlInfo.info.uikit.colorbuffer;
#elif defined (T3D_OS_ANDROID)
            info.window = sdlInfo.info.android.window;
            info.surface = sdlInfo.info.android.surface;
#endif
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    void SDLMobileWindow::setWindowIcon(void *pixels, int32_t width,
                                        int32_t height, int32_t depth,
                                        int32_t pitch, uint32_t format)
    {
        if (mSDLIconSurface != nullptr)
        {
            SDL_FreeSurface(mSDLIconSurface);
            mSDLIconSurface = nullptr;
        }

        if (mSDLWindow != nullptr)
        {
            mSDLIconSurface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, width,
                                                                 height, depth,
                                                                 pitch, format);

            if (mSDLIconSurface != nullptr)
            {
                SDL_SetWindowIcon(mSDLWindow, mSDLIconSurface);
            }
        }
    }

    //--------------------------------------------------------------------------

    void SDLMobileWindow::getWindowSize(int32_t &width,
                                        int32_t &height) const
    {
        width = 0, height = 0;

        if (mSDLWindow != nullptr)
        {
            SDL_GetWindowSize(mSDLWindow, &width, &height);
        }
    }

    //--------------------------------------------------------------------------

    uint32_t SDLMobileWindow::getColorDepth() const
    {
        uint32_t depth = 0;

        if (mSDLWindow != nullptr)
        {
            uint32_t format = SDL_GetWindowPixelFormat(mSDLWindow);
            depth = SDL_BITSPERPIXEL(format);
        }

        return depth;
    }

    //--------------------------------------------------------------------------

    uint8_t *SDLMobileWindow::getFramebuffer()
    {
        if (mSDLWindow == nullptr)
            return nullptr;

        SDL_Surface *buffer = SDL_GetWindowSurface(mSDLWindow);

        if (SDL_MUSTLOCK(buffer))
        {
            if (mFramebuffer == nullptr)
            {
                // 没有帧缓冲，先创建跟窗口一样大小的帧缓冲
                int32_t w, h;
                SDL_GetWindowSize(mSDLWindow, &w, &h);
                SDL_Surface *frontbuffer = SDL_GetWindowSurface(mSDLWindow);
                mFramebufferSize = frontbuffer->pitch * h;
                mFramebuffer = new uint8_t[mFramebufferSize];
            }
        }
        else
        {
            int32_t w, h;
            SDL_GetWindowSize(mSDLWindow, &w, &h);
            mFramebuffer = (uint8_t *)buffer->pixels;
            mFramebufferSize = buffer->pitch * h;
        }

        return mFramebuffer;
    }

    size_t SDLMobileWindow::getFramebufferSize() const
    {
        return mFramebufferSize;
    }

    //--------------------------------------------------------------------------

    TResult SDLMobileWindow::updateWindow()
    {
        TResult ret = T3D_OK;

        SDL_Surface *frontbuffer = SDL_GetWindowSurface(mSDLWindow);

        if (SDL_MUSTLOCK(frontbuffer))
        {
            SDL_LockSurface(frontbuffer);
            memcpy(frontbuffer->pixels, mFramebuffer, mFramebufferSize);
            SDL_UnlockSurface(frontbuffer);
        }

        SDL_UpdateWindowSurface(mSDLWindow);

        return ret;
    }
}
