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


#ifndef __T3D_HARDWARE_BUFFER_H__
#define __T3D_HARDWARE_BUFFER_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "T3DErrorDef.h"


namespace Tiny3D
{
    /**
     * @class   HardwareBuffer
     * @brief   GPU 硬件缓冲区，用于 CPU 和 GPU 之间数据传递
     */
    class T3D_ENGINE_API HardwareBuffer : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @enum    Usage
         * @brief   緩衝區用法
         */
        enum class Usage : uint32_t
        {
            STATIC = 0,     /**< 數據在初始化设置后不能被修改 */
            DYNAMIC,        /**< 數據會被頻繁修改 */
            STREAM,         /**< 数据每帧都会被修改 */
        };

        /**
         * @enum    AccessMode
         * @brief   緩衝區訪問方式
         */
        enum AccessMode : uint32_t
        {
            CPU_NONE = 0,           /**< CPU 不访问 */
            CPU_WRITE = (1 << 0),   /**< CPU寫數據，GPU讀數據 */
            CPU_READ = (1 << 1),    /**< CPU讀數據，GPU寫數據 */
            GPU_COPY = (1 << 2)     /**< 從GPU讀數據，作為另一个GPU操作數據源 */
        };

        /**
         * @enum    LockOptions
         * @brief   缓冲区锁定访问标签
         * @remarks 对应的锁定选项需要跟创建资源的标签结合使用，具体如下：
         *  - READ 使用该选项时，该资源在创建的时候必须绑定 AccessMode::CPU_READ 标签。
         *  - WRITE 该资源在创建的时候必须绑定 AccessMode::CPU_WRITE 标签
         *  - READ_WRITE 该资源在创建的时候必须绑定 AccessMode::CPU_READ 和 AccessMode::CPU_WRITE 标签
         *  - WRITE_DISCARD 该资源在创建的时候必须绑定 AccessMode::CPU_ACCESS_WRITE 和 Usage::DYNAMIC 标签
         *  - WRITE_NO_OVERWRITE 该值只能用于顶点/索引缓冲区。 该资源在创建的时候需要有 AccessMode::CPU_WRITE 标签.
         */
        enum class LockOptions : uint32_t
        {
            READ = 0,           /**< 映射到内存的资源用于读取 */
            WRITE,              /**< 映射到内存的资源用于写入 */
            READ_WRITE,         /**< 映射到内存的资源用于读写 */
            WRITE_DISCARD,      /**< 映射到内存的资源用于写入，之前的资源数据将会被抛弃 */
            WRITE_NO_OVERWRITE  /**< 映射到内存的资源用于写入，但不能复写已经存在的资源 */
        };

        /**
         * @fn  virtual HardwareBuffer::~HardwareBuffer();
         * @brief   析构函数
         */
        virtual ~HardwareBuffer();

        /**
         * @fn  void HardwareBuffer::*lock(size_t offset, size_t size, 
         *      LockOptions options);
         * @brief   CPU锁定GPU缓冲区，访问其数据
         * @param [in]  offset  锁定区域相对缓冲区开始的偏移位置.
         * @param [in]  size    锁定缓冲区大小.
         * @param [in]  options 锁定选项.
         * @returns 成功返回锁定区域首地址，否则返回nullptr。.
         * @remarks 调用后要使用unlock解锁，重新让GPU获得访问数据权限.
         * @sa  enum class LockOptions
         * @sa  TResult HardwareBuffer::unlock()
         *
         * 
         */
        void *lock(size_t offset, size_t size, LockOptions options);

        /**
         * @fn  virtual void HardwareBuffer::*lock(LockOptions options);
         * @brief   CPU锁定GPU缓冲区，访问其数据
         * @param [in]  options 锁定方式选项.
         * @returns 成功返回锁定区域首地址，否则返回nullptr.
         * @remarks  调用后要使用unlock解锁，重新让GPU获得访问数据权限.
         * @sa  enum class LockOptions
         * @sa  TResult HardwareBuffer::unlock()
         */
        virtual void *lock(LockOptions options);

        /**
         * @fn  TResult HardwareBuffer::unlock();
         * @brief   解锁缓冲区
         * @returns 成功调用返回 T3D_OK.
         * @sa  void *HardwareBuffer::lock(size_t offset, size_t size, 
         *      LockOptions options)
         * @sa  void *HardwareBuffer::lock(LockOptions options)
         */
        TResult unlock();

        /**
         * @fn  virtual size_t HardwareBuffer::readData(size_t offset, size_t size, void *dst) = 0;
         * @brief   从缓冲区读取数据出来
         * @param [in]  offset  要读取的相对缓冲区首地址的偏移位置.
         * @param [in]  size    要读取缓冲区大小.
         * @param [in]  dst     存储返回读取到数据的缓冲区首地址.
         * @returns 返回读取的字节数.
         * @remarks 具体的渲染系统子类需要实现该接口.
         */
        virtual size_t readData(size_t offset, size_t size, void *dst) = 0;

