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


#ifndef __T3D_IMAGE_CODEC_BASE_H__
#define __T3D_IMAGE_CODEC_BASE_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Kernel/T3DCommon.h"
#include "ImageCodec/T3DImage.h"


namespace Tiny3D
{
    /**
     * @class   ImageCodecBase
     * @brief   图像编解码基类
     * @remarks 具体对应的图像编解码类需要继承本类并实现具体的逻辑.
     */
    class T3D_ENGINE_API ImageCodecBase : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
        * @brief 支持的图像类型
        */
        enum class FileType : uint32_t
        {
            UNKNOWN = 0xFFFFFFFF,      /**< 未知图像类型 */
            BMP = 0,           /**< Bitmap */
            ICO = 1,           /**< Windows 图标  */
            JPEG = 2,          /**< JPEG */
            JNG = 3,           /**< JNG */
            KOALA = 4,  /**< An enum constant representing the koala option */
            LBM = 5,    /**< An enum constant representing the lbm option */
            IFF = LBM,  /**< An enum constant representing the iff option */
            MNG = 6,    /**< An enum constant representing the mng option */
            PBM = 7,    /**< An enum constant representing the Portable bitmap option */
            PBMRAW = 8, /**< An enum constant representing the pbmraw option */
            PCD = 9,    /**< An enum constant representing the pcd option */
            PCX = 10,
            PGM = 11,
            PGMRAW = 12,
            PNG = 13,
            PPM = 14,
            PPMRAW = 15,
            RAS = 16,
            TARGA = 17,
            TIFF = 18,
            WBMP = 19,
            PSD = 20,
            CUT = 21,
            XBM = 22,
            XPM = 23,
            DDS = 24,
            GIF = 25,
            HDR = 26,
            FAXG3 = 27,
            SGI = 28,
            EXR = 29,
            J2K = 30,
            JP2 = 31,
            PFM = 32,
            PICT = 33,
            RAW = 34,
            WEBP = 35,
            JXR = 36,
            IMG = 37,
            PVRTC = 38,
            ASTC = 39,
            ETC1 = 40,
            ETC2 = 41,
            MAX_TYPE_SUPPORTED,
        };

        /**
         * @fn  virtual ImageCodecBase::~ImageCodecBase();
         * @brief   析构函数
         */
        virtual ~ImageCodecBase();

        /**
         * @fn  virtual bool ImageCodecBase::isSupportedType(uint8_t *data, size_t size, FileType &type) const = 0;
         * @brief   是否支持的类型
         * @param [in]  data    : 图像数据.
         * @param [in]  size    : 图像数据大小.
         * @param [in]  type    : 图像文件类型，默认可以自动识别.
         * @return  支持的返回true，否则返回false.
         * @remarks 具体图像类型编解码器实现本接口.
         */
        virtual bool isSupportedType(uint8_t *data, size_t size,
            FileType &type) const = 0;

        /**
         * @fn  virtual FileType ImageCodecBase::getFileType() const = 0;
         * @brief   获取文件类型
         * @return  返回文件类型.
         * @remarks 具体图像类型编解码器实现本接口.
         */
        virtual FileType getFileType() const = 0;

        /**
         * @fn  virtual TResult ImageCodecBase::encode(uint8_t *&data, 
         *      size_t &size, const Image &image, FileType type) = 0;
         * @brief   把图像对象编码到数据缓冲中
         * @param [in]  data    data : 编码后的数据.
         * @param [in]  size    size : 编码后的数据大小.
         * @param [in]  image   : 图像对象，数据源.
         * @param [in]  type    : 文件类型.
         * @return  调用成功返回 T3D_OK.
         * @remarks 具体图像类型编解码器实现本接口.
         */
        virtual TResult encode(uint8_t *&data, size_t &size, const Image &image,
            FileType type) = 0;

        /**
         * @fn  virtual TResult ImageCodecBase::decode(uint8_t *data, 
         *      size_t size, Image &image, FileType type) = 0;
         * @brief   把缓冲数据解码到图像对象中
         * @param [in]  data    : 要解码的数据.
         * @param [in]  size    : 要解码的数据大小.
         * @param [in]  image   : 图像对象，解码后的数据保存在此对象中.
         * @param [in]  type    : 图像类型.
         * @return  调用成功返回 T3D_OK.
         * @remarks  具体图像类型编解码器实现本接口.
         */
        virtual TResult decode(uint8_t *data, size_t size, Image &image,
            FileType type) = 0;

