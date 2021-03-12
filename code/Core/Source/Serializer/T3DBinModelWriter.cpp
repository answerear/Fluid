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


#include "Serializer/T3DBinModelWriter.h"
#include "Resource/T3DModel.h"
#include "protobuf/FileScriptObject.pb.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------
    
    T3D_IMPLEMENT_CLASS_1(BinModelWriter, ModelWriter);

    //--------------------------------------------------------------------------
    
    BinModelWriterPtr BinModelWriter::create()
    {
        BinModelWriterPtr writer = new BinModelWriter();
        writer->release();
        return writer;
    }

    //--------------------------------------------------------------------------
    
    BinModelWriter::BinModelWriter()
    {

    }

    //--------------------------------------------------------------------------
    
    BinModelWriter::~BinModelWriter()
    {

    }

    //--------------------------------------------------------------------------
    
    TResult BinModelWriter::serialize(DataStream &stream, Model *model)
    {
        TResult ret = T3D_OK;

        Script::FileFormat::FileLevel *data = (Script::FileFormat::FileLevel *)model->getModelData();

        T3DFileHeader header;
        memcpy(header.magic, T3D_FILE_MAGIC, 3);
        header.magic[3] = 0;
        header.version = T3D_FILE_MDL_VERSION;
        header.subtype = T3D_FILE_SUBTYPE_MDL;
        header.filesize = 0;
        int size = data->data().ByteSize();
        char *buffer = new char[size + sizeof(header)];
        memcpy(buffer, &header, sizeof(header));
        char *body = buffer + sizeof(header);
        data->data().SerializeToArray(body, size);
        stream.write(buffer, size);
        T3D_SAFE_DELETE_ARRAY(buffer);

        return ret;
    }
}
