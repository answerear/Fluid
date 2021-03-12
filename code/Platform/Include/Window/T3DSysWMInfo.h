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

#ifndef __T3D_SYS_WM_INFO_H__
#define __T3D_SYS_WM_INFO_H__


#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DPlatformPrerequisites.h"


namespace Tiny3D
{
    struct SysWMInfo
    {
#if defined (T3D_OS_WINDOWS)
        // Windows
        THandle     hWnd;           /**< The window handle */
        THandle     hDC;            /**< The window device context */
        THandle     hInstance;      /**< The window instance */
#elif defined (T3D_OS_LINUX)
        // Linux X11
        void        *display;       /**< The X11 display (Display) */
        ulong_t     window;        /**< The X11 window (Window) */
#elif defined (T3D_OS_OSX)
        // Mac OS X cocoa
        void        *window;        /**< The Cocoa window (NSWindow) */
#elif defined (T3D_OS_IOS)
        // iOS UIKit
        void        *window;        /**< The UIKit window (UIWindow) */
        uint32_t    framebuffer;    /**< The GL view's Framebuffer Object */
        uint32_t    colorbuffer;    /**< the GL view's color Renderbuffer Object */
#elif defined (T3D_OS_ANDROID)
        void        *window;        /**< The Android native window */
        void        *surface;       /**< The Android EGL surface */
#endif
    };
}


#endif  /*__T3D_SYS_WM_INFO_H__*/
