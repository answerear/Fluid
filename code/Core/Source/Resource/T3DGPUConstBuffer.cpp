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


#include "Resource/T3DGPUConstBuffer.h"
#include "Render/T3DHardwareBufferManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(GPUConstBuffer, Resource);

    //--------------------------------------------------------------------------

    GPUConstBufferPtr GPUConstBuffer::create(const String& name, size_t bufSize)
    {
        GPUConstBufferPtr mgr = new GPUConstBuffer(name, bufSize);
        mgr->release();
        return mgr;
    }

    //--------------------------------------------------------------------------

    GPUConstBuffer::GPUConstBuffer(const String& name, size_t bufSize)
        : Resource(name)
        , mBufSize(bufSize)
        , mBuffer(nullptr)
        , mUsage(HardwareBuffer::Usage::STATIC)
        , mAccessMode(0)
        , mHasData(false)
        , mBufferImpl(nullptr)
    {
        if (mBufSize > 0)
        {
            mBuffer = new uint8_t[mBufSize];
        }
    }

    //--------------------------------------------------------------------------

    GPUConstBuffer::~GPUConstBuffer()
    {
        T3D_SAFE_DELETE_ARRAY(mBuffer);
    }

    //--------------------------------------------------------------------------

    Resource::Type GPUConstBuffer::getType() const
    {
        return Type::E_RT_GPUCBUFFER;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBuffer::initWithData(size_t bufSize, const void *buffer,
        HardwareBuffer::Usage usage, uint32_t mode)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mHasData)
            {
                ret = T3D_ERR_RES_ALREADY_INIT;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "GPU constant buffer has alreay initialized with data !");
                break;
            }

            if ((mBufSize & 0xF) != 0)
            {
                // GPU常量緩衝需要128位(16字節)對齊
                ret = T3D_ERR_RES_INVALID_PARAM;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "GPU constant buffer must be 128 bytes alignment !");
                break;
            }

            if (bufSize != mBufSize)
            {
                // 輸入的大小應該跟數據類型定義的大小匹配
                ret = T3D_ERR_RES_INVALID_PARAM;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Input data size must equal the size of data type declaration !");
                break;
            }

            mBufferImpl = T3D_HARDWARE_BUFFER_MGR.createConstantBuffer(
                bufSize, buffer, usage, mode);
            if (mBufferImpl == nullptr)
            {
                ret = T3D_ERR_RES_LOAD_FAILED;
                break;
            }

            mUsage = usage;
            mAccessMode = mode;
            mHasData = true;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBuffer::initWithData(
        HardwareBuffer::Usage usage, uint32_t mode)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mHasData)
            {
                ret = T3D_ERR_RES_ALREADY_INIT;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "GPU constant buffer has alreay initialized with data !");
                break;
            }

            if ((mBufSize & 0xF) != 0)
            {
                // GPU常量緩衝需要128位(16字節)對齊
                ret = T3D_ERR_RES_INVALID_PARAM;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "GPU constant buffer must be 128 bytes alignment !");
                break;
            }

            mBufferImpl = T3D_HARDWARE_BUFFER_MGR.createConstantBuffer(
                mBufSize, mBuffer, usage, mode);
            if (mBufferImpl == nullptr)
            {
                ret = T3D_ERR_RES_LOAD_FAILED;
                break;
            }

            mUsage = usage;
            mAccessMode = mode;
            mHasData = true;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBuffer::load()
    {
        // Do nothing here.
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBuffer::unload()
    {
        TResult ret = T3D_OK;

        mBufferImpl = nullptr;
        mHasData = false;
        mBufSize = 0;
        mBuffer = nullptr;

        return ret;
    }

    //--------------------------------------------------------------------------

    ResourcePtr GPUConstBuffer::clone() const
    {
        GPUConstBufferPtr buffer;

        do 
        {
            buffer = GPUConstBuffer::create(mName, mBufSize);

            if (buffer != nullptr)
            {
                memcpy(buffer->mBuffer, mBuffer, mBufSize);
                TResult ret = buffer->initWithData(mUsage, mAccessMode);

                if (T3D_FAILED(ret))
                {
                    buffer = nullptr;
                    break;
                }
            }
        } while (0);

        return buffer;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBuffer::addDeclaration(BuiltinType type, uint32_t count, 
        uint8_t *data, size_t dataSize)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mHasData)
            {
                // 已經有數據了，不能再添加數據類型聲明
                ret = T3D_ERR_RES_ALREADY_INIT;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "GPU constant buffer has already initialized with data !");
                break;

            }

            // 计算数据偏移
            size_t offset = 0;
            auto itr = mDeclarations.begin();
            while (itr != mDeclarations.end())
            {
                offset += itr->count;
                offset += itr->extraCount;
                offset *= 4;
                ++itr;
            }

            DataDeclaration decl;
            decl.code = BuiltinConstantType::NONE;
            decl.type = type;
            decl.count = count;
            mDeclarations.push_back(decl);

            if (mBufSize > 0 && mBuffer != nullptr)
            {
                memcpy(mBuffer+offset, data, dataSize);
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBuffer::addDeclaration(BuiltinConstantType code, 
        BuiltinType type, uint32_t count, BuiltinType extraType, 
        uint32_t extraCount)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mHasData)
            {
                // 已經有數據了，不能再添加數據類型聲明
                ret = T3D_ERR_RES_ALREADY_INIT;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "GPU constant buffer has already initialized with data !");
                break;

            }

            // 计算数据偏移
            size_t offset = 0;
            auto itr = mDeclarations.begin();
            while (itr != mDeclarations.end())
            {
                offset += itr->count;
                offset += itr->extraCount;
                offset *= 4;
                ++itr;
            }

            DataDeclaration decl;
            decl.code = code;
            decl.type = type;
            decl.count = count;
            decl.extraType = extraType;
            decl.extraCount = extraCount;
            mDeclarations.push_back(decl);

            mSearchOffsets.insert(QuickSearchOffsetsValue(code, offset));
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBuffer::removeDeclaration(size_t index)
    {
        TResult ret = T3D_OK;

        do
        {
            if (mHasData)
            {
                ret = T3D_ERR_RES_ALREADY_INIT;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "GPU constant buffer has already initialized with data !");
                break;
            }

            bool found = false;
            size_t i = 0;

            for (auto itr = mDeclarations.begin();
                itr != mDeclarations.end();
                ++itr)
            {
                if (i == index)
                {
                    found = true;
                    mBufSize -= itr->count;
                    mDeclarations.erase(itr);
                    break;
                }

                ++i;
            }

            if (!found)
            {
                ret = T3D_ERR_NOT_FOUND;
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    const GPUConstBuffer::DataDeclaration
        &GPUConstBuffer::getDeclaration(size_t index) const
    {
        static DataDeclaration DECL_NULL;

        do
        {
            bool found = false;
            size_t i = 0;

            auto itr = mDeclarations.begin();
            while (itr != mDeclarations.end())
            {
                if (i == index)
                {
                    found = true;
                    return *itr;
                }

                ++i;
                ++itr;
            }
        } while (0);

        return DECL_NULL;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBuffer::updateData(
        BuiltinConstantType code, uint8_t *data, size_t dataSize)
    {
        TResult ret = T3D_OK;

        do
        {
            auto itr = mSearchOffsets.find(code);

            if (itr == mSearchOffsets.end())
            {
                ret = T3D_ERR_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Counld not find data offset !");
                break;
            }

            uint32_t offset = itr->second;
            if (offset >= mBufSize)
            {
                ret = T3D_ERR_OUT_OF_BOUND;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Data offset is out of bound !");
                break;
            }

            size_t len = (offset + dataSize < mBufSize) 
                ? dataSize: (mBufSize - offset);
            memcpy(mBuffer + offset, data, len);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBuffer::updateData(
        uint8_t *data, size_t dataSize, size_t offset)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (offset >= mBufSize)
            {
                ret = T3D_ERR_OUT_OF_BOUND;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Data offset is out of bound !");
                break;
            }

            size_t len = (offset + dataSize < mBufSize) 
                ? dataSize : (mBufSize - offset);
            memcpy(mBuffer + offset, data, len);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBuffer::flushData(size_t offset, size_t size, 
        const void *buffer, bool discardWholeBuffer /* = true */)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mBufferImpl == nullptr)
            {
                ret = T3D_ERR_SYS_NOT_INIT;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, 
                    "Have not create hardware buffer !");
                break;
            }

            size_t bytesOfWritten = mBufferImpl->writeData(
                offset, size, buffer, discardWholeBuffer);

            if (bytesOfWritten != size)
            {
                ret = T3D_ERR_INVALID_SIZE;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Write data failed !");
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult GPUConstBuffer::flushData(bool discardWholeBuffer /* = true */)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mBufferImpl == nullptr)
            {
                ret = T3D_ERR_SYS_NOT_INIT;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Have not create hardware buffer !");
                break;
            }

            size_t bytesOfWritten = mBufferImpl->writeData(
                0, mBufSize, mBuffer, discardWholeBuffer);

            if (bytesOfWritten != mBufSize)
            {
                ret = T3D_ERR_INVALID_SIZE;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Write data failed !");
                break;
            }
        } while (0);

        return ret;
    }
}
