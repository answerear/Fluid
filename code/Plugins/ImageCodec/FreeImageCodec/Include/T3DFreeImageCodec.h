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


#ifndef __T3D_IMAGE_CODEC_FREEIMAGE_H__
#define __T3D_IMAGE_CODEC_FREEIMAGE_H__


#include "T3DFreeImageCodecPrerequisites.h"


namespace Tiny3D
{
    /**
     * @brief 
     */
    class FreeImageCodec : public ImageCodecBase
    {
        T3D_DECLARE_CLASS();

    public:
        typedef TArray<ImageCodecBase::FileType>    FileTypeList;
        typedef FileTypeList::iterator              FileTypeListItr;
        typedef FileTypeList::const_iterator        FileTypeListConstItr;

        /**
         * @brief 创建 FreeImageCodec 对象
         */
        static FreeImageCodecPtr create();

        /**
         * @brief 初始化和启动图像编解码器
         * @return 调用成功返回 T3D_OK
         */
        TResult startup();

        /**
         * @brief 关闭图像编解码器并且清理其使用的资源
         * @return 调用成功返回 T3D_OK
         */
        TResult shutdown();

        /**
         * @brief 是否支持的类型，实现基类接口
         */
        virtual bool isSupportedType(uint8_t *data, size_t size,
            FileType &type) const override;

        /**
         * @brief 获取文件类型，实现基类接口
         */
        virtual FileType getFileType() const override;

        /**
         * @brief 把图像对象编码到数据缓冲中，实现基类接口
         */
        virtual TResult encode(uint8_t *&data, size_t &size, const Image &image,
            FileType type) override;

        /**
         * @brief 把缓冲数据解码到图像对象中，实现基类接口
         */
        virtual TResult decode(uint8_t *data, size_t size, Image &image,
            FileType type) override;

        /**
         * @brief 颠倒图像，实现基类接口
         */
        virtual TResult flip(Image &image) override;

        /**
         * @brief 镜像图像，实现基类接口
         */
        virtual TResult mirror(Image &image) override;

        /**
         * @brief 用指定颜色填充图像，实现基类接口
         */
        virtual TResult fill(Image &image, const Color4 &color) override;

        /**
         * @brief 复制源图像指定区域数据到目标图像指定区域，实现基类接口
         */
        virtual TResult copy(const Image &srcImage, const Rect *srcRect,
            Image &dstImage, const Rect *dstRect, uint32_t filter) override;

        /**
         * @brief 转换到目标像素格式，实现基类接口
         */
        virtual TResult convert(Image &image, PixelFormat format) override;

        /**
         * @brief 把源图像转换成目标像素格式并生成一个新的图像对象，实现基类接口
         */
        virtual TResult convert(const Image &srcImage, Image &dstImage,
            PixelFormat format) override;

        /**
         * @brief 获取支持的文件类型列表
         */
        FileTypeList getSupportFileTypeList() const
        {
            return mFileTypeList;
        }

    protected:
        FileTypeList    mFileTypeList;

        static const size_t MAX_SUPPORTED_FILE_TYPE;
    };
}


#endif  /*__T3D_IMAGE_CODEC_FREEIMAGE_H__*/
