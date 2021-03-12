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

#ifndef __T3D_SERIALIZER_MANAGER_H__
#define __T3D_SERIALIZER_MANAGER_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Kernel/T3DObject.h"
#include "Kernel/T3DCommon.h"


namespace Tiny3D
{
    /**
     * @brief 数据序列化管理器
     */
    class T3D_ENGINE_API SerializerManager 
        : public Object
        , public Singleton<SerializerManager>
    {
        T3D_DECLARE_CLASS();

    public:
        enum class FileMode : uint32_t
        {
            BINARY,
            TEXT,
        };

        static SerializerManagerPtr create();

        void setFileMode(FileMode mode) { mFileMode = mode; }

        FileMode getFileMode() const { return mFileMode; }

        TResult parseMaterial(DataStream &stream, Material *material);

        TResult serializeMaterial(DataStream &stream, Material *material);

        TResult parseModel(DataStream &stream, Model *model);

        TResult serializeModel(DataStream &stream, Model *model);

    protected:
        SerializerManager();

        void constructBuiltinConstantMap();

        BuiltinConstantMap  mBuiltinConstantMap;

        FileMode            mFileMode;
    };

    #define T3D_SERIALIZER_MGR      (SerializerManager::getInstance())
}


#endif    /*__T3D_SERIALIZER_MANAGER_H__*/
