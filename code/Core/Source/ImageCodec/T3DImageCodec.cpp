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

#include "ImageCodec/T3DImageCodec.h"
#include "Resource/T3DArchiveManager.h"
#include "Resource/T3DArchive.h"
#include "T3DErrorDef.h"
#include "Kernel/T3DAgent.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(ImageCodec);
    T3D_IMPLEMENT_CLASS_1(ImageCodec, Object);

    //--------------------------------------------------------------------------

    ImageCodecPtr ImageCodec::create()
    {
        ImageCodecPtr codec = new ImageCodec();
        codec->release();
        return codec;
    }

    //--------------------------------------------------------------------------

    ImageCodec::ImageCodec()
    {

    }

    ImageCodec::~ImageCodec()
    {

    }

    //--------------------------------------------------------------------------

    TResult ImageCodec::addImageCodec(ImageCodecBase::FileType type,
        ImageCodecBasePtr codec)
    {
        TResult ret = T3D_OK;

        mCodecMap.insert(ImageCodecMapValue(type, codec));

        return ret;
    }

    TResult ImageCodec::removeImageCodec(ImageCodecBase::FileType type)
    {
        TResult ret = T3D_OK;

        mCodecMap.erase(type);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ImageCodec::encode(const String &name, const Image &image,
        ImageCodecBase::FileType type /* = ImageCodecBase::FileType::PNG */)
    {
        TResult ret = T3D_OK;

        FileDataStream fs;

        do 
        {
            if (!fs.open(name.c_str(), FileDataStream::E_MODE_WRITE_ONLY))
            {
                ret = T3D_ERR_FILE_NOT_EXIST;
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC,
                    "Open file %s failed when encoding image !",
                    name.c_str());
                break;
            }

            ret = encode(fs, image, type);
            if (T3D_FAILED(ret))
            {
                break;
            }
        } while (0);

        if (fs.isOpened())
        {
            fs.close();
        }

        return ret;
    }

    TResult ImageCodec::encode(DataStream &stream, const Image &image,
        ImageCodecBase::FileType type /* = ImageCodecBase::PNG */)
    {
        TResult ret = T3D_OK;

        do 
        {
            uint8_t *data = nullptr;
            size_t size = 0;

            ret = encode(data, size, image, type);
            if (T3D_FAILED(ret))
            {
                break;
            }

            if (stream.write(data, size) != size)
            {
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC,
                    "Write file content failed !");
            }
            
            T3D_SAFE_DELETE_ARRAY(data);
        } while (0);

        return ret;
    }

    TResult ImageCodec::encode(uint8_t *&data, size_t &size, const Image &image,
        ImageCodecBase::FileType type /* = ImageCodecBase::FileType::PNG */)
    {
        TResult ret = T3D_OK;

        do 
        {
            ImageCodecBasePtr codec = getImageCodec(type);
            if (codec == nullptr)
            {
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC, 
                    "Could not find the destinate image codec !");
                break;
            }

            ret = codec->encode(data, size, image, type);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ImageCodec::decode(const String &name, Image &image,
        ImageCodecBase::FileType type /* = ImageCodecBase::FileType::UNKNOWN */)
    {
        TResult ret = T3D_OK;

        do 
        {
            ArchivePtr archive = T3D_AGENT.getAssetsArchive(name);
            if (archive == nullptr)
            {
                ret = T3D_ERR_IMG_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC,
                    "Could not find the archive for file %s !", name.c_str());
                break;
            }
            
            String path = T3D_AGENT.getMainAssetsPath(name);
            MemoryDataStream stream;
            ret = archive->read(path, stream);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC,
                    "Read image content failed from file %s ! ", name.c_str());
                break;
            }

            ret = decode(stream, image, type);
        } while (0);

        return ret;
    }

    TResult ImageCodec::decode(DataStream &stream, Image &image, 
        ImageCodecBase::FileType type /* = ImageCodecBase::FileType::UNKNOWN */)
    {
        TResult ret = T3D_OK;

        do 
        {
            uint8_t *data = nullptr;
            size_t size = stream.read(data);
            if (size == 0)
            {
                ret = T3D_ERR_FILE_DATA_MISSING;
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC, 
                    "Read image content failed !");
                break;
            }

            ret = decode(data, size, image, type);
        } while (0);

        return ret;
    }

    TResult ImageCodec::decode(uint8_t *data, size_t size, Image &image,
        ImageCodecBase::FileType type /* = ImageCodecBase::FileType::UNKNOWN */)
    {
        TResult ret = T3D_OK;

        do 
        {
            ImageCodecBasePtr codec = getImageCodec(data, size, type);
            if (codec == nullptr)
            {
                ret = T3D_ERR_IMG_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC,
                    "Could not find the image codec !");
                break;
            }

            ret = codec->decode(data, size, image, type);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ImageCodec::flip(Image &image)
    {
        TResult ret = T3D_OK;

        do 
        {
            ImageCodecBasePtr codec = getImageCodec(
                (ImageCodecBase::FileType)image.getSourceType());
            if (codec == nullptr)
            {
                ret = T3D_ERR_IMG_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC,
                    "Could not find the image codec !");
                break;
            }

            ret = codec->flip(image);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ImageCodec::mirror(Image &image)
    {
        TResult ret = T3D_OK;

        do 
        {
            ImageCodecBasePtr codec = getImageCodec(
                (ImageCodecBase::FileType)image.getSourceType());
            if (codec == nullptr)
            {
                ret = T3D_ERR_IMG_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC,
                    "Could not find the image codec !");
                break;
            }

            ret = codec->mirror(image);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ImageCodec::fill(Image &image, const Color4 &color)
    {
        TResult ret = T3D_OK;

        do 
        {
            ImageCodecBasePtr codec = getImageCodec(
                (ImageCodecBase::FileType)image.getSourceType());
            if (codec == nullptr)
            {
                ret = T3D_ERR_IMG_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC,
                    "Could not find the image codec !");
                break;
            }

            ret = codec->fill(image, color);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ImageCodec::copy(const Image &srcImage, const Rect *srcRect, 
        Image &dstImage, const Rect *dstRect, uint32_t filter)
    {
        TResult ret = T3D_OK;

        do 
        {
            ImageCodecBasePtr codec = getImageCodec(
                (ImageCodecBase::FileType)srcImage.getSourceType());
            if (codec == nullptr)
            {
                ret = T3D_ERR_IMG_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC,
                    "Could not find the image codec !");
                break;
            }

            ret = codec->copy(srcImage, srcRect, dstImage, dstRect, filter);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ImageCodec::convert(Image &image, PixelFormat format)
    {
        TResult ret = T3D_OK;

        do
        {
            ImageCodecBasePtr codec = getImageCodec(
                (ImageCodecBase::FileType)image.getSourceType());
            if (codec == nullptr)
            {
                ret = T3D_ERR_IMG_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC,
                    "Could not find the image codec !");
                break;
            }

            ret = codec->convert(image, format);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ImageCodec::convert(const Image &srcImage, Image &dstImage, 
        PixelFormat format)
    {
        TResult ret = T3D_OK;

        do
        {
            ImageCodecBasePtr codec = getImageCodec(
                (ImageCodecBase::FileType)srcImage.getSourceType());
            if (codec == nullptr)
            {
                ret = T3D_ERR_IMG_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_IMAGE_CODEC,
                    "Could not find the image codec !");
                break;
            }

            ret = codec->convert(srcImage, dstImage, format);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    ImageCodecBasePtr ImageCodec::getImageCodec(uint8_t *data, size_t size, 
        ImageCodecBase::FileType &type) const
    {
        ImageCodecBasePtr codec;

        if (type != ImageCodecBase::FileType::UNKNOWN)
        {
            auto itr = mCodecMap.find(type);
            if (itr != mCodecMap.end())
            {
                codec = itr->second;
            }
        }
        else
        {
            auto itr = mCodecMap.begin();
            while (itr != mCodecMap.end())
            {
                if (itr->second->isSupportedType(data, size, type))
                {
                    codec = itr->second;
                    break;
                }
                ++itr;
            }
        }

        return codec;
    }

    ImageCodecBasePtr ImageCodec::getImageCodec(
        ImageCodecBase::FileType type) const
    {
        ImageCodecBasePtr codec;
        auto itr = mCodecMap.find(type);

        if (itr != mCodecMap.end())
        {
            codec = itr->second;
        }

        return codec;
    }
}

