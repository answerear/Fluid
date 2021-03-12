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

#ifndef __T3D_COLOR_RGBA_H__
#define __T3D_COLOR_RGBA_H__


#include "T3DMathPrerequisites.h"
#include "T3DColorRGB.h"
#include "T3DColorARGB.h"


namespace Tiny3D
{
    class T3D_MATH_API ColorRGBA
    {
    public:
        static const ColorRGBA BLACK;
        static const ColorRGBA WHITE;
        static const ColorRGBA RED;
        static const ColorRGBA GREEN;
        static const ColorRGBA BLUE;
        static const ColorRGBA YELLOW;

        ColorRGBA(float32_t r = 1.0f, float32_t g = 1.0f, float32_t b = 1.0f,
            float32_t a = 1.0f)
            : mRed(r)
            , mGreen(g)
            , mBlue(b)
            , mAlpha(a)
        {

        }

        ColorRGBA(const ColorRGB &color)
            : mRed(color.red())
            , mGreen(color.green())
            , mBlue(color.blue())
            , mAlpha(1.0f)
        {

        }

        ColorRGBA(const ColorARGB &color)
            : mRed(color.red())
            , mGreen(color.green())
            , mBlue(color.blue())
            , mAlpha(1.0f)
        {

        }

        ColorRGBA(const ColorRGBA &other)
        {
            mAlpha = other.mAlpha; 
            mRed = other.mRed;
            mGreen = other.mGreen; 
            mBlue = other.mBlue;
        }

        ColorARGB toARGB() const
        {
            return ColorARGB(mRed, mGreen, mBlue, mAlpha);
        }

        ColorRGBA &operator =(const ColorRGBA &other)
        {
            mAlpha = other.mAlpha; 
            mRed = other.mRed;
            mGreen = other.mGreen; 
            mBlue = other.mBlue;
            return *this;
        }

        bool operator ==(const ColorRGBA &other) const
        {
            return (mAlpha == other.mAlpha 
                && mRed == other.mRed
                && mGreen == other.mGreen 
                && mBlue == other.mBlue);
        }

        bool operator !=(const ColorRGBA &other) const
        {
            return !operator ==(other);
        }

        float32_t alpha() const   { return mAlpha; }
        float32_t &alpha()        { return mAlpha; }

        float32_t red() const     { return mRed; }
        float32_t &red()          { return mRed; }

        float32_t green() const   { return mGreen; }
        float32_t &green()        { return mGreen; }

        float32_t blue() const    { return mBlue; }
        float32_t &blue()         { return mBlue; }

    private:
        float32_t   mRed;
        float32_t   mGreen;
        float32_t   mBlue;
        float32_t   mAlpha;
    };
}


#endif  /*__T3D_COLOR_RGBA_H__*/
