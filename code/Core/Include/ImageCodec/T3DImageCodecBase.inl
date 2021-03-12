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


namespace Tiny3D
{
    inline void ImageCodecBase::setImageData(Image &image, uint8_t *data, 
        size_t size)
    {
        image.mData = data;
        image.mDataSize = size;
    }

    inline void ImageCodecBase::setImageDimension(Image &image, int32_t width, 
        int32_t height, int32_t pitch)
    {
        image.mWidth = width;
        image.mHeight = height;
        image.mPitch = pitch;
    }

    inline void ImageCodecBase::setImageInfo(Image &image, uint32_t sourceType,
        int32_t bpp, bool hasAlpha, bool isPreMulti, PixelFormat eFormat)
    {
        image.mBPP = bpp;
        image.mSourceType = sourceType;
        image.mHasAlpha = hasAlpha;
        image.mIsPreMulti = isPreMulti;
        image.mFormat = eFormat;
    }
}