        /**
         * @fn  virtual TResult ImageCodecBase::flip(Image &image) = 0;
         * @brief   颠倒图像
         * @param [in]  image   image : 需要颠倒的图像对象.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult flip(Image &image) = 0;

        /**
         * @fn  virtual TResult ImageCodecBase::mirror(Image &image) = 0;
         * @brief   镜像图像
         * @param [in]  image   image : 需要镜像的图像对象.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult mirror(Image &image) = 0;

        /**
         * @fn  virtual TResult ImageCodecBase::fill(Image &image, 
         *      const Color4 &color) = 0;
         * @brief   用指定颜色填充图像
         * @param [in]  image   image : 需要填充的图像对象.
         * @param [in]  color   : 需要填充的颜色.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult fill(Image &image, const Color4 &color) = 0;

        /**
         * @fn  virtual TResult ImageCodecBase::copy(const Image &srcImage, 
         *      const Rect *srcRect, Image &dstImage, const Rect *dstRect, 
         *      uint32_t filter) = 0;
         * @brief   复制源图像指定区域数据到目标图像指定区域
         * @param [in]  srcImage    : 源图像对象.
         * @param [in]  srcRect     : 源图像区域.
         * @param [in]  dstImage    dstImage : 目标图像对象.
         * @param [in]  dstRect     : 目标图像区域.
         * @param [in]  filter      : 缩放时候使用的算法.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult copy(const Image &srcImage, const Rect *srcRect,
            Image &dstImage, const Rect *dstRect, uint32_t filter) = 0;

        /**
         * @fn  virtual TResult ImageCodecBase::convert(Image &image, 
         *      PixelFormat format) = 0;
         * @brief   转换到目标像素格式
         * @param [in]  image   image : 需要转换像素格式图像对象.
         * @param [in]  format  : 目标图像像素格式.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult convert(Image &image, PixelFormat format) = 0;

        /**
         * @fn  virtual TResult ImageCodecBase::convert(const Image &srcImage, 
         *      Image &dstImage, PixelFormat format) = 0;
         * @brief   把源图像转换成目标像素格式并生成一个新的图像对象
         * @param [in]  srcImage    : 源图像对象.
         * @param [in]  dstImage    dstImage : 目标图像对象.
         * @param [in]  format      : 目标像素格式.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult convert(const Image &srcImage, Image &dstImage,
            PixelFormat format) = 0;

    protected:
        /**
         * @fn  void ImageCodecBase::setImageData(Image &image, uint8_t *data, 
         *      size_t size);
         * @brief   设置图像数据
         * @param [in]  image   : 需要设置数据的图像对象.
         * @param [in]  data    : 解码后的ARGB数据.
         * @param [in]  size    : 解码后的ARGB数据大小.
         */
        void setImageData(Image &image, uint8_t *data, size_t size);

        /**
         * @fn  void ImageCodecBase::setImageDimension(Image &image, 
         *      int32_t width, int32_t height, int32_t pitch);
         * @brief   设置图像尺寸
         * @param [in]  image   : 需要设置尺寸的图像对象.
         * @param [in]  width   : 图像宽度.
         * @param [in]  height  : 图像高度.
         * @param [in]  pitch   : 图像跨度.
         */
        void setImageDimension(Image &image, int32_t width, int32_t height,
            int32_t pitch);

        /**
         * @fn  void ImageCodecBase::setImageInfo(Image &image, 
         *      uint32_t sourceType, int32_t bpp, bool hasAlpha, 
         *      bool isPreMulti, PixelFormat format);
         * @brief   设置图像信息
         * @param [in]  image       : 需要设置信息的图像对象.
         * @param [in]  sourceType  : 数据来源的文件类型.
         * @param [in]  bpp         : 图像色深.
         * @param [in]  hasAlpha    : 是否有透明通道.
         * @param [in]  isPreMulti  : 是否预乘.
         * @param [in]  format      : 像素格式.
         */
        void setImageInfo(Image &image, uint32_t sourceType, int32_t bpp,
            bool hasAlpha, bool isPreMulti, PixelFormat format);
    };
}


#include "T3DImageCodecBase.inl"


#endif  /*__T3D_IMAGE_CODEC_BASE_H__*/
