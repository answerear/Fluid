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


#ifndef __T3D_DYLIB_H__
#define __T3D_DYLIB_H__


#include "Resource/T3DResource.h"


namespace Tiny3D
{
    /**
     * @class   Dylib
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API Dylib : public Resource
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static DylibPtr Dylib::create(const String &name);
         * @brief   创建 Dylib 对象
         * @param   name    The name.
         * @return  A DylibPtr.
         */
        static DylibPtr create(const String &name);

        /**
         * @fn  virtual Dylib::~Dylib();
         * @brief   析构函数
         */
        virtual ~Dylib();

        /**
         * @fn  virtual Type Dylib::getType() const override;
         * @brief   重写 Resource::getType()
         * @return  The type.
         */
        virtual Type getType() const override;

        /**
         * @fn  virtual void Dylib::*getSymbol(const String &name) const;
         * @brief   根据名称获取对应符号地址
         * @param   name    The name.
         * @return  Null if it fails, else the symbol.
         */
        virtual void *getSymbol(const String &name) const;

    protected:
        /**
         * @fn  Dylib::Dylib(const String &name);
         * @brief   构造函数
         * @param   name    The name.
         */
        Dylib(const String &name);

        /**
         * @fn  virtual TResult Dylib::load() override;
         * @brief   重写 Resource::load()
         * @return  A TResult.
         */
        virtual TResult load() override;

        /**
         * @fn  virtual TResult Dylib::unload() override;
         * @brief   重写 Resource::unlaod()
         * @return  A TResult.
         */
        virtual TResult unload() override;

        /**
         * @fn  virtual ResourcePtr Dylib::clone() const override;
         * @brief   重写 Resource::clone()
         * @return  A copy of this object.
         */
        virtual ResourcePtr clone() const override;

    protected:
        THandle mHandle;    /**< The handle */
    };
}


#endif  /*__T3D_DYLIB_H__*/
