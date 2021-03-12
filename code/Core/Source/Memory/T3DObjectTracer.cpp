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


#include "Memory/T3DObjectTracer.h"
#include <sstream>


namespace Tiny3D
{
    T3D_INIT_SINGLETON(ObjectTracer);

    ObjectTracer::ObjectTracer(bool enabled /* = false */)
        : mIsEnabled(enabled)
        , mStream(nullptr)
    {

    }

    ObjectTracer::~ObjectTracer()
    {

    }

    void ObjectTracer::dumpMemoryInfo() const
    {
        if (mIsEnabled)
        {
            printInfo("Dump memory leak =================================>\n");

            std::stringstream ss;

            for (auto itr = mObjects.begin(); itr != mObjects.end(); ++itr)
            {
                Object *obj = *itr;

                ss.str("");
                ss << "Leak Object : " << typeid(*obj).name() << " ReferCount : " << obj->referCount() << "\n";
                printInfo(ss.str());
            }

            ss.str("");

            ss << "Total leak objects " << mObjects.size();
        }
    }

    void ObjectTracer::dumpMemoryInfo(FileDataStream &fs) const
    {
        mStream = &fs;
        dumpMemoryInfo();
        mStream = nullptr;
    }

    void ObjectTracer::printInfo(const String &str) const
    {
        if (mStream != nullptr)
        {
            DataStream &stream = *mStream;
            stream << str;
        }
        else
        {
            T3D_CONSOLE.print(str.c_str());
        }
    }
}

