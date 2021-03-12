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

#ifndef __T3D_EVENT_ERROR_DEF_H__
#define __T3D_EVENT_ERROR_DEF_H__


#include "T3DEventPrerequisites.h"


namespace Tiny3D
{
    // Framework 模块错误码从 T3D_ERR_FRAMEWORK 开始
    enum FrameworkErrorCode
    {
        /**< 无效的实例句柄 */
        T3D_ERR_FWK_INVALID_INSTANCE    = T3D_ERR_FRAMEWORK,
        /**< 无效的接收者 */
        T3D_ERR_FWK_INVALID_RECVER      = T3D_ERR_FRAMEWORK + 1,
        /**< 无效的发送者 */
        T3D_ERR_FWK_INVALID_SENDER      = T3D_ERR_FRAMEWORK + 2,
        /**< 无效事件ID */
        T3D_ERR_FWK_INVALID_EVID        = T3D_ERR_FRAMEWORK + 3,
        /**< 事件处理超时，无法立刻完成全部，被打断了 */
        T3D_ERR_FWK_HANDLING_TIMEOVER   = T3D_ERR_FRAMEWORK + 4,
        /**< 事件嵌套超出栈调用层次，被打断了 */
        T3D_ERR_FWK_CALLSTACK_OVERFLOW  = T3D_ERR_FRAMEWORK + 5,
        /**< 没有任何对象处理 */
        T3D_ERR_FWK_NONE_HANDLER        = T3D_ERR_FRAMEWORK + 6,
        /**< 无法马上处理，因为被暂停派发了 */
        T3D_ERR_FWK_SUSPENDED           = T3D_ERR_FRAMEWORK + 7,
        /**< 重复实例句柄 */
        T3D_ERR_FWK_DUPLICATE_INSTANCE  = T3D_ERR_FRAMEWORK + 8,
    };
    
}


#endif  /*__T3D_EVENT_ERROR_DEF_H__*/
