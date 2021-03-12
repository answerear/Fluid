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


#ifndef __T3D_VIEWPORT_H__
#define __T3D_VIEWPORT_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"


namespace Tiny3D
{
    /**
     * @brief 渲染视口
     */
    class T3D_ENGINE_API Viewport : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 创建视口对象
         * @param [in] camera : 跟本视口关联的相机对象
         * @param [in] target : 跟本视口关联的渲染目标对象
         * @param [in] left : 视口左边在渲染目标区域的比例值
         * @param [in] top : 视口上边在渲染目标区域的比例值
         * @param [in] width : 视口宽度占渲染目标区域的比例值
         * @param [in] height : 视口高度占渲染目标区域的比例值
         * @param [in] zOrder : 视口深度序列值
         */
        static ViewportPtr create(CameraPtr camera, RenderTargetPtr target, 
            Real left, Real top, Real width, Real height, long_t zOrder);

        /**
         * @brief 析构函数
         */
        virtual ~Viewport();

        /**
         * @brief 获取观察视口对应的相机
         */
        CameraPtr getCamera() const;

        /**
         * @brief 渲染
         */
        void render();

        /**
         * @brief 获取渲染目标对象
         */
        RenderTargetPtr getRenderTarget() const;

        /**
         * @brief 获取左边在渲染目标区域的比值
         */
        Real getLeft() const;

        /**
         * @brief 获取上边在渲染目标区域的比值
         */
        Real getTop() const;

        /**
         * @brief 获取宽度在渲染目标区域的比值
         */
        Real getWidth() const;

        /**
         * @brief 获取高度在渲染目标区域的比值
         */
        Real getHeight() const;

        /**
         * @brief 获取视口实际左边位置
         */
        size_t getActualLeft() const;

        /**
         * @brief 获取视口实际上边位置
         */
        size_t getActualTop() const;

        /**
         * @brief 获取视口实际宽度
         */
        size_t getActualWidth() const;

        /**
         * @brief 获取视口实际高度
         */
        size_t getActualHeight() const;

        /**
         * @brief 获取视口变换矩阵
         */
        const Matrix4 &getViewportMatrix() const;

        /**
         * @brief 设置视口位置和大小
         * @param [in] left : 视口左边在渲染目标区域的相对位置
         * @param [in] top : 视口上边在渲染目标区域的相对位置
         * @param [in] width : 视口宽度在渲染目标区域的相对值
         * @param [in] height : 视口高度在渲染目标区域的相对值
         */
        void setDimensions(Real left, Real top, Real width, Real height);

        /**
         * @brief 设置清除标记
         * @param [in] flags : 清除标记
         * @return void
         * @see Renderer::ClearFlags
         */
        void setClearFlags(uint32_t flags);

        /**
         * @brief 获取清除标记
         * @return 返回清除标记
         */
        uint32_t getClearFlags() const;

        /**
         * @brief 设置用于清除的 z-buffer 值
         * @param [in] z : z值
         * @return void
         */
        void setClearZ(Real z);

        /**
         * @brief 获取用于清除的 z-buffer 值
         */
        Real getClearZ() const;

        /**
         * @brief 设置背景颜色
         * @param [in] color : 颜色值
         * @return void
         */
        void setBkgndColor(const ColorRGB &color);

        /**
         * @brief 获取背景颜色
         * @return 返回背景颜色
         */
        const ColorRGB &getBkgndColor() const;

    protected:
        /**
         * @brief 构造函数
         * @param [in] camera : 跟本视口关联的相机对象
         * @param [in] target : 跟本视口关联的渲染目标对象
         * @param [in] left : 视口左边在渲染目标区域的比例值
         * @param [in] top : 视口上边在渲染目标区域的比例值
         * @param [in] width : 视口宽度占渲染目标区域的比例值
         * @param [in] height : 视口高度占渲染目标区域的比例值
         * @param [in] zOrder : 视口深度序列值
         */
        Viewport(CameraPtr camera, RenderTargetPtr target, Real left, 
            Real top, Real width, Real height, long_t zOrder);

        /**
         * @brief 更新视口位置和大小
         */
        void updateDimensions();

    protected:
        CameraPtr         mCamera;        /**< 关联本视口对应的相机 */
        RenderTarget        *mRenderTarget; /**< 关联本视口对应的渲染目标 */

        Real        mLeft;          /**< 视口左边在渲染目标区域的相对位置 */
        Real        mTop;           /**< 视口上边在渲染目标区域的相对位置 */
        Real        mWidth;         /**< 视口宽度在渲染目标区域的相对值 */
        Real        mHeight;        /**< 视口高度在渲染目标区域的相对值 */

        size_t      mActualLeft;    /**< 视口实际的左边位置 */
        size_t      mActualTop;     /**< 视口实际的上边位置 */
        size_t      mActualWidth;   /**< 视口实际的宽度 */
        size_t      mActualHeight;  /**< 视口实际的高度 */

        uint32_t    mClearFlags;    /**< 清除标记 */
        Real        mClearZ;        /**< 用于清除的 z-buffer 值 */

        ColorRGB    mBkgndColor;    /**< 背景颜色 */

        Matrix4     mMatrix;        /**< 视口变换矩阵 */
    };
}


#include "T3DViewport.inl"


#endif  /*__T3D_VIEWPORT_H__*/
