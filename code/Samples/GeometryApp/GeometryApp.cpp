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

#include "GeometryApp.h"


using namespace Tiny3D;


#define OBJ_MASK_SCENE         1


GeometryApp theApp;


GeometryApp::GeometryApp()
    : SampleApp()
{
}

GeometryApp::~GeometryApp()
{
}

bool GeometryApp::applicationDidFinishLaunching()
{
    SceneNodePtr root = T3D_SCENE_MGR.getRoot();

    RenderWindowPtr renderWindow = T3D_AGENT.getDefaultRenderWindow();

    // 相机
    SceneNodePtr node = T3D_SCENE_MGR.createSceneNode(root);

    CameraPtr camera = smart_pointer_cast<Camera>(node->addComponent(T3D_CLASS(Camera)));
    camera->lookAt(Vector3(0.0f, 4.0f, 8.0f), Vector3::ZERO, Vector3::UNIT_Y);
    camera->setProjectionType(Camera::Type::PERSPECTIVE);
    Real w = Real(renderWindow->getWidth());
    Real h = Real(renderWindow->getHeight());
    Real aspect = w / h;
    Radian fovY(Math::PI * REAL_HALF);
    camera->setPerspectiveParams(fovY, aspect, 0.5f, 1000.0f);
    camera->setObjectMask(OBJ_MASK_SCENE);

    // 视口
    ViewportPtr viewport = renderWindow->addViewport(camera, 1, 
        REAL_ZERO, REAL_ZERO, REAL_ONE, REAL_ONE);
    viewport->setBkgndColor(ColorRGB::BLACK);

    // 箱子
    node = T3D_SCENE_MGR.createSceneNode(root);
    Vector3 extent(1.0f, 1.0f, 1.0f);
    CubePtr cube = smart_pointer_cast<Cube>(node->addComponent(T3D_CLASS(Cube), Vector3::ZERO, extent));
    node->getTransform3D()->setPosition(Vector3(-4.0f, 0.0f, -2.0f));
    node->setCameraMask(OBJ_MASK_SCENE);
    ObbBoundPtr b0 = smart_pointer_cast<ObbBound>(node->addComponent(T3D_CLASS(ObbBound)));
    b0->setCenter(Vector3::ZERO);
    b0->setAxis(Vector3::UNIT_X * extent[0],
        Vector3::UNIT_Y * extent[1], Vector3::UNIT_Z * extent[2]);
//     box->setScaling(Vector3(100, 100, 100));

    // 球
    node = T3D_SCENE_MGR.createSceneNode(root);
    Real radius(1.0f);
    GlobePtr sphere = smart_pointer_cast<Globe>(node->addComponent(T3D_CLASS(Globe), Vector3::ZERO, &radius));
    node->getTransform3D()->setPosition(Vector3(2.0f, 0.0f, 0.0f));
    node->setCameraMask(OBJ_MASK_SCENE);
    SphereBoundPtr b1 = smart_pointer_cast<SphereBound>(node->addComponent(T3D_CLASS(SphereBound)));
    b1->setParams(Vector3::ZERO, radius);

    // 空间四边形
    
    // 模型
    //node = T3D_SCENE_MGR.createSceneNode(root);
    //MeshPtr mesh = smart_pointer_cast<Mesh>(node->addComponent(T3D_CLASS(Mesh)));
    //node->getTransform3D()->setPosition(Vector3::ZERO);
    //node->setCameraMask(OBJ_MASK_SCENE);

    // Mesh
    node = T3D_SCENE_MGR.createSceneNode(root);
    node->getTransform3D()->setPosition(Vector3::ZERO);
    node->setCameraMask(OBJ_MASK_SCENE);
    MeshPtr mesh = smart_pointer_cast<Mesh>(node->addComponent(T3D_CLASS(Mesh)));
//     ModelPtr model = T3D_MODEL_MGR.loadModel();
    mesh->setModel("models/tortoise.t3d");

    return true;
}


