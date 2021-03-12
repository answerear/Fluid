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


#ifndef __T3D_ZIP_ARCHIVE_H__
#define __T3D_ZIP_ARCHIVE_H__


#include "T3DZipArchivePrerequisites.h"


namespace Tiny3D
{
    /**
     * @brief zip 压缩档案结构类，用于访问 zip 压缩包里面的文件
     */
    class ZipArchive : public Archive
    {
        T3D_DECLARE_CLASS();

    public:
        static const char * const ARCHIVE_TYPE; /**< 档案类型 */

        /**
         * @brief 创建对象
         */
        static ZipArchivePtr create(const String &name);

        /**
         * @brief 析构函数
         */
        virtual ~ZipArchive();

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
        ZipArchive(const String &name);

    protected:
        THandle     mZipFile;   /**< zip 压缩文件句柄 */
    };
}


#endif  /*__T3D_ZIP_ARCHIVE_H__*/
