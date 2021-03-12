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


#include "T3DD3D11Renderer.h"
#include "T3DD3D11RenderWindow.h"
#include "T3DD3D11HardwareBufferManager.h"
#include "T3DD3D11GPUProgram.h"
#include "T3DD3D11HardwareConstantBuffer.h"
#include "T3DD3D11Mappings.h"
#include "T3DD3D11VertexArrayObject.h"
#include "T3DD3D11HardwareVertexBuffer.h"
#include "T3DD3D11HardwareIndexBuffer.h"
#include "T3DD3D11HardwarePixelBuffer.h"
#include "T3DD3D11VertexDeclaration.h"
#include "T3DD3D11Capabilities.h"
#include "T3DD3D11Sampler.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(D3D11Renderer);
    T3D_IMPLEMENT_CLASS_1(D3D11Renderer, Renderer);

    //--------------------------------------------------------------------------

    D3D11RendererPtr D3D11Renderer::create()
    {
        D3D11RendererPtr renderer = new D3D11Renderer();
        renderer->release();
        return renderer;
    }

    //--------------------------------------------------------------------------

    D3D11Renderer::D3D11Renderer()
        : mInstance(nullptr)
        , mD3DDevice(nullptr)
        , mD3DDeviceContext(nullptr)
        , mD3DRState(nullptr)
        , mFeatureLevel(D3D_FEATURE_LEVEL_10_0)
        , mVendorID(0)
        , mIsRSStateDirty(false)
    {
        mName = Renderer::DIRECT3D11;
        memset(&mD3DRSDesc, 0, sizeof(mD3DRSDesc));
    }

    //--------------------------------------------------------------------------

    D3D11Renderer::~D3D11Renderer()
    {
        destroy();
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::init()
    {
        TResult ret = T3D_OK;

        do 
        {
            D3D11HardwareBufferManagerPtr mgr 
                = D3D11HardwareBufferManager::create();
            mHardwareBufferMgr = HardwareBufferManager::create(mgr);

            HRESULT hr = S_OK;

            // device flags
            UINT flags = 0;
#ifdef T3D_DEBUG
            flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

            // features level
            const UINT numLevels = 4;
            D3D_FEATURE_LEVEL featureLevels[numLevels] =
            {
                D3D_FEATURE_LEVEL_11_1,
                D3D_FEATURE_LEVEL_11_0,
                D3D_FEATURE_LEVEL_10_1,
                D3D_FEATURE_LEVEL_10_0,
            };

            D3D_FEATURE_LEVEL level;

            hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags, 
                featureLevels, numLevels, D3D11_SDK_VERSION, 
                &mD3DDevice, &level, &mD3DDeviceContext);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_CREATE_FAILED;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create ID3D11Device object failed ! DX ERROR : %d", hr);
                break;
            }

            mFeatureLevel = level;

            // Raster State
            ret = initD3DRasterizerState();
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Initialize D3D11 Rasterizer State failed !");
                break;
            }

            // 收集硬件和驱动信息
            ret = collectInformation();
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Collect information failed !");
                break;
            }

            ret = postInit();
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Post initialize failed !");
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::destroy()
    {
        TResult ret = T3D_OK;

        do 
        {
            mRenderTarget = nullptr;
            mCapabilities = nullptr;
            mPrimaryWindow = nullptr;
            mHardwareBufferMgr = nullptr;

            D3D_SAFE_RELEASE(mD3DRState);
            D3D_SAFE_RELEASE(mD3DDeviceContext);
            D3D_SAFE_RELEASE(mD3DDevice);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::renderAllTargets()
    {
        TResult ret = T3D_OK;

        do 
        {
            // 绑定内置常量缓冲区
            bindGPUConstantBuffer(0, mGPUBufferUpdateObject->getBufferImpl());
            bindGPUConstantBuffer(1, mGPUBufferUpdateFrame->getBufferImpl());
            bindGPUConstantBuffer(2, mGPUBufferUpdateRarely->getBufferImpl());

            ret = Renderer::renderAllTargets();

            // 清理 GPU 程序对象
            mBoundGPUProgram = nullptr;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    RenderWindowPtr D3D11Renderer::createRenderWindow(const String &name,
        const RenderWindowCreateParam &param,
        const RenderWindowCreateParamEx &paramEx)
    {
        TResult ret = T3D_OK;

        RenderWindowPtr window = nullptr;

        do
        {
            window = D3D11RenderWindow::create(name);
            if (window == nullptr)
            {
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER, 
                    "Create render window failed !");
                break;
            }

            ret = window->create(param, paramEx);
            if (T3D_FAILED(ret))
            {
                window->release();
                window = nullptr;
                break;
            }

            if (mPrimaryWindow == nullptr)
            {
                mPrimaryWindow = window;
                mCapabilities = createRendererCapabilities();
            }
            else
            {

            }
        } while (0);

        return window;
    }

    //--------------------------------------------------------------------------

    RendererCapabilitiesPtr D3D11Renderer::createRendererCapabilities() const
    {
        return D3D11Capabilities::create();
    }

    //--------------------------------------------------------------------------

    Matrix4 D3D11Renderer::perspective(const Radian &fovY, Real aspect,
        Real nearDist, Real farDist)
    {
        // Direct3D 9 NDC (Normalized Device Coordinates) is : 
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
            m00,   0,   0,   0,
              0, m11,   0,   0,
              0,   0, m22, m23,
              0,   0,  -1,   0);
    }

    //--------------------------------------------------------------------------

    Matrix4 D3D11Renderer::orthographic(Real width, Real height, 
        Real nearDist, Real farDist)
    {
        // Direct3D 9 NDC (Normalized Device Coordinates) is : 
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
        //          |  0   0  1/(n-f) n/(n-f) |
        //          |  0   0     0       1    |

        Real m00 = Real(2.0) / width;
        Real m11 = Real(2.0) / height;
        Real m22 = REAL_ONE / (nearDist - farDist);
        Real m23 = nearDist * m22;

        return Matrix4(
            m00,   0,   0,   0,
              0, m11,   0,   0,
              0,   0, m22, m23,
              0,   0,   0,   1);
    }

    //--------------------------------------------------------------------------

    Matrix4 D3D11Renderer::makeViewportMatrix(ViewportPtr viewport)
    {
        Matrix4 mat(false);
        mat[0][0] = Real(viewport->getActualWidth()) * REAL_HALF;
        mat[1][1] = -Real(viewport->getActualHeight()) * REAL_HALF;
        mat[2][2] = REAL_ONE;
        mat[3][3] = REAL_ONE;
        mat[0][3] = viewport->getActualLeft() 
            + viewport->getActualWidth() * REAL_HALF;
        mat[1][3] = viewport->getActualTop() 
            + viewport->getActualHeight() * REAL_HALF;
        mat[2][3] = REAL_ZERO;
        return mat;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::updateFrustum(const Matrix4 &m, FrustumBoundPtr bound)
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
        //  这里要分一下DX和OpenGL的区别，因为投影空间不一样：
        //
        //      1、在DX里，V'在这个空间里，则符合下面的不等式规则
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
        //              left    :   0 < V * (row3 + row0)   a=m30+m00, b=m31+m01, c=m32+m02, d=m33+m03
        //              right   :   0 < V * (row3 - row0)   a=m30-m00, b=m31-m01, c=m32-m02, d=m33-m03
        //              bottom  :   0 < V * (row3 + row1)   a=m30+m10, b=m31+m11, c=m32+m12, d=m33+m13
        //              top     :   0 < V * (row3 - row1)   a=m30-m10, b=m31-m11, c=m32-m12, d=m33-m13
        //              near    :   0 < V * row2            a=m20,     b=m21,     c=m22,     d=m23
        //              far     :   0 < V * (row3 - row2)   a=m30-m20, b=m31-m21, c=m32-m22, d=m33-m23
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

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::setCullingMode(CullingMode mode)
    {
        mD3DRSDesc.CullMode = D3D11Mappings::get(mode);
        mCullingMode = mode;
        mIsRSStateDirty = true;
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::setPolygonMode(PolygonMode mode)
    {
        mD3DRSDesc.FillMode = D3D11Mappings::get(mode);
        mPolygonMode = mode;
        mIsRSStateDirty = true;
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::setViewport(ViewportPtr viewport)
    {
        TResult ret = T3D_OK;

        do 
        {
            D3D11_VIEWPORT vp;
            vp.TopLeftX = float(viewport->getActualLeft());
            vp.TopLeftY = float(viewport->getActualTop());
            vp.Width = float(viewport->getActualWidth());
            vp.Height = float(viewport->getActualHeight());
            vp.MinDepth = 0.0f;
            vp.MaxDepth = 1.0f;

            mD3DDeviceContext->RSSetViewports(1, &vp);

            mViewport = viewport;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::bindGPUConstantBuffer(size_t slot,
        HardwareConstantBufferPtr buffer)
    {
        TResult ret = T3D_OK;

        do 
        {
            D3D11HardwareConstantBufferPtr d3dBuffer 
                = smart_pointer_cast<D3D11HardwareConstantBuffer>(buffer);
            ID3D11Buffer *pBuffer = d3dBuffer->getD3DBuffer();
            mD3DDeviceContext->VSSetConstantBuffers((UINT)slot, 1, 
                (ID3D11Buffer * const *)&pBuffer);

            mD3DDeviceContext->PSSetConstantBuffers((UINT)slot, 1,
                (ID3D11Buffer * const *)&pBuffer);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::bindGPUProgram(GPUProgramPtr program)
    {
        TResult ret = T3D_OK;

        do 
        {
            // Vertex Shader
            D3D11VertexShaderPtr vshader 
                = smart_pointer_cast<D3D11VertexShader>(
                    program->getVertexShader());
            mD3DDeviceContext->VSSetShader(vshader->getD3DShader(), nullptr, 0);

            // Pixel Shader
            D3D11PixelShaderPtr fshader = smart_pointer_cast<D3D11PixelShader>(
                program->getPixelShader());
            mD3DDeviceContext->PSSetShader(fshader->getD3DShader(), nullptr, 0);

            mBoundGPUProgram = program;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::bindTexture(TextureUnitPtr unit)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (unit == nullptr)
                break;

            TexturePtr texture = unit->getTexture();
            if (texture != nullptr)
            {
                D3D11HardwarePixelBufferPtr pbo
                    = smart_pointer_cast<D3D11HardwarePixelBuffer>(
                        texture->getPixelBuffer());

                ID3D11ShaderResourceView *pD3DSRView = pbo->getD3DSRView();
                mD3DDeviceContext->PSSetShaderResources(0, 1,
                    (ID3D11ShaderResourceView *const *)&pD3DSRView);
            }

            D3D11SamplerPtr sampler 
                = smart_pointer_cast<D3D11Sampler>(unit->getSampler());
            if (sampler != nullptr)
            {
                ID3D11SamplerState *pSampler = sampler->getD3DSamplerState();
                mD3DDeviceContext->PSSetSamplers(0, 1,
                    (ID3D11SamplerState *const *)&pSampler);
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::renderObject(VertexArrayObjectPtr vao)
    {
        TResult ret = T3D_OK;

        do 
        {
            // 按需更新 GPU 常量缓冲区内容
            if (mIsWorldMatrixDirty || mIsViewMatrixDirty || mIsProjMatrixDirty)
            {
                // 更新每个对象都可能需要更新的缓冲区
                updateBufferPerObject();
            }

            if (mIsViewMatrixDirty || mIsProjMatrixDirty)
            {
                // 更新每帧都可能需要更新的缓冲区
                updateBufferPerFrame();
            }

            if (mIsProjMatrixDirty)
            {
                // 更新很少需要跟新的缓冲区
                updateBufferRarely();
            }

            mIsWorldMatrixDirty = false;
            mIsViewMatrixDirty = false;
            mIsProjMatrixDirty = false;

            // 按需更新光栅化状态
            if (mIsRSStateDirty)
            {
                updateD3DRasterizerState();
                mIsRSStateDirty = false;
            }

            D3D11VertexArrayObjectPtr d3dVAO 
                = smart_pointer_cast<D3D11VertexArrayObject>(vao);

            // 设置图元
            PrimitiveType primitive = vao->getPrimitiveType();
            D3D11_PRIMITIVE_TOPOLOGY topology = D3D11Mappings::get(primitive);
            mD3DDeviceContext->IASetPrimitiveTopology(topology);

            // 顶点布局
            D3D11VertexDeclarationPtr decl = smart_pointer_cast<D3D11VertexDeclaration>(vao->getVertexDeclaration());
            D3D11VertexShaderPtr vshader = smart_pointer_cast<D3D11VertexShader>(mBoundGPUProgram->getVertexShader());
            ID3D11InputLayout *d3dLayout = decl->getD3DInputLayout(vshader);
            mD3DDeviceContext->IASetInputLayout(d3dLayout);

            // 顶点缓冲
            UINT numberOfBuffers = (UINT)d3dVAO->getVertexBufferCount();
            ID3D11Buffer * const * buffers = d3dVAO->getD3D11Buffers();
            UINT *strides = d3dVAO->getD3D11BufferStrides();
            UINT *offsets = d3dVAO->getD3D11BufferOffsets();
            mD3DDeviceContext->IASetVertexBuffers(0, numberOfBuffers,
                buffers, strides, offsets);

            if (vao->isIndicesUsed())
            {
                // 索引缓冲区
                D3D11HardwareIndexBufferPtr ibo = smart_pointer_cast<D3D11HardwareIndexBuffer>(vao->getIndexBuffer());
                ID3D11Buffer *d3dBuffer = ibo->getD3D11Buffer();
                DXGI_FORMAT idxFormat = D3D11Mappings::get(ibo->getIndexType());
                mD3DDeviceContext->IASetIndexBuffer(d3dBuffer, idxFormat, 0);

                // 绘制
                mD3DDeviceContext->DrawIndexed((UINT)ibo->getIndexCount(), 0, 0);
            }
            else
            {
                // 绘制
                mD3DDeviceContext->Draw((UINT)d3dVAO->getVertexCount(), 0);
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::initD3DRasterizerState()
    {
        TResult ret = T3D_OK;

        do 
        {
            D3D_SAFE_RELEASE(mD3DRState);

            HRESULT hr = S_OK;

            memset(&mD3DRSDesc, 0, sizeof(mD3DRSDesc));
            mD3DRSDesc.FillMode = D3D11Mappings::get(mPolygonMode);
            mD3DRSDesc.CullMode = D3D11Mappings::get(mCullingMode);
            mD3DRSDesc.FrontCounterClockwise = TRUE;
            mD3DRSDesc.DepthBias = 0;
            mD3DRSDesc.SlopeScaledDepthBias = 0.0f;
            mD3DRSDesc.DepthBiasClamp = 0.0f;
            mD3DRSDesc.DepthClipEnable = TRUE;
            mD3DRSDesc.ScissorEnable = FALSE;
            mD3DRSDesc.MultisampleEnable = FALSE;
            mD3DRSDesc.AntialiasedLineEnable = FALSE;

            hr = mD3DDevice->CreateRasterizerState(&mD3DRSDesc, &mD3DRState);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_CREATE_FAILED;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create ID3D11RasterizerState object failed ! DX ERROR : %d",
                    hr);
                break;
            }

            mD3DDeviceContext->RSSetState(mD3DRState);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::updateD3DRasterizerState()
    {
        TResult ret = T3D_OK;

        do 
        {
            D3D_SAFE_RELEASE(mD3DRState);

            HRESULT hr = S_OK;

            hr = mD3DDevice->CreateRasterizerState(&mD3DRSDesc, &mD3DRState);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_CREATE_FAILED;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Create ID3D11RasterizerState object failed ! DX ERROR : %d",
                    hr);
                break;
            }

            mD3DDeviceContext->RSSetState(mD3DRState);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult D3D11Renderer::collectInformation()
    {
        TResult ret = T3D_OK;

        IDXGIDevice *pDXGIDevice = nullptr;
        IDXGIAdapter *pDXGIAdapter = nullptr;

        do 
        {
            HRESULT hr = S_OK;
            hr = mD3DDevice->QueryInterface(__uuidof(IDXGIDevice),
                (void **)&pDXGIDevice);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_CREATE_FAILED;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Query interface for IDXGIDevice failed ! DX ERROR [%d]",
                    hr);
                break;
            }

            hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter),
                (void **)&pDXGIAdapter);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_GET_INTERFACE;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Get COM for IDXGIAdapter failed ! DX ERROR [%d]", hr);
                break;
            }

            // 获取驱动版本号
            LARGE_INTEGER driverVersion;
            hr = pDXGIAdapter->CheckInterfaceSupport(__uuidof(ID3D10Device),
                &driverVersion);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_CHECK_INTERFACE_SUPPORT;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Check interface support failed ! DX ERROR [%d]", hr);
                break;
            }

            mDriverVersion.major = HIWORD(driverVersion.HighPart);
            mDriverVersion.minor = LOWORD(driverVersion.HighPart);
            mDriverVersion.release = HIWORD(driverVersion.LowPart);
            mDriverVersion.build = LOWORD(driverVersion.LowPart);

            // 获取 GPU 信息
            DXGI_ADAPTER_DESC desc;
            hr = pDXGIAdapter->GetDesc(&desc);
            if (FAILED(hr))
            {
                ret = T3D_ERR_D3D11_GET_DRIVER_DESC;
                T3D_LOG_ERROR(LOG_TAG_D3D11RENDERER,
                    "Get adapter description failed ! DX ERROR [%d]", hr);
                break;
            }

            // 获取 GPU 名称
            char text[sizeof(desc.Description)+1];
            wcstombs(text, desc.Description, sizeof(text) - 1);
            String str(text);
            StringUtil::trim(str);
            mDeviceName = str;

            // 获取 GPU 制造商 ID
            mVendorID = desc.VendorId;

            // 构造信息并且输出
            std::stringstream ss;
            uint64_t high = desc.AdapterLuid.HighPart;
            uint64_t low = desc.AdapterLuid.LowPart;
            uint64_t luid = (high << 32) | (low & 0x00000000FFFFFFFFLL);
            size_t VRAM = ((desc.DedicatedVideoMemory >> 10) >> 10);
            size_t SRAM = ((desc.DedicatedSystemMemory >> 10) >> 10);
            size_t SSRAM = ((desc.SharedSystemMemory >> 10) >> 10);
            ss << "Renderer Name : " << getName() << std::endl;
            ss << "Adapter Name : " << mDeviceName << std::endl;
            ss << "Adapter LUID : " << luid << std::endl;
            ss << "Vendor ID : " << desc.VendorId << std::endl;
            ss << "Device ID : " << desc.DeviceId << std::endl;
            ss << "Subsystem ID : " << desc.SubSysId << std::endl;
            ss << "Revision : " << desc.Revision << std::endl;
            ss << "Video RAM : " << VRAM << "MB" << std::endl;
            ss << "System RAM : " << SRAM << "MB" << std::endl;
            ss << "Shared System RAM :" << SSRAM << "MB" << std::endl;
            T3D_LOG_INFO(LOG_TAG_D3D11RENDERER, 
                "Display Adapter Information : \n%s", ss.str().c_str());
        } while (0);

        D3D_SAFE_RELEASE(pDXGIAdapter);
        D3D_SAFE_RELEASE(pDXGIDevice);

        return ret;
    }
}

