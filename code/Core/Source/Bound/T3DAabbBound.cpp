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


#include "Bound/T3DAabbBound.h"
#include "Component/T3DCube.h"
#include "Scene/T3DSceneNode.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(AabbBound, Bound);

    //--------------------------------------------------------------------------

    AabbBoundPtr AabbBound::create(ID uID /* = E_CID_AUTOMATIC */)
    {
        AabbBoundPtr bound = new AabbBound(uID);
        bound->release();
        return bound;
    }

    //--------------------------------------------------------------------------

    AabbBound::AabbBound(ID uID /* = E_CID_AUTOMATIC */)
        : Bound(uID)
    {

    }

    //--------------------------------------------------------------------------

    AabbBound::~AabbBound()
    {

    }

    //--------------------------------------------------------------------------

    Bound::Type AabbBound::getType() const
    {
        return Type::AABB;
    }

    //--------------------------------------------------------------------------

    ComponentPtr AabbBound::clone() const
    {
        AabbBoundPtr bound = AabbBound::create();
        TResult ret = cloneProperties(bound);

        if (T3D_FAILED(ret))
        {
            bound = nullptr;
        }

        return bound;
    }

    //--------------------------------------------------------------------------

    TResult AabbBound::cloneProperties(ComponentPtr bound) const
    {
        TResult ret = Bound::cloneProperties(bound);

        if (ret == T3D_OK)
        {
            AabbBoundPtr aabbBound = smart_pointer_cast<AabbBound>(bound);
            aabbBound->mAabb = mAabb;
            aabbBound->mOriginalAabb = mOriginalAabb;
            aabbBound->mRenderable
                = smart_pointer_cast<Cube>(mRenderable->clone());
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    void AabbBound::setParams(Real minX, Real maxX, Real minY, Real maxY,
        Real minZ, Real maxZ)
    {
        mOriginalAabb.setParam(Vector3(minX, minY, minZ), 
            Vector3(maxX, maxY, maxZ));
    }

    //--------------------------------------------------------------------------

    RenderablePtr AabbBound::getRenderable()
    {
        return mRenderable;
    }

    //--------------------------------------------------------------------------

    bool AabbBound::testSphere(const Sphere &sphere) const
    {
        IntrSphereAabb intr(&sphere, &mAabb);
        return intr.test();
    }

    //--------------------------------------------------------------------------

    bool AabbBound::testAabb(const Aabb &aabb) const
    {
        IntrAabbAabb intr(&mAabb, &aabb);
        return intr.test();
    }

    //--------------------------------------------------------------------------

    bool AabbBound::testObb(const Obb &obb) const
    {
        IntrAabbObb intr(&mAabb, &obb);
        return intr.test();
    }

    //--------------------------------------------------------------------------

    bool AabbBound::testFrustum(const Frustum &frustum) const
    {
        IntrFrustumAabb intr(&frustum, &mAabb);
        return intr.test();
    }

    //--------------------------------------------------------------------------

    void AabbBound::update()
    {
        // 这里不用传统的变换8个顶点，然后逐个比较获取最大x,y,z来重新设置AABB
        // 这里使用快速变换的方法，减少矩阵变换带来的开销，原理如下：
        // 
        // 碰撞盒8个顶点的任意一点为P，变换后一点为P'，变换矩阵为M，则可得：
        //      P' = M * P
        // 其中
        //      P' = (x' y' z' 1)
        //
        //      P = (x y z 1)
        //
        //          | m00 m01 m02 tx|
        //      M = | m10 m11 m12 ty|
        //          | m20 m21 m22 tz|
        //          | 0   0   0   1 |
        // 则
        //      p'x' = px * m00 + py * m01 + pz * m02 + tx
        //      p'y' = px * m10 + py * m11 + pz * m12 + ty
        //      p'z' = px * m20 + py * m21 + pz * m22 + tz
        // 这里只要计算最大的p'x'、p'y'和p'z'就可以得出最大和最小值了。
        // 如此这样
        //      如 m00 > 0时，则当px = min_x时，则px * m00最小，
        //      如 m00 < 0时，则当px = max_x时，则px * m00最小
        // 同理，可以根据最小值计算方法计算最大值，并且如此类推，计算p'y'和p'z'

        if (mIsDirty)
        {
            Transform3D *xform = getSceneNode()->getTransform3D();
            const Transform &transform = xform->getLocalToWorldTransform();
            const Vector3 &translate = transform.getTranslation();
            const Matrix4 &M = transform.getAffineMatrix();

            Vector3 vMin = translate;
            Vector3 vMax = translate;

            // Calculate min x & max x
            if (M[0][0] > Real(0.0))
            {
                vMin.x() += M[0][0] * mOriginalAabb.getMinX();
                vMax.x() += M[0][0] * mOriginalAabb.getMaxX();
            }
            else
            {
                vMin.x() += M[0][0] * mOriginalAabb.getMaxX();
                vMax.x() += M[0][0] * mOriginalAabb.getMinX();
            }

            if (M[0][1] > Real(0.0))
            {
                vMin.x() += M[0][1] * mOriginalAabb.getMinY();
                vMax.x() += M[0][1] * mOriginalAabb.getMaxY();
            }
            else
            {
                vMin.x() += M[0][1] * mOriginalAabb.getMaxY();
                vMax.x() += M[0][1] * mOriginalAabb.getMinY();
            }

            if (M[0][2] > Real(0.0))
            {
                vMin.x() += M[0][2] * mOriginalAabb.getMinZ();
                vMax.x() += M[0][2] * mOriginalAabb.getMaxZ();
            }
            else
            {
                vMin.x() += M[0][2] * mOriginalAabb.getMaxZ();
                vMax.x() += M[0][2] * mOriginalAabb.getMinZ();
            }

            // Calculate min y & max y
            if (M[1][0] > Real(0.0))
            {
                vMin.y() += M[1][0] * mOriginalAabb.getMinX();
                vMax.y() += M[1][0] * mOriginalAabb.getMaxX();
            }
            else
            {
                vMin.y() += M[1][0] * mOriginalAabb.getMaxX();
                vMax.y() += M[1][0] * mOriginalAabb.getMinX();
            }

            if (M[1][1] > Real(0.0))
            {
                vMin.y() += M[1][1] * mOriginalAabb.getMinY();
                vMax.y() += M[1][1] * mOriginalAabb.getMaxY();
            }
            else
            {
                vMin.y() += M[1][1] * mOriginalAabb.getMaxY();
                vMax.y() += M[1][1] * mOriginalAabb.getMinY();
            }

            if (M[1][2] > Real(0.0))
            {
                vMin.y() += M[1][2] * mOriginalAabb.getMinZ();
                vMax.y() += M[1][2] * mOriginalAabb.getMaxZ();
            }
            else
            {
                vMin.y() += M[1][2] * mOriginalAabb.getMaxZ();
                vMax.y() += M[1][2] * mOriginalAabb.getMinZ();
            }

            // Calculate min z & max z
            if (M[2][0] > Real(0.0))
            {
                vMin.z() += M[2][0] * mOriginalAabb.getMinX();
                vMax.z() += M[2][0] * mOriginalAabb.getMaxX();
            }
            else
            {
                vMin.z() += M[2][0] * mOriginalAabb.getMaxX();
                vMax.z() += M[2][0] * mOriginalAabb.getMinX();
            }

            if (M[2][1] > Real(0.0))
            {
                vMin.z() += M[2][1] * mOriginalAabb.getMinY();
                vMax.z() += M[2][1] * mOriginalAabb.getMaxY();
            }
            else
            {
                vMin.z() += M[2][1] * mOriginalAabb.getMaxY();
                vMax.z() += M[2][1] * mOriginalAabb.getMinY();
            }

            if (M[2][2] > Real(0.0))
            {
                vMin.z() += M[2][2] * mOriginalAabb.getMinZ();
                vMax.z() += M[2][2] * mOriginalAabb.getMaxZ();
            }
            else
            {
                vMin.z() += M[2][2] * mOriginalAabb.getMaxZ();
                vMax.z() += M[2][2] * mOriginalAabb.getMinZ();
            }

            mAabb.setParam(vMin, vMax);

            mIsDirty = false;
        }
    }
}
