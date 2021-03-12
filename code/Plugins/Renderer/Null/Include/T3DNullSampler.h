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


#ifndef __T3D_D3D11_SAMPLER_STATE_H__
#define __T3D_D3D11_SAMPLER_STATE_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    /**
     * @class   D3D11SamplerCreator
     * @brief   DirectX 11 采样器创建器.
     */
    class D3D11SamplerCreator : public SamplerCreator
    {
        T3D_DECLARE_CLASS();

    public:
        static const char * const SAMPLER_TYPE; /**< Sampler 创建器类型 */

        /**
         * @fn  virtual String D3D11SamplerCreator::getType() const override;
         * @brief   重写ShaderCreator::getType() 接口
         * @return  返回创建器类型.
         * @sa  String SamplerCreator::getType() const;
         * @sa  const char * const SAMPLER_TYPE;
         */
        virtual String getType() const override;

        /**
         * @fn  virtual SamplerPtr D3D11SamplerCreator::createObject(
         *      int32_t argc, ...) const override;
         * @brief   重写 SamplerCreator::createObject() 接口
         * @param [in]  argc    创建对象带的参数个数.
         * @param [in]  ...     创建对象带的参数列表.
         * @returns 调用成功返回一个新建的采样器对象.
         * @sa  SamplerPtr SamplerCreator::createObject(int32_t argc, ...) const;
         */
        virtual SamplerPtr createObject(int32_t argc, ...) const override;
    };


    /**
     * @class   D3D11Sampler
     * @brief   DirectX 11 采样器.
     */
    class D3D11Sampler : public Sampler
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static D3D11SamplerPtr D3D11Sampler::create(const String &name);
         * @brief   创建 D3D11 采样器对象
         * @param [in]  name    采样器名称.
         * @returns 调用成功返回一个 D3D11 采样器对象.
         */
        static D3D11SamplerPtr create(const String &name);

        /**
         * @fn  virtual D3D11Sampler::~D3D11Sampler();
         * @brief   析构函数
         */
        virtual ~D3D11Sampler();

        /**
         * @fn  ID3D11SamplerState D3D11Sampler::*getD3DSamplerState()
         * @brief   获取 ID3D11SamplerState 对象
         * @returns 返回 ID3D11SamplerState 对象.
         */
        ID3D11SamplerState *getD3DSamplerState();

    protected:
        /**
         * @fn  D3D11Sampler::D3D11Sampler(const String &name);
         * @brief   构造函数
         * @param [in]  name    采样器名称.
         */
        D3D11Sampler(const String &name);

        /**
         * @fn  virtual TResult Sampler::load() override;
         * @brief   重寫 Resource::load()
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult load() override;

        /**
         * @fn  virtual TResult Sampler::unload() override;
         * @brief   重寫 Resource::unlaod()
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult unload() override;

        /**
         * @fn  virtual ResourcePtr Sampler::clone() const override;
         * @brief   重寫 Resource::clone()
         * @returns 调用成功返回一个新的材质对象.
         */
        virtual ResourcePtr clone() const override;

    protected:
        ID3D11SamplerState  *mD3DSampler;   /**< ID3D11SamplerState 对象 */
    };
}


#endif  /*__T3D_D3D11_SAMPLER_STATE_H__*/
