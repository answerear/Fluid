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


#ifndef __T3D_HARDWARE_CONSTANT_BUFFER_H__
#define __T3D_HARDWARE_CONSTANT_BUFFER_H__


#include "Render/T3DHardwareBuffer.h"


namespace Tiny3D
{
    /**
     * @brief 常量缓冲区
     */
    class T3D_ENGINE_API HardwareConstantBuffer : public HardwareBuffer
    {
        T3D_DECLARE_CLASS();

    protected:
        /**
         * @fn  HardwareConstantBuffer::HardwareConstantBuffer(size_t bufSize, 
         *      Usage usage, uint32_t mode);
         * @brief   构造函数
         * @param [in]  bufSize 缓冲区大小.
         * @param [in]  usage   缓冲区使用方式.
         * @param [in]  mode    缓冲区访问方式.
         */
        HardwareConstantBuffer(size_t bufSize, Usage usage, uint32_t mode);
    };
}


#endif  /*__T3D_HARDWARE_CONSTANT_BUFFER_H__*/
