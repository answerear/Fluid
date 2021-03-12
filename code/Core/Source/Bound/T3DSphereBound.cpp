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


#include "Bound/T3DSphereBound.h"
#include "Component/T3DGlobe.h"
#include "Scene/T3DSceneNode.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(SphereBound, Bound);

    //--------------------------------------------------------------------------

    SphereBoundPtr SphereBound::create(ID uID /* = E_CID_AUTOMATIC */)
    {
        SphereBoundPtr bound = new SphereBound(uID);
        bound->release();
        return bound;
    }

    //--------------------------------------------------------------------------

    SphereBound::SphereBound(ID uID /* = E_CID_AUTOMATIC */)
        : Bound(uID)
        , mRenderable(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    SphereBound::~SphereBound()
    {
        mRenderable = nullptr;
    }

    //--------------------------------------------------------------------------

    Bound::Type SphereBound::getType() const
    {
        return Type::SPHERE;
    }

    //--------------------------------------------------------------------------

    ComponentPtr SphereBound::clone() const
    {
        SphereBoundPtr bound = SphereBound::create();
        TResult ret = cloneProperties(bound);

        if (T3D_FAILED(ret))
        {
            bound = nullptr;
        }

        return bound;
    }

    //--------------------------------------------------------------------------

    TResult SphereBound::cloneProperties(ComponentPtr newObj) const
    {
        TResult ret = Bound::cloneProperties(newObj);

        if (ret == T3D_OK)
        {
            SphereBoundPtr sphereBound = smart_pointer_cast<SphereBound>(newObj);
            sphereBound->mOriginalSphere = mOriginalSphere;
            sphereBound->mSphere = mSphere;
            sphereBound->mRenderable
                = smart_pointer_cast<Globe>(mRenderable->clone());
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    void SphereBound::setParams(const Vector3 &center, Real radius)
    {
        mOriginalSphere.setCenter(center);
        mOriginalSphere.setRadius(radius);

        mSphere.setCenter(center);
        mSphere.setRadius(radius);
    }

    //--------------------------------------------------------------------------

    RenderablePtr SphereBound::getRenderable()
    {
        return mRenderable;
    }

    //--------------------------------------------------------------------------

    bool SphereBound::testSphere(const Sphere &sphere) const
    {
        IntrSphereSphere intr(&mSphere, &sphere);
        return intr.test();
    }

    //--------------------------------------------------------------------------

    bool SphereBound::testAabb(const Aabb &aabb) const
    {
        IntrSphereAabb intr(&mSphere, &aabb);
        return intr.test();
    }

    //--------------------------------------------------------------------------

    bool SphereBound::testObb(const Obb &obb) const
    {
        IntrSphereObb intr(&mSphere, &obb);
        return intr.test();
    }

    //--------------------------------------------------------------------------

    bool SphereBound::testFrustum(const Frustum &frustum) const
    {
        IntrFrustumSphere intr(&frustum, &mSphere);
        return intr.test();
    }

    //--------------------------------------------------------------------------

    void SphereBound::update()
    {
        if (mIsDirty)
        {
            Transform3D *transform = getSceneNode()->getTransform3D();
            const Transform &xform = transform->getLocalToWorldTransform();

            // 更新变换后用于碰撞检测的球体
            const Matrix4 &M = xform.getAffineMatrix();
            Vector3 center = M * mOriginalSphere.getCenter();

            const Vector3 &S = xform.getScaling();
            Real factor = std::max(std::max(S.x(), S.y()), S.z());
            Real radius = factor * mOriginalSphere.getRadius();

            mSphere.setCenter(center);
            mSphere.setRadius(radius);

            // 原始球体，只更新球心位置，不更新半径大小
            center = M * mOriginalSphere.getCenter();
            mOriginalSphere.setCenter(center);

            mIsDirty = false;
        }
    }
}
