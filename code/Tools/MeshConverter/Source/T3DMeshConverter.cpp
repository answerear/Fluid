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


#include "T3DMeshConverter.h"
#include "T3DConverterOptions.h"
#include "T3DConverterCommand.h"
#include "T3DFBXReader.h"
#include "T3DOGREReader.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    MeshConverter::MeshConverter()
    {

    }

    //--------------------------------------------------------------------------

    MeshConverter::~MeshConverter()
    {

    }

    //--------------------------------------------------------------------------

    TResult MeshConverter::execute(int32_t argc, char *argv[])
    {
        TResult ret = T3D_OK;

        do 
        {
            ConverterOptions opts;
            ConverterCommand cmd;

            bool rt = cmd.parse(argc, argv, opts);

            if (rt)
            {
                // 根据输入参数，创建输入文件解析器对象
                ModelReaderPtr reader;

                String name = opts.mSrcPath;
                Dir dir;
                dir.findFile(name);
                name = dir.getFileTitle();

                switch (opts.mSrcFileType)
                {
                case MeshFileType::FBX:
                    reader = FBXReader::create(opts.mDstFileType == MeshFileType::T3T, name);
                    break;
                case MeshFileType::OGRE:
                    reader = OGREReader::create();
                    break;
                default:
                    ret = T3D_ERR_RES_INVALID_FILETYPE;
                    MCONV_LOG_ERROR("Invalid input file type [%d] !", 
                        opts.mSrcFileType);
                    break;
                }

                if (T3D_FAILED(ret))
                {
                    break;
                }

                ModelManagerPtr modelMgr = ModelManager::create();


                // 创建引擎序列化模块模块
                SerializerManagerPtr mgr = SerializerManager::create();
                uint32_t flags = FileDataStream::E_MODE_WRITE_ONLY;

                // 根据输入参数，设置输出文件是二进制还是文本
                switch (opts.mDstFileType)
                {
                case MeshFileType::T3B:
                    mgr->setFileMode(SerializerManager::FileMode::BINARY);
                    break;
                case MeshFileType::T3T:
                    mgr->setFileMode(SerializerManager::FileMode::TEXT);
                    flags |= FileDataStream::E_MODE_TEXT;
                    break;
                default:
                    ret = T3D_ERR_RES_INVALID_FILETYPE;
                    MCONV_LOG_ERROR("Invalid output file type [%d] !", 
                        opts.mDstFileType);
                    break;
                }

                if (T3D_FAILED(ret))
                {
                    break;
                }

                // 读取输入文件
                FileDataStream is;
                rt = is.open(opts.mSrcPath.c_str(), 
                    FileDataStream::E_MODE_READ_ONLY);
                if (!rt)
                {
                    MCONV_LOG_ERROR("Invalid input file path [%s] !", 
                        opts.mSrcPath.c_str());
                    break;
                }

                ModelPtr model = Model::create(opts.mSrcPath);
                //ModelPtr model = modelMgr->loadModel(opts.mSrcPath);
                ret = reader->parse(is, model);
                if (T3D_FAILED(ret))
                {
                    is.close();
                    break;
                }

                is.close();

                // 写到输出文件
                FileDataStream os;
                rt = os.open(opts.mDstPath.c_str(), flags);
                if (!rt)
                {
                    MCONV_LOG_ERROR("Invalid output file path [%s] !", 
                        opts.mDstPath.c_str());
                    break;
                }

                ret = mgr->serializeModel(os, model);
                if (T3D_FAILED(ret))
                {
                    os.close();
                    break;
                }

                os.close();

                modelMgr->unloadModel(model);
            }
        } while (0);
        return ret;
    }
}

