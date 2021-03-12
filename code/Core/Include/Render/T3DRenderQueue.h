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


#ifndef __T3D_RENDER_QUEUE_H__
#define __T3D_RENDER_QUEUE_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"


namespace Tiny3D
{
    /**
     * @brief 渲染分组
     */
    class T3D_ENGINE_API RenderGroup : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @brief 创建渲染分组
         */
        static RenderGroupPtr create();

        /**
         * @brief 析构函数
         */
        virtual ~RenderGroup();

        /**
         * @brief 添加一个渲染对象到渲染分组
         * @param [in] renderable : 可渲染对象
         * @return 成功返回 T3D_OK
         */
        TResult addRenderable(RenderablePtr renderable);

        /**
         * @brief 清空分组里的渲染对象
         */
        void clear();

        /**
         * @brief 渲染分组里的所有渲染对象
         * @param [in] groupID : 渲染分组ID
         * @param [in] renderer : 渲染器对象
         * @return 成功返回 T3D_OK
         */
        TResult render(ID groupID, RenderContextPtr renderer);

    protected:
        /**
         * @brief 构造函数
         */
        RenderGroup();

        /**
         * @brief 计算渲染图元数量
         * @param [in] vao : 要渲染的VAO对象
         * @return 返回需要渲染的图元数量
         */
        size_t calcPrimitiveCount(VertexArrayObjectPtr vao) const;

    protected:
        typedef TList<RenderablePtr>              RenderableList;
        typedef RenderableList::iterator                RenderableListItr;
        typedef RenderableList::const_iterator          RenderableListConstItr;

        typedef TMap<MaterialPtr, RenderableList>   Renderables;
        typedef Renderables::iterator                   RenderablesItr;
        typedef Renderables::const_iterator             RenderablesConstItr;
        typedef std::pair<MaterialPtr, RenderableList>  RenderablesValue;

        Renderables     mRenderables;   /**< 可渲染对象列表 */
    };


    /**
     * @brief 渲染队列
     */
    class T3D_ENGINE_API RenderQueue : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /** 
         * @brief 分组ID
         */
        enum GroupID
        {
            E_GRPID_NONE = 0,                   /**< 没有分组 */
            E_GRPID_BACKGROUND = 10,            /**< 背景分组 */
            E_GRPID_LIGHT = 15,                 /**< 灯光分组 */
            E_GRPID_SKY_BOX = 20,               /**< 天空盒分组 */
            E_GRPID_INDICATOR = 30,             /**< 坐标指示器分组 */
            E_GRPID_AUTOMATIC = 50,             /**< 自动分组 */
            E_GRPID_SOLID = 60,                 /**< 实体分组 */
            E_GRPID_WIREFRAME = 65,             /**< 线框分组 */
            E_GRPID_TRANSPARENT = 70,           /**< 半透明物体分组 */
            E_GRPID_TRANSPARENT_EFFECT = 80,    /**< 半透明特效分组 */
            E_GRPID_SHADOW = 90,                /**< 阴影分组 */
            E_GRPID_OVERLAY = 100               /**< UI分组 */
        };

        /**
         * @brief 创建渲染队列对象
         */
        static RenderQueuePtr create();

        /**
         * @brief 析构函数
         */
        virtual ~RenderQueue();

        /**
         * @brief 添加可渲染对象到指定渲染分组
         * @param [in] groupID : 分组ID
         * @param [in] renderable : 可渲染对象
         * @return 成功返回 T3D_OK
         * @see enum GroupID
         */
        TResult addRenderable(uint32_t groupID, RenderablePtr renderable);

        /**
         * @brief 清空渲染队列
         */
        void clear();

        /**
         * @brief 渲染
         * @param [in] renderer : 渲染器
         * @return 成功返回 T3D_OK
         */
        TResult render(RenderContextPtr renderer);

    protected:
        /**
         * @brief 构造函数
         */
        RenderQueue();

    protected:
        typedef TMap<uint32_t, RenderGroupPtr>  RenderableGroup;
        typedef RenderableGroup::iterator       RenderableGroupItr;
        typedef RenderableGroup::const_iterator RenderableGroupConstItr;
        typedef TPair<uint32_t, RenderGroupPtr> RenderableGroupValue;

        RenderableGroup     mGroups;        /**< 渲染分组 */
    };
}


#endif  /*__T3D_RENDER_QUEUE_H__*/
