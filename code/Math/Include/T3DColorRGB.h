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

#ifndef __T3D_COLOR_RGB_H__
#define __T3D_COLOR_RGB_H__


#include "T3DMathPrerequisites.h"


namespace Tiny3D
{
    class T3D_MATH_API ColorRGB
    {
    public:
        static const ColorRGB BLACK;
        static const ColorRGB WHITE;
        static const ColorRGB RED;
        static const ColorRGB GREEN;
        static const ColorRGB BLUE;
        static const ColorRGB YELLOW;

        ColorRGB(float32_t r = 1.0f, float32_t g = 1.0f, float32_t b = 1.0f)
            : mBlue(b)
            , mGreen(g)
            , mRed(r)
        {

        }

        ColorRGB(const ColorRGB &other)
        {
            mRed = other.mRed;
            mGreen = other.mGreen; 
            mBlue = other.mBlue;
        }

        ColorRGB &operator =(const ColorRGB &other)
        {
            mRed = other.mRed;
            mGreen = other.mGreen; 
            mBlue = other.mBlue;
            return *this;
        }

        bool operator ==(const ColorRGB &other) const
        {
            return (mRed == other.mRed && mGreen == other.mGreen 
                && mBlue == other.mBlue);
        }

        float32_t red() const     { return mRed; }
        float32_t &red()          { return mRed; }

        float32_t green() const   { return mGreen; }
        float32_t &green()        { return mGreen; }

        float32_t blue() const    { return mBlue; }
        float32_t &blue()         { return mBlue; }

    private:
        float32_t   mBlue;
        float32_t   mGreen;
        float32_t   mRed;
    };
}


#endif  /*__T3D_COLOR_RGB_H__*/
