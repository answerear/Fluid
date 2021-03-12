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

#ifndef __T3D_DIR_INTERFACE_H__
#define __T3D_DIR_INTERFACE_H__


#include "T3DPlatformPrerequisites.h"
#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DClass.h"


namespace Tiny3D
{
    /**
     * @class IDirAdapter
     * @brief 操作系统相关平台层的目录树搜索接口类.
     * @note 相关操作系统平台需要继承该接口类实现具体平台相关功能.
     */
    class IDir
    {
        T3D_DECLARE_INTERFACE(IDir);
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 开始枚举搜索指定目录下的文件.
         * @param [in] strPath : 指定目录文件格式字符串
         * @return 调用成功返回true，失败返回false.
         */
        virtual bool findFile(const String &strPath) = 0;

        /**
         * @brief 搜索下一个文件.
         * @return 枚举没结束返回true，否则返回false表示枚举结束.
         */
        virtual bool findNextFile() = 0;

        /**
         * @brief 结束当前枚举搜索.
         * @return void
         */
        virtual void close() = 0;

        /**
         * @brief 获取枚举目录的完整路径.
         * @return 返回枚举目录的路径，返回类型std::string.
         */
        virtual String getRoot() const = 0;

        /**
         * @brief 获取当前枚举到的完整文件名.
         * @return 返回当前枚举到的完整文件名，类型std::string.
         */
        virtual String getFileName() const = 0;

        /**
         * @brief 获取当前枚举到的文件的全路径名，包括完整文件名.
         * @return 返回当前枚举到的文件的全路径名，类型std::string.
         */
        virtual String getFilePath() const = 0;

        /**
         * @brief 获取当前枚举到的文件文件名，不包括扩展名.
         * @return 返回当前枚举到的文件文件名，类型std::string.
         */
        virtual String getFileTitle() const = 0;

        /**
         * @brief 获取当前枚举到的文件大小.
         * @return 返回当前枚举到的文件大小.
         */
        virtual uint32_t getLength() const = 0;

        /**
         * @brief 判断当前枚举到的文件是否点目录，包括'.'和'..' .
         * @return 点目录返回true，否则返回false.
         */
        virtual bool isDots() const = 0;

        /**
         * @brief 判断当前枚举到的文件是否文件夹.
         * @return 文件返回true，否则返回false.
         */
        virtual bool isDirectory() const = 0;

        /**
         * @brief 获取当前枚举到的文件的创建时间戳.
         * @return 返回文件创建时间戳，该时间是从1970年1月1日到当前的秒数
         */
        virtual long_t getCreationTime() const = 0;

        /**
         * @brief 获取当前枚举到的文件的最后访问时间戳.
         * @return 返回文件最后访问时间戳，该时间是从1970年1月1日到当前的秒数
         */
        virtual long_t getLastAccessTime() const = 0;

        /**
         * @brief 获取当前枚举到的文件的最后修改时间戳.
         * @return 返回文件最后修改时间戳，该时间是从1970年1月1日到当前的秒数
         */
        virtual long_t getLastWriteTime() const = 0;

        /**
         * @brief 创建文件夹.
         * @note 该接口不能创建多级文件夹.
         * @param [in] strDir : 文件夹路径名称
         * @return 调用成功返回true，否则返回false.
         */
        virtual bool makeDir(const String &strDir) = 0;

        /**
         * @brief 删除文件夹.
         * @note 该接口不能删除多级文件夹.
         * @param [in] strDir : 文件夹路径名称
         * @return 调用成功返回true，否则返回false.
         */
        virtual bool removeDir(const String &strDir) = 0;

        /**
         * @brief 删除文件.
         * @param [in] strFileName : 需要删除文件的名称.
         * @return 调用成功返回true，否则返回false.
         */
        virtual bool remove(const String &strFileName) = 0;

        /**
         * @brief 判断路径对应的文件是否存在.
         * @param [in] strPath : 完整路径名
         * @return 文件存在返回true，否则返回false.
         */
        virtual bool exists(const String &strPath) const = 0;

        /**
         * @brief 获取应用程序缓存数据存储路径，不同平台指定对应的路径
         * @return 返回应用程序缓存数据存储路径.
         */
        virtual String getCachePath() const = 0;

        /**
         * @brief 获取应用程序路径
         * @return 返回应用程序路径
         */
        virtual String getAppPath() const = 0;

        /**
         * @brief 获取动态库路径
         * @return 返回动态库路径
         * @remarks 本接口在android上才有效，其他平台跟getAppPath()相同
         */
        virtual String getLibraryPath() const = 0;

        /**
         * @brief 获取应用程序可写路径，不同平台指定对应的路径
         * @return 返回应用程序可写路径.
         */
        virtual String getWritablePath() const = 0;

        virtual char getNativeSeparator() const = 0;
    };
}


#endif  /*__T3D_DIR_INTERFACE_H__*/
