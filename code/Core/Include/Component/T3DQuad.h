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


#ifndef __T3D_QUAD_H__
#define __T3D_QUAD_H__


#include "Component/T3DRenderable.h"


namespace Tiny3D
{
    /**
     * @class   Quad
     * @brief   可渲染四边形
     */
    class T3D_ENGINE_API Quad : public Renderable
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @enum    VertexIndex
         * @brief   顶点位置
         */
        enum VertexIndex
        {
            VI_TOP_LEFT = 0,
            VI_TOP_RIGHT,
            VI_BOTTOM_LEFT,
            VI_BOTTOM_RIGHT,
            VI_MAX_VERTICES
        };

        /**
         * @struct  Vertex
         * @brief   顶点信息
         */
        struct Vertex
        {
            Vector3     position;   /**< 顶点位置 */
            Vector2     uv;         /**< UV坐标 */
        };

        /**
         * @struct  QuadData
         * @brief   A quad data.
         */
        struct QuadData
        {
            Vertex  vertices[VI_MAX_VERTICES];
        };

        /**
         * @fn  static QuadPtr Quad::create(const QuadData &quad, 
         *      const String &materialName, ID uID = E_CID_AUTOMATIC);
         * @brief   创建可渲染空间四边形对象
         * @param [in]  quad            : 空间四边形数据.
         * @param [in]  materialName    : 材质名称.
         * @param [in]  uID             (Optional) : 结点ID，默认自动生成.
         * @return  返回一个可渲染空间四边形对象.
         */
        static QuadPtr create(const QuadData &quad, const String &materialName,
            ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual Quad::~Quad();
         * @brief   析构函数
         */
        virtual ~Quad();

        /**
         * @fn  virtual ComponentPtr Quad::clone() const override;
         * @brief   重写基类接口，实现克隆对象功能
         * @return  A copy of this object.
         * @sa  NodePtr Node::clone() const
         */
        virtual ComponentPtr clone() const override;

        /**
         * @fn  void Quad::setVertexPos(size_t idx, const Vector3 &pos)
         * @brief   设置空间四边形四个顶点的本地坐标
         * @param   idx Zero-based index of the.
         * @param   pos The position.
         */
        void setVertexPos(size_t idx, const Vector3 &pos)
        {
            T3D_ASSERT(idx < VI_MAX_VERTICES);
            mQuad.vertices[idx].position = pos;
        }

        /**
         * @fn  const Vector3 Quad::&getVertexPos(size_t idx) const
         * @brief   获取空间四边形四个顶点的本地坐标
         * @param   idx Zero-based index of the.
         * @return  The vertex position.
         */
        const Vector3 &getVertexPos(size_t idx) const
        {
            T3D_ASSERT(idx < VI_MAX_VERTICES);
            return mQuad.vertices[idx].position;
        }

        /**
         * @fn  void Quad::setVertexUV(size_t idx, const Vector2 &uv)
         * @brief   设置空间四边形四个顶点的UV坐标
         * @param   idx Zero-based index of the.
         * @param   uv  The uv.
         */
        void setVertexUV(size_t idx, const Vector2 &uv)
        {
            T3D_ASSERT(idx < VI_MAX_VERTICES);
            mQuad.vertices[idx].uv = uv;
        }

        /**
         * @fn  const Vector2 Quad::&getVertexUV(size_t idx) const
         * @brief   获取空间四边形四个顶点的UV坐标
         * @param   idx Zero-based index of the.
         * @return  The vertex uv.
         */
        const Vector2 &getVertexUV(size_t idx) const
        {
            T3D_ASSERT(idx < VI_MAX_VERTICES);
            return mQuad.vertices[idx].uv;
        }

    protected:
        /**
         * @fn  Quad::Quad(ID uID = E_CID_AUTOMATIC);
         * @brief   构造函数
         * @param   uID (Optional) The identifier.
         */
        Quad(ID uID = E_CID_AUTOMATIC);
            
        /**
         * @fn  virtual TResult Quad::init(const QuadData &quad, 
         *      const String &materialName);
         * @brief   初始化对象
         * @param [in]  quad            : 空间四边形.
         * @param [in]  materialName    : 材质名称.
         * @return  成功返回 T3D_OK.
         */
        virtual TResult init(const QuadData &quad, const String &materialName);

        /**
         * @fn  virtual TResult 
         *      Quad::cloneProperties(ComponentPtr newObj) const override;
         * @brief   重写基类接口，实现克隆对象属性
         * @param   newObj  The new object.
         * @return  A TResult.
         * @sa  TResult Node::cloneProperties(NodePtr node) const
         */
        virtual TResult cloneProperties(ComponentPtr newObj) const override;

        /**
         * @fn  virtual MaterialPtr Quad::getMaterial() const override;
         * @brief   重写基类接口，获取渲染材质对象
         * @return  The material.
         * @sa  MaterialPtr Renderable::getMaterial() const
         */
        virtual MaterialPtr getMaterial() const override;

        /**
         * @fn  virtual VertexArrayObjectPtr 
         *      Quad::getVertexArrayObject() const override;
         * @brief   重写基类接口，获取渲染VAO数据对象
         * @return  The vertex array object.
         * @sa  VertexArrayObjectPtr Renderable::getVertexArrayObject() const
         */
        virtual VertexArrayObjectPtr getVertexArrayObject() const override;

    protected:
        QuadData    mQuad;                          /**< 原始数据 */
        Vector3     mWorldQuad[VI_MAX_VERTICES];    /**< 变换成世界坐标的顶点 */

        MaterialPtr             mMaterial;          /**< 渲染用的材质 */
        VertexArrayObjectPtr    mVAO;               /**< 渲染用的VAO */
    };
}


#endif  /*__T3D_QUAD_H__*/
