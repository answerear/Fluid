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

#ifndef __T3D_SCRIPT_ERROR_H__
#define __T3D_SCRIPT_ERROR_H__


#include "T3DScriptPrerequisites.h"


namespace Tiny3D
{
    /**
     * @brief 编译错误码
     */
    enum ErrorCode : uint32_t
    {
        CERR_STRINGEXPECTED,
        CERR_NUMBEREXPECTED,
        CERR_FEWERPARAMETERSEXPECTED,
        CERR_VARIABLEEXPECTED,
        CERR_VARIABLEVALUEEXPECTED,
        CERR_VARIABLENAMEEXPECTED,
        CERR_UNDEFINEDVARIABLE,
        CERR_IMPORTTARGETEXPECTED,
        CERR_IMPORTSOURCEEXPECTED,
        CERR_OBJECTIDENTIFIEREXPECTED,
        CERR_OBJECTNAMEEXPECTED,
        CERR_OBJECTALLOCATIONERROR,
        CERR_OBJECTBASENOTFOUND,
        CERR_INVALIDPARAMETERS,
        CERR_DUPLICATEOVERRIDE,
        CERR_UNEXPECTEDTOKEN,
        CERR_UNSUPPORTEDBYRENDERSYSTEM, //!< @deprecated do not use
        CERR_REFERENCETOANONEXISTINGOBJECT,
        CERR_DEPRECATEDSYMBOL
    };

    class ScriptError
    {
    public:
        /**
         * @brief 输出错误信息
         * @param [in] code : 错误码
         * @param [in] token : 错误相关的符号
         * @param [in] file : 源码文件名
         * @param [in] line : 错误发生行号
         * @param [in] msg : 额外信息
         */
        static void printError(ErrorCode code, const String &token,
            const String &file, uint32_t line, const String &msg = "");
    };
    
}


#endif  /*__T3D_SCRIPT_ERROR_H__*/
