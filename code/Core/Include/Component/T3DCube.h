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


#ifndef __T3D_CUBE_H__
#define __T3D_CUBE_H__


#include "Component/T3DRenderable.h"


namespace Tiny3D
{
    /**
     * @class   Cube
     * @brief   可渲染的方盒子结点
     */
    class T3D_ENGINE_API Cube : public Renderable
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static CubePtr Cube::create(const Vector3 &center, 
         *      const Vector3 &extent, ID uID = E_CID_AUTOMATIC);
         * @brief   创建长方体渲染对象
         * @param [in]  center  : 长方体的中心点.
         * @param [in]  extent  : 长方体沿轴的6个方向长度.
         * @param [in]  uID     (Optional) : 结点ID，默认自动生成.
         * @return  返回新建的长方体渲染对象.
         */
        static CubePtr create(const Vector3 &center, const Vector3 &extent,
            ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual Cube::~Cube();
         * @brief   析构函数
         */
        virtual ~Cube();

        /**
         * @fn  virtual ComponentPtr Cube::clone() const override;
         * @brief   重写基类接口，实现克隆对象功能
         * @return  A copy of this object.
         * @sa  NodePtr Node::clone() const
         */
        virtual ComponentPtr clone() const override;

        /**
         * @fn  const Vector3 Cube::&getCenter() const
         * @brief   获取长方体中心
         * @return  The center.
         */
        const Vector3 &getCenter() const { return mCenter; }

        /**
         * @fn  const Vector3 Cube::&getExtent() const
         * @brief   获取三个轴方向上的长度
         * @return  The extent.
         */
        const Vector3 &getExtent() const { return mExtent; }

    protected:
        /**
         * @fn  Cube::Cube(ID uID = E_CID_AUTOMATIC);
         * @brief   构造函数
         * @param   uID (Optional) The identifier.
         */
        Cube(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual TResult 
         *      Cube::init(const Vector3 &center, const Vector3 &extent);
         * @brief   初始化对象
         * @param [in]  center  : 长方体的中心点.
         * @param [in]  extent  : 长方体沿轴的6个方向长度.
         * @return  成功返回 T3D_OK.
         */
        virtual TResult init(const Vector3 &center, const Vector3 &extent);

        /**
         * @fn  virtual TResult 
         *      Cube::cloneProperties(ComponentPtr newObj) const override;
         * @brief   重写基类接口，实现克隆对象属性
         * @param   newObj  The new object.
         * @return  A TResult.
         * @sa  TResult Node::cloneProperties(NodePtr node) const
         */
        virtual TResult cloneProperties(ComponentPtr newObj) const override;

        /**
         * @fn  virtual MaterialPtr Cube::getMaterial() const override;
         * @brief   重写基类接口，获取渲染材质对象
         * @return  The material.
         * @sa  MaterialPtr Renderable::getMaterial() const
         */
        virtual MaterialPtr getMaterial() const override;

        /**
         * @fn  virtual VertexArrayObjectPtr 
         *      Cube::getVertexArrayObject() const override;
         * @brief   重写基类接口，获取渲染VAO数据对象
         * @return  The vertex array object.
         * @sa  VertexArrayObjectPtr Renderable::getVertexArrayObject() const
         */
        virtual VertexArrayObjectPtr getVertexArrayObject() const override;

    private:
        /**
         * @fn  void Cube::setupBox(void *vertices, size_t vertexCount, 
         *      uint16_t *indices, size_t indexCount);
         * @brief   Sets up the box
         * @param [in,out]  vertices    If non-null, the vertices.
         * @param           vertexCount Number of vertices.
         * @param [in,out]  indices     If non-null, the indices.
         * @param           indexCount  Number of indexes.
         */
        void setupBox(void *vertices, size_t vertexCount,  uint16_t *indices, 
            size_t indexCount);

    protected:
        Vector3                 mCenter;        /**< 长方体的中心 */
        Vector3                 mExtent;        /**< 沿3个轴方向上的长度 */
        VertexArrayObjectPtr    mVAO;           /**< 渲染用的VAO */
        MaterialPtr             mMaterial;      /**< 材质 */
    };
}


#endif  /*__T3D_CUBE_H__*/
