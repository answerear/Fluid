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


#include "T3DMeshConverter.h"

// For debug
// Text : -i FBX -o t3t -b sphere -m shared $(SolutionDir)..\..\..\assets\models\tortoise.fbx 
// Binary : -i FBX -o t3b -b sphere -m shared $(SolutionDir)..\..\..\assets\models\tortoise.fbx


int main(int argc, char *argv[])
{
    using namespace Tiny3D;

    System *system = new System();
    system->init();

    Logger *logger = new Logger();
    logger->startup(1001, "MeshConverter", true, false);

    ObjectTracer *tracer = new ObjectTracer(true);

    MCONV_LOG_INFO("Begin mesh-conv --------------------------------------");

    MeshConverter *converter = new MeshConverter();
    TResult ret = converter->execute(argc, argv);
    delete converter;

    MCONV_LOG_INFO("End mesh-conv ----------------------------------------");

    delete tracer;

    logger->shutdown();

    delete logger;
    delete system;

    return ret;
}

