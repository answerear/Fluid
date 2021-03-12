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


#ifndef __T3D_NODE_H__
#define __T3D_NODE_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Kernel/T3DObject.h"


namespace Tiny3D
{
    /**
     * @class   Node
     * @brief   树形结构结点类
     */
    class T3D_ENGINE_API Node : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @enum    NodeID
         * @brief   结点ID
         */
        enum NodeID : ID
        {
            E_NID_AUTOMATIC = 0xFFFFFFFF,   /**< 自动生成ID */
            E_NID_INVALID = 0,              /**< 无效ID */
        };

        /**
         * @enum    Type
         * @brief   结点类型
         */
        enum class Type : uint32_t
        {
            UNKNOWN = 0,       /**< 未知结点类型 */
            SCENE_NODE,        /**< 场景结点 */
        };

        /**
         * @fn  virtual Node::~Node();
         * @brief   析构函数
         */
        virtual ~Node();

        /**
         * @fn  virtual Type Node::getNodeType() const = 0;
         * @brief   返回结点类型
         * @return  返回结点类型.
         * @sa  enum Type
         *  @note 每个派生类都要实现本接口，以返回具体的类型，如果不实现，
         *  则无法实例化对象了
         */
        virtual Type getNodeType() const = 0;

        /**
         * @fn  ID Node::getNodeID() const;
         * @brief   返回结点全局唯一标识ID
         * @return  返回结点ID.
         * @sa  enum ID
         */
        ID getNodeID() const;

        /**
         * @fn  void Node::setName(const String &name);
         * @brief   设置结点名称
         * @param [in]  name    : 结点名称.
         * @sa  const String &amp;getName() const
         *
         * ### return   void.
         */
        void setName(const String &name);

        /**
         * @fn  const String Node::&getName() const;
         * @brief   获取结点名称
         * @return  返回结点名称.
         * @sa  void setName(const String &amp;name)
         */
        const String &getName() const;

        /**
         * @fn  virtual TResult Node::addChild(NodePtr node);
         * @brief   添加一个子结点
         * @param [in]  node    : 子结点对象.
         * @return  调用成功返回 T3D_OK.
         * @sa  TResult removeChild(const NodePtr &amp;node, bool cleanup)
         * @sa  TResult removeChild(uint32_t nodeID, bool cleanup)
         */
        virtual TResult addChild(NodePtr node);

        /**
         * @fn  virtual TResult Node::removeChild(NodePtr node);
         * @brief   移除一个子结点
         * @param [in]  node    : 子结点对象.
         * @return  调用成功返回 T3D_OK.
         * @sa  TResult removeChild(uint32_t nodeID)
         */
        virtual TResult removeChild(NodePtr node);

        /**
         * @fn  virtual TResult Node::removeChild(uint32_t nodeID);
         * @brief   移除一个子结点
         * @param [in]  nodeID  : 结点唯一标识ID.
         * @return  调用成功返回 T3D_OK.
         * @sa  TResult removeChild(const NodePtr &amp;node)
         */
        virtual TResult removeChild(uint32_t nodeID);

        /**
         * @brief 移除所有子结点
         * @param [in] cleanup : 是否删除所有子结点，true表示删除，
         *      false表示仅仅移除而并不删除子结点
         * @return 调用成功返回 T3D_OK
         */
        virtual TResult removeAllChildren();

        /**
         * @brief 从父结点移除自己
         * @param [in] cleanup : 是否删除自己，true表示删除，
         *      false表示仅仅移除而并不删除自己
         * @return 调用成功返回 T3D_OK
         * @note 当cleanup用true调用后，本身结点已经被释放了，
         *      则不能在访问任何结点接口和数据
         */
        TResult removeFromParent();

        /**
         * @brief 获取第一个子结点
         * @return 返回第一个子结点对象
         */
        NodePtr getFirstChild() const;

        /**
         * @brief 获取最后一个子结点
         * @return 返回最后一个子结点对象
         */
        NodePtr getLastChild() const;

        /**
         * @brief 返回指定结点ID的子结点
         * @param [in] nodeID : 子结点ID
         * @return 返回子结点对象
         * @see NodePtr getChild() const
         * @see NodePtr getChild(const String &name) const
         */
        NodePtr getChild(ID nodeID) const;

        /**
         * @brief 返回指定名称的子结点
         * @param [in] name : 子结点名称
         * @return 返回子结点对象
         */
        NodePtr getChild(const String &name) const;

        /**
         * @brief 获取前一个兄弟结点
         */
        NodePtr getPrevSibling() const;

        /**
         * @brief 获取后一个兄弟结点
         */
        NodePtr getNextSibling() const;

        /**
         * @brief 获取子结点数量
         */
        size_t getChildrenCount() const;

        /**
         * @brief 获取父结点
         * @return 返回父结点对象
         */
        NodePtr getParent() const;

        /**
         * @brief 复制一个新结点对象出来
         * @return 返回新结点对象
         * @note 派生类需要重写本接口以实现其具体的对象复制操作
         */
        virtual NodePtr clone() const = 0;

    protected:
        /**
         * @brief 构造函数
         */
        Node(ID uID = E_NID_AUTOMATIC);

        /**
         * @brief 复制结点的属性数据
         * @param [in] node : 新结点
         * @return 调用成功返回 T3D_OK
         * @note 重写了clone方法的一般都需要重写本方法以实现具体类属性数据的复制
         */
        virtual TResult cloneProperties(NodePtr node) const;

        /**
         * @brief 结点挂到Scene Graph上时回调通知
         * @param [in] parent : 挂上去的父结点
         * @return void
        */
        virtual void onAttachParent(NodePtr parent);

        /**
         * @brief 结点从Scene Graph上拿下来时回调通知
         * @param [in] parent : 拿下来的父结点
         * @return void
         */
        virtual void onDetachParent(NodePtr parent);

    private:
        /**
         * @brief 生成全局唯一标识
         * @return 返回全局唯一标识
         */
        ID makeGlobalID() const;

    private:
        ID          mID;            /**< 结点ID */
        String      mName;          /**< 结点名称 */
        
        size_t      mChildrenCount; /**< 子结点数量 */
        NodePtr     mParent;        /**< 父结点 */
        NodePtr     mFirstChild;    /**< 第一个子结点 */
        NodePtr     mLastChild;     /**< 最后一个子结点 */
        NodePtr     mPrevSibling;   /**< 前一个兄弟结点 */
        NodePtr     mNextSibling;   /**< 后一个兄弟结点 */
    };
}


#include "T3DNode.inl"


#endif  /*__T3D_NODE_H__*/
