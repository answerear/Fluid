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


#ifndef __TINY3D_H__
#define __TINY3D_H__

// Global
#include <T3DPrerequisites.h>
#include <T3DErrorDef.h>
#include <T3DTypedef.h>
#include <T3DConfig.h>

// Kernel
#include <Kernel/T3DCommon.h>
#include <Kernel/T3DAgent.h>
#include <Kernel/T3DConfigFile.h>
#include <Kernel/T3DCreator.h>
#include <Kernel/T3DObject.h>
#include <Kernel/T3DPlugin.h>
#include <Kernel/T3DNode.h>
#include <Kernel/T3DBlendMode.h>
#include <Kernel/T3DTechnique.h>
#include <Kernel/T3DPass.h>
#include <Kernel/T3DTextureUnit.h>
#include <Kernel/T3DSampler.h>

// Memory
#include <Memory/T3DSmartPtr.h>
#include <Memory/T3DObjectTracer.h>

// Resource
#include <Resource/T3DArchive.h>
#include <Resource/T3DArchiveCreator.h>
#include <Resource/T3DArchiveManager.h>
#include <Resource/T3DDylib.h>
#include <Resource/T3DDylibManager.h>
#include <Resource/T3DResource.h>
#include <Resource/T3DResourceManager.h>
#include <Resource/T3DGPUProgram.h>
#include <Resource/T3DGPUProgramCreator.h>
#include <Resource/T3DGPUProgramManager.h>
#include <Resource/T3DGPUConstBuffer.h>
#include <Resource/T3DGPUConstBufferManager.h>
#include <Resource/T3DTexture.h>
#include <Resource/T3DTextureManager.h>
#include <Resource/T3DMaterial.h>
#include <Resource/T3DMaterialManager.h>
#include <Resource/T3DModel.h>
#include <Resource/T3DModelManager.h>

// Serialize
#include <Serializer/T3DSerializerManager.h>
#include <Serializer/T3DMaterialReader.h>
#include <Serializer/T3DMaterialWriter.h>
#include <Serializer/T3DModelReader.h>
#include <Serializer/T3DModelWriter.h>


// ImageCodec
#include <ImageCodec/T3DImageCodec.h>
#include <ImageCodec/T3DImageCodecBase.h>
#include <ImageCodec/T3DImage.h>

// Render
#include <Render/T3DRenderContext.h>
#include <Render/T3DRenderCapabilities.h>
#include <Render/T3DRenderState.h>
#include <Render/T3DRenderQueue.h>
#include <Render/T3DRenderTarget.h>
#include <Render/T3DRenderWindow.h>
#include <Render/T3DViewport.h>
#include <Render/T3DHardwareBufferManagerBase.h>
#include <Render/T3DHardwareBufferManager.h>
#include <Render/T3DHardwareBuffer.h>
#include <Render/T3DHardwareVertexBuffer.h>
#include <Render/T3DHardwareIndexBuffer.h>
#include <Render/T3DHardwarePixelBuffer.h>
#include <Render/T3DHardwareConstantBuffer.h>
#include <Render/T3DVertexArrayObject.h>

// Bound
#include <Bound/T3DBound.h>
#include <Bound/T3DSphereBound.h>
#include <Bound/T3DAabbBound.h>
#include <Bound/T3DObbBound.h>
#include <Bound/T3DFrustumBound.h>

// Scene Graph
#include <Scene/T3DSceneNode.h>
#include <Scene/T3DSceneManager.h>

// Component
#include <Component/T3DComponent.h>
#include <Component/T3DComponentCreator.h>
#include <Component/T3DAxis.h>
#include <Component/T3DBillboard.h>
#include <Component/T3DCube.h>
#include <Component/T3DCamera.h>
#include <Component/T3DLight.h>
#include <Component/T3DMesh.h>
#include <Component/T3DQuad.h>
#include <Component/T3DRenderable.h>
#include <Component/T3DGlobe.h>
#include <Component/T3DTransform3D.h>


#endif  /*__TINY3D_H__*/
