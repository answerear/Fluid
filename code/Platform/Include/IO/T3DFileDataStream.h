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

#ifndef __T3D_FILE_DATA_STREAM_H__
#define __T3D_FILE_DATA_STREAM_H__



#include "IO/T3DDataStream.h"
#include <stdio.h>


namespace Tiny3D
{
    /**
     * @class T3DFileDataStream
     * @brief 文件流类.
     * @note 该类提供文件流读写操作.
     */
    class T3D_PLATFORM_API FileDataStream : public DataStream
    {
        T3D_DISABLE_COPY(FileDataStream);
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 文件流打开模式
         */
        enum EOpenMode
        {
            /// 文件没有打开
            E_MODE_NOT_OPEN = 0x00000000L,
            /// 只读方式打开
            E_MODE_READ_ONLY = 0x00000001L,
            /// 只写方式打开
            E_MODE_WRITE_ONLY = 0x00000002L,
            /// 读写方式打开
            E_MODE_READ_WRITE = E_MODE_READ_ONLY | E_MODE_WRITE_ONLY,
            /// 追加方式打开
            E_MODE_APPEND = 0x00000004L,
            /// 文件已经存在时清空原来内容打开
            E_MODE_TRUNCATE = 0x00000008L,
            /// 文本文件
            E_MODE_TEXT = 0x00000010L,
        };

        /**
         * @brief Constructor for T3DFileDataStream.
         */
        FileDataStream();

        /**
         * @brief Destructor for T3DFileDataStream.
         */
        virtual ~FileDataStream();

        /**
         * @brief 打开文件流.
         * @param [in] szFileName : 文件名
         * @param [in] eMode : 打开方式
         * @return 打开成功返回true，否则返回false.
         * @see enum EOpenMode
         */
        bool open(const char *szFileName, uint32_t unMode);

        /**
         * @brief 关闭文件流.
         * @return void
         */
        void close();

        /**
         * @brief 读取文件流.
         * @param [in] pBuffer : 数据缓冲区
         * @param [in] nSize : 数据缓冲区大小
         * @return 读取到的数据大小.
         */
        virtual size_t read(void *pBuffer, size_t nSize) override;

        /**
         * @brief 写入文件流.
         * @param [in] pBuffer : 待写入数据缓冲区
         * @param [in] nSize : 数据缓冲区大小
         * @return 写入的数据大小
         */
        virtual size_t write(void *pBuffer, size_t nSize) override;

        /**
         * @brief 把文件缓存在内存的内容全部强制写到文件中
         */
        void flush();

        /**
         * @brief 设置文件流读写偏移位置.
         * @param [in] llPos : 偏移位置
         * @return 当调用成功时，返回当前读写位置，若错误时，返回-1
         */
        virtual bool seek(long_t lPos, bool relative) override;

        /**
         * @brief 获取当前文件流当前读写位置.
         * @return 返回文件流当前读写位置
         */
        virtual long_t tell() const override;

        /**
         * @brief 获取文件大小.
         * @return 返回文件大小
         */
        virtual long_t size() const override;

        /**
         * @brief 获取是否到文件流末尾.
         * @return 已到文件流末尾
         */
        virtual bool eof() const override;

        /**
         * @brief 一次把整个数据流读取完并返回这块buffer
         * @note 返回的pData内部管理，外部不用负责释放
         * @param [in][out] pData : 返回读取的数据首地址
         * @return 返回读取的长度
         */
        virtual size_t read(uint8_t *&pData) override;

        bool isOpened() const   { return m_bIsOpened; }

    protected:
        FILE                *m_pFileHandle;     /**< 文件操作指针 */
        mutable long_t      m_lSize;            /**< 文件大小 */
        bool                m_bIsOpened;        /**< 文件是否打开 */
        uint8_t             *m_pData;           /**< 读取回来的数据 */
    };
}


#endif  /*__T3D_FILE_DATA_STREAM_H__*/
