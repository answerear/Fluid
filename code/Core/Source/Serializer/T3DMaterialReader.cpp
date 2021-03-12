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


#include "Serializer/T3DMaterialReader.h"

#include "Kernel/T3DCommon.h"
#include "Resource/T3DMaterial.h"
#include "Resource/T3DGPUProgram.h"
#include "Resource/T3DGPUConstBuffer.h"
#include "Resource/T3DGPUConstBuffer.h"
#include "Resource/T3DGPUConstBufferManager.h"
#include "Resource/T3DGPUProgram.h"
#include "Resource/T3DGPUProgramManager.h"
#include "Kernel/T3DTechnique.h"
#include "Kernel/T3DPass.h"
#include "Kernel/T3DTextureUnit.h"
#include "Kernel/T3DSampler.h"

#include "protobuf/MaterialScriptObject.pb.h"


namespace Tiny3D
{
    #define T3D_CHECK_PARSING_RET(ret)    \
        if (T3D_FAILED(ret))    \
        {   \
            break;  \
        }

    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(MaterialReader, Object);

    //--------------------------------------------------------------------------

    MaterialReader::MaterialReader(const BuiltinConstantMap& definitions)
        : mDefinitions(definitions)
    {

    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseMaterial(
        const Script::MaterialSystem::Material *src, Material *dst)
    {
        TResult ret = T3D_OK;

        do 
        {
            // Material name
            const Script::ObjectHeader &header = src->header();

            if (dst != nullptr)
                dst->setMaterialName(header.name());

            // lod_values & lod_strategy
            // auto values = src->values();

            // receive_shadows
            // src->receive_shadows();

            // transparency_casts_shadows
            // src->transparency_casts_shadows();

            // texture_alias
            // auto alias = src->texture_alias();
            // auto aliasName = alias.alias_name();
            // auto texName = alias.texture_name();

            // Techniques
            auto techniques = src->techniques();
            for (const Script::MaterialSystem::Technique &tech : techniques)
            {
                ret = parseTechnique(&tech, dst);
                T3D_CHECK_PARSING_RET(ret);
            }

            // constant buffers
            auto cbuffers = src->cbuffers();
            for (const Script::MaterialSystem::GPUConstantBuffer &cbuf : cbuffers)
            {
                ret = parseGPUConstantBuffer(&cbuf, dst);
                T3D_CHECK_PARSING_RET(ret);
            }

            // GPU programs
            auto programs = src->programs();
            for (const Script::MaterialSystem::GPUProgram &program : programs)
            {
                ret = parseGPUProgram(&program, dst);
                T3D_CHECK_PARSING_RET(ret);
            }

            // Samplers
            auto samplers = src->samplers();
            for (const Script::MaterialSystem::Sampler &sampler : samplers)
            {
                ret = parseSampler(&sampler, dst);
                T3D_CHECK_PARSING_RET(ret);
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseTechnique(
        const Script::MaterialSystem::Technique *src, Material *dst)
    {
        TResult ret = T3D_OK;

        do 
        {
            // Technique name
            const Script::ObjectHeader &header = src->header();
            TechniquePtr tech;
            ret = dst->addTechnique(header.name(), tech);
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, 
                    "Add technique for material [%s] failed !", 
                    dst->getName().c_str());
                    break;
            }

            // render_queue
            if (src->has_render_queue())
            {
                tech->setRenderQueue(src->render_queue().value());
            }

            // lod_index
            // auto index = src->lod_index();

            // scheme
            // auto scheme = src->scheme();

            // shadow_caster_material
            // auto casterMaterial = src->shadow_caster_material();

            // shadow_receiver_material
            // auto receiverMaterial = src->shadow_receiver_material();

            // gpu_vendor_rule
            // auto vendor = src->gpu_vendor_rule();
            // auto ruleType = vendor.rule();
            // auto vendorName = vendor.vendor_name();

            // gpu_device_rule
            // auto device = src->gpu_device_rule();
            // auto ruleType = device.rule();
            // auto pattern = device.device_pattern();
            // auto caseSensitive = device.case_sensitive();

            // Passes
            auto passes = src->passes();

            for (const Script::MaterialSystem::Pass &pass : passes)
            {
                ret = parsePass(&pass, tech);
                T3D_CHECK_PARSING_RET(ret);
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parsePass(
        const Script::MaterialSystem::Pass *src, Technique *dst)
    {
        TResult ret = T3D_OK;

        do 
        {
            // Pass name
            const Script::ObjectHeader &header = src->header();
            PassPtr pass;
            ret = dst->addPass(header.name(), pass);
            T3D_CHECK_PARSING_RET(ret);

            // ambient
            ret = parseAmbient(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // diffuse
            ret = parseDiffuse(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // specular
            ret = parseSpecular(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // emissive
            ret = parseEmissive(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // scene_blend
            ret = parseSceneBlend(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // separate_scene_blend
            ret = parseSeparateSceneBlend(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // scene_blend_op
            ret = parseSceneBlendOp(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // separate_scene_blend_op
            ret = parseSeparateSceneBlendOp(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // depth_check
            ret = parseDepthCheck(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // depth_write
            ret = parseDepthWrite(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // depth_func
            ret = parseDepthFunc(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // depth_bias
            ret = parseDepthBias(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // iteration_depth_bias
            ret = parseIterationDepthBias(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // alpha_rejection
            ret = parseAlphaRejection(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // alpha_to_coverage
            ret = parseAlpha2Coverage(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // light_scissor
            ret = parseLightScissor(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // light_clip_planes
            ret = parseLightClipPlanes(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // illumination_stage
            ret = parseIlluminationStage(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // normailize_normals
            ret = parseNormalizeNormals(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // transparent_sorting
            ret = parseTransparentSorting(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // cull_hardware
            ret = parseCullHardware(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // cull_software
            ret = parseCullSoftware(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // lighting
            ret = parseLighting(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // shading
            ret = parseShading(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // polygon_mode
            ret = parsePolygonMode(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // polygon_mode_overrideable
            ret = parsePolygonModeOverridable(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // fog
            ret = parseFog(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // color_write
            ret = parseColorWrite(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // max_lights
            ret = parseMaxLights(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // start_light
            ret = parseStartLight(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // iteration
            ret = parseIteration(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // point_size
            ret = parsePointSize(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // point_sprites
            ret = parsePointSprites(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // point_size_attenuation
            ret = parsePointSizeAttenuation(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // point_size_min
            ret = parsePointSizeMin(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // point_size_max
            ret = parsePointSizeMax(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // gpu_program_ref
            ret = parseGPUProgramRef(src, pass);
            T3D_CHECK_PARSING_RET(ret);

            // textures
            ret = parseTextures(src, pass);
            T3D_CHECK_PARSING_RET(ret);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseAmbient(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_ambient())
        {
            auto ambient = src->ambient();
            if (!ambient.has_color() && ambient.vertex_color())
            {
                // use vertex color for ambient
                dst->setVertexColorTracking(TrackVertexColor::AMBIENT);
            }
            else
            {
                // color value
                auto clr = ambient.color();
                dst->setAmbient(clr.r(), clr.g(), clr.b(), clr.a());
            }
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseDiffuse(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_diffuse())
        {
            auto diffuse = src->diffuse();
            if (!diffuse.has_color() && diffuse.vertex_color())
            {
                // use vertex color for diffuse
                dst->setVertexColorTracking(TrackVertexColor::DIFFUSE);
            }
            else
            {
                // color value
                auto clr = diffuse.color();
                dst->setDiffuse(clr.r(), clr.g(), clr.b(), clr.a());
            }
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseSpecular(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_specular())
        {
            auto specular = src->specular();
            if (!specular.has_color() && specular.vertex_color())
            {
                // use vertex color for specular
                dst->setVertexColorTracking(TrackVertexColor::SPECULAR);
            }
            else
            {
                // color value
                auto clr = specular.color();
                dst->setSpecular(clr.r(), clr.g(), clr.b(), clr.a());
            }

            dst->setShininess(src->shininess().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseEmissive(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_emissive())
        {
            auto emissive = src->emissive();
            if (!emissive.has_color() && emissive.vertex_color())
            {
                // use vertex color for emissive
                dst->setVertexColorTracking(TrackVertexColor::EMISSIVE);
            }
            else
            {
                // color value
                auto clr = emissive.color();
                dst->setEmissive(clr.r(), clr.g(), clr.b(), clr.a());
            }
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseSceneBlend(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_scene_blend())
        {
            auto blend = src->scene_blend();
            if (blend.has_blend_factor())
            {
                // blend factor
                auto factor = blend.blend_factor();
                BlendFactor srcFactor = (BlendFactor)factor.src_factor();
                BlendFactor dstFactor = (BlendFactor)factor.dest_factor();
                dst->setSceneBlending(srcFactor, dstFactor);
            }
            else
            {
                // blend type
                BlendType blendType = (BlendType)blend.blend_type();
                dst->setSceneBlending(blendType);
            }
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseSeparateSceneBlend(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_separate_scene_blend())
        {
            auto blend = src->separate_scene_blend();
            if (blend.has_blend_type())
            {
                // separate blend type
                auto blendType = blend.blend_type();
                BlendType colorType = (BlendType)blendType.color_blend();
                BlendType alphaType = (BlendType)blendType.alpha_blend();
                dst->setSeparateSceneBlending(colorType, alphaType);
            }
            else
            {
                // separate blend factor
                auto blendFactor = blend.blend_factor();
                BlendFactor colorSrcF = (BlendFactor)blendFactor.color_src_factor();
                BlendFactor colorDstF = (BlendFactor)blendFactor.color_dest_factor();
                BlendFactor alphaSrcF = (BlendFactor)blendFactor.alpha_src_factor();
                BlendFactor alphaDstF = (BlendFactor)blendFactor.alpha_dest_factor();
                dst->setSeparateSceneBlending(colorSrcF, colorDstF,
                    alphaSrcF, alphaDstF);
            }
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseSceneBlendOp(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_scene_blend_op())
        {
            BlendOperation op = (BlendOperation)(src->scene_blend_op().value());
            dst->setSceneBlendingOperation(op);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseSeparateSceneBlendOp(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_separate_scene_blend_op())
        {
            auto op = src->separate_scene_blend_op();
            BlendOperation colorOp = (BlendOperation)op.color_op();
            BlendOperation alphaOp = (BlendOperation)op.alpha_op();
            dst->setSeparateSceneBlendingOperation(colorOp, alphaOp);
        }
        
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseDepthCheck(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_depth_check())
        {
            dst->setDepthCheckEnabled(src->depth_check().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseDepthWrite(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_depth_write())
        {
            dst->setDepthWriteEnabled(src->depth_write().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseDepthFunc(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_depth_func())
        {
            CompareFunction func = (CompareFunction)(src->depth_func().value());
            dst->setDepthFunction(func);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseDepthBias(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_depth_bias())
        {
            float32_t constant = src->depth_bias().constant_bias();
            float32_t slopeScale = src->depth_bias().slopescale_bias();
            dst->setDepthBias(constant, slopeScale);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseIterationDepthBias(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_iteration_depth_bias())
        {
            dst->setDepthBiasPerIteration(src->iteration_depth_bias().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseAlphaRejection(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_alpha_rejection())
        {
            CompareFunction func = (CompareFunction)(src->alpha_rejection().function());
            uint8_t value = (uint8_t)(src->alpha_rejection().value());
            dst->setAlphaRejectFunction(func);
            dst->setAlphaRejectValue(value);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseAlpha2Coverage(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_alpha_to_coverage())
        {
            bool enabled = src->alpha_to_coverage().value();
            dst->setAlphaToCoverageEnabled(enabled);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseLightScissor(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_light_scissor())
        {
            bool enabled = src->light_scissor().value();
            dst->setLightScissoringEnabled(enabled);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseLightClipPlanes(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_light_clip_planes())
        {
            bool enabled = src->light_clip_planes().value();
            dst->setLightClipPlanesEnabled(enabled);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseIlluminationStage(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_illumination_stage())
        {
            IlluminationStage stage = (IlluminationStage)src->illumination_stage().stage();
            dst->setIlluminationStage(stage);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseNormalizeNormals(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_normailize_normals())
        {
            bool enabled = src->normailize_normals().value();
            dst->setNormalizeNormalsEnabled(enabled);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseTransparentSorting(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        TResult ret = T3D_OK;

        if (src->has_transparent_sorting())
        {
            switch (src->transparent_sorting().value())
            {
            case Script::MaterialSystem::TransparentSorting::TS_OFF:
                {
                    dst->setTransparentSortingEnabled(false);
                    dst->setTransparentSortingForced(false);
                }
                break;
            case Script::MaterialSystem::TransparentSorting::TS_ON:
                {
                    dst->setTransparentSortingEnabled(true);
                    dst->setTransparentSortingForced(false);
                }
                break;
            case Script::MaterialSystem::TransparentSorting::TS_FORCE:
                {
                    dst->setTransparentSortingEnabled(true);
                    dst->setTransparentSortingForced(true);
                }
                break;
            default:
                {
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE, 
                        "Invalid transparent sorting value !");
                    ret = T3D_ERR_RES_INVALID_PROPERTY;
                }
                break;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseCullHardware(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_cull_hardware())
        {
            CullingMode mode = (CullingMode)(src->cull_hardware().value());
            dst->setCullingMode(mode);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseCullSoftware(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_cull_software())
        {
            ManualCullingMode mode = (ManualCullingMode)(src->cull_software().value());
            dst->setManualCullingMode(mode);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseLighting(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_lighting())
        {
            bool enabled = src->lighting().value();
            dst->setLightEnabled(enabled);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseShading(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_shading())
        {
            ShadingMode mode = (ShadingMode)(src->shading().value());
            dst->setShadingMode(mode);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parsePolygonMode(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_polygon_mode())
        {
            PolygonMode mode = (PolygonMode)src->polygon_mode().value();
            dst->setPolygonMode(mode);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parsePolygonModeOverridable(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_polygon_mode_overrideable())
        {
            bool enabled = src->polygon_mode_overrideable().value();
            dst->setPolygonModeOverrideable(enabled);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseFog(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_fog())
        {
            bool overrideable = src->fog().overrideable();

            if (overrideable)
            {
                FogMode mode = (FogMode)src->fog().type();
                auto clr = src->fog().color();
                ColorRGBA color(clr.r(), clr.g(), clr.b(), clr.a());
                float32_t density = src->fog().density();
                float32_t start = src->fog().start();
                float32_t end = src->fog().end();
                dst->setFog(overrideable, mode, color, density, start, end);
            }
            else
            {
                dst->setFog(overrideable);
            }
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseColorWrite(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_color_write())
        {
            bool enabled = src->color_write().value();
            dst->setColorWriteEnabled(enabled);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseMaxLights(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_max_lights())
        {
            dst->setMaxLights((uint16_t)src->max_lights().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseStartLight(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_start_light())
        {
            dst->setStartLight((uint16_t)src->start_light().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseIteration(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        TResult ret = T3D_OK;

        if (src->has_iteration())
        {
            auto iter = src->iteration();

            if (iter.has_once())
            {
                // once
                dst->setIteratePerLight(false);
            }
            else if (iter.has_once_per_light())
            {
                // once per light
                auto data = iter.once_per_light();

                // light type
                switch (data.light_type())
                {
                case Script::MaterialSystem::LT_POINT:
                    dst->setIteratePerLight(true);
                    break;
                case Script::MaterialSystem::LT_DIRECTIONAL:
                    dst->setIteratePerLight(true, true, LightType::DIRECTIONAL);
                    break;
                case Script::MaterialSystem::LT_SPOT:
                    dst->setIteratePerLight(true, true, LightType::SPOTLIGHT);
                    break;
                default:
                    ret = T3D_ERR_RES_INVALID_PROPERTY;
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Invalid iteration data !");
                    break;
                }
            }
            else if (iter.has_per_light())
            {
                // per light
                auto data = iter.per_light();

                // number
                dst->setPassIterationCount(data.number());

                // light type
                switch (data.light_type())
                {
                case Script::MaterialSystem::LT_POINT:
                    dst->setIteratePerLight(true);
                    break;
                case Script::MaterialSystem::LT_DIRECTIONAL:
                    dst->setIteratePerLight(true, true, LightType::DIRECTIONAL);
                    break;
                case Script::MaterialSystem::LT_SPOT:
                    dst->setIteratePerLight(true, true, LightType::SPOTLIGHT);
                    break;
                default:
                    ret = T3D_ERR_RES_INVALID_PROPERTY;
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Invalid iteration data !");
                    break;
                }
            }
            else if (iter.has_per_n_light())
            {
                // per n lights
                auto data = iter.per_n_light();

                // number
                dst->setPassIterationCount(data.number());

                // number of lights
                dst->setLightCountPerIteration(data.num_lights());

                // light type
                switch (data.light_type())
                {
                case Script::MaterialSystem::LT_POINT:
                    dst->setIteratePerLight(true);
                    break;
                case Script::MaterialSystem::LT_DIRECTIONAL:
                    dst->setIteratePerLight(true, true, LightType::DIRECTIONAL);
                    break;
                case Script::MaterialSystem::LT_SPOT:
                    dst->setIteratePerLight(true, true, LightType::SPOTLIGHT);
                    break;
                default:
                    ret = T3D_ERR_RES_INVALID_PROPERTY;
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Invalid iteration data !");
                    break;
                }
            }
            else if (iter.has_number())
            {
                // number
                auto data = iter.number();

                dst->setPassIterationCount(data.number());
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parsePointSize(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_point_size())
        {
            dst->setPointSize(src->point_size().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parsePointSprites(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_point_sprites())
        {
            dst->setPointSpritesEnabled(src->point_sprites().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parsePointSizeAttenuation(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_point_size_attenuation())
        {
            auto attenuation = src->point_size_attenuation();

            if (attenuation.enable())
            {
                // enabled
                float32_t constant = attenuation.constant();
                float32_t linear = attenuation.linear();
                float32_t quadratic = attenuation.quadratic();
                dst->setPointAttenuation(true, constant, linear, quadratic);
            }
            else
            {
                // disabled
                dst->setPointAttenuation(false);
            }
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parsePointSizeMin(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_point_size_min())
        {
            dst->setPointMinSize(src->point_size_min().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parsePointSizeMax(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        if (src->has_point_size_max())
        {
            dst->setPointMaxSize(src->point_size_max().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseGPUProgramRef(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        TResult ret = T3D_OK;

        if (src->has_gpu_program_ref())
        {
            auto data = src->gpu_program_ref();

            // name
            auto header = data.header();
            GPUProgramRefPtr program = GPUProgramRef::create(header.name());
            dst->setGPUProgram(program);

            // GPU constant buffer reference
            auto refs = data.gpu_cbuffer_ref();
            for (const Script::MaterialSystem::GPUConstantBufferRef &ref : refs)
            {
                ret = parseGPUConstantBufferRef(&ref, program);
                T3D_CHECK_PARSING_RET(ret);
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseGPUConstantBufferRef(
        const Script::MaterialSystem::GPUConstantBufferRef *src, GPUProgramRef *dst)
    {
        TResult ret = T3D_OK;

        do 
        {
            // name
            auto header = src->header();

            // slot
            uint32_t slot = src->slot();

            GPUConstBufferRefPtr buffer;
            ret = dst->addConstBufferRef(header.name(), slot, buffer);
            T3D_CHECK_PARSING_RET(ret);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseTextures(
        const Script::MaterialSystem::Pass *src, Pass *dst)
    {
        TResult ret = T3D_OK;
        auto textures = src->textures();
        for (const Script::MaterialSystem::TextureUnit &unit : textures)
        {
            ret = parseTextureUnit(&unit, dst);
            T3D_CHECK_PARSING_RET(ret);
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseTextureUnit(
        const Script::MaterialSystem::TextureUnit *src, Pass *dst)
    {
        TResult ret = T3D_OK;

        do 
        {
            auto header = src->header();

            TextureUnitPtr unit;
            ret = dst->addTextureUnit(header.name(), unit);
            T3D_CHECK_PARSING_RET(ret);

            // texture_alias
            ret = parseTextureAlias(src, unit);
            T3D_CHECK_PARSING_RET(ret);

            // texture
            ret = parseTexture(src, unit);
            T3D_CHECK_PARSING_RET(ret);

            // anim_texture
            ret = parseAnimTexture(src, unit);
            T3D_CHECK_PARSING_RET(ret);

            // cubic_texture
            ret = parseCubicTexture(src, unit);
            T3D_CHECK_PARSING_RET(ret);

            // binding_type
            ret = parseBindingType(src, unit);
            T3D_CHECK_PARSING_RET(ret);

            // tex_coord_set
            ret = parseTexCoordSet(src, unit);
            T3D_CHECK_PARSING_RET(ret);

            // color_op
            ret = parseColorOp(src, unit);
            T3D_CHECK_PARSING_RET(ret);

            // sampler_ref
            ret = parseSamplerRef(src, unit);
            T3D_CHECK_PARSING_RET(ret);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseTextureAlias(
        const Script::MaterialSystem::TextureUnit *src, TextureUnit *dst)
    {
        if (src->has_texture_alias())
        {
            // auto alias = src->texture_alias();
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseTexture(
        const Script::MaterialSystem::TextureUnit *src, TextureUnit *dst)
    {
        if (src->has_texture())
        {
            // texture name
            auto texture = src->texture();

            // texture type
            TextureType texType = (TextureType)texture.type();
            // mipmaps
            uint32_t mipmaps = texture.mipmaps();
            // alpha
            bool alpha = texture.alpha();
            // gamma
            bool gamma = texture.gamma();

            dst->setTextureName(texture.name());
        }
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseAnimTexture(
        const Script::MaterialSystem::TextureUnit *src, TextureUnit *dst)
    {
        if (src->has_anim_texture())
        {
            auto animTex = src->anim_texture();

            if (animTex.has_simple())
            {
                // simple format
                auto simple = animTex.simple();

                // base_name
                auto name = simple.base_name();
                // num_frames
                auto frames = simple.num_frames();
                // duration
                auto duration = simple.duration();
            }
            else if (animTex.has_complex())
            {
                // complex format
                auto complex = animTex.complex();

                // duration
                auto duration = complex.duration();
                // frames
                auto frames = complex.frames();
                for (const String &name : frames)
                {

                }
            }
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseCubicTexture(
        const Script::MaterialSystem::TextureUnit *src, TextureUnit *dst)
    {
        if (src->has_cubic_texture())
        {
            auto cubicTex = src->cubic_texture();

            // combinedUVW | separateUV
            auto mode = cubicTex.cubic_texture_mode();

            if (cubicTex.has_simple())
            {
                // simple format
                auto simple = cubicTex.simple();

                // base_name
                auto name = simple.base_name();
            }
            else if (cubicTex.has_complex())
            {
                // complex format
                auto complex = cubicTex.complex();

                // front
                auto front = complex.front();
                // back
                auto back = complex.back();
                // left
                auto left = complex.left();
                // right
                auto right = complex.right();
                // up
                auto up = complex.up();
                // down
                auto down = complex.down();
            }
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseBindingType(
        const Script::MaterialSystem::TextureUnit *src, TextureUnit *dst)
    {
        if (src->has_binding_type())
        {
            // binding_type
            auto type = src->binding_type().value();
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseTexCoordSet(
        const Script::MaterialSystem::TextureUnit *src, TextureUnit *dst)
    {
        if (src->has_tex_coord_set())
        {
            uint32_t index = src->tex_coord_set().value();
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseColorOp(
        const Script::MaterialSystem::TextureUnit *src, TextureUnit *dst)
    {
        if (src->has_color_op())
        {
            BlendType type = (BlendType)(src->color_op().value());
        }
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseSamplerRef(
        const Script::MaterialSystem::TextureUnit *src, TextureUnit *dst)
    {
        if (src->has_sampler_ref())
        {
//             dst->setSampler(src->sampler_ref().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseSampler(
        const Script::MaterialSystem::Sampler *src, Material *dst)
    {
        TResult ret = T3D_OK;

        do 
        {
            // name
            auto header = src->header();
            SamplerPtr sampler = Sampler::create(header.name());
            if (sampler == nullptr)
            {
                ret = T3D_ERR_RES_INVALID_PROPERTY;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE, "Load sampler [%s] failed !",
                    header.name().c_str());
                break;
            }

            // tex_address_mode
            ret = parseTexAddressMode(src, sampler);
            T3D_CHECK_PARSING_RET(ret);

            // tex_border_color
            ret = parseTexBorderColor(src, sampler);
            T3D_CHECK_PARSING_RET(ret);

            // filtering
            ret = parseFiltering(src, sampler);
            T3D_CHECK_PARSING_RET(ret);

            // compare_test
            ret = parseCompareTest(src, sampler);
            T3D_CHECK_PARSING_RET(ret);

            // compare_func
            ret = parseCompareFunc(src, sampler);
            T3D_CHECK_PARSING_RET(ret);

            // max_anisotropy
            ret = parseMaxAnisotropy(src, sampler);
            T3D_CHECK_PARSING_RET(ret);

            // mipmap_bias
            ret = parseMipmapBias(src, sampler);
            T3D_CHECK_PARSING_RET(ret);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseTexAddressMode(
        const Script::MaterialSystem::Sampler *src, Sampler *dst)
    {
        if (src->has_tex_address_mode())
        {
            auto mode = src->tex_address_mode();

            if (mode.has_simple())
            {
                // simple format
                auto simple = mode.simple();

                TextureAddressMode uvw = (TextureAddressMode)simple.uvw_mode();
                dst->setAddressMode(uvw);
            }
            else if (mode.has_complex())
            {
                // complex format
                auto complex = mode.complex();

                TextureAddressMode u = (TextureAddressMode)complex.u_mode();
                TextureAddressMode v = (TextureAddressMode)complex.v_mode();
                TextureAddressMode w = (TextureAddressMode)complex.w_mode();
                dst->setAddressMode(u, v, w);
            }
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseTexBorderColor(
        const Script::MaterialSystem::Sampler *src, Sampler *dst)
    {
        if (src->has_tex_border_color())
        {
            auto clr = src->tex_border_color();
            ColorRGBA color(clr.r(), clr.g(), clr.b(), clr.a());
            dst->setBorderColor(color);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseFiltering(
        const Script::MaterialSystem::Sampler *src, Sampler *dst)
    {
        if (src->has_filtering())
        {
            auto filter = src->filtering();

            if (filter.has_simple())
            {
                // simple format
                auto simple = filter.simple();
                TexFilterOptions type = (TexFilterOptions)simple.filter();
                dst->setFilter(type);
            }
            else if (filter.has_complex())
            {
                // complex format
                auto complex = filter.complex();
                FilterOptions minFilter = (FilterOptions)complex.minification();
                FilterOptions magFilter = (FilterOptions)complex.magnification();
                FilterOptions mipFilter = (FilterOptions)complex.mip();
                dst->setFilter(minFilter, magFilter, mipFilter);
            }
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseCompareTest(
        const Script::MaterialSystem::Sampler *src, Sampler *dst)
    {
        if (src->has_compare_test())
        {
            dst->setCompareEnabled(src->compare_test().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseCompareFunc(
        const Script::MaterialSystem::Sampler *src, Sampler *dst)
    {
        if (src->has_compare_func())
        {
            CompareFunction func = (CompareFunction)src->compare_func().value();
            dst->setCompareFunction(func);
        }
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseMaxAnisotropy(
        const Script::MaterialSystem::Sampler *src, Sampler *dst)
    {
        if (src->has_max_anisotropy())
        {
            dst->setAnisotropy(src->max_anisotropy().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseMipmapBias(
        const Script::MaterialSystem::Sampler *src, Sampler *dst)
    {
        if (src->has_mipmap_bias())
        {
            dst->setMipmapBias(src->mipmap_bias().value());
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseGPUConstantBuffer(
        const Script::MaterialSystem::GPUConstantBuffer *src, Material *dst)
    {
        TResult ret = T3D_OK;

        do 
        {
            // header & name
            auto header = src->header();
            GPUConstBufferPtr cbuffer;

            uint32_t bufSize = src->buffer_size();

            if (dst != nullptr)
            {
                // belongs to material
                ret = dst->addGPUConstBuffer(header.name(), cbuffer, bufSize);
                T3D_CHECK_PARSING_RET(ret);
            }
            else
            {
                // global
                cbuffer = T3D_GPU_CONST_BUFFER_MGR.loadBuffer(header.name(), bufSize);
                if (cbuffer == nullptr)
                {
                    ret = T3D_ERR_RES_CREATE_GPUCBUFFER;
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                        "Create GPU constant buffer [%s] failed !",
                        header.name().c_str());
                    break;
                }
            }

            // param_indexed
            auto param_indexed = src->param_indexed();
            for (const Script::MaterialSystem::Param &param : param_indexed)
            {
                ret = parseParam(&param, cbuffer, false);
                T3D_CHECK_PARSING_RET(ret);
            }

            T3D_CHECK_PARSING_RET(ret);

            // param_indexed_auto
            auto param_indexed_auto = src->param_indexed_auto();
            for (const Script::MaterialSystem::ParamAuto &param : param_indexed_auto)
            {
                ret = parseParamAuto(&param, cbuffer, false);
                T3D_CHECK_PARSING_RET(ret);
            }

            T3D_CHECK_PARSING_RET(ret);

            // param_named
            auto param_named = src->param_named();
            for (const Script::MaterialSystem::Param &param : param_named)
            {
                ret = parseParam(&param, cbuffer, true);
                T3D_CHECK_PARSING_RET(ret);
            }

            T3D_CHECK_PARSING_RET(ret);

            // param_named_auto
            auto param_named_auto = src->param_named_auto();
            for (const Script::MaterialSystem::ParamAuto &param : param_named_auto)
            {
                ret = parseParamAuto(&param, cbuffer, true);
                T3D_CHECK_PARSING_RET(ret);
            }

            T3D_CHECK_PARSING_RET(ret);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseParam(
        const Script::MaterialSystem::Param *src, GPUConstBuffer *dst, bool named)
    {
        String name;
        uint32_t index = 0;

        if (named)
        {
            // name
            name = src->name();
        }
        else
        {
            // index
            index = src->index();
        }

        // type
        auto type = src->type();

        uint32_t count = 0;
        uint8_t *data = nullptr;
        uint32_t dataSize = 0;

        // values
        if (Script::MaterialSystem::BuiltInType::BT_INT == type)
        {
            count = src->ivalues_size();
            auto values = src->ivalues();
            data = (uint8_t*)values.data();
            dataSize = count * sizeof(uint32_t);
        }
        else if (Script::MaterialSystem::BuiltInType::BT_REAL == type)
        {
            count = src->fvalues_size();
            auto values = src->fvalues();
            data = (uint8_t*)values.data();
            dataSize = count * sizeof(float32_t);
        }

        if (count > 0)
        {
            dst->addDeclaration((BuiltinType)type, count, data, dataSize);
        }

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseParamAuto(
        const Script::MaterialSystem::ParamAuto *src, GPUConstBuffer *dst, bool named)
    {
        String name;
        uint32_t index = 0;

        if (named)
        {
            // name
            name = src->name();
        }
        else
        {
            // index
            index = src->index();
        }

        // value_code
        BuiltinConstantType code = (BuiltinConstantType)src->value_code();

        uint32_t extraCount = 0;

        // extra_params
        if (src->fextra_params_size() > 0)
        {
            extraCount = src->fextra_params_size();
        }
        else if (src->iextra_params_size() > 0)
        {
            extraCount = src->iextra_params_size();
        }

        auto itr = mDefinitions.find(code);
        if (itr != mDefinitions.end())
        {
            dst->addDeclaration(code, itr->second.elementType,
                itr->second.elementCount, itr->second.extraType, extraCount);
        }
        
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseGPUProgram(
        const Script::MaterialSystem::GPUProgram *src, Material *dst)
    {
        TResult ret = T3D_OK;

        do 
        {
            // header & name
            auto header = src->header();
            GPUProgramPtr program;

            if (dst != nullptr)
            {
                // belongs to material
                ret = dst->addGPUProgram(header.name(), program);
                T3D_CHECK_PARSING_RET(ret);
            }
            else
            {
                // global
                program = T3D_GPU_PROGRAM_MGR.loadGPUProgram(header.name());
                if (program == nullptr)
                {
                    ret = T3D_ERR_RES_CREATE_GPUPROGRAM;
                    T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                        "Create GPU Program [%s] failed !", 
                        header.name().c_str());
                    break;
                }
            }

            // shaders
            auto shaders = src->shaders();
            for (const Script::MaterialSystem::Shader &shader : shaders)
            {
                ret = parseShader(&shader, program);
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult MaterialReader::parseShader(
        const Script::MaterialSystem::Shader *src, GPUProgram *dst)
    {
        TResult ret = T3D_OK;

        do 
        {
            // header & name
            auto header = src->header();

            // properties
            const String &source = src->source();
            const String &target = src->target();
            const String &entry = src->entry();
            const String &stage = src->stage();

            Shader::ShaderType shaderType = Shader::ShaderType::VERTEX_SHADER;
            size_t len = source.find_last_of('.');
            String title =
                (len != String::npos ? source.substr(0, len) : source);
            String filename = title + "." + stage;

            if (stage == "vs")
            {
                // vertex shader
                shaderType = Shader::ShaderType::VERTEX_SHADER;
            }
            else if (stage == "ps")
            {
                // fragment shader
                shaderType = Shader::ShaderType::PIXEL_SHADER;

            }
            else if (stage == "gs")
            {
                // geometry shader
                shaderType = Shader::ShaderType::GEOMETRY_SHADER;
            }
            else if (stage == "ds")
            {
                shaderType = Shader::ShaderType::DOMAIN_SHADER;
            }
            else if (stage == "cs")
            {
                shaderType = Shader::ShaderType::COMPUTE_SHADER;
            }
            else
            {
                ret = T3D_ERR_RES_INVALID_PROPERTY;
                T3D_LOG_ERROR(LOG_TAG_RESOURCE,
                    "Invalid property of GPU program !");
                break;
            }

            ShaderPtr shader;
            ret = dst->addShader(filename, shaderType, shader);
            T3D_CHECK_PARSING_RET(ret);
        } while (0);

        return ret;
    }
}
