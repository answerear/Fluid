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


#ifndef __T3D_GPU_CONST_BUFFER_H__
#define __T3D_GPU_CONST_BUFFER_H__


#include "Resource/T3DResource.h"
#include "Render/T3DHardwareConstantBuffer.h"
#include "Kernel/T3DCommon.h"


namespace Tiny3D
{
    /**
     * @class   GPUConstBuffer
     * @brief   GPU 常量緩衝區代理類，讓常量緩衝區有資源行為，用於資源管理.
     */
    class T3D_ENGINE_API GPUConstBuffer : public Resource
    {
        T3D_DECLARE_CLASS();

    public:
        struct DataDeclaration
        {
            DataDeclaration()
                : code(BuiltinConstantType::NONE)
                , type(BuiltinType::NONE)
                , count(0)
                , extraType(BuiltinType::NONE)
                , extraCount(0)
            {}

            BuiltinConstantType code;
            BuiltinType         type;
            uint32_t            count;
            BuiltinType         extraType;
            uint32_t            extraCount;
        };

        typedef TList<DataDeclaration>          Declarations;
        typedef Declarations::iterator          DeclarationsItr;
        typedef Declarations::const_iterator    DeclarationsConstItr;

        /**
         * @fn  static GPUConstBufferPtr 
         *      GPUConstBuffer::create(const String& name);
         * @brief   創建一個新的常量緩衝區資源對象
         * @param   name    資源名稱.
         * @returns 調用成功返回一個新建對象.
         */
        static GPUConstBufferPtr create(const String& name, size_t bufSize);

        /**
         * @fn  virtual GPUConstBuffer::~GPUConstBuffer();
         * @brief   析構函數
         */
        virtual ~GPUConstBuffer();

        /**
         * @fn  virtual Type GPUConstBuffer::getType() const override;
         * @brief   重寫 Resource::getType()
         * @returns 返回資源類型.
         */
        virtual Type getType() const override;

        /**
         * @fn  virtual TResult GPUConstBuffer::initWithData(size_t bufSize, 
         *      const void* buffer, HardwareBuffer::Usage usage, uint32_t mode);
         * @brief   用數據初始化硬件常量緩衝區
         * @param   bufSize 緩衝區大小.
         * @param   buffer  緩衝區數據.
         * @param   usage   緩衝區用法.
         * @param   mode    缓冲区访问方式.
         * @returns 調用成功返回T3D_OK.
         */
        virtual TResult initWithData(size_t bufSize, const void *buffer,
            HardwareBuffer::Usage usage, uint32_t mode);

        virtual TResult initWithData(HardwareBuffer::Usage usage, uint32_t mode);

        /**
         * @fn  TResult GPUConstBuffer::addDataDeclaration(
         *      BuiltinType type, uint8_t count);
         * @brief   添加一個數據類型聲明
         * @param   type    數據類型枚舉.
         * @param   count   數據數量.
         * @returns 調用成功返回 T3D_OK.
         * @sa  enum BuiltinType
         */
        TResult addDeclaration(BuiltinType type, uint32_t count, 
            uint8_t *data, size_t dataSize);

        /**
         * @fn  TResult GPUConstBuffer::addDeclaration(BuiltinConstantType code, 
         *      BuiltinType type, uint32_t count, BuiltinType extraType, 
         *      uint32_t extraCount);
         * @brief   Adds a declaration
         * @param   code        The code.
         * @param   type        The type.
         * @param   count       Number of.
         * @param   extraType   Type of the extra.
         * @param   extraCount  Number of extras.
         * @return  A TResult.
         */
        TResult addDeclaration(BuiltinConstantType code, BuiltinType type,
            uint32_t count, BuiltinType extraType, uint32_t extraCount);

        /**
         * @fn  TResult GPUConstBuffer::removeDataDeclaration(size_t index);
         * @brief   根據索引移除一個數據類型聲明
         * @param   index   位置索引.
         * @returns 調用成功返回 T3D_OK.
         */
        TResult removeDeclaration(size_t index);

        /**
         * @fn  DataDeclaration GPUConstBuffer::getDataType(size_t index) const;
         * @brief   根據索引獲取對應的索引位置的數據類型
         * @param   index   索引位置.
         * @returns 返回對應索引位置的數據聲明.
         */
        const DataDeclaration &getDeclaration(size_t index) const;

