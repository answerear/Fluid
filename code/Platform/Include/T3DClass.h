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


#ifndef __T3D_CLASS_H__
#define __T3D_CLASS_H__


#include "T3DPlatformPrerequisites.h"
#include "T3DMacro.h"


namespace Tiny3D
{
    /**
     * @class   Class
     * @brief   用于运行时动态类型检查机制 
     */
    class T3D_PLATFORM_API Class
    {
        T3D_DISABLE_COPY(Class);

    public:
        static const size_t MAX_BASE_CLASS_COUNT = 8;

        static const Class *getClass(const String &name);

        Class(const char *name, size_t baseCount = 0, 
            const Class *base1 = nullptr, const Class *base2 = nullptr, 
            const Class *base3 = nullptr, const Class *base4 = nullptr, 
            const Class *base5 = nullptr, const Class *base6 = nullptr, 
            const Class *base7 = nullptr, const Class *base8 = nullptr);

        const char *getName() const
        {
            return mName;
        }

        size_t getBaseClassCount() const
        {
            return mBaseClassesCount;
        }

        const Class *getBaseClass(size_t idx) const
        {
            T3D_ASSERT(idx < mBaseClassesCount);
            return mBaseClasses[idx];
        }

        bool hasBase() const { return mBaseClassesCount != 0; }

        /**
         * @brief 查询自己是否 cls 的基类
         */
        bool isBaseOf(const Class *cls) const;

        /**
         * @brief 查询自己是否 cls 的父类
         */
        bool isSuperOf(const Class *cls) const;

        /**
         * @brief 查询自己是否与 cls 类型一致
         */
        bool isSameAs(const Class *cls) const
        {
            return (this == cls);
        }

        /**
         * @brief 查询自己是否与 cls 一致或者是 cls 子类
         */
        bool isKindOf(const Class *cls) const
        {
            return (this == cls || cls->isBaseOf(this));
        }

    private:
        const char *mName;
        const Class *mBaseClasses[MAX_BASE_CLASS_COUNT];
        const size_t mBaseClassesCount;

        typedef TMap<String, const Class *> Classes;
        typedef Classes::iterator           ClassesItr;
        typedef Classes::const_iterator     ClassesConstItr;
        typedef Classes::value_type         ClassesValue;

        static Classes  msClasses;
    };


    template <typename TYPE, typename OBJ>
    inline bool isBaseOf(OBJ *obj)
    {
        return TYPE::getStaticClass()->isBaseOf(obj->getClass());
    }

    template <typename TYPE, typename OBJ>
    inline bool isBaseOf(const OBJ &obj)
    {
        return TYPE::getStaticClass()->isBaseOf(obj.getClass());
    }

    template <typename TYPE, typename OBJ>
    inline bool isSuperOf(OBJ *obj)
    {
        return TYPE::getStaticClass()->isSuperOf(obj->getClass());
    }

    template <typename TYPE, typename OBJ>
    inline bool isSuperOf(const OBJ &obj)
    {
        return TYPE::getStaticClass()->isSuperOf(obj.getClass());
    }

    template <typename TYPE, typename OBJ>
    inline bool isSameAs(OBJ *obj)
    {
        return TYPE::getStaticClass()->isSameAs(obj->getClass());
    }

    template <typename TYPE, typename OBJ>
    inline bool isSameAs(const OBJ &obj)
    {
        return TYPE::getStaticClass()->isSameAs(obj.getClass());
    }

    template <typename TYPE, typename OBJ>
    inline bool isKindOf(OBJ *obj)
    {
        return TYPE::getStaticClass()->isKindOf(obj->getClass());
    }

    template <typename TYPE, typename OBJ>
    inline bool isKindOf(const OBJ &obj)
    {
        return TYPE::getStaticClass()->isKindOf(obj.getClass());
    }

    #define T3D_CLASS(cls)  cls::getStaticClass()

    #define T3D_DECLARE_CLASS() \
        public: \
            static const Class *getStaticClass() { return &msClass; } \
            virtual const Class *getClass() const { return &msClass; } \
        private: \
            static const Class msClass;

    #define T3D_IMPLEMENT_CLASS_0(cls) \
        const Class cls::msClass(#cls);

    #define T3D_IMPLEMENT_CLASS_1(cls, b1) \
        const Class cls::msClass(#cls, 1, \
            b1::getStaticClass());

    #define T3D_IMPLEMENT_CLASS_2(cls, b1, b2) \
        const Class cls::msClass(#cls, 2, \
            b1::getStaticClass(), b2::getStaticClass());

    #define T3D_IMPLEMENT_CLASS_3(cls, b1, b2, b3) \
        const Class cls::msClass(#cls, 3, \
                b1::getStaticClass(), b2::getStaticClass(), \
                b3::getStaticClass());

    #define T3D_IMPLEMENT_CLASS_4(cls, b1, b2, b3, b4) \
        const Class cls::msClass(#cls, 4, \
                b1::getStaticClass(), b2::getStaticClass(), \
                b3::getStaticClass(), b4::getStaticClass());

    #define T3D_IMPLEMENT_CLASS_5(cls, b1, b2, b3, b4, b5) \
        const Class cls::msClass(#cls, 5, \
                b1::getStaticClass(), b2::getStaticClass(), \
                b3::getStaticClass(), b4::getStaticClass(), \
                b5::getStaticClass(), );

    #define T3D_IMPLEMENT_CLASS_6(cls, b1, b2, b3, b4, b5, b6) \
        const Class cls::msClass(#cls, 6, \
                b1::getStaticClass(), b2::getStaticClass(), \
                b3::getStaticClass(), b4::getStaticClass(), \
                b5::getStaticClass(), b6::getStaticClass());

    #define T3D_IMPLEMENT_CLASS_7(cls, b0, b1, b2, b3, b4, b5, b6) \
        const Class cls::msClass(#cls, 7, \
                b1::getStaticClass(), b2::getStaticClass(), \
                b3::getStaticClass(), b4::getStaticClass(), \
                b5::getStaticClass(), b6::getStaticClass(), \
                b7::getStaticClass());

    #define T3D_IMPLEMENT_CLASS_8(cls, b0, b1, b2, b3, b4, b5, b6, b7) \
        const Class cls::msClass(#cls, 8, \
                b1::getStaticClass(), b2::getStaticClass(), \
                b3::getStaticClass(), b4::getStaticClass(), \
                b5::getStaticClass(), b6::getStaticClass(), \
                b7::getStaticClass(), b8::getStaticClass());
}


#endif  /*__T3D_CLASS_H__*/
