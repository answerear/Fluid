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

#ifndef __T3D_UNIX_DIR_H__
#define __T3D_UNIX_DIR_H__

#include "Adapter/T3DDirInterface.h"
#include <dirent.h>

namespace Tiny3D
{
    class UnixDir : public IDir
    {
    public:
        UnixDir();
        virtual ~UnixDir();
        
        virtual bool findFile(const String &strPath) override;
        
        virtual bool findNextFile() override;
        
        virtual void close() override;
        
        virtual String getRoot() const override;
        
        virtual String getFileName() const override;
        
        virtual String getFilePath() const override;
        
        virtual String getFileTitle() const override;
        
        virtual uint32_t getLength() const override;
        
        virtual bool isDots() const override;
        
        virtual bool isDirectory() const override;
        
        virtual bool makeDir(const String &strDir) override;
        
        virtual bool removeDir(const String &strDir) override;
        
        virtual bool remove(const String &strFileName) override;
        
        virtual bool exists(const String &strPath) const override;
        
        virtual char getNativeSeparator() const override;
        
    protected:
        bool extractRoot(const String &strPath, String &strRoot);
        bool extractExt(const String &strName, String &strExt);
        bool extractFileName(const String &strPath, String &strName, 
            String &strTitle) const;
        
    protected:
        DIR     *m_pDir;
        dirent  *m_pDirent;
        
        mutable bool    m_bExtractName;
        
        std::string m_strExt;
        std::string m_strRoot;
        mutable std::string m_strName;
        mutable std::string m_strTitle;
    };
}


#endif  /*__T3D_UNIX_DIR_H__*/
