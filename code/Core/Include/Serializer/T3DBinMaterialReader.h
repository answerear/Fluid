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

#ifndef __T3D_BIN_MATERIAL_READER_H__
#define __T3D_BIN_MATERIAL_READER_H__


#include "Serializer/T3DMaterialReader.h"



namespace Tiny3D
{
    

//     using namespace Script;

    /**
     * @class   BinMaterialReader
     * @brief   A bin material reader.
     */
    class BinMaterialReader : public MaterialReader
    {
        T3D_DECLARE_CLASS();
        T3D_DISABLE_COPY(BinMaterialReader);

    public:
        /**
         * @fn  static BinMaterialReaderPtr BinMaterialReader::create(
         *      const BuiltinConstantMap &definitions);
         * @brief   Creates a new BinMaterialReaderPtr
         * @param   definitions The definitions.
         * @return  A BinMaterialReaderPtr.
         */
        static BinMaterialReaderPtr create(const BuiltinConstantMap &definitions);

        /**
         * @fn  virtual BinMaterialReader::~BinMaterialReader();
         * @brief   Destructor
         */
        virtual ~BinMaterialReader();

    protected:
        /**
         * @fn  BinMaterialReader::BinMaterialReader(
         *      const BuiltinConstantMap &definitions);
         * @brief   Constructor
         * @param   definitions The definitions.
         */
        BinMaterialReader(const BuiltinConstantMap &definitions);

        /**
         * @fn  virtual TResult BinMaterialReader::parse(DataStream &stream, 
         *      Material *material) override;
         * @brief   Parses
         * @param [in,out]  stream      The stream.
         * @param [in,out]  material    If non-null, the material.
         * @return  A TResult.
         */
        virtual TResult parse(DataStream &stream, Material *material) override;

        
    };
}


#endif    /*__T3D_BIN_MATERIAL_READER_H__*/
