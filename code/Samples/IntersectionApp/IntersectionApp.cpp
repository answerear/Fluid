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

#include "IntersectionApp.h"


using namespace Tiny3D;

const size_t TriVerticesCount = 3;

const Vector3 TriangleVertices0[TriVerticesCount] =
{
    Vector3(-REAL_ONE, -REAL_ONE, REAL_ZERO),
    Vector3( REAL_ONE, -REAL_ONE, REAL_ZERO),
    Vector3( REAL_ZERO, REAL_ONE, REAL_ZERO)
};

const Vector3 TriangleVertices1[TriVerticesCount] =
{
    Vector3(Real(3), -REAL_ONE, REAL_ZERO),
    Vector3(Real(5), -REAL_ONE, REAL_ZERO),
    Vector3(Real(4),  REAL_ONE, REAL_ZERO)
};

const size_t BoxVerticesCount = 8;

const Vector3 BoxVertices0[BoxVerticesCount] =
{
    Vector3( REAL_HALF,  REAL_HALF,  REAL_HALF),
    Vector3( REAL_HALF, -REAL_HALF,  REAL_HALF),
    Vector3(-REAL_HALF,  REAL_HALF,  REAL_HALF),
    Vector3(-REAL_HALF, -REAL_HALF,  REAL_HALF),
    Vector3( REAL_HALF,  REAL_HALF, -REAL_HALF),
    Vector3( REAL_HALF, -REAL_HALF, -REAL_HALF),
    Vector3(-REAL_HALF,  REAL_HALF, -REAL_HALF),
    Vector3(-REAL_HALF, -REAL_HALF, -REAL_HALF),
};

const Vector3 BoxVertices1[BoxVerticesCount] = 
{
    Vector3(Real(4),  REAL_HALF,  REAL_HALF),
    Vector3(Real(4), -REAL_HALF,  REAL_HALF),
    Vector3(Real(3),  REAL_HALF,  REAL_HALF),
    Vector3(Real(3), -REAL_HALF,  REAL_HALF),
    Vector3(Real(4),  REAL_HALF, -REAL_HALF),
    Vector3(Real(4), -REAL_HALF, -REAL_HALF),
    Vector3(Real(3),  REAL_HALF, -REAL_HALF),
    Vector3(Real(3), -REAL_HALF, -REAL_HALF),
};

const Vector3 BoxVertices2[BoxVerticesCount] =
{
    Vector3( REAL_ONE,  REAL_HALF,  REAL_HALF),
    Vector3( REAL_ONE, -REAL_HALF,  REAL_HALF),
    Vector3(REAL_ZERO,  REAL_HALF,  REAL_HALF),
    Vector3(REAL_ZERO, -REAL_HALF,  REAL_HALF),
    Vector3( REAL_ONE,  REAL_HALF, -REAL_HALF),
    Vector3( REAL_ONE, -REAL_HALF, -REAL_HALF),
    Vector3(REAL_ZERO,  REAL_HALF, -REAL_HALF),
    Vector3(REAL_ZERO, -REAL_HALF, -REAL_HALF),
};

const Vector3 BoxVertices3[BoxVerticesCount] =
{
    Vector3(Real(60),  REAL_HALF,  REAL_HALF),
    Vector3(Real(60), -REAL_HALF,  REAL_HALF),
    Vector3(Real(50),  REAL_HALF,  REAL_HALF),
    Vector3(Real(50), -REAL_HALF,  REAL_HALF),
    Vector3(Real(60),  REAL_HALF, -REAL_HALF),
    Vector3(Real(60), -REAL_HALF, -REAL_HALF),
    Vector3(Real(50),  REAL_HALF, -REAL_HALF),
    Vector3(Real(50), -REAL_HALF, -REAL_HALF),
};


IntersectionApp::IntersectionApp()
    : Application()
{
}

IntersectionApp::~IntersectionApp()
{
}


/*******************************************************************************

                                    Y
                                    |
                                    |
                                    |
                                    |
                                    |
                                    |
                                    |
                                    |
                                    |
                                    |______________________________ X
                                   / 
                                  /  O
                                 /
                                /
                               /
                              /
                             /
                            /
                           Z

 ******************************************************************************/
bool IntersectionApp::applicationDidFinishLaunching()
{
    // ���ߺ��������ཻ���
    testRayTriangle();

    // ���ߺ�ƽ���ཻ���
    testRayPlane();

    // ���ߺ������ཻ���
    testRaySphere();

    // ���ߺ�AABB�ཻ���
    testRayAabb();

    // ���ߺ�OBB�ཻ���
    testRayObb();

    // �������ཻ���
    testSphereSphere();

    // ���ƽ���ཻ���
    testSpherePlane();

    // AABB��ƽ���ཻ���
    testAabbPlane();

    // OBB��ƽ���ཻ���
    testObbPlane();

    // ��׶������ཻ���
    testFrustumSphere();

    // ��׶���AABB�ཻ���
    testFrustumAabb();

    // ��׶���OBB�ཻ���
    testFrustumObb();

    return true;
}

