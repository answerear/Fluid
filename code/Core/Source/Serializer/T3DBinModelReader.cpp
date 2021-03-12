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


#include "Serializer/T3DBinModelReader.h"
#include "Resource/T3DModel.h"
#include "protobuf/FileScriptObject.pb.h"
#include "T3DErrorDef.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(BinModelReader, ModelReader);

    //--------------------------------------------------------------------------
    
    BinModelReaderPtr BinModelReader::create()
    {
        BinModelReaderPtr reader = new BinModelReader();
        reader->release();
        return reader;
    }

    //--------------------------------------------------------------------------
    
    BinModelReader::BinModelReader()
    {

    }

    //--------------------------------------------------------------------------
    
    BinModelReader::~BinModelReader()
    {

    }

    //--------------------------------------------------------------------------
    
    TResult BinModelReader::parse(DataStream &stream, Model *model)
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
                // 非法模型类型
                ret = T3D_ERR_RES_INVALID_FILETYPE;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Invalid file subtype !");
                break;
            }

            // 从 proto buffer 解析出来 pb 对象
            data += sizeof(T3DFileHeader);
            size -= sizeof(T3DFileHeader);
            Script::FileFormat::FileLevel *modelData = (Script::FileFormat::FileLevel *)model->getModelData();
            Script::FileFormat::FileLevelData *body = modelData->mutable_data();

            if (!body->ParseFromArray(data, size))
            {
                ret = T3D_ERR_RES_INVALID_CONTENT;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Invalid file content !");
                break;
            }
        } while (false);

        return ret;
    }
}
