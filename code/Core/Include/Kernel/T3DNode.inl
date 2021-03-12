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


namespace Tiny3D
{
    inline uint32_t Node::getNodeID() const
    {
        return mID;
    }

    inline void Node::setName(const String &name)
    {
        mName = name;
    }

    inline const String &Node::getName() const
    {
        return mName;
    }

    inline NodePtr Node::getFirstChild() const
    {
        return mFirstChild;
    }

    inline NodePtr Node::getLastChild() const
    {
        return mLastChild;
    }

    inline NodePtr Node::getPrevSibling() const
    {
        return mPrevSibling;
    }

    inline NodePtr Node::getNextSibling() const
    {
        return mNextSibling;
    }

    inline size_t Node::getChildrenCount() const
    {
        return mChildrenCount;
    }

    inline NodePtr Node::getParent() const
    {
        return mParent;
    }
}
