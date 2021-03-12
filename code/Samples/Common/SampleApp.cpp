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

#include "SampleApp.h"


using namespace Tiny3D;

SampleApp *app = nullptr;


SampleApp::SampleApp()
    : Application()
{
    app = this;
}

SampleApp::~SampleApp()
{
    app = nullptr;
}

TResult SampleApp::go(const String &appPath)
{
    TResult ret;

    Tiny3D::Agent *theEngine = new Tiny3D::Agent();

    ret = theEngine->init(appPath, true);
    if (ret == T3D_OK)
        theEngine->run();

    delete theEngine;

    return ret;
}

bool SampleApp::applicationDidFinishLaunching()
{
    return true;
}

void SampleApp::applicationDidEnterBackground()
{
    T3D_AGENT.appDidEnterBackground();
}

void SampleApp::applicationWillEnterForeground()
{
    T3D_AGENT.appWillEnterForeground();
}

void SampleApp::applicationWillTerminate()
{

}

void SampleApp::applicationLowMemory()
{

}

