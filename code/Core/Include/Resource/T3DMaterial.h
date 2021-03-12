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


#ifndef __T3D_MATERIAL_H__
#define __T3D_MATERIAL_H__


#include "Resource/T3DResource.h"
#include "Resource/T3DGPUProgram.h"


namespace Tiny3D
{
    /**
     * @class   Material
     * @brief   材質資源
     */
    class T3D_ENGINE_API Material : public Resource
    {
        T3D_DECLARE_CLASS();

    public:
        typedef TArray<TechniquePtr>            Techniques;
        typedef Techniques::iterator            TechniquesItr;
        typedef Techniques::const_iterator      TechniquesConstItr;

        typedef TMap<String, GPUProgramPtr>     GPUPrograms;
        typedef GPUPrograms::iterator           GPUProgramsItr;
        typedef GPUPrograms::const_iterator     GPUProgramsConstItr;
        typedef GPUPrograms::value_type         GPUProgramsValue;

        typedef TMap<String, GPUConstBufferPtr> GPUConstBuffers;
        typedef GPUConstBuffers::iterator       GPUConstBuffersItr;
        typedef GPUConstBuffers::const_iterator GPUConstBuffersConstITr;
        typedef GPUConstBuffers::value_type     GPUConstBuffersValue;

        /**
         * @enum    MaterialType
         * @brief   材質來源類型
         */
        enum MaterialType
        {
            E_MT_DEFAULT = 0,   /**< 默認是從資源文件加載資源 */
            E_MT_MANUAL,        /**< 由調用者自己創建 */
        };

        /**
         * @fn  static MaterialPtr Material::create(const String &name, 
         *      MaterialType type);
         * @brief   創建 Material 对象
         * @param   name    The name.
         * @param   type    The type.
         * @returns A MaterialPtr.
         */
        static MaterialPtr create(const String &name, MaterialType type);

        /**
         * @fn  virtual Material::~Material();
         * @brief   析構函數
         */
        virtual ~Material();

        /**
         * @fn  virtual Type Material::getType() const override;
         * @brief   重寫 Resource::getType()
         * @returns The type.
         */
        virtual Type getType() const override;

        /**
         * @fn  const String Material::&getMaterialName() const
         * @brief   獲取材質名稱
         * @returns The material name.
         */
        const String &getMaterialName() const { return mMaterialName; }

        /**
         * @fn  void Material::setMaterialName(const String &name)
         * @brief   設置材質名稱
         * @param   name    The name.
         */
        void setMaterialName(const String &name) { mMaterialName = name; }

        /**
         * @fn  TResult Material::addTechnique(const String &name, 
         *      TechniquePtr &tech);
         * @brief   新增一個 Technique 對象到材質中
         * @param       name    The name.
         * @param [in]  tech    : 新創建的 Technique 對象.
         * @returns 創建成功返回 T3D_OK.
         */
        TResult addTechnique(const String &name, TechniquePtr &tech);

        /**
         * @fn  TResult Material::removeTechnique(const String &name);
         * @brief   根據名稱移除一個 Technique 對象
         * @param   name    The name.
         * @returns A TResult.
         */
        TResult removeTechnique(const String &name);

        /**
         * @fn  TResult Material::removeTechnique(size_t index);
         * @brief   根據索引移除一個 Technique 對象
         * @param   index   Zero-based index of the.
         * @returns A TResult.
         */
        TResult removeTechnique(size_t index);

        /**
         * @fn  TechniquePtr Material::getTechnique(const String &name) const;
         * @brief   根據名稱獲取 Technique 對象
         * @param   name    The name.
         * @returns The technique.
         */
        TechniquePtr getTechnique(const String &name) const;

        /**
         * @fn  TechniquePtr Material::getTechnique(size_t index) const;
         * @brief   根據索引獲取 Technique 對象
         * @param   index   Zero-based index of the.
         * @returns The technique.
         */
        TechniquePtr getTechnique(size_t index) const;

        /**
         * @fn  size_t Material::getTechniqueCount() const
         * @brief   獲取材質中 Technique 對象數量
         * @returns The technique count.
         */
        size_t getTechniqueCount() const { return mTechniques.size(); }

        /**
         * @fn  const Techniques Material::&getTechniques() const
         * @brief   獲取所有 Technique 對象
         * @returns The techniques.
         */
        const Techniques &getTechniques() const { return mTechniques; }

        /**
         * @fn  TechniquePtr Material::getBestTechnique()
         * @brief   获取最合适的 Technique 对象
         * @return  The best technique.
         */
        TechniquePtr getBestTechnique() { return mSupportedTechniques[0]; }

