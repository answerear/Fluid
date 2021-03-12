/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2017  Answer Wong
 * For latest info, see https://github.com/asnwerear/Tiny3D
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

#include "Adapter/Android/T3DJniApi.h"


namespace Tiny3D
{
    bool GetClassStaticMethodID(JNIEnv *pEnv, JNICallParam &param, const char *className, const char *methodName, const char *methodParam)
    {
        bool ret = false;

        do
        {
            if (pEnv == nullptr)
                break;

            param.classID = pEnv->FindClass(className);
            if (param.classID == 0)
                break;

            param.methodID = pEnv->GetStaticMethodID(param.classID, methodName, methodParam);
            if (param.methodID == 0)
                break;

            ret = true;
        } while (0);

        return ret;
    }

    void DeleteLocalRef(JNIEnv *pEnv, JNICallParam &param)
    {
        if (pEnv != nullptr && param.classID)
        {
            pEnv->DeleteLocalRef(param.classID);
        }
    }
}
