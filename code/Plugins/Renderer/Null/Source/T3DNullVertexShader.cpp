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


#include "T3DD3D11VertexShader.h"
#include "T3DD3D11Renderer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11VertexShader, D3D11Shader);

    //--------------------------------------------------------------------------

    D3D11VertexShaderPtr D3D11VertexShader::create(const String &name, 
        const String &content)
    {
        D3D11VertexShaderPtr shader = new D3D11VertexShader(name, content);
        shader->release();
        return shader;
    }

    //--------------------------------------------------------------------------

    D3D11VertexShader::D3D11VertexShader(const String &name, 
        const String &content)
        : D3D11Shader(name, content)
        , mD3DVertexShader(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    D3D11VertexShader::~D3D11VertexShader()
    {
        D3D_SAFE_RELEASE(mD3DVertexShader);
    }

    //--------------------------------------------------------------------------

    Shader::ShaderType D3D11VertexShader::getShaderType() const
    {
        return ShaderType::VERTEX_SHADER;
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexShader::compile(bool force /* = false */)
    {
        TResult ret = T3D_OK;

        do 
        {
            D3D_FEATURE_LEVEL featureLevel = D3D11_RENDERER.getFeatureLevel();

            if (featureLevel >= D3D_FEATURE_LEVEL_11_0)
            {
                ret = D3D11Shader::compile("main", "vs_5_0");
            }
            else
            {
                ret = D3D11Shader::compile("main", "vs_4_0");
            }

            if (T3D_FAILED(ret))
            {
                break;
            }

            if (mD3DVertexShader == nullptr)
            {
                // 创建 ID3D11VertexShader 对象
                ID3D11Device *pD3DDevice = D3D11_RENDERER.getD3DDevice();

                HRESULT hr = S_OK;
                hr = pD3DDevice->CreateVertexShader(mContent, mContentLength,
                    nullptr, &mD3DVertexShader);
                if (FAILED(hr))
                {
                    ret = T3D_ERR_D3D11_CREATE_VERTEX_SHADER;
                    T3D_LOG_ERROR(
                        LOG_TAG_D3D11RENDERER,
                        "Create ID3D11VertexShader for shader file (%s) failed !"
                        "DX ERROR [%d]", getName().c_str(), hr);
                    break;
                }
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexShader::load()
    {
        TResult ret = T3D_OK;

        do 
        {
            // 读取文件内容
            ret = loadContent();
            if (T3D_FAILED(ret))
            {
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11VertexShader::unload()
    {
        TResult ret = T3D_OK;

        do 
        {
            D3D_SAFE_RELEASE(mD3DVertexShader);
            T3D_SAFE_DELETE_ARRAY(mContent);
            mContentLength = 0;
            mHasCompiled = false;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    ResourcePtr D3D11VertexShader::clone() const
    {
        D3D11VertexShaderPtr shader = new D3D11VertexShader(getName(), "");
        shader->release();

        TResult ret = T3D_OK;

        do 
        {
            ret = cloneProperties(shader);
            if (T3D_FAILED(ret))
            {
                shader = nullptr;
                break;
            }

            if (mD3DVertexShader != nullptr)
            {
                // 创建 ID3D11VertexShader 对象
                ID3D11Device *pD3DDevice = D3D11_RENDERER.getD3DDevice();

                HRESULT hr = S_OK;
                hr = pD3DDevice->CreateVertexShader(mContent, mContentLength, 
                    nullptr, &shader->mD3DVertexShader);
                if (FAILED(hr))
                {
                    T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, "Create \
                            ID3D11VertexShader for shader file (%s) failed ! \
                            Error : %d", getName().c_str(), hr);
                    shader = nullptr;
                    break;
                }
            }
        } while (0);

        return shader;
    }
}