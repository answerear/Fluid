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

#include "IO/T3DDir.h"
#include "Adapter/T3DFactoryInterface.h"
#include "Adapter/T3DDirInterface.h"
#include "T3DSystem.h"
#include "T3DType.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    IDir *Dir::sDir = nullptr;

    String Dir::sCachePath;
    String Dir::sAppPath;
    String Dir::sWritablePath;
    String Dir::sLibPath;

    char Dir::NATIVE_SEPARATOR = 0;

    T3D_IMPLEMENT_CLASS_0(Dir);

    //--------------------------------------------------------------------------

    Dir::Dir()
    {
        mDir = T3D_PLATFORM_FACTORY.createPlatformDir();
    }

    //--------------------------------------------------------------------------

    Dir::~Dir()
    {
        T3D_SAFE_DELETE(mDir);
    }

    //--------------------------------------------------------------------------

    bool Dir::findFile(const String &strPath)
    {
        if (mDir != nullptr)
        {
            return mDir->findFile(strPath);
        }

        return false;
    }

    //--------------------------------------------------------------------------

    bool Dir::findNextFile()
    {
        if (mDir != nullptr)
        {
            return mDir->findNextFile();
        }

        return false;
    }

    //--------------------------------------------------------------------------

    void Dir::close()
    {
        if (mDir != nullptr)
        {
            mDir->close();
        }
    }

    //--------------------------------------------------------------------------

    String Dir::getRoot() const
    {
        if (mDir != nullptr)
        {
            return mDir->getRoot();
        }

        return "";
    }

    //--------------------------------------------------------------------------

    String Dir::getFileName() const
    {
        if (mDir != nullptr)
        {
            return mDir->getFileName();
        }

        return "";
    }

    //--------------------------------------------------------------------------

    String Dir::getFilePath() const
    {
        if (mDir != nullptr)
        {
            return mDir->getFilePath();
        }

        return "";
    }

    //--------------------------------------------------------------------------

    String Dir::getFileTitle() const
    {
        if (mDir != nullptr)
        {
            return mDir->getFileTitle();
        }

        return "";
    }

    //--------------------------------------------------------------------------

    uint32_t Dir::getFileSize() const
    {
        if (mDir != nullptr)
        {
            return mDir->getLength();
        }

        return 0;
    }

    //--------------------------------------------------------------------------

    bool Dir::isDots() const
    {
        if (mDir != nullptr)
        {
            return mDir->isDots();
        }

        return false;
    }

    //--------------------------------------------------------------------------

    bool Dir::isDirectory() const
    {
        if (mDir != nullptr)
        {
            return mDir->isDirectory();
        }

        return false;
    }

    //--------------------------------------------------------------------------

    long_t Dir::getCreationTime() const
    {
        if (mDir != nullptr)
        {
            return mDir->getCreationTime();
        }

        return 0;
    }

    //--------------------------------------------------------------------------

    long_t Dir::getLastAccessTime() const
    {
        if (mDir != nullptr)
        {
            return mDir->getLastAccessTime();
        }

        return 0;
    }

    //--------------------------------------------------------------------------

    long_t Dir::getLastWriteTime() const
    {
        if (mDir != nullptr)
        {
            return mDir->getLastWriteTime();
        }

        return 0;
    }

    //--------------------------------------------------------------------------

    bool Dir::makeDir(const String &strDir)
    {
        if (nullptr == sDir)
            sDir = T3D_PLATFORM_FACTORY.createPlatformDir();

        if (sDir != nullptr)
        {
            return sDir->makeDir(strDir);
        }

        return false;
    }

    //--------------------------------------------------------------------------

    bool Dir::removeDir(const String &strDir)
    {
        if (nullptr == sDir)
            sDir = T3D_PLATFORM_FACTORY.createPlatformDir();

        if (sDir != nullptr)
        {
            return sDir->removeDir(strDir);
        }

        return false;
    }

    //--------------------------------------------------------------------------

    bool Dir::remove(const String &strFileName)
    {
        if (nullptr == sDir)
            sDir = T3D_PLATFORM_FACTORY.createPlatformDir();

        if (sDir != nullptr)
        {
            return sDir->remove(strFileName);
        }

        return false;
    }

    //--------------------------------------------------------------------------

    bool Dir::exists(const String &strPath)
    {
        if (nullptr == sDir)
            sDir = T3D_PLATFORM_FACTORY.createPlatformDir();

        if (sDir != nullptr)
        {
            return sDir->exists(strPath);
        }

        return false;
    }

    //--------------------------------------------------------------------------

    const String &Dir::getCachePath()
    {
        if (sCachePath.empty())
        {
            if (nullptr == sDir)
                sDir = T3D_PLATFORM_FACTORY.createPlatformDir();

            if (sDir != nullptr)
            {
                sCachePath = sDir->getCachePath();
            }
        }

        return sCachePath;
    }

    //--------------------------------------------------------------------------

    const String &Dir::getAppPath()
    {
        if (sAppPath.empty())
        {
            if (nullptr == sDir)
                sDir = T3D_PLATFORM_FACTORY.createPlatformDir();

            if (sDir != nullptr)
            {
                sAppPath = sDir->getAppPath();
            }
        }

        return sAppPath;
    }

    //--------------------------------------------------------------------------

    const String &Dir::getWritablePath()
    {
        if (sWritablePath.empty())
        {
            if (nullptr == sDir)
                sDir = T3D_PLATFORM_FACTORY.createPlatformDir();

            if (sDir != nullptr)
            {
                sWritablePath = sDir->getWritablePath();
            }
        }

        return sWritablePath;
    }

    //--------------------------------------------------------------------------

    const String &Dir::getLibraryPath()
    {
        if (sLibPath.empty())
        {
            if (nullptr == sDir)
                sDir = T3D_PLATFORM_FACTORY.createPlatformDir();

            if (sDir != nullptr)
            {
                sLibPath = sDir->getLibraryPath();
            }
        }

        return sLibPath;
    }

    //--------------------------------------------------------------------------

    char Dir::getNativeSeparator()
    {
        if (NATIVE_SEPARATOR == 0)
        {
            if (nullptr == sDir)
                sDir = T3D_PLATFORM_FACTORY.createPlatformDir();

            if (sDir != nullptr)
            {
                NATIVE_SEPARATOR = sDir->getNativeSeparator();
            }
        }

        return NATIVE_SEPARATOR;
    }
}
