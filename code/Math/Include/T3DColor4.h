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

#ifndef __T3D_COLOR4_H__
#define __T3D_COLOR4_H__


#include "T3DMathPrerequisites.h"
#include "T3DColorRGB.h"
#include "T3DColorARGB.h"


namespace Tiny3D
{
    class T3D_MATH_API Color4
    {
    public:
        static const Color4 BLACK;
        static const Color4 WHITE;
        static const Color4 RED;
        static const Color4 GREEN;
        static const Color4 BLUE;
        static const Color4 YELLOW;

        static const uint16_t RGB555_RED_MASK;
        static const uint16_t RGB555_GREEN_MASK;
        static const uint16_t RGB555_BLUE_MASK;
        static const uint16_t RGB555_ALPHA_MASK;

        static const uint16_t RGB565_RED_MASK;
        static const uint16_t RGB565_GREEN_MASK;
        static const uint16_t RGB565_BLUE_MASK;

        static const uint16_t RGB444_RED_MASK;
        static const uint16_t RGB444_GREEN_MASK;
        static const uint16_t RGB444_BLUE_MASK;
        static const uint16_t RGB444_ALPHA_MASK;

        static const uint32_t RGB_RED_MASK;
        static const uint32_t RGB_GREEN_MASK;
        static const uint32_t RGB_BLUE_MASK;
        static const uint32_t RGB_ALPHA_MASK;

        Color4(uint8_t r = 0xFF, uint8_t g = 0xFF, uint8_t b = 0xFF, 
            uint8_t a = 0xFF)
            : mBlue(b)
            , mGreen(g)
            , mRed(r)
            , mAlpha(a)
        {

        }

        Color4(const ColorRGB &color)
            : mBlue((uint8_t)(color.blue() * 255.0f))
            , mGreen((uint8_t)(color.green() * 255.0f))
            , mRed((uint8_t)(color.red() * 255.0f))
            , mAlpha(255)
        {

        }

        Color4(const ColorARGB &color)
            : mBlue((uint8_t)(color.blue() * 255.0f))
            , mGreen((uint8_t)(color.green() * 255.0f))
            , mRed((uint8_t)(color.red() * 255.0f))
            , mAlpha((uint8_t)(color.alpha() * 255.0f))
        {

        }

        Color4(const Color4 &other)
        {
            mAlpha = other.mAlpha; mRed = other.mRed;
            mGreen = other.mGreen; mBlue = other.mBlue;
        }

        Color4 &operator =(const Color4 &other)
        {
            mAlpha = other.mAlpha; mRed = other.mRed;
            mGreen = other.mGreen; mBlue = other.mBlue;
            return *this;
        }

        bool operator ==(const Color4 &other) const
        {
            return (mAlpha == other.mAlpha && mRed == other.mRed
                && mGreen == other.mGreen && mBlue == other.mBlue);
        }

        void from(const ColorRGB &color)
        {
            mAlpha = 0xFF;
            mRed = (uint8_t)(color.red() * 255.0f);
            mGreen = (uint8_t)(color.green() * 255.0f);
            mBlue = (uint8_t)(color.blue() * 255.0f);
        }

        void from(const ColorARGB &color)
        {
            mAlpha = (uint8_t)(color.alpha() * 255.0f);
            mRed = (uint8_t)(color.red() * 255.0f);
            mGreen = (uint8_t)(color.green() * 255.0f);
            mBlue = (uint8_t)(color.blue() * 255.0f);
        }

        ColorRGB toColor3f() const
        {
            return ColorRGB(
                (float32_t)mBlue / 255.0f,
                (float32_t)mGreen / 255.0f,
                (float32_t)mRed / 255.0f
            );
        }

        ColorARGB toColor4f() const
        {
            return ColorARGB(
                (float32_t)mBlue / 255.0f,
                (float32_t)mGreen / 255.0f,
                (float32_t)mRed / 255.0f,
                (float32_t)mAlpha / 255.0f
            );
        }

        uint8_t alpha() const   { return mAlpha; }
        uint8_t &alpha()        { return mAlpha; }

        uint8_t red() const     { return mRed; }
        uint8_t &red()          { return mRed; }

        uint8_t green() const   { return mGreen; }
        uint8_t &green()        { return mGreen; }

        uint8_t blue() const    { return mBlue; }
        uint8_t &blue()         { return mBlue; }

        uint32_t A8R8G8B8() const
        {
            return ((mAlpha << 24) & RGB_ALPHA_MASK) 
                | ((mRed << 16) & RGB_RED_MASK)
                | ((mGreen << 8) & RGB_GREEN_MASK) 
                | (mBlue & RGB_BLUE_MASK);
        }

        uint16_t A1R5G5B5() const
        {
            uint8_t alpha = (mAlpha > 0 ? 1 : 0);
            return ((alpha << 15) & RGB555_ALPHA_MASK) 
                | ((mRed << 10) & RGB555_RED_MASK)
                | ((mGreen << 5) & RGB555_GREEN_MASK) 
                | (mBlue & RGB555_BLUE_MASK);
        }

        uint16_t R5G6B5() const
        {
            return ((mRed << 11) & RGB565_RED_MASK) 
                | ((mGreen << 5) & RGB565_GREEN_MASK)
                | (mBlue & RGB565_BLUE_MASK);
        }

        uint16_t A4R4G4B4() const
        {
            uint8_t alpha = (mAlpha >> 1);
            return ((alpha << 12) & RGB444_ALPHA_MASK) 
                | ((mRed << 8) & RGB444_RED_MASK) 
                | ((mGreen << 4) & RGB444_GREEN_MASK) 
                | (mBlue & RGB444_BLUE_MASK);
        }

    private:
        uint8_t     mBlue;
        uint8_t     mGreen;
        uint8_t     mRed;
        uint8_t     mAlpha;
    };
}


#endif  /*__T3D_COLOR4_H__*/
