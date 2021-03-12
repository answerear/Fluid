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

#include "Kernel/T3DPass.h"
#include "Kernel/T3DTextureUnit.h"
#include "T3DConfig.h"
#include "T3DErrorDef.h"
#include "Resource/T3DGPUProgramManager.h"
#include "Resource/T3DGPUConstBufferManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Pass, Object);

    //--------------------------------------------------------------------------

    PassPtr Pass::create(const String &name, Technique *tech)
    {
        PassPtr pass = new Pass(name, tech);
        pass->release();
        return pass;
    }

    //--------------------------------------------------------------------------

    Pass::Pass(const String &name, Technique *tech)
        : mGPUProgram(nullptr)
        , mParent(tech)
        , mName(name)
        , mAmbient(ColorRGBA::WHITE)
        , mDiffuse(ColorRGBA::WHITE)
        , mSpecular(ColorRGBA::BLACK)
        , mShininess(0.0f)
        , mEmissive(ColorRGBA::BLACK)
        , mTracking(TrackVertexColor::NONE)
        , mDepthCheck(true)
        , mDepthWrite(true)
        , mDepthFunc(CompareFunction::LESS_EQUAL)
        , mDepthBiasConstant(0.0f)
        , mDepthBiasSlopeScale(0.0f)
        , mDepthBiasPerIteration(0.0f)
        , mAlphaRejectFunc(CompareFunction::ALWAYS_PASS)
        , mAlphaRejectVal(0)
        , mAlpha2CoverageEnabled(false)
        , mLightScissoring(false)
        , mLightClipPlanes(false)
        , mLightingEnabled(true)
        , mNormalizeNormals(false)
        , mTransparentSorting(true)
        , mTransparentSortingForced(false)
        , mPolygonModeOverrideable(true)
        , mCullMode(CullingMode::CLOCKWISE)
        , mManualCullMode(ManualCullingMode::BACK)
        , mIlluminationStage(IlluminationStage::UNKNOWN)
        , mShadingMode(ShadingMode::GOURAUD)
        , mPolygonMode(PolygonMode::SOLID)
        , mFogOverride(false)
        , mFogMode(FogMode::NONE)
        , mFogColor(ColorRGBA::WHITE)
        , mFogStart(0.0f)
        , mFogEnd(1.0f)
        , mFogDensity(0.01f)
        , mStartLight(0)
        , mMaxLights(T3D_MAX_SIMULTANEOUS_LIGHTS)
        , mPassIterationCount(1)
        , mLightsPerIteration(1)
        , mOnlyLightType(LightType::POINT)
        , mIteratePerLight(false)
        , mRunOnlyForOneLightType(false)
        , mPointSpritesEnabled(false)
        , mPointSize(1.0f)
        , mPointAttenuationEnabled(false)
        , mPointAttenuationCoeffs(1.0f, 0.0f, 0.0f)
        , mPointMinSize(0.0f)
        , mPointMaxSize(0.0f)
    {

    }

    //--------------------------------------------------------------------------

    Pass::~Pass()
    {

    }

    //--------------------------------------------------------------------------

    TResult Pass::setGPUProgram(GPUProgramRefPtr program)
    {
        TResult ret = T3D_OK;

        do 
        {
            mGPUProgram 
                = T3D_GPU_PROGRAM_MGR.loadGPUProgram(program->getName());
            if (mGPUProgram == nullptr)
            {
                ret = T3D_ERR_RES_LOAD_FAILED;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Load GPU Program [%s] failed !",
                    program->getName().c_str());
                break;
            }

            auto list = program->getBufferRefList();
            mConstBuffers.resize(list.size());

            auto itr = list.begin();

            while (itr != list.end())
            {
                GPUConstBufferRefPtr bufferRef = *itr;
                GPUConstBufferPtr buffer 
                    = T3D_GPU_CONST_BUFFER_MGR.loadBuffer(bufferRef->getName(), 0);
                if (buffer == nullptr)
                {
                    ret = T3D_ERR_RES_LOAD_FAILED;
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                        "Load GPU constant buffer [%s] failed !",
                        bufferRef->getName());
                    break;
                }

                if (bufferRef->getSlot() >= mConstBuffers.size())
                {
                    ret = T3D_ERR_OUT_OF_BOUND;
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                        "Constant buffer reference is out of bound !");
                    break;
                }
                mConstBuffers[bufferRef->getSlot()] = buffer;
                ++itr;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Pass::addTextureUnit(const String &name, TextureUnitPtr &unit)
    {
        TResult ret = T3D_OK;

        do
        {
            unit = TextureUnit::create(name, this);
            if (unit == nullptr)
            {
                ret = T3D_ERR_RES_CREATE_TEX_UNIT;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Create texture unit [%s] object failed !", name.c_str());
                break;
            }

            mTextureUnits.push_back(unit);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Pass::removeTextureUnit(const String &name)
    {
        TResult ret = T3D_ERR_NOT_FOUND;

        auto itr = mTextureUnits.begin();
        while (itr != mTextureUnits.end())
        {
            TextureUnitPtr unit = *itr;
            if (name == unit->getName())
            {
                mTextureUnits.erase(itr);
                ret = T3D_OK;
                break;
            }

            ++itr;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TextureUnitPtr Pass::getTextureUnit(const String &name) const
    {
        TextureUnitPtr texUnit;

        auto itr = mTextureUnits.begin();
        while (itr != mTextureUnits.end())
        {
            const TextureUnitPtr &unit = *itr;
            if (name == unit->getName())
            {
                texUnit = unit;
                break;
            }

            ++itr;
        }

        return texUnit;
    }

    //--------------------------------------------------------------------------

    void Pass::getBlendFlags(BlendType type, BlendFactor &source, BlendFactor &dest)
    {
        switch (type)
        {
        case BlendType::TRANSPARENT_ALPHA:
            source = BlendFactor::SOURCE_ALPHA;
            dest = BlendFactor::ONE_MINUS_SOURCE_ALPHA;
            return;
        case BlendType::TRANSPARENT_COLOR:
            source = BlendFactor::SOURCE_COLOR;
            dest = BlendFactor::ONE_MINUS_SOURCE_COLOR;
            return;
        case BlendType::MODULATE:
            source = BlendFactor::DEST_COLOR;
            dest = BlendFactor::ZERO;
            return;
        case BlendType::ADD:
            source = BlendFactor::ONE;
            dest = BlendFactor::ONE;
            return;
        case BlendType::REPLACE:
            source = BlendFactor::ONE;
            dest = BlendFactor::ZERO;
            return;
        }

        source = BlendFactor::ONE;
        dest = BlendFactor::ZERO;
    }
}