void IntersectionApp::applicationDidEnterBackground()
{
}

void IntersectionApp::applicationWillEnterForeground()
{
}

void IntersectionApp::applicationWillTerminate()
{

}

void IntersectionApp::applicationLowMemory()
{

}

void IntersectionApp::testRayTriangle()
{
    // λ�� (0, 0, 5) λ����㣬���� -Z ���������
    Ray ray(
        Vector3(REAL_ZERO, REAL_ZERO, Real(5)),
        Vector3::NEGATIVE_UNIT_Z * Real(1000));

    // Triangle #0
    Triangle triangle0(TriangleVertices0);

    // ���Ray��Triangle���ཻ��
    IntrRayTriangle intr(ray, triangle0);
    bool isIntersection = intr.test();
    printf("Ray and Triangle #0 intersection result is %d\n", isIntersection);

    // Triangle #1
    Triangle triangle1(TriangleVertices1);

    // ���Ray��Triangle�ǲ��ཻ��
    intr.setTriangle(&triangle1);
    isIntersection = intr.test();
    printf("Ray and Triangle #1 intersection result is %d\n", isIntersection);
}

void IntersectionApp::testRayPlane()
{
    // λ�� (0, 0, 5) λ����㣬���� -Z ���������
    Ray ray(
        Vector3(REAL_ZERO, REAL_ZERO, Real(5)),
        Vector3::NEGATIVE_UNIT_Z * Real(1000));

    // Plane #0
    Plane plane0(
        TriangleVertices0[0], 
        TriangleVertices0[1], 
        TriangleVertices0[2]);

    // ���Ray��Plane���ཻ��
    IntrRayPlane intr(ray, plane0);
    bool isIntersection = intr.test();
    printf("Ray and Plane #0 intersection result is %d\n", isIntersection);

    // Plane #1
    Plane plane1(
        Vector3(Real(4), REAL_ONE, REAL_ONE), 
        Vector3(Real(4), -REAL_ONE, REAL_ZERO),
        Vector3(Real(4), REAL_ONE, REAL_ZERO));

    // ���Ray��Plane�ǲ��ཻ��
    intr.setPlane(&plane1);
    isIntersection = intr.test();
    printf("Ray and Plane #1 intersection result is %d\n", isIntersection);
}

void IntersectionApp::testRaySphere()
{
    // λ�� (0, 0, 5) λ����㣬���� -Z ���������
    Ray ray(
        Vector3(REAL_ZERO, REAL_ZERO, Real(5)),
        Vector3::NEGATIVE_UNIT_Z * Real(1000));

    // Sphere #0
    Sphere sphere0;
    sphere0.build(BoxVertices0, BoxVerticesCount);

    // ���Ray��Sphere���ཻ��
    IntrRaySphere intr(ray, sphere0);
    bool isIntersection = intr.test();
    printf("Ray and Sphere #0 intersection result is %d\n", isIntersection);

    // Sphere #1
    Sphere sphere1;
    sphere1.build(BoxVertices1, BoxVerticesCount);

    // ���Ray��Sphere�ǲ��ཻ��
    intr.setSphere(&sphere1);
    isIntersection = intr.test();
    printf("Ray and Sphere #1 intersection result is %d\n", isIntersection);
}


void IntersectionApp::testRayAabb()
{
    // λ�� (0, 0, 5) λ����㣬���� -Z ���������
    Ray ray(
        Vector3(REAL_ZERO, REAL_ZERO, Real(5)), 
        Vector3::NEGATIVE_UNIT_Z * Real(1000));

    // AABB #0
    Aabb box0;
    box0.build(BoxVertices0, BoxVerticesCount);

    // ���Ray��AABB���ཻ��
    IntrRayAabb intr(ray, box0);
    bool isIntersection = intr.test();
    printf("Ray and AABB #0 intersection result is %d\n", isIntersection);

    // AABB #1
    Aabb box1;
    box1.build(BoxVertices1, BoxVerticesCount);

    // ���Ray��AABB�ǲ��ཻ��
    intr.setAabb(&box1);
    isIntersection = intr.test();
    printf("Ray and AABB #1 intersection result is %d\n", isIntersection);
}

