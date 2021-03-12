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


#include "Resource/T3DModel.h"
#include "Kernel/T3DAgent.h"
#include "Resource/T3DArchive.h"
#include "Resource/T3DArchiveManager.h"
#include "Serializer/T3DSerializerManager.h"
#include "protobuf/FileScriptObject.pb.h"
#include "Scene/T3DSceneManager.h"
#include "Render/T3DHardwareBufferManager.h"
#include "Render/T3DHardwareVertexBuffer.h"
#include "Render/T3DHardwareIndexBuffer.h"
#include "Bound/T3DBound.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    TResult buildNode(google::protobuf::Map<String, Script::LevelSystem::Node>& nodes, const std::string& uuid, SceneNodePtr parent, SceneNodePtr& node);

    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Model, Resource);

    //--------------------------------------------------------------------------

    ModelPtr Model::create(const String &name)
    {
        ModelPtr mesh = new Model(name);
        mesh->release();
        return mesh;
    }

    //--------------------------------------------------------------------------

    Model::Model(const String &name)
        : Resource(name)
        , mModelData(nullptr)
    {
        mModelData = new Script::FileFormat::FileLevel();
    }

    //--------------------------------------------------------------------------

    Model::~Model()
    {

    }

    //--------------------------------------------------------------------------

    Resource::Type Model::getType() const
    {
        return Type::E_RT_MODEL;
    }

    //--------------------------------------------------------------------------

    TResult Model::load()
    {
        TResult ret = T3D_OK;

        do 
        {
            // 加载模型文件
            ArchivePtr archive = T3D_AGENT.getAssetsArchive(mName);
            if (archive == nullptr)
            {
                ret = T3D_ERR_IMG_NOT_FOUND;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Could not find the archive for file %s !",
                    mName.c_str());
                break;
            }

            String path = T3D_AGENT.getMainAssetsPath(mName);
            MemoryDataStream stream;
            ret = archive->read(path, stream);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Read material content failed from file %s ! ",
                    mName.c_str());
                break;
            }

            // 交给模型解析器解析出来
            ret = T3D_SERIALIZER_MGR.parseModel(stream, this);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Could not parse material file %s !", mName.c_str());
                break;
            }

            ret = buildMeshData();
            if (T3D_FAILED(ret))
            {
                break;
            }
        } while (false);

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult Model::unload()
    {
        T3D_SAFE_DELETE(mModelData);
        return Resource::unload();
    }

    //--------------------------------------------------------------------------

    ResourcePtr Model::clone() const
    {
        ModelPtr model = Model::create(mName);
        return model;
    }

    //--------------------------------------------------------------------------

    void Model::setModelData(void *data)
    {
        Script::FileFormat::FileLevel *src 
            = (Script::FileFormat::FileLevel *)data;
        Script::FileFormat::FileLevel *dst 
            = (Script::FileFormat::FileLevel *)mModelData;
        dst->CopyFrom(*src);
    }

    //--------------------------------------------------------------------------

    TResult Model::buildMeshData()
    {
        TResult ret = T3D_OK;

        do 
        {
            Script::FileFormat::FileLevel* model 
                = (Script::FileFormat::FileLevel*)mModelData;

            //mMeshData.vertices.clear();
            //mMeshData.submeshes.clear();

            //// Vertex delcaration
            //mMeshData.declartion = T3D_HARDWARE_BUFFER_MGR.createVertexDeclaration();

            //auto meshes = model->data().meshes();
            //auto itr = meshes.begin();
            //while (itr != meshes.end())
            //{

            //}
            //auto body = model->data();
            //const std::string& uuid = body.root();
            //auto nodes = body.nodes();

            //// 构建场景结点
            //ret = buildNode(nodes, uuid, nullptr, mRoot);
            //if (T3D_FAILED(ret))
            //{
            //    break;
            //}

            //auto meshes = body.meshes();
            //buildMesh(meshes);

        } while (false);
        

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult buildNode(
        google::protobuf::Map<String, Script::LevelSystem::Node> &nodes, 
        const std::string &uuid, SceneNodePtr parent, SceneNodePtr &node)
    {
        TResult ret = T3D_OK;

        Script::LevelSystem::Node& src = nodes[uuid];

        node = T3D_SCENE_MGR.createSceneNode(parent);
        node->setName(src.name());

        int32_t i = 0;
        //for (i = 0; i < src.components_size(); ++i)
        //{
        //    auto component = src.components(i);
        //    ret = buildComponent(component, node);
        //}

        auto children = src.children();

        for (i = 0; i < src.children_size(); ++i)
        {
            SceneNodePtr child;
            ret = buildNode(nodes, children[i], node, child);
            if (T3D_FAILED(ret))
            {
                break;
            }
        }

        return ret;
    }

    TResult buildComponent(Script::LevelSystem::Component &srcComponent, SceneNodePtr node)
    {
        TResult ret = T3D_OK;

        switch (srcComponent.type())
        {
        case Script::LevelSystem::Component_Type_Transform:
            {

            }
            break;
        case Script::LevelSystem::Component_Type_SkinnedMesh:
            {

            }
            break;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult buildMesh(
        google::protobuf::Map<String, Script::ModelSystem::MeshData>& meshes)
    {
        TResult ret = T3D_OK;


        return ret;
    }
}
