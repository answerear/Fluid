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


#ifndef __T3D_FS_ARCHIEVE_H__
#define __T3D_FS_ARCHIEVE_H__


#include "T3DFSArchivePrerequisites.h"


namespace Tiny3D
{
    /**
     * @brief 文件系统档案结构类，用于访问文件系统里面的文件
     */
    class FileSystemArchive : public Archive
    {
        T3D_DECLARE_CLASS();

    public:
        static const char * const ARCHIVE_TYPE; /**< 档案类型 */

        /**
         * @brief 创建对象
         */
        static FileSystemArchivePtr create(const String &name);

        /**
         * @brief 析构函数
         */
        virtual ~FileSystemArchive();

        /**
         * @brief 获取档案类型
         */
        virtual String getArchiveType() const override;

    protected:
        /**
         * @brief 重写 Resource::load() 接口
         */
        virtual TResult load() override;

        /**
         * @brief 重写 Resource::unload() 接口
         */
        virtual TResult unload() override;

        /**
         * @brief 重写 Resource::clone() 接口
         */
        virtual ResourcePtr clone() const override;

        /**
         * @brief 重写 Achive::Init(const String &assetPath) 接口
         */
        virtual TResult init(const String& assetPath) override;

        /**
         * @brief 重写 Archieve::getLocation() 接口
         */
        virtual String getLocation() const override;

        /**
         * @brief 重写 Archieve::exists() 接口
         */
        virtual bool exists(const String &name) const override;

        /**
         * @brief 重写 Archieve::read() 接口
         */
        virtual TResult read(const String &name, MemoryDataStream &stream) override;

        /**
         * @brief 重写 Archieve::write() 接口
         */
        virtual TResult write(const String &name, const MemoryDataStream &stream) override;

        /**
         * @brief 构造函数
         */
        FileSystemArchive(const String &name);

        /**
         * @brief 从文件流对象缓存中获取文件流对象
         */
        TResult getFileStreamFromCache(const String &name, FileDataStream *&stream);

        /**
         * @brief 创建文件流缓存
         */
        void initFileStreamCache();

        /**
         * @brief 清除文件流对象缓存
         */
        void clearFileStreamCache();

    protected:
        enum
        {
            MAX_FILE_STREAM_CACHE = 10, /**< 文件流最大的缓存 */
        };

        typedef TMap<String, FileDataStream*>       FileStreamCache;
        typedef FileStreamCache::iterator           FileStreamCacheItr;
        typedef FileStreamCache::const_iterator     FileStreamCacheConstItr;
        typedef FileStreamCache::value_type         FileStreamCacheValue;

        typedef TMap<uint64_t, String>              FileIndexCache;
        typedef FileIndexCache::iterator            FileIndexCacheItr;
        typedef FileIndexCache::const_iterator      FileIndexCacheConstItr;
        typedef FileIndexCache::value_type          FileIndexCacheValue;

        typedef TList<FileDataStream*>              FileStreamPool;
        typedef FileStreamPool::iterator            FileStreamPoolItr;
        typedef FileStreamPool::const_iterator      FileStreamPoolConstItr;

        FileStreamPool  mFileStreamPool;    /**< 空闲文件流对象池 */
        FileIndexCache  mFileIndexCache;    /**< 文件流索引缓存，其中第一个是存在时间最长的对象 */
        FileStreamCache mFileStreamCache;   /**< 使用中的文件流缓存 */
    };
}


#endif  /*__T3D_FS_ARCHIEVE_H__*/
