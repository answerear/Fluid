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


#ifndef __T3D_GLOBE_H__
#define __T3D_GLOBE_H__

#include "Component/T3DRenderable.h"


namespace Tiny3D
{
    /**
     * @class   Globe
     * @brief   可渲染球体
     */
    class T3D_ENGINE_API Globe : public Renderable
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static GlobePtr Globe::create(const Vector3 &center, 
         *      Real radius, ID uID = E_CID_AUTOMATIC);
         * @brief   创建可渲染球体对象
         * @param [in]  center  : 球心.
         * @param [in]  radius  : 球半径.
         * @param [in]  uID     (Optional) : 结点ID，默认自动生成.
         * @return  返回一个可渲染球体对象.
         */
        static GlobePtr create(const Vector3 &center, Real radius, 
            ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual Globe::~Globe();
         * @brief   析构函数
         */
        virtual ~Globe();

        /**
         * @fn  virtual ComponentPtr Globe::clone() const override;
         * @brief   重写基类接口，实现克隆对象功能
         * @return  A copy of this object.
         * @sa  NodePtr Node::clone() const
         */
        virtual ComponentPtr clone() const override;

        /**
         * @fn  const Vector3 Globe::&getCenter() const
         * @brief   获取球心
         * @return  The center.
         */
        const Vector3 &getCenter() const { return mCenter; }

        /**
         * @fn  Real Globe::getRadius() const
         * @brief   获取球半径
         * @return  The radius.
         */
        Real getRadius() const { return mRadius; }

    protected:
        /**
         * @fn  Globe::Globe(ID uID = E_CID_AUTOMATIC);
         * @brief   构造函数
         * @param   uID (Optional) The identifier.
         */
        Globe(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual TResult Globe::init(const Vector3 &center, Real radius);
         * @brief   初始化对象
         * @param [in]  center  : 球心.
         * @param [in]  radius  : 球半径.
         * @return  成功返回 T3D_OK.
         */
        virtual TResult init(const Vector3 &center, Real radius);

        /**
         * @fn  virtual TResult 
         *      Globe::cloneProperties(ComponentPtr newObj) const override;
         * @brief   重写基类接口，实现克隆对象属性
         * @param   newObj  The new object.
         * @return  A TResult.
         * @sa  TResult Node::cloneProperties(NodePtr node) const
         */
        virtual TResult cloneProperties(ComponentPtr newObj) const override;

        /**
         * @fn  virtual MaterialPtr Globe::getMaterial() const override;
         * @brief   重写基类接口，获取渲染材质对象
         * @return  The material.
         * @sa  MaterialPtr Renderable::getMaterial() const
         */
        virtual MaterialPtr getMaterial() const override;

        /**
         * @fn  virtual VertexArrayObjectPtr Globe::getVertexArrayObject() const override;
         * @brief   重写基类接口，获取渲染VAO数据对象
         * @return  The vertex array object.
         * @sa  VertexArrayObjectPtr Renderable::getVertexArrayObject() const
         */
        virtual VertexArrayObjectPtr getVertexArrayObject() const override;

    private:
        /**
         * @fn  void Globe::setupSphere(void *vertices, size_t vertexCount, 
         *      uint16_t *indices, size_t indexCount);
         * @brief   Sets up the sphere
         * @param [in,out]  vertices    If non-null, the vertices.
         * @param           vertexCount Number of vertices.
         * @param [in,out]  indices     If non-null, the indices.
         * @param           indexCount  Number of indexes.
         */
        void setupSphere(void *vertices, size_t vertexCount, uint16_t *indices,
            size_t indexCount);

    protected:
        Vector3                 mCenter;    /**< 球心 */
        Real                    mRadius;    /**< 球半径 */

        VertexArrayObjectPtr    mVAO;       /**< 渲染用的VAO */

        MaterialPtr             mMaterial;  /**< 材质 */
    };
}


#endif  /*__T3D_GLOBE_H__*/
