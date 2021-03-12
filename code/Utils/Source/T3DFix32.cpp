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


#include "T3DFix32.h"


namespace Tiny3D
{
    const int32_t fix32::INTEGER_BITS = 20;
    const int32_t fix32::DECIMAL_BITS = 12;

    const int32_t fix32::MAX_INT_VALUE = 524287; // 524287
    const int32_t fix32::MIN_INT_VALUE = -524288; // -524288

    const float32_t fix32::MAX_FLOAT_VALUE = (fix32::MAX_INT_VALUE * 1.0f); // 524287.0f
    const float32_t fix32::MIN_FLOAT_VALUE = (fix32::MIN_INT_VALUE * 1.0f); // -524288.0f

    const fix32 fix32::ZERO(0);
    const fix32 fix32::HALF(0.5f);
    const fix32 fix32::ONE(1);
    const fix32 fix32::MINUS_ONE(-1);
    const fix32 fix32::INF(0x7FFFFFFF, 0);
    const fix32 fix32::MINUSINF(0x80000000, 0);
}
