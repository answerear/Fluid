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


#ifndef __T3D_AABB_BOUND_H__
#define __T3D_AABB_BOUND_H__


#include "Bound/T3DBound.h"


namespace Tiny3D
{
    /**
     * @class   AabbBound
     * @brief   轴对齐碰撞体
     */
    class T3D_ENGINE_API AabbBound : public Bound
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static AabbBoundPtr AabbBound::create(SceneNode *node, 
         *      ID uID = E_BID_AUTOMATIC);
         * @brief   创建AABB碰撞体对象
         * @param [in]  node    : 碰撞体所在的结点对象.
         * @param [in]  uID     (Optional) : 碰撞体ID.
         * @return  返回一个AABB碰撞体对象.
         */
        static AabbBoundPtr create(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual AabbBound::~AabbBound();
         * @brief   析构函数
         */
        virtual ~AabbBound();

        /**
         * @fn  virtual Type AabbBound::getType() const override;
         * @brief   实现基类接口
         * @return  The type.
         * @sa  Bound::Type Bound::getType() const
         */
        virtual Type getType() const override;

        /**
         * @fn  virtual BoundPtr AabbBound::clone() const override;
         * @brief   实现基类接口
         * @return  A copy of this object.
         * @sa  BoundPtr Bound::clone() const
         */
        virtual ComponentPtr clone() const override;

        /**
         * @fn  const Aabb AabbBound::&getAlignAxisBox() const
         * @brief   获取轴对齐包围盒对象
         * @return  The align axis box.
         */
        const Aabb &getAlignAxisBox() const 
        { 
            return mAabb; 
        }

        /**
         * @fn  void AabbBound::setParams(Real minX, Real maxX, Real minY, 
         *      Real maxY, Real minZ, Real maxZ);
         * @brief   设置包围体需要的一些参数
         * @param   minX    The minimum x coordinate.
         * @param   maxX    The maximum x coordinate.
         * @param   minY    The minimum y coordinate.
         * @param   maxY    The maximum y coordinate.
         * @param   minZ    The minimum z coordinate.
         * @param   maxZ    The maximum z coordinate.
         */
        void setParams(Real minX, Real maxX, Real minY, Real maxY, 
            Real minZ, Real maxZ);

        /**
         * @fn  virtual RenderablePtr AabbBound::getRenderable() override;
         * @brief   实现基类接口
         * @return  The renderable.
         * @sa  RenderablePtr Bound::getRenderable()
         */
        virtual RenderablePtr getRenderable() override;

        virtual void update() override;

    protected:
        /**
         * @fn  AabbBound::AabbBound(SceneNode *node, ID uID = E_BID_AUTOMATIC);
         * @brief   构造函数
         * @param [in]  node    : 碰撞体所在的结点对象.
         * @param [in]  uID     (Optional) : 碰撞体ID.
         */
        AabbBound(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual bool AabbBound::testSphere(
         *      const Sphere &sphere) const override;
         * @brief   实现基类接口
         * @param   sphere  The sphere.
         * @return  True if the test passes, false if the test fails.
         * @sa  bool Bound::testSphere(const Spher &amp;sphere) const
         */
        virtual bool testSphere(const Sphere &sphere) const override;

        /**
         * @fn  virtual bool AabbBound::testAabb(
         *      const Aabb &aabb) const override;
         * @brief   实现基类接口
         * @param   aabb    The aabb.
         * @return  True if the test passes, false if the test fails.
         * @sa  bool Bound::testAabb(const Aabb &amp;aabb) const
         */
        virtual bool testAabb(const Aabb &aabb) const override;

        /**
         * @fn  virtual bool AabbBound::testObb(const Obb &obb) const override;
         * @brief   实现基类接口
         * @param   obb The obb.
         * @return  True if the test passes, false if the test fails.
         * @sa  bool Bound::testObb(const Obb &amp;obb) const
         */
        virtual bool testObb(const Obb &obb) const override;

        /**
         * @fn  virtual bool AabbBound::testFrustum(const Frustum &frustum) const override;
         * @brief   实现基类接口
         * @param   frustum The frustum.
         * @return  True if the test passes, false if the test fails.
         * @sa  bool Bound::testFrustum(const Frustum &amp;frustum) const
         */
        virtual bool testFrustum(const Frustum &frustum) const override;

        /**
         * @fn  virtual void AabbBound::cloneProperties(BoundPtr bound) const override;
         * @brief   实现基类接口
         * @param   bound   The bound.
         * @sa  void Bound::cloneProperties(BoundPtr bound) const
         */
        virtual TResult cloneProperties(ComponentPtr newObj) const override;

    protected:
        Aabb        mAabb;          /**< 实时变换的AABB */
        Aabb        mOriginalAabb;  /**< 不参与变换的原始AABB */
        CubePtr     mRenderable;    /**< 用于渲染碰撞体的可渲染对象 */
    };
}

#endif  /*__T3D_AABB_BOUND_H__*/
