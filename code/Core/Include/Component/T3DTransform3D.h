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


#ifndef __T3D_TRANSFORM3D_H__
#define __T3D_TRANSFORM3D_H__


#include "Component/T3DComponent.h"
#include "Kernel/T3DTransform.h"


namespace Tiny3D
{
    /**
     * @bfrief 变换监听者
     */
    class T3D_ENGINE_API ITransformListener
    {
        T3D_DECLARE_INTERFACE(ITransformListener);
        T3D_DECLARE_CLASS();

    public:
        virtual void updateTransform(const Transform3D *xform) = 0;
    };

    /**
     * @class   Transform3D
     * @brief   带变换属性的场景树结点
     */
    class T3D_ENGINE_API Transform3D : public Component
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static Transform3DPtr 
         *      Transform3D::create(ID uID = E_CID_AUTOMATIC);
         * @brief   创建对象
         * @param [in]  uID (Optional) : 结点唯一标识，默认是自动生成.
         * @return  返回一个3D变换结点对象.
         */
        static Transform3DPtr create(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual Transform3D::~Transform3D();
         * @brief   析构函数
         */
        virtual ~Transform3D();

        /**
         * @fn  void Transform3D::setPosition(const Vector3 &pos);
         * @brief   设置在父结点空间坐标系下的位置
         * @param [in]  pos : 位置.
         * @sa  void setPosition(Real x, Real y, Real z)
         *
         * ### return   void.
         */
        void setPosition(const Vector3 &pos);

        /**
         * @fn  void Transform3D::setPosition(Real x, Real y, Real z);
         * @brief   设置在父结点空间坐标系下的位置
         * @param [in]  x   : X方向位置.
         * @param [in]  y   : Y方向位置.
         * @param [in]  z   : Z方向位置.
         * @sa  void setPosition(const Vector3 &amp;rkPos)
         */
        void setPosition(Real x, Real y, Real z);

        /**
         * @fn  const Vector3 Transform3D::&getPosition() const;
         * @brief   获取在父结点空间坐标系下的位置
         * @return  返回位置.
         */
        const Vector3 &getPosition() const;

        /**
         * @fn  void Transform3D::setOrientation(const Quaternion &orientation);
         * @brief   设置在父结点空间坐标系下的朝向
         * @param [in]  orientation : 方向四元素.
         * @sa  void setOrientation(Real w, Real x, Real y, Real z)
         */
        void setOrientation(const Quaternion &orientation);

        /**
         * @fn  void Transform3D::setOrientation(Real w, Real x, Real y, Real z);
         * @brief   设置在父结点空间坐标系下的朝向
         * @param [in]  w   : 四元素的w分量.
         * @param [in]  x   : 四元素的x分量.
         * @param [in]  y   : 四元素的y分量.
         * @param [in]  z   : 四元素的z分量.
         * @sa  void setOrientation(const Quaternion &amp;orientation)
         */
        void setOrientation(Real w, Real x, Real y, Real z);

        /**
         * @fn  void Transform3D::setOrientation(const Radian &radian, 
         *      const Vector3 &axis);
         * @brief   设置在父结点空间坐标系下的朝向
         * @param [in]  radian  : 旋转弧度.
         * @param [in]  axis    : 父结点空间下的旋转轴.
         * @sa  void setOrientation(const Quaternion &amp;ori)
         */
        void setOrientation(const Radian &radian, const Vector3 &axis);

        /**
         * @fn  const Quaternion Transform3D::&getOrientation() const;
         * @brief   获取在父结点空间坐标系下的朝向
         * @return  返回一个表示朝向的四元素对象.
         */
        const Quaternion &getOrientation() const;

        /**
         * @fn  void Transform3D::setScaling(const Vector3 &scaling);
         * @brief   设置在父结点空间坐标系下的缩放
         * @param [in]  scaling : 缩放值.
         * @sa  void setScaling(Real x, Real y, Real z)
         */
        void setScaling(const Vector3 &scaling);

        /**
         * @fn  void Transform3D::setScaling(Real x, Real y, Real z);
         * @brief   设置在父结点空间坐标系下的缩放
         * @param [in]  x   : X轴缩放值.
         * @param [in]  y   : Y轴缩放值.
         * @param [in]  z   : Z轴缩放值.
         * @sa  void setScaling(const Vector3 &amp;scaling)
         */
        void setScaling(Real x, Real y, Real z);

        /**
         * @fn  const Vector3 Transform3D::&getScaling() const;
         * @brief   获取在父结点空间坐标系下的缩放值
         * @return  返回一个表示三个周缩放值的向量，每个分量表示一个轴的缩放值.
         */
        const Vector3 &getScaling() const;

        /**
         * @fn  void Transform3D::translate(const Vector3 &offset);
         * @brief   在当前位置基础上平移一个偏移值
         * @param [in]  offset  : 三个坐标轴上的偏移值.
         */
        void translate(const Vector3 &offset);

        /**
         * @brief 在当前位置基础上平移一个偏移值
         * @param [in] x : X轴上偏移值
         * @param [in] y : Y轴上偏移值
         * @param [in] z : Z轴上偏移值
         * @return void
         */
        void translate(Real x, Real y, Real z);

        /**
         * @fn  void Transform3D::translate(const Vector3 &dir, Real step);
         * @brief   在当前位置基础上，朝一个向量所指方向移动某一个步长
         * @param [in]  dir     : 方向向量.
         * @param [in]  step    : 移动步长.
         */
        void translate(const Vector3 &dir, Real step);

        /**
         * @fn  void Transform3D::rotate(const Quaternion &orientation);
         * @brief   在当前方向上旋转一个四元素表示的旋转变换
         * @param [in]  orientation : 表示旋转变换的四元素.
         */
        void rotate(const Quaternion &orientation);

        /**
         * @fn  void Transform3D::rotate(const Vector3 &axis, const Radian &radians);
         * @brief   在当前方向上旋转一个给定旋转轴和绕该轴的旋转角表示的旋转变换
         * @param [in]  axis    : 旋转轴.
         * @param [in]  radians : 旋转角，单位：弧度.
         * @sa  void rotate(const Vector3 &amp;axis, const Degree &amp;degrees)
         * @sa  void rotate(const Quaternion &amp;orientation)
         */
        void rotate(const Vector3 &axis, const Radian &radians);

        /**
         * @fn  void Transform3D::rotate(const Vector3 &axis, const Degree &degrees);
         * @brief   在当前方向上旋转一个给定旋转轴和绕该轴的旋转角表示的旋转变换
         * @param [in]  axis    : 旋转轴.
         * @param [in]  degrees : 旋转角，单位：角度.
         * @sa  void rotate(const Vector3 &amp;axis, const Radian &amp;radians)
         * @sa  void rotate(const Quaternion &amp;orientation)
         */
        void rotate(const Vector3 &axis, const Degree &degrees);

        /**
         * @fn  void Transform3D::pitch(const Degree &degrees);
         * @brief   在当前方向上绕X轴旋转，倾斜角
         * @param [in]  degrees : 倾斜角，单位：角度.
         * @sa  void pitch(const Radian &amp;radians)
         */
        void pitch(const Degree &degrees);

        /**
         * @fn  void Transform3D::yaw(const Degree &degrees);
         * @brief   在当前方向上绕Y轴旋转，航向角
         * @param [in]  degrees : 航向角，单位：角度.
         * @sa  void yaw(const Radian &amp;radians)
         */
        void yaw(const Degree &degrees);

        /**
         * @fn  void Transform3D::roll(const Degree &degrees);
         * @brief   在当前方向上绕Z周旋转，翻滚角
         * @param [in]  degrees : 翻滚角，单位：角度.
         * @sa  void roll(const Radian &amp;radians)
         */
        void roll(const Degree &degrees);

        /**
         * @fn  void Transform3D::pitch(const Radian &radians);
         * @brief   在当前方向上绕X轴旋转，倾斜角
         * @param [in]  radians : 倾斜角，单位：弧度.
         * @sa  void pitch(const Degree &degrees)
         */
        void pitch(const Radian &radians);

        /**
         * @fn  void Transform3D::yaw(const Radian &radians);
         * @brief   在当前方向上绕Y轴旋转，航向角
         * @param [in]  radians : 航向角，单位：弧度.
         * @sa  void yaw(const Degree &degrees)
         */
        void yaw(const Radian &radians);

        /**
         * @fn  void Transform3D::roll(const Radian &radians);
         * @brief   在当前方向上绕Z周旋转，翻滚角
         * @param [in]  radians : 翻滚角，单位：弧度.
         * @sa  void roll(const Degree &degrees)
         */
        void roll(const Radian &radians);

        /**
         * @fn  void Transform3D::scale(const Vector3 &scaling);
         * @brief   在当前大小下缩放
         * @param [in]  scaling : 缩放值.
         * @sa  void scale(Real x, Real y, Real z)
         */
        void scale(const Vector3 &scaling);

        /**
         * @fn  void Transform3D::scale(Real x, Real y, Real z);
         * @brief   在当前大小下缩放
         * @param [in]  x   : X轴缩放值.
         * @param [in]  y   : Y轴缩放值.
         * @param [in]  z   : Z轴缩放值.
         * @sa  void scale(const Vector3 &scaling)
         */
        void scale(Real x, Real y, Real z);

        /**
         * @fn  void Transform3D::setLocalMatrix(const Matrix4 &m);
         * @brief   直接设置一个局部变换矩阵
         * @param [in]  m   : 局部变换矩阵.
         * @note 本接口会根据设置的局部变换矩阵来分解出旋转、平移、缩放三个分量.
         */
        void setLocalMatrix(const Matrix4 &m);

        /**
         * @fn  virtual const Transform 
         *      Transform3D::&getLocalToWorldTransform() const;
         * @brief   获取局部到世界的变换
         * @return  返回一个局部到世界的变换对象.
         */
        virtual const Transform &getLocalToWorldTransform() const;

        /**
         * @fn  Transform Transform3D::getLocalTransform() const;
         * @brief   获取局部变换
         * @return  返回一个局部变换对象.
         */
        Transform getLocalTransform() const;

        /**
         * @fn  virtual void Transform3D::updateTransform();
         * @brief   从父类继承，重写实现更新变换操作
         */
        virtual void update();

        /**
         * @fn  virtual void Transform3D::setDirty(bool isDirty, 
         *      bool recursive = false);
         * @brief   设置结点是否需要重绘、重新计算标记
         * @param [in]  isDirty     : 结点数据是否脏了标记.
         * @param [in]  recursive   (Optional) : 是否需要递归所有子节点都设置上该标记， 默认为只设置本结点.
         * @sa  bool isDirty() const
         *      
         */
        virtual void setDirty(bool isDirty, bool recursive = false);

        /**
         * @fn  bool Transform3D::isDirty() const;
         * @brief   返回结点数据是否脏，需要重新绘制、计算等标记
         * @return  返回结点数据脏标记.
         * @sa  void setDirty(bool isDirty, bool recursive)
         */
        bool isDirty() const;

        void addListener(ITransformListener *listener);

        void removeListner(ITransformListener *listener);

        /**
         * @fn  virtual ComponentPtr Transform3D::clone() const override;
         * @brief   从父类继承，重写父类克隆方法，以实现本类对象的复制操作
         * @return  返回一个新的3D变换结点对象.
         */
        virtual ComponentPtr clone() const override;

    protected:
        /**
         * @fn  Transform3D::Transform3D(ID uID = E_CID_AUTOMATIC);
         * @brief   默认构造函数
         * @param [in]  uID (Optional) : 结点唯一标识，默认是自动生成.
         */
        Transform3D(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual void 
         *      Transform3D::onAttachSceneNode(SceneNode *node) override;
         * @brief   从父类继承，重写以响应结点挂到父结点的通知事件
         * @param [in]  node    : 父结点对象.
         *              
         */
        virtual void onAttachSceneNode(SceneNode *node) override;

        /**
         * @fn  virtual void 
         *      Transform3D::onDetachSceneNode(SceneNode *node) override;
         * @brief   从父类继承，重写以响应结点从父结点拿走的通知事件
         * @param [in]  node    : 父结点对象.
         *              
         */
        virtual void onDetachSceneNode(SceneNode *node) override;

        /**
         * @fn  virtual TResult Transform3D::cloneProperties(
         *      ComponentPtr newObj) const override;
         * @brief   从父类继承，重写实现3D变换对象属性数据的复制
         * @param [in]  newObj  : 新的结点对象.
         * @return  void.
         */
        virtual TResult cloneProperties(ComponentPtr newObj) const override;

        void notifyListener() const;

    protected:
        typedef TList<ITransformListener *>     Listeners;
        typedef Listeners::iterator             ListenersItr;
        typedef Listeners::const_iterator       ListenersConstItr;

        Listeners           mListeners;     /**< 变换更新监听者对象 */

    private:
        Vector3             mPosition;      /**< 父节点坐标系下的局部位置 */
        Quaternion          mOrientation;   /**< 父节点坐标系下的局部朝向 */
        Vector3             mScaling;       /**< 父节点坐标系下的局部大小 */

        mutable Transform   mWorldTransform;/**< 从局部到世界的变换对象 */

        mutable bool        mIsDirty;       /**< 结点数据脏标记，需要重新计算 */
    };
}


#include "T3DTransform3D.inl"


#endif  /*__T3D_TRANSFORM3D_H__*/
