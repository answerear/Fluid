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

#include "T3DStringUtil.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    StringArray StringUtil::split(const String &str, 
        const String &delims/* = " "*/, size_t maxSplits/* = 0*/)
    {
        StringArray ret;
        // Pre-allocate some space for performance
        // 10 is guessed capacity for most case
        ret.reserve(maxSplits ? maxSplits + 1 : 10);

        unsigned int numSplits = 0;

        // Use STL methods 
        size_t start, pos;
        start = 0;
        do
        {
            pos = str.find_first_of(delims, start);
            if (pos == start)
            {
                // Do nothing
                start = pos + 1;
            }
            else if (pos == String::npos 
                || (maxSplits && numSplits == maxSplits))
            {
                // Copy the rest of the string
                ret.push_back(str.substr(start));
                break;
            }
            else
            {
                // Copy up to delimiter
                ret.push_back(str.substr(start, pos - start));
                start = pos + 1;
            }
            // parse up to next real data
            start = str.find_first_not_of(delims, start);
            ++numSplits;

        } while (pos != String::npos);

        return ret;
    }

    //--------------------------------------------------------------------------

    void StringUtil::split(const String &fullpath, String &path, String &name)
    {
        String filepath = fullpath;
        std::replace(filepath.begin(), filepath.end(), '\\', '/');
        size_t pos = filepath.find_last_of('/');

        if (pos == String::npos)
        {
            path.clear();
            name = filepath;
        }
        else
        {
            name = filepath.substr(pos + 1, path.size() - pos - 1);
            path = filepath.substr(0, pos + 1);
        }
    }

    //--------------------------------------------------------------------------

    void StringUtil::trim(String &str, bool left/* = true*/, 
        bool right/* = true*/)
    {
        static const String delims = " \t\r\n";
        if (right)
        {
            size_t pos = str.find_last_not_of(delims);
            str.erase(pos + 1); // trim right
        }
        if (left)
        {
            size_t pos = str.find_first_not_of(delims);
            str.erase(0, pos); // trim left
        }
    }

    //--------------------------------------------------------------------------

    void StringUtil::toLowerCase(String &str)
    {
        std::transform(
            str.begin(),
            str.end(),
            str.begin(),
            tolower);
    }

    //--------------------------------------------------------------------------

    void StringUtil::toUpperCase(String& str)
    {
        std::transform(
            str.begin(),
            str.end(),
            str.begin(),
            toupper);
    }

    //--------------------------------------------------------------------------

    bool StringUtil::startsWith(const String& str, const String& pattern, 
        bool lowerCase/* = true*/)
    {
        size_t thisLen = str.length();
        size_t patternLen = pattern.length();
        if (thisLen < patternLen || patternLen == 0)
            return false;

        String startOfThis = str.substr(0, patternLen);
        if (lowerCase)
            StringUtil::toLowerCase(startOfThis);

        return (startOfThis == pattern);
    }

    //--------------------------------------------------------------------------

    bool StringUtil::endsWith(const String& str, const String& pattern, 
        bool lowerCase/* = true*/)
    {
        size_t thisLen = str.length();
        size_t patternLen = pattern.length();
        if (thisLen < patternLen || patternLen == 0)
            return false;

        String endOfThis = str.substr(thisLen - patternLen, patternLen);
        if (lowerCase)
            StringUtil::toLowerCase(endOfThis);

        return (endOfThis == pattern);
    }

    //--------------------------------------------------------------------------

    void StringUtil::replaceAll(String &str, const String &replaceWhat, 
        const String &replaceWithWhat)
    {
        String::size_type pos = 0;

        while (1)
        {
            pos = str.find(replaceWhat, pos);
            if (pos == String::npos)
                break;
            str.replace(pos, 1, replaceWithWhat);
            pos++;
        }
    }

    //--------------------------------------------------------------------------

    bool StringUtil::match(const String& str, const String& pattern, 
        bool caseSensitive)
    {
        String tmpStr = str;
        String tmpPattern = pattern;
        if (!caseSensitive)
        {
            StringUtil::toLowerCase(tmpStr);
            StringUtil::toLowerCase(tmpPattern);
        }

        String::const_iterator strIt = tmpStr.begin();
        String::const_iterator patIt = tmpPattern.begin();
        String::const_iterator lastWildCardIt = tmpPattern.end();
        while (strIt != tmpStr.end() && patIt != tmpPattern.end())
        {
            if (*patIt == '*')
            {
                lastWildCardIt = patIt;
                // Skip over looking for next character
                ++patIt;
                if (patIt == tmpPattern.end())
                {
                    // Skip right to the end since * matches the entire 
                    // rest of the string
                    strIt = tmpStr.end();
                }
                else
                {
                    // scan until we find next pattern character
                    while (strIt != tmpStr.end() && *strIt != *patIt)
                        ++strIt;
                }
            }
            else
            {
                if (*patIt != *strIt)
                {
                    if (lastWildCardIt != tmpPattern.end())
                    {
                        // The last wildcard can match this incorrect sequence
                        // rewind pattern to wildcard and keep searching
                        patIt = lastWildCardIt;
                        lastWildCardIt = tmpPattern.end();
                    }
                    else
                    {
                        // no wildwards left
                        return false;
                    }
                }
                else
                {
                    ++patIt;
                    ++strIt;
                }
            }

        }
        // If we reached the end of both the pattern and the string, 
        // we succeeded
        if ((patIt == tmpPattern.end() 
            || (*patIt == '*' && patIt + 1 == tmpPattern.end())) 
            && strIt == tmpStr.end())
        {
            return true;
        }
        else
        {
            return false;
        }

    }
}

