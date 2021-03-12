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


#ifndef __T3D_D3D11_RENDERER_H__
#define __T3D_D3D11_RENDERER_H__


#include "T3DD3D11Prerequisites.h"


namespace Tiny3D
{
    /**
     * @class   D3D11Renderer
     * @brief   DirectX 11 渲染器.
     */
    class D3D11Renderer 
        : public Renderer
        , public Singleton<D3D11Renderer>
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static D3D11RendererPtr create();
         * @brief   创建一个D3D11Renderer对象
         * @returns 返回一个新建对象.
         */
        static D3D11RendererPtr create();

        /**
         * @fn  virtual ~D3D11Renderer();
         * @brief   析构函数
         */
        virtual ~D3D11Renderer();

        /**
         * @fn  virtual TResult init() override;
         * @brief   初始化渲染器
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult init() override;

        /**
         * @fn  virtual TResult destroy() override;
         * @brief   销毁渲染器
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult destroy() override;

        /**
         * @fn  virtual TResult renderAllTarget() override;
         * @brief   渲染一帧
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult renderAllTargets() override;

        /**
         * @fn  virtual RenderWindowPtr createRenderWindow( const String &name, 
         *      const RenderWindowCreateParam &param, 
         *      const RenderWindowCreateParamEx &paramEx) override;
         * @brief   创建渲染窗口
         * @param [in]  name    : 用于标识窗口的名称，不需要跟窗口标题栏相同.
         * @param [in]  param   : 创建渲染窗口必要数据.
         * @param [in]  paramEx : 创建渲染窗口额外数据.
         * @returns 调用成功返回一个渲染窗口对象，失败返回nullptr.
         * @remarks 具体渲染系统实现本接口以创建渲染系统相关的渲染窗口对象.
         */
        virtual RenderWindowPtr createRenderWindow(
            const String &name,
            const RenderWindowCreateParam &param,
            const RenderWindowCreateParamEx &paramEx) override;

        /**
         * @brief   创建渲染器能力组
         * @returns 调用成功返回一个渲染平台相关的渲染器能力组对象
         * @remarks 具体渲染系统实现本接口
         */
        virtual RendererCapabilitiesPtr createRendererCapabilities() const override;

        /**
         * @fn  virtual Matrix4 perspective(const Radian &amp;fovY, Real aspect,
         *  Real nearDist, Real farDist) override;
         * @brief   获取透视投影矩阵
         * @param [in]  fovY        : top 和 bottom 的夹角.
         * @param [in]  aspect      : 宽高比.
         * @param [in]  nearDist    : 观察空间的近平面.
         * @param [in]  farDist     : 观察空间的远平面.
         * @returns 返回一个平台相关的透视投影矩阵.
         */
        virtual Matrix4 perspective(const Radian &fovY, Real aspect,
            Real nearDist, Real farDist) override;

        /**
         * @fn  virtual Matrix4 orthographic(Real width, Real height, 
         *      Real nearDist, Real farDist) override;
         * @brief   获取正交投影矩阵
         * @param [in]  width       : 投影平面宽度.
         * @param [in]  height      : 投影平面高度.
         * @param [in]  nearDist    : 观察空间的近平面.
         * @param [in]  farDist     : 观察空间的远平面.
         * @returns 返回一个平台相关的正交投影矩阵.
         */
        virtual Matrix4 orthographic(Real width, Real height,
            Real nearDist, Real farDist) override;

        /**
         * @fn  virtual Matrix4 
         *      makeViewportMatrix(ViewportPtr viewport) override;
         * @brief   根据视口生成渲染器相关的视口变换矩阵
         * @param [in]  viewport    : 视口对象.
         * @returns 返回的视口变换矩阵.
         */
        virtual Matrix4 makeViewportMatrix(ViewportPtr viewport) override;

        /**
         * @fn  virtual TResult updateFrustum(const Matrix4 &m, 
         *      FrustumBoundPtr bound) override;
         * @brief   更新视锥体的多个平面
         * @param [in]  m       : 投影变换矩阵和观察矩阵的连接， 即 (M_proj * M_view)
         * @param [in]  bound   frustum : 需要更新的视锥体.
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult updateFrustum(const Matrix4 &m,
            FrustumBoundPtr bound) override;

        /**
         * @fn  virtual TResult setCullingMode(CullingMode mode) override;
         * @brief   设置裁剪模式
         * @param [in]  mode    : 裁剪模式.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult setCullingMode(CullingMode mode) override;

        /**
         * @fn  virtual TResult setPolygonMode(PolygonMode mode) override;
         * @brief   设置渲染模式
         * @param [in]  mode    : 渲染模式.
         * @return  成功返回 T3D_OK.
         * @sa  enum PolygonMode
         */
        virtual TResult setPolygonMode(PolygonMode mode) override;

