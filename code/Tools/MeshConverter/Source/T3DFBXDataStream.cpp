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


#include "T3DFBXDataStream.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    FbxDataStream::FbxDataStream(DataStream &stream, FbxManager *manager, bool readable)
        : mStream(stream)
        , mReaderID(-1)
        , mWriterID(-1)
    {
        if (readable)
        {
            const char *format = "FBX (*.fbx)";
            mReaderID = manager->GetIOPluginRegistry()->FindReaderIDByDescription(format);
            mWriterID = -1;
        }
        else
        {
            const char *format = "FBX ascii (*.fbx)";
            mWriterID = manager->GetIOPluginRegistry()->FindWriterIDByDescription(format);
            mReaderID = -1;
        }
    }

    //--------------------------------------------------------------------------

    FbxDataStream::~FbxDataStream()
    {

    }

    //--------------------------------------------------------------------------

    FbxStream::EState FbxDataStream::GetState()
    {
        return EState::eOpen;
    }

    //--------------------------------------------------------------------------

    bool FbxDataStream::Open(void *pStreamData)
    {
        mStream.seek(0, false);
        return true;
    }

    //--------------------------------------------------------------------------

    bool FbxDataStream::Close()
    {
        return true;
    }

    //--------------------------------------------------------------------------

    bool FbxDataStream::Flush()
    {
        return true;
    }

    //--------------------------------------------------------------------------

    int FbxDataStream::Write(const void *pData, int size)
    {
        return mStream.write((void *)pData, size);
    }

    //--------------------------------------------------------------------------

    int FbxDataStream::Read(void *pData, int size) const
    {
        return mStream.read(pData, size);
    }

    //--------------------------------------------------------------------------

    int FbxDataStream::GetReaderID() const
    {
        return mReaderID;
    }

    //--------------------------------------------------------------------------

    int FbxDataStream::GetWriterID() const
    {
        return mWriterID;
    }

    //--------------------------------------------------------------------------

    void FbxDataStream::Seek(const FbxInt64 &pOffset, const FbxFile::ESeekPos &pSeekPos)
    {
        switch (pSeekPos)
        {
        case FbxFile::ESeekPos::eBegin:
            {
                mStream.seek(pOffset, false);
            }
            break;
        case FbxFile::ESeekPos::eCurrent:
            {
                mStream.seek(pOffset, true);
            }
            break;
        case FbxFile::ESeekPos::eEnd:
            {
                mStream.seek(mStream.size() - 1, false);
                mStream.seek(pOffset, true);
            }
            break;
        }
    }

    //--------------------------------------------------------------------------

    long FbxDataStream::GetPosition() const
    {
        return mStream.tell();
    }

    //--------------------------------------------------------------------------

    void FbxDataStream::SetPosition(long pPosition)
    {
        mStream.seek(pPosition, false);
    }

    //--------------------------------------------------------------------------

    int FbxDataStream::GetError() const
    {
        return 0;
    }

    //--------------------------------------------------------------------------

    void FbxDataStream::ClearError()
    {

    }
}

