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


#ifndef __T3D_CAMERA_H__
#define __T3D_CAMERA_H__


#include "Component/T3DComponent.h"
#include "Component/T3DTransform3D.h"
#include "Bound/T3DBound.h"


namespace Tiny3D
{
    /**
     * @class   Camera
     * @brief   场景相机结点类
     */
    class T3D_ENGINE_API Camera 
        : public Component
        , public ITransformListener
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @enum    Type
         * @brief   投影类型
         */
        enum class Type : uint32_t
        {
            ORTHOGRAPHIC = 0,      /**< 正交投影矩阵 */
            PERSPECTIVE,           /**< 透视投影矩阵 */
        };

        /**
         * @fn  static CameraPtr Camera::create(ID uID = E_CID_AUTOMATIC);
         * @brief   创建相机结点对象
         * @param [in]  uID (Optional) : 结点ID，默认自动生成.
         * @return  返回一个相机结点对象.
         */
        static CameraPtr create(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual Camera::~Camera();
         * @brief   析构函数
         */
        virtual ~Camera();

        /**
         * @fn  virtual ComponentPtr Camera::clone() const override;
         * @brief   重写基类接口
         * @return  A copy of this object.
         * @sa  NodePtr Node::clone() const
         */
        virtual ComponentPtr clone() const override;

        /**
         * @fn  void Camera::lookAt(const Vector3 &pos, const Vector3 &obj, 
         *      const Vector3 &up);
         * @brief   专门提供给挂相机结点的3D变换结点使用，用于构建UVN相机.
         * @param [in]  pos : 相机位置.
         * @param [in]  obj : 相机观察物体位置.
         * @param [in]  up  : 上方向向量.
         * @note UVN相机通过此接口可以构造一个变换矩阵出来.
         */
        void lookAt(const Vector3 &pos, const Vector3 &obj, const Vector3 &up);

        /**
         * @fn  void Camera::setObjectMask(uint32_t mask);
         * @brief   设置相机能看见的场景结点掩码
         * @param   mask    The mask.
         * @sa  uint32_t getObjectMask() const
         * @remarks 掩码可以通过“或”操作，设置多个掩码，只要场景结点中的相机掩码 
         *          CameraMask 设置的跟本相机中其中一个掩码一致的，
         *          均能渲染到本相机对应的视口中。.
         */
        void setObjectMask(uint32_t mask);

        /**
         * @fn  uint32_t Camera::getObjectMask() const;
         * @brief   获取相机能看见的场景结点掩码
         * @return  The object mask.
         * @sa  void setObjectMask(uint32_t mask)
         */
        uint32_t getObjectMask() const;

        /**
         * @fn  void Camera::setProjectionType(Type type);
         * @brief   设置投影类型
         * @param [in]  type    : 投影类型.
         * @sa  enum Type
         */
        void setProjectionType(Type type);

        /**
         * @fn  Type Camera::getProjectionType() const;
         * @brief   获取投影类型
         * @return  返回投影类型.
         * @sa  enum Type
         */
        Type getProjectionType() const;

        /**
         * @fn  void Camera::setPerspectiveParams(const Radian &fovY, 
         *      Real aspect, Real nearDist, Real farDist);
         * @brief   设置透视投影变换需要的参数
         * @param [in]  fovY        : top和bottom的夹角.
         * @param [in]  aspect      : 投影平面宽高比.
         * @param [in]  nearDist    : 近平面距离.
         * @param [in]  farDist     : 远平面距离.
         */
        void setPerspectiveParams(const Radian &fovY, Real aspect,
            Real nearDist, Real farDist);

        /**
         * @fn  void Camera::setOrthographicParams(Real width, Real height, 
         *      Real nearDist, Real farDist);
         * @brief   设置正交投影变换需要的参数
         * @param [in]  width       : 视口宽度.
         * @param [in]  height      : 视口高度.
         * @param [in]  nearDist    : 近平面距离.
         * @param [in]  farDist     : 远平面距离.
         */
        void setOrthographicParams(Real width, Real height, Real nearDist,
            Real farDist);

        /**
         * @fn  Real Camera::getAspectRatio() const;
         * @brief   获取宽高比
         * @return  返回宽高比.
         */
        Real getAspectRatio() const;

        /**
         * @fn  const Radian Camera::&getFovY() const;
         * @brief   获取纵向视角大小
         * @return  返回纵向视角大小.
         */
        const Radian &getFovY() const;

        /**
         * @fn  Real Camera::getNearPlaneDistance() const;
         * @brief   获取近平面距离
         * @return  返回近平面距离.
         */
        Real getNearPlaneDistance() const;

        /**
         * @fn  Real Camera::getFarPlaneDistance() const;
         * @brief   获取远平面距离
         * @return  返回远平面距离.
         */
        Real getFarPlaneDistance() const;

        /**
         * @fn  BoundPtr Camera::getBound() const;
         * @brief   获取相机的视锥体碰撞体
         * @return  返回相机关联的视锥体碰撞体.
         */
        BoundPtr getBound() const;

        /**
         * @fn  const Matrix4 Camera::&getViewMatrix() const;
         * @brief   获取观察空间变换矩阵
         * @return  返回观察空间变换矩阵.
         */
        const Matrix4 &getViewMatrix() const;

        /**
         * @fn  const Matrix4 Camera::&getProjectionMatrix() const;
         * @brief   获取投影变换矩阵
         * @return  返回投影变换矩阵.
         */
        const Matrix4 &getProjectionMatrix() const;

        /**
         * @fn  virtual void Camera::updateTransform() override;
         * @brief   实现基类接口
         */
        virtual void update() override;

    protected:
        /**
         * @fn  Camera::Camera(ID uID = E_CID_AUTOMATIC);
         * @brief   构造函数
         * @param   uID (Optional) The identifier.
         */
        Camera(ID uID = E_CID_AUTOMATIC);

        /**
         * @fn  virtual TResult Camera::init();
         * @brief   初始化对象
         * @return  A TResult.
         */
        virtual TResult init();

        /**
         * @fn  virtual TResult 
         *      Camera::cloneProperties(ComponentPtr newObj) const override;
         * @brief   实现基类接口
         * @param   newObj  The new object.
         * @return  A TResult.
         */
        virtual TResult cloneProperties(ComponentPtr newObj) const override;

        virtual void updateTransform(const Transform3D *xform) override;

    protected:
        BoundPtr        mBound;         /**< 视锥体碰撞体 */

        Type            mProjType;      /**< 投影类型 */

        uint32_t        mObjectMask;    /**< 相机看到的物体掩码 */

        Radian          mFovY;          /**< 上下平面夹角，用于透视投影 */
        Real            mAspectRatio;   /**< 宽高比，用于透视投影 */
        Real            mWidth;         /**< 视口宽度，用于正交投影 */
        Real            mHeight;        /**< 视口高度，用于正交投影 */
        Real            mNear;          /**< 近平面距离 */
        Real            mFar;           /**< 远平面距离 */

        mutable Matrix4 mViewMatrix;    /**< 观察变换矩阵 */
        mutable Matrix4 mProjMatrix;    /**< 投影变换矩阵 */

        mutable bool    mIsViewDirty;   /**< 是否需要更新观察变换矩阵 */
        mutable bool    mIsFrustumDirty;/**< 是否需要更新投影变换 */
    };
}


#include "T3DCamera.inl"


#endif  /*__T3D_CAMERA_H__*/
