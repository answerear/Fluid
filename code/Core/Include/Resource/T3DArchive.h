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


#ifndef __T3D_ARCHIVE_H__
#define __T3D_ARCHIVE_H__


#include "T3DResource.h"


namespace Tiny3D
{
    /**
     * @class   Archive
     * @brief   档案类，用于档案文件的组织管理，隔离文件系统、zip压缩文件的实现细节
     */
    class T3D_ENGINE_API Archive : public Resource
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  virtual Archive::~Archive();
         * @brief   析构函数
         */
        virtual ~Archive();

        /**
         * @fn  virtual Type Archive::getType() const override;
         * @brief   获取资源类型，重写基类 Resource::getType() 接口
         * @return  The type.
         */
        virtual Type getType() const override;

        /**
         * @fn virtual TResult init(const String &assetPath);
         * @brief   初始化档案系统
         * @param [in]  assetPath   : 资源根目录
         * @return  调用成功返回 T3D_OK
         */
        virtual TResult init(const String &assetPath) = 0;

        /**
         * @fn  virtual String Archive::getArchiveType() const = 0;
         * @brief   获取档案结构类型
         * @return  The archive type.
         */
        virtual String getArchiveType() const = 0;

        /**
         * @fn  virtual String Archive::getLocation() const = 0;
         * @brief   获取档案位置
         * @return  The location.
         */
        virtual String getLocation() const = 0;

        /**
         * @fn  virtual bool Archive::exists(const String &name) const = 0;
         * @brief   指定文件是否在档案结构里
         * @param [in]  name    : 文件名称.
         * @return  存在就返回true，否则返回false。.
         */
        virtual bool exists(const String &name) const = 0;

        /**
         * @fn  virtual TResult Archive::read(const String &name, 
         *      MemoryDataStream &stream) = 0;
         * @brief   从档案读取指定文件到数据流中
         * @param [in]  name    : 文件名称.
         * @param [in]  stream  stream : 数据流.
         * @return  读成功返回T3D_OK.
         */
        virtual TResult read(const String &name, MemoryDataStream &stream) = 0;

        /**
         * @fn  virtual TResult Archive::write(const String &name, 
         *      const MemoryDataStream &stream) = 0;
         * @brief   写数据流到档案里的指定文件中
         * @param [in]  name    : 文件名称.
         * @param [in]  stream  : 数据流.
         * @return  写成功返回T3D_OK.
         */
        virtual TResult write(const String &name, const MemoryDataStream &stream) = 0;

    protected:
        /**
         * @fn  Archive::Archive(const String &name);
         * @brief   构造函数
         * @param [in]  name    : 资源名称，一般使用档案路径作为名称.
         */
        Archive(const String &name);
    };
}


#endif  /*__T3D_ARCHIVE_H__*/
