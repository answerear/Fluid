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


#ifndef __T3D_R3D_PREREQUISITES_H__
#define __T3D_R3D_PREREQUISITES_H__


#include <Tiny3D.h>

#if defined R3DRENDERER_EXPORT
    #define T3D_R3DRENDER_API        T3D_EXPORT_API
#else
    #define T3D_R3DRENDER_API        T3D_IMPORT_API
#endif


namespace Tiny3D
{
    #define LOG_TAG_R3DRENDERER    "R3DRenderer"

    class R3DRenderer;
    class R3DRenderWindow;
    class R3DHardwareBufferManager;
    class R3DHardwareVertexBuffer;
    class R3DHardwareIndexBuffer;
    class R3DHardwarePixelBuffer;
    class R3DHardwareConstantBuffer;
    class R3DVertexArrayObject;
    class R3DVertexDeclaration;
    class R3DFramebuffer;

    T3D_DECLARE_SMART_PTR(R3DRenderer);
    T3D_DECLARE_SMART_PTR(R3DRenderWindow);
    T3D_DECLARE_SMART_PTR(R3DHardwareBufferManager);
    T3D_DECLARE_SMART_PTR(R3DHardwareVertexBuffer);
    T3D_DECLARE_SMART_PTR(R3DHardwareIndexBuffer);
    T3D_DECLARE_SMART_PTR(R3DHardwarePixelBuffer);
    T3D_DECLARE_SMART_PTR(R3DHardwareConstantBuffer);
    T3D_DECLARE_SMART_PTR(R3DVertexArrayObject);
    T3D_DECLARE_SMART_PTR(R3DVertexDeclaration);
    T3D_DECLARE_SMART_PTR(R3DFramebuffer);
}


#endif  /*__T3D_R3D_PREREQUISITES_H__*/
