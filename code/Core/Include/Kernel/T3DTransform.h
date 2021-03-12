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


#ifndef __T3D_TRANSFORM_H__
#define __T3D_TRANSFORM_H__


#include "T3DPrerequisites.h"


namespace Tiny3D
{
    /**
     * @class   Transform
     * @brief   变换类
     */
    class T3D_ENGINE_API Transform
    {
    public:
        /**
         * @fn  Transform::Transform();
         * @brief   默认构造函数
         */
        Transform();

        /**
         * @fn  Transform::Transform(const Vector3 &translation, 
         *      const Vector3 &scaling, const Quaternion &orientation);
         * @brief   构造函数
         * @param [in]  translation : 平移.
         * @param [in]  scaling     : 缩放.
         * @param [in]  orientation : 朝向.
         */
        Transform(const Vector3 &translation, const Vector3 &scaling,
            const Quaternion &orientation);

        /**
         * @fn  Transform::Transform(const Transform &other);
         * @brief   拷贝构造函数
         * @param   other   The other.
         */
        Transform(const Transform &other);

        /**
         * @fn  Transform Transform::&operator=(const Transform &other);
         * @brief   重载赋值运算符
         * @param   other   The other.
         * @return  A shallow copy of this object.
         */
        Transform &operator =(const Transform &other);

        /**
         * @fn  void Transform::setTranslation(const Vector3 &translation);
         * @brief   设置平移量
         * @param [in]  translation : 平移量.
         */
        void setTranslation(const Vector3 &translation);

        /**
         * @fn  const Vector3 Transform::&getTranslation() const;
         * @brief   获取平移量
         * @return  The translation.
         */
        const Vector3 &getTranslation() const;

        /**
         * @fn  Vector3 Transform::&getTranslation();
         * @brief   获取平移量
         * @return  The translation.
         */
        Vector3 &getTranslation();

        /**
         * @fn  void Transform::setScaling(const Vector3 &scaling);
         * @brief   设置缩放量
         * @param [in]  scaling : 缩放量.
         */
        void setScaling(const Vector3 &scaling);

        /**
         * @fn  const Vector3 Transform::&getScaling() const;
         * @brief   获取缩放量
         * @return  The scaling.
         */
        const Vector3 &getScaling() const;

        /**
         * @fn  Vector3 Transform::&getScaling();
         * @brief   获取缩放量
         * @return  The scaling.
         */
        Vector3 &getScaling();

        /**
         * @fn  void Transform::setOrientation(const Quaternion &orientation);
         * @brief   设置朝向量
         * @param   orientation The orientation.
         */
        void setOrientation(const Quaternion &orientation);

        /**
         * @fn  const Quaternion Transform::&getOrientation() const;
         * @brief   获取朝向量
         * @return  The orientation.
         */
        const Quaternion &getOrientation() const;

        /**
         * @fn  Quaternion Transform::&getOrientation();
         * @brief   获取朝向量
         * @return  The orientation.
         */
        Quaternion &getOrientation();

        /**
         * @fn  void Transform::applyTransform(const Transform &xform1, 
         *      const Transform &xform2);
         * @brief   把一个变换应用到另外一个变换上
         * @param [in]  xform1  : 源变换.
         * @param [in]  xform2  : 应用到源变换上的变换.
         */
        void applyTransform(const Transform &xform1, const Transform &xform2);

        /**
         * @fn  void Transform::applyTransform(const Transform &xform, 
         *      const Vector3 &translation, const Quaternion &orientation, 
         *      const Vector3 &scaling);
         * @brief   把一个RTS变换应用到另外一个变换上
         * @param [in]  xform       : 源变换.
         * @param [in]  translation : 应用到源变换上的平移量.
         * @param [in]  orientation : 应用到源变换上的朝向量.
         * @param [in]  scaling     : 应用到源变换上的缩放量.
         */
        void applyTransform(const Transform &xform, const Vector3 &translation,
            const Quaternion &orientation, const Vector3 &scaling);

        /**
         * @fn  const Matrix4 Transform::&getAffineMatrix() const;
         * @brief   获取仿射变换矩阵
         * @return  The affine matrix.
         */
        const Matrix4 &getAffineMatrix() const;

        /**
         * @fn  void Transform::update();
         * @brief   更新变换
         */
        void update();

    private:
        /**
         * @fn  void Transform::makeAffineMatrix();
         * @brief   构造仿射变换
         */
        void makeAffineMatrix();

        Vector3     mTranslation;       /**< 平移量 */
        Vector3     mScaling;           /**< 缩放量 */
        Quaternion  mOrientation;       /**< 朝向量 */

        Matrix4     mAffineMatrix;      /**< 根据TRS构造的仿射变换 */
    };
}


#include "T3DTransform.inl"


#endif  /*__T3D_TRANSFORM_H__*/
