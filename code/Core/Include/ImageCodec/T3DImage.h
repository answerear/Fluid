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


#ifndef __T3D_IMAGE_H__
#define __T3D_IMAGE_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Kernel/T3DCommon.h"


namespace Tiny3D
{
    /**
     * @class   Image
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API Image : public Object
    {
        friend class ImageCodecBase;

        T3D_DECLARE_CLASS();

    public:
        static const uint32_t FILETYPE_RAW;     /**< The filetype raw */
        static const uint32_t FILETYPE_PNG;     /**< The filetype PNG */
        static const uint32_t FILETYPE_JPG;     /**< The filetype JPEG */
        static const uint32_t FILETYPE_BMP;     /**< The filetype bitmap */
        static const uint32_t FILETYPE_TGA;     /**< The filetype tga */
        static const uint32_t FILETYPE_DDS;     /**< The filetype DDS */
        static const uint32_t FILETYPE_PVRTC;   /**< The filetype pvrtc */
        static const uint32_t FILETYPE_ASTC;    /**< The filetype astc */
        static const uint32_t FILETYPE_ETC1;    /**< The first filetype etc */
        static const uint32_t FILETYPE_ETC2;    /**< The second filetype etc */

        /**
         * @enum    Filter
         * @brief   Values that represent filters
         */
        enum class Filter : uint32_t
        {
            /**< Box, pulse, Fourier window, 1st order (constant) b-spline */
            E_FILTER_BOX = 0,
            /**< Mitchell & Netravali's two-param cubic filter */
            E_FILTER_BICUBIC = 1,
            /**< Bilinear filter */
            E_FILTER_BILINEAR = 2,
            /**< 4th order (cubic) b-spline */
            E_FILTER_BSPLINE = 3,
            /**< Catmull-Rom spline, Overhauser spline */
            E_FILTER_CATMULLROM = 4,
            /**< Lanczos3 filter */
            E_FILTER_LANCZOS3 = 5
        };

        /**
         * @fn  Image::Image();
         * @brief   默认构造函数
         */
        Image();

        /**
         * @fn  Image::Image(int32_t width, int32_t height, int32_t bpp, 
         *      PixelFormat format);
         * @brief   构造一个指定宽高图像对象
         * @param   width   The width.
         * @param   height  The height.
         * @param   bpp     The bits per pixel.
         * @param   format  Describes the format to use.
         */
        Image(int32_t width, int32_t height, int32_t bpp, PixelFormat format);

        /**
         * @fn  Image::Image(const Image &other);
         * @brief   拷贝构造函数
         * @param   other   The other.
         */
        Image(const Image &other);

        /**
         * @fn  virtual Image::~Image();
         * @brief   析构函数
         */
        virtual ~Image();

        /**
         * @fn  Image Image::&operator=(const Image &other);
         * @brief   从别的图像对象复制过来
         * @param   other   The other.
         * @return  A shallow copy of this object.
         */
        Image &operator =(const Image &other);

        /**
         * @fn  bool Image::operator==(const Image &other) const;
         * @brief   比较图像是否相同，主要使用图像MD5值来比对
         * @param   other   The other.
         * @return  True if the parameters are considered equivalent.
         */
        bool operator ==(const Image &other) const;

        /**
         * @fn  bool Image::operator!=(const Image &other) const;
         * @brief   比较图像是否不同，主要使用图像MD5值来比对
         * @param   other   The other.
         * @return  True if the parameters are not considered equivalent.
         */
        bool operator !=(const Image &other) const;

        /**
         * @fn  TResult Image::load(const String &path);
         * @brief   从文件加载图像数据
         * @param [in]  path    : 文件全路径.
         * @return  调用成功返回 T3D_OK
         *  @note 本接口读取文件后会自动识别文件格式来解码.
         * @sa  TResult load(DataStream &amp;stream)
         */
        TResult load(const String &path);

        /**
         * @fn  TResult Image::load(DataStream &stream);
         * @brief   从内存加载图像数据
         * @param [in]  stream  : 数据输入流.
         * @return  调用成功返回 T3D_OK
         *  @note 本接口自动识别数据流的格式，并且解析数据流.
         * @sa  TResult load(const String &amp;path);
         */
        TResult load(DataStream &stream);

