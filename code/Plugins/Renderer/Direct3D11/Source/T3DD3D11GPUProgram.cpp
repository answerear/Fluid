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


#include "T3DD3D11GPUProgram.h"
#include "T3DD3D11Context.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(D3D11GPUProgram, GPUProgram);

    //--------------------------------------------------------------------------

    D3D11GPUProgramPtr D3D11GPUProgram::create(const String &name)
    {
        D3D11GPUProgramPtr program = new D3D11GPUProgram(name);
        program->release();
        return program;
    }

    //--------------------------------------------------------------------------

    D3D11GPUProgram::D3D11GPUProgram(const String &name)
        : GPUProgram(name)
        , mHasLinked(false)
    {

    }

    //--------------------------------------------------------------------------

    D3D11GPUProgram::~D3D11GPUProgram()
    {

    }

    //--------------------------------------------------------------------------

    TResult D3D11GPUProgram::link(bool force /* = false */)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mHasLinked)
                break;

            for (auto i = mShaders.begin(); i != mShaders.end(); ++i)
            {
                ShaderPtr shader = *i;
                if (shader == nullptr)
                    continue;

                if (!shader->hasCompiled())
                {
                    T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, 
                        "Shader has not compiled !");
                    ret = T3D_ERR_D3D11_SHADER_NOT_COMPILED;
                    break;
                }
            }

            if (T3D_FAILED(ret))
            {
                break;
            }

            mHasLinked = true;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool D3D11GPUProgram::hasLinked() const
    {
        return mHasLinked;
    }

    //--------------------------------------------------------------------------

    TResult D3D11GPUProgram::load()
    {
        TResult ret = T3D_OK;

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11GPUProgram::unload()
    {
        TResult ret = T3D_OK;

        return ret;
    }

    //--------------------------------------------------------------------------

    ResourcePtr D3D11GPUProgram::clone() const
    {
        D3D11GPUProgramPtr program = create(getName());

        TResult ret = cloneProperties(program);
        if (T3D_FAILED(ret))
        {
            program = nullptr;
        }

        return program;
    }

    //--------------------------------------------------------------------------

    TResult D3D11GPUProgram::cloneProperties(GPUProgramPtr newObj) const
    {
        TResult ret = T3D_OK;

        do 
        {
            ret = GPUProgram::cloneProperties(newObj);
            if (T3D_FAILED(ret))
            {
                ret = T3D_ERR_RES_CLONE;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Clone GPU program proterties failed !");
                break;
            }

            D3D11GPUProgramPtr program 
                = smart_pointer_cast<D3D11GPUProgram>(newObj);
            program->mHasLinked = mHasLinked;
        } while (0);

        return ret;
    }
}