        /**
         * @fn  const DataTypeList GPUConstBuffer::&getDataTypeList() const;
         * @brief   獲取數據類型列表
         * @returns 返回數據類型列表.
         */
        const Declarations& getDeclarations() const { return mDeclarations; }

        /**
         * @fn  TResult GPUConstBuffer::updateData( BuiltinConstantType code, 
         *      uint8_t *data, size_t dataSize);
         * @brief   Updates the data
         * @param           code        The code.
         * @param [in,out]  data        If non-null, the data.
         * @param           dataSize    Size of the data.
         * @return  A TResult.
         */
        TResult updateData(
            BuiltinConstantType code, uint8_t *data, size_t dataSize);

        /**
         * @fn  TResult GPUConstBuffer::updateData(uint8_t *data, 
         *      size_t dataSize, size_t offset);
         * @brief   Updates the data
         * @param [in,out]  data        If non-null, the data.
         * @param           dataSize    Size of the data.
         * @param           offset      The offset.
         * @return  A TResult.
         */
        TResult updateData(uint8_t *data, size_t dataSize, size_t offset);

        /**
         * @fn  TResult GPUConstBuffer::flushData(size_t offset, size_t size, 
         *      const void *buffer, bool discardWholeBuffer = true);
         * @brief   Flushes the data
         * @param   offset              The offset.
         * @param   size                The size.
         * @param   buffer              The buffer.
         * @param   discardWholeBuffer  (Optional) True to discard whole buffer.
         * @return  A TResult.
         */
        TResult flushData(size_t offset, size_t size, const void *buffer, 
            bool discardWholeBuffer = true);

        /**
         * @fn  TResult GPUConstBuffer::flushData(bool discardWholeBuffer = true);
         * @brief   Flushes the data described by discardWholeBuffer
         * @param   discardWholeBuffer  (Optional) True to discard whole buffer.
         * @return  A TResult.
         */
        TResult flushData(bool discardWholeBuffer = true);
        
        /**
         * @fn  size_t GPUConstBuffer::getBufferSize() const;
         * @brief   獲取緩衝區的字節數大小
         * @returns 返回緩衝區的字節數大小.
         */
        size_t getBufferSize() const
        {
            return mBufSize;
        }

        /**
         * @fn  HardwareConstantBufferPtr GPUConstBuffer::getBufferImpl() const;
         * @brief   獲取具體跟平台有關的對象
         * @returns 返回具體跟平台有關的對象.
         */
        HardwareConstantBufferPtr getBufferImpl() const { return mBufferImpl; }

    protected:
        /**
         * @fn  GPUConstBuffer::GPUConstBuffer(const String& name);
         * @brief   構造函數
         * @param   name    資源名稱.
         */
        GPUConstBuffer(const String& name, size_t bufSize);

        /**
         * @fn  virtual TResult GPUConstBuffer::load() override;
         * @brief   重寫 Resource::load()
         * @returns 調用成功返回T3D_OK.
         */
        virtual TResult load() override;

        /**
         * @fn  virtual TResult GPUConstBuffer::unload() override;
         * @brief   重寫 Resource::unlaod()
         * @returns 調用成功返回T3D_OK.
         */
        virtual TResult unload() override;

        /**
         * @fn  virtual ResourcePtr GPUConstBuffer::clone() const override;
         * @brief   重寫 Resource::clone()
         * @returns 調用成功返回一個新資源對象.
         */
        virtual ResourcePtr clone() const override;

    protected:
        typedef TMap<BuiltinConstantType, uint32_t> QuickSearchOffsets;
        typedef QuickSearchOffsets::value_type      QuickSearchOffsetsValue;

        size_t                      mBufSize;           /**< 緩衝區大小 */
        uint8_t                     *mBuffer;           /**< 緩衝區數據 */
        HardwareBuffer::Usage       mUsage;             /**< 緩衝區用法 */
        uint32_t                    mAccessMode;        /**< 缓冲区访问方式 */
        bool                        mHasData;           /**< 是否初始化數據 */
        HardwareConstantBufferPtr   mBufferImpl;        /**< 具體實現類 */

        Declarations                mDeclarations;      /**< 數據聲明列表 */
        QuickSearchOffsets          mSearchOffsets;     /**< 快速搜索偏移 */
    };
}


#endif  /*__T3D_GPU_CONST_BUFFER_H__*/
