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


#ifndef __T3D_MATERIAL_MANAGER_H__
#define __T3D_MATERIAL_MANAGER_H__


#include "Resource/T3DResourceManager.h"
#include "Resource/T3DMaterial.h"


namespace Tiny3D
{
    /**
     * @class   MaterialManager
     * @brief   材质资源管理器
     */
    class T3D_ENGINE_API MaterialManager
        : public Singleton<MaterialManager>
        , public ResourceManager
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static MaterialManagerPtr create();
         * @brief   创建材质管理器对象
         * @return  返回一个材质管理器对象.
         */
        static MaterialManagerPtr create();

        /**
         * @fn  virtual ~MaterialManager();
         * @brief   析构函数
         */
        virtual ~MaterialManager();

        /**
         * @fn  virtual MaterialPtr loadMaterial(const String &name, 
         *      Material::MaterialType matType);
         * @brief   加载材质
         * @param [in]  name    : 材质资源名称.
         * @param [in]  matType : 材质类型.
         * @return  返回一个新建材质对象.
         * @sa  enum Material::MaterialType
         */
        virtual MaterialPtr loadMaterial(const String &name, 
            Material::MaterialType matType);

        /**
         * @fn  virtual TResult unloadMaterial(MaterialPtr material);
         * @brief   卸载材质资源
         * @param [in]  material    : 要卸载的材质资源对象.
         * @return  void.
         */
        virtual TResult unloadMaterial(MaterialPtr material);

    protected:
        /**
         * @fn  MaterialManager();
         * @brief   构造函数
         */
        MaterialManager();

        /**
         * @fn  virtual ResourcePtr create(const String &name, int32_t argc, 
         *      va_list args) override;
         * @brief   重写基类接口，实现创建材质对象
         * @param [in]  name    资源名称.
         * @param [in]  argc    传入的参数数量.
         * @param [in]  args    参数列表.
         * @return  返回新建资源对象.
         * @sa  ResourcePtr Resource::create(const String &amp;name, 
         *      int32_t argc, va_list args)
         */
        virtual ResourcePtr create(const String &name, int32_t argc, 
            va_list args) override;

    protected:

    };

    #define T3D_MATERIAL_MGR        (MaterialManager::getInstance())
}


#endif  /*__T3D_MATERIAL_MANAGER_H__*/
