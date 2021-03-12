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


#ifndef __T3D_FBX_DATA_STREAM_H__
#define __T3D_FBX_DATA_STREAM_H__



#include "T3DConverterPrerequisites.h"


namespace Tiny3D
{
    class FbxDataStream : public FbxStream
    {
    public:
        FbxDataStream(DataStream &stream, FbxManager *manager, bool readable);

        virtual ~FbxDataStream();

        virtual EState GetState() override;

        virtual bool Open(void *pStreamData) override;

        virtual bool Close() override;

        virtual bool Flush() override;

        virtual int Write(const void *pData, int size) override;

        virtual int Read(void *pData, int size) const override;

        virtual int GetReaderID() const override;

        virtual int GetWriterID() const override;

        virtual void Seek(const FbxInt64 &pOffset, const FbxFile::ESeekPos &pSeekPos) override;

        virtual long GetPosition() const override;

        virtual void SetPosition(long pPosition) override;

        virtual int GetError() const override;

        virtual void ClearError() override;

    protected:
        DataStream &mStream;
        int mReaderID;
        int mWriterID;
    };
}

#endif  /*__T3D_FBX_DATA_STREAM_H__*/
