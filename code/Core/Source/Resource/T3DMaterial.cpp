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


#include "Resource/T3DMaterial.h"
#include "Resource/T3DArchive.h"
#include "Resource/T3DArchiveManager.h"
#include "Resource/T3DGPUProgram.h"
#include "Resource/T3DGPUProgramManager.h"
#include "Resource/T3DGPUConstBuffer.h"
#include "REsource/T3DGPUConstBufferManager.h"
#include "Kernel/T3DAgent.h"
#include "Kernel/T3DTechnique.h"
#include "T3DErrorDef.h"
#include "Serializer/T3DSerializerManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Material, Resource);

    //--------------------------------------------------------------------------

    MaterialPtr Material::create(const String &name, MaterialType type)
    {
        MaterialPtr material = new Material(name, type);
        material->release();
        return material;
    }

    //--------------------------------------------------------------------------

    Material::Material(const String &name, MaterialType type)
        : Resource(name)
        , mMaterialType(type)
        , mHasCompiled(false)
    {

    }

    //--------------------------------------------------------------------------

    Material::~Material()
    {

    }

    //--------------------------------------------------------------------------

    Resource::Type Material::getType() const
    {
        return Type::E_RT_MATERIAL;
    }

    //--------------------------------------------------------------------------

    TResult Material::load()
    {
        TResult ret = T3D_OK;

        do
        {
            if (E_MT_DEFAULT == mMaterialType)
            {
                // 默認類型，從文件加載

                // 加載材質文件
                ArchivePtr archive = T3D_AGENT.getAssetsArchive(mName);
                if (archive == nullptr)
                {
                    ret = T3D_ERR_IMG_NOT_FOUND;
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                        "Could not find the archive for file %s !",
                        mName.c_str());
                    break;
                }

                String path = T3D_AGENT.getMainAssetsPath(mName);
                MemoryDataStream stream;
                ret = archive->read(path, stream);
                if (T3D_FAILED(ret))
                {
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                        "Read material content failed from file %s ! ",
                        mName.c_str());
                    break;
                }

                // 交給腳本解析器解析
//                 ret = T3D_SCRIPT_PARSER.parse(stream, this);
                ret = T3D_SERIALIZER_MGR.parseMaterial(stream, this);
                if (T3D_FAILED(ret))
                {
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                        "Could not parse material file %s !", mName.c_str());
                    break;
                }

                if (!mHasCompiled)
                {
                    // 脚本没编译，编译
                    ret = compile();
                    if (T3D_FAILED(ret))
                    {
                        T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                            "Compile material %s failed !", mName.c_str());
                        break;
                    }
                }
            }
            else if (E_MT_MANUAL == mMaterialType)
            {
                // 手動創建，不從文件加載
            }
            else
            {
                ret = T3D_ERR_RES_INVALID_TYPE;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Invalid material type !");
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Material::unload()
    {
        mTechniques.clear();

        // 卸載所有 GPUProgram 對象
        auto itr = mGPUPrograms.begin();

        while (itr != mGPUPrograms.end())
        {
            auto program = itr->second;
            T3D_GPU_PROGRAM_MGR.unloadGPUProgram(program);
            ++itr;
        }

        mGPUPrograms.clear();

        return Resource::unload();
    }

    //--------------------------------------------------------------------------

    ResourcePtr Material::clone() const
    {
        MaterialPtr material = Material::create(mName, mMaterialType);

        material->mTechniques = mTechniques;

        return material;
    }

    //--------------------------------------------------------------------------

    TResult Material::addTechnique(const String &name, TechniquePtr &tech)
    {
        TResult ret = T3D_OK;

        do 
        {
            tech = Technique::create(name, this);
            if (tech == nullptr)
            {
                ret = T3D_ERR_RES_CREATE_TECHNIQUE;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Create technique [%s] object failed !", name.c_str());
                break;
            }

            mTechniques.push_back(tech);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Material::removeTechnique(const String &name)
    {
        TResult ret = T3D_ERR_NOT_FOUND;

        auto itr = mTechniques.begin();

        while (itr != mTechniques.end())
        {
            TechniquePtr &tech = *itr;
            if (name == tech->getName())
            {
                mTechniques.erase(itr);
                ret = T3D_OK;
                break;
            }

            ++itr;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Material::removeTechnique(size_t index)
    {
        TResult ret = T3D_ERR_NOT_FOUND;

        size_t i = 0;
        auto itr = mTechniques.begin();

        while (itr != mTechniques.end())
        {
            if (i == index)
            {
                mTechniques.erase(itr);
                ret = T3D_OK;
                break;
            }

            ++i;
            ++itr;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TechniquePtr Material::getTechnique(const String &name) const
    {
        TechniquePtr tech;
        auto itr = mTechniques.begin();

        while (itr != mTechniques.end())
        {
            const TechniquePtr &t = *itr;
            if (name == tech->getName())
            {
                tech = t;
                break;
            }

            ++itr;
        }

        return tech;
    }

    //--------------------------------------------------------------------------

    TechniquePtr Material::getTechnique(size_t index) const
    {
        TechniquePtr tech;

//         size_t i = 0;
//         auto itr = mTechniques.begin();
// 
//         while (itr != mTechniques.end())
//         {
//             if (i == index)
//             {
//                 tech = *itr;
//                 break;
//             }
// 
//             ++i;
//             ++itr;
//         }

        if (index < mTechniques.size())
        {
            tech = mTechniques[index];
        }

        return tech;
    }

    //--------------------------------------------------------------------------

    TResult Material::addGPUProgram(const String &name, GPUProgramPtr &program)
    {
        TResult ret = T3D_OK;

        do 
        {
            program = T3D_GPU_PROGRAM_MGR.loadGPUProgram(name);
            if (program == nullptr)
            {
                ret = T3D_ERR_RES_CREATE_GPUPROGRAM;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Create GPUProgram [%s] object failed !", name.c_str());
                break;
            }

            mGPUPrograms.insert(GPUProgramsValue(name, program));
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Material::removeGPUProgram(const String &name)
    {
        TResult ret = T3D_OK;
        mGPUPrograms.erase(name);
        return ret;
    }

    //--------------------------------------------------------------------------

    GPUProgramPtr Material::getGPUProgram(const String &name) const
    {
        return mGPUPrograms.at(name);
    }

    //--------------------------------------------------------------------------

    TResult Material::addGPUConstBuffer(
        const String &name, GPUConstBufferPtr &buffer, size_t bufSize)
    {
        TResult ret = T3D_OK;

        do 
        {
            buffer = T3D_GPU_CONST_BUFFER_MGR.loadBuffer(name, bufSize);
            if (buffer == nullptr)
            {
                ret = T3D_ERR_RES_CREATE_GPUCBUFFER;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Create GPUConstBuffer [%s] object failed !", name.c_str());
                break;
            }

            mConstBuffers.insert(GPUConstBuffersValue(name, buffer));
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Material::removeGPUConstBuffer(const String &name)
    {
        TResult ret = T3D_OK;
        mConstBuffers.erase(name);
        return ret;
    }

    //--------------------------------------------------------------------------

    GPUConstBufferPtr Material::getGPUConstBuffer(const String &name) const
    {
        return mConstBuffers.at(name);
    }

    //--------------------------------------------------------------------------

    TResult Material::compile()
    {
        TResult ret = T3D_OK;

        do 
        {
            auto i = mTechniques.begin(), iend = mTechniques.end();
            for (i = mTechniques.begin(); i != iend; ++i)
            {
                TechniquePtr tech = *i;
                ret = tech->compile();
                if (ret == T3D_OK)
                    mSupportedTechniques.push_back(tech);
            }

            ret = T3D_OK;
        } while (0);

        return ret;
    }
}
