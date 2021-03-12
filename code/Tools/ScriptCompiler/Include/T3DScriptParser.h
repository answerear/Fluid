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

#ifndef __T3D_SCRIPT_PARSER_H__
#define __T3D_SCRIPT_PARSER_H__


#include "T3DScriptPrerequisites.h"
#include "T3DScriptType.h"
#include "T3DScriptASTree.h"


namespace Tiny3D
{
    class ScriptCompiler;

    /**
     * @brief 脚本语法分析器
     * @remarks 这里直接借用OGRE的语法分析器
     */
    class ScriptParser : public Singleton<ScriptParser>
    {
    public:
        

    public:
        /**
         * @brief 构造函数
         */
        ScriptParser(ScriptCompiler *compiler);

        /**
         * @brief 析构函数
         */
        virtual ~ScriptParser();

        /**
         * @brief 语义分析
         * @param [in] tokens : 词法分析出的符号表
         * @param [out] ast : 返回的抽象语法树
         * @return 调用成功返回true
         */
        bool parse(const TokenListPtr &tokens, AbstractNodeListPtr &ast);

        /**
         * @brief 语义分析
         * @param [in] tokens : 词法分析出的符号表
         * @param [out] ast : 返回的抽象语法树
         * @return 调用成功返回true
         */
        bool parseChunk(const TokenListPtr &tokens, AbstractNodeListPtr &ast);

    protected:
        /**
         * @brief 语义分析，产生中间结果
         * @param [in] tokens : 词法分析后的符号表
         * @param [out] nodes : 返回的中间结果列表
         * @return 调用成功返回true
         */
        bool parse(const TokenListPtr &tokens, ConcreteNodeListPtr &nodes);

        /**
         * @brief 语义分析，产生中间结果
         * @param [in] tokens : 词法分析后的符号表
         * @param [out] nodes : 返回的中间结果列表
         * @return 调用成功返回true
         */
        bool parseChunk(const TokenListPtr &tokens, ConcreteNodeListPtr &nodes);
        
        /**
         * @brief 把中间结果转换成抽象语法树
         * @param [in] nodes : 语法分析中间结果
         * @param [out] ast : 返回的抽象语法树
         * @return 调用成功返回true
         */
        bool convertToAST(const ConcreteNodeList &nodes, AbstractNodeListPtr &ast);

        /**
          * @brief 跳过空行
          */
        TokenList::iterator skipNewlines(TokenList::iterator i, 
            TokenList::iterator end);

    protected:
        ScriptCompiler  *mCompiler;
    };
}


#endif  /*__T3D_SCRIPT_PARSER_H__*/
