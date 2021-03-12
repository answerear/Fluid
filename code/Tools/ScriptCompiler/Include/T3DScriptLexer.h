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

#ifndef __T3D_SCRIPT_LEXER_H__
#define __T3D_SCRIPT_LEXER_H__


#include "T3DScriptPrerequisites.h"
#include "T3DScriptType.h"


namespace Tiny3D
{
    /**
     * @brief 脚本词法分析器
     * @remarks 这里直接借用OGRE的词法分析器
     */
    class ScriptLexer : public Singleton<ScriptLexer>
    {
    public:
        /**
         * @brief 构造函数
         */
        ScriptLexer();

        /**
         * @brief 析构函数
         */
        virtual ~ScriptLexer();

        /**
         * @brief 词法分析，并且返回分析出来的符号表
         * @param [in] str : 脚本字符串
         * @param [in] source : 脚本文件名
         * @return 返回符号表
         */
        TokenListPtr tokenize(const String &str, const String &source);

    protected:
        /**
         * @brief 词法分析实现，并且返回分析出来的符号表
         * @param [in] str : 脚本字符串
         * @param [in] source : 脚本文件名
         * @param [in][out] error : 词法分析过程中错误字符串信息
         * @return 返回符号表
         */
        TokenListPtr tokenize(const String &str, const String &source, 
            String &error);

        /**
         * @brief 设置符号
         * @param [in] lexeme : 词素
         * @param [in] line : 当前符号所在的行号
         * @param [in] source : 脚本文件名
         * @param [in] tokens : 符号表
         */
        void setToken(const String &lexeme, uint32_t line, const String &source,
            TokenListPtr tokens);

        /**
         * @brief 是否空白符
         * @param [in] c : 字符对象
         * @return 空白符返回true
         */
        bool isWhitespace(String::value_type c);

        /**
         * @brief 是否换行
         * @param [in] c : 字符对象
         * @return 换行符返回true
         */
        bool isNewline(String::value_type c);
    };
}


#endif  /*__T3D_SCRIPT_LEXER_H__*/
