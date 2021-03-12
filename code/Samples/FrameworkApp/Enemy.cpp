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


#include "Enemy.h"

T3D_BEGIN_EVENT_FILTER(Enemy, Entity)
    T3D_EVENT_FILTER(EV_ATTACKED)
    T3D_EVENT_FILTER(EV_DEFEND)
T3D_END_EVENT_FILTER()

T3D_BEGIN_EVENT_MAP(Enemy, Entity)
    T3D_ON_EVENT(EV_ATTACKED, onAttacked)
    T3D_ON_EVENT(EV_DEFEND, onDefended)
T3D_END_EVENT_MAP()


Enemy::Enemy(const String &name)
    : Entity(name)
{
    T3D_SETUP_EVENT_FILTER();
}

Enemy::~Enemy()
{

}

void Enemy::fire(TINSTANCE target)
{
    mState = ST_FIRING;
    T3D_LOG_INFO(LOG_TAG_APP, "Enemy [%s] fire skill. State [%d]", mName.c_str(), mState);
    AttackParam param(10, false);
    postEvent(EV_ATTACKED, &param, target);
}

void Enemy::attack(TINSTANCE target)
{
    mState = ST_ATTACKING;
    T3D_LOG_INFO(LOG_TAG_APP, "Enemy [%s] attack ! State [%d]", mName.c_str(), mState);
    AttackParam param(5, true);
    postEvent(EV_ATTACKED, &param, target);
}

void Enemy::defend(TINSTANCE attacker)
{
    mState = ST_DEFENDING;
    T3D_LOG_INFO(LOG_TAG_APP, "Enemy [%s] defend ! State [%d]", mName.c_str(), mState);
    DefendParam param;
    sendEvent(EV_DEFEND, &param, attacker);
}

void Enemy::idle()
{
    mState = ST_IDLE;
}

bool Enemy::onAttacked(EventParam *param, TINSTANCE sender)
{
    AttackParam *attackParam = static_cast<AttackParam*>(param);

    if (attackParam->IsNormal)
    {
        mHP -= attackParam->DecreaseHP;
        T3D_LOG_INFO(LOG_TAG_APP, "Enemy [%s] was attacked, HP [%d] ! State [%d]", mName.c_str(), mHP, mState);
        defend(sender);
        fire(sender);
    }
    else
    {
        mHP -= attackParam->DecreaseHP;
        T3D_LOG_INFO(LOG_TAG_APP, "Enemy [%s] was attacked, HP [%d] ! State [%d]", mName.c_str(), mHP, mState);
    }

    return true;
}

bool Enemy::onDefended(EventParam *param, TINSTANCE sender)
{
    return true;
}