void IntersectionApp::testRayObb()
{
    // λ�� (0, 0, 5) λ����㣬���� -Z ���������
    Ray ray(
        Vector3(REAL_ZERO, REAL_ZERO, Real(5)),
        Vector3::NEGATIVE_UNIT_Z * Real(1000));

    // ������ת����
    Matrix3 m;
    m.fromAxisAngle(Vector3::UNIT_Y, Degree(30));

    Vector3 points[BoxVerticesCount];
    size_t i = 0;
    for (i = 0; i < BoxVerticesCount; ++i)
    {
        points[i] = m * BoxVertices0[i];
    }

    // OBB #0
    Obb box0;
    box0.build(points, BoxVerticesCount);
    
    // ���Ray��OBB���ཻ��
    IntrRayObb intr(ray, box0);
    bool isIntersection = intr.test();
    printf("Ray and OBB #0 intersection result is %d\n", isIntersection);

    for (i = 0; i < BoxVerticesCount; ++i)
    {
        points[i] = m * BoxVertices1[i];
    }

    // OBB #1
    Obb box1;
    box1.build(points, BoxVerticesCount);

    // ���Ray��OBB�ǲ��ཻ��
    intr.setObb(&box1);
    isIntersection = intr.test();
    printf("Ray and OBB #1 intersection result is %d\n", isIntersection);
}

void IntersectionApp::testSphereSphere()
{
    // Sphere #0
    Sphere sphere0;
    sphere0.build(BoxVertices0, BoxVerticesCount);

    // Sphere #1
    Sphere sphere1;
    sphere1.build(BoxVertices2, BoxVerticesCount);

    // ������sphere���ཻ��
    IntrSphereSphere intr(sphere0, sphere1);
    bool isIntersection = intr.test();
    printf("Sphere #0 and Sphere #1 intersection result is %d\n", isIntersection);

    // Sphere #2
    Sphere sphere2;
    sphere2.build(BoxVertices1, BoxVerticesCount);

    // ������sphere�ǲ��ཻ��
    intr.setSphere1(&sphere2);
    isIntersection = intr.test();
    printf("Sphere #0 and Sphere #2 intersection result is %d\n", isIntersection);
}

void IntersectionApp::testSpherePlane()
{
    // Sphere
    Sphere sphere;
    sphere.build(BoxVertices0, BoxVerticesCount);

    // Plane #0
    Plane plane0(
        TriangleVertices0[0],
        TriangleVertices0[1],
        TriangleVertices0[2]);

    // ���Sphere��Plane���ཻ��
    IntrSpherePlane intr(sphere, plane0);
    int32_t isIntersection = intr.test();
    printf("Sphere and Plane #0 intersection result is %d\n", isIntersection);

    // Plane #1
    Plane plane1(
        Vector3(Real(4), REAL_ONE, REAL_ONE),
        Vector3(Real(4), -REAL_ONE, REAL_ZERO),
        Vector3(Real(4), REAL_ONE, REAL_ZERO));

    // ���Sphere��Plane�ǲ��ཻ��
    intr.setPlane(&plane1);
    isIntersection = intr.test();
    printf("Sphere and Plane #1 intersection result is %d\n", isIntersection);
}

void IntersectionApp::testAabbPlane()
{
    // Box
    Aabb box;
    box.build(BoxVertices0, BoxVerticesCount);

    // Plane #0
    Plane plane0(
        TriangleVertices0[0],
        TriangleVertices0[1],
        TriangleVertices0[2]);

    // ���AABB��Plane���ཻ��
    IntrAabbPlane intr(box, plane0);
    int32_t isIntersection = intr.test();
    printf("AABB and Plane #0 intersection result is %d\n", isIntersection);

    // Plane #1
    Plane plane1(
        Vector3(Real(4), REAL_ONE, REAL_ONE),
        Vector3(Real(4), -REAL_ONE, REAL_ZERO),
        Vector3(Real(4), REAL_ONE, REAL_ZERO));

    // ���AABB��Plane�ǲ��ཻ��
    intr.setPlane(&plane1);
    isIntersection = intr.test();
    printf("AABB and Plane #1 intersection result is %d\n", isIntersection);
}

void IntersectionApp::testObbPlane()
{
    // ������ת����
    Matrix3 m;
    m.fromAxisAngle(Vector3::UNIT_Y, Degree(30));

    Vector3 points[BoxVerticesCount];
    size_t i = 0;
    for (i = 0; i < BoxVerticesCount; ++i)
    {
        points[i] = m * BoxVertices0[i];
    }

    // OBB
    Obb box;
    box.build(points, BoxVerticesCount);

    // Plane #0
    Plane plane0(
        TriangleVertices0[0],
        TriangleVertices0[1],
        TriangleVertices0[2]);

    // ���OBB��Plane���ཻ��
    IntrObbPlane intr(box, plane0);
    int32_t isIntersection = intr.test();
    printf("OBB and Plane #0 intersection result is %d\n", isIntersection);

    // Plane #1
    Plane plane1(
        Vector3(Real(5), REAL_ONE, REAL_ONE),
        Vector3(Real(5), -REAL_ONE, REAL_ZERO),
        Vector3(Real(5), REAL_ONE, REAL_ZERO));

    // ���OBB��Plane�ǲ��ཻ��
    intr.setPlane(&plane1);
    isIntersection = intr.test();
    printf("OBB and Plane #1 intersection result is %d\n", isIntersection);
}

