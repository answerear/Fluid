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

#include "TextureApp.h"


using namespace Tiny3D;


#define OBJ_MASK_SCENE         1


TextureApp theApp;


TextureApp::TextureApp()
    : SampleApp()
{
}

TextureApp::~TextureApp()
{
}

bool TextureApp::applicationDidFinishLaunching()
{
    SceneNodePtr root = T3D_SCENE_MGR.getRoot();

    RenderWindowPtr renderWindow = T3D_AGENT.getDefaultRenderWindow();

    // 相机
//     CameraPtr camera = T3D_SCENE_MGR.createCamera(root);
//     camera->lookAt(Vector3(0.0f, 4.0f, 8.0f), Vector3::ZERO, Vector3::UNIT_Y);
//     camera->setProjectionType(Camera::Type::PERSPECTIVE);
//     Real w = Real(renderWindow->getWidth());
//     Real h = Real(renderWindow->getHeight());
//     Real aspect = w / h;
//     Radian fovY(Math::PI * REAL_HALF);
//     camera->setPerspectiveParams(fovY, aspect, 0.5f, 1000.0f);
//     camera->setObjectMask(OBJ_MASK_SCENE);
// 
//     // 视口
//     ViewportPtr viewport = renderWindow->addViewport(camera, 1, 
//         REAL_ZERO, REAL_ZERO, REAL_ONE, REAL_ONE);
//     viewport->setBkgndColor(ColorRGB::BLACK);

    // 箱子
//     Vector3 extent(1.0f, 1.0f, 1.0f);
//     CubePtr box = T3D_SCENE_MGR.createBox(Vector3::ZERO, extent, root);
//     box->setPosition(Vector3(-4.0f, 0.0f, -2.0f));
//     box->setCameraMask(OBJ_MASK_SCENE);
//     box->setScaling(Vector3(100, 100, 100));

    // 球
//     GlobePtr sphere = T3D_SCENE_MGR.createSphere(Vector3::ZERO, 1.0f, root);
//     sphere->setPosition(Vector3(2.0f, 0.0f, 0.0f));
//     sphere->setCameraMask(OBJ_MASK_SCENE);

    // 空间四边形
    

    return true;
}


