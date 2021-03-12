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


#ifndef __T3D_RENDER_TARGET_H__
#define __T3D_RENDER_TARGET_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Render/T3DViewport.h"


namespace Tiny3D
{
    /**
     * @brief 渲染目标
     */
    class T3D_ENGINE_API RenderTarget : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 渲染目标类型
         */
        enum Type
        {
            E_RT_WINDOW = 0,        /**< 渲染到窗口 */
            E_RT_TEXTURE,           /**< 渲染到纹理 */
            E_RT_MAX
        };

        /**
         * @brief 析构函数
         */
        virtual ~RenderTarget();

        /**
         * @brief 获取渲染目标名称
         * @return 返回一个字符串名称
         */
        const String &getName() const;

        /**
         * @brief 获取渲染目标类型
         */
        virtual Type getType() const = 0;

        /**
         * @brief 获取渲染目标的一些度量值
         * @param [out] width : 渲染目标宽度
         * @param [out] height : 渲染目标高度
         * @param [out] clrDepth : 渲染目标色深
         */
        void getMetrics(size_t &width, size_t &height, size_t &clrDepth) const;

        /**
         * @brief 获取渲染目标宽度
         */
        size_t getWidth() const;

        /**
         * @brief 获取渲染目标高度
         */
        size_t getHeight() const;

        /**
         * @brief 获取渲染目标色深
         */
        size_t getColorDepth() const;

        /**
         * @brief 获取渲染目标行间距
         */
        size_t getPitch() const;

        /**
         * @brief 获取活跃状态
         */
        bool isActive() const;

        /**
         * @brief 设置活跃状态
         */
        void setActive(bool active);

        /**
         * @fn  virtual void RenderTarget::clear(const ColorRGB &clrFill, 
         *      uint32_t clearFlags, Real depth, uint32_t stencil) = 0;
         * @brief   Clears this object to its blank/initial state
         * @param   clrFill     The color fill.
         * @param   clearFlags  The clear flags.
         * @param   depth       The depth.
         * @param   stencil     The stencil.
         */
        virtual void clear(const ColorRGB &clrFill, uint32_t clearFlags, 
            Real depth, uint32_t stencil) = 0;

        /**
         * @brief 渲染
         */
        virtual void render();

        /**
         * @brief 新增一个视口对象，并且关联到本渲染目标上
         * @param [in] camera : 观察新增视口对应的相机对象
         * @param [in] zOrder : 深度值，用于控制渲染顺序
         * @param [in] left : 视口左边在渲染目标区域的比例值
         * @param [in] top : 视口上边在渲染目标区域的比例值
         * @param [in] width : 视口宽度占渲染目标区域的比例值
         * @param [in] height : 视口高度占渲染目标区域的比例值
         */
        ViewportPtr addViewport(CameraPtr camera, long_t zOrder, 
            Real left, Real top, Real width, Real height);

        /**
         * @brief 移除指定深度值的视口对象
         * @param [in] zOrder : 深度值
         * @return 调用成功返回 T3D_OK
         */
        TResult removeViewport(long_t zOrder);

        /**
         * @brief 移除所有当前渲染目标关联的视口对象
         */
        TResult removeAllViewports();

        /**
         * @brief 获取当前渲染目标关联的视口对象的数量
         */
        size_t getNumViewports() const;

        /**
         * @brief 根据指定索引获取对应的视口对象
         * @param [in] zOrder : 深度值
         * @return 调用成功返回视口对象，否则返回nullptr
         */
        ViewportPtr getViewport(long_t zOrder) const;

    protected:
        /**
         * @brief 构造函数
         */
        RenderTarget(const String &name);

    protected:
        typedef TMap<long_t, ViewportPtr>       ViewportList;
        typedef ViewportList::iterator          ViewportListItr;
        typedef ViewportList::const_iterator    ViewportListConstItr;
        typedef ViewportList::value_type        ViewportValue;

        size_t          mWidth;         /**< 渲染目标宽度 */
        size_t          mHeight;        /**< 渲染目标高度 */
        size_t          mColorDepth;    /**< 渲染目标色深 */
        size_t          mPitch;         /**< 渲染目标行间距 */

        bool            mIsActive;      /**< 是否活跃状态 */

        String          mName;          /**< 渲染目标名称 */

        ViewportList    mViewportList;  /**< 视口列表 */
    };
}


#include "T3DRenderTarget.inl"


#endif  /*__T3D_RENDER_TARGET_H__*/
