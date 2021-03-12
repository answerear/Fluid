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

#include "T3DReal.h"


namespace Tiny3D
{
    const float32_t TReal<float32_t>::ZERO = 0.0f;
    const float32_t TReal<float32_t>::ONE = 1.0f;
    const float32_t TReal<float32_t>::HALF = 0.5f;
    const float32_t TReal<float32_t>::MINUS_ONE = -1.0f;
    const float32_t TReal<float32_t>::INF = std::numeric_limits<float32_t>::infinity();
    const float32_t TReal<float32_t>::MINUS_INF = -std::numeric_limits<float32_t>::infinity();
    const float32_t TReal<float32_t>::EPSILON = 1e-5f;

    const float64_t TReal<float64_t>::ZERO = 0.0;
    const float64_t TReal<float64_t>::ONE = 1.0;
    const float64_t TReal<float64_t>::HALF = 0.5;
    const float64_t TReal<float64_t>::MINUS_ONE = -1.0;
    const float64_t TReal<float64_t>::INF = std::numeric_limits<float64_t>::infinity();
    const float64_t TReal<float64_t>::MINUS_INF = -std::numeric_limits<float64_t>::infinity();
    const float64_t TReal<float64_t>::EPSILON = 1e-5;

    const fix32_t TReal<fix32_t>::ZERO = fix32_t::ZERO;
    const fix32_t TReal<fix32_t>::ONE = fix32_t::ONE;
    const fix32_t TReal<fix32_t>::HALF = fix32_t::HALF;
    const fix32_t TReal<fix32_t>::MINUS_ONE = fix32_t::MINUS_ONE;
    const fix32_t TReal<fix32_t>::INF = fix32_t::INF;
    const fix32_t TReal<fix32_t>::MINUS_INF = fix32_t::MINUSINF;
    const fix32_t TReal<fix32_t>::EPSILON = 1e-5;

    const fix64_t TReal<fix64_t>::ZERO = fix32_t::ZERO;
    const fix64_t TReal<fix64_t>::ONE = fix32_t::ONE;
    const fix64_t TReal<fix64_t>::HALF = fix32_t::HALF;
    const fix64_t TReal<fix64_t>::MINUS_ONE = fix32_t::MINUS_ONE;
    const fix64_t TReal<fix64_t>::INF = fix32_t::INF;
    const fix64_t TReal<fix64_t>::MINUS_INF = fix32_t::MINUSINF;
    const fix64_t TReal<fix64_t>::EPSILON = 1e-5;
}
