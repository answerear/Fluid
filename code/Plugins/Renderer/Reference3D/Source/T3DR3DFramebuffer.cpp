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


#include "T3DR3DFramebuffer.h"
#include "T3DR3DRenderWindow.h"
#include "T3DR3DError.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    R3DFramebufferPtr R3DFramebuffer::create(RenderTargetPtr target)
    {
        R3DFramebufferPtr fbo = new R3DFramebuffer();
        fbo->release();

        if (fbo->init(target) != T3D_OK)
        {
            fbo = nullptr;
        }

        return fbo;
    }

    //--------------------------------------------------------------------------

    R3DFramebuffer::R3DFramebuffer()
        : mFramebuffer(nullptr)
        , mFramebufferSize(0)
        , mWidth(0)
        , mHeight(0)
        , mColorDepth(0)
        , mBytesPerPixel(0)
        , mPitch(0)
    {
        
    }

    //--------------------------------------------------------------------------

    R3DFramebuffer::~R3DFramebuffer()
    {

    }

    //--------------------------------------------------------------------------

    TResult R3DFramebuffer::init(RenderTargetPtr target)
    {
        TResult ret = T3D_OK;

        switch (target->getType())
        {
        case RenderTarget::E_RT_WINDOW:
            {
                R3DRenderWindowPtr window 
                    = smart_pointer_cast<R3DRenderWindow>(target);
                mFramebuffer = window->getFramebuffer();
                mFramebufferSize = window->getFramebufferSize();
                mWidth = window->getWidth();
                mHeight = window->getHeight();
                mColorDepth = window->getColorDepth();
                mPitch = window->getPitch();
                mBytesPerPixel = (mColorDepth >> 3);
            }
            break;
        case RenderTarget::E_RT_TEXTURE:
            break;
        default:
            ret = T3D_ERR_R3D_INVALID_TARGET;
            break;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DFramebuffer::fill(const ColorARGB &color, size_t count /* = 0 */,
        Rect *rects /* = nullptr */)
    {
        TResult ret = T3D_OK;

        if (count == 0 && rects == nullptr)
        {
            uint8_t *fb = nullptr;
            Color4 clr;
            clr.from(color);

            size_t x = 0, y = 0;

            for (y = 0; y < mHeight; ++y)
            {
                fb = mFramebuffer + mPitch * y;

                for (x = 0; x < mWidth; ++x)
                {
                    fillColor(fb, clr, false);
                    fb += mBytesPerPixel;
                }
            }
        }
        else if (count > 0 && rects != nullptr)
        {
            size_t i = 0;

            for (i = 0; i < count; ++i)
            {
                const Rect &rect = rects[i];
                uint8_t *fb = nullptr;
                Color4 clr;
                clr.from(color);

                size_t x = 0, y = 0;

                for (y = rect.top; y < rect.height(); ++y)
                {
                    fb = mFramebuffer + y * mPitch + rect.left * mBytesPerPixel;

                    for (x = rect.left; x < rect.width(); ++x)
                    {
                        fillColor(fb, clr, false);
                        fb += mBytesPerPixel;
                    }
                }
            }
        }
        else
        {
            ret = T3D_ERR_R3D_INVALID_FILLRECT;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DFramebuffer::drawPoint(const Point &point, const ColorARGB &color)
    {
        uint8_t *fb = mFramebuffer;
        size_t pitch = mPitch;
        size_t bytesPerPixel = (mColorDepth >> 3);
        fb = fb + point.y * pitch + point.x * bytesPerPixel;
        Color4 clr;
        clr.from(color);
        fillColor(fb, clr, false);

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DFramebuffer::drawLine(const Point &start, const Point &end,
        const ColorARGB &color, size_t border /* = 1 */)
    {
        TResult ret = T3D_OK;

        Color4 clr;
        clr.from(color);

        uint8_t *fb = mFramebuffer;
        size_t fbSize = mFramebufferSize;
        int32_t pitch = (int32_t)mPitch;
        int32_t bytesPerPixel = (int32_t)mBytesPerPixel;

        int32_t w = (int32_t)mWidth;
        int32_t h = (int32_t)mHeight;

        int32_t x1 = (int32_t)start.x;
        int32_t y1 = (int32_t)start.y;
        int32_t x2 = (int32_t)end.x;
        int32_t y2 = (int32_t)end.y;

        int32_t dx = x2 - x1;
        int32_t dy = y2 - y1;

        int32_t error = 0;

        int32_t x_inc = 0;
        int32_t y_inc = 0;

        if (dx > 0)
        {
            // X-axis 正方向
            x_inc = bytesPerPixel;
        }
        else
        {
            // X-axis 负方向
            x_inc = -bytesPerPixel;
            dx = -dx;
        }

        if (dy > 0)
        {
            // Y-axis 正方向
            y_inc = pitch;
        }
        else
        {
            // Y-axis 负方向
            y_inc = -pitch;
            dy = -dy;
        }

        int32_t dx2 = dx << 1;
        int32_t dy2 = dy << 1;

        int32_t i = 0;

        // 寻址到开始地址
        fb = fb + x1 * bytesPerPixel + y1 * pitch;

        if (dx > dy)
        {
            error = dy2 - dx;

            for (i = 0; i < dx; ++i)
            {
                fillColor(fb, clr, false);

                if (error >= 0)
                {
                    // 调整误差，跳到下一行
                    error -= dx2;
                    fb += y_inc;
                }

                error += dy2;
                fb += x_inc;
            }
        }
        else
        {
            error = dx2 - dy;

            for (i = 0; i < dy; ++i)
            {
                fillColor(fb, clr, false);

                if (error >= 0)
                {
                    error -= dy2;
                    fb += x_inc;
                }

                error += dx2;
                fb += y_inc;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DFramebuffer::drawGradualLine(const Point &start,
        const Point &end, const ColorARGB &clrStart, const ColorARGB &clrEnd,
        size_t border /* = 1 */)
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DFramebuffer::drawTriangle(const Point &p1, const Point &p2,
        const Point &p3, const ColorARGB &color, size_t border /* = 1 */)
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DFramebuffer::drawSolidTriangle(const Point &p1,
        const Point &p2, const Point &p3, const ColorARGB &color)
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DFramebuffer::drawGradualTriangle(
        const Point &p1, const ColorARGB &clr1,
        const Point &p2, const ColorARGB &clr2,
        const Point &p3, const ColorARGB &clr3)
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DFramebuffer::drawRect(const Rect &rect, const ColorARGB &color,
        size_t border /* = 1 */)
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DFramebuffer::drawSolidRect(const Rect &rect,
        const ColorARGB &color)
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    void R3DFramebuffer::fillColor(uint8_t *fb, const Color4 &color, 
        bool alphaBlend)
    {
        if (!alphaBlend)
        {
            fb[0] = color.blue();
            fb[1] = color.green();
            fb[2] = color.red();
        }
        else
        {
            uint8_t srcB = *fb;
            uint8_t srcG = *fb;
            uint8_t srcR = *fb;
            fb[0] = color.alpha() * color.blue() + (1 - color.alpha() * srcB);
            fb[1] = color.alpha() * color.green() + (1 - color.alpha() * srcG);
            fb[2] = color.alpha() * color.red() + (1 - color.alpha() * srcR);
        }
        
        if (mBytesPerPixel == 4)
            fb[3] = 0xFF;
    }
}
