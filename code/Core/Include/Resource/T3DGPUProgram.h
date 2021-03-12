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


#ifndef __T3D_GPU_PROGRAM_H__
#define __T3D_GPU_PROGRAM_H__


#include "T3DResource.h"


namespace Tiny3D
{
    /**
     * @class   GPUConstBufferRef
     * @brief   GPU 常量緩衝區引用類.
     */
    class T3D_ENGINE_API GPUConstBufferRef : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static GPUConstBufferRefPtr GPUConstBufferRef::create(
         *      const String &name, uint32_t slot);
         * @brief   Creates a new GPUConstBufferRefPtr
         * @param   name    The name.
         * @param   slot    The slot.
         * @returns A GPUConstBufferRefPtr.
         */
        static GPUConstBufferRefPtr create(const String &name, uint32_t slot);

        /**
         * @fn  virtual GPUConstBufferRef::~GPUConstBufferRef();
         * @brief   Destructor
         */
        virtual ~GPUConstBufferRef();

        /**
         * @fn  const String& GPUConstBufferRef::getName() const
         * @brief   Gets the name
         * @returns The name.
         */
        const String& getName() const { return mName; }

        /**
         * @fn  uint32_t GPUConstBufferRef::getSlot() const
         * @brief   Gets the slot
         * @returns The slot.
         */
        uint32_t getSlot() const { return mSlot; }

    protected:
        /**
         * @fn  GPUConstBufferRef::GPUConstBufferRef(const String &name, 
         *      uint32_t slot);
         * @brief   Default constructor
         * @param   name    The name.
         * @param   slot    The slot.
         */
        GPUConstBufferRef(const String &name, uint32_t slot);