        /**
         * @fn  virtual size_t HardwareBuffer::writeData(size_t offset, 
         *      size_t size, const void *src, 
         *      bool discardWholeBuffer = false) = 0;
         * @brief   向缓冲区写数据
         * @param [in]  offset              要写入的相对缓冲区首地址的偏移位置.
         * @param [in]  size                要写入缓冲区大小.
         * @param [in]  src                 写入的数据地址.
         * @param [in]  discardWholeBuffer  是否丢弃原有数据，默认不丢弃.
         * @returns 返回写入的字节数.
         * @remarks 具体的渲染系统子类需要实现该接口.
         */
        virtual size_t writeData(size_t offset, size_t size, const void *src,
            bool discardWholeBuffer = false) = 0;

        /**
         * @fn  virtual size_t HardwareBuffer::copyData(
         *      HardwareBufferPtr srcBuffer, size_t srcOffset, size_t dstOffset, 
         *      size_t size, bool discardWholeBuffer = false);
         * @brief   从源缓冲区复制数据到本缓冲区里
         * @param [in]  srcBuffer           源缓冲区对象.
         * @param [in]  srcOffset           源缓冲区偏移位置.
         * @param [in]  dstOffset           目标缓冲区偏移位置.
         * @param [in]  size                要复制的数据大小.
         * @param [in]  discardWholeBuffer  是否丢弃原有数据，默认不丢弃.
         * @returns 返回复制的字节数.
         */
        virtual size_t copyData(HardwareBufferPtr srcBuffer, size_t srcOffset,
            size_t dstOffset, size_t size, bool discardWholeBuffer = false);

        /**
         * @fn  virtual size_t HardwareBuffer::copyData(
         *      HardwareBufferPtr srcBuffer);
         * @brief   从源缓冲区全部复制数据到本缓冲区
         * @param [in]  srcBuffer   源缓冲区.
         * @returns 返回复制的字节数.
         */
        virtual size_t copyData(HardwareBufferPtr srcBuffer);

        /**
         * @fn  size_t HardwareBuffer::getBufferSize() const
         * @brief   获取缓冲区大小
         * @returns 返回缓冲区字节数大小.
         */
        size_t getBufferSize() const { return mBufferSize; }

        /**
         * @fn  Usage HardwareBuffer::getUsage() const
         * @brief   获取缓冲区用法
         * @returns 返回缓冲区用法.
         */
        Usage getUsage() const { return mUsage; }

        /**
         * @fn  AccessMode HardwareBuffer::getAccessMode() const
         * @brief   获取缓冲区访问方式
         * @returns 返回缓冲区访问方式.
         * @sa  enum AccessMode
         */
        uint32_t getAccessMode() const { return mAccessMode; }

        /**
         * @fn  bool HardwareBuffer::isLocked() const
         * @brief   获取缓存是否被锁
         * @returns 返回锁定状态.
         * @sa  enum class LockOptions
         * @sa  void *HardwareBuffer::lock(size_t offset, size_t size, 
         *      LockOptions options)
         * @sa  void *HardwareBuffer::lock(LockOptions options)
         */
        bool isLocked() const { return mIsLocked; }

    protected:
        /**
         * @fn  HardwareBuffer::HardwareBuffer(Usage usage, AccessMode mode);
         * @brief   构造函数
         * @param [in]  usage 缓冲区用法.
         * @param [in]  mode 缓冲区访问模式.
         */
        HardwareBuffer(Usage usage, uint32_t mode);

        /**
         * @fn  virtual void HardwareBuffer::*lockImpl(size_t offset, 
         *      size_t size, LockOptions options) = 0;
         * @brief   锁定缓冲区的具体实现接口
         * @param [in]  offset  锁定区域相对缓冲区开始偏移位置.
         * @param [in]  size    锁定区域大小.
         * @param [in]  options 锁定选项.
         * @returns 返回锁定缓冲区区域首地址.
         * @remarks 具体的渲染系统子类需要实现该接口.
         */
        virtual void *lockImpl(size_t offset, size_t size, 
            LockOptions options) = 0;

        /**
         * @fn  virtual TResult HardwareBuffer::unlockImpl() = 0;
         * @brief   解锁缓冲区的具体实现接口
         * @returns 成功调用返回 T3D_OK.
         * @remarks 具体的渲染系统子类需要实现该接口.
         */
        virtual TResult unlockImpl() = 0;

    protected:
        size_t      mBufferSize;        /**< 缓冲区大小 */
        size_t      mLockSize;          /**< 锁缓存大小 */
        size_t      mLockOffset;        /**< 锁缓存起始偏移 */

        Usage       mUsage;             /**< 缓冲区用法类型 */
        uint32_t    mAccessMode;        /**< 缓冲区访问方式 */

        bool        mIsLocked;          /**< 硬件缓存是否被锁 */
    };
}


#endif  /*__T3D_HARDWARE_BUFFER_H__*/
