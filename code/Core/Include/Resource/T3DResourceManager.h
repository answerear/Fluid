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

#ifndef __T3D_RESOURCE_MANAGER_H__
#define __T3D_RESOURCE_MANAGER_H__


#include "Resource/T3DResource.h"


namespace Tiny3D
{
    /**
     * @class   ResourceManager
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API ResourceManager : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  virtual ResourceManager::~ResourceManager();
         * @brief   析構函數
         */
        virtual ~ResourceManager();

        /**
         * @fn  virtual ResourcePtr ResourceManager::load(const String &name, 
         *      int32_t argc, ...);
         * @brief   從文件加載資源到內存並生成資源對象
         * @param   name    The name.
         * @param   argc    The argc.
         * @param   ...     Variable arguments providing additional information.
         * @return  A ResourcePtr.
         */
        virtual ResourcePtr load(const String &name, int32_t argc, ...);

        /**
         * @fn  virtual TResult ResourceManager::unload(ResourcePtr res);
         * @brief   從內存中卸載資源
         * @param   res The resource.
         * @return  A TResult.
         */
        virtual TResult unload(ResourcePtr res);

        /**
         * @fn  virtual TResult ResourceManager::unloadAllResources();
         * @brief   卸載所有資源，慎用 ！
         * @return  A TResult.
         */
        virtual TResult unloadAllResources();

        /**
         * @fn  virtual TResult ResourceManager::unloadUnused();
         * @brief   把當前資源管理裡所有不適用資源從內存中卸載掉
         * @return  A TResult.
         */
        virtual TResult unloadUnused();

        /**
         * @fn  ResourcePtr ResourceManager::clone(ResourcePtr src);
         * @brief   從源資源克隆 一份新資源出來
         * @param [in]  src : 源資源對象.
         * @return  返回一個新的與源資源對象相同內容的對象.
         * @remarks  所有的 Resource 派生類都需要實現 Resource::clone() 接口。 
         *           本接口將會調用 Resource::clone() 接口來實現具體的克隆邏輯.
         */
        ResourcePtr clone(ResourcePtr src);

        /**
         * @fn  ResourcePtr ResourceManager::getResource( const String &name, 
         *      ID cloneID = T3D_INVALID_ID) const;
         * @brief   根據資源名稱獲取對應資源對象
         * @param [in]  name    : 資源名稱.
         * @param [in]  cloneID (Optional) : 傳入該參數直接用該ID查找，默認自動找非克隆對象.
         * @return  返回查詢的資源對象，如果返回 NULL_PTR 則表示沒有該資源。.
         */
        ResourcePtr getResource(
            const String &name, ID cloneID = T3D_INVALID_ID) const;

    protected:
        /**
         * @fn  ResourceManager::ResourceManager();
         * @brief   構造函數
         */
        ResourceManager();

        /**
         * @fn  virtual ResourcePtr ResourceManager::create( 
         *      const String &strName, int32_t argc, va_list args) = 0;
         * @brief   創建具體資源對象，具體子類實現該方法
         * @param [in]  strName : 資源名稱.
         * @param [in]  argc    : 資源創建帶的參數列表大小.
         * @param [in]  args    : 參數列表.
         * @return  A ResourcePtr.
         */
        virtual ResourcePtr create(
            const String &strName, int32_t argc, va_list args) = 0;

        /**
         * @fn  uint32_t ResourceManager::hash(const char *str) const;
         * @brief   根據名稱計算資源 hash 值，作為其ID
         * @param   str The string.
         * @return  An uint32_t.
         */
        uint32_t hash(const char *str) const;

        /**
         * @fn  ID ResourceManager::toID(const String &name) const;
         * @brief   根據名稱生成ID
         * @param   name    The name.
         * @return  Name as an ID.
         */
        ID toID(const String &name) const;

        /**
         * @fn  ID ResourceManager::toCloneID(const String &name, 
         *      ID cloneID) const;
         * @brief   根據名稱生成克隆對象 ID
         * @param   name    The name.
         * @param   cloneID Identifier for the clone.
         * @return  The given data converted to an ID.
         */
        ID toCloneID(const String &name, ID cloneID) const;

    protected:
        typedef TMap<ID, ResourcePtr>       Resources;
        typedef Resources::iterator         ResourcesItr;
        typedef Resources::const_iterator   ResourcesConstItr;
        typedef Resources::value_type       ResourcesValue;

        typedef TMap<String, Resources>         ResourcesMap;
        typedef ResourcesMap::iterator          ResourcesMapItr;
        typedef ResourcesMap::const_iterator    ResourcesMapConstItr;
        typedef ResourcesMap::value_type        ResourcesMapValue;

        Resources   mResourcesCache;    /**< 資源對象池 */
        ID          mCloneID;           /**< 克隆ID */
    };
}


#endif  /*__T3D_RESOURCE_MANAGER_H__*/
