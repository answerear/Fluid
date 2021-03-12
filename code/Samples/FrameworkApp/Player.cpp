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


#include "Player.h"

T3D_BEGIN_EVENT_FILTER(Player, Entity)
    T3D_EVENT_FILTER(EV_ATTACKED)
    T3D_EVENT_FILTER(EV_DEFEND)
T3D_END_EVENT_FILTER()

T3D_BEGIN_EVENT_MAP(Player, Entity)
T3D_ON_EVENT(EV_ATTACKED, onAttacked)
T3D_ON_EVENT(EV_DEFEND, onDefended)
T3D_END_EVENT_MAP()


Player::Player(const String &name)
    : Entity(name)
{
    T3D_SETUP_EVENT_FILTER();
}

Player::~Player()
{

}

void Player::fire(TINSTANCE target)
{
    mState = ST_FIRING;
    T3D_LOG_INFO(LOG_TAG_APP, "Player [%s] fire skill. State [%d]", mName.c_str(), mState);
    AttackParam param(20, false);
    postEvent(EV_ATTACKED, &param, target);
}

void Player::attack(TINSTANCE target)
{
    mState = ST_ATTACKING;
    T3D_LOG_INFO(LOG_TAG_APP, "Player [%s] attack ! State [%d]", mName.c_str(), mState);
    AttackParam param(10, true);
    postEvent(EV_ATTACKED, &param, target);
}

void Player::defend(TINSTANCE attacker)
{
    mState = ST_DEFENDING;
    T3D_LOG_INFO(LOG_TAG_APP, "Player [%s] defend ! State [%d]", mName.c_str(), mState);
    DefendParam param;
    sendEvent(EV_DEFEND, &param, attacker);
}

void Player::idle()
{
    mState = ST_IDLE;
}

bool Player::onAttacked(EventParam *param, TINSTANCE sender)
{
    AttackParam *attackParam = static_cast<AttackParam*>(param);

    if (attackParam->IsNormal)
    {
        mHP -= attackParam->DecreaseHP;
        T3D_LOG_INFO(LOG_TAG_APP, "Player [%s] was attacked, HP [%d] ! State [%d]", mName.c_str(), mHP, mState);
        defend(sender);
        fire(sender);
    }
    else
    {
        mHP -= attackParam->DecreaseHP;
        T3D_LOG_INFO(LOG_TAG_APP, "Player [%s] was attacked, HP [%d] ! State [%d]", mName.c_str(), mHP, mState);
        fire(sender);
    }

    return true;
}

bool Player::onDefended(EventParam *param, TINSTANCE sender)
{
    return true;
}

