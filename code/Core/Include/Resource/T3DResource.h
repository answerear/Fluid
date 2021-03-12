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


#ifndef __T3D_RESOURCE_H__
#define __T3D_RESOURCE_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Kernel/T3DObject.h"


namespace Tiny3D
{
    /**
     * @class   Resource
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API Resource : public Object
    {
        friend class ResourceManager;

        T3D_DECLARE_CLASS();

    public:
        /**
         * @enum    Type
         * @brief   資源類型枚舉
         */
        enum class Type : size_t
        {
            E_RT_UNKNOWN = 0,   /**< 未知類型資源 */
            E_RT_DYLIB,         /**< 動態庫 */
            E_RT_ARCHIVE,       /**< 文件檔案系統 */
            E_RT_MATERIAL,      /**< 材質 */
            E_RT_TEXTURE,       /**< 紋理 */
            E_RT_SHADER,        /**< 著色器 */
            E_RT_GPUPROGRAM,    /**< GPU程序 */
            E_RT_GPUCBUFFER,    /**< GPU 常量緩衝區 */
            E_RT_SAMPLER,       /**< 采样器 */
            E_RT_MODEL,         /**< 模型数据 */
        };

        /**
         * @fn  virtual Resource::~Resource();
         * @brief   構造函數
         */
        virtual ~Resource();

        /**
         * @fn  virtual Type Resource::getType() const = 0;
         * @brief   獲取資源類型
         * @return  The type.
         */
        virtual Type getType() const = 0;

        /**
         * @fn  ID Resource::getID() const
         * @brief   獲取資源唯一ID
         * @return  The identifier.
         */
        ID getID() const
        {
            return mID;
        }
        
        /**
         * @fn  ID Resource::getCloneID() const
         * @brief   獲取克隆資源唯一ID，當該資源是從其他資源克隆出來試，該ID才有效
         * @return  The clone identifier.
         */
        ID getCloneID() const
        {
            return mCloneID;
        }

        /**
         * @fn  bool Resource::isCloned() const
         * @brief   是否克隆資源
         * @return  True if cloned, false if not.
         */
        bool isCloned() const
        {
            return (mCloneID != T3D_INVALID_ID);
        }

        /**
         * @fn  size_t Resource::getSize() const
         * @brief   獲取資源大小
         * @return  The size.
         */
        size_t getSize() const
        {
            return mSize;
        }

        /**
         * @fn  const String Resource::&getName() const
         * @brief   獲取資源名稱
         * @return  The name.
         */
        const String &getName() const
        {
            return mName;
        }

        /**
         * @fn  bool Resource::isLoaded() const
         * @brief   獲取資源是否加載
         * @return  True if loaded, false if not.
         */
        bool isLoaded() const
        {
            return mIsLoaded;
        }

        /**
         * @fn  uint32_t Resource::resReferCount() const
         * @brief   獲取資源引用計數
         * @return  An uint32_t.
         */
        uint32_t resReferCount() const
        {
            return mResReferCount;
        }

    protected:
        /**
         * @fn  Resource::Resource(const String &name);
         * @brief   構造函數
         * @param   name    The name.
         * @remarks 本類不能直接實例化，所以只能隱藏構造函數.
         */
        Resource(const String &name);

        /**
         * @fn  virtual TResult Resource::load() = 0;
         * @brief   加載資源
         * @return  A TResult.
         * @remarks 每種類型資源需要各自實現其加載邏輯，資源只有加載後才能使用.
         */
        virtual TResult load() = 0;

        /**
         * @fn  virtual TResult Resource::unload();
         * @brief   卸載資源
         * @return  A TResult.
         * @remarks 每種類型資源需要各自實現其卸載邏輯，資源卸載後就不能再使用了.
         */
        virtual TResult unload();

        /**
         * @fn  virtual ResourcePtr Resource::clone() const = 0;
         * @brief   克隆資源
         * @return  A copy of this object.
         * @remarks  每種類型資源需要各自實現其克隆邏輯，克隆出一個新資源對象.
         */
        virtual ResourcePtr clone() const = 0;

    private:
        uint32_t    mResReferCount; /**< 資源自身的引用計數 */

    protected:
        ID      mID;        /**< 資源ID */
        ID      mCloneID;   /**< 如果資源是從其他資源克隆出來的，該ID才有效 */
        size_t  mSize;      /**< 資源大小 */
        bool    mIsLoaded;  /**< 資源是否加載標記 */
        String  mName;      /**< 資源名稱 */
    };
}


#endif  /*__T3D_RESOURCE_H__*/
