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

#ifndef __T3D_SINGLETON_H__
#define __T3D_SINGLETON_H__


#include "T3DType.h"
#include "T3DMacro.h"
#include <vector>


#if defined (T3D_OS_WINDOWS)
#pragma warning(disable:4661)
#endif


#define T3D_INIT_SINGLETON(T) template<> T::pointer Singleton<T>::m_pInstance = nullptr


namespace Tiny3D
{
    template <typename T>
    class Singleton
    {
        T3D_DISABLE_COPY(Singleton);

    public:
        typedef T  value_type;
        typedef T* pointer;
        typedef T& reference;

        Singleton()
        {
            T3D_ASSERT(m_pInstance == nullptr);
            m_pInstance = static_cast<pointer>(this);
        }

        virtual ~Singleton()
        {
            m_pInstance = nullptr;
        }

        static reference getInstance()
        {
            return *m_pInstance;
        }

        static pointer getInstancePtr()
        {
            return m_pInstance;
        }

    protected:
        static pointer m_pInstance;
    };
}


#endif  /*__T3D_SINGLETON_H__*/
