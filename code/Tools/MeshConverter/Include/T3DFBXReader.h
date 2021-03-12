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


#ifndef __T3D_FBX_READER_H__
#define __T3D_FBX_READER_H__


#include "T3DConverterPrerequisites.h"
#include "FileScriptObject.pb.h"
#include "T3DVertexData.h"


namespace Tiny3D
{
    class FBXReader;

    T3D_DECLARE_SMART_PTR(FBXReader);

    class FBXReader : public ModelReader
    {
    public:
        static FBXReaderPtr create(bool isTxt, const String &name);

        virtual ~FBXReader();

        const TArray<MaterialPtr> &getMaterials() const { return mMaterials; }

    protected:
        FBXReader(bool isTxt, const String &name);

        virtual TResult parse(DataStream &stream, Model *model) override;

        TResult initFbxObjects();
        TResult destroyFbxObjects();

        TResult importFbxScene(DataStream &stream, FbxScene *pFbxScene);
        TResult setupMetricSystem(FbxScene *pFbxScene);

        TResult processFbxScene(FbxScene *pFbxScene, Script::FileFormat::FileLevel *model);

        TResult processFbxNode(FbxNode *pFbxNode, Script::FileFormat::FileLevel *model, Script::LevelSystem::Node *parent, Script::LevelSystem::Node *&pNode);
        TResult processFbxAttributes(FbxNode *pFbxNode, Script::FileFormat::FileLevel *model, Script::LevelSystem::Node *parent, Script::LevelSystem::Node *pNode);
        TResult processFbxMesh(FbxNode *pFbxNode, FbxMesh *pFbxMesh, Script::FileFormat::FileLevel *model);
        TResult processFbxMeshAttributes(FbxMesh *pFbxMesh, Script::ModelSystem::MeshData *pMesh);
        TResult processFbxMeshData(FbxMesh *pFbxMesh, Script::ModelSystem::MeshData *pMesh);

        TResult processFbxMaterial(FbxNode *pFbxNode, FbxMesh *pFbxMesh);
        TResult processFbxShaderMaterial(FbxSurfaceMaterial* pFbxMaterial, const FbxImplementation *pFbxImpl, MaterialPtr material);
        TResult processFbxPhongMaterial(FbxSurfacePhong* pFbxMaterial, MaterialPtr material);
        TResult processFbxLambertMaterial(FbxSurfaceLambert* pFbxMaterial, MaterialPtr material);

        TResult processFbxCamera(FbxNode *pFbxNode);
        TResult processFbxLight(FbxNode *pFbxNode);

        TResult processFbxAnimation(FbxScene *pFbxScene, Script::FileFormat::FileLevel *model);
        TResult processFbxAnimation(FbxAnimStack *pFbxAnimStack, FbxNode *pFbxNode, Script::FileFormat::FileLevel *model, int32_t idx);
        TResult processFbxAnimation(FbxAnimLayer *pFbxAnimLayer, FbxNode *pFbxNode, Script::ModelSystem::AnimationClip *clip, int32_t idx);
        TResult processFbxAnimationChannels(FbxAnimLayer *pFbxAnimLayer, FbxNode *pFbxNode);
        TResult processFbxAnimationCurve(FbxAnimCurve *pFbxAnimCurve);
        TResult processFbxAnimationCurve(FbxAnimLayer *pFbxAnimLayer, FbxNode *pFbxNode, Script::ModelSystem::AnimationClip *clip);

        TResult processFbxBindPose(FbxScene *pFbxScene);

        TResult processFbxSkin(FbxGeometry *pFbxGeometry, Script::ModelSystem::MeshData *pMesh);


        int InterpolationFlagToIndex(int flags);
        int ConstantmodeFlagToIndex(int flags);
        int TangentmodeFlagToIndex(int flags);
        int TangentweightFlagToIndex(int flags);
        int TangentVelocityFlagToIndex(int flags);

		void convertMatrix(const FbxAMatrix &src, Matrix4 &dst);
        void convertMatrix(const FbxMatrix &src, Matrix4 &dst);

        TResult generateNode(FbxNode *pFbxNode, Script::FileFormat::FileLevel *model, Script::LevelSystem::Node *parent, Script::LevelSystem::Node *&pNode);

        TResult readPosition(FbxMesh *pFbxMesh, int32_t ctrlPointIdx,
            Vector3 &pos);
        TResult readColor(FbxMesh *pFbxMesh, int32_t ctrlPointIdx, 
            int32_t vertexIdx, int32_t layer, ColorRGBA &color);
        TResult readUV(FbxMesh *pFbxMesh, int32_t ctrlPointIdx, int32_t uvIdx,
            int32_t layer, Vector2 &uv);
        TResult readNormal(FbxMesh *pFbxMesh, int32_t ctrlPointIdx,
            int32_t vertexIdx, int32_t layer, Vector3 &normal);
        TResult readBinormal(FbxMesh *pFbxMesh, int32_t ctrlPointIdx,
            int32_t vertexIdx, int32_t layer, Vector3 &binormal);
        TResult readTangent(FbxMesh *pFbxMesh, int32_t ctrlPointIdx,
            int32_t vertexIdx, int32_t layer, Vector3 &tangent);

        TResult setupMaterialConnections(FbxMesh *pFbxMesh, int32_t triangle, Vertex &vertex);

        void updateBlendInfo(int index, int boneIdx, float weight);

        TResult optimizeMesh();

        TResult rebuildTxtVertices(std::map<uint32_t, Vertex> &vertices);
        TResult rebuildTxtIndices(std::map<uint32_t, Vertex> &vertices);

        TResult rebuildBinVertices(std::map<uint32_t, Vertex> &vertices);
        TResult rebuildBinIndices(std::map<uint32_t, Vertex> &vertices);

    protected:
        FbxManager  *mFbxManager;
        size_t      mTabCount;

        struct MeshData
        {
            Script::ModelSystem::MeshData *pTarget;

            Vertices    vertices;
            Indices     indices;
        };

        MeshData    mMeshData;

        TArray<String>  mMaterialNames;

        TArray<MaterialPtr>    mMaterials;

        String      mFbxName;
        bool        mIsTxt;
    };
}

#endif  /*__T3D_FBX_READER_H__*/

