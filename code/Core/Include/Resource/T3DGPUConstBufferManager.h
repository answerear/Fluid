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


#ifndef __T3D_GPU_CONST_BUFFER_MANAGER_H__
#define __T3D_GPU_CONST_BUFFER_MANAGER_H__


#include "Resource/T3DResourceManager.h"
#include "Resource/T3DGPUConstBuffer.h"


namespace Tiny3D
{
    /**
     * @class   GPUConstBufferManager
     * @brief   GPU 常量緩衝區管理器
     */
    class T3D_ENGINE_API GPUConstBufferManager
        : public Singleton<GPUConstBufferManager>
        , public ResourceManager
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static HardwareConstantBufferPtr create();
         * @brief   創建一個緩衝區資源管理器對象
         * @returns 調用成功返回新建的緩衝區資源管理器對象.
         */
        static GPUConstBufferManagerPtr create();

        /**
         * @fn  virtual ~GPUConstBufferManager();
         * @brief   析構函數
         */
        virtual ~GPUConstBufferManager();

        /**
         * @fn  virtual GPUConstBufferPtr loadBuffer(const String &name);
         * @brief   加載緩衝區資源
         * @param   name    緩衝區資源名稱.
         * @returns 調用成功返回緩衝區資源對象.
         */
        virtual GPUConstBufferPtr loadBuffer(const String &name, size_t bufSize);

        /**
         * @fn  virtual TResult unloadBuffer(GPUConstBufferPtr buffer);
         * @brief   卸載緩衝區資源
         * @param   buffer  緩衝區資源對象.
         * @returns 調用成功返回 T3D_OK.
         */
        virtual TResult unloadBuffer(GPUConstBufferPtr buffer);

        /**
         * @fn  TResult loadBuiltInResources();
         * @brief   Loads built in constant buffer
         * @returns The built in constant buffer.
         */
        TResult loadBuiltInResources();

    protected:
        /**
         * @brief 构造函数
         */
        GPUConstBufferManager();

        /**
         * @fn  virtual ResourcePtr create(const String &name, 
         *      int32_t argc, va_list args) override;
         * @brief   重写基类接口，实现创建材质对象
         * @param   name    資源名稱.
         * @param   argc    創建需要的參數數量.
         * @param   args    創建需要的參數列表.
         * @returns 調用成功返回新建的資源對象.
         * @sa  ResourcePtr Resource::create(const String &amp;name, 
         *      int32_t argc, va_list args)
         */
        virtual ResourcePtr create(const String &name, int32_t argc, 
            va_list args) override;
    };

    #define T3D_GPU_CONST_BUFFER_MGR    (GPUConstBufferManager::getInstance())
}


#endif  /*__T3D_GPU_CONST_BUFFER_MANAGER_H__*/