        /**
         * @fn  virtual TResult setViewport(ViewportPtr viewport) override;
         * @brief   设置渲染视口
         * @param   viewport    The viewport.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult setViewport(ViewportPtr viewport) override;

        /**
         * @fn  virtual TResult bindGPUProgram(GPUProgramPtr program) override;
         * @brief   绑定渲染需要的 GPU 程序对象
         * @param [in]  program GPU 程序对象.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult bindGPUProgram(GPUProgramPtr program) override;

        /**
         * @fn  virtual TResult bindGPUConstantBuffer(size_t slot, 
         *      HardwareConstantBufferPtr buffer) override;
         * @brief   绑定渲染需要的 GPU 常量缓冲区
         * @param [in]  slot    常量缓冲区槽索引.
         * @param [in]  buffer  常量缓冲区对象.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult bindGPUConstantBuffer(size_t slot, 
            HardwareConstantBufferPtr buffer) override;

        /**
         * @brief   绑定渲染纹理
         * @param [in]  texture 纹理单元对象
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult bindTexture(TextureUnitPtr unit) override;

        /**
         * @fn  virtual TResult renderObject(VertexArrayObjectPtr vao) override;
         * @brief   渲染对象
         * @param [in]  vao VAO 对象.
         * @return  调用成功返回 T3D_OK.
         */
        virtual TResult renderObject(VertexArrayObjectPtr vao) override;

        /**
         * @fn  ID3D11Device *getD3DDevice()
         * @brief   获取 ID3D11Device 对象
         * @return  返回 ID3D11Device 对象.
         */
        ID3D11Device *getD3DDevice() { return mD3DDevice; }

        /**
         * @fn  ID3D11DeviceContext *getD3DDeviceContext()
         * @brief   获取 ID3D11DeviceContext 对象
         * @return  返回 ID3D11DeviceContext 对象.
         */
        ID3D11DeviceContext *getD3DDeviceContext() { return mD3DDeviceContext; }

        /**
         * @fn  DriverVersion getDriverVersion() const
         * @brief   获取驱动版本号
         * @return  返回驱动版本号.
         */
        const DriverVersion &getDriverVersion() const { return mDriverVersion; }

        /**
         * @fn  const String &getDeviceName() const
         * @brief   获取设备名称
         * @return  返回设备名称.
         */
        const String &getDeviceName() const { return mDeviceName; }

        /**
         * @fn  uint32_t getVendorID() const
         * @brief   获取设备制造商 ID
         * @return  返回设备制造商 ID.
         */
        uint32_t getVendorID() const { return mVendorID; }

        /**
         * @fn  D3D_FEATURE_LEVEL getFeatureLevel() const
         * @brief   获取 D3D 特性级别
         * @return  返回 D3D 特性级别.
         */
        D3D_FEATURE_LEVEL getFeatureLevel() const { return mFeatureLevel; }

    protected:
        /**
         * @fn  D3D11Renderer();
         * @brief   构造函数
         */
        D3D11Renderer();

        /**
         * @fn  TResult initD3DRasterizerState();
         * @brief   初始化光栅化状态
         * @return  调用成功返回 T3D_OK.
         */
        TResult initD3DRasterizerState();

        /**
         * @fn  TResult updateD3DRasterizerState();
         * @brief   更新光栅化状态
         * @return  调用成功返回 T3D_OK.
         */
        TResult updateD3DRasterizerState();

        /**
         * @fn  TResult collectInformation();
         * @brief   收集驱动、开发商等信息
         * @return  调用成功返回 T3D_OK.
         */
        TResult collectInformation();

    protected:
        HINSTANCE                   mInstance;          /**< The instance */

        ID3D11Device                *mD3DDevice;        /**< D3D11 设备对象 */
        ID3D11DeviceContext         *mD3DDeviceContext; /**< D3D11 上下文对象 */
        ID3D11RasterizerState       *mD3DRState;        /**< D3D11 光栅化状态 */

        D3D_FEATURE_LEVEL           mFeatureLevel;      /**< D3D 特性级别 */

        D3D11_RASTERIZER_DESC       mD3DRSDesc;         /**< D3D11 光栅化状态描述结构 */

        HardwareBufferManagerPtr    mHardwareBufferMgr; /**< 缓冲区管理对象 */

        GPUProgramPtr               mBoundGPUProgram;   /**< 渲染用的 GPU 程序对象 */

        DriverVersion               mDriverVersion;     /**< 驱动版本号 */
        String                      mDeviceName;        /**< 设备名称 */
        uint32_t                    mVendorID;          /**< GPU 制造商ID */

        bool        mIsRSStateDirty;    /**< 光栅化状态是否有改变标识 */
    };

    #define D3D11_RENDERER      (D3D11Renderer::getInstance())
}


#endif  /*__T3D_D3D11_RENDERER_H__*/
