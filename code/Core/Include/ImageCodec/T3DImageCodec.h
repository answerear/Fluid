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


#ifndef __T3D_IMAGE_CODEC_H__
#define __T3D_IMAGE_CODEC_H__


#include "ImageCodec/T3DImageCodecBase.h"
#include "Kernel/T3DObject.h"


namespace Tiny3D
{
    /**
     * @class   ImageCodec
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API ImageCodec
        : public Singleton<ImageCodec>
        , public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static ImageCodecPtr create();
         * @brief   创建对象
         * @return  An ImageCodecPtr.
         */
        static ImageCodecPtr create();

        /**
         * @fn  virtual ~ImageCodec();
         * @brief   析构函数
         */
        virtual ~ImageCodec();

        /**
         * @fn  TResult addImageCodec(ImageCodecBase::FileType type, 
         *      ImageCodecBasePtr codec);
         * @brief   添加图像编解码器对象
         * @param [in]  type    : 文件类型.
         * @param [in]  codec   : 编解码器对象.
         * @return  调用成功返回 T3D_OK.
         */
        TResult addImageCodec(ImageCodecBase::FileType type,
            ImageCodecBasePtr codec);

        /**
         * @fn  TResult removeImageCodec(ImageCodecBase::FileType type);
         * @brief   移除图像编解码器对象
         * @param [in]  type    : 文件类型.
         * @return  调用成功返回 T3D_OK.
         */
        TResult removeImageCodec(ImageCodecBase::FileType type);

        /**
         * @fn  TResult encode(const String &name, const Image &image, 
         *      ImageCodecBase::FileType type = ImageCodecBase::FileType::PNG);
         * @brief   编码到指定文件名的文件
         * @param [in]  name    : 文件名.
         * @param [in]  image   : 数据源的图像对象.
         * @param [in]  type    (Optional) : 图像文件格式类型，默认PNG格式.
         * @return  调用成功返回 T3D_OK.
         */
        TResult encode(const String &name, const Image &image, 
            ImageCodecBase::FileType type = ImageCodecBase::FileType::PNG);

        /**
         * @fn  TResult encode(DataStream &stream, const Image &image, 
         *      ImageCodecBase::FileType type = ImageCodecBase::FileType::PNG);
         * @brief   编码到数据流对象
         * @param [in]  stream  stream : 数据流对象.
         * @param [in]  image   : 数据源的图像对象.
         * @param [in]  type    (Optional) : 图像文件格式类型，默认PNG格式.
         * @return  调用成功返回 T3D_OK.
         */
        TResult encode(DataStream &stream, const Image &image, 
            ImageCodecBase::FileType type = ImageCodecBase::FileType::PNG);

        /**
         * @fn  TResult encode(uint8_t *&data, size_t &size, const Image &image, 
         *      ImageCodecBase::FileType type = ImageCodecBase::FileType::PNG);
         * @brief   编码到数据缓冲
         * @param [in]  data    data : 编码后返回的数据缓冲区.
         * @param [in]  size    size : 编码后返回的数据缓冲区大小.
         * @param       image   The image.
         * @param [in]  type    (Optional) : 图像文件格式类型，默认PNG格式.
         * @return  调用成功返回 T3D_OK.
         */
        TResult encode(uint8_t *&data, size_t &size, const Image &image, 
            ImageCodecBase::FileType type = ImageCodecBase::FileType::PNG);

        /**
         * @fn  TResult decode(const String &name, Image &image, 
         *      ImageCodecBase::FileType type = ImageCodecBase::FileType::UNKNOWN);
         * @brief   把指定文件读取并解码到图像对象中
         * @param [in]  name    : 图像文件路径.
         * @param [in]  image   image : 图像对象.
         * @param [in]  type    (Optional) : 图像文件格式类型，默认是根据文件内容自动判断.
         * @return  调用成功返回 T3D_OK.
         */
        TResult decode(const String &name, Image &image, 
            ImageCodecBase::FileType type = ImageCodecBase::FileType::UNKNOWN);

        /**
         * @fn  TResult decode(DataStream &stream, Image &image, 
         *      ImageCodecBase::FileType type = ImageCodecBase::FileType::UNKNOWN);
         * @brief   把数据流对象中的数据解码到图像对象中
         * @param [in]  stream  : 数据流对象.
         * @param [in]  image   image : 图像对象.
         * @param [in]  type    (Optional) : 图像文件格式类型，默认是根据数据流内容自动判断.
         * @return  调用成功返回 T3D_OK.
         */
        TResult decode(DataStream &stream, Image &image, 
            ImageCodecBase::FileType type = ImageCodecBase::FileType::UNKNOWN);

