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


#include "T3DFSArchive.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(FileSystemArchive, Archive);

    //--------------------------------------------------------------------------

    const char * const FileSystemArchive::ARCHIVE_TYPE = "FileSystem";

    //--------------------------------------------------------------------------

    FileSystemArchivePtr FileSystemArchive::create(const String &name)
    {
        FileSystemArchivePtr archive = new FileSystemArchive(name);
        archive->release();
        return archive;
    }

    //--------------------------------------------------------------------------

    FileSystemArchive::FileSystemArchive(const String &name)
        : Archive(name)
    {

    }

    //--------------------------------------------------------------------------

    FileSystemArchive::~FileSystemArchive()
    {
        clearFileStreamCache();
    }

    //--------------------------------------------------------------------------

    TResult FileSystemArchive::load()
    {
        initFileStreamCache();
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult FileSystemArchive::unload()
    {
        clearFileStreamCache();
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    ResourcePtr FileSystemArchive::clone() const
    {
        ArchivePtr archive = create(mName);
        return archive;
    }

    //--------------------------------------------------------------------------

    String FileSystemArchive::getArchiveType() const
    {
        return ARCHIVE_TYPE;
    }

    //--------------------------------------------------------------------------

    String FileSystemArchive::getLocation() const
    {
        return getName();
    }

    //--------------------------------------------------------------------------

    TResult FileSystemArchive::init(const String& assetPath)
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    bool FileSystemArchive::exists(const String &name) const
    {
        String path = getLocation() + Dir::getNativeSeparator() + name;
        return Dir::exists(path);
    }

    //--------------------------------------------------------------------------

    TResult FileSystemArchive::read(const String &name, 
        MemoryDataStream &stream)
    {
        String path = getLocation() + Dir::getNativeSeparator() + name;
        FileDataStream *fs = nullptr;
        TResult ret = T3D_OK;

        do 
        {
            ret = getFileStreamFromCache(name, fs);
            if (T3D_FAILED(ret))
            {
                break;
            }

            if (!fs->isOpened())
            {
                // 文件没有打开，先打开文件
                if (!fs->open(path.c_str(), FileDataStream::E_MODE_READ_WRITE))
                {
                    ret = T3D_ERR_FILE_NOT_EXIST;
                    T3D_LOG_ERROR(LOG_TAG_FILESYSTEM, "Open file [%s] from file"
                         " system failed !", name.c_str());
                    break;
                }
            }

            size_t size = fs->size();
            uint8_t *data = new uint8_t[size];
            if (fs->read(data, size) != size)
            {
                ret = T3D_ERR_FILE_DATA_MISSING;
                T3D_LOG_ERROR(LOG_TAG_FILESYSTEM, "Read file [%s] from file "
                    "system failed !", name.c_str());
                break;
            }

            stream.setBuffer(data, size, false);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult FileSystemArchive::write(const String &name, 
        const MemoryDataStream &stream)
    {
        String path = getLocation() + Dir::getNativeSeparator() + name;
        FileDataStream *fs = nullptr;
        TResult ret = T3D_OK;

        do 
        {
            ret = getFileStreamFromCache(name, fs);
            if (T3D_FAILED(ret))
            {
                break;
            }

            if (!fs->isOpened())
            {
                // 文件没有打开，先打开文件
                if (!fs->open(path.c_str(), FileDataStream::E_MODE_READ_WRITE))
                {
                    ret = T3D_ERR_FILE_NOT_EXIST;
                    T3D_LOG_ERROR(LOG_TAG_FILESYSTEM, "Open file [%s] from file"
                         " system failed !", name.c_str());
                    break;
                }
            }

            uint8_t *data = nullptr;
            size_t size = 0;
            stream.getBuffer(data, size);
            if (fs->write(data, size) != size)
            {
                ret = T3D_ERR_FILE_DATA_MISSING;
                T3D_LOG_ERROR(LOG_TAG_FILESYSTEM, "Write file [%s] from file "
                    "system failed !", name.c_str());
                break;
            }

        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult FileSystemArchive::getFileStreamFromCache(const String &name,
        FileDataStream *&stream)
    {
        TResult ret = T3D_OK;

        do 
        {
            auto itr = mFileStreamCache.find(name);

            if (itr != mFileStreamCache.end())
            {
                stream = itr->second;
            }
            else
            {
                if (mFileStreamCache.size() >= MAX_FILE_STREAM_CACHE)
                {
                    // 大于可缓存最大文件流数，需要删掉最老的一个，
                    // 来存放最新打开的文件流
                    auto itr = mFileIndexCache.begin();

                    auto i = mFileStreamCache.find(itr->second);

                    if (i != mFileStreamCache.end())
                    {
                        FileDataStream *fs = i->second;

                        if (fs->isOpened())
                        {
                            fs->close();
                        }

                        mFileStreamCache.erase(i);
                        mFileIndexCache.erase(itr);
                        stream = fs;
                    }
                }
                else
                {
                    // 没有大于缓存，从空闲缓存链表获取空闲对象
                    FileDataStream *fs = mFileStreamPool.front();
                    mFileStreamPool.pop_front();
                    stream = fs;
                }

                uint64_t timestamp = DateTime::currentMSecsSinceEpoch();
                mFileIndexCache.insert(FileIndexCacheValue(timestamp, name));
                mFileStreamCache.insert(FileStreamCacheValue(name, stream));
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void FileSystemArchive::initFileStreamCache()
    {
        size_t i = 0;
        for (i = 0; i < MAX_FILE_STREAM_CACHE; ++i)
        {
            FileDataStream *fs = new FileDataStream();
            mFileStreamPool.push_back(fs);
        }
    }

    //--------------------------------------------------------------------------

    void FileSystemArchive::clearFileStreamCache()
    {
        auto itr = mFileStreamPool.begin();

        while (itr != mFileStreamPool.end())
        {
            FileDataStream *fs = *itr;
            T3D_SAFE_DELETE(fs);
            ++itr;
        }

        mFileStreamPool.clear();

        auto i = mFileStreamCache.begin();

        while (i != mFileStreamCache.end())
        {
            FileDataStream *fs = i->second;
            T3D_SAFE_DELETE(fs);
            ++i;
        }

        mFileStreamCache.clear();
    }
}

