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


#ifndef __T3D_HARDWARE_INDEX_BUFFER_H__
#define __T3D_HARDWARE_INDEX_BUFFER_H__


#include "Render/T3DHardwareBuffer.h"


namespace Tiny3D
{
    /**
     * @class   HardwareIndexBuffer
     * @brief   索引缓冲区
     * @sa  class HardwareBuffer
     */
    class T3D_ENGINE_API HardwareIndexBuffer : public HardwareBuffer
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @enum    Type
         * @brief   索引大小类型
         */
        enum class Type : uint32_t
        {
            E_IT_16BITS = 0,    /**< 16位索引 */
            E_IT_32BITS,        /**< 32位索引 */
        };

        /**
         * @fn  virtual HardwareIndexBuffer::~HardwareIndexBuffer();
         * @brief   析构函数
         */
        virtual ~HardwareIndexBuffer();

        /**
         * @fn  Type HardwareIndexBuffer::getIndexType() const
         * @brief   获取索引类型
         * @returns 返回索引类型.
         */
        Type getIndexType() const { return mType; }

        /**
         * @fn  size_t HardwareIndexBuffer::getIndexSize() const
         * @brief   获取索引大小
         * @returns 返回索引大小.
         */
        size_t getIndexSize() const { return mIndexSize; }

        /**
         * @fn  size_t HardwareIndexBuffer::getIndexCount() const
         * @brief   获取索引数量
         * @returns 返回索引数量.
         */
        size_t getIndexCount() const { return mIndexCount; }

    protected:
        /**
         * @fn  HardwareIndexBuffer::HardwareIndexBuffer(Type indexType, 
         *      size_t indexCount, HardwareBuffer::Usage usage, uint32_t mode);
         * @brief   构造函数
         * @param [in]  indexType   索引类型.
         * @param [in]  indexCount  索引数量.
         * @param [in]  usage       缓冲区使用方式.
         * @param [in]  mode        缓冲区访问方式.
         */
        HardwareIndexBuffer(Type indexType, size_t indexCount, Usage usage, 
            uint32_t mode);

    protected:
        Type    mType;          /**< 索引类型，是16位还是32位 */
        size_t  mIndexSize;     /**< 索引大小 */
        size_t  mIndexCount;    /**< 索引数量 */
    };
}


#endif  /*__T3D_HARDWARE_INDEX_BUFFER_H__*/
