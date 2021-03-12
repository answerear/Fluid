/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2017  Answer Wong
 * For latest info, see https://github.com/asnwerear/Tiny3D
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

#include "Adapter/Unix/T3DUnixDir.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


namespace Tiny3D
{
    UnixDir::UnixDir()
    {

    }

    UnixDir::~UnixDir()
    {

    }

    bool UnixDir::findFile(const String &strPath)
    {
        if (strPath.empty() || strPath == "")
        {
            return false;
        }

        extractRoot(strPath, m_strRoot);
        extractExt(strPath, m_strExt);
        m_pDir = opendir(m_strRoot.c_str());
        m_bExtractName = false;

        return (m_pDir != NULL);
    }

    bool UnixDir::findNextFile()
    {
        if (NULL == m_pDir)
        {
            return false;
        }

        m_pDirent = readdir(m_pDir);
        if (m_pDirent != NULL && !isDirectory())
        {
            String strName = m_pDirent->d_name;
            String strExt;
            extractExt(strName, strExt);
            if (strExt != m_strExt && m_strExt != "*" && m_strExt != "")
                findNextFile();
        }

        m_bExtractName = false;

        return (m_pDirent != NULL);
    }

    void UnixDir::close()
    {
        if (NULL == m_pDir)
        {
            return;
        }

        closedir(m_pDir);
        m_pDir = NULL;
        m_pDirent = NULL;
        m_bExtractName = false;
    }

    String UnixDir::getRoot() const
    {
        if (NULL == m_pDir)
            return "";

        return m_strRoot;
    }

    String UnixDir::getFileName() const
    {
        if (NULL == m_pDir || NULL == m_pDirent)
            return "";

        if (!m_bExtractName)
        {
            String strFilePath = m_pDirent->d_name;
            extractFileName(strFilePath, m_strName, m_strTitle);
        }

        return m_strName;
    }

    String UnixDir::getFilePath() const
    {
        if (NULL == m_pDir || NULL == m_pDirent)
            return "";

        String strPath = m_pDirent->d_name;

        if (!m_bExtractName)
        {
            extractFileName(strPath, m_strName, m_strTitle);
        }

        return m_strRoot + strPath;
    }

    String UnixDir::getFileTitle() const
    {
        if (NULL == m_pDir || NULL == m_pDirent)
            return "";

        if (!m_bExtractName)
        {
            String strPath = m_pDirent->d_name;
            extractFileName(strPath, m_strName, m_strTitle);
        }

        return m_strTitle;
    }

    uint32_t UnixDir::getLength() const
    {
        String strPath = m_strRoot + String(m_pDirent->d_name);
        struct stat s;
        int result = stat(strPath.c_str(), &s);

        return (result == 0 ? (uint32_t)s.st_size : 0);
    }

    bool UnixDir::isDots() const
    {
        if (NULL == m_pDir || NULL == m_pDirent)
            return false;

        return (strcmp(m_pDirent->d_name, ".") == 0
            || strcmp(m_pDirent->d_name, "..") == 0);
    }

    bool UnixDir::isDirectory() const
    {
        if (NULL == m_pDir || NULL == m_pDirent)
            return false;

        String strPath = m_strRoot + String(m_pDirent->d_name);
        struct stat s;
        int result = stat(strPath.c_str(), &s);

        return (result == 0 && S_ISDIR(s.st_mode));
    }

    bool UnixDir::makeDir(const String &strDir)
    {
        if (strDir.empty() || strDir == "")
            return false;

		return (::mkdir(strDir.c_str(), S_IRWXU) == 0);
    }

    bool UnixDir::removeDir(const String &strDir)
    {
        if (strDir.empty() || strDir == "")
            return false;

		return (::rmdir(strDir.c_str()) == 0);
    }

    bool UnixDir::remove(const String &strFileName)
    {
        if (strFileName.empty() || strFileName == "")
            return false;

		return (::remove(strFileName.c_str()) == 0);
    }

    bool UnixDir::exists(const String &strPath) const
    {
        struct stat s;
        int result = stat(strPath.c_str(), &s);
        return (result == 0);
    }

    char UnixDir::getNativeSeparator() const
    {
        return '/';
    }

    bool UnixDir::extractRoot(const String &strPath, String &strRoot)
    {
        bool bResult = false;
        size_t nPos = strPath.rfind("/");

        if (nPos == -1)
        {
            nPos = strPath.rfind("\\");
        }

        if (nPos != -1)
        {
            bResult = true;
            size_t nCount = nPos + 1;
            size_t nOffset = 0;
            strRoot = strPath.substr(nOffset, nCount);
        }
        else
        {
            bResult = false;
        }

        return bResult;
    }

    bool UnixDir::extractExt(const String &strName, String &strExt)
    {
        bool bResult = false;

        size_t nPos = strName.rfind(".");

        if (nPos != -1)
        {
            bResult = true;
            size_t nLength = strName.length();
            size_t nCount = nLength - nPos - 1;
            size_t nOffset = nPos + 1;
            strExt = strName.substr(nOffset, nCount);
        }
        else
        {
            bResult = false;
        }

        return bResult;
    }

    bool UnixDir::extractFileName(const String &strPath, String &strName, String &strTitle) const
    {
        bool bResult = false;

        strName = strPath;

        size_t nPos = strName.rfind(".");
        size_t nCount = nPos;
        size_t nOffset = 0;
        if (nPos == 0)
            strTitle = "";
        else
            strTitle = strPath.substr(nOffset, nCount);

        m_bExtractName = true;

        return bResult;
    }
}

