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


#include "Resource/T3DResourceManager.h"
#include "T3DErrorDef.h"
#include <sstream>


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(ResourceManager, Object);

    //--------------------------------------------------------------------------

    ResourceManager::ResourceManager()
        : mCloneID(T3D_INVALID_ID)
    {

    }

    //--------------------------------------------------------------------------

    ResourceManager::~ResourceManager()
    {
        unloadAllResources();
    }

    //--------------------------------------------------------------------------

    ID ResourceManager::toID(const String &name) const
    {
        return hash(name.c_str());
    }

    //--------------------------------------------------------------------------

    uint32_t ResourceManager::hash(const char *str) const
    {
        uint32_t value = 5381;

        while (*str)
        {
            value += (value << 5) + (*str++);
        }

        return (value & 0x7FFFFFFF);
    }

    //--------------------------------------------------------------------------

    ID ResourceManager::toCloneID(const String &name, ID cloneID) const
    {
        std::stringstream ss;
        ss.width(4);
        ss.fill('0');
        ss << name << "_clone#" << cloneID;
        return hash(ss.str().c_str());
    }

    //--------------------------------------------------------------------------

    ResourcePtr ResourceManager::load(const String &name, int32_t argc, ...)
    {
        ResourcePtr res = nullptr;

        ID resID = toID(name);

        do 
        {
            // 從 cache 中搜索
            auto itr = mResourcesCache.find(resID);
            if (itr != mResourcesCache.end())
            {
                // cache 中存在，直接返回cache中的，並且把引用計數遞增
                res = itr->second;
                res->mResReferCount++;
                break;
            }

            // cache 中沒有，只能新建對象
            va_list params;
            va_start(params, argc);
            res = create(name, argc, params);
            va_end(params);

            if (res == nullptr)
            {
                // 創建失敗
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Create resource [%s] object failed !", name.c_str());
                break;
            }

            TResult ret = res->load();
            if (T3D_FAILED(ret))
            {
                // 加載失敗
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Load resource [%s] failed !", name.c_str());
                res = nullptr;
                break;
            }

            auto rval = mResourcesCache.insert(ResourcesValue(resID, res));
            if (!rval.second)
            {
                // 插入緩存失敗
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Insert resource [%s] to cache failed !", name.c_str());
                res = nullptr;
                break;
            }

            res->mID = resID;
            res->mIsLoaded = true;
        } while (0);

        return res;
    }

    //--------------------------------------------------------------------------

    TResult ResourceManager::unload(ResourcePtr res)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (res == nullptr)
            {
                ret = T3D_ERR_RES_INVALID_OBJECT;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Invalid resource object !");
                break;
            }

            if (res->mResReferCount == 0)
            {
                // 沒有地方引用了，已經卸載了
                break;
            }

            // 引用計數遞減，減少一次引用
            res->mResReferCount--;

            if (res->resReferCount() > 0)
            {
                // 資源還有其他地方引用，不卸載
                break;
            }

            // 卸載資源
            ID resID = (res->isCloned() ? res->getCloneID() : res->getID());
            auto itr = mResourcesCache.find(resID);
            if (itr == mResourcesCache.end())
            {
                ret = T3D_ERR_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Couldn't find the resource [%s] in the cache !", 
                    res->getName().c_str());
                break;
            }

            // 讓資源自己處理卸載事情
            ret = res->unload();
            if (T3D_FAILED(ret))
            {
                break;
            }

            // 最後從緩存中清除掉
            mResourcesCache.erase(itr);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ResourceManager::unloadAllResources()
    {
        TResult ret = T3D_OK;

        auto itr = mResourcesCache.begin();
        while (itr != mResourcesCache.end())
        {
            auto res = itr->second;
            itr++;
            if (res->isLoaded())
                unload(res);
        }

        mResourcesCache.clear();

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ResourceManager::unloadUnused()
    {
        TResult ret = T3D_OK;

        do 
        {
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    ResourcePtr ResourceManager::clone(ResourcePtr src)
    {
        ResourcePtr res;

        do 
        {
            if (src == nullptr)
            {
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Invalid source object to clone !");
                break;
            }

            res = src->clone();
            if (res == nullptr)
            {
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Clone resource [%s] object failed !", 
                    src->getName().c_str());
                break;
            }

            ID cloneID = toCloneID(res->getName(), mCloneID++);
            res->mCloneID = cloneID;

            auto rval = mResourcesCache.insert(ResourcesValue(cloneID, res));
            if (!rval.second)
            {
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Add resource [%s] cloned to cache failed !",
                    res->getName().c_str());
                res = nullptr;
            }
        } while (0);

        return res;
    }

    //--------------------------------------------------------------------------

    ResourcePtr ResourceManager::getResource(
        const String &name, ID cloneID /* = T3D_INVALID_ID */) const
    {
        ResourcePtr res;

        do 
        {
            ID resID = T3D_INVALID_ID;
            if (cloneID != T3D_INVALID_ID)
            {
                // 克隆對象
                resID = cloneID;
            }
            else
            {
                resID = toID(name);
            }

            auto itr = mResourcesCache.find(resID);
            if (itr == mResourcesCache.end())
            {
                break;
            }

            res = itr->second;
        } while (0);

        return res;
    }
}