    protected:
        String      mName;  /**< The name */
        uint32_t    mSlot;  /**< The slot */
    };

    /**
     * @class   GPUProgramRef
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API GPUProgramRef : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        typedef TArray<GPUConstBufferRefPtr>    BufferRefList;
        typedef BufferRefList::iterator         BufferRefListItr;
        typedef BufferRefList::const_iterator   BufferRefListConstItr;

        /**
         * @fn  static GPUProgramRefPtr GPUProgramRef::create();
         * @brief   Creates a new GPUProgramRefPtr
         * @returns A GPUProgramRefPtr.
         */
        static GPUProgramRefPtr create(const String &name);

        /**
         * @fn  virtual GPUProgramRef::~GPUProgramRef();
         * @brief   Destructor
         */
        virtual ~GPUProgramRef();

        /**
         * @fn  const String GPUProgramRef::&getName() const
         * @brief   Gets the name
         * @returns The name.
         */
        const String &getName() const { return mName; }

        /**
         * @fn  TResult GPUProgramRef::addConstBufferRef(const String& name, 
         *      uint32_t slot, GPUConstBufferRefPtr& buffer);
         * @brief   Adds a constant buffer reference
         * @param   name    The name.
         * @param   slot    The slot.
         * @param   buffer  The buffer.
         * @returns A TResult.
         */
        TResult addConstBufferRef(const String& name, uint32_t slot,
            GPUConstBufferRefPtr &buffer);

        /**
         * @fn  TResult GPUProgramRef::removeConstBufferRef(const String& name);
         * @brief   Removes the constant buffer reference described by name
         * @param   name    The name.
         * @returns A TResult.
         */
        TResult removeConstBufferRef(const String& name);

        /**
         * @fn  BufferRefList GPUProgramRef::getBufferRefList() const
         * @brief   Gets buffer reference list
         * @returns The buffer reference list.
         */
        BufferRefList getBufferRefList() const { return mBuffers; }

        /**
         * @fn  GPUConstBufferRefPtr GPUProgramRef::getBufferRef(uint32_t slot);
         * @brief   Gets buffer reference
         * @param   slot    The slot.
         * @returns The buffer reference.
         */
        GPUConstBufferRefPtr getBufferRef(uint32_t slot) const;

        /**
         * @fn  GPUConstBufferRefPtr GPUProgramRef::getBufferRef(
         *      const String& name);
         * @brief   Gets buffer reference
         * @param   name    The name.
         * @returns The buffer reference.
         */
        GPUConstBufferRefPtr getBufferRef(const String& name) const;

        /**
         * @fn  size_t GPUProgramRef::getBufferRefCount() const;
         * @brief   Gets buffer reference count
         * @returns The buffer reference count.
         */
        size_t getBufferRefCount() const { return mBuffers.size(); }

    protected:
        /**
         * @fn  GPUProgramRef::GPUProgramRef();
         * @brief   Default constructor
         */
        GPUProgramRef(const String &name);

    protected:
        String          mName;      /**< The name */
        BufferRefList   mBuffers;   /**< The buffers */
    };

    /**
     * @class   Shader
     * @brief   着色器程序
     */
    class T3D_ENGINE_API Shader : public Resource
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @enum    ShaderType
         * @brief   着色器类型
         */
        enum ShaderType : uint32_t
        {
            VERTEX_SHADER = 0,  /**< 顶点着色器 */
            HULL_SHADER,        /**< 曲面细分控制着色器 */
            DOMAIN_SHADER,      /**< 曲面细分计算着色器 */
            GEOMETRY_SHADER,    /**< 几何着色器 */
            PIXEL_SHADER,       /**< 像素着色器 */
            COMPUTE_SHADER,     /**< 计算着色器 */
            MAX_SHADERS,
        };

        /**
         * @fn  virtual Type Shader::getType() const override;
         * @brief   获取资源类型，重写基类 Resource::getType() 接口
         * @returns The type.
         */
        virtual Type getType() const override;

        /**
         * @fn  virtual ShaderType Shader::getShaderType() const = 0;
         * @brief   获取着色器类型
         * @returns The shader type.
         */
        virtual ShaderType getShaderType() const = 0;

        /**
         * @fn  virtual TResult Shader::compile() = 0;
         * @brief   编译着色器程序
         * @param [in]  force : 是否强制重新编译，默认强制
         * @returns 编译成功返回 T3D_OK.
         */
        virtual TResult compile(bool force = false) = 0;

        /**
         * @fn  virtual bool Shader::hasCompiled() const = 0;
         * @brief   是否已经编译过
         * @returns True if compiled, false if not.
         */
        virtual bool hasCompiled() const = 0;

    protected:
        /**
         * @fn  Shader::Shader(const String &name);
         * @brief   构造函数
         * @param   name    The name.
         */
        Shader(const String &name);
    };

    /**
     * @brief GPU程序
     */
    class T3D_ENGINE_API GPUProgram : public Resource
    {
        T3D_DECLARE_CLASS();

    public:
        typedef TArray<ShaderPtr>           Shaders;
        typedef Shaders::iterator           ShadersItr;
        typedef Shaders::const_iterator     ShadersConstItr;
        typedef Shaders::value_type         ShadersValue;

        /**
         * @fn  virtual Type GPUProgram::getType() const override;
         * @brief   獲取資源類型，重寫基類 Resource::getType() 接口
         * @returns The type.
         */
        virtual Type getType() const override;

        /**
         * @brief   编译所有着色器程序
         * @param [in]  force   : 是否强制重新编译所有着色器程序
         * @returns 调用成功返回 T3D_OK.
         */
        TResult compile(bool force = false);

        /**
         * @fn  virtual TResult GPUProgram::link(bool force = false) = 0;
         * @brief   把所有著色器程序鏈接成一個 GPU 程序
         * @param [in]  force   (Optional) : 是否強制重新鏈接.
         * @returns 調用成功返回 true.
         */
        virtual TResult link(bool force = false) = 0;

        /**
         * @brief 是否鏈接成GPU程序
         */
        virtual bool hasLinked() const = 0;

        /**
         * @fn  TResult GPUProgram::addShader(const String &name, 
         *      Shader::ShaderType type, ShaderPtr &shader);
         * @brief   新增 shader
         * @param [in]  name    : Shader 名稱.
         * @param [in]  type    : Shader 類型.
         * @param [in]  shader  shader : 返回新增的 Shader 對象.
         * @returns 調用成功返回 T3D_OK.
         */
        TResult addShader(
            const String &name, Shader::ShaderType type, ShaderPtr &shader);

        /**
         * @fn  TResult GPUProgram::removeShader(const String &name);
         * @brief   根據名稱移除 shader
         * @param   name    The name.
         * @returns A TResult.
         */
        TResult removeShader(const String &name);

        /**
         * @fn  TResult GPUProgram::removeShader(Shader::ShaderType type);
         * @brief   根據類型移除 shader
         * @param   type    The type.
         * @returns A TResult.
         */
        TResult removeShader(Shader::ShaderType type);

        /**
         * @fn  ShaderPtr GPUProgram::getVertexShader() const;
         * @brief   获取頂點著色器對象
         * @returns The vertex shader.
         */
        ShaderPtr getVertexShader() const;

        /**
         * @fn  ShaderPtr GPUProgram::getPixelShader() const;
         * @brief   获取片段著色器對象
         * @returns The pixel shader.
         */
        ShaderPtr getPixelShader() const;

        /**
         * @brief   获取几何着色器对象
         */
        ShaderPtr getGeometryShader() const;

        /**
         * @brief   获取曲面细分控制着色器对象
         */
        ShaderPtr getHullShader() const;

        /**
         * @brief   获取曲面细分计算着色器对象
         */
        ShaderPtr getDomainShader() const;

        /**
         * @brief   获取计算着色器对象
         */
        ShaderPtr getComputeShader() const;

    protected:
        /**
         * @fn  GPUProgram::GPUProgram(const String &name);
         * @brief   構造函數
         * @param   name    The name.
         */
        GPUProgram(const String &name);

        /**
         * @fn  virtual TResult GPUProgram::cloneProperties(
         *      GPUProgramPtr newObj) const;
         * @brief   克隆属性
         * @param   newObj  The new object.
         * @returns A TResult.
         */
        virtual TResult cloneProperties(GPUProgramPtr newObj) const;

    protected:
        Shaders mShaders;   /**< 所有的著色器程序 */
    };
}


#include "T3DGPUProgram.inl"


#endif  /*__T3D_GPU_PROGRAM_H__*/
