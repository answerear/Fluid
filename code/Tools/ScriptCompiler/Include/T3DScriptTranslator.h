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

#ifndef __T3D_SCRIPT_TRANSLATOR_H__
#define __T3D_SCRIPT_TRANSLATOR_H__


#include "T3DScriptPrerequisites.h"
#include "T3DScriptType.h"
#include "T3DScriptASTree.h"
#include "MaterialScriptObject.pb.h"


namespace Tiny3D
{
    class ScriptCompiler;

//     using namespace Script;

    //--------------------------------------------------------------------------

    class ScriptTranslator
    {
    public:
        T3D_DECLARE_INTERFACE(ScriptTranslator);

        virtual bool translate(ScriptCompiler *compiler, void *object,
            const AbstractNodePtr &node) = 0;

    protected:
        bool processNode(ScriptCompiler *compiler, void *object,
            const AbstractNodePtr &node);

        bool translateObjectHeader(ObjectAbstractNode *obj, 
            Script::ObjectHeader *header);

        AbstractNodeList::const_iterator getNodeAt(
            const AbstractNodeList &nodes, int32_t index);

        bool getBoolean(const AbstractNodePtr &node, bool *result);
        bool getString(const AbstractNodePtr &node, String *result);
        bool getSingle(const AbstractNodePtr &node, float32_t *result);
        bool getDouble(const AbstractNodePtr &node, float64_t *result);
        bool getInt(const AbstractNodePtr &node, int32_t *result);
        bool getUInt(const AbstractNodePtr &node, uint32_t *result);
        bool getHex(const AbstractNodePtr &node, uint32_t *result);

        bool getColor(AbstractNodeList::const_iterator i, 
            AbstractNodeList::const_iterator end, 
            Script::Color *result, 
            int32_t maxEntries = 4);

        bool getMatrix4(AbstractNodeList::const_iterator i, 
            AbstractNodeList::const_iterator end, 
            Script::Matrix4 *m);

        bool getInts(AbstractNodeList::const_iterator i, 
            AbstractNodeList::const_iterator end, 
            int32_t *vals, int32_t count);

        bool getSingles(AbstractNodeList::const_iterator i, 
            AbstractNodeList::const_iterator end, 
            float32_t *vals, int32_t count);

        BuiltinType getBuiltinType(const String &name);
    };

    //--------------------------------------------------------------------------

    class MaterialTranslator : public ScriptTranslator
    {
    public:
        virtual bool translate(ScriptCompiler *compiler, void *object, 
            const AbstractNodePtr &node) override;

    protected:
        bool translateLODValues(
            PropertyAbstractNode *prop, Script::MaterialSystem::Material *material);
        bool translateLODStrategy(
            PropertyAbstractNode *prop, Script::MaterialSystem::Material *material);
        bool translateReceiveShadow(
            PropertyAbstractNode *prop, Script::MaterialSystem::Material *material);
        bool translateTransparentCastsShadow(
            PropertyAbstractNode *prop, Script::MaterialSystem::Material *material);
        bool translateSetTextuerAlias(
            PropertyAbstractNode *prop, Script::MaterialSystem::Material *material);
    };

    //--------------------------------------------------------------------------

    class TechniqueTranslator : public ScriptTranslator
    {
    public:
        virtual bool translate(ScriptCompiler *compiler, void *object,
            const AbstractNodePtr &node) override;

    protected:
        bool translateScheme(
            PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech);
        bool translateLODIndex(
            PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech);
        bool translateRenderQueue(
            PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech);
        bool translateShadowCasterMaterial(
            PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech);
        bool translateShadowReceiveMaterial(
            PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech);
        bool translateGPUVendorRule(
            PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech);
        bool translateGPUDeviceRule(
            PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech);
    };

    //--------------------------------------------------------------------------

    class PassTranslator : public ScriptTranslator
    {
    public:
        virtual bool translate(ScriptCompiler *compiler, void *object,
            const AbstractNodePtr &node) override;

