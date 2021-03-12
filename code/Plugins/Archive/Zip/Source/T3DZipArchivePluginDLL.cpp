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
#include "T3DZipArchiveError.h"


Tiny3D::ZipArchivePlugin *gPlugin = nullptr;

extern "C"
{
    T3D_ZIPARCHIVE_API TResult dllStartPlugin()
    {
        gPlugin = new Tiny3D::ZipArchivePlugin();
        return Tiny3D::Agent::getInstance().installPlugin(gPlugin);
    }

    T3D_ZIPARCHIVE_API TResult dllStopPlugin()
    {
        TResult ret = Tiny3D::Agent::getInstance().uninstallPlugin(gPlugin);

        if (ret == Tiny3D::T3D_OK)
        {
            delete gPlugin;
            gPlugin = nullptr;
        }

        return ret;
    }
}
