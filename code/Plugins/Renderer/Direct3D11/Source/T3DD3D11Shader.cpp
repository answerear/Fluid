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


#include "T3DD3D11Shader.h"
#include "T3DD3D11Context.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11Shader, Shader);

    //--------------------------------------------------------------------------

    D3D11Shader::D3D11Shader(const String &name,
        const String &content)
        : Shader(name)
        , mContent(nullptr)
        , mContentLength(0)
        , mHasCompiled(false)
    {
        if (!content.empty())
        {
            mContentLength = content.length();
            mContent = new char[mContentLength];
            memcpy(mContent, content.c_str(), mContentLength);
        }
    }

    //--------------------------------------------------------------------------

    D3D11Shader::~D3D11Shader()
    {
        T3D_SAFE_DELETE_ARRAY(mContent);
    }

    //--------------------------------------------------------------------------

    TResult D3D11Shader::compile(const String &entry, const String &model)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mHasCompiled)
            {
                // 已经编译过了
                break;
            }

            // 编译
            HRESULT hr = S_OK;
            char szMsg[256] = { 0 };

            UINT unShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef T3D_DEBUG
            unShaderFlags |= (D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION);
#endif

            ID3DBlob *pCode = nullptr;
            ID3DBlob *pError = nullptr;

            hr = D3DCompile(mContent, mContentLength, szMsg, nullptr, 
                nullptr, entry.c_str(), model.c_str(), 
                unShaderFlags, 0, &pCode, &pError);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_SHADER_COMPILED;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, 
                    "Compile shader [%s] failed ! - %s", mName.c_str(), 
                    (const char *)pError->GetBufferPointer());

                D3D_SAFE_RELEASE(pCode);
                D3D_SAFE_RELEASE(pError);
                break;
            }

            // 保存编译后的字节码
            mContentLength = pCode->GetBufferSize();
            T3D_SAFE_DELETE_ARRAY(mContent);
            mContent = new char[mContentLength];
            memcpy(mContent, pCode->GetBufferPointer(), mContentLength);

            mHasCompiled = true;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool D3D11Shader::hasCompiled() const
    {
        return mHasCompiled;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Shader::cloneProperties(D3D11ShaderPtr shader) const
    {
        do 
        {
            if (mContentLength > 0 && mContent != nullptr)
            {
                shader->mContentLength = mContentLength;
                shader->mContent = new char[mContentLength];
                memcpy(shader->mContent, mContent, mContentLength);
            }

            shader->mHasCompiled = mHasCompiled;

        } while (0);

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Shader::loadContent()
    {
        TResult ret = T3D_OK;

        do 
        {
            // 读取文件内容
            const String &name = getName();
            ArchivePtr archive = T3D_AGENT.getAssetsArchive(name);
            if (archive == nullptr)
            {
                ret = T3D_ERR_FILE_NOT_EXIST;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, "Could not find the "
                    "archive for shader file %s !", name.c_str());
                break;
            }

            String path = T3D_AGENT.getMainAssetsPath(name);
            MemoryDataStream stream;
            ret = archive->read(path, stream);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, "Could not read the \
                    shader file %s !", name.c_str());
                break;
            }

            uint8_t *buffer = nullptr;
            size_t bufSize = 0;
            stream.getBuffer(buffer, bufSize);

            mContentLength = bufSize;
            T3D_SAFE_DELETE_ARRAY(mContent);
            mContent = new char[bufSize+1];
            memcpy(mContent, buffer, bufSize);
            mContent[bufSize] = 0;

            ret = T3D_OK;
        } while (0);

        return ret;
    }
}