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


#include "Entity.h"


T3D_BEGIN_EVENT_FILTER(Entity, EventHandler)
T3D_END_EVENT_FILTER()

T3D_BEGIN_EVENT_MAP(Entity, EventHandler)
T3D_END_EVENT_MAP()


Entity::Entity(const String &name)
    : mName(name)
    , mHP(100)
    , mMP(100)
    , mState(ST_NONE)
{

}

Entity::~Entity()
{

}


