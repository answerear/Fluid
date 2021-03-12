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

#ifndef __T3D_JSON_MATERIAL_READER_H__
#define __T3D_JSON_MATERIAL_READER_H__


#include "Serializer/T3DMaterialReader.h"


namespace Tiny3D
{
    class JsonMaterialReader : public MaterialReader
    {
        enum 
        {
            JSON_STRING_SIZE = 10 * 1024 * 1024
        };

        T3D_DECLARE_CLASS();
        T3D_DISABLE_COPY(JsonMaterialReader);

    public:
        static JsonMaterialReaderPtr create(const BuiltinConstantMap& definitions);

        virtual ~JsonMaterialReader();

    protected:
        JsonMaterialReader(const BuiltinConstantMap& definitions);

        virtual TResult parse(DataStream &stream, Material *material) override;

    private:
        char *mStr;
    };
}


#endif  /*__T3D_JSON_MATERIAL_READER_H__*/
