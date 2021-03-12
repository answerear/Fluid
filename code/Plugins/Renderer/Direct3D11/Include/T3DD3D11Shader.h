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


#ifndef __T3D_D3D11_SHADER_H__
#define __T3D_D3D11_SHADER_H__


#include "T3DD3D11Prerequisites.h"
#include "T3DD3D11Error.h"


namespace Tiny3D
{
    /**
     * @class   D3D11Shader
     * @brief   DirectX 11 着色器
     */
    class D3D11Shader : public Shader
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  virtual D3D11Shader::~D3D11Shader();
         * @brief   析构函数
         */
        virtual ~D3D11Shader();

        /**
         * @fn  virtual bool D3D11Shader::hasCompiled() const override;
         * @brief   重写 Shader::hasCompiled() 接口
         * @return  True if compiled, false if not.
         */
        virtual bool hasCompiled() const override;

        /**
         * @fn  TResult D3D11Shader::getBytecode(const char *&bytecode, 
         *      size_t &bytecodeLength)
         * @brief   获取编译后的字节码
         * @param [in]  bytecode        bytecode : 字节码二进制数据.
         * @param [in]  bytecodeLength  bytecodeLength : 字节码长度.
         * @return  调用成功返回T3D_OK.
         */
        TResult getBytecode(const char *&bytecode, size_t &bytecodeLength)
        {
            if (!mHasCompiled)
                return T3D_ERR_D3D11_SHADER_NOT_COMPILED;
            bytecode = mContent;
            bytecodeLength = mContentLength;
            return T3D_OK;
        }

    protected:
        /**
         * @fn  D3D11Shader::D3D11Shader(const String &name, 
         *      const String &content);
         * @brief   构造函数
         * @param   name    The name.
         * @param   content The content.
         */
        D3D11Shader(const String &name, const String &content);

        /**
         * @fn  virtual TResult D3D11Shader::cloneProperties(
         *      D3D11ShaderPtr shader) const;
         * @brief   克隆属性
         * @param   shader  The shader.
         * @return  A TResult.
         */
        virtual TResult cloneProperties(D3D11ShaderPtr shader) const;

        /**
         * @fn  TResult D3D11Shader::compile(const String &entry, 
         *      const String &model);
         * @brief   编译着色器
         * @param [in]  entry   : 入口函数名称.
         * @param [in]  model   : 着色器版本.
         * @return  调用成功返回 T3D_OK.
         */
        TResult compile(const String &entry, const String &model);

        /**
         * @fn  TResult D3D11Shader::loadContent();
         * @brief   加载 shader 源码内容
         * @return  调用成功返回 T3D_OK.
         */
        TResult loadContent();

    protected:
        char    *mContent;          /**< 编译前存放源码，编译后存放字节码 */
        size_t  mContentLength;     /**< 编译前是源码长度，编译后是字节码长度 */
        bool    mHasCompiled;       /**< 是否编译 */
    };
}


#endif  /*__T3D_D3D11_SHADER_H__*/