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


#include "Serializer/T3DBinMaterialReader.h"
#include "T3DErrorDef.h"
#include "protobuf/MaterialScriptObject.pb.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(BinMaterialReader, MaterialReader);

    //--------------------------------------------------------------------------

    BinMaterialReaderPtr BinMaterialReader::create(const BuiltinConstantMap &definitions)
    {
        BinMaterialReaderPtr reader = new BinMaterialReader(definitions);
        reader->release();
        return reader;
    }

    //--------------------------------------------------------------------------

    BinMaterialReader::BinMaterialReader(const BuiltinConstantMap &definitions)
        : MaterialReader(definitions)
    {

    }

    //--------------------------------------------------------------------------

    BinMaterialReader::~BinMaterialReader()
    {

    }

    //--------------------------------------------------------------------------

    TResult BinMaterialReader::parse(DataStream &stream, Material *material)
    {
        TResult ret = T3D_OK;

        do 
        {
            uint8_t *data = nullptr;
            size_t size = stream.size();
            size = stream.read(data);

            if (size == 0)
            {
                ret = T3D_ERR_INVALID_SIZE;
                break;
            }

            // 读取文件头
            T3DFileHeader *header = (T3DFileHeader *)data;

            if (stricmp(header->magic, T3D_FILE_MAGIC) != 0)
            {
                // 非法的文件类型
                ret = T3D_ERR_RES_INVALID_FILETYPE;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Invalid file type !");
                break;
            }

            if (header->subtype != T3D_FILE_SUBTYPE_SCC)
            {
                // 非法材质脚本类型
                ret = T3D_ERR_RES_INVALID_FILETYPE;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Invalid file subtype !");
                break;
            }

            // 从 proto buffer 解析出来 pb 对象
            data += sizeof(T3DFileHeader);
            size -= sizeof(T3DFileHeader);
            Script::MaterialSystem::Material src;

            if (!src.ParseFromArray(data, size))
            {
                ret = T3D_ERR_RES_INVALID_CONTENT;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Invalid file content !");
                break;
            }

            ret = parseMaterial(&src, material);
        } while (0);

        return ret;
    }

    
}

