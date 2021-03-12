/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2019  Answer Wong
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


#include "T3DR3DRenderer.h"
#include "T3DR3DRenderWindow.h"
#include "T3DR3DHardwareBufferManager.h"
#include "T3DR3DError.h"
#include "T3DR3DFramebuffer.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    R3DRendererPtr R3DRenderer::create()
    {
        R3DRendererPtr renderer = new R3DRenderer();
        renderer->release();
        return renderer;
    }

    //--------------------------------------------------------------------------

    R3DRenderer::R3DRenderer()
        : Renderer()
        , mFramebuffer(nullptr)
        , mRenderWindow(nullptr)
        , mHardwareBufferMgr(nullptr)
        , mR3DHardwareBufferMgr(nullptr)
        , mFrustumBound(nullptr)
    {
        mName = Renderer::REFERENCE3D;
    }

    R3DRenderer::~R3DRenderer()
    {
        mHardwareBufferMgr = nullptr;
        mR3DHardwareBufferMgr = nullptr;
        mRenderWindow = nullptr;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::init()
    {
        mR3DHardwareBufferMgr = R3DHardwareBufferManager::create();
        mHardwareBufferMgr
            = HardwareBufferManager::create(mR3DHardwareBufferMgr);

        size_t i = 0;

        for (i = 0; i < MAX; ++i)
        {
            mMatrices[i].makeIdentity();
        }

        return T3D_OK;
    }

    TResult R3DRenderer::destroy()
    {
        mHardwareBufferMgr = nullptr;
        mR3DHardwareBufferMgr = nullptr;
        mRenderWindow = nullptr;
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    RenderWindowPtr R3DRenderer::createRenderWindow(
        const String &name,
        const RenderWindowCreateParam &param,
        const RenderWindowCreateParamEx &paramEx)
    {
        TResult ret = T3D_OK;

        RenderWindowPtr window = nullptr;

        do 
        {
            window = R3DRenderWindow::create(name);
            if (window == nullptr)
            {
                T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Create render window \
                    failed !");
                break;
            }

            ret = window->create(param, paramEx);
            if (ret != T3D_OK)
            {
                window->release();
                window = nullptr;
                break;
            }

            mRenderWindow = window;
        } while (0);

        return window;
    }

    //--------------------------------------------------------------------------

    bool R3DRenderer::queryCapability(Capability cap) const
    {
        return false;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::setTransform(TransformState state, const Matrix4 &mat)
    {
        mMatrices[state] = mat;
        return T3D_OK;
    }

    const Matrix4 &R3DRenderer::getTransform(TransformState state) const
    {
        return mMatrices[state];
    }

    //--------------------------------------------------------------------------

    Matrix4 R3DRenderer::perspective(const Radian &fovY, Real aspect,
        Real nearDist, Real farDist)
    {
        // Reference3D NDC (Normalized Device Coordinates) is : 
        //      [left, right] => [-1, 1] => l <= x <= r
        //      [bottom, top] => [-1, 1] => b <= y <= t
        //      [near, far] => [0, 1]    => -n <= z <= -f (Right Hand)
        //
        //  由正交投影矩阵推导过程可得：
        //      x' = 2x/(r-l) - (r+l)/(r-l)                 (1)
        //      y' = 2y/{t-b) - (t+b)/(t-b)                 (2)
        //
        //  根据相似三角形可得：
        //      x0 = nx/-z
        //      y0 = ny/-z
        //
        //  把 x0 和 y0 代入 (1)、(2) 式中的 x 和 y，可得：
        //      x' = (2nx/(r-l))/(-z) + ((r+l)z/(r-l))/(-z) (3)
        //      y' = (2ny/(t-b))/(-z) + ((t+b)z/(t-b))/(-z) (4)
        //
        //  当 z=-n 时 z'=0，当 z=-f 时 z'=1，即 -n <= z <= -f
        //  而 -zz' 和 z 是一种线性关系，即 
        //      z' = (pz + q) / -z                          (5)
        //  
        //  分别把 z'=0 和 z'=1 代入到 (5) 可得：
        //      0 = -pn + q                                 (6)
        //      f = -pf + q                                 (7)
        //  把 (6) 和 (7) 联列方程组可解得：
        //      p = f/(n-f)
        //      q = nf/(n-f)
        //
        //  考虑齐次坐标的w，通常情况下，如正交投影的时候w简单的等于-1，而现在
        //  我们需要为点 (-zx', -zy', -zz', -zw') 写一个变换，所以取而代之的是
        //  把 w'=1 写成：
        //      -zw' = z                                    (8)
        //
        //  最后把 p 和 q 代入等式 (5) 与等式 (3)、(4)、(8) 列方程组可得：
        //      x' = (2nx/(r-l))/(-z) + ((r+l)z/(r-l))/(-z)
        //      y' = (2ny/(t-b))/(-z) + ((t+b)z/(t-b))/(-z)
        //      z' = (fz/(n-f))/(-z) + (nf/(n-f))/(-z)
        //      w' = -1
        //
        //  通过矩阵形式表达上述方程组，可得：
        //          | 2n/(r-l)    0     (r+l)/(r-l)    0     |
        //      M = |    0     2n/(t-b) (t+b)/(t-b)    0     |      [1]
        //          |    0        0       f/(n-f)   nf/(n-f) |
        //          |    0        0         -1         0     |
        //
        //  一般情况下，相机都看屏幕正中，所以左右对称，上下对称，则可简化为：
        //          | 2n/w  0      0       0     |
        //      M = |  0   2n/h    0       0     |                  [2]
        //          |  0    0   f/(n-f) nf/(n-f) |
        //          |  0    0     -1       0     |
        //
        //  fovY 是指 top 和 bottom 之间夹角，则：
        //      tan(fovY/2) = (h/2)/n
        //  aspect 是指宽高比，即：
        //      aspect = w/h
        //
        //  从上可得 ：
        //      h = 2 * n * tan(fovY/2)
        //      w = aspect * h
        //      w = aspect * 2 * n * tan(fovY/2)
        //
        //  把上述代入矩阵[2]，可得：
        //          | 1/(aspect*tan(fovY/2))       0          0       0     |
        //      M = |           0            1/tan(fovY/2)    0       0     |
        //          |           0                  0       f/(n-f) nf/(n-f) |
        //          |           0                  0         -1       0     |

        Radian radian = fovY * REAL_HALF;
        Real m11 = REAL_ONE / (Math::tan(radian));
        Real m00 = m11 / aspect;
        Real m22 = farDist / (nearDist - farDist);
        Real m23 = nearDist * m22;

        return Matrix4(
            m00, 0, 0, 0,
            0, m11, 0, 0,
            0, 0, m22, m23,
            0, 0, -1, 0);
    }

    //--------------------------------------------------------------------------

    Matrix4 R3DRenderer::orthographic(Real width, Real height, 
        Real nearDist, Real farDist)
    {
        // Reference3D 9 NDC (Normalized Device Coordinates) is : 
        //      [left, right] => [-1, 1] => l <= x <= r
        //      [bottom, top] => [-1, 1] => b <= y <= t
        //      [near, far] => [0, 1]    => -n <= z <= -f (Right Hand)
        // 
        //  由 l <= x <= r 
        //      => 0 <= x-l <= r-l 
        //      => 0 <= (x-l)/(r-l) <= 1 
        //      => 0 <= 2(x-l)/(r-) <= 2
        //      => 0 <= (2x-2l)/(r-l) <= 2
        //      => -1 <= (2x-2l)/(r-l)-1 <= 1
        //      => -1 <= (2x-r-l)/(r-l) <= 1
        //      => -1 <= 2x/(r-l)-(r+l)/(r-l) <= 1
        //  由上可得： x' = 2x/(r-l) - (r+l)/(r-l)       (1)
        //
        //  同理可得： y' = 2y/(t-b) - (t+b)/(t-b)       (2)
        //
        //  由 -n <= z <= -f
        //      => 0 <= z+n <= n-f
        //      => 0 <= (z+n)/(n-f> <= 1
        //      => 0 <= z/(n-f) + n/(n-f) <= 1
        //  由上可得： z' = z/(n-f) + n/(n-f)            (3)
        //
        //  由(1)、(2)和(3)等式构成方程组：
        //      x' = 2x/(r-l) - (r+l)/(r-l) 
        //      y' = 2y/(t-b) - (t+b)/(t-b)
        //      z' = z/(n-f) + n/(n-f)
        //
        //  由方程组可得矩阵：
        //          | 2/(r-l)    0       0    -(r+l)/(r-l) |
        //      M = |    0    2/(t-b)    0    -(t+b)/(t-b) |        [1]
        //          |    0       0    1/(n-f)    n/(n-f)   |
        //          |    0       0       0          1      |
        //
        //  一般情况下，相机都看屏幕正中，所以左右对称，上下对称，则可简化为：
        //          | 2/w  0     0       0    |
        //      M = |  0  2/h    0       0    |                     [2]
        //          |  0   0  f/(n-f) n/(n-f) |
        //          |  0   0     0       1    |
        //

        Real invert0 = REAL_ONE / width;
        Real m00 = Real(2.0) * invert0;
        Real invert1 = REAL_ONE / height;
        Real m11 = Real(2.0) * invert1;
        Real m22 = REAL_ONE / (nearDist - farDist);
        Real m23 = nearDist * m22;

        return Matrix4(
            m00, 0, 0, 0,
            0, m11, 0, 0,
            0, 0, m22, m23,
            0, 0, 0, 1);
    }

    //--------------------------------------------------------------------------

    Matrix4 R3DRenderer::makeViewportMatrix(ViewportPtr viewport)
    {
        Real m00 = Real(viewport->getActualWidth()) * REAL_HALF;
        Real m11 = -Real(viewport->getActualHeight()) * REAL_HALF;
        Real m22 = REAL_ONE;
        Real m33 = REAL_ONE;
        Real m03 = Real(viewport->getActualLeft()) + Real(viewport->getActualWidth()) * REAL_HALF;
        Real m13 = Real(viewport->getActualTop()) + Real(viewport->getActualHeight()) * REAL_HALF;
        Real m23 = REAL_ONE;
        return Matrix4(
            m00,   0,   0, m03,
              0, m11,   0, m13,
              0,   0, m22, m23,
              0,   0,   0, m33);
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::updateFrustum(const Matrix4 &m, FrustumBoundPtr bound)
    {
        // 快速计算视棱锥六个裁剪平面原理：
        //
        //  假设点V'是投影变换后的点，V是投影变换前相机坐标系的点，M是投影变换矩阵，则可得：
        //      V' = M * V
        //  其中
        //      V' = (x' y' z' w')
        //
        //      V = (x y z w), (w = 1)
        //
        //          | m00 m01 m02 m03 |
        //      M = | m10 m11 m12 m13 |
        //          | m20 m21 m22 m23 |
        //          | m30 m31 m32 m33 |
        //  则
        //      | m00 m01 m02 m03 |   | x |   | x*m00 + y*m01 + z*m02 + w*m03 |   | V * row0 |
        //      | m10 m11 m12 m13 |   | y |   | x*m10 + y*m11 + z*m12 + w*m13 |   | V * row1 |
        //      | m20 m21 m22 m23 | * | z | = | x*m20 + y*m21 + z*m22 + w*m23 | = | V * row2 |
        //      | m30 m31 m32 m33 |   | w |   | x*m30 + y*m31 + z*m32 + w*m33 |   | V * row3 |
        //
        //  这里的*代表点积，而rowi = (mi0 mi1 mi2 mi3)
        // 
        //  经过转换后，V'在齐次裁剪空间里。这个空间实际上现在已经是一个轴对齐的盒子。
        //  如果V'在这个盒子空间里，则变换前的V点也在这个没有经过变换的盒子空间里。
        //  
        //  在 Reference3D 里，V'在这个空间里，则符合下面的不等式规则
        //              -w' < x' < w'
        //              -w' < y' < w'
        //               0 < z' < w'
        //          用 -w' < x' 推导：
        //              -(V * row3) < (V * row0)
        //          移动项得：
        //              0 < (V * row3) + (V * row0)
        //          合并同类项，最终可得：
        //              0 < V * (row3 + row0)
        //
        //          如此类推可得：
        //              left    :   0 < V * (row3 + row0)   
        //                          a=m30+m00, b=m31+m01, c=m32+m02, d=m33+m03
        //              right   :   0 < V * (row3 - row0)   
        //                          a=m30-m00, b=m31-m01, c=m32-m02, d=m33-m03
        //              bottom  :   0 < V * (row3 + row1)   
        //                          a=m30+m10, b=m31+m11, c=m32+m12, d=m33+m13
        //              top     :   0 < V * (row3 - row1)   
        //                          a=m30-m10, b=m31-m11, c=m32-m12, d=m33-m13
        //              near    :   0 < V * row2            
        //                          a=m20,     b=m21,     c=m22,     d=m23
        //              far     :   0 < V * (row3 - row2)   
        //                          a=m30-m20, b=m31-m21, c=m32-m22, d=m33-m23
        //

        Plane plane[Frustum::E_MAX_FACE];

        // Left
        plane[Frustum::E_FACE_LEFT][0] = m[3][0] + m[0][0];
        plane[Frustum::E_FACE_LEFT][1] = m[3][1] + m[0][1];
        plane[Frustum::E_FACE_LEFT][2] = m[3][2] + m[0][2];
        plane[Frustum::E_FACE_LEFT][3] = m[3][3] + m[0][3];
        plane[Frustum::E_FACE_LEFT].normalize();

        // Right
        plane[Frustum::E_FACE_RIGHT][0] = m[3][0] - m[0][0];
        plane[Frustum::E_FACE_RIGHT][1] = m[3][1] - m[0][1];
        plane[Frustum::E_FACE_RIGHT][2] = m[3][2] - m[0][2];
        plane[Frustum::E_FACE_RIGHT][3] = m[3][3] - m[0][3];
        plane[Frustum::E_FACE_RIGHT].normalize();

        // Bottom
        plane[Frustum::E_FACE_BOTTOM][0] = m[3][0] + m[1][0];
        plane[Frustum::E_FACE_BOTTOM][1] = m[3][1] + m[1][1];
        plane[Frustum::E_FACE_BOTTOM][2] = m[3][2] + m[1][2];
        plane[Frustum::E_FACE_BOTTOM][3] = m[3][3] + m[1][3];
        plane[Frustum::E_FACE_BOTTOM].normalize();

        // Top
        plane[Frustum::E_FACE_TOP][0] = m[3][0] - m[1][0];
        plane[Frustum::E_FACE_TOP][1] = m[3][1] - m[1][1];
        plane[Frustum::E_FACE_TOP][2] = m[3][2] - m[1][2];
        plane[Frustum::E_FACE_TOP][3] = m[3][3] - m[1][3];
        plane[Frustum::E_FACE_TOP].normalize();

        // Near
        plane[Frustum::E_FACE_NEAR][0] = m[2][0];
        plane[Frustum::E_FACE_NEAR][1] = m[2][1];
        plane[Frustum::E_FACE_NEAR][2] = m[2][2];
        plane[Frustum::E_FACE_NEAR][3] = m[2][3];
        plane[Frustum::E_FACE_NEAR].normalize();

        // Far
        plane[Frustum::E_FACE_FAR][0] = m[3][0] - m[2][0];
        plane[Frustum::E_FACE_FAR][1] = m[3][1] - m[2][1];
        plane[Frustum::E_FACE_FAR][2] = m[3][2] - m[2][2];
        plane[Frustum::E_FACE_FAR][3] = m[3][3] - m[2][3];
        plane[Frustum::E_FACE_FAR].normalize();

        bound->setFrustumFaces(plane, Frustum::E_MAX_FACE);

        if (mFrustumBound != bound)
            mFrustumBound = bound;

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::setCullingMode(CullingMode mode)
    {
        mCullingMode = mode;
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::setPolygonMode(PolygonMode mode)
    {
        mPolygonMode = mode;
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::setViewport(ViewportPtr viewport)
    {
        mViewport = viewport;
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::setMaterial(MaterialPtr material)
    {
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::drawVertexArray(VertexArrayObjectPtr vao)
    {
        TResult ret = T3D_OK;

        size_t indexCount = 0;
        uint8_t *indices = nullptr;
        bool is16Bits = false;

        if (vao->isIndicesUsed())
        {
            auto ibo = vao->getIndexBuffer();
            indexCount = ibo->getIndexCount();
            indices = (uint8_t*)ibo->lock(
                HardwareBuffer::LockOptions::READ);
            is16Bits 
                = (ibo->getIndexType()==HardwareIndexBuffer::Type::E_IT_16BITS);
        }

        Vertex *vertices = nullptr;

        do 
        {
            mMV = mMatrices[TransformState::VIEW] 
                * mMatrices[TransformState::WORLD];
            mMVP = mMatrices[TransformState::PROJECTION]
                * mMatrices[TransformState::VIEW]
                * mMatrices[TransformState::WORLD];

            auto vbo = vao->getVertexBuffer(0);
            size_t vertexCount = vbo->getVertexCount();
            vertices = new Vertex[vertexCount];

            ret = processVertices(vao, vertices, vertexCount);
            if (ret != T3D_OK)
            {
                break;
            }

            PrimitiveType primitive = vao->getPrimitiveType();

            switch (primitive)
            {
            case Renderer::E_PT_POINT_LIST:
                {
                    // Point list
                    ret = processPointList(vertices, vertexCount, indices, 
                        indexCount, is16Bits);
                }
                break;
            case Renderer::E_PT_LINE_LIST:
                {
                    // Line list
                    
                }
                break;
            case Renderer::E_PT_LINE_STRIP:
                {
                    // Line strip
                }
                break;
            case Renderer::E_PT_TRIANGLE_LIST:
                {
                    // Triangle list
                }
                break;
            case Renderer::E_PT_TRIANGLE_STRIP:
                {
                    // Triangle strip
                }
                break;
            case Renderer::E_PT_TRIANGLE_FAN:
                {
                    // Triangle fan
                }
                break;
            default:
                {
                    T3D_LOG_ERROR(LOG_TAG_R3DRENDERER, "Unsupported primitive type !");
                    ret = T3D_ERR_R3D_INVALID_PRIMITIVE;
                }
                break;
            }
        } while (0);

        T3D_SAFE_DELETE_ARRAY(vertices);

        if (vao->isIndicesUsed())
        {
            auto ibo = vao->getIndexBuffer();
            ibo->unlock();
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::drawVertexList(PrimitiveType priType, 
        VertexDeclarationPtr decl, HardwareVertexBufferPtr vbo)
    {
        VertexArrayObjectPtr vao 
            = T3D_HARDWARE_BUFFER_MGR.createVertexArrayObject(false);

        vao->setPrimitiveType(priType);
        vao->setVertexDeclaration(decl);
        vao->addVertexBuffer(vbo);

        return drawVertexArray(vao);
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::drawIndexList(PrimitiveType priType, 
        VertexDeclarationPtr decl, HardwareVertexBufferPtr vbo, 
        HardwareIndexBufferPtr ibo)
    {
        VertexArrayObjectPtr vao
            = T3D_HARDWARE_BUFFER_MGR.createVertexArrayObject(true);

        vao->setPrimitiveType(priType);
        vao->setVertexDeclaration(decl);
        vao->addVertexBuffer(vbo);
        vao->setIndexBuffer(ibo);

        return drawVertexArray(vao);
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::processVertices(VertexArrayObjectPtr vao, 
        Vertex *vertices, size_t vertexCount)
    {
        TResult ret = T3D_OK;

        struct BufferInfo
        {
            uint8_t *buffer;
            size_t  vertexSize;
            size_t  vertexCount;
        };

        TArray<BufferInfo> buffers(vao->getVertexBufferCount());
        size_t i = 0;
        for (i = 0; i < vao->getVertexBufferCount(); ++i)
        {
            auto vbo = vao->getVertexBuffer(0);

            BufferInfo info;
            info.buffer = (uint8_t*)vbo->lock(
                HardwareBuffer::LockOptions::READ);
            info.vertexSize = vbo->getVertexSize();
            info.vertexCount = vbo->getVertexCount();
            if (info.vertexCount != vertexCount)
            {
                ret = T3D_ERR_R3D_MISMATCH_VERTEX_COUNT;
                break;
            }
            buffers.push_back(info);
        }

        if (ret == T3D_OK)
        {
            VertexDeclarationPtr decl = vao->getVertexDeclaration();

            const VertexDeclaration::VertexAttriList &attributes
                = decl->getAttributes();

            auto itr = attributes.begin();
            while (itr != attributes.end())
            {
                auto attr = *itr;
                size_t idx = attr.getStream();
                auto info = buffers[idx];
                processVertices(info.buffer, info.vertexSize, attr, vertices,
                    vertexCount);

                ++itr;
            }
        }

        for (i = 0; i < vao->getVertexBufferCount(); ++i)
        {
            auto vbo = vao->getVertexBuffer(0);
            vbo->unlock();
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::processVertices(uint8_t *buffer, size_t vertexSize,
        const VertexAttribute &attr, Vertex *vertices, size_t vertexCount)
    {
        TResult ret = T3D_OK;

        size_t start = 0;
        size_t srcOffset = attr.getOffset();
        size_t size = attr.getSize();
        size_t idx = 0;
        size_t dstOffset = 0;
        size_t dstVertexSize = sizeof(Vertex);
        bool needTransform = false;

        switch (attr.getSemantic())
        {
        case VertexAttribute::Semantic::E_VAS_POSITION:
            dstOffset = 0;
            needTransform = true;
            break;
        case VertexAttribute::Semantic::E_VAS_NORMAL:
            dstOffset = sizeof(Vector4);
            needTransform = true;
            break;
        case VertexAttribute::Semantic::E_VAS_DIFFUSE:
            dstOffset = sizeof(Vector4) + sizeof(Vector4) + sizeof(Vector2);
            break;
        case VertexAttribute::Semantic::E_VAS_SPECULAR:
            dstOffset = sizeof(Vector4) + sizeof(Vector4) + sizeof(Vector2)
                + sizeof(ColorRGB);
            break;
        case VertexAttribute::Semantic::E_VAS_TEXCOORD:
            dstOffset = sizeof(Vector4) + sizeof(Vector4);
            break;
        }

        size_t i = 0;

        for (i = 0; i < vertexCount; ++i)
        {
            size_t offset = start + srcOffset;

            if (VertexAttribute::Semantic::E_VAS_POSITION == attr.getSemantic())
            {
                memcpy(&vertices[i].pos, &buffer[offset], sizeof(Real) * 3);
                vertices[i].pos.w() = REAL_ONE;
                vertices[i].pos = mMVP * vertices[i].pos;
            }
            else if (VertexAttribute::Semantic::E_VAS_NORMAL == attr.getSemantic())
            {
                memcpy(&vertices[i].normal, &buffer[offset], sizeof(Real) * 3);
                vertices[i].normal.w() = REAL_ZERO;
                vertices[i].normal = mMV * vertices[i].normal;
                vertices[i].normal.normalize();
            }
            else
            {
                memcpy(&vertices[dstOffset], &buffer[offset], size);
            }

            vertices += dstVertexSize;
            start += size;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::processPointList(Vertex *vertices, size_t vertexCount,
        uint8_t *indices, size_t indexCount, bool is16Bits)
    {
        TResult ret = T3D_OK;

        if (indexCount == 0 || indices == nullptr)
        {
            // 不使用顶点索引
            Vertex *verts = nullptr;
            size_t vertCount = 0;

            // 视锥体裁剪
            clipPointList(vertices, vertexCount, verts, vertCount);

            // 光栅化
            rasterPointList(verts, vertCount);

            T3D_SAFE_DELETE_ARRAY(verts);
        }
        else
        {
            // 使用顶点索引
            uint8_t *dstIndices = nullptr;
            size_t dstIndexCount = 0;

            // 视锥体裁剪
            clipIndexPointList(vertices, vertexCount, indices, indexCount,
                dstIndices, dstIndexCount, is16Bits);

            // 光栅化
            rasterIndexPointList(vertices, vertexCount, 
                dstIndices, dstIndexCount, is16Bits);

            T3D_SAFE_DELETE_ARRAY(dstIndices);
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::clipPointList(Vertex *srcVerts, size_t srcVertCount, 
        Vertex *&dstVerts, size_t &dstVertCount)
    {
        TResult ret = T3D_OK;

        dstVerts = new Vertex[srcVertCount];
        dstVertCount = 0;
        size_t i = 0;

        IntrPointFrustum intr;
        const Frustum &frustum = mFrustumBound->getFrustum();
        intr.setFrustum(&frustum);

        for (i = 0; i < srcVertCount; ++i)
        {
            const Vector4 &pt = srcVerts[i].pos;
            Vector3 pos(pt.x(), pt.y(), pt.z());
            intr.setPoint(&pos);
            if (intr.test())
            {
                // 在视锥体内，不用裁剪
                dstVerts[dstVertCount] = srcVerts[i];

                // 除 w ，转到 NDC
                Vector4 &v = dstVerts[dstVertCount].pos;
                v /= v.w();
                dstVertCount++;
            }
            else
            {
                // 裁减掉
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::clipIndexPointList(Vertex *vertices,
        size_t vertexCount, uint8_t *srcIndices, size_t srcIdxCount,
        uint8_t *&dstIndices, size_t &dstIdxCount, bool is16Bits)
    {
        TResult ret = T3D_OK;

        if (is16Bits)
        {
            uint16_t *indices = new uint16_t[srcIdxCount];
            dstIndices = (uint8_t*)indices;
            size_t i = 0;
            uint16_t *srcIdx = (uint16_t*)srcIndices;
            dstIdxCount = 0;

            IntrPointFrustum intr;
            const Frustum &frustum = mFrustumBound->getFrustum();
            intr.setFrustum(&frustum);

            for (i = 0; i < srcIdxCount; ++i)
            {
                uint16_t index = srcIdx[i];
                const Vector4 &pt = vertices[index].pos;
                Vector3 pos(pt.x(), pt.y(), pt.z());
                intr.setPoint(&pos);

                if (intr.test())
                {
                    // 在视锥体内，不用裁剪
                    indices[dstIdxCount] = index;

                    // 除 w ，转到 NDC
                    Vector4 &p = vertices[index].pos;
                    p /= p.w();

                    dstIdxCount++;
                }
                else
                {
                    // 裁减掉
                }
            }
        }
        else
        {
            uint32_t *indices = new uint32_t[srcIdxCount];
            dstIndices = (uint8_t*)indices;
            size_t i = 0;
            uint32_t *srcIdx = (uint32_t*)srcIndices;
            dstIdxCount = 0;

            IntrPointFrustum intr;
            const Frustum &frustum = mFrustumBound->getFrustum();
            intr.setFrustum(&frustum);

            for (i = 0; i < srcIdxCount; ++i)
            {
                uint32_t index = srcIdx[i];
                const Vector4 &pt = vertices[index].pos;
                Vector3 pos(pt.x(), pt.y(), pt.z());
                intr.setPoint(&pos);

                if (intr.test())
                {
                    // 在视锥体内，不用裁剪
                    indices[dstIdxCount] = index;

                    // 除 w ，转到 NDC
                    Vector4 &p = vertices[index].pos;
                    p /= p.w();

                    dstIdxCount++;
                }
                else
                {
                    // 裁减掉
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::rasterPointList(Vertex *vertices, size_t vertexCount)
    {
        TResult ret = T3D_OK;

        const Matrix4 &matViewport = mViewport->getViewportMatrix();

        size_t i = 0;

        for (i = 0; i < vertexCount; ++i)
        {
            Vector4 pos = matViewport * vertices[i].pos;
            Point pt(size_t(pos.x()), size_t(pos.y()));
            mFramebuffer->drawPoint(pt, vertices[i].diffuse);
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult R3DRenderer::rasterIndexPointList(Vertex *vertices, 
        size_t vertexCount, uint8_t *indices, size_t indexCount, bool is16Bits)
    {
        TResult ret = T3D_OK;

        const Matrix4 &matViewport = mViewport->getViewportMatrix();

        size_t i = 0;

        if (is16Bits)
        {
            uint16_t *index = (uint16_t*)indices;

            for (i = 0; i < indexCount; ++i)
            {
                const Vertex &vertex = vertices[index[i]];
                Vector4 pos = matViewport * vertex.pos;
                Point pt(size_t(pos.x()), size_t(pos.y()));
                mFramebuffer->drawPoint(pt, vertex.diffuse);
            }
        }
        else
        {
            uint32_t *index = (uint32_t*)indices;

            for (i = 0; i < indexCount; ++i)
            {
                const Vertex &vertex = vertices[index[i]];
                Vector4 pos = matViewport * vertex.pos;
                Point pt(size_t(pos.x()), size_t(pos.y()));
                mFramebuffer->drawPoint(pt, vertex.diffuse);
            }
        }

        return ret;
    }
}
