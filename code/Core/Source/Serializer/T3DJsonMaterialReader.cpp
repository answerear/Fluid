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


#include "Serializer/T3DJsonMaterialReader.h"
#include "protobuf/FileScriptObject.pb.h"
#include <google/protobuf/util/json_util.h>
#include "T3DErrorDef.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(JsonMaterialReader, MaterialReader);

    //--------------------------------------------------------------------------

    JsonMaterialReaderPtr JsonMaterialReader::create(const BuiltinConstantMap& definitions)
    {
        JsonMaterialReaderPtr reader = new JsonMaterialReader(definitions);
        reader->release();
        return reader;
    }

    //--------------------------------------------------------------------------

    JsonMaterialReader::JsonMaterialReader(const BuiltinConstantMap& definitions)
        : MaterialReader(definitions)
        , mStr(nullptr)
    {
        mStr = new char[JSON_STRING_SIZE];
    }

    //--------------------------------------------------------------------------

    JsonMaterialReader::~JsonMaterialReader()
    {
        T3D_SAFE_DELETE_ARRAY(mStr);
    }

    //--------------------------------------------------------------------------

    TResult JsonMaterialReader::parse(DataStream &stream, Material *material)
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

            Script::FileFormat::FileMaterial file;

            google::protobuf::util::JsonParseOptions opts;
            opts.ignore_unknown_fields = true;
            google::protobuf::StringPiece input(mStr);
            google::protobuf::util::Status status = google::protobuf::util::JsonStringToMessage(input, &file, opts);

            if (!status.ok())
            {
                ret = T3D_ERR_FAIL;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, 
                    "Json string to message failed ! Error : %s", 
                    status.message().as_string().c_str());
                break;
            }

            if (file.header().magic() != T3D_FILE_MAGIC 
                && file.header().type() != Script::FileFormat::FileHeader_FileType_Material)
            {
                ret = T3D_ERR_RES_INVALID_FILETYPE;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Invalid file type !");
                break;
            }

            const Script::MaterialSystem::Material &src = file.material();
            ret = parseMaterial(&src, material);
        } while (0);

        return ret;
    }
}


