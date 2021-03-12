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

#ifndef __T3D_PREREQUISITES_H__
#define __T3D_PREREQUISITES_H__


#include "T3DMacro.h"

#if defined T3DCORE_EXPORT
    #define T3D_ENGINE_API        T3D_EXPORT_API
#else
    #define T3D_ENGINE_API        T3D_IMPORT_API
#endif


#include <T3DPlatform.h>
#include <T3DMathLib.h>
#include <T3DLog.h>
#include <T3DUtils.h>
#include <T3DFramework.h>

#if defined (T3D_OS_IOS) || defined (T3D_OS_OSX)
#include <SDL_main.h>
#else
#endif

#include <algorithm>
#undef min

namespace Tiny3D
{
    #define LOG_TAG_CONFIG_FILE         "ConfigFile"
    #define LOG_TAG_ENGINE              "Agent"
    #define LOG_TAG_IMAGE               "Image"
    #define LOG_TAG_RENDER              "Render"
    #define LOG_TAG_PLUGIN              "Plugin"
    #define LOG_TAG_IMAGE_CODEC         "ImageCodec"
    #define LOG_TAG_SCENE               "Scene"
    #define LOG_TAG_RESOURCE            "Resource"
    #define LOG_TAG_COMPONENT           "Component"

    class Object;
    class ObjectTracer;

    class Agent;
    class Plugin;

    class Variant;

    class Component;
    class ComponentCreator;

    class SerializerManager;
    class MaterialReader;
    class MaterialWriter;
    class BinMaterialReader;
    class BinMaterialWriter;
    class JsonMaterialReader;
    class JsonMaterialWriter;
    class ModelReader;
    class ModelWriter;
    class BinModelReader;
    class BinModelWriter;
    class JsonModelReader;
    class JsonModelWriter;

    class Resource;
    class ResourceManager;
    class Dylib;
    class DylibManager;
    class Archive;
    class ArchiveCreator;
    class ArchiveManager;
    class Material;
    class MaterialManager;
    class Texture;
    class TextureManager;
    class Shader;
    class ShaderManager;
    class GPUProgram;
    class GPUProgramManager;
    class GPUConstBuffer;
    class GPUConstBufferManager;
    class Model;
    class ModelManager;

    class NodeData;
    class KeyFrameData;
    class KeyFrameDataT;
    class KeyFrameDataR;
    class KeyFrameDataS;
    class ActionData;
    class SubMeshData;
    class VertexData;
    class MeshData;

    class HardwareBuffer;
    class HardwareIndexBuffer;
    class HardwarePixelBuffer;
    class HardwareVertexBuffer;
    class HardwareConstantBuffer;
    class VertexAttribute;
    class VertexDeclaration;

    class GPUProgramRef;
    class GPUConstBufferRef;

    class Technique;
    class Pass;
    class TextureUnit;
    class Sampler;

    class VertexArrayObject;

    class HardwareBufferManagerBase;
    class HardwareBufferManager;

    class RenderTarget;
    class RenderWindow;
    
    class Viewport;

    class RenderContext;
    class RenderCapabilities;
    class RenderGroup;
    class RenderQueue;

    class ImageCodecBase;
    class ImageCodec;

    class Node;

    class Bound;
    class SphereBound;
    class AabbBound;
    class ObbBound;
    class FrustumBound;

    class SceneManagerBase;
    class SceneManager;
    class DefaultSceneMgr;

    class SceneNode;

    class Transform3D;
    class Bone;

    class Camera;
    class Light;
    class SceneModel;

    class Renderable;
    class Mesh;
    class SceneTerrain;
    class Billboard;
    class Quad;
    class Cube;
    class Axis;
    class Globe;

    class SceneTransform2D;
    class SceneText2D;
    class SceneSprite;
}


#endif    /*__T3D_PREREQUISITES_H__*/
