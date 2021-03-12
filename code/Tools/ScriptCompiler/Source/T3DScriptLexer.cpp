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


#include "T3DScriptLexer.h"
#include <sstream>


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(ScriptLexer);

    //--------------------------------------------------------------------------

    ScriptLexer::ScriptLexer()
    {

    }

    //--------------------------------------------------------------------------

    ScriptLexer::~ScriptLexer()
    {

    }

    //--------------------------------------------------------------------------

    TokenListPtr ScriptLexer::tokenize(const String &str,
        const String &source)
    {
        String error;
        TokenListPtr tokens = tokenize(str, source, error);

        if (!error.empty())
        {
            T3D_LOG_ERROR("ScriptCompiler", "Lexer - %s", error.c_str());
        }

        return tokens;
    }

    //--------------------------------------------------------------------------

    TokenListPtr ScriptLexer::tokenize(const String &str, const String &source, 
        String &error)
    {
        // State enumerates
        enum { READY = 0, COMMENT, MULTICOMMENT, WORD, QUOTE, VAR, POSSIBLECOMMENT };

        const char varopener = '$', quote = '\"', slash = '/', backslash = '\\';
        const char openbrace = '{', closebrace = '}', colon = ':', star = '*';
        const char cr = '\r', lf = '\n';
        char c = 0, lastc = 0;

        String lexeme;
        uint32_t line = 1, state = READY;
        uint32_t lastQuote = 0;

        TokenListPtr tokens(new TokenList());

        String::const_iterator i = str.begin(), end = str.end();
        while (i != end)
        {
            lastc = c;
            c = *i;

            if (c == quote)
            {
                lastQuote = line;
            }

            switch (state)
            {
            case READY:
                if (c == slash && lastc == slash)
                {
                    // Comment start, clear out the lexeme
                    lexeme = "";
                    state = COMMENT;
                }
                else if (c == star && lastc == slash)
                {
                    lexeme = "";
                    state = MULTICOMMENT;
                }
                else if (c == quote)
                {
                    // Clear out the lexeme ready to be filled with quotes!
                    lexeme = c;
                    state = QUOTE;
                }
                else if (c == varopener)
                {
                    // Set up to read in a variable
                    lexeme = c;
                    state = VAR;
                }
                else if (isNewline(c))
                {
                    lexeme = c;
                    setToken(lexeme, line, source, tokens);
                }
                else if (!isWhitespace(c))
                {
                    lexeme = c;
                    if (c == slash)
                        state = POSSIBLECOMMENT;
                    else
                        state = WORD;
                }
                break;
            case COMMENT:
                if (isNewline(c))
                {
                    lexeme = c;
                    setToken(lexeme, line, source, tokens);
                    state = READY;
                }
                break;
            case MULTICOMMENT:
                if (c == slash && lastc == star)
                    state = READY;
                break;
            case POSSIBLECOMMENT:
                if (c == slash && lastc == slash)
                {
                    lexeme = "";
                    state = COMMENT;
                    break;
                }
                else if (c == star && lastc == slash)
                {
                    lexeme = "";
                    state = MULTICOMMENT;
                    break;
                }
                else
                {
                    state = WORD;
                }
            case WORD:
                if (isNewline(c))
                {
                    setToken(lexeme, line, source, tokens);
                    lexeme = c;
                    setToken(lexeme, line, source, tokens);
                    state = READY;
                }
                else if (isWhitespace(c))
                {
                    setToken(lexeme, line, source, tokens);
                    state = READY;
                }
                else if (c == openbrace || c == closebrace || c == colon)
                {
                    setToken(lexeme, line, source, tokens);
                    lexeme = c;
                    setToken(lexeme, line, source, tokens);
                    state = READY;
                }
                else
                {
                    lexeme += c;
                }
                break;
            case QUOTE:
                if (c != backslash)
                {
                    // Allow embedded quotes with escaping
                    if (c == quote && lastc == backslash)
                    {
                        lexeme += c;
                    }
                    else if (c == quote)
                    {
                        lexeme += c;
                        setToken(lexeme, line, source, tokens);
                        state = READY;
                    }
                    else
                    {
                        // Backtrack here and allow a backslash normally within the quote
                        if (lastc == backslash)
                            lexeme = lexeme + "\\" + c;
                        else
                            lexeme += c;
                    }
                }
                break;
            case VAR:
                if (isNewline(c))
                {
                    setToken(lexeme, line, source, tokens);
                    lexeme = c;
                    setToken(lexeme, line, source, tokens);
                    state = READY;
                }
                else if (isWhitespace(c))
                {
                    setToken(lexeme, line, source, tokens);
                    state = READY;
                }
                else if (c == openbrace || c == closebrace || c == colon)
                {
                    setToken(lexeme, line, source, tokens);
                    lexeme = c;
                    setToken(lexeme, line, source, tokens);
                    state = READY;
                }
                else
                {
                    lexeme += c;
                }
                break;
            }

            // Separate check for newlines just to track line numbers
            if (c == cr || (c == lf && lastc != cr))
                line++;

            i++;
        }

        // Check for valid exit states
        if (state == WORD || state == VAR)
        {
            if (!lexeme.empty())
                setToken(lexeme, line, source, tokens);
        }
        else
        {
            if (state == QUOTE)
            {
                std::stringstream ss;
                ss << "no matching \" found for \" at ";
                ss << source;
                ss << ":";
                ss << lastQuote;
                error = ss.str();
                return tokens;
            }
        }

        return tokens;
    }

    //--------------------------------------------------------------------------

    void ScriptLexer::setToken(const String &lexeme, uint32_t line,
        const String &source, TokenListPtr tokens)
    {
        const char openBracket = '{', closeBracket = '}', colon = ':',
            quote = '\"', var = '$';

        TokenPtr token(new Token());
        token->lexeme = lexeme;
        token->line = line;
        token->file = source;
        bool ignore = false;

        // Check the user token map first
        if (lexeme.size() == 1 && isNewline(lexeme[0]))
        {
            token->type = TID_NEWLINE;
            if (!tokens->empty() && tokens->back()->type == TID_NEWLINE)
                ignore = true;
        }
        else if (lexeme.size() == 1 && lexeme[0] == openBracket)
            token->type = TID_LBRACE;
        else if (lexeme.size() == 1 && lexeme[0] == closeBracket)
            token->type = TID_RBRACE;
        else if (lexeme.size() == 1 && lexeme[0] == colon)
            token->type = TID_COLON;
        else if (lexeme.size() > 1 && lexeme[0] == var)
            token->type = TID_VARIABLE;
        else
        {
            // This is either a non-zero length phrase or quoted phrase
            if (lexeme.size() >= 2 && lexeme[0] == quote && lexeme[lexeme.size() - 1] == quote)
            {
                token->type = TID_QUOTE;
            }
            else
            {
                token->type = TID_WORD;
            }
        }

        if (!ignore)
            tokens->push_back(token);
    }

    //--------------------------------------------------------------------------

    bool ScriptLexer::isWhitespace(String::value_type c)
    {
        return c == ' ' || c == '\r' || c == '\t';
    }

    //--------------------------------------------------------------------------

    bool ScriptLexer::isNewline(String::value_type c)
    {
        return c == '\n' || c == '\r';
    }
}

