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


#ifndef __T3D_HARDWARE_VERTEX_BUFFER_H__
#define __T3D_HARDWARE_VERTEX_BUFFER_H__


#include "Render/T3DHardwareBuffer.h"


namespace Tiny3D
{
    /**
     * @class   HardwareVertexBuffer
     * @brief   顶点缓冲区
     * @sa  class HardwareBuffer
     */
    class T3D_ENGINE_API HardwareVertexBuffer : public HardwareBuffer
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  virtual HardwareVertexBuffer::~HardwareVertexBuffer();
         * @brief   析构函数
         */
        virtual ~HardwareVertexBuffer();

        /**
         * @fn  size_t HardwareVertexBuffer::getVertexSize() const
         * @brief   获取当个顶点的字节数大小
         * @returns 返回顶点大小.
         */
        size_t getVertexSize() const { return mVertexSize; }

        /**
         * @fn  size_t HardwareVertexBuffer::getVertexCount() const
         * @brief   获取顶点数
         * @returns 返回定点数.
         */
        size_t getVertexCount() const { return mVertexCount; }

    protected:
        /**
         * @fn  HardwareVertexBuffer::HardwareVertexBuffer(size_t vertexSize, 
         *      size_t vertexCount, Usage usage, uint32_t mode);
         * @brief   构造函数
         * @param [in]  vertexSize  顶点字节数大小.
         * @param [in]  vertexCount 顶点数量.
         * @param [in]  usage       缓冲区用法.
         * @param [in]  mode        缓冲区访问方式.
         */
        HardwareVertexBuffer(size_t vertexSize, size_t vertexCount, Usage usage,
            uint32_t mode);