        /**
         * @fn  TResult Image::load(uint8_t *data, size_t width, size_t height, 
         *      size_t bpp, size_t pitch, PixelFormat format, 
         *      bool copySource = false);
         * @brief   从内存Raw数据加载图像
         * @param [in]  data        : 图像原始数据.
         * @param [in]  width       : 图像宽度.
         * @param [in]  height      : 图像高度.
         * @param [in]  bpp         : 图像色深.
         * @param [in]  pitch       : 图像跨度.
         * @param [in]  format      : 图像像素格式.
         * @param [in]  copySource  (Optional) : 是否深拷贝一份数据到内部维护.
         * @return  调用成功返回 T3D_OK.
         */
        TResult load(uint8_t *data, size_t width, size_t height, size_t bpp,
            size_t pitch, PixelFormat format, bool copySource = false);

        /**
         * @fn  TResult Image::save(const String &path, 
         *      uint32_t ft = FILETYPE_PNG) const;
         * @brief   把图像保存到文件中
         * @param [in]  path    : 文件全路径.
         * @param [in]  ft      (Optional) : 要保存的文件类型，默认是PNG文件.
         * @return  调用成功返回 T3D_OK.
         */
        TResult save(const String &path, uint32_t ft = FILETYPE_PNG) const;

        /**
         * @fn  TResult Image::save(DataStream &stream, 
         *      uint32_t ft = FILETYPE_PNG) const;
         * @brief   把图像保存到文件中
         * @param [in]  stream  : 输出的数据流对象.
         * @param [in]  ft      (Optional) : 要保存的文件类型，默认是PNG文件.
         * @return  调用成功返回 T3D_OK.
         */
        TResult save(DataStream &stream, uint32_t ft = FILETYPE_PNG) const;

        /**
         * @fn  TResult Image::destroy();
         * @brief   销毁图像，使其成为空图像对象
         * @return  销毁成功返回true，否则返回false.
         */
        TResult destroy();

        /**
         * @fn  TResult Image::flip();
         * @brief   上下翻转图像
         * @return  调用成功返回true，否则返回false.
         */
        TResult flip();

        /**
         * @fn  TResult Image::mirror();
         * @brief   左右镜像图像
         * @return  调用成功返回true，否则返回false.
         */
        TResult mirror();

        /**
         * @fn  TResult Image::fill(const Color4 &rkColor);
         * @brief   给图像填充指定颜色
         * @param   rkColor The rk color.
         * @return  A TResult.
         */
        TResult fill(const Color4 &rkColor);

        /**
         * @fn  TResult Image::copy(const Image &image, 
         *      const Rect *srcRect = nullptr, const Rect *dstRect = nullptr, 
         *      Filter filter = Filter::E_FILTER_BILINEAR);
         * @brief   从别的图像对象复制数据过来
         * @param [in]  image   : 源图像.
         * @param [in]  srcRect (Optional) : 要复制的源区域，默认nullptr为整个区域.
         * @param [in]  dstRect (Optional) : 要复制过去的目标区域，默认nullptr为整个区域.
         * @param       filter  (Optional) Specifies the filter.
         * @return  调用成功返回 T3D_OK
         *  @note 当源和目标区域不相同大小时，自动缩放来复制，
         *   源和目标图像必须要像素格式一致，否则调用失败。
         *  @note 当自动缩放时，会导致性能下降.
         */
        TResult copy(const Image &image, const Rect *srcRect = nullptr,
            const Rect *dstRect = nullptr, Filter filter = Filter::E_FILTER_BILINEAR);

        /**
         * @fn  TResult Image::convert(PixelFormat format);
         * @brief   转成目标像素格式的图像
         * @param [in]  format  : 目标像素格式.
         * @return  调用成功返回true，否则返回false.
         */
        TResult convert(PixelFormat format);

        /**
         * @fn  TResult Image::convert(Image &image, PixelFormat format) const;
         * @brief   转成目标像素格式的图像
         * @param [in,out]  image   The image.
         * @param [in]      format  : 目标像素格式.
         * @return  调用成功返回true，否则返回false.
         */
        TResult convert(Image &image, PixelFormat format) const;

        /**
         * @fn  bool Image::compare(const Image &other, 
         *      bool compareAlpha = true) const;
         * @brief   比较图像
         * @param [in]  other           : 另外一个图像对象.
         * @param [in]  compareAlpha    (Optional) : 如果存在alpha通道，是否比较alpha通道，
         *   如果不存在alpha通道，本参数无效.
         * @return  比较出相同返回true，不同返回false
         *  @note 主要是比较图像MD5值.
         */
        bool compare(const Image &other, bool compareAlpha = true) const;

        /**
         * @fn  uint32_t Image::getSourceType() const;
         * @brief   获取数据源类型
         * @return  The source type.
         */
        uint32_t getSourceType() const;

