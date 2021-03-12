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

#ifndef __T3D_COMMON_ERROR_DEF_H__
#define __T3D_COMMON_ERROR_DEF_H__


#include "T3DMacro.h"


namespace Tiny3D
{
    enum CommonErrorCode
    {
        T3D_ERR_NONE                = 0,            /**< û�д��� */
        T3D_OK                      = T3D_ERR_NONE, /**< �ɹ� */
        T3D_SUCCESS                 = T3D_ERR_NONE, /**< �ɹ� */
        T3D_ERR_FAIL                = 0x00000001,   /**< ͨ�ô��� */
        T3D_ERR_INVALID_POINTER     = 0x00000002,   /**< ��ָ����߷Ƿ�ָ�� */
        T3D_ERR_INVALID_TIMERID     = 0x00000003,   /**< ��Ч��ʱ��ID */
        T3D_ERR_FILE_NOT_EXIST      = 0x00000004,   /**< �ļ������� */
        T3D_ERR_FILE_DATA_MISSING   = 0x00000005,   /**< �ļ�����ȱʧ */
        T3D_ERR_OUT_OF_BOUND        = 0x00000006,   /**< ����Խ�� */
        T3D_ERR_NOT_FOUND           = 0x00000007,   /**< û���ҵ� */
        T3D_ERR_DUPLICATED_ITEM     = 0x00000008,   /**< �ظ�Ԫ�� */
        T3D_ERR_SYS_NOT_INIT        = 0x00000009,   /**< ϵͳû�г�ʼ�� */
        T3D_ERR_INVALID_ID          = 0x0000000A,   /**< ��ЧID */
        T3D_ERR_INVALID_PARAM       = 0x0000000B,   /**< ������� */
        T3D_ERR_INVALID_SIZE        = 0x0000000C,   /**< �����С */
    };

    #define T3D_FAILED(ret)         (ret != T3D_OK)
};

#endif  /*__T3D_COMMON_ERROR_DEF_H__*/