        /**
         * @fn  TResult Material::addGPUProgram(const String &name, 
         *      GPUProgramPtr &program);
         * @brief   新增一個 GPUProgram 對象到材質中
         * @param           name    The name.
         * @param [in,out]  program The program.
         * @returns A TResult.
         */
        TResult addGPUProgram(const String &name, GPUProgramPtr &program);

        /**
         * @fn  TResult Material::removeGPUProgram(const String &name);
         * @brief   根據名稱移除一個 GPUProgram 對象
         * @param   name    The name.
         * @returns A TResult.
         */
        TResult removeGPUProgram(const String &name);

        /**
         * @fn  GPUProgramPtr Material::getGPUProgram(const String &name) const;
         * @brief   根據名稱獲取 GPUProgram 對象
         * @param   name    The name.
         * @returns The GPU program.
         */
        GPUProgramPtr getGPUProgram(const String &name) const;

        /**
         * @fn  size_t Material::getGPUProgramCount() const
         * @brief   獲取材質中 GPUProgram 對象數量
         * @returns The GPU program count.
         */
        size_t getGPUProgramCount() const { return mGPUPrograms.size(); }

        /**
         * @fn  const GPUPrograms Material::getGPUPrograms() const
         * @brief   獲取所有 GPUProgram 對象
         * @returns The GPU programs.
         */
        const GPUPrograms getGPUPrograms() const { return mGPUPrograms; }

        /**
         * @fn  TResult Material::addGPUConstBuffer(const String &name, 
         *      GPUConstBufferPtr &buffer);
         * @brief   Adds a GPU constant buffer to 'buffer'
         * @param   name    The name.
         * @param   buffer  The buffer.
         * @returns A TResult.
         */
        TResult addGPUConstBuffer(
            const String &name, GPUConstBufferPtr &buffer, size_t bufSize);

        /**
         * @fn  TResult Material::removeGPUConstBuffer(const String &name);
         * @brief   Removes the GPU constant buffer described by name
         * @param   name    The name.
         * @returns A TResult.
         */
        TResult removeGPUConstBuffer(const String &name);

        /**
         * @fn  GPUConstBufferPtr 
         *      Material::getGPUConstBuffer(const String &name) const;
         * @brief   Gets GPU constant buffer
         * @param   name    The name.
         * @returns The GPU constant buffer.
         */
        GPUConstBufferPtr getGPUConstBuffer(const String &name) const;

        /**
         * @fn  size_t Material::getGPUConstBufferCount() const
         * @brief   Gets GPU constant buffer count
         * @returns The GPU constant buffer count.
         */
        size_t getGPUConstBufferCount() const { return mConstBuffers.size(); }

        /**
         * @fn  const GPUConstBuffers Material::getGPUConstBuffers() const
         * @brief   Gets GPU constant buffers
         * @returns The GPU constant buffers.
         */
        const GPUConstBuffers getGPUConstBuffers() const 
        { 
            return mConstBuffers; 
        }

    protected:
        /**
         * @fn  Material::Material(const String &name, MaterialType type);
         * @brief   構造函數
         * @param [in]  name    材质资源名称.
         * @param [in]  type    材质资源来源类型.
         */
        Material(const String &name, MaterialType type);

        /**
         * @fn  virtual TResult Material::load() override;
         * @brief   重寫 Resource::load()
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult load() override;

        /**
         * @fn  virtual TResult Material::unload() override;
         * @brief   重寫 Resource::unlaod()
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult unload() override;

        /**
         * @fn  virtual ResourcePtr Material::clone() const override;
         * @brief   重寫 Resource::clone()
         * @returns 调用成功返回一个新的材质对象.
         */
        virtual ResourcePtr clone() const override;

        /**
         * @fn  TResult Material::compile();
         * @brief   编译材质脚本
         * @return  调用成功返回 T3D_OK.
         */
        TResult compile();

    protected:
        MaterialType    mMaterialType;  /**< 材質資源類型 */
        String          mMaterialName;  /**< 材質名稱 */

        Techniques      mTechniques;            /**< 材質中所有的 Technique 對象 */
        Techniques      mSupportedTechniques;   /**< 材质中支持的 Technique 对象 */
        GPUPrograms     mGPUPrograms;           /**< 材質擁有的 GPUProgram 對象*/
        GPUConstBuffers mConstBuffers;          /**< The constant buffers */

        bool            mHasCompiled;   /**< 材质编译标识 */
    };
}


#endif  /*__T3D_MATERIAL_H__*/