void IntersectionApp::testFrustumSphere()
{
    Frustum frustum;
    buildFrustum(frustum);

    // Sphere #0
    Sphere sphere0;
    sphere0.build(BoxVertices0, BoxVerticesCount);

    // ���Frustum��Sphere���ཻ��
    IntrFrustumSphere intr(frustum, sphere0);
    bool isIntersection = intr.test();
    printf("Frustum and Sphere #0 intersection result is %d\n", isIntersection);

    // Sphere #1
    Sphere sphere1;
    sphere1.build(BoxVertices3, BoxVerticesCount);

    // ���Frustum��Sphere�ǲ��ཻ��
    intr.setSphere(&sphere1);
    isIntersection = intr.test();
    printf("Frustum and Sphere #1 intersection result is %d\n", isIntersection);
}

void IntersectionApp::testFrustumAabb()
{
    Frustum frustum;
    buildFrustum(frustum);

    // AABB #0
    Aabb box0;
    box0.build(BoxVertices0, BoxVerticesCount);

    // ���Frustum��AABB���ཻ��
    IntrFrustumAabb intr(frustum, box0);
    bool isIntersection = intr.test();
    printf("Frustum and AABB #0 intersection result is %d\n", isIntersection);

    // AABB #1
    Aabb box1;
    box1.build(BoxVertices3, BoxVerticesCount);

    // ���Frustum��Sphere�ǲ��ཻ��
    intr.setBox(&box1);
    isIntersection = intr.test();
    printf("Frustum and AABB #1 intersection result is %d\n", isIntersection);
}

void IntersectionApp::testFrustumObb()
{
    Frustum frustum;
    buildFrustum(frustum);

    // ������ת����
    Matrix3 m;
    m.fromAxisAngle(Vector3::UNIT_Y, Degree(30));

    Vector3 points[BoxVerticesCount];
    size_t i = 0;
    for (i = 0; i < BoxVerticesCount; ++i)
    {
        points[i] = m * BoxVertices0[i];
    }

    // OBB #0
    Obb box0;
    box0.build(points, BoxVerticesCount);

    // ���Frustum��AABB���ཻ��
    IntrFrustumObb intr(frustum, box0);
    bool isIntersection = intr.test();
    printf("Frustum and OBB #0 intersection result is %d\n", isIntersection);

    for (i = 0; i < BoxVerticesCount; ++i)
    {
        points[i] = m * BoxVertices3[i];
    }

    // OBB #1
    Obb box1;
    box1.build(points, BoxVerticesCount);

    // ���Frustum��Sphere�ǲ��ཻ��
    intr.setBox(&box1);
    isIntersection = intr.test();
    printf("Frustum and OBB #1 intersection result is %d\n", isIntersection);
}

void IntersectionApp::buildFrustum(Frustum &frustum)
{
    // ����Frustum������ƽ��

    // ��ƽ��
    Plane near(Vector3::NEGATIVE_UNIT_Z, Vector3(0, 0, 10));

    // Զƽ��
    Plane far(Vector3::UNIT_Z, Vector3(0, 0, -10));

    // ��ƽ��
    Matrix3 m0(Vector3::UNIT_X, Radian(Math::PI / Real(6.0f)));
    Vector3 axis0 = m0 * Vector3::NEGATIVE_UNIT_Y;
    Plane top(axis0, Vector3(0, 10, 0));

    // ��ƽ��
    Matrix3 m1(Vector3::UNIT_X, -Radian(Math::PI / Real(6.0f)));
    Vector3 axis1 = m1 * Vector3::UNIT_Y;
    Plane bottom(axis1, Vector3(0, -10, 0));

    // ��ƽ��
    Matrix3 m2(Vector3::UNIT_Y, Radian(Math::PI / Real(6.0f)));
    Vector3 axis2 = m2 * Vector3::UNIT_X;
    Plane left(axis2, Vector3(-10, 0, 0));

    // ��ƽ��
    Matrix3 m3(Vector3::UNIT_Y, -Radian(Math::PI / Real(6.0f)));
    Vector3 axis3 = m2 * Vector3::NEGATIVE_UNIT_X;
    Plane right(axis3, Vector3(10, 0, 0));

    // Frustum
    frustum.setFace(Frustum::E_FACE_NEAR, near);
    frustum.setFace(Frustum::E_FACE_FAR, far);
    frustum.setFace(Frustum::E_FACE_TOP, top);
    frustum.setFace(Frustum::E_FACE_BOTTOM, bottom);
    frustum.setFace(Frustum::E_FACE_LEFT, left);
    frustum.setFace(Frustum::E_FACE_RIGHT, right);
}
