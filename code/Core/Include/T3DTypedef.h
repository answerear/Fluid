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


#ifndef __T3D_TYPEDEF_H__
#define __T3D_TYPEDEF_H__

#include "Kernel/T3DObject.h"
#include "Memory/T3DSmartPtr.h"

namespace Tiny3D
{
    T3D_DECLARE_SMART_PTR(Object);

    T3D_DECLARE_SMART_PTR(Component);
    T3D_DECLARE_SMART_PTR(ComponentCreator);

    T3D_DECLARE_SMART_PTR(Resource);
    T3D_DECLARE_SMART_PTR(ResourceManager);
    T3D_DECLARE_SMART_PTR(Dylib);
    T3D_DECLARE_SMART_PTR(DylibManager);
    T3D_DECLARE_SMART_PTR(Archive);
    T3D_DECLARE_SMART_PTR(ArchiveManager);
    T3D_DECLARE_SMART_PTR(Material);
    T3D_DECLARE_SMART_PTR(MaterialManager);
    T3D_DECLARE_SMART_PTR(Model);
    T3D_DECLARE_SMART_PTR(ModelManager);
    T3D_DECLARE_SMART_PTR(Texture);
    T3D_DECLARE_SMART_PTR(TextureManager);
    T3D_DECLARE_SMART_PTR(Shader);
    T3D_DECLARE_SMART_PTR(ShaderManager);
    T3D_DECLARE_SMART_PTR(GPUProgram);
    T3D_DECLARE_SMART_PTR(GPUProgramManager);
    T3D_DECLARE_SMART_PTR(GPUConstBuffer);
    T3D_DECLARE_SMART_PTR(GPUConstBufferManager);
    T3D_DECLARE_SMART_PTR(Model);
    T3D_DECLARE_SMART_PTR(ModelManager);

    T3D_DECLARE_SMART_PTR(NodeData);
    T3D_DECLARE_SMART_PTR(KeyFrameData);
    T3D_DECLARE_SMART_PTR(KeyFrameDataT);
    T3D_DECLARE_SMART_PTR(KeyFrameDataR);
    T3D_DECLARE_SMART_PTR(KeyFrameDataS);
    T3D_DECLARE_SMART_PTR(ActionData);
    T3D_DECLARE_SMART_PTR(SubMeshData);
    T3D_DECLARE_SMART_PTR(VertexData);
    T3D_DECLARE_SMART_PTR(MeshData);

    T3D_DECLARE_SMART_PTR(SerializerManager);
    T3D_DECLARE_SMART_PTR(MaterialReader);
    T3D_DECLARE_SMART_PTR(MaterialWriter);
    T3D_DECLARE_SMART_PTR(BinMaterialReader);
    T3D_DECLARE_SMART_PTR(BinMaterialWriter);
    T3D_DECLARE_SMART_PTR(JsonMaterialReader);
    T3D_DECLARE_SMART_PTR(JsonMaterialWriter);
    T3D_DECLARE_SMART_PTR(ModelReader);
    T3D_DECLARE_SMART_PTR(ModelWriter);
    T3D_DECLARE_SMART_PTR(BinModelReader);
    T3D_DECLARE_SMART_PTR(BinModelWriter);
    T3D_DECLARE_SMART_PTR(JsonModelReader);
    T3D_DECLARE_SMART_PTR(JsonModelWriter);

    T3D_DECLARE_SMART_PTR(HardwareBuffer);
    T3D_DECLARE_SMART_PTR(HardwareIndexBuffer);
    T3D_DECLARE_SMART_PTR(HardwarePixelBuffer);
    T3D_DECLARE_SMART_PTR(HardwareVertexBuffer);
    T3D_DECLARE_SMART_PTR(HardwareConstantBuffer);
    T3D_DECLARE_SMART_PTR(VertexAttribute);
    T3D_DECLARE_SMART_PTR(VertexDeclaration);

    T3D_DECLARE_SMART_PTR(VertexArrayObject);

    T3D_DECLARE_SMART_PTR(GPUProgramRef);
    T3D_DECLARE_SMART_PTR(GPUConstBufferRef);

    T3D_DECLARE_SMART_PTR(Technique);
    T3D_DECLARE_SMART_PTR(Pass);
    T3D_DECLARE_SMART_PTR(TextureUnit);
    T3D_DECLARE_SMART_PTR(Sampler);

    T3D_DECLARE_SMART_PTR(HardwareBufferManagerBase);
    T3D_DECLARE_SMART_PTR(HardwareBufferManager);

    T3D_DECLARE_SMART_PTR(RenderTarget);
    T3D_DECLARE_SMART_PTR(RenderWindow);

    T3D_DECLARE_SMART_PTR(Viewport);

    T3D_DECLARE_SMART_PTR(RenderContext);
    T3D_DECLARE_SMART_PTR(RenderCapabilities);

    T3D_DECLARE_SMART_PTR(RenderGroup);
    T3D_DECLARE_SMART_PTR(RenderQueue);

    T3D_DECLARE_SMART_PTR(ImageCodecBase);
    T3D_DECLARE_SMART_PTR(ImageCodec);

    T3D_DECLARE_SMART_PTR(Node);

    T3D_DECLARE_SMART_PTR(Bound);
    T3D_DECLARE_SMART_PTR(SphereBound);
    T3D_DECLARE_SMART_PTR(AabbBound);
    T3D_DECLARE_SMART_PTR(ObbBound);
    T3D_DECLARE_SMART_PTR(FrustumBound);

    T3D_DECLARE_SMART_PTR(SceneManagerBase);
    T3D_DECLARE_SMART_PTR(SceneManager);

    T3D_DECLARE_SMART_PTR(DefaultSceneMgr);

    T3D_DECLARE_SMART_PTR(SceneNode);

    T3D_DECLARE_SMART_PTR(Transform3D);
    T3D_DECLARE_SMART_PTR(Bone);

    T3D_DECLARE_SMART_PTR(Camera);
    T3D_DECLARE_SMART_PTR(Light);
    T3D_DECLARE_SMART_PTR(SceneModel);

    T3D_DECLARE_SMART_PTR(Renderable);
    T3D_DECLARE_SMART_PTR(Mesh);
    T3D_DECLARE_SMART_PTR(SceneTerrain);
    T3D_DECLARE_SMART_PTR(Billboard);
    T3D_DECLARE_SMART_PTR(Quad);
    T3D_DECLARE_SMART_PTR(Cube);
    T3D_DECLARE_SMART_PTR(Axis);
    T3D_DECLARE_SMART_PTR(Globe);

    T3D_DECLARE_SMART_PTR(SceneTransform2D);
    T3D_DECLARE_SMART_PTR(SceneSprite);
    T3D_DECLARE_SMART_PTR(SceneText2D);

    typedef VariantMap                      Settings;

    typedef TMap<String, RenderContextPtr>       Renderers;
    typedef Renderers::iterator             RenderersItr;
    typedef Renderers::const_iterator       RenderersConstItr;
    typedef Renderers::value_type           RenderersValue;

    typedef TList<NodePtr>                  Children;
    typedef Children::iterator              ChildrenItr;
    typedef Children::const_iterator        ChildrenConstItr;
}


#endif  /*__T3D_TYPEDEF_H__*/