        /**
         * @fn  uint8_t Image::*getData();
         * @brief   返回图像数据
         * @return  Null if it fails, else the data.
         */
        uint8_t *getData();

        /**
         * @fn  const uint8_t * const Image::getData() const;
         * @brief   返回图像数据
         * @return  The data.
         */
        const uint8_t * const getData() const;

        /**
         * @fn  size_t Image::getSize() const;
         * @brief   返回图像数据大小
         * @return  The size.
         */
        size_t getSize() const;

        /**
         * @fn  size_t Image::getWidth() const;
         * @brief   返回图像宽度
         * @return  The width.
         */
        size_t getWidth() const;

        /**
         * @fn  size_t Image::getHeight() const;
         * @brief   返回图像高度
         * @return  The height.
         */
        size_t getHeight() const;

        /**
         * @fn  size_t Image::getPitch() const;
         * @brief   返回图像跨度
         * @return  The pitch.
         */
        size_t getPitch() const;

        /**
         * @fn  size_t Image::getBPP() const;
         * @brief   返回图像色深
         * @return  The bits per pixel.
         */
        size_t getBPP() const;

        /**
         * @fn  PixelFormat Image::getFormat() const;
         * @brief   返回图像像素格式
         * @return  The format.
         */
        PixelFormat getFormat() const;

        /**
         * @fn  bool Image::hasAlpha() const;
         * @brief   返回图像是否带alpha通道
         * @return  True if alpha, false if not.
         */
        bool hasAlpha() const;

        /**
         * @fn  bool Image::isPremultipliedAlpha() const;
         * @brief   返回图像是否做了alpha预乘
         * @return  True if premultiplied alpha, false if not.
         */
        bool isPremultipliedAlpha() const;

        /**
         * @fn  bool Image::isEmpty() const;
         * @brief   返回是否空图像
         * @return  True if empty, false if not.
         */
        bool isEmpty() const;

        /**
         * @fn  void Image::getColorMask(uint32_t &redMask, uint32_t &greenMask, 
         *      uint32_t &blueMask, uint32_t &alphaMask) const;
         * @brief   获取三个颜色通道和一个透明通道的颜色mask
         * @param [in,out]  redMask     The red mask.
         * @param [in,out]  greenMask   The green mask.
         * @param [in,out]  blueMask    The blue mask.
         * @param [in,out]  alphaMask   The alpha mask.
         */
        void getColorMask(uint32_t &redMask, uint32_t &greenMask, 
            uint32_t &blueMask, uint32_t &alphaMask) const;

        /**
         * @fn  static size_t Image::calcPitch(size_t width, size_t bpp);
         * @brief   根据色深计算图像行跨度
         * @param   width   The width.
         * @param   bpp     The bits per pixel.
         * @return  The calculated pitch.
         */
        static size_t calcPitch(size_t width, size_t bpp);

        /**
         * @fn  static size_t Image::getBPP(PixelFormat format);
         * @brief   根据图像像素格式获取色深
         * @param   format  Describes the format to use.
         * @return  The bits per pixel.
         */
        static size_t getBPP(PixelFormat format);

        /**
         * @fn  size_t Image::getBytesPerPixel() const;
         * @brief   获取当前像素格式下一个像素占用的字节数
         * @return  The bytes per pixel.
         */
        size_t getBytesPerPixel() const;

    protected:
        /**
         * @fn  size_t Image::calcPitch() const;
         * @brief   计算图像行跨度
         * @return  The calculated pitch.
         */
        size_t calcPitch() const;

    private:
        uint32_t    mSourceType;        /**< 图像数据源类型 */
        size_t      mWidth;             /**< 图像宽度 */
        size_t      mHeight;            /**< 图像高度 */
        size_t      mBPP;               /**< 图像色深 */
        size_t      mPitch;             /**< 图像行跨度 */

        PixelFormat mFormat;            /**< 图像像素格式 */

        bool        mHasAlpha;          /**< 是否带alpha通道 */
        bool        mIsPreMulti;        /**< 是否预乘alpha */
        bool        mIsDataExternal;    /**< 数据是否外部分配的 */
        bool        mIsEmpty;           /**< 空图像（即没有任何数据的图像） */

        uint8_t     *mData;             /**< 图像数据 */
        size_t      mDataSize;          /**< 图像数据大小 */
    };
}


#include "T3DImage.inl"


#endif  /*__T3D_IMAGE_H__*/
