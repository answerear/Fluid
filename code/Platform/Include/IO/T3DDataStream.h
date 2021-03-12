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

#ifndef __T3D_DATA_STREAM_H__
#define __T3D_DATA_STREAM_H__


#include "T3DType.h"
#include "T3DMacro.h"
#include "T3DPlatformPrerequisites.h"
#include "T3DClass.h"


namespace Tiny3D
{
    class T3D_PLATFORM_API DataStream
    {
        T3D_DECLARE_INTERFACE(DataStream);
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 从数据流中读数据到缓冲区.
         * @param [in] pBuffer : 数据缓冲区
         * @param [in] nSize : 数据缓冲区大小
         * @return 返回读取到的数据大小.
         */
        virtual size_t read(void *pBuffer, size_t nSize) = 0;

        /**
         * @brief 写缓冲区数据到数据流中.
         * @param [in] pBuffer : 数据缓冲区
         * @param [in] nSize : 数据缓冲区大小
         * @return 返回写入的数据大小.
         */
        virtual size_t write(void *pBuffer, size_t nSize) = 0;

        /**
         * @brief 把数据流指针移动到指定位置.
         * @param [in] llPos : 指定偏移位置
         * @param [in] relative : 是否相对位置
         * @return 当调用成功时，返回true
         */
        virtual bool seek(long_t lPos, bool relative) = 0;

        /**
         * @brief 获取当前数据流读写位置.
         * @return 返回当前数据流读写位置.
         */
        virtual long_t tell() const = 0;

        /**
         * @brief 获取数据流的大小.
         * @return 返回当前数据流的大小
         */
        virtual long_t size() const = 0;

        /**
         * @brief 是否到数据流末尾.
         * @return 到末尾返回true，否则返回false.
         */
        virtual bool eof() const = 0;

        /**
         * @brief 一次把整个数据流读取完并返回这块buffer
         * @note 返回的pData内部管理，外部不用负责释放
         * @param [in][out] pData : 返回读取的数据首地址
         * @return 返回读取的长度
         */
        virtual size_t read(uint8_t *&pData) = 0;

        /**
         * @brief 读取一行文本
         * @param [in] trim : 是否裁剪掉前后的tab、空格等无效字符
         * @return 返回一行文本
         */
        String readLine(bool trim = true);

        /**
         * @brief 写一行文本
         * @param [in] strLine : 文本串
         * @return 返回写入文本长度
         */
        size_t writeLine(const String &strLine);

        /**
         * @brief 输出基本类型值到数据流
         */
        DataStream &operator<<(bool val);
        DataStream &operator<<(int8_t val);
        DataStream &operator<<(uint8_t val);
        DataStream &operator<<(int16_t val);
        DataStream &operator<<(uint16_t val);
        DataStream &operator<<(int32_t val);
        DataStream &operator<<(uint32_t val);
        DataStream &operator<<(int64_t val);
        DataStream &operator<<(uint64_t val);
        DataStream &operator<<(float val);
        DataStream &operator<<(double val);
        DataStream &operator<<(const char *s);
        DataStream &operator<<(const String &s);

        /**
         * @brief 输入数据流到基本类型值
         */
        DataStream &operator>>(bool &val);
        DataStream &operator>>(int8_t &val);
        DataStream &operator>>(uint8_t &val);
        DataStream &operator>>(int16_t &val);
        DataStream &operator>>(uint16_t &val);
        DataStream &operator>>(int32_t &val);
        DataStream &operator>>(uint32_t &val);
        DataStream &operator>>(int64_t &val);
        DataStream &operator>>(uint64_t &val);
        DataStream &operator>>(float &val);
        DataStream &operator>>(double &val);
        DataStream &operator>>(char *&s);
        DataStream &operator>>(String &s);
    };
}

#endif  /*__T3D_DATA_STREAM_H__*/
