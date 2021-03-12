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


#include "T3DClass.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    Class::Classes Class::msClasses;

    const Class *Class::getClass(const String &name)
    {
        return msClasses[name];
    }

    //--------------------------------------------------------------------------

    Class::Class(const char *name, size_t baseCount /* = 0 */, 
        const Class *base1 /* = nullptr */, const Class *base2 /* = nullptr */, 
        const Class *base3 /* = nullptr */, const Class *base4 /* = nullptr */, 
        const Class *base5 /* = nullptr */, const Class *base6 /* = nullptr */, 
        const Class *base7 /* = nullptr */, const Class *base8 /* = nullptr */)
        : mName(name)
        , mBaseClassesCount(baseCount)
    {
        mBaseClasses[0] = base1;
        mBaseClasses[1] = base2;
        mBaseClasses[2] = base3;
        mBaseClasses[3] = base4;
        mBaseClasses[4] = base5;
        mBaseClasses[5] = base6;
        mBaseClasses[6] = base7;
        mBaseClasses[7] = base8;

        msClasses.insert(ClassesValue(name, this));
    }

    //--------------------------------------------------------------------------

    bool Class::isBaseOf(const Class *cls) const
    {
        if (cls == nullptr || !cls->hasBase())
            return false;

        bool ret = false;

        for (size_t i = 0; i < cls->getBaseClassCount(); ++i)
        {
            const Class *c = cls->getBaseClass(i);

            if (c == this)
            {
                ret = true;
                break;
            }
            else
            {
                ret = isBaseOf(c);
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool Class::isSuperOf(const Class *cls) const
    {
        if (cls == nullptr || !cls->hasBase())
            return false;

        for (size_t i = 0; i < cls->getBaseClassCount(); ++i)
        {
            if (this == cls->getBaseClass(i))
                return true;
        }

        return false;
    }
}
