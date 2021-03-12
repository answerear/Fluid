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


#ifndef __T3D_D3D11_GPU_PROGRAM_H__
#define __T3D_D3D11_GPU_PROGRAM_H__


#include "T3DD3D11Prerequisites.h"
#include "T3DD3D11Error.h"
#include "T3DD3D11VertexShader.h"
#include "T3DD3D11PixelShader.h"


namespace Tiny3D
{
    /**
     * @brief DirectX 11 GPU程序
     */
    class D3D11GPUProgram : public GPUProgram
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 创建 D3D11GPUProgram 对象
         */
        static D3D11GPUProgramPtr create(const String &name);

        /**
         * @brief 析构函数
         */
        virtual ~D3D11GPUProgram();

        /**
         * @brief 重写 GPUProgram::link() 接口
         */
        virtual TResult link(bool force = false) override;

        /**
         * @brief 重写 GPUProgram::hasLinked() 接口
         */
        virtual bool hasLinked() const override;

    protected:
        /**
         * @brief 构造函数
         */
        D3D11GPUProgram(const String &name);

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
         * @brief 重寫 GPUProgram::cloneProperties() 接口
         */
        virtual TResult cloneProperties(GPUProgramPtr newObj) const override;

    protected:
        bool                    mHasLinked;     /**< 是否链接标记 */
    };
}


#endif  /*__T3D_D3D11_GPU_PROGRAM_H__*/