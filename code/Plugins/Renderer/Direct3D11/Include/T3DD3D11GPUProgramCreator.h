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


#ifndef __T3D_D3D11_GPU_PROGRAM_CREATOR_H__
#define __T3D_D3D11_GPU_PROGRAM_CREATOR_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    /**
     * @class   D3D11ShaderCreator
     * @brief   DirectX 11 着色器生成器
     */
    class D3D11ShaderCreator : public ShaderCreator
    {
        T3D_DECLARE_CLASS();

    public:
        static const char * const SHADER_TYPE;  /**< Type of the shader */

        /**
         * @fn  virtual String D3D11ShaderCreator::getType() const override;
         * @brief   重写ShaderCreator::getType() 接口
         * @return  The type.
         */
        virtual String getType() const override;

        /**
         * @fn  virtual ShaderPtr D3D11ShaderCreator::createObject(
         *      int32_t argc, ...) const override;
         * @brief   重写ShaderCreator::createObject() 接口
         * @param   argc    The argc.
         * @param   ...     Variable arguments providing additional information.
         * @return  The new object.
         */
        virtual ShaderPtr createObject(int32_t argc, ...) const override;
    };

    /**
     * @class   D3D11GPUProgramCreator
     * @brief   DirectX 11 GPU程序生成器
     */
    class D3D11GPUProgramCreator : public GPUProgramCreator
    {
    public:
        static const char * const GPUPROGRAM_TYPE;  /**< Type of the gpuprogram */

        /**
         * @fn  virtual String D3D11GPUProgramCreator::getType() const override;
         * @brief   重写ShaderCreator::getType() 接口
         * @return  The type.
         */
        virtual String getType() const override;

        /**
         * @fn  virtual GPUProgramPtr D3D11GPUProgramCreator::createObject(
         *      int32_t argc, ...) const override;
         * @brief   重写ShaderCreator::createObject() 接口
         * @param   argc    The argc.
         * @param   ...     Variable arguments providing additional information.
         * @return  The new object.
         */
        virtual GPUProgramPtr createObject(int32_t argc, ...) const override;
    };
}


#endif  /*__T3D_D3D11_GPU_PROGRAM_CREATOR_H__*/