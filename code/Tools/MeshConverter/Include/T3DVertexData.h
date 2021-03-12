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


#ifndef __T3D_VERTEX_DATA_H__
#define __T3D_VERTEX_DATA_H__


#include "T3DConverterPrerequisites.h"


namespace Tiny3D
{
    typedef std::list<Vector2>              VectorElements2;
    typedef VectorElements2::iterator       VectorElements2Itr;
    typedef VectorElements2::const_iterator VectorElements2ConstItr;

    typedef std::list<Vector3>              VectorElements3;
    typedef VectorElements3::iterator       VectorElements3Itr;
    typedef VectorElements3::const_iterator VectorElements3ConstItr;

    typedef std::list<Vector4>              VectorElements4;
    typedef VectorElements4::iterator       VectorElements4Itr;
    typedef VectorElements4::const_iterator VectorElements4ConstItr;

    typedef std::list<ColorRGBA>            ColorElement;
    typedef ColorElement::iterator          ColorElementItr;
    typedef ColorElement::const_iterator    ColorElementConstItr;

    typedef std::vector<int>                Indices;
    typedef Indices::iterator               IndicesItr;
    typedef Indices::const_iterator         IndicesConstItr;

    typedef std::list<uint16_t>             BlendIndices;
    typedef BlendIndices::iterator          BlendIndicesItr;
    typedef BlendIndices::const_iterator    BlendIndicesConstItr;

    class BlendInfo
    {
    public:
        BlendInfo()
            : mBlendIndex(-1)
            , mBlendWeight(0.0f)
        {

        }

        bool operator <(const BlendInfo &other) const
        {
            return mBlendWeight < other.mBlendWeight;
        }

        bool operator ==(const BlendInfo &other) const
        {
            return (mBlendWeight == other.mBlendWeight && mBlendIndex == other.mBlendIndex);
        }

        uint8_t     mBlendIndex;
        float       mBlendWeight;
    };

    typedef std::set<BlendInfo>                 BlendInfoList;
    typedef BlendInfoList::iterator             BlendInfoListItr;
    typedef BlendInfoList::const_iterator       BlendInfoListConstItr;

    class Vertex
    {
    public:

        Vertex()
            : mCtrlPointIdx(0)
            , mPosition(0.0, 0.0, 0.0)
            , mMaterialIdx(-1)
            , mIndex(0)
            , mHash(0)
        {

        }

        size_t size() const
        {
            size_t s;
            std::vector<float> vertices;
            char *bytes = data(vertices, s);
            return s;
        }

        char *data(std::vector<float> &vertices, size_t &size) const
        {
            vertices.push_back(mPosition[0]);
            vertices.push_back(mPosition[1]);
            vertices.push_back(mPosition[2]);

            auto itr2 = mTexElements.begin();
            while (itr2 != mTexElements.end())
            {
                //                 FbxVector2 &texcoord = *itr2;
                const Vector2 &texcoord = *itr2;
                vertices.push_back(texcoord[0]);
                vertices.push_back(texcoord[1]);
                ++itr2;
            }

            auto itr3 = mNormalElements.begin();
            while (itr3 != mNormalElements.end())
            {
                //                 FbxVector3 &normal = *itr3;
                const Vector3 &normal = *itr3;
                vertices.push_back(normal[0]);
                vertices.push_back(normal[1]);
                vertices.push_back(normal[2]);
                ++itr3;
            }

            itr3 = mBinormalElements.begin();
            while (itr3 != mBinormalElements.end())
            {
                //                 FbxVector3 &binormal = *itr3;
                const Vector3 &binormal = *itr3;
                vertices.push_back(binormal[0]);
                vertices.push_back(binormal[1]);
                vertices.push_back(binormal[2]);
                ++itr3;
            }

            itr3 = mTangentElements.begin();
            while (itr3 != mTangentElements.end())
            {
                //                 FbxVector3 &tangent = *itr3;
                const Vector3 &tangent = *itr3;
                vertices.push_back(tangent[0]);
                vertices.push_back(tangent[1]);
                vertices.push_back(tangent[2]);
                ++itr3;
            }

            auto itr4 = mColorElements.begin();
            while (itr4 != mColorElements.end())
            {
                //                 FbxVector4 &color = *itr4;
                const ColorRGBA &color = *itr4;
                vertices.push_back(color.red());
                vertices.push_back(color.green());
                vertices.push_back(color.blue());
                vertices.push_back(color.alpha());
                ++itr4;
            }

            int i = 0;

            if (mBlendInfo.size() > 0)
            {
                auto it = mBlendInfo.rbegin();
                while (it != mBlendInfo.rend() && i < 4)
                {
                    const BlendInfo &info = *it;//it->second;
                    vertices.push_back((float)info.mBlendIndex);
                    ++it;
                    ++i;
                }

                while (i < 4)
                {
                    vertices.push_back(-1);
                    ++i;
                }

                i = 0;
                it = mBlendInfo.rbegin();

                while (it != mBlendInfo.rend() && i < 4)
                {
                    const BlendInfo &info = *it;//it->second;
                    vertices.push_back(info.mBlendWeight);
                    ++it;
                    ++i;
                }

                while (i < 4)
                {
                    vertices.push_back(0);
                    ++i;
                }
            }

            vertices.push_back(mMaterialIdx);

            char *str = (char *)vertices.data();
            size = vertices.size() * sizeof(float);
            return str;
        }

        void hash()
        {
            std::vector<float> vertices;
            size_t size = 0;
            char *bytes = data(vertices, size);
            uint32_t value = 5381;
            size_t i = 0;
            while (i < size)
            {
                value += (value << 5) + (*bytes++);
                i++;
            }

            mHash = (value & 0x7FFFFFFF);
        }

        bool operator <(const Vertex &other) const
        {
            return mHash < other.mHash;
        }

        bool operator ==(const Vertex &other) const
        {
            return mHash == other.mHash;
        }

        int                 mCtrlPointIdx;
        Vector3             mPosition;
        ColorElement        mColorElements;
        VectorElements2     mTexElements;
        VectorElements3     mNormalElements;
        VectorElements3     mBinormalElements;
        VectorElements3     mTangentElements;
        BlendInfoList       mBlendInfo;
        int                 mMaterialIdx;
        int                 mIndex;
        uint32_t            mHash;
    };

    typedef std::vector<Vertex>         Vertices;
    typedef Vertices::iterator          VerticesItr;
    typedef Vertices::const_iterator    VerticesConstItr;
}


#endif  /*__T3D_VERTEX_DATA_H__*/
