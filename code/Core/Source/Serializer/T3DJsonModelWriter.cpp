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


#include "Serializer/T3DJsonModelWriter.h"
#include "Resource/T3DModel.h"
#include "protobuf/FileScriptObject.pb.h"
#include <google/protobuf/util/json_util.h>


namespace Tiny3D
{
    //--------------------------------------------------------------------------
    
    T3D_IMPLEMENT_CLASS_1(JsonModelWriter, ModelWriter);

    //--------------------------------------------------------------------------
    
    JsonModelWriterPtr JsonModelWriter::create()
    {
        JsonModelWriterPtr writer = new JsonModelWriter();
        writer->release();
        return writer;
    }

    //--------------------------------------------------------------------------
    
    JsonModelWriter::JsonModelWriter()
    {

    }

    //--------------------------------------------------------------------------

    JsonModelWriter::~JsonModelWriter()
    {

    }

    //--------------------------------------------------------------------------

    TResult JsonModelWriter::serialize(DataStream &stream, Model *model)
    {
        TResult ret = T3D_OK;

        Script::FileFormat::FileLevel *data = (Script::FileFormat::FileLevel *)model->getModelData();

        String str;
        google::protobuf::util::JsonOptions opts;
        opts.add_whitespace = true;
        opts.always_print_enums_as_ints = false;
        opts.always_print_primitive_fields = true;
        google::protobuf::util::Status status = google::protobuf::util::MessageToJsonString(*data, &str, opts);

        stream.write((void*)str.c_str(), str.length());

        return ret;
    }
}
