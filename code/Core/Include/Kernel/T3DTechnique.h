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


#ifndef __T3D_TECHNIQUE_H__
#define __T3D_TECHNIQUE_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "T3DObject.h"

namespace Tiny3D
{
    /**
     * @class   Technique
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API Technique : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        typedef TArray<PassPtr>                 Passes;
        typedef Passes::iterator                PassesItr;
        typedef Passes::const_iterator          PassesConstItr;

        /**
         * @fn  static TechniquePtr Technique::create(const String &name, 
         *      Material *material);
         * @brief   創建 Technique 對象
         * @param           name        The name.
         * @param [in,out]  material    If non-null, the material.
         * @return  A TechniquePtr.
         */
        static TechniquePtr create(const String &name, Material *material);

        /**
         * @fn  virtual Technique::~Technique();
         * @brief   析構函數
         */
        virtual ~Technique();

        /**
         * @fn  TResult Technique::compile();
         * @brief   编译
         * @return  调用成功返回 T3D_OK.
         */
        TResult compile();

        /**
         * @fn  const String Technique::&getName() const;
         * @brief   獲取 Technique 的名稱
         * @return  The name.
         */
        const String &getName() const;

        uint32_t getRenderQueue() const;

        void setRenderQueue(uint32_t queue);

        /**
         * @fn  Material Technique::*getMaterial() const;
         * @brief   獲取擁有該 Technique 對象的材質對象
         * @return  Null if it fails, else the material.
         */
        Material *getMaterial() const;

        /**
         * @fn  TResult Technique::addPass(const String &name, PassPtr &pass);
         * @brief   新增一個 Pass 對象
         * @param [in]  name    : 新增的 Pass 對象名稱.
         * @param [in]  pass    pass : 返回新增的 Pass 對象.
         * @return  調用成功返回 T3D_OK.
         */
        TResult addPass(const String &name, PassPtr &pass);

        /**
         * @fn  TResult Technique::removePass(const String &name);
         * @brief   移除指定名稱的 Pass 對象
         * @param [in]  name    : Pass 對象名稱.
         * @return  調用成功返回 T3D_OK.
         */
        TResult removePass(const String &name);

        /**
         * @fn  TResult Technique::removePass(size_t index);
         * @brief   移除指定索引的 Pass 對象
         * @param [in]  index   : 索引.
         * @return  調用成功返回 T3D_OK.
         */
        TResult removePass(size_t index);

        /**
         * @fn  PassPtr Technique::getPass(const String &name) const;
         * @brief   獲取指定名稱的 Pass 對象
         * @param [in]  name    : Pass 名稱.
         * @return  調用成功返回 Pass 對象，否則返回 nullptr.
         */
        PassPtr getPass(const String &name) const;

        /**
         * @fn  PassPtr Technique::getPass(size_t index) const;
         * @brief   獲取指定索引的 Pass 對象
         * @param [in]  index   : Pass 對象所在索引.
         * @return  調用成功返回 Pass 對象，否則返回 nullptr.
         */
        PassPtr getPass(size_t index) const;

        /**
         * @fn  const Passes Technique::&getPasses() const;
         * @brief   獲取所有 Pass 對象
         * @return  The passes.
         */
        const Passes &getPasses() const;

        /**
         * @fn  size_t Technique::getPassCount() const;
         * @brief   獲取 Pass 對象數量
         * @return  The pass count.
         */
        size_t getPassCount() const;

    protected:
        /**
         * @fn  Technique::Technique(const String &name, Material *material);
         * @brief   構造函數
         * @param           name        The name.
         * @param [in,out]  material    If non-null, the material.
         */
        Technique(const String &name, Material *material);

    protected:
        Material    *mParent;   /**< The parent */
        String      mName;      /**< The name */
        Passes      mPasses;    /**< The passes */

        //---------------------------------------
        // Command : lod_index
        // Usage : lod_index <number>
        uint16_t    mLodIndex;      /**< Zero-based index of the LOD */

        uint16_t    mSchemeIndex;   /**< Zero-based index of the scheme */

        uint32_t    mRenderQueue;   /**< index of render queue */
        bool        mIsSupported;   /**< GPU 是否支持本 Technique */
    };
}


#include "T3DTechnique.inl"


#endif  /*__T3D_TECHNIQUE_H__*/