    protected:
        bool translateAmbient(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateDiffuse(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateSpecular(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateEmissive(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateSceneBlend(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateSeparateSceneBlend(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateSceneBlendOp(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateSeparateSceneBlendOp(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateDepthCheck(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateDepthWrite(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateDepthBias(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateDepthFunc(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateIterationDepthBias(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateAlphaRejection(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateAlphaToCoverage(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateLightScissor(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateLightClipPlanes(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateTransparentSorting(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateIlluminationStage(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateCullHardware(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateCullSoftware(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateNormalizeNormals(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateLighting(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateShading(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translatePolygonMode(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translatePolygonModeOverridable(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateFogOverride(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateColorWrite(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateMaxLights(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateStartLight(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateLightMask(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translateIteration(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translatePointSize(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translatePointSprites(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translatePointSizeAttenuation(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translatePointSizeMin(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
        bool translatePointSizeMax(
            PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass);
    };

    //--------------------------------------------------------------------------

    class TextureUnitTranslator : public ScriptTranslator
    {
    public:
        virtual bool translate(ScriptCompiler *compiler, void *object,
            const AbstractNodePtr &node) override;

    protected:
        bool translateSamplerRef(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateTextureAlias(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);

        bool translateTexture(ScriptCompiler *compiler, 
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);

        bool translateAnimTexture(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateCubicTexture(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateTexCoordSet(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateColorOp(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateColorOpEx(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateColorOpMultiPassFallback(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateAlphaOpEx(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateEnvMap(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateScroll(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateScrollAnim(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateRotate(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateRotateAnim(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateScale(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateWaveXform(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateTransform(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateBindingType(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
        bool translateContentType(
            PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit);
    };

    //--------------------------------------------------------------------------

    class SamplerTranslator : public ScriptTranslator
    {
    public:
        virtual bool translate(ScriptCompiler *compiler, void *object,
            const AbstractNodePtr &node) override;

        bool translateSamplerParams(
            PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler);

    protected:
        bool translateTexAddressMode(
            PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler);
        bool translateTexBorderColor(
            PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler);
        bool translateFiltering(
            PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler);
        bool translateCompareTest(
            PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler);
        bool translateCompareFunc(
            PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler);
        bool translateMaxAnisotropy(
            PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler);
        bool translateMipmapBias(
            PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler);
    };

    //--------------------------------------------------------------------------

    class GPUProgramTranslator : public ScriptTranslator
    {
    public:
        GPUProgramTranslator();

        virtual bool translate(ScriptCompiler *compiler, void *object,
            const AbstractNodePtr &node) override;

    protected:
        bool translateGPUProgram(ScriptCompiler *compiler, 
            void *object, ObjectAbstractNode *obj);

        bool translateGPUProgramRef(ScriptCompiler *compiler, 
            void *object, ObjectAbstractNode *obj);

        bool translateShader(ScriptCompiler* compiler,
            void *object, ObjectAbstractNode* obj);

        bool translateGPUCBuffer(ScriptCompiler *compiler, 
            void *object, ObjectAbstractNode *obj);

        bool translateGPUCBufferRef(ScriptCompiler* compiler, 
            void *object, ObjectAbstractNode *obj);

        bool translateSharedParamRef(
            PropertyAbstractNode *prop, Script::MaterialSystem::GPUConstantBuffer *cbuffer);
        bool translateParamIndexed(
            PropertyAbstractNode *prop, Script::MaterialSystem::GPUConstantBuffer *cbuffer);
        bool translateParamIndexedAuto(
            PropertyAbstractNode *prop, Script::MaterialSystem::GPUConstantBuffer *cbuffer,
            uint32_t &count);

        bool translateCBuffer(
            PropertyAbstractNode* prop, Script::MaterialSystem::GPUConstantBufferRef *cref);

//         size_t translateGPUProgramEx(ScriptCompiler *compiler, 
//             DataStream &stream, ObjectAbstractNode *obj);
//         size_t translateGPUProgramRefEx(ScriptCompiler *compiler, 
//             DataStream &stream, ObjectAbstractNode *obj);

        void constructBuiltinConstantMap();

        typedef std::map<String, BuiltinConstantDefinition> BuiltinConstantMap;
        typedef BuiltinConstantMap::iterator                BuiltinConstantMapItr;
        typedef BuiltinConstantMap::const_iterator          BuiltinConstantMapConstItr;
        typedef BuiltinConstantMap::value_type              BuiltinConstantMapValue;

        BuiltinConstantMap   mBuiltinConstantMap;
    };
}


#endif  /*__T3D_SCRIPT_TRANSLATOR_H__*/
