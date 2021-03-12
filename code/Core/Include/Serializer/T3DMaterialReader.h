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

#ifndef __T3D_MATERIAL_READER_H__
#define __T3D_MATERIAL_READER_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "Kernel/T3DObject.h"
#include "Kernel/T3DCommon.h"


namespace Tiny3D
{
    namespace Script
    {
        namespace MaterialSystem
        {
            class Material;
            class Technique;
            class Pass;
            class GPUConstantBufferRef;
            class TextureUnit;
            class Sampler;
            class GPUConstantBuffer;
            class GPUProgram;
            class Param;
            class ParamAuto;
            class Shader;
        }
    }

    class T3D_ENGINE_API MaterialReader : public Object
    {
        T3D_DECLARE_CLASS();
        T3D_DECLARE_INTERFACE(MaterialReader);

    public:
        virtual TResult parse(DataStream &stream, Material *material) = 0;

    protected:
        MaterialReader(const BuiltinConstantMap& definitions);

        /**
         * @fn  TResult BinMaterialReader::parseMaterial(
         *      const Script::MaterialSystem::Material *src, Material *dst);
         * @brief   Parse material
         * @param           src Source for the.
         * @param [in,out]  dst If non-null, destination for the.
         * @return  A TResult.
         */
        TResult parseMaterial(
            const Script::MaterialSystem::Material* src, Material* dst);

        /**
         * @fn  TResult BinMaterialReader::parseTechnique(
         *      const Script::MaterialSystem::Technique *src, Material *dst);
         * @brief   Parse technique
         * @param           src Source for the.
         * @param [in,out]  dst If non-null, destination for the.
         * @return  A TResult.
         */
        TResult parseTechnique(
            const Script::MaterialSystem::Technique* src, Material* dst);

        /**
         * @fn  TResult BinMaterialReader::parsePass(
         *      const Script::MaterialSystem::Pass *src, Technique *dst);
         * @brief   Parse pass
         * @param           src Source for the.
         * @param [in,out]  dst If non-null, destination for the.
         * @return  A TResult.
         */
        TResult parsePass(
            const Script::MaterialSystem::Pass* src, Technique* dst);

        /**
         * @fn  TResult BinMaterialReader::parseAmbient(
         *      const Script::MaterialSystem::Pass *src, Pass *dst);
         * @brief   Parse ambient
         * @param           src Source for the.
         * @param [in,out]  dst If non-null, destination for the.
         * @return  A TResult.
         */
        TResult parseAmbient(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        /**
         * @fn  TResult BinMaterialReader::parseDiffuse(
         *      const Script::MaterialSystem::Pass *src, Pass *dst);
         * @brief   Parse diffuse
         * @param           src Source for the.
         * @param [in,out]  dst If non-null, destination for the.
         * @return  A TResult.
         */
        TResult parseDiffuse(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        /**
         * @fn  TResult BinMaterialReader::parseSpecular(
         *      const Script::MaterialSystem::Pass *src, Pass *dst);
         * @brief   Parse specular
         * @param           src Source for the.
         * @param [in,out]  dst If non-null, destination for the.
         * @return  A TResult.
         */
        TResult parseSpecular(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        /**
         * @fn  TResult BinMaterialReader::parseEmissive(
         *      const Script::MaterialSystem::Pass *src, Pass *dst);
         * @brief   Parse emissive
         * @param           src Source for the.
         * @param [in,out]  dst If non-null, destination for the.
         * @return  A TResult.
         */
        TResult parseEmissive(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        /**
         * @fn  TResult BinMaterialReader::parseSceneBlend(
         *      const Script::MaterialSystem::Pass *src, Pass *dst);
         * @brief   Parse scene blend
         * @param           src Source for the.
         * @param [in,out]  dst If non-null, destination for the.
         * @return  A TResult.
         */
        TResult parseSceneBlend(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseSeparateSceneBlend(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseSceneBlendOp(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseSeparateSceneBlendOp(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseDepthCheck(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseDepthWrite(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseDepthFunc(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseDepthBias(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseIterationDepthBias(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseAlphaRejection(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseAlpha2Coverage(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseLightScissor(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseLightClipPlanes(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseIlluminationStage(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseNormalizeNormals(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseTransparentSorting(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseCullHardware(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseCullSoftware(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseLighting(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseShading(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parsePolygonMode(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parsePolygonModeOverridable(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseFog(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseColorWrite(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseMaxLights(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseStartLight(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseIteration(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parsePointSize(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parsePointSprites(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parsePointSizeAttenuation(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parsePointSizeMin(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parsePointSizeMax(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseGPUProgramRef(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseTextures(
            const Script::MaterialSystem::Pass* src, Pass* dst);

        TResult parseGPUConstantBufferRef(
            const Script::MaterialSystem::GPUConstantBufferRef* src, GPUProgramRef* dst);

        TResult parseTextureUnit(
            const Script::MaterialSystem::TextureUnit* src, Pass* dst);

        TResult parseTextureAlias(
            const Script::MaterialSystem::TextureUnit* src, TextureUnit* dst);

        TResult parseTexture(
            const Script::MaterialSystem::TextureUnit* src, TextureUnit* dst);

        TResult parseAnimTexture(
            const Script::MaterialSystem::TextureUnit* src, TextureUnit* dst);

        TResult parseCubicTexture(
            const Script::MaterialSystem::TextureUnit* src, TextureUnit* dst);

        TResult parseBindingType(
            const Script::MaterialSystem::TextureUnit* src, TextureUnit* dst);

        TResult parseTexCoordSet(
            const Script::MaterialSystem::TextureUnit* src, TextureUnit* dst);

        TResult parseColorOp(
            const Script::MaterialSystem::TextureUnit* src, TextureUnit* dst);

        TResult parseSamplerRef(
            const Script::MaterialSystem::TextureUnit* src, TextureUnit* dst);

        TResult parseSampler(
            const Script::MaterialSystem::Sampler* src, Material* dst);

        TResult parseTexAddressMode(
            const Script::MaterialSystem::Sampler* src, Sampler* dst);

        TResult parseTexBorderColor(
            const Script::MaterialSystem::Sampler* src, Sampler* dst);

        TResult parseFiltering(
            const Script::MaterialSystem::Sampler* src, Sampler* dst);

        TResult parseCompareTest(
            const Script::MaterialSystem::Sampler* src, Sampler* dst);

        TResult parseCompareFunc(
            const Script::MaterialSystem::Sampler* src, Sampler* dst);

        TResult parseMaxAnisotropy(
            const Script::MaterialSystem::Sampler* src, Sampler* dst);

        TResult parseMipmapBias(
            const Script::MaterialSystem::Sampler* src, Sampler* dst);

        TResult parseGPUConstantBuffer(
            const Script::MaterialSystem::GPUConstantBuffer* src, Material* dst);

        TResult parseParam(
            const Script::MaterialSystem::Param* src, GPUConstBuffer* dst, bool named);

        TResult parseParamAuto(
            const Script::MaterialSystem::ParamAuto* src, GPUConstBuffer* dst, bool named);

        TResult parseGPUProgram(
            const Script::MaterialSystem::GPUProgram* src, Material* dst);

        TResult parseShader(
            const Script::MaterialSystem::Shader* src, GPUProgram* dst);

    protected:
        const BuiltinConstantMap& mDefinitions;
    };
}


#endif    /*__T3D_MATERIAL_READER_H__*/
