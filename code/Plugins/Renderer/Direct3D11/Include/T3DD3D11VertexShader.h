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


#ifndef __T3D_D3D11_VERTEX_SHADER_H__
#define __T3D_D3D11_VERTEX_SHADER_H__


#include "T3DD3D11Shader.h"


namespace Tiny3D
{
    /**
     * @class   D3D11VertexShader
     * @brief   DirectX 11 顶点着色器
     */
    class D3D11VertexShader : public D3D11Shader
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static D3D11VertexShaderPtr D3D11VertexShader::create( 
         *      const String &name, const String &content);
         * @brief   创建 D3D11VertexShader 对象
         * @param [in]  name    : Shader 名称.
         * @param [in]  content : 着色器内容，可以为空.
         * @return  返回一个新建的D3D11着色器对象.
         */
        static D3D11VertexShaderPtr create(
            const String &name, const String &content);

        /**
         * @fn  virtual D3D11VertexShader::~D3D11VertexShader();
         * @brief   析构函数
         */
        virtual ~D3D11VertexShader();

        /**
         * @fn  virtual ShaderType 
         *      D3D11VertexShader::getShaderType() const override;
         * @brief   重写 Shader::getShaderType() 接口
         * @return  The shader type.
         */
        virtual ShaderType getShaderType() const override;

        /**
         * @fn  virtual TResult D3D11VertexShader::compile(
         *      bool force = false) override;
         * @brief   重写 Shader::compile() 接口
         * @param   force   (Optional) True to force.
         * @return  A TResult.
         */
        virtual TResult compile(bool force = false) override;

        /**
         * @fn  ID3D11VertexShader D3D11VertexShader::*getD3DShader() const
         * @brief   Gets d 3D shader
         * @return  Null if it fails, else the d 3D shader.
         */
        ID3D11VertexShader *getD3DShader() const { return mD3DVertexShader; }

    protected:
        /**
         * @fn  D3D11VertexShader::D3D11VertexShader(const String &name, 
         *      const String &content);
         * @brief   构造函数
         * @param   name    The name.
         * @param   content The content.
         */
        D3D11VertexShader(const String &name, const String &content);

        /**
         * @fn  virtual TResult D3D11VertexShader::load() override;
         * @brief   重写 Resource::load() 接口
         * @return  A TResult.
         */
        virtual TResult load() override;

        /**
         * @fn  virtual TResult D3D11VertexShader::unload() override;
         * @brief   重写 Resource::unload() 接口
         * @return  A TResult.
         */
        virtual TResult unload() override;

        /**
         * @fn  virtual ResourcePtr D3D11VertexShader::clone() const override;
         * @brief   重写 Resource::clone() 接口
         * @return  A copy of this object.
         */
        virtual ResourcePtr clone() const override;

    protected:
        ID3D11VertexShader  *mD3DVertexShader;  /**< D3D11 顶点着色器对象 */
    };
}


#endif  /*__T3D_D3D11_VERTEX_SHADER_H__*/