        /**
         * @fn  TResult decode(uint8_t *data, size_t size, Image &image, 
         *      ImageCodecBase::FileType type = ImageCodecBase::FileType::UNKNOWN);
         * @brief   把数据缓冲中的数据解码到图像对象中
         * @param [in]      data    : 要解码的数据缓冲区.
         * @param [in]      size    : 要解码的数据缓冲区大小.
         * @param [in,out]  image   The image.
         * @param [in]      type    (Optional) : 图像文件格式类型，默认是根据数据流内容自动判断.
         * @return  调用成功返回 T3D_OK.
         */
        TResult decode(uint8_t *data, size_t size, Image &image, 
            ImageCodecBase::FileType type = ImageCodecBase::FileType::UNKNOWN);

        /**
         * @fn  TResult flip(Image &image);
         * @brief   颠倒图像
         * @param [in]  image   image : 需要颠倒的图像对象.
         * @return  调用成功返回 T3D_OK.
         */
        TResult flip(Image &image);

        /**
         * @fn  TResult mirror(Image &image);
         * @brief   镜像图像
         * @param [in]  image   image : 需要镜像的图像对象.
         * @return  调用成功返回 T3D_OK.
         */
        TResult mirror(Image &image);

        /**
         * @fn  TResult fill(Image &image, const Color4 &color);
         * @brief   用指定颜色填充图像
         * @param [in]  image   image : 需要填充的图像对象.
         * @param [in]  color   : 需要填充的颜色.
         * @return  调用成功返回 T3D_OK.
         */
        TResult fill(Image &image, const Color4 &color);

        /**
         * @fn  TResult copy(const Image &srcImage, const Rect *srcRect, 
         *      Image &dstImage, const Rect *dstRect, uint32_t filter);
         * @brief   复制源图像指定区域数据到目标图像指定区域
         * @param [in]  srcImage    : 源图像对象.
         * @param [in]  srcRect     : 源图像区域.
         * @param [in]  dstImage    dstImage : 目标图像对象.
         * @param [in]  dstRect     : 目标图像区域.
         * @param [in]  filter      : 缩放时候使用的算法.
         * @return  调用成功返回 T3D_OK.
         */
        TResult copy(const Image &srcImage, const Rect *srcRect,
            Image &dstImage, const Rect *dstRect, uint32_t filter);

        /**
         * @fn  TResult convert(Image &image, PixelFormat format);
         * @brief   转换到目标像素格式
         * @param [in]  image   image : 需要转换像素格式图像对象.
         * @param [in]  format  : 目标图像像素格式.
         * @return  调用成功返回 T3D_OK.
         */
        TResult convert(Image &image, PixelFormat format);

        /**
         * @fn  TResult convert(const Image &srcImage, Image &dstImage, 
         *      PixelFormat format);
         * @brief   把源图像转换成目标像素格式并生成一个新的图像对象
         * @param [in]  srcImage    : 源图像对象.
         * @param [in]  dstImage    dstImage : 目标图像对象.
         * @param [in]  format      : 目标像素格式.
         * @return  调用成功返回 T3D_OK.
         */
        TResult convert(const Image &srcImage, Image &dstImage,
            PixelFormat format);

    protected:
        /**
         * @fn  ImageCodec();
         * @brief   构造函数
         */
        ImageCodec();

        /**
         * @fn  ImageCodecBasePtr getImageCodec(uint8_t *data, size_t size, 
         *      ImageCodecBase::FileType &type) const;
         * @brief   根据缓冲区内容获取图像编解码器对象
         * @param [in]  data    : 数据缓冲区.
         * @param [in]  size    : 数据缓冲区大小.
         * @param [in]  type    : 数据缓冲区对应的文件类型.
         * @return  调用成功返回对应的图像编解码器对象，否则返回 nullptr.
         */
        ImageCodecBasePtr getImageCodec(uint8_t *data, size_t size, 
            ImageCodecBase::FileType &type) const;

        /**
         * @fn  ImageCodecBasePtr getImageCodec(
         *      ImageCodecBase::FileType type) const;
         * @brief   根据类型获取图像编解码器对象
         * @param [in]  type    : 图像数据格式类型.
         * @return  调用成功返回对应的图像编解码器对象，否则返回 nullptr.
         */
        ImageCodecBasePtr getImageCodec(ImageCodecBase::FileType type) const;

        typedef TMap<ImageCodecBase::FileType, ImageCodecBasePtr> ImageCodecMap;
        typedef ImageCodecMap::iterator             ImageCodecMapItr;
        typedef ImageCodecMap::const_iterator       ImageCodecMapConstItr;
        typedef ImageCodecMap::value_type           ImageCodecMapValue;

        ImageCodecMap   mCodecMap;  /**< The codec map */
    };

    #define T3D_IMAGE_CODEC     ImageCodec::getInstance()
}


#endif  /*__T3D_IMAGE_CODEC_H__*/
