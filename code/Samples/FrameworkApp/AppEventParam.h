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


#ifndef __APP_EVENT_PARAM_H__
#define __APP_EVENT_PARAM_H__


#include <Tiny3D.h>

using namespace Tiny3D;

class AttackParam : public EventParam
{
public:
    AttackParam()
        : DecreaseHP(0)
        , IsNormal(true)
    {
    }

    AttackParam(int32_t decreaseHP, bool isNormal)
        : DecreaseHP(decreaseHP)
        , IsNormal(isNormal)
    {
    }

    virtual ~AttackParam()
    {
    }

protected:
    virtual EventParam *clone() override
    {
        AttackParam *param = new AttackParam(DecreaseHP, IsNormal);
        return param;
    }

public:
    int32_t DecreaseHP;
    bool    IsNormal;
};


class DefendParam : public EventParam
{
public:
    DefendParam()
    {
    }

    virtual ~DefendParam()
    {
    }

protected:
    virtual EventParam *clone() override
    {
        DefendParam *param = new DefendParam();
        return param;
    }
};


#endif  /*__APP_EVENT_PARAM_H__*/
