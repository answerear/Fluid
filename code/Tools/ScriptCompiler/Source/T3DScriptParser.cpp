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


#include "T3DScriptParser.h"
#include "T3DScriptASTree.h"
#include "T3DScriptCompiler.h"
#include "T3DScriptError.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(ScriptParser);

    //--------------------------------------------------------------------------

    ScriptParser::ScriptParser(ScriptCompiler *compiler)
        : mCompiler(compiler)
    {

    }

    //--------------------------------------------------------------------------

    ScriptParser::~ScriptParser()
    {

    }

    //--------------------------------------------------------------------------

    bool ScriptParser::parse(const TokenListPtr &tokens, AbstractNodeListPtr &ast)
    {
        bool ret = false;

        do 
        {
            ConcreteNodeListPtr nodes(new ConcreteNodeList());

            ret = parse(tokens, nodes);
            if (!ret)
            {
                break;
            }

            ret = convertToAST(*nodes, ast);
            if (!ret)
            {
                break;
            }

            ret = true;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptParser::parse(const TokenListPtr &tokens, 
        ConcreteNodeListPtr &nodes)
    {
        enum { READY, OBJECT };
        uint32_t state = READY;

        ConcreteNode *parent = 0;
        ConcreteNodePtr node;
        Token *token = 0;
        TokenList::iterator i = tokens->begin(), end = tokens->end();
        while (i != end)
        {
            token = (*i).get();

            switch (state)
            {
            case READY:
                if (token->type == TID_WORD)
                {
                    if (token->lexeme == "import")
                    {
                        node = ConcreteNodePtr(new ConcreteNode());
                        node->token = token->lexeme;
                        node->file = token->file;
                        node->line = token->line;
                        node->type = CNT_IMPORT;

                        // The next token is the target
                        ++i;
                        if (i == end || ((*i)->type != TID_WORD 
                            && (*i)->type != TID_QUOTE))
                        {
                            ScriptError::printError(CERR_IMPORTTARGETEXPECTED, 
                                token->lexeme, token->file, token->line);
                            return false;
                        }
                            
                        ConcreteNodePtr temp(new ConcreteNode());
                        temp->parent = node.get();
                        temp->file = (*i)->file;
                        temp->line = (*i)->line;
                        temp->type = (*i)->type == TID_WORD ? CNT_WORD : CNT_QUOTE;
                        if (temp->type == CNT_QUOTE)
                            temp->token = (*i)->lexeme.substr(1, token->lexeme.size() - 2);
                        else
                            temp->token = (*i)->lexeme;
                        node->children.push_back(temp);

                        // The second-next token is the source
                        ++i;
                        ++i;
                        if (i == end || ((*i)->type != TID_WORD
                            && (*i)->type != TID_QUOTE))
                        {
                            ScriptError::printError(CERR_IMPORTSOURCEEXPECTED,
                                token->lexeme, token->file, token->line);
                            return false;
                        }

                        temp = ConcreteNodePtr(new ConcreteNode());
                        temp->parent = node.get();
                        temp->file = (*i)->file;
                        temp->line = (*i)->line;
                        temp->type = (*i)->type == TID_WORD ? CNT_WORD : CNT_QUOTE;
                        if (temp->type == CNT_QUOTE)
                            temp->token = (*i)->lexeme.substr(1, (*i)->lexeme.size() - 2);
                        else
                            temp->token = (*i)->lexeme;
                        node->children.push_back(temp);

                        // Consume all the newlines
                        i = skipNewlines(i, end);

                        // Insert the node
                        if (parent)
                        {
                            node->parent = parent;
                            parent->children.push_back(node);
                        }
                        else
                        {
                            node->parent = 0;
                            nodes->push_back(node);
                        }
                        node = ConcreteNodePtr();
                    }
                    else if (token->lexeme == "set")
                    {
                        node = ConcreteNodePtr(new ConcreteNode());
                        node->token = token->lexeme;
                        node->file = token->file;
                        node->line = token->line;
                        node->type = CNT_VARIABLE_ASSIGN;

                        // The next token is the variable
                        ++i;
                        if (i == end || (*i)->type != TID_VARIABLE)
                        {
                            ScriptError::printError(CERR_VARIABLENAMEEXPECTED,
                                token->lexeme, token->file, token->line);
                            return false;
                        }

                        ConcreteNodePtr temp(new ConcreteNode());
                        temp->parent = node.get();
                        temp->file = (*i)->file;
                        temp->line = (*i)->line;
                        temp->type = CNT_VARIABLE;
                        temp->token = (*i)->lexeme;
                        node->children.push_back(temp);

                        // The next token is the assignment
                        ++i;
                        if (i == end || ((*i)->type != TID_WORD 
                            && (*i)->type != TID_QUOTE))
                        {
                            ScriptError::printError(CERR_VARIABLEVALUEEXPECTED,
                                token->lexeme, token->file, token->line);
                            return false;
                        }
                            
                        temp = ConcreteNodePtr(new ConcreteNode());
                        temp->parent = node.get();
                        temp->file = (*i)->file;
                        temp->line = (*i)->line;
                        temp->type = (*i)->type == TID_WORD ? CNT_WORD : CNT_QUOTE;
                        if (temp->type == CNT_QUOTE)
                            temp->token = (*i)->lexeme.substr(1, (*i)->lexeme.size() - 2);
                        else
                            temp->token = (*i)->lexeme;
                        node->children.push_back(temp);

                        // Consume all the newlines
                        i = skipNewlines(i, end);

                        // Insert the node
                        if (parent)
                        {
                            node->parent = parent;
                            parent->children.push_back(node);
                        }
                        else
                        {
                            node->parent = 0;
                            nodes->push_back(node);
                        }
                        node = ConcreteNodePtr();
                    }
                    else
                    {
                        node = ConcreteNodePtr(new ConcreteNode());
                        node->file = token->file;
                        node->line = token->line;
                        node->type = token->type == TID_WORD ? CNT_WORD : CNT_QUOTE;
                        if (node->type == CNT_QUOTE)
                            node->token = token->lexeme.substr(1, token->lexeme.size() - 2);
                        else
                            node->token = token->lexeme;

                        // Insert the node
                        if (parent)
                        {
                            node->parent = parent;
                            parent->children.push_back(node);
                        }
                        else
                        {
                            node->parent = 0;
                            nodes->push_back(node);
                        }

                        // Set the parent
                        parent = node.get();

                        // Switch states
                        state = OBJECT;

                        node = ConcreteNodePtr();
                    }
                }
                else if (token->type == TID_RBRACE)
                {
                    // Go up one level if we can
                    if (parent)
                        parent = parent->parent;

                    node = ConcreteNodePtr(new ConcreteNode());
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_RBRACE;

                    // Consume all the newlines
                    i = skipNewlines(i, end);

                    // Insert the node
                    if (parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes->push_back(node);
                    }

                    // Move up another level
                    if (parent)
                        parent = parent->parent;

                    node = ConcreteNodePtr();
                }
                break;
            case OBJECT:
                if (token->type == TID_NEWLINE)
                {
                    // Look ahead to the next non-newline token 
                    // and if it isn't an {, this was a property
                    TokenList::iterator next = skipNewlines(i, end);
                    if (next == end || (*next)->type != TID_LBRACE)
                    {
                        // Ended a property here
                        if (parent)
                            parent = parent->parent;
                        state = READY;
                    }
                }
                else if (token->type == TID_COLON)
                {
                    node = ConcreteNodePtr(new ConcreteNode());
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_COLON;

                    // The following token are the parent objects (base classes).
                    // Require at least one of them.

                    TokenList::iterator j = i + 1;
                    j = skipNewlines(j, end);
                    if (j == end || ((*j)->type != TID_WORD 
                        && (*j)->type != TID_QUOTE)) 
                    {
                        ScriptError::printError(CERR_OBJECTIDENTIFIEREXPECTED,
                            token->lexeme, token->file, token->line);
                        return false;
                    }

                    while (j != end && ((*j)->type == TID_WORD || (*j)->type == TID_QUOTE))
                    {
                        ConcreteNodePtr tempNode = ConcreteNodePtr(new ConcreteNode());
                        tempNode->token = (*j)->lexeme;
                        tempNode->file = (*j)->file;
                        tempNode->line = (*j)->line;
                        tempNode->type = (*j)->type == TID_WORD ? CNT_WORD : CNT_QUOTE;
                        tempNode->parent = node.get();
                        node->children.push_back(tempNode);
                        ++j;
                    }

                    // Move it backwards once, since the end of the loop moves it forwards again anyway
                    i = --j;

                    // Insert the node
                    if (parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes->push_back(node);
                    }
                    node = ConcreteNodePtr();
                }
                else if (token->type == TID_LBRACE)
                {
                    node = ConcreteNodePtr(new ConcreteNode());
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_LBRACE;

                    // Consume all the newlines
                    i = skipNewlines(i, end);

                    // Insert the node
                    if (parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes->push_back(node);
                    }

                    // Set the parent
                    parent = node.get();

                    // Change the state
                    state = READY;

                    node = ConcreteNodePtr();
                }
                else if (token->type == TID_RBRACE)
                {
                    // Go up one level if we can
                    if (parent)
                        parent = parent->parent;

                    // If the parent is currently a { then go up again
                    if (parent && parent->type == CNT_LBRACE && parent->parent)
                        parent = parent->parent;

                    node = ConcreteNodePtr(new ConcreteNode());
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_RBRACE;

                    // Consume all the newlines
                    i = skipNewlines(i, end);

                    // Insert the node
                    if (parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes->push_back(node);
                    }

                    // Move up another level
                    if (parent)
                        parent = parent->parent;

                    node = ConcreteNodePtr();
                    state = READY;
                }
                else if (token->type == TID_VARIABLE)
                {
                    node = ConcreteNodePtr(new ConcreteNode());
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_VARIABLE;

                    // Insert the node
                    if (parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes->push_back(node);
                    }
                    node = ConcreteNodePtr();
                }
                else if (token->type == TID_QUOTE)
                {
                    node = ConcreteNodePtr(new ConcreteNode());
                    node->token = token->lexeme.substr(1, token->lexeme.size() - 2);
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_QUOTE;

                    // Insert the node
                    if (parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes->push_back(node);
                    }
                    node = ConcreteNodePtr();
                }
                else if (token->type == TID_WORD)
                {
                    node = ConcreteNodePtr(new ConcreteNode());
                    node->token = token->lexeme;
                    node->file = token->file;
                    node->line = token->line;
                    node->type = CNT_WORD;

                    // Insert the node
                    if (parent)
                    {
                        node->parent = parent;
                        parent->children.push_back(node);
                    }
                    else
                    {
                        node->parent = 0;
                        nodes->push_back(node);
                    }
                    node = ConcreteNodePtr();
                }
                break;
            }

            ++i;
        }

        return true;
    }

    //--------------------------------------------------------------------------

    bool ScriptParser::parseChunk(const TokenListPtr &tokens, AbstractNodeListPtr &ast)
    {
        bool ret = false;

        do 
        {
            ConcreteNodeListPtr nodes(new ConcreteNodeList());

            ret = parseChunk(tokens, nodes);
            if (!ret)
            {
                break;
            }

            ret = convertToAST(*nodes, ast);
            if (!ret)
            {
                break;
            }

            ret = true;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptParser::parseChunk(const TokenListPtr &tokens, ConcreteNodeListPtr &nodes)
    {
        bool ret = false;

        ConcreteNodePtr node;
        Token *token = 0;
        for (TokenList::const_iterator i = tokens->begin(); i != tokens->end(); ++i)
        {
            token = (*i).get();

            switch (token->type)
            {
            case TID_VARIABLE:
                node = ConcreteNodePtr(new ConcreteNode());
                node->file = token->file;
                node->line = token->line;
                node->parent = 0;
                node->token = token->lexeme;
                node->type = CNT_VARIABLE;
                ret = true;
                break;
            case TID_WORD:
                node = ConcreteNodePtr(new ConcreteNode());
                node->file = token->file;
                node->line = token->line;
                node->parent = 0;
                node->token = token->lexeme;
                node->type = CNT_WORD;
                ret = true;
                break;
            case TID_QUOTE:
                node = ConcreteNodePtr(new ConcreteNode());
                node->file = token->file;
                node->line = token->line;
                node->parent = 0;
                node->token = token->lexeme.substr(1, token->lexeme.size() - 2);
                node->type = CNT_QUOTE;
                ret = true;
                break;
            default:
                ScriptError::printError(CERR_UNEXPECTEDTOKEN, token->lexeme, token->file, token->line);
                ret = false;
                break;
            }

            if (ret && node)
                nodes->push_back(node);
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptParser::convertToAST(const ConcreteNodeList &nodes, AbstractNodeListPtr &ast)
    {
        bool ret = false;

        do 
        {
            AbstractTreeBuilder builder(mCompiler);
            if (!builder.visit(nodes))
            {
                break;
            }

            ast = builder.getResult();
            ret = true;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TokenList::iterator ScriptParser::skipNewlines(TokenList::iterator i, 
        TokenList::iterator end)
    {
        while (i != end && (*i)->type == TID_NEWLINE)
            ++i;
        return i;
    }
}

