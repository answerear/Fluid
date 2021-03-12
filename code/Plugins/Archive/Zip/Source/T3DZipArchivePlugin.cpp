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


#include "T3DZipArchivePlugin.h"
#include "T3DZipArchiveCreator.h"
#include "T3DZipArchiveError.h"

namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(ZipArchivePlugin, Plugin);

    //--------------------------------------------------------------------------

    ZipArchivePlugin::ZipArchivePlugin()
        : mName("ZipArchive")
        , mZipCreator(nullptr)
    {

    }

    //--------------------------------------------------------------------------

    ZipArchivePlugin::~ZipArchivePlugin()
    {

    }

    //--------------------------------------------------------------------------

    const String &ZipArchivePlugin::getName() const
    {
        return mName;
    }

    //--------------------------------------------------------------------------

    TResult ZipArchivePlugin::install()
    {
        TResult ret = T3D_OK;

        mZipCreator = new ZipArchiveCreator();
        Agent::getInstance().addArchiveCreator(mZipCreator);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ZipArchivePlugin::startup()
    {
        TResult ret = T3D_OK;

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ZipArchivePlugin::shutdown()
    {
        TResult ret = T3D_OK;

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ZipArchivePlugin::uninstall()
    {
        TResult ret = T3D_OK;
        Agent::getInstance().removeArchiveCreator(mZipCreator);
        delete mZipCreator;
        mZipCreator = nullptr;

        return ret;
    }
}

