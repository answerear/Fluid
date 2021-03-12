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


#include "Kernel/T3DNode.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Node, Object);

    //--------------------------------------------------------------------------

    Node::Node(ID uID /* = E_NID_AUTOMATIC */)
        : mID(E_NID_INVALID)
        , mName()
        , mChildrenCount(0)
        , mParent(nullptr)
        , mFirstChild(nullptr)
        , mLastChild(nullptr)
        , mPrevSibling(nullptr)
        , mNextSibling(nullptr)
    {
        if (E_NID_AUTOMATIC == uID)
        {
            mID = makeGlobalID();
        }
        else
        {
            mID = uID;
        }
    }

    Node::~Node()
    {
        removeAllChildren();
    }

    //--------------------------------------------------------------------------

    TResult Node::addChild(NodePtr node)
    {
        T3D_ASSERT(node->getParent() == nullptr);
        
        if (mFirstChild == nullptr)
        {
            // 没有子结点
            mLastChild = mFirstChild = node;
        }
        else
        {
            // 有子结点，直接插入子结点链表末尾
            node->mPrevSibling = mLastChild;
            node->mNextSibling = nullptr;
            mLastChild->mNextSibling = node;
            mLastChild = node;
        }

        node->mParent = this;
        mChildrenCount++;
        node->onAttachParent(this);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult Node::removeChild(NodePtr node)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (node == nullptr)
            {
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Invalid node pointer !");
                ret = T3D_ERR_INVALID_POINTER;
                break;
            }

            Node *child = mFirstChild;

            while (child != nullptr)
            {
                if (child == node)
                {
                    // 找到要删除的，先断开链表前后关系
                    child->onDetachParent(this);
                    child->mParent = nullptr;
                    mChildrenCount--;

                    if (child->mPrevSibling != nullptr)
                        child->mPrevSibling->mNextSibling = child->mNextSibling;
                    if (child->mNextSibling != nullptr)
                        child->mNextSibling->mPrevSibling = child->mPrevSibling;

                    break;
                }

                child = child->mNextSibling;
            }

            if (mChildrenCount == 0)
            {
                mFirstChild = nullptr;
                mLastChild = nullptr;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Node::removeChild(uint32_t nodeID)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (nodeID == E_NID_INVALID)
            {
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Invalid node ID !");
                ret = T3D_ERR_INVALID_ID;
                break;
            }

            Node *child = mFirstChild;

            while (child != nullptr)
            {
                if (child->getNodeID() == nodeID)
                {
                    // 找到要删除的，先断开链表前后关系
                    child->onDetachParent(this);
                    child->mParent = nullptr;
                    mChildrenCount--;

                    if (child->mPrevSibling != nullptr)
                        child->mPrevSibling->mNextSibling = child->mNextSibling;
                    if (child->mNextSibling != nullptr)
                        child->mNextSibling->mPrevSibling = child->mPrevSibling;

                    break;
                }

                child = child->mNextSibling;
            }

            if (mChildrenCount == 0)
            {
                mFirstChild = nullptr;
                mLastChild = nullptr;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Node::removeAllChildren()
    {
        TResult ret = T3D_OK;

        Node *child = mFirstChild;

        while (child != nullptr)
        {
            child->onDetachParent(this);
            child->mParent = nullptr;
            if (child->mPrevSibling != nullptr)
                child->mPrevSibling->mNextSibling = nullptr;
            child->mPrevSibling = nullptr;
            if (child->mNextSibling != nullptr)
                child->mNextSibling->mPrevSibling = nullptr;
            child = child->mNextSibling;
        }

        mFirstChild = mLastChild = nullptr;
        mChildrenCount = 0;

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Node::removeFromParent()
    {
        TResult ret = T3D_OK;

        if (mParent != nullptr)
        {
            mParent->removeChild(this);
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    NodePtr Node::getChild(ID nodeID) const
    {
        Node *child = nullptr;
        Node *temp = mFirstChild;

        while (temp != nullptr)
        {
            if (temp->getNodeID() == nodeID)
            {
                child = temp;
                break;
            }

            temp = temp->mNextSibling;
        }

        return child;
    }

    //--------------------------------------------------------------------------

    NodePtr Node::getChild(const String &name) const
    {
        Node *child = nullptr;
        Node *temp = mFirstChild;

        while (temp != nullptr)
        {
            if (temp->getName() == name)
            {
                child = temp;
                break;
            }

            temp = temp->mNextSibling;
        }

        return child;

        return child;
    }

    //--------------------------------------------------------------------------

    TResult Node::cloneProperties(NodePtr node) const
    {
        TResult ret = T3D_OK;

        do 
        {
            if (node == nullptr)
            {
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Invalid pointer !");
                ret = T3D_ERR_INVALID_POINTER;
                break;
            }

            // 克隆结点名称
            node->mName = mName;

            // 克隆子结点属性
            Node *child = mFirstChild;

            while (child != nullptr)
            {
                NodePtr newChild = child->clone();
                child->cloneProperties(newChild);
                node->addChild(newChild);
                child = child->mNextSibling;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void Node::onAttachParent(NodePtr parent)
    {

    }

    //--------------------------------------------------------------------------

    void Node::onDetachParent(NodePtr parent)
    {

    }

    //--------------------------------------------------------------------------

    ID Node::makeGlobalID() const
    {
        static ID uID = 0;
        return ++uID;
    }
}


