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

#include "T3DColor4.h"


namespace Tiny3D
{
    const Color4 Color4::BLACK(0, 0, 0);
    const Color4 Color4::WHITE(255, 255, 255);
    const Color4 Color4::RED(255, 0, 0);
    const Color4 Color4::GREEN(0, 255, 0);
    const Color4 Color4::BLUE(0, 0, 255);
    const Color4 Color4::YELLOW(255, 255, 0);

    const uint16_t Color4::RGB555_RED_MASK = 0x7C00;
    const uint16_t Color4::RGB555_GREEN_MASK = 0x03E0;
    const uint16_t Color4::RGB555_BLUE_MASK = 0x001F;
    const uint16_t Color4::RGB555_ALPHA_MASK = 0x8000;

    const uint16_t Color4::RGB565_RED_MASK = 0xF800;
    const uint16_t Color4::RGB565_GREEN_MASK = 0x07E0;
    const uint16_t Color4::RGB565_BLUE_MASK = 0x001F;

    const uint16_t Color4::RGB444_RED_MASK = 0x0F00;
    const uint16_t Color4::RGB444_GREEN_MASK = 0x00F0;
    const uint16_t Color4::RGB444_BLUE_MASK = 0x000F;
    const uint16_t Color4::RGB444_ALPHA_MASK = 0xF000;

    const uint32_t Color4::RGB_RED_MASK = 0x00FF0000;
    const uint32_t Color4::RGB_GREEN_MASK = 0x0000FF00;
    const uint32_t Color4::RGB_BLUE_MASK = 0x000000FF;
    const uint32_t Color4::RGB_ALPHA_MASK = 0xFF000000;
}
