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


#include "Kernel/T3DTechnique.h"
#include "Kernel/T3DAgent.h"
#include "Kernel/T3DPass.h"
#include "T3DErrorDef.h"
#include "Render/T3DRenderContext.h"
#include "Render/T3DRenderCapabilities.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Technique, Object);

    //--------------------------------------------------------------------------

    TechniquePtr Technique::create(const String &name, Material *material)
    {
        TechniquePtr tech = new Technique(name, material);
        tech->release();
        return tech;
    }

    //--------------------------------------------------------------------------

    Technique::Technique(const String &name, Material *material)
        : mParent(material)
        , mName(name)
        , mLodIndex(0)
        , mSchemeIndex(0)
        , mRenderQueue(0)
        , mIsSupported(false)
    {

    }

    //--------------------------------------------------------------------------

    Technique::~Technique()
    {

    }

    //--------------------------------------------------------------------------

    TResult Technique::compile()
    {
        TResult ret = T3D_OK;

        do 
        {
            RenderContextPtr renderer = T3D_AGENT.getActiveRenderer();
            RenderCapabilitiesPtr caps = renderer->getRendererCapabilities();
            size_t numTexUnits = caps->getNumTextureUnits();

            for (auto i = mPasses.begin(); i != mPasses.end(); ++i)
            {
                PassPtr pass = *i;

                // 检测纹理单元是否超过硬件限制
                size_t numTexUnitsRequested = pass->getTextureUnitsCount();
                if (!pass->hasPixelShader())
                {
                    if (numTexUnitsRequested > numTexUnits)
                    {
                        ret = T3D_ERR_RES_COMPILED;
                        T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Pass %s : "
                            "Too many texture units for current hardware !",
                            pass->getName().c_str());
                        break;
                    }
                }

                // 编译 Pass 的 GPU 程序
                GPUProgramPtr program = pass->getGPUProgram();
                ret = program->compile();
                if (T3D_FAILED(ret))
                    break;

                // 链接 Pass 的 GPU 程序
                ret = program->link();
                if (T3D_FAILED(ret))
                    break;

                mIsSupported = true;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Technique::addPass(const String &name, PassPtr &pass)
    {
        TResult ret = T3D_OK;

        do 
        {
            pass = Pass::create(name, this);
            if (pass == nullptr)
            {
                ret = T3D_ERR_RES_CREATE_PASS;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Create pass [%s] object failed !", name.c_str());
                break;
            }

            mPasses.push_back(pass);
        } while (0);
        
        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Technique::removePass(const String &name)
    {
        TResult ret = T3D_ERR_NOT_FOUND;

        auto itr = mPasses.begin();
        while (itr != mPasses.end())
        {
            PassPtr pass = *itr;
            if (name == pass->getName())
            {
                mPasses.erase(itr);
                ret = T3D_OK;
                break;
            }

            ++itr;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Technique::removePass(size_t index)
    {
        TResult ret = T3D_ERR_NOT_FOUND;

        if (index >= mPasses.size())
            return ret;

        mPasses.erase(mPasses.begin() + index);

//         size_t i = 0;
//         auto itr = mPasses.begin();
// 
//         while (itr != mPasses.end())
//         {
//             if (i == index)
//             {
//                 mPasses.erase(itr);
//                 ret = T3D_OK;
//                 break;
//             }
// 
//             ++i;
//             ++itr;
//         }

        return ret;
    }

    //--------------------------------------------------------------------------

    PassPtr Technique::getPass(const String &name) const
    {
        PassPtr pass;

        auto itr = mPasses.begin();
        while (itr != mPasses.end())
        {
            const PassPtr &p = *itr;
            if (name == pass->getName())
            {
                pass = p;
                break;
            }

            ++itr;
        }

        return pass;
    }
}