    protected:
        size_t  mVertexCount;       /**< 顶点数量 */
        size_t  mVertexSize;        /**< 顶点字节数大小 */
    };


    /**
     * @class   VertexAttribute
     * @brief   顶点属性
     */
    class T3D_ENGINE_API VertexAttribute
    {
    public:
        /**
         * @enum    Type
         * @brief   顶点属性类型
         */
        enum class Type : uint32_t
        {
            E_VAT_FLOAT1 = 0,   /**< 1 float */
            E_VAT_FLOAT2 = 1,   /**< 2 float tuple */
            E_VAT_FLOAT3 = 2,   /**< 3 float tuple */
            E_VAT_FLOAT4 = 3,   /**< 4 float tuple */
            E_VAT_COLOR = 4,    /**< color type */
            E_VAT_BYTE4 = 5,
            E_VAT_BYTE4_NORM = 6,
            E_VAT_UBYTE4 = 7,
            E_VAT_UBYTE4_NORM = 8,
            E_VAT_SHORT2 = 9,
            E_VAT_SHORT4 = 10,
            E_VAT_SHORT2_NORM = 11,
            E_VAT_SHORT4_NORM = 12,
            E_VAT_USHORT2 = 13,
            E_VAT_USHORT4 = 14,
            E_VAT_USHORT2_NORM = 15,
            E_VAT_USHORT4_NORM = 16,
            E_VAT_DOUBLE1 = 17,
            E_VAT_DOUBLE2 = 18,
            E_VAT_DOUBLE3 = 19,
            E_VAT_DOUBLE4 = 20,
            E_VAT_INT1 = 21,
            E_VAT_INT2 = 22,
            E_VAT_INT3 = 23,
            E_VAT_INT4 = 24,
            E_VAT_UINT1 = 25,
            E_VAT_UINT2 = 26,
            E_VAT_UINT3 = 27,
            E_VAT_UINT4 = 28,
            E_VAT_FLOAT16_2 = 29,
            E_VAT_FLOAT16_4 = 30,
        };

        /**
         * @enum    Semantic
         * @brief   顶点语义解释
         */
        enum class Semantic : uint32_t
        {
            E_VAS_POSITION = 0,     /**< 位置 */
            E_VAS_BLENDWEIGHT = 1,  /**< 骨骼混合权重 */
            E_VAS_BLENDINDICES = 2, /**< 骨骼索引 */
            E_VAS_NORMAL = 3,       /**< 法线 */
            E_VAS_DIFFUSE = 4,      /**< 漫反射值 */
            E_VAS_SPECULAR = 5,     /**< 镜面反射值 */
            E_VAS_TEXCOORD = 6,     /**< 纹理坐标 */
            E_VAS_TANGENT = 7,      /**< 切线 */
            E_VAS_BINORMAL = 8,     /**< 副法线 */
        };

        /**
         * @fn  VertexAttribute::VertexAttribute();
         * @brief   默认构造函数
         */
        VertexAttribute();

        /**
         * @fn  VertexAttribute::VertexAttribute(size_t stream, size_t offset, 
         *      Type type, Semantic semantic, size_t semanticIndex);
         * @brief   构造函数
         * @param [in]  stream          数据流索引.
         * @param [in]  offset          相对当前顶点起始位置的偏移.
         * @param [in]  type            顶点数据类型.
         * @param [in]  semantic        顶点语义解释.
         * @param [in]  semanticIndex   语义索引.
         */
        VertexAttribute(size_t stream, size_t offset, Type type,
            Semantic semantic, size_t semanticIndex);

        /**
         * @fn  virtual VertexAttribute::~VertexAttribute();
         * @brief   析构函数
         */
        virtual ~VertexAttribute();

        /**
         * @fn  size_t VertexAttribute::getStream() const
         * @brief   获取数据流索引
         * @returns 返回数据流索引.
         */
        size_t getStream() const { return mStream; }

        /**
         * @fn  size_t VertexAttribute::getOffset() const
         * @brief   获取顶点相对一个顶点数据起点的偏移位置
         * @returns 返回偏移值.
         */
        size_t getOffset() const { return mOffset; }

        /**
         * @fn  Type VertexAttribute::getType() const
         * @brief   获取顶点数据类型
         * @returns 返回顶点数据类型.
         */
        Type getType() const { return mType; }

        /**
         * @fn  Semantic VertexAttribute::getSemantic() const
         * @brief   获取顶点语义解释
         * @returns 返回顶点语义解释.
         */
        Semantic getSemantic() const { return mSemantic; }

        /**
         * @fn  size_t VertexAttribute::getSemanticIndex() const
         * @brief   获取顶点语义索引
         * @returns 返回顶点语义索引.
         */
        size_t getSemanticIndex() const { return mSemanticIndex; }

        /**
         * @fn  size_t VertexAttribute::getSize() const;
         * @brief   获取顶点数据字节大小
         * @returns 返回顶点数据字节大小.
         */
        size_t getSize() const;

    protected:
        Type        mType;          /**< 顶点属性数据类型 */
        Semantic    mSemantic;      /**< 顶点属性语义 */
        size_t      mOffset;        /**< 顶点属性定义的在顶点缓存中的偏移值 */
        size_t      mStream;        /**< 对应定义的顶点缓存索引 */
        size_t      mSemanticIndex; /**< 顶点语义索引 */
    };


    /**
     * @class   VertexDeclaration
     * @brief   顶点声明
     */
    class T3D_ENGINE_API VertexDeclaration : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        typedef TList<VertexAttribute>              VertexAttriList;
        typedef VertexAttriList::iterator           VertexAttriListItr;
        typedef VertexAttriList::const_iterator     VertexAttriListConstItr;

        /**
         * @fn  static VertexDeclarationPtr VertexDeclaration::create();
         * @brief   创建顶点声明对象
         * @returns 返回一个顶点声明对象.
         */
        static VertexDeclarationPtr create();

        /**
         * @fn  virtual VertexDeclaration::~VertexDeclaration();
         * @brief   析构函数
         */
        virtual ~VertexDeclaration();

        /**
         * @fn  size_t VertexDeclaration::getAttributeCount() const
         * @brief   获取顶点属性数量
         * @returns 返回顶点属性数量.
         */
        size_t getAttributeCount() const  {  return mVertexAttributes.size(); }

        /**
         * @fn  const VertexAttriList VertexDeclaration::&getAttributes() const
         * @brief   获取顶点属性列表
         * @returns 返回顶点属性列表.
         */
        const VertexAttriList &getAttributes() const
        { 
            return mVertexAttributes; 
        }

        /**
         * @fn  const VertexAttribute VertexDeclaration::&getAttribute(
         *      size_t index) const;
         * @brief   获取顶点属性
         * @param [in]  index   顶点属性数组中的索引.
         * @returns 返回顶点属性.
         */
        const VertexAttribute &getAttribute(size_t index) const;

        /**
         * @fn  virtual const VertexAttribute VertexDeclaration::&addAttribute(
         *      size_t stream, size_t offset, VertexAttribute::Type type, 
         *      VertexAttribute::Semantic semantic, size_t semanticIndex);
         * @brief   新增一个顶点属性
         * @param [in]  stream          数据流索引.
         * @param [in]  offset          相对一个顶点数据开始位置的偏移.
         * @param [in]  type            顶点数据类型.
         * @param [in]  semantic        顶点语义解释.
         * @param [in]  semanticIndex   顶点语义索引.
         * @returns 返回一个新的顶点属性.
         */
        virtual const VertexAttribute &addAttribute(size_t stream, 
            size_t offset, VertexAttribute::Type type, 
            VertexAttribute::Semantic semantic, size_t semanticIndex);

        /**
         * @fn  virtual const VertexAttribute 
         *      VertexDeclaration::&insertAttribute(size_t pos, size_t stream, 
         *      size_t offset, VertexAttribute::Type type, 
         *      VertexAttribute::Semantic semantic, size_t semanticIndex);
         * @brief   新增插入一个顶点属性
         * @param [in]  pos             插入位置.
         * @param [in]  stream          数据流索引.
         * @param [in]  offset          相对一个顶点数据开始位置的偏移.
         * @param [in]  type            顶点数据类型.
         * @param [in]  semantic        顶点语义解释.
         * @param [in]  semanticIndex   顶点语义索引.
         * @returns 返回一个新的顶点属性.
         */
        virtual const VertexAttribute &insertAttribute(size_t pos, 
            size_t stream, size_t offset, VertexAttribute::Type type, 
            VertexAttribute::Semantic semantic, size_t semanticIndex);

        /**
         * @fn  virtual TResult VertexDeclaration::addAttribute(
         *      const VertexAttribute &vertexAttribute);
         * @brief   添加一个顶点属性
         * @param [in]  vertexAttribute 顶点属性对象.
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult addAttribute(const VertexAttribute &vertexAttribute);

        /**
         * @fn  virtual TResult VertexDeclaration::insertAttribute(size_t pos, 
         *      const VertexAttribute &vertexAttribute);
         * @brief   插入一个顶点属性
         * @param [in]  pos             插入的位置.
         * @param [in]  vertexAttribute 顶点属性对象.
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult insertAttribute(size_t pos, 
            const VertexAttribute &vertexAttribute);

        /**
         * @fn  virtual TResult VertexDeclaration::removeAttribute(size_t pos);
         * @brief   移除指定位置的顶点属性
         * @param [in]  pos 数组位置.
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult removeAttribute(size_t pos);

        /**
         * @fn  virtual TResult VertexDeclaration::removeAttribute(
         *      VertexAttribute::Semantic semantic, size_t semanticIndex);
         * @brief   移除对应语义解释的顶点属性
         * @param [in]  semantic        语义解释.
         * @param       semanticIndex   Zero-based index of the semantic.
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult removeAttribute(VertexAttribute::Semantic semantic,
            size_t semanticIndex);

        /**
         * @fn  virtual TResult VertexDeclaration::removeAllAttributes();
         * @brief   移除所有顶点属性
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult removeAllAttributes();

        /**
         * @fn  virtual TResult VertexDeclaration::updateAttribute(size_t pos, 
         *      size_t stream, size_t offset, VertexAttribute::Type type, 
         *      VertexAttribute::Semantic semantic, size_t semanticIndex);
         * @brief   更新顶点属性
         * @param [in]  pos             更新对应位置的顶点属性.
         * @param [in]  stream          数据流索引.
         * @param [in]  offset          The offset.
         * @param [in]  type            顶点数据类型.
         * @param [in]  semantic        顶点语义解释.
         * @param [in]  semanticIndex   语义索引.
         * @returns 调用成功返回 T3D_OK.
         */
        virtual TResult updateAttribute(size_t pos, size_t stream, 
            size_t offset, VertexAttribute::Type type, 
            VertexAttribute::Semantic semantic, size_t semanticIndex);

        /**
         * @fn  virtual const VertexAttribute 
         *      VertexDeclaration::*findAttributeBySemantic(
         *      VertexAttribute::Semantic semantic, size_t semanticIndex) const;
         * @brief   根据语义解释查找对应顶点属性对象
         * @param [in]  semantic        语义解释枚举.
         * @param [in]  semanticIndex   顶点语义索引.
         * @returns 查找成功返回对应的顶点属性对象，失败返回nullptr.
         */
        virtual const VertexAttribute *findAttributeBySemantic(
            VertexAttribute::Semantic semantic, size_t semanticIndex) const;
         
        /**
         * @fn  virtual size_t VertexDeclaration::getVertexSize(
         *      size_t source) const;
         * @brief   获取顶点字节大小
         * @param [in]  source  数据流索引.
         * @returns 返回字节大小.
         */
        virtual size_t getVertexSize(size_t source) const;

        /**
         * @fn  virtual VertexDeclarationPtr VertexDeclaration::clone() const;
         * @brief   克隆一个顶点声明对象
         * @returns 返回一个新的顶点声明对象.
         * @remarks 具体的渲染系统子类需要实现该接口.
         */
        virtual VertexDeclarationPtr clone() const;

    protected:
        /**
         * @fn  VertexDeclaration::VertexDeclaration();
         * @brief   构造函数
         */
        VertexDeclaration();

    protected:
        VertexAttriList mVertexAttributes;  /**< 顶点属性列表 */
    };
}


#endif  /*__T3D_HARDWARE_VERTEX_BUFFER_H__*/
