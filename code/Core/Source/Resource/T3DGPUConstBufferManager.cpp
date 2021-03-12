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


#include "Resource/T3DGPUConstBufferManager.h"
#include "Resource/T3DArchive.h"
#include "Kernel/T3DAgent.h"
#include "Serializer/T3DSerializerManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(GPUConstBufferManager);
    T3D_IMPLEMENT_CLASS_1(GPUConstBufferManager, ResourceManager);

    //--------------------------------------------------------------------------

    GPUConstBufferManagerPtr GPUConstBufferManager::create()
    {
        GPUConstBufferManagerPtr mgr = new GPUConstBufferManager();
        mgr->release();
        return mgr;
    }

    //--------------------------------------------------------------------------

    GPUConstBufferManager::GPUConstBufferManager()
    {

    }

    //--------------------------------------------------------------------------

    GPUConstBufferManager::~GPUConstBufferManager()
    {

    }

    //--------------------------------------------------------------------------

    GPUConstBufferPtr GPUConstBufferManager::loadBuffer(
        const String &name, size_t bufSize)
    {
        return smart_pointer_cast<GPUConstBuffer>(
            ResourceManager::load(name, 1, bufSize));
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBufferManager::unloadBuffer(GPUConstBufferPtr material)
    {
        return unload(material);
    }

    //--------------------------------------------------------------------------

    ResourcePtr GPUConstBufferManager::create(const String &name, int32_t argc,
        va_list args)
    {
        GPUConstBufferPtr buffer;

        if (argc == 1)
        {
            size_t bufSize = va_arg(args, size_t);
            buffer = GPUConstBuffer::create(name, bufSize);
        }
        
        return buffer;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBufferManager::loadBuiltInResources()
    {
        TResult ret = T3D_OK;

        do 
        {
            // 加載文件
            String name("builtin/program/BuiltinConstant.t3d");
            ArchivePtr archive = T3D_AGENT.getAssetsArchive(name);
            if (archive == nullptr)
            {
                ret = T3D_ERR_IMG_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Could not find the archive for file %s !",
                    name.c_str());
                break;
            }

            String path = T3D_AGENT.getMainAssetsPath(name);
            MemoryDataStream stream;
            ret = archive->read(path, stream);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Read constant content failed from file %s ! ",
                    name.c_str());
                break;
            }

            // 交給腳本解析器解析
//             ret = T3D_SCRIPT_PARSER.parse(stream);
            ret = T3D_SERIALIZER_MGR.parseMaterial(stream, nullptr);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Could not parse constant file %s !", name.c_str());
                break;
            }
        } while (0);

        return ret;
    }
}
