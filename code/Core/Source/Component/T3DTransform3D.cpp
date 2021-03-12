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


#include "Component/T3DTransform3D.h"
#include "Scene/T3DSceneNode.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_0(ITransformListener);

    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Transform3D, Component);

    //--------------------------------------------------------------------------

    Transform3DPtr Transform3D::create(ID uID /* = E_CID_AUTOMATIC */)
    {
        Transform3DPtr node = new Transform3D(uID);
        node->release();
        return node;
    }

    //--------------------------------------------------------------------------

    Transform3D::Transform3D(ID uID /* = E_CID_AUTOMATIC */)
        : Component(uID)
        , mPosition(Vector3::ZERO)
        , mOrientation(Quaternion::IDENTITY)
        , mScaling(Vector3::UNIT_SCALE)
        , mIsDirty(false)
    {
        mWorldTransform.setTranslation(mPosition);
        mWorldTransform.setOrientation(mOrientation);
        mWorldTransform.setScaling(mScaling);
    }

    //--------------------------------------------------------------------------

    Transform3D::~Transform3D()
    {

    }

    //--------------------------------------------------------------------------

    void Transform3D::setLocalMatrix(const Matrix4 &m)
    {
        m.decomposition(mPosition, mScaling, mOrientation);
        setDirty(true, true);
    }

    //--------------------------------------------------------------------------

    const Transform &Transform3D::getLocalToWorldTransform() const
    {
        if (isDirty())
        {
            SceneNodePtr node 
                = smart_pointer_cast<SceneNode>(getSceneNode()->getParent());

            while (node != nullptr)
            {
                node = node->getParent();
            }

            if (node != nullptr)
            {
                Transform3DPtr xform = node->getTransform3D();
                const Transform &transform = xform->getLocalToWorldTransform();
                mWorldTransform.applyTransform(transform, mPosition, 
                    mOrientation, mScaling);
            }
            else
            {
                mWorldTransform.setTranslation(mPosition);
                mWorldTransform.setOrientation(mOrientation);
                mWorldTransform.setScaling(mScaling);
                mWorldTransform.update();
            }

            mIsDirty = false;

            notifyListener();
        }

        return mWorldTransform;
    }

    //--------------------------------------------------------------------------

    void Transform3D::addListener(ITransformListener *listener)
    {
        mListeners.push_back(listener);
    }

    //--------------------------------------------------------------------------

    void Transform3D::removeListner(ITransformListener *listener)
    {
        auto itr = std::find(mListeners.begin(), mListeners.end(), listener);

        if (itr != mListeners.end())
        {
            mListeners.erase(itr);
        }
    }

    //--------------------------------------------------------------------------

    void Transform3D::notifyListener() const
    {
        auto itr = mListeners.begin();

        while (itr != mListeners.end())
        {
            ITransformListener *listener = *itr;
            listener->updateTransform(this);
            ++itr;
        }
    }

    //--------------------------------------------------------------------------

    void Transform3D::setDirty(bool isDirty, bool recursive /* = false */)
    {
        if (mIsDirty != isDirty)
        {
            mIsDirty = isDirty;

            if (recursive)
            {
                SceneNode *node = getSceneNode();
                NodePtr child = node->getFirstChild();
                while (child != nullptr)
                {
                    SceneNodePtr node = smart_pointer_cast<SceneNode>(child);
                    Transform3DPtr xform = node->getTransform3D();
                    xform->setDirty(isDirty, recursive);
                    child = child->getNextSibling();
                }
            }
        }
    }

    //--------------------------------------------------------------------------

    ComponentPtr Transform3D::clone() const
    {
        Transform3DPtr newObj = create();
        if (cloneProperties(newObj) != T3D_OK)
        {
            newObj = nullptr;
        }
        return newObj;
    }
    //--------------------------------------------------------------------------

    void Transform3D::onAttachSceneNode(SceneNode *node)
    {
        Component::onAttachSceneNode(node);

        setDirty(true, true);
    }

    //--------------------------------------------------------------------------

    void Transform3D::onDetachSceneNode(SceneNode *node)
    {
        Component::onDetachSceneNode(node);
    }

    //--------------------------------------------------------------------------

    void Transform3D::update()
    {
        getLocalToWorldTransform();
    }

    //--------------------------------------------------------------------------

    TResult Transform3D::cloneProperties(ComponentPtr newObj) const
    {
        TResult ret = Component::cloneProperties(newObj);

        if (ret == T3D_OK)
        {
            Transform3DPtr obj = smart_pointer_cast<Transform3D>(newObj);
            obj->mPosition = mPosition;
            obj->mOrientation = mOrientation;
            obj->mScaling = mScaling;
            obj->mWorldTransform = mWorldTransform;
            obj->mIsDirty = mIsDirty;
        }

        return ret;
    }
}
