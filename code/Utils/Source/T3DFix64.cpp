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


#include "T3DFix64.h"

namespace Tiny3D
{
    const int32_t fix64::INTEGER_BITS = 40;
    const int32_t fix64::DECIMAL_BITS = 24;

    const int64_t fix64::MAX_INT_VALUE = 549755813887LL; // 549755813887LL
    const int64_t fix64::MIN_INT_VALUE = -549755813888LL; // -549755813888LL

    const float32_t fix64::MAX_FLOAT_VALUE = (fix64::MAX_INT_VALUE * 1.0f); // 549755813887.0f
    const float32_t fix64::MIN_FLOAT_VALUE = (fix64::MIN_INT_VALUE * 1.0f); // -549755813888.0f

    const fix64 fix64::ZERO = fix64(0);
    const fix64 fix64::HALF = fix64(0.5f);
    const fix64 fix64::ONE = fix64(1);
    const fix64 fix64::MINUS_ONE = fix64(-1);
    const fix64 fix64::INF = fix64(0x7FFFFFFFFFFFFFFFLL, 0);
    const fix64 fix64::MINUSINF = fix64(0x8000000000000000LL, 0);
}


