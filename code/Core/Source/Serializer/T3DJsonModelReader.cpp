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


#include "Serializer/T3DJsonModelReader.h"
#include "Resource/T3DModel.h"
#include "T3DErrorDef.h"
#include "protobuf/FileScriptObject.pb.h"
#include <google/protobuf/util/json_util.h>


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(JsonModelReader, ModelReader);

    //--------------------------------------------------------------------------
    
    JsonModelReaderPtr JsonModelReader::create()
    {
        JsonModelReaderPtr reader = new JsonModelReader();
        reader->release();
        return reader;
    }

    //--------------------------------------------------------------------------
    
    JsonModelReader::JsonModelReader()
        : mStr(nullptr)
    {
        mStr = new char[JSON_STRING_SIZE];
    }

    //--------------------------------------------------------------------------
    
    JsonModelReader::~JsonModelReader()
    {
        T3D_SAFE_DELETE_ARRAY(mStr);
    }

    //--------------------------------------------------------------------------
    
    TResult JsonModelReader::parse(DataStream &stream, Model *model)
    {
        TResult ret = T3D_OK;


        do 
        {
            long_t size = stream.size();
            if (size >= JSON_STRING_SIZE)
            {
                ret = T3D_ERR_OUT_OF_BOUND;
                T3D_LOG_ERROR(LOG_TAG_ENGINE,
                    "The length of json string is out of bound when parsing json material !");
                break;
            }

            stream.read(mStr, size);
            mStr[size] = 0;

            Script::FileFormat::FileLevel *modelData = (Script::FileFormat::FileLevel *)model->getModelData();

            google::protobuf::util::JsonParseOptions opts;
            opts.ignore_unknown_fields = true;
            google::protobuf::StringPiece input(mStr);
            google::protobuf::util::Status status = google::protobuf::util::JsonStringToMessage(input, modelData, opts);

            if (!status.ok())
            {
                ret = T3D_ERR_FAIL;
                T3D_LOG_ERROR(LOG_TAG_ENGINE,
                    "Json string to message failed ! Error : %s",
                    status.message().as_string().c_str());
                break;
            }

            if (modelData->header().magic() != T3D_FILE_MAGIC
                && modelData->header().type() != Script::FileFormat::FileHeader_FileType_Level)
            {
                ret = T3D_ERR_RES_INVALID_FILETYPE;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Invalid file type !");
                break;
            }
        } while (false);

        return ret;
    }
}
