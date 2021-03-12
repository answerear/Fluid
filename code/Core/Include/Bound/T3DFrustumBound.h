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


#ifndef __T3D_FRUSTUM_BOUND_H__
#define __T3D_FRUSTUM_BOUND_H__


#include "Bound/T3DBound.h"


namespace Tiny3D
{
    /**
     * @class   FrustumBound
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API FrustumBound : public Bound
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static FrustumBoundPtr FrustumBound::create(SceneNode *node, 
         *      ID uID = E_BID_AUTOMATIC);
         * @brief   创建Frustum碰撞体对象
         * @param [in]  node    : 碰撞体所在的结点对象.
         * @param [in]  uID     (Optional) : 碰撞体ID.
         * @return  返回一个Frustum碰撞体对象.
         */
        static FrustumBoundPtr create(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual FrustumBound::~FrustumBound();
         * @brief   析构函数
         */
        virtual ~FrustumBound();

        /**
         * @fn  virtual Type FrustumBound::getType() const override;
         * @brief   实现基类接口
         * @return  The type.
         * @sa  Bound::Type Bound::getType() const
         */
        virtual Type getType() const override;

        /**
         * @fn  virtual BoundPtr FrustumBound::clone() const override;
         * @brief   实现基类接口
         * @return  A copy of this object.
         * @sa  BoundPtr Bound::clone() const
         */
        virtual ComponentPtr clone() const override;

        /**
         * @fn  const Frustum FrustumBound::&getFrustum() const
         * @brief   获取视锥体包围体对象
         * @return  The frustum.
         */
        const Frustum &getFrustum() const
        {
            return mFrustum;
        }

        /**
         * @fn  void FrustumBound::setFrustumFace(Frustum::Face face, 
         *      const Plane &plane);
         * @brief   设置视锥体面
         * @param   face    The face.
         * @param   plane   The plane.
         */
        void setFrustumFace(Frustum::Face face, const Plane &plane);

        /**
         * @fn  void FrustumBound::setFrustumFaces(Plane *plane, 
         *      size_t planeCount);
         * @brief   设置视锥体所有面
         * @param [in,out]  plane       If non-null, the plane.
         * @param           planeCount  Number of planes.
         */
        void setFrustumFaces(Plane *plane, size_t planeCount);

        /**
         * @fn  virtual RenderablePtr 
         *      FrustumBound::getRenderable() override;
         * @brief   实现基类接口
         * @return  The renderable.
         * @sa  RenderablePtr Bound::getRenderable()
         */
        virtual RenderablePtr getRenderable() override;

        /**
         * @fn  virtual void FrustumBound::updateBound(
         *      const Transform &xform) override;
         * @brief   实现基类接口
         * @param   xform   The transform.
         * @sa  void Bound::updateBound(const Transform &amp;xform)
         */
        virtual void update() override;

    protected:
        /**
         * @fn  FrustumBound::FrustumBound(SceneNode *node, 
         *      ID uID = E_BID_AUTOMATIC);
         * @brief   构造函数
         * @param [in]  node    : 碰撞体所在的结点对象.
         * @param [in]  uID     (Optional) : 碰撞体ID.
         */
        FrustumBound(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual bool FrustumBound::testSphere(
         *      const Sphere &sphere) const override;
         * @brief   实现基类接口
         * @param   sphere  The sphere.
         * @return  True if the test passes, false if the test fails.
         * @sa  bool Bound::testSphere(const Spher &amp;sphere) const
         */
        virtual bool testSphere(const Sphere &sphere) const override;

        /**
         * @fn  virtual bool FrustumBound::testAabb(const Aabb &aabb) 
         *      const override;
         * @brief   实现基类接口
         * @param   aabb    The aabb.
         * @return  True if the test passes, false if the test fails.
         * @sa  bool Bound::testAabb(const Aabb &amp;aabb) const
         */
        virtual bool testAabb(const Aabb &aabb) const override;

        /**
         * @fn  virtual bool FrustumBound::testObb(const Obb &obb) 
         *      const override;
         * @brief   实现基类接口
         * @param   obb The obb.
         * @return  True if the test passes, false if the test fails.
         * @sa  bool Bound::testObb(const Obb &amp;obb) const
         */
        virtual bool testObb(const Obb &obb) const override;

        /**
         * @fn  virtual bool FrustumBound::testFrustum(const Frustum &frustum) 
         *      const override;
         * @brief   实现基类接口
         * @param   frustum The frustum.
         * @return  True if the test passes, false if the test fails.
         * @sa  bool Bound::testFrustum(const Frustum &amp;frustum) const
         */
        virtual bool testFrustum(const Frustum &frustum) const override;

        /**
         * @fn  virtual void FrustumBound::cloneProperties(BoundPtr bound) 
         *      const override;
         * @brief   实现基类接口
         * @param   bound   The bound.
         * @sa  void Bound::cloneProperties(BoundPtr bound) const
         */
        virtual TResult cloneProperties(ComponentPtr newObj) const override;

    protected:
        Frustum     mFrustum;           /**< 可变换的视锥体对象 */
        Frustum     mOriginalFrustum;   /**< 不参与变换的原始视锥体 */
        CubePtr     mRenderable;        /**< 用于渲染碰撞体的可渲染对象 */
    };
}


#endif  /*__T3D_FRUSTUM_BOUND_H__*/
