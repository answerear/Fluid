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


#include "T3DScriptError.h"

namespace Tiny3D
{
    void ScriptError::printError(ErrorCode code, const String &token,
        const String &file, uint32_t line, const String &msg /* = "" */)
    {
        const char *TAG = "Compiler";

        switch (code)
        {
        case CERR_STRINGEXPECTED:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Expected a string for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }   
            else
            {
                T3D_LOG_ERROR(TAG, "Expected a string for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_NUMBEREXPECTED:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Expected a number for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Expected a number for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_FEWERPARAMETERSEXPECTED:
            T3D_LOG_ERROR(TAG, "%s Expected more parameters for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            break;
        case CERR_VARIABLEEXPECTED:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Expected variable for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Expected variable for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_VARIABLEVALUEEXPECTED:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Expected variable value for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Expected variable value for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_VARIABLENAMEEXPECTED:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Expected variable name for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Expected variable name for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_UNDEFINEDVARIABLE:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Undefined variable for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Undefined variable for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_IMPORTTARGETEXPECTED:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Expected import target for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Expected import target for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_IMPORTSOURCEEXPECTED:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Expected import source for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Expected import source for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_OBJECTIDENTIFIEREXPECTED:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Expected object identifier for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Expected object identifier for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_OBJECTNAMEEXPECTED:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Expected object name for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Expected object name for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_OBJECTALLOCATIONERROR:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Could not allocate for object for %s in \
                    %s : %u", msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Could not allocate for object for %s in \
                    %s : %u", token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_OBJECTBASENOTFOUND:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Could not find base object for %s in \
                    %s : %u", msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Could not find base object for %s in \
                    %s : %u", token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_INVALIDPARAMETERS:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Invalid parameters for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Invalid parameters for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_DUPLICATEOVERRIDE:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Duplicated override for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Duplicated override for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_UNEXPECTEDTOKEN:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "% Unexpected token for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Unexpected token for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_UNSUPPORTEDBYRENDERSYSTEM:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Unsupported by render system for %s in \
                    %s : %u", msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Unsupported by render system for %s in \
                    %s : %u", token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_REFERENCETOANONEXISTINGOBJECT:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Reference to an a none existing object \
                    for %s in %s : %u", msg.c_str(), token.c_str(), 
                    file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Reference to an a none existing object for \
                    %s in %s : %u", token.c_str(), file.c_str(), line);
            }
            break;
        case CERR_DEPRECATEDSYMBOL:
            if (!msg.empty())
            {
                T3D_LOG_ERROR(TAG, "%s Deprecated symbol for %s in %s : %u",
                    msg.c_str(), token.c_str(), file.c_str(), line);
            }
            else
            {
                T3D_LOG_ERROR(TAG, "Deprecated symbol for %s in %s : %u",
                    token.c_str(), file.c_str(), line);
            }
            break;
        }
    }
}

