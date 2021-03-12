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


#ifndef __ENTITY_H__
#define __ENTITY_H__


#include <Tiny3D.h>
#include "AppEventDefine.h"
#include "AppEventParam.h"


using namespace Tiny3D;


class Entity : public EventHandler
{
    T3D_DECLARE_EVENT_FILTER();
    T3D_DECLARE_EVENT_MAP();

public:
    enum State
    {
        ST_NONE = 0,
        ST_IDLE,
        ST_FIRING,
        ST_ATTACKING,
        ST_DEFENDING,
    };

    Entity(const String &name);
    virtual ~Entity();

    virtual void fire(TINSTANCE target) = 0;
    virtual void attack(TINSTANCE target) = 0;
    virtual void defend(TINSTANCE attacker) = 0;
    virtual void idle() = 0;

protected:
    String      mName;

    int32_t     mHP;
    int32_t     mMP;

    State       mState;
};


#endif  /*__ENTITY_H__*/

