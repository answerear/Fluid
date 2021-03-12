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


#include "T3DFreeImageCodec.h"
#include "T3DFreeImageCodecError.h"
#include <FreeImage.h>
#include <sstream>


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(FreeImageCodec, ImageCodecBase);

    //--------------------------------------------------------------------------

    void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message)
    {
        if (fif != FIF_UNKNOWN)
        {
            T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, "Error [%s] : %s", 
                FreeImage_GetFormatFromFIF(fif), message);
        }
        else
        {
            T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, "Error [UNKNOWN] : %s",
                message);
        }
    }

    //--------------------------------------------------------------------------

    const size_t FreeImageCodec::MAX_SUPPORTED_FILE_TYPE = 37;

    //--------------------------------------------------------------------------

    FreeImageCodecPtr FreeImageCodec::create()
    {
        FreeImageCodecPtr codec = new FreeImageCodec();
        codec->release();
        return codec;
    }

    //--------------------------------------------------------------------------

    TResult FreeImageCodec::startup()
    {
        TResult ret = T3D_OK;

        do 
        {
            FreeImage_Initialise(FALSE);
            FreeImage_SetOutputMessage(FreeImageErrorHandler);

            T3D_LOG_INFO(LOG_TAG_FREEIMAGE_CODEC, "FreeImage Version : %s", 
                FreeImage_GetVersion());
            T3D_LOG_INFO(LOG_TAG_FREEIMAGE_CODEC, "%s", 
                FreeImage_GetCopyrightMessage());

            std::stringstream ss;
            ss << "Supported formats : ";
            bool first = true;
            int i = 0;
            for (i = 0; i < FreeImage_GetFIFCount(); ++i)
            {
                String exts(FreeImage_GetFIFExtensionList((FREE_IMAGE_FORMAT)i));
                
                if (!first)
                {
                    ss << ",";
                }

                first = false;
                ss << exts;
            }

            T3D_LOG_INFO(LOG_TAG_FREEIMAGE_CODEC, "%s", ss.str().c_str());

            mFileTypeList.resize(MAX_SUPPORTED_FILE_TYPE);
            for (i = 0; i < mFileTypeList.size(); ++i)
            {
                mFileTypeList[i] = (ImageCodecBase::FileType)i;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult FreeImageCodec::shutdown()
    {
        TResult ret = T3D_OK;
        FreeImage_DeInitialise();
        return ret;
    }

    //--------------------------------------------------------------------------

    bool FreeImageCodec::isSupportedType(uint8_t *data, size_t size, 
        FileType &type) const
    {
        bool ret = true;

        do 
        {
            FIMEMORY* fiMem = FreeImage_OpenMemory(data, (DWORD)size);
            if (fiMem == nullptr)
            {
                ret = false;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, "Open memory failed !");
                break;
            }

            FREE_IMAGE_FORMAT fif 
                = FreeImage_GetFileTypeFromMemory(fiMem, (DWORD)size);
            FreeImage_CloseMemory(fiMem);

            type = (FileType)fif;
            if (fif == FIF_UNKNOWN)
            {
                ret = false;
                break;
            }

        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    ImageCodecBase::FileType FreeImageCodec::getFileType() const
    {
        return FileType::IMG;
    }

    //--------------------------------------------------------------------------

    TResult FreeImageCodec::encode(uint8_t *&data, size_t &size, 
        const Image &image, FileType type)
    {
        TResult ret = T3D_OK;

        FIBITMAP *dib = nullptr;
        FIMEMORY *stream = nullptr;

        do 
        {
            uint32_t redMask, greenMask, blueMask, alphaMask;
            image.getColorMask(redMask, greenMask, blueMask, alphaMask);

            dib = FreeImage_ConvertFromRawBitsEx(FALSE, (BYTE*)image.getData(), 
                FIT_BITMAP, (int32_t)image.getWidth(), (int32_t)image.getHeight(), 
                (int32_t)image.getPitch(), (uint32_t)image.getBPP(), 
                redMask, greenMask, blueMask, TRUE);
            if (dib == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC,
                    "Convert from raw data failed !");
                break;
            }

            stream = FreeImage_OpenMemory(0, 0);
            if (stream == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, "Open memory failed !");
                break;
            }

            FREE_IMAGE_FORMAT fif = (FREE_IMAGE_FORMAT)type;

            if (!FreeImage_SaveToMemory(fif, dib, stream))
            {
                ret = T3D_ERR_CODEC_ENCODE_TO_MEMORY;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, 
                    "Encode image data to target format failed !");
                break;
            }

            uint8_t *temp = nullptr;

            if (!FreeImage_AcquireMemory(stream, &temp, (DWORD *)&size))
            {
                ret = T3D_ERR_CODEC_ACQUIRE_MEMORY;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, 
                    "Acquire memory for encoding data failed !");
                break;
            }

            data = new uint8_t[size];
            memcpy(data, temp, size);
        } while (0);

        if (dib != nullptr)
        {
            FreeImage_Unload(dib);
            dib = nullptr;
        }

        if (stream != nullptr)
        {
            FreeImage_CloseMemory(stream);
            stream = nullptr;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult FreeImageCodec::decode(uint8_t *data, size_t size, Image &image, 
        FileType type)
    {
        TResult ret = T3D_OK;

        FIMEMORY *stream = nullptr;
        FIBITMAP *dib = nullptr;

        do 
        {
            stream = FreeImage_OpenMemory(data, (DWORD)size);
            if (stream == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, "Open memory failed !");
                break;
            }

            FREE_IMAGE_FORMAT fif = (FREE_IMAGE_FORMAT)type;
            dib = FreeImage_LoadFromMemory(fif, stream);
            if (dib == nullptr)
            {
                ret = T3D_ERR_CODEC_DECODE_FROM_MEMORY;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC,
                    "Decode from memory failed !");
                break;
            }

            uint32_t width = FreeImage_GetWidth(dib);
            uint32_t height = FreeImage_GetHeight(dib);
            int32_t bpp = FreeImage_GetBPP(dib);

            FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(dib);
            FREE_IMAGE_COLOR_TYPE colorType = FreeImage_GetColorType(dib);
            PixelFormat eFormat = PixelFormat::E_PF_A8R8G8B8;

            switch (imageType)
            {
            case FIT_BITMAP:
                {
                    if (colorType == FIC_MINISWHITE 
                        || colorType == FIC_MINISBLACK)
                    {
                        FIBITMAP *newBitmap = FreeImage_ConvertToGreyscale(dib);
                        if (newBitmap == nullptr)
                        {
                            ret = T3D_ERR_CODEC_CONVERT_TO_GREY;
                            T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC,
                                "Convert to grey scale failed !");
                            break;
                        }

                        FreeImage_Unload(dib);
                        dib = newBitmap;
                        bpp = FreeImage_GetBPP(dib);
                    }
                    else if (bpp < 8 
                        || colorType == FIC_PALETTE || colorType == FIC_CMYK)
                    {
                        FIBITMAP *newBitmap = nullptr;
//                         if (FreeImage_IsTransparent(dib))
                        {
                            // 把带透明通道，转成32位
                            newBitmap = FreeImage_ConvertTo32Bits(dib);
                            if (newBitmap == nullptr)
                            {
                                ret = T3D_ERR_CODEC_CONVERT_TO_32BIT;
                                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC,
                                    "Convert to 32 bits failed !");
                                break;
                            }
                        }
//                         else
//                         {
//                             // 不带透明通道，直接转成24位
//                             newBitmap = FreeImage_ConvertTo24Bits(dib);
//                             if (newBitmap == nullptr)
//                             {
//                                 ret = T3D_ERR_CODEC_CONVERT_TO_24BIT;
//                                 T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC,
//                                     "Convert to 24 bits failed !");
//                                 break;
//                             }
//                         }

                        FreeImage_Unload(dib);
                        dib = newBitmap;
                        bpp = FreeImage_GetBPP(dib);
                    }
                }
                break;
            default:
                break;
            }

            if (ret == T3D_OK)
            {
                bool hasAlpha = false;
                bool isPreMulti = false;

                uint32_t srcPitch = FreeImage_GetPitch(dib);
                uint8_t *src = FreeImage_GetBits(dib);

                uint32_t dstPitch = srcPitch;
                size_t imageSize = (size_t)dstPitch * height;
                uint8_t *dst = new uint8_t[imageSize];

                switch (bpp)
                {
                case 8:
                    {
                        eFormat = PixelFormat::E_PF_PALETTE8;
                    }
                    break;
                case 16:
                    {
                        if (FreeImage_GetGreenMask(dib) == FI16_565_GREEN_MASK)
                        {
                            eFormat = PixelFormat::E_PF_R5G6B5;
                        }
                        else
                        {
                            eFormat = PixelFormat::E_PF_A1R5G5B5;
                        }
                    }
                    break;
                case 24:
                    {
                        eFormat = PixelFormat::E_PF_R8G8B8;
                    }
                    break;
                case 32:
                    {
                        eFormat = PixelFormat::E_PF_A8R8G8B8;
                        hasAlpha = true;
                    }
                    break;
                }

                uint32_t y = 0;
                uint8_t *pDst = dst;

                if (type == FileType::DDS)
                {
                    // DDS要翻转一次，因为DDS原点在左上角
                    for (y = 0; y < height; ++y)
                    {
                        uint8_t *pSrc = src + (height - y - 1) * srcPitch;
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
                        Color4::convert_B8G8R8A8toA8R8G8B8(pSrc, pDst, width);
#elif FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR
                        memcpy(pDst, pSrc, dstPitch);
#endif
                        pDst += dstPitch;
                    }
                }
                else
                {
                    for (y = 0; y < height; ++y)
                    {
                        uint8_t *pSrc = src + (height - y - 1) * srcPitch;
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
                        Color4::convert_B8G8R8A8toA8R8G8B8(pSrc, pDst, width);
#elif FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR
                        memcpy(pDst, pSrc, dstPitch);
#endif
                        pDst += dstPitch;
                    }
                }


                fif = FreeImage_GetFileTypeFromMemory(stream);

                setImageDimension(image, width, height, dstPitch);
                setImageInfo(image, fif, bpp, hasAlpha, 
                    isPreMulti, eFormat);
                setImageData(image, dst, imageSize);
            }
        } while (0);

        if (dib != nullptr)
        {
            FreeImage_Unload(dib);
            dib = nullptr;
        }

        if (stream != nullptr)
        {
            FreeImage_CloseMemory(stream);
            stream = nullptr;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult FreeImageCodec::flip(Image &image)
    {
        TResult ret = T3D_OK;
        FIBITMAP *dib = nullptr;

        do
        {
            uint32_t redMask, greenMask, blueMask, alphaMask;
            image.getColorMask(redMask, greenMask, blueMask, alphaMask);

            dib = FreeImage_ConvertFromRawBitsEx(FALSE, image.getData(), 
                FIT_BITMAP, (int32_t)image.getWidth(), (int32_t)image.getHeight(),
                (int32_t)image.getPitch(), (uint32_t)image.getBPP(), 
                redMask, greenMask, blueMask, FALSE);

            if (dib == nullptr)
            {
                ret = T3D_ERR_CODEC_LOAD_FROM_RAW_DATA;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, 
                    "Convert from raw bits failed !");
                break;
            }

            if (!FreeImage_FlipVertical(dib))
            {
                ret = T3D_ERR_CODEC_FLIP;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, 
                    "Flip image failed !");
                break;
            }

            FreeImage_Unload(dib);
            dib = nullptr;
        } while (0);

        if (dib != nullptr)
        {
            FreeImage_Unload(dib);
            dib = nullptr;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult FreeImageCodec::mirror(Image &image)
    {
        TResult ret = T3D_OK;
        FIBITMAP *dib = nullptr;

        do
        {
            uint32_t redMask, greenMask, blueMask, alphaMask;
            image.getColorMask(redMask, greenMask, blueMask, alphaMask);

            dib = FreeImage_ConvertFromRawBitsEx(FALSE, image.getData(), 
                FIT_BITMAP, (int32_t)image.getWidth(), (int32_t)image.getHeight(), 
                (int32_t)image.getPitch(), (uint32_t)image.getBPP(),
                redMask, greenMask, blueMask, FALSE);

            if (dib == nullptr)
            {
                ret = T3D_ERR_CODEC_LOAD_FROM_RAW_DATA;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, 
                    "Convert from raw bits failed !");
                break;
            }

            if (!FreeImage_FlipHorizontal(dib))
            {
                ret = T3D_ERR_CODEC_MIRROR;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, 
                    "Mirror image failed !");
                break;
            }

            FreeImage_Unload(dib);
            dib = nullptr;
        } while (0);

        if (dib != nullptr)
        {
            FreeImage_Unload(dib);
            dib = nullptr;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult FreeImageCodec::fill(Image &image, const Color4 &color)
    {
        TResult ret = T3D_OK;

        FIBITMAP *dib = nullptr;

        do
        {
            uint32_t redMask, greenMask, blueMask, alphaMask;
            image.getColorMask(redMask, greenMask, blueMask, alphaMask);

            dib = FreeImage_ConvertFromRawBitsEx(FALSE, image.getData(), 
                FIT_BITMAP, (int32_t)image.getWidth(), (int32_t)image.getHeight(),
                (int32_t)image.getPitch(), (uint32_t)image.getBPP(),
                redMask, greenMask, blueMask, FALSE);

            if (dib == nullptr)
            {
                ret = T3D_ERR_CODEC_LOAD_FROM_RAW_DATA;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, 
                    "Convert from raw bits failed !");
                break;
            }

            uint32_t clr = color.A8R8G8B8();
            if (!FreeImage_FillBackground(dib, (const void *)&clr))
            {
                ret = T3D_ERR_CODEC_FILL_COLOR;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, 
                    "Fill image failed !");
                break;
            }

            FreeImage_Unload(dib);
            dib = nullptr;
        } while (0);

        if (dib != nullptr)
        {
            FreeImage_Unload(dib);
            dib = nullptr;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult FreeImageCodec::copy(const Image &srcImage, const Rect *srcRect,
        Image &dstImage, const Rect *dstRect, uint32_t filter)
    {
        TResult ret = T3D_OK;
        FIBITMAP *dib = nullptr;
        FIBITMAP *newdib = nullptr;

        do
        {
            // 非空图像，这个有点麻烦了，只能硬头皮来
            // 如果像素格式不一致，直接返回，
            // 请先调用convert接口来转换成一致格式的图像
            if (srcImage.getFormat() != dstImage.getFormat())
            {
                ret = T3D_ERR_CODEC_FORMAT_NOT_SAME;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, 
                    "Source image and destination image are different !");
                break;
            }

            Rect rtDst;
            if (dstRect == nullptr)
            {
                rtDst = Rect(Point(0, 0), Size(srcImage.getWidth(), 
                    srcImage.getHeight()));
            }
            else
            {
                rtDst = *dstRect;
            }

            Rect rtSrc;
            if (srcRect == nullptr)
            {
                rtSrc = Rect(Point(0, 0), Size(srcImage.getWidth(), 
                    srcImage.getHeight()));
            }
            else
            {
                rtSrc = *srcRect;
            }

            // 检验区域有效性
            if (rtSrc.left < 0 || rtSrc.right >= srcImage.getWidth()
                || rtSrc.top < 0 || rtSrc.bottom >= srcImage.getHeight())
            {
                // 超出源图像范围了
                ret = T3D_ERR_OUT_OF_BOUND;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, 
                    "Source image rectangle is out of bound !");
                break;
            }

            if (rtDst.left < 0 || rtDst.right >= dstImage.getWidth()
                || rtDst.top < 0 || rtDst.bottom >= dstImage.getHeight())
            {
                // 超出目标图像范围了
                ret = T3D_ERR_OUT_OF_BOUND;
                T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC,
                    "Destination image rectangle is out of bound !");
                break;
            }

            if (srcImage.getWidth() == dstImage.getWidth() 
                && srcImage.getHeight() == dstImage.getHeight()
                && rtDst == rtSrc)
            {
                // 源和目标区域完全相同，直接点吧
                T3D_ASSERT(srcImage.getSize() == dstImage.getSize());
                size_t size = srcImage.getSize();
                memcpy(dstImage.getData(), srcImage.getData(), size);
            }
            else if (rtSrc.width() == rtDst.width() 
                && rtSrc.height() == rtDst.height())
            {
                // 源和目标区域大小一致，啃下来，自己来复制
                const uint8_t *srcData = srcImage.getData() 
                    + rtSrc.top * srcImage.getPitch()
                    + rtSrc.left * srcImage.getBPP();
                uint8_t *dstData = dstImage.getData()
                    + rtDst.top * dstImage.getPitch() 
                    + rtDst.left * dstImage.getBytesPerPixel();
                const uint8_t *src = srcData;
                uint8_t *dst = dstData;

                size_t pitch 
                    = std::min(srcImage.getPitch(), dstImage.getPitch());

                size_t y = 0;
                for (y = 0; y < rtSrc.height(); ++y)
                {
                    memcpy(dst, src, pitch);
                    dst += dstImage.getPitch();
                    src += srcImage.getPitch();
                }
            }
            else
            {
                // 没办法，自己图像处理算法烂，也懒得去研究，先用FreeImage帮忙吧
                uint32_t redMask, greenMask, blueMask, alphaMask;
                srcImage.getColorMask(redMask, greenMask, blueMask, alphaMask);

                // 把源数据读到FreeImage里面，让FreeImage来处理
                dib = FreeImage_ConvertFromRawBitsEx(FALSE, 
                    (uint8_t*)srcImage.getData(), FIT_BITMAP,
                    (int32_t)srcImage.getWidth(), (int32_t)srcImage.getWidth(),
                    (int32_t)srcImage.getPitch(), (uint32_t)srcImage.getBPP(),
                    redMask, greenMask, blueMask, TRUE);

                if (dib == nullptr)
                {
                    ret = T3D_ERR_CODEC_CONVERT_TO_RAW;
                    T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC,
                        "Convert from raw bits failed !");
                    break;
                }

                // 缩放
                newdib = FreeImage_Rescale(dib, (int32_t)rtDst.width(), 
                    (int32_t)rtDst.height(), (FREE_IMAGE_FILTER)filter);
                if (newdib == nullptr)
                {
                    ret = T3D_ERR_CODEC_SCALE;
                    T3D_LOG_ERROR(LOG_TAG_FREEIMAGE_CODEC, 
                        "Scale image failed !");
                    break;
                }

                // 把转好的数据复制到目标图像上
                uint32_t srcBPP = FreeImage_GetBPP(newdib);
                T3D_ASSERT(srcBPP == srcImage.getBPP());

                uint32_t srcPitch = FreeImage_GetPitch(newdib);
                uint8_t *srcData = FreeImage_GetBits(newdib);

                uint32_t dstPitch = (uint32_t)dstImage.getPitch();
                uint8_t *dstData = dstImage.getData() 
                    + rtDst.top * dstPitch 
                    + rtDst.left * dstImage.getBytesPerPixel();

                uint8_t *src = srcData;
                uint8_t *dst = dstData;
                int32_t y = 0;

                for (y = 0; y < rtDst.height(); ++y)
                {
                    memcpy(dst, src, srcPitch);
                    dst += dstPitch;
                    src += srcPitch;
                }

                // 释放FreeImage对象
                FreeImage_Unload(newdib);
                newdib = nullptr;

                FreeImage_Unload(dib);
                dib = nullptr;
            }
        } while (0);

        if (newdib != nullptr)
        {
            FreeImage_Unload(newdib);
            newdib = nullptr;
        }

        if (dib != nullptr)
        {
            FreeImage_Unload(dib);
            dib = nullptr;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult FreeImageCodec::convert(Image &image, PixelFormat format)
    {
        TResult ret = T3D_OK;


        return ret;
    }

    //--------------------------------------------------------------------------

    TResult FreeImageCodec::convert(const Image &srcImage, Image &dstImage,
        PixelFormat format)
    {
        TResult ret = T3D_OK;

        return ret;
    }
}

