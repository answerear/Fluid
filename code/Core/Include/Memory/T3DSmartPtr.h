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


#ifndef __T3D_SMART_PTR_H__
#define __T3D_SMART_PTR_H__


#include "T3DPrerequisites.h"
#include <type_traits>


#if defined (T3D_OS_WINDOWS)
#if _MSC_VER >= 1900
namespace std
{
    struct _Static_tag {};
}
#endif
#else
namespace std
{
    struct _Static_tag {};
}
#endif


namespace Tiny3D
{
    /**
     * @class   SmartPtr
     * @brief   智能指针类
     * @tparam  T   Generic type parameter.
     */
    template <typename T>
    class SmartPtr
    {
    public:
        static const SmartPtr NULL_PTR; /**< The null pointer */

        /**
         * @fn  SmartPtr::SmartPtr(T *obj = nullptr)
         * @brief   构造函数
         * @param [in,out]  obj (Optional) If non-null, the object.
         */
        SmartPtr(T *obj = nullptr)
        {
            mReferObject = obj;

            if (mReferObject != nullptr)
            {
                mReferObject->acquire();
            }
        }

        /**
         * @fn  SmartPtr::SmartPtr(const SmartPtr &rkPointer)
         * @brief   Copy constructor
         * @param   rkPointer   The rk pointer.
         */
        SmartPtr(const SmartPtr &rkPointer)
        {
            mReferObject = rkPointer.mReferObject;

            if (mReferObject != nullptr)
            {
                mReferObject->acquire();
            }
        }

        /**
         * @fn  template <typename T2> SmartPtr::SmartPtr(
         *      const SmartPtr<T2> &rkOther, 
         *      typename std::enable_if<std::is_convertible<T2 *, 
         *      T *>::value, void>::type ** = 0)
         * @brief   Constructor
         * @tparam  T2  Generic type parameter.
         * @param           rkOther     The rk other.
         * @param [in,out]  parameter2  (Optional) If non-null, the second parameter.
         */
        template <typename T2>
        SmartPtr(const SmartPtr<T2> &rkOther,
            typename std::enable_if<std::is_convertible<T2 *, T *>::value, void>::type ** = 0)
        {
            mReferObject = rkOther;

            if (mReferObject != nullptr)
            {
                mReferObject->acquire();
            }
        }

        /**
         * @fn  template <typename T2> SmartPtr::SmartPtr(
         *      const SmartPtr<T2> &rkOther, const std::_Static_tag &)
         * @brief   Constructor
         * @tparam  T2  Generic type parameter.
         * @param   rkOther     The rk other.
         * @param   parameter2  The second parameter.
         */
        template <typename T2>
        SmartPtr(const SmartPtr<T2> &rkOther, const std::_Static_tag &)
        {
            mReferObject = rkOther;

            if (mReferObject != nullptr)
            {
                mReferObject->acquire();
            }
        }

        /**
         * @fn  virtual SmartPtr::~SmartPtr()
         * @brief   Destructor
         */
        virtual ~SmartPtr()
        {
            if (mReferObject != nullptr)
            {
                mReferObject->release();
            }
        }

        /**
         * @fn  operator SmartPtr::T*() const
         * @brief   T* casting operator
         * @return  The result of the operation.
         */
        operator T*() const
        {
            return (T*)mReferObject;
        }

        /**
         * @fn  T SmartPtr::&operator*() const
         * @brief   Indirection operator
         * @return  The result of the operation.
         */
        T &operator *() const
        {
            return (T&)(*mReferObject);
        }

        /**
         * @fn  T SmartPtr::*operator->() const
         * @brief   Member dereference operator
         * @return  The dereferenced object.
         */
        T *operator ->() const
        {
            return (T*)mReferObject;
        }

        /**
         * @fn  SmartPtr SmartPtr::&operator=(T *obj)
         * @brief   Assignment operator
         * @param [in,out]  obj If non-null, the object.
         * @return  A shallow copy of this object.
         */
        SmartPtr &operator =(T *obj)
        {
            if (mReferObject != obj)
            {
                if (obj != nullptr)
                {
                    obj->acquire();
                }

                if (mReferObject != nullptr)
                {
                    mReferObject->release();
                }

                mReferObject = obj;
            }

            return *this;
        }

        /**
         * @fn  SmartPtr SmartPtr::&operator=(const SmartPtr &rkPointer)
         * @brief   Assignment operator
         * @param   rkPointer   The rk pointer.
         * @return  A shallow copy of this object.
         */
        SmartPtr &operator =(const SmartPtr &rkPointer)
        {
            if (mReferObject != rkPointer.mReferObject)
            {
                if (rkPointer.mReferObject != nullptr)
                {
                    rkPointer.mReferObject->acquire();
                }

                if (mReferObject != nullptr)
                {
                    mReferObject->release();
                }

                mReferObject = rkPointer.mReferObject;
            }

            return *this;
        }

        /**
         * @fn  template <typename T2> SmartPtr 
         *      SmartPtr::&operator=(const SmartPtr<T2> &rkOther)
         * @brief   Assignment operator
         * @tparam  T2  Generic type parameter.
         * @param   rkOther The rk other.
         * @return  The result of the operation.
         */
        template <typename T2>
        SmartPtr &operator =(const SmartPtr<T2> &rkOther)
        {
            if (mReferObject != rkOther)
            {
                if (rkOther != nullptr)
                {
                    rkOther->acquire();
                }

                if (mReferObject != nullptr)
                {
                    mReferObject->release();
                }

                mReferObject = rkOther;
            }

            return *this;
        }

    protected:
        Object  *mReferObject;  /**< The refer object */
    };

    template <typename T1, typename T2>
    SmartPtr<T1> smart_pointer_cast(const SmartPtr<T2> &rkOther)
    {
        return SmartPtr<T1>(rkOther, std::_Static_tag());
    }

    template <typename T>
    const SmartPtr<T> SmartPtr<T>::NULL_PTR(nullptr);

    #define T3D_DECLARE_SMART_PTR(classname)    \
            typedef SmartPtr<classname> classname##Ptr
}


#endif  /*__T3D_SMART_PTR_H__*/
