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

#ifndef __INTERSECTION_APP_H__
#define __INTERSECTION_APP_H__

#include <T3DPlatform.h>
#include <T3DMathLib.h>


class IntersectionApp : public Tiny3D::Application
{
public:
    IntersectionApp();
    virtual ~IntersectionApp();

protected:  // from Tiny3D::Application
    virtual bool applicationDidFinishLaunching() override;

    virtual void applicationDidEnterBackground() override;

    virtual void applicationWillEnterForeground() override;

    virtual void applicationWillTerminate() override;

    virtual void applicationLowMemory() override;

    // ���ߺ��������ཻ���
    void testRayTriangle();

    // ���ߺ�ƽ���ཻ���
    void testRayPlane();

    // ���ߺ������ཻ���
    void testRaySphere();

    // ���ߺ�AABB�ཻ���
    void testRayAabb();

    // ���ߺ�OBB�ཻ���
    void testRayObb();

    // �������ཻ���
    void testSphereSphere();

    // ���ƽ���ཻ���
    void testSpherePlane();

    // AABB��ƽ���ཻ���
    void testAabbPlane();

    // OBB��ƽ���ཻ���
    void testObbPlane();

    // ��׶������ཻ���
    void testFrustumSphere();

    // ��׶���AABB�ཻ���
    void testFrustumAabb();

    // ��׶���OBB�ཻ���
    void testFrustumObb();

    void buildFrustum(Tiny3D::Frustum &frustum);
};


#endif  /*__INTERSECTION_APP_H__*/
