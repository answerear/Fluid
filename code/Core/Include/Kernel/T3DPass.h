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


#ifndef __T3D_PASS_H__
#define __T3D_PASS_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "T3DObject.h"
#include "Kernel/T3DAgent.h"
#include "Kernel/T3DBlendMode.h"
#include "Kernel/T3DCommon.h"
#include "Resource/T3DGPUProgram.h"
#include "Resource/T3DGPUConstBuffer.h"
#include "Kernel/T3DTextureUnit.h"
#include "Render/T3DRenderContext.h"
#include "Render/T3DRenderCapabilities.h"


namespace Tiny3D
{
    /**
     * @class   Pass
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API Pass : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        typedef TArray<GPUConstBufferPtr>       GPUConstBuffers;
        typedef GPUConstBuffers::iterator       GPUConstBuffersItr;
        typedef GPUConstBuffers::const_iterator GPUConstBuffersConstItr;

        typedef TArray<TextureUnitPtr>          TextureUnits;
        typedef TextureUnits::iterator          TextureUnitsItr;
        typedef TextureUnits::const_iterator    TextureUnitsConstItr;

        /**
         * @fn  static PassPtr Pass::create(const String &name, 
         *      Technique *tech);
         * @brief   创建 Pass 对象
         * @param [in]  name    Pass 名称.
         * @param [in]  tech    Pass 所属的 Technique 对象.
         * @return  调用成功返回一个 Pass 对象.
         */
        static PassPtr create(const String &name, Technique *tech);

        /**
         * @fn  virtual Pass::~Pass();
         * @brief   析构函数
         */
        virtual ~Pass();

        /**
         * @fn  const String Pass::&getName() const
         * @brief   獲取 Pass 名稱
         * @returns 返回 Pass 名称.
         */
        const String &getName() const;

        /**
         * @fn  TResult Pass::setGPUProgram(GPUProgramRefPtr program);
         * @brief   设置 Pass 使用的 GPU 程序对象
         * @param [in]  program GPU 程序对象.
         * @returns 调用成功返回 T3D_OK.
         */
        TResult setGPUProgram(GPUProgramRefPtr program);

        /**
         * @fn  GPUProgramPtr Pass::getGPUProgram() const;
         * @brief   获取 GPU 程序对象
         * @returns 返回 GPU 程序对象.
         */
        GPUProgramPtr getGPUProgram() const;

        /**
         * @fn  GPUConstBuffers Pass::getGPUConstBuffers() const;
         * @brief   获取 GPU 程序绑定的所有常量缓冲区对象
         * @returns 返回 GPU 程序绑定的所有常量缓冲区对象.
         */
        GPUConstBuffers getGPUConstBuffers() const;

        /**
         * @fn  GPUConstBufferPtr Pass::getGPUConstBuffer(uint32_t slot) const
         * @brief   Gets GPU constant buffer
         * @param   slot    The slot.
         * @return  The GPU constant buffer.
         */
        GPUConstBufferPtr getGPUConstBuffer(uint32_t slot) const;

        /**
         * @fn  size_t Pass::getGPUConstBufferCount() const;
         * @brief   Gets GPU constant buffer count
         * @returns The GPU constant buffer count.
         */
        size_t getGPUConstBufferCount() const;

        /**
         * @fn  TResult Pass::addTextureUnit(const String &name, 
         *      TextureUnitPtr &unit);
         * @brief   Adds a texture unit to 'unit'
         * @param           name    The name.
         * @param [in,out]  unit    The unit.
         * @return  A TResult.
         */
        TResult addTextureUnit(const String &name, TextureUnitPtr &unit);

        /**
         * @fn  TResult Pass::removeTextureUnit(const String &name);
         * @brief   Removes the texture unit described by name
         * @param   name    The name.
         * @return  A TResult.
         */
        TResult removeTextureUnit(const String &name);

        /**
         * @fn  TResult Pass::removeTextureUnit(size_t index);
         * @brief   Removes the texture unit described by index
         * @param   index   Zero-based index of the.
         * @return  A TResult.
         */
        TResult removeTextureUnit(size_t index);

        /**
         * @fn  TextureUnitPtr Pass::getTextureUnit(const String &name) const;
         * @brief   Gets texture unit
         * @param   name    The name.
         * @return  The texture unit.
         */
        TextureUnitPtr getTextureUnit(const String &name) const;

        /**
         * @fn  TextureUnitPtr Pass::getTextureUnit(size_t index) const;
         * @brief   Gets texture unit
         * @param   index   Zero-based index of the.
         * @return  The texture unit.
         */
        TextureUnitPtr getTextureUnit(size_t index) const;

        /**
         * @fn  const TextureUnits Pass::&getTextureUnits() const;
         * @brief   Gets texture units
         * @return  The texture units.
         */
        const TextureUnits &getTextureUnits() const;

        /**
         * @fn  size_t Pass::getTextureUnitsCount() const;
         * @brief   获取纹理单元数量
         * @return  The texture units count.
         */
        size_t getTextureUnitsCount() const;

        /**
         * @fn  bool Pass::hasVertexShader() const;
         * @brief   是否有顶点着色器
         * @return  True if vertex shader, false if not.
         */
        bool hasVertexShader() const;

        /**
         * @fn  bool Pass::hasPixelShader() const;
         * @brief   是否有像素着色器
         * @return  True if pixel shader, false if not.
         */
        bool hasPixelShader() const;

        /**
         * @fn  bool Pass::hasGeometryShader() const;
         * @brief   是否有几何着色器
         * @return  True if geometry shader, false if not.
         */
        bool hasGeometryShader() const;

        /**
         * @fn  bool Pass::hasComputeShader() const;
         * @brief   是否有计算着色器
         * @return  True if compute shader, false if not.
         */
        bool hasComputeShader() const;

        /**
         * @fn  bool Pass::hasHullShader() const;
         * @brief   是否有细分曲面控制着色器
         * @return  True if hull shader, false if not.
         */
        bool hasHullShader() const;

        /**
         * @fn  bool Pass::hasDomainShader() const;
         * @brief   是否有细分曲面计算着色器
         * @return  True if domain shader, false if not.
         */
        bool hasDomainShader() const;

        /**
         * @fn  const ColorRGBA Pass::&getAmbient() const;
         * @brief   获取环境光颜色
         * @return  The ambient.
         */
        const ColorRGBA &getAmbient() const;

        /**
         * @fn  void Pass::setAmbient(const ColorRGBA &color);
         * @brief   设置环境光颜色
         * @param   color   The color.
         */
        void setAmbient(const ColorRGBA &color);

        /**
         * @fn  void Pass::setAmbient(Real red, Real green, Real blue);
         * @brief   设置环境光颜色
         * @param   red     The red.
         * @param   green   The green.
         * @param   blue    The blue.
         */
        void setAmbient(Real red, Real green, Real blue, Real alpha = 1.0f);

        /**
         * @fn  const ColorRGBA Pass::&getDiffuse() const;
         * @brief   获取漫反射光颜色
         * @return  The diffuse.
         */
        const ColorRGBA &getDiffuse() const;

        /**
         * @fn  void Pass::setDiffuse(const ColorRGBA &color);
         * @brief   设置漫反射光颜色
         * @param   color   The color.
         */
        void setDiffuse(const ColorRGBA &color);

        /**
         * @fn  void Pass::setDiffuse(Real red, Real green, Real blue, 
         *      Real alpha);
         * @brief   设置漫反射光颜色
         * @param   red     The red.
         * @param   green   The green.
         * @param   blue    The blue.
         * @param   alpha   The alpha.
         */
        void setDiffuse(Real red, Real green, Real blue, Real alpha = 1.0f);

        /**
         * @fn  const ColorRGBA Pass::&getSpecular() const;
         * @brief   获取镜面反射光颜色
         * @return  The specular.
         */
        const ColorRGBA &getSpecular() const;

        /**
         * @fn  void Pass::setSpecular(const ColorRGBA &color);
         * @brief   设置镜面反射光颜色
         * @param   color   The color.
         */
        void setSpecular(const ColorRGBA &color);

        /**
         * @fn  void Pass::setSpecular(Real red, Real green, Real blue, 
         *      Real alpha);
         * @brief   设置镜面反射光颜色
         * @param   red     The red.
         * @param   green   The green.
         * @param   blue    The blue.
         * @param   alpha   The alpha.
         */
        void setSpecular(Real red, Real green, Real blue, Real alpha = 1.0f);

        /**
         * @fn  Real Pass::getShininess() const;
         * @brief   获取镜面反射的亮度
         * @return  The shininess.
         */
        Real getShininess() const;

        /**
         * @fn  void Pass::setShininess(Real value);
         * @brief   设置镜面反射的亮度
         * @param   value   The value.
         */
        void setShininess(Real value);

        /**
         * @fn  const ColorRGBA Pass::&getEmissive() const;
         * @brief   获取自发光颜色
         * @return  The emissive.
         */
        const ColorRGBA &getEmissive() const;

        /**
         * @fn  void Pass::setEmissive(const ColorRGBA &color);
         * @brief   设置自发光颜色
         * @param   color   The color.
         */
        void setEmissive(const ColorRGBA &color);

        /**
         * @fn  void Pass::setEmissive(Real red, Real green, Real blue);
         * @brief   设置自发光颜色
         * @param   red     The red.
         * @param   green   The green.
         * @param   blue    The blue.
         */
        void setEmissive(Real red, Real green, Real blue, Real alpha = 1.0f);

        /**
         * @fn  TrackVertexColorType Pass::getVertexColorTracking() const;
         * @brief   获取顶点颜色用于光的类型
         * @return  The vertex color tracking.
         */
        TrackVertexColorType getVertexColorTracking() const;

        /**
         * @fn  void Pass::setVertexColorTracking(
         *      TrackVertexColorType tracking);
         * @brief   设置顶点颜色用于光的类型
         * @param   tracking    The tracking.
         */
        void setVertexColorTracking(TrackVertexColorType tracking);

        /**
         * @fn  BlendFactor Pass::getSourceBlendFactor() const;
         * @brief   获取源混合因子
         * @return  The source blend factor.
         */
        BlendFactor getSourceBlendFactor() const;

        /**
         * @fn  BlendFactor Pass::getDestBlendFactor() const;
         * @brief   获取目标混合因子
         * @return  The destination blend factor.
         */
        BlendFactor getDestBlendFactor() const;

        /**
         * @fn  BlendFactor Pass::getSourceBlendFactorAlpha() const;
         * @brief   获取 alpha 源混合因子
         * @return  The source blend factor alpha.
         */
        BlendFactor getSourceBlendFactorAlpha() const;

        /**
         * @fn  BlendFactor Pass::getDestBlendFactorAlpha() const;
         * @brief   获取 alpha 目标混合因子
         * @return  The destination blend factor alpha.
         */
        BlendFactor getDestBlendFactorAlpha() const;

        /**
         * @fn  void Pass::setSceneBlending(BlendType bt);
         * @brief   设置混合类型
         * @param   bt  The bt.
         */
        void setSceneBlending(BlendType bt);

        /**
         * @fn  void Pass::setSceneBlending(BlendFactor src, BlendFactor dst);
         * @brief   设置混合因子
         * @param   src Source for the.
         * @param   dst Destination for the.
         */
        void setSceneBlending(BlendFactor src, BlendFactor dst);

        /**
         * @fn  void Pass::setSeparateSceneBlending(BlendType bt, 
         *      BlendType bta);
         * @brief   分别设置混合类型
         * @param   bt  The bt.
         * @param   bta The bta.
         */
        void setSeparateSceneBlending(BlendType bt, BlendType bta);

        /**
         * @fn  void Pass::setSeparateSceneBlending(BlendFactor src, 
         *      BlendFactor dst, BlendFactor srcAlpha, BlendFactor dstAlpha);
         * @brief   分别设置混合因子
         * @param   src         Source for the.
         * @param   dst         Destination for the.
         * @param   srcAlpha    Source alpha.
         * @param   dstAlpha    Destination alpha.
         */
        void setSeparateSceneBlending(BlendFactor src, BlendFactor dst, 
            BlendFactor srcAlpha, BlendFactor dstAlpha);

        /**
         * @fn  BlendOperation Pass::getSceneBlendingOperation() const;
         * @brief   获取混合操作
         * @return  The scene blending operation.
         */
        BlendOperation getSceneBlendingOperation() const;

        /**
         * @fn  BlendOperation Pass::getSceneBlendingOperationAlpha() const;
         * @brief   获取 Alpha 混合操作
         * @return  The scene blending operation alpha.
         */
        BlendOperation getSceneBlendingOperationAlpha() const;

        /**
         * @fn  void Pass::setSceneBlendingOperation(BlendOperation op);
         * @brief   设置混合操作
         * @param   op  The operation.
         */
        void setSceneBlendingOperation(BlendOperation op);

        /**
         * @fn  void Pass::setSeparateSceneBlendingOperation(BlendOperation op, 
         *      BlendOperation alphaOp);
         * @brief   分别设置颜色部分和 Alpha 部分混合操作
         * @param   op      The operation.
         * @param   alphaOp The alpha operation.
         */
        void setSeparateSceneBlendingOperation(BlendOperation op, 
            BlendOperation alphaOp);

        /**
         * @fn  const BlendState Pass::&getBlendState() const;
         * @brief   Gets blend state
         * @return  The blend state.
         */
        const BlendMode &getBlendState() const;

        /**
         * @fn  bool Pass::isTransparent() const;
         * @brief   Query if this object is transparent
         * @return  True if transparent, false if not.
         */
        bool isTransparent() const;

        /**
         * @fn  bool Pass::isDepthCheckEnabled() const;
         * @brief   获取是否开启深度检测
         * @return  True if the depth check is enabled, false if not.
         */
        bool isDepthCheckEnabled() const;

        /**
         * @fn  void Pass::setDepthCheckEnabled(bool enabled);
         * @brief   设置是否开启深度检测
         * @param   enabled True to enable, false to disable.
         */
        void setDepthCheckEnabled(bool enabled);

        /**
         * @fn  bool Pass::isDepthWriteEnabled() const;
         * @brief   获取是否写深度值
         * @return  True if the depth write is enabled, false if not.
         */
        bool isDepthWriteEnabled() const;

        /**
         * @fn  void Pass::setDepthWriteEnabled(bool enabled);
         * @brief   设置是否写深度值
         * @param   enabled True to enable, false to disable.
         */
        void setDepthWriteEnabled(bool enabled);

        /**
         * @fn  CompareFunction Pass::getDepthFunction() const;
         * @brief   获取深度比较函数
         * @return  The depth function.
         */
        CompareFunction getDepthFunction() const;

        /**
         * @fn  void Pass::setDepthFunction(CompareFunction func);
         * @brief   设置深度比较函数
         * @param   func    The function.
         */
        void setDepthFunction(CompareFunction func);

        /**
         * @fn  Real Pass::getDepthBiasConstant() const;
         * @brief   获取深度偏移常量
         * @return  The depth bias constant.
         */
        Real getDepthBiasConstant() const;

        /**
         * @fn  Real Pass::getDepthBiasSlopeScale() const;
         * @brief   获取深度坡度偏移
         * @return  The depth bias slope scale.
         */
        Real getDepthBiasSlopeScale() const;

        /**
         * @fn  void Pass::setDepthBias(Real constantBias, 
         *      Real slopeScaleBias = 0.0f);
         * @brief   设置深度偏移常量和坡度偏移
         * @param   constantBias    The constant bias.
         * @param   slopeScaleBias  (Optional) The slope scale bias.
         * @remarks  $$finalBias = maxSlope * slopeScaleBias + constantBias$$.
         */
        void setDepthBias(Real constantBias, Real slopeScaleBias = 0.0f);

        /**
         * @fn  Real Pass::getDepthBiasPerIteration() const;
         * @brief   获取深度迭代偏移
         * @return  The depth bias per iteration.
         */
        Real getDepthBiasPerIteration() const;

        /**
         * @fn  void Pass::setDepthBiasPerIteration(Real biasPerIteration);
         * @brief   设置深度迭代偏移
         * @param   biasPerIteration    The bias per iteration.
         * @remarks $$finalBias = constantBias + biasPerIteration * iteration$$.
         */
        void setDepthBiasPerIteration(Real biasPerIteration);

        /**
         * @fn  CompareFunction Pass::getAlphaRejectFunction() const;
         * @brief   Gets alpha reject function
         * @return  The alpha reject function.
         */
        CompareFunction getAlphaRejectFunction() const;

        /**
         * @fn  void Pass::setAlphaRejectFunction(CompareFunction func);
         * @brief   Sets alpha reject function
         * @param   func    The function.
         */
        void setAlphaRejectFunction(CompareFunction func);

        /**
         * @fn  uint8_t Pass::getAlphaRejectValue() const;
         * @brief   Gets alpha reject value
         * @return  The alpha reject value.
         */
        uint8_t getAlphaRejectValue() const;

        /**
         * @fn  void Pass::setAlphaRejectValue(uint8_t val);
         * @brief   Sets alpha reject value
         * @param   val The value.
         */
        void setAlphaRejectValue(uint8_t val);

        /**
         * @fn  bool Pass::isAlphaToCoverageEnabled() const;
         * @brief   Queries if the alpha to coverage is enabled
         * @return  True if the alpha to coverage is enabled, false if not.
         */
        bool isAlphaToCoverageEnabled() const;

        /**
         * @fn  void Pass::setAlphaToCoverageEnabled(bool enabled);
         * @brief   Sets alpha to coverage enabled
         * @param   enabled True to enable, false to disable.
         */
        void setAlphaToCoverageEnabled(bool enabled);

        /**
         * @fn  void Pass::setAlphaRejectSettings(CompareFunction func, 
         *      uint8_t val, bool alphaToCoverageEnabled = false);
         * @brief   Sets alpha reject settings
         * @param   func                    The function.
         * @param   val                     The value.
         * @param   alphaToCoverageEnabled  (Optional) True to enable, false to 
         *                                  disable the alpha to coverage.
         */
        void setAlphaRejectSettings(CompareFunction func, uint8_t val, 
            bool alphaToCoverageEnabled = false);

        /**
         * @fn  bool Pass::isLightScissoringEnabled() const;
         * @brief   Queries if the light scissoring is enabled
         * @return  True if the light scissoring is enabled, false if not.
         */
        bool isLightScissoringEnabled() const;

        /**
         * @fn  void Pass::setLightScissoringEnabled(bool enabled);
         * @brief   Sets light scissoring enabled
         * @param   enabled True to enable, false to disable.
         */
        void setLightScissoringEnabled(bool enabled);

        /**
         * @fn  bool Pass::isLightClipPlanesEnabled() const;
         * @brief   Queries if the light clip planes is enabled
         * @return  True if the light clip planes is enabled, false if not.
         */
        bool isLightClipPlanesEnabled() const;

        /**
         * @fn  void Pass::setLightClipPlanesEnabled(bool enabled);
         * @brief   Sets light clip planes enabled
         * @param   enabled True to enable, false to disable.
         */
        void setLightClipPlanesEnabled(bool enabled);

        /**
         * @fn  bool Pass::isLightEnabled() const;
         * @brief   Queries if the light is enabled
         * @return  True if the light is enabled, false if not.
         */
        bool isLightEnabled() const;

        /**
         * @fn  void Pass::setLightEnabled(bool enabled);
         * @brief   Sets light enabled
         * @param   enabled True to enable, false to disable.
         */
        void setLightEnabled(bool enabled);

        /**
         * @fn  bool Pass::isNormalizeNormalsEnabled() const;
         * @brief   Queries if the normalize normals is enabled
         * @return  True if the normalize normals is enabled, false if not.
         */
        bool isNormalizeNormalsEnabled() const;

        /**
         * @fn  void Pass::setNormalizeNormalsEnabled(bool enabled);
         * @brief   Sets normalize normals enabled
         * @param   enabled True to enable, false to disable.
         */
        void setNormalizeNormalsEnabled(bool enabled);

        /**
         * @fn  bool Pass::isTransparentSortingEnabled() const;
         * @brief   Queries if the transparent sorting is enabled
         * @return  True if the transparent sorting is enabled, false if not.
         */
        bool isTransparentSortingEnabled() const;

        /**
         * @fn  void Pass::setTransparentSortingEnabled(bool enabled);
         * @brief   Sets transparent sorting enabled
         * @param   enabled True to enable, false to disable.
         */
        void setTransparentSortingEnabled(bool enabled);

        /**
         * @fn  bool Pass::isTransparentSortingForced() const;
         * @brief   Query if this object is transparent sorting forced
         * @return  True if transparent sorting forced, false if not.
         */
        bool isTransparentSortingForced() const;

        /**
         * @fn  void Pass::setTransparentSortingForced(bool enabled);
         * @brief   Sets transparent sorting forced
         * @param   enabled True to enable, false to disable.
         */
        void setTransparentSortingForced(bool enabled);

        /**
         * @fn  bool Pass::isColorWriteEnabled() const;
         * @brief   Queries if the color write is enabled
         * @return  True if the color write is enabled, false if not.
         */
        bool isColorWriteEnabled() const;

        /**
         * @fn  void Pass::setColorWriteEnabled(bool enabled);
         * @brief   Sets color write enabled
         * @param   enabled True to enable, false to disable.
         */
        void setColorWriteEnabled(bool enabled);

        /**
         * @fn  void Pass::isColorWriteEnabled(bool &red, bool &green, bool &blue, bool &alpha);
         * @brief   Is color write enabled
         * @param [in,out]  red     True if red.
         * @param [in,out]  green   True to green.
         * @param [in,out]  blue    True to blue.
         * @param [in,out]  alpha   True to alpha.
         */
        void isColorWriteEnabled(bool &red, bool &green, bool &blue, bool &alpha);

        /**
         * @fn  void Pass::setColorWriteEnabled(bool red, bool green, bool blue, bool alpha);
         * @brief   Sets color write enabled
         * @param   red     True if red.
         * @param   green   True to green.
         * @param   blue    True to blue.
         * @param   alpha   True to alpha.
         */
        void setColorWriteEnabled(bool red, bool green, bool blue, bool alpha);

        /**
         * @fn  bool Pass::isPolygonModeOverrideable() const;
         * @brief   Query if this object is polygon mode overrideable
         * @return  True if polygon mode overrideable, false if not.
         */
        bool isPolygonModeOverrideable() const;

        /**
         * @fn  void Pass::setPolygonModeOverrideable(bool enabled);
         * @brief   Sets polygon mode overrideable
         * @param   enabled True to enable, false to disable.
         */
        void setPolygonModeOverrideable(bool enabled);

        /**
         * @fn  CullingMode Pass::getCullingMode() const;
         * @brief   Gets culling mode
         * @return  The culling mode.
         */
        CullingMode getCullingMode() const;

        /**
         * @fn  void Pass::setCullingMode(CullingMode mode);
         * @brief   Sets culling mode
         * @param   mode    The mode.
         */
        void setCullingMode(CullingMode mode);

        /**
         * @fn  ManualCullingMode Pass::getManualCullingMode() const;
         * @brief   Gets manual culling mode
         * @return  The manual culling mode.
         */
        ManualCullingMode getManualCullingMode() const;

        /**
         * @fn  void Pass::setManualCullingMode(ManualCullingMode mode);
         * @brief   Sets manual culling mode
         * @param   mode    The mode.
         */
        void setManualCullingMode(ManualCullingMode mode);

        /**
         * @fn  IlluminationStage Pass::getIlluminationStage() const;
         * @brief   Gets illumination stage
         * @return  The illumination stage.
         */
        IlluminationStage getIlluminationStage() const;

        /**
         * @fn  void Pass::setIlluminationStage(IlluminationStage stage);
         * @brief   Sets illumination stage
         * @param   stage   The stage.
         */
        void setIlluminationStage(IlluminationStage stage);

        /**
         * @fn  ShadingMode Pass::getShadingMode() const;
         * @brief   Gets shading mode
         * @return  The shading mode.
         */
        ShadingMode getShadingMode() const;

        /**
         * @fn  void Pass::setShadingMode(ShadingMode mode);
         * @brief   Sets shading mode
         * @param   mode    The mode.
         */
        void setShadingMode(ShadingMode mode);

        /**
         * @fn  PolygonMode Pass::getPolygonMode() const;
         * @brief   Gets polygon mode
         * @return  The polygon mode.
         */
        PolygonMode getPolygonMode() const;

        /**
         * @fn  void Pass::setPolygonMode(PolygonMode mode);
         * @brief   Sets polygon mode
         * @param   mode    The mode.
         */
        void setPolygonMode(PolygonMode mode);

        /**
         * @fn  bool Pass::isFogOverrideable() const;
         * @brief   Query if this object is fog overrideable
         * @return  True if fog overrideable, false if not.
         */
        bool isFogOverrideable() const;

        /**
         * @fn  FogMode Pass::getFogMode() const;
         * @brief   Gets fog mode
         * @return  The fog mode.
         */
        FogMode getFogMode() const;

        /**
         * @fn  const ColorRGBA Pass::&getFogColor() const;
         * @brief   Gets fog color
         * @return  The fog color.
         */
        const ColorRGBA &getFogColor() const;

        /**
         * @fn  Real Pass::getFogStart() const;
         * @brief   Gets fog start
         * @return  The fog start.
         */
        Real getFogStart() const;

        /**
         * @fn  Real Pass::getFogEnd() const;
         * @brief   Gets fog end
         * @return  The fog end.
         */
        Real getFogEnd() const;

        /**
         * @fn  Real Pass::getFogDensity() const;
         * @brief   Gets fog density
         * @return  The fog density.
         */
        Real getFogDensity() const;

        /**
         * @fn  void Pass::setFog(bool overrideable, 
         *      FogMode mode = FogMode::NONE, 
         *      const ColorRGBA &color = ColorRGBA::WHITE, 
         *      Real density = 0.001f, Real linearStart = 0.0f, 
         *      Real linearEnd = 1.0f);
         * @brief   Sets a fog
         * @param   overrideable    True if overrideable.
         * @param   mode            (Optional) The mode.
         * @param   color           (Optional) The color.
         * @param   density         (Optional) The density.
         * @param   linearStart     (Optional) The linear start.
         * @param   linearEnd       (Optional) The linear end.
         */
        void setFog(bool overrideable, FogMode mode = FogMode::NONE, 
            const ColorRGBA &color = ColorRGBA::WHITE, Real density = 0.001f, 
            Real linearStart = 0.0f, Real linearEnd = 1.0f);

        /**
         * @fn  uint16_t Pass::getStartLight() const;
         * @brief   Gets start light
         * @return  The start light.
         */
        uint16_t getStartLight() const;

        /**
         * @fn  void Pass::setStartLight(uint16_t startLight);
         * @brief   Sets start light
         * @param   startLight  The start light.
         */
        void setStartLight(uint16_t startLight);

        /**
         * @fn  uint16_t Pass::getMaxLights() const;
         * @brief   Gets maximum lights
         * @return  The maximum lights.
         */
        uint16_t getMaxLights() const;

        /**
         * @fn  void Pass::setMaxLights(uint16_t lights);
         * @brief   Sets maximum lights
         * @param   lights  The lights.
         */
        void setMaxLights(uint16_t lights);

        void setPassIterationCount(size_t count);

        size_t getPassIterationCount() const;

        /**
         * @fn  uint16_t Pass::getLightCountPerIteration() const;
         * @brief   Gets light count per iteration
         * @return  The light count per iteration.
         */
        uint16_t getLightCountPerIteration() const;

        /**
         * @fn  void Pass::setLightCountPerIteration(uint16_t val);
         * @brief   Sets light count per iteration
         * @param   val The value.
         */
        void setLightCountPerIteration(uint16_t val);

        /**
         * @fn  LightType Pass::getOnlyLightType() const;
         * @brief   Gets only light type
         * @return  The only light type.
         */
        LightType getOnlyLightType() const;

        /**
         * @fn  bool Pass::isIteratePerLight() const;
         * @brief   Query if this object is iterate per light
         * @return  True if iterate per light, false if not.
         */
        bool isIteratePerLight() const;

        /**
         * @fn  bool Pass::isRunOnlyForOneLightType() const;
         * @brief   Query if this object is run only for one light type
         * @return  True if run only for one light type, false if not.
         */
        bool isRunOnlyForOneLightType() const;

        /**
         * @fn  void Pass::setIteratePerLight(bool enabled, 
         *      bool onlyForOneLightType = true, 
         *      LightType lightType = LightType::POINT);
         * @brief   Sets iterate per light
         * @param   enabled             True to enable, false to disable.
         * @param   onlyForOneLightType (Optional) True to only for one light type.
         * @param   lightType           (Optional) Type of the light.
         */
        void setIteratePerLight(bool enabled, bool onlyForOneLightType = true,
            LightType lightType = LightType::POINT);

        /**
         * @fn  bool Pass::isPointSpritesEnabled() const;
         * @brief   Queries if the point sprites is enabled
         * @return  True if the point sprites is enabled, false if not.
         */
        bool isPointSpritesEnabled() const;

        /**
         * @fn  void Pass::setPointSpritesEnabled(bool enabled);
         * @brief   Sets point sprites enabled
         * @param   enabled True to enable, false to disable.
         */
        void setPointSpritesEnabled(bool enabled);

        /**
         * @fn  Real Pass::getPointSize() const;
         * @brief   Gets point size
         * @return  The point size.
         */
        Real getPointSize() const;

        /**
         * @fn  void Pass::setPointSize(Real val);
         * @brief   Sets point size
         * @param   val The value.
         */
        void setPointSize(Real val);

        /**
         * @fn  bool Pass::isPointAttenuationEnabled() const;
         * @brief   Queries if the point attenuation is enabled
         * @return  True if the point attenuation is enabled, false if not.
         */
        bool isPointAttenuationEnabled() const;

        /**
         * @fn  Real Pass::getPointAttenuationConstant() const;
         * @brief   Gets point attenuation constant
         * @return  The point attenuation constant.
         */
        Real getPointAttenuationConstant() const;

        /**
         * @fn  Real Pass::getPointAttenuationLinear() const;
         * @brief   Gets point attenuation linear
         * @return  The point attenuation linear.
         */
        Real getPointAttenuationLinear() const;

        /**
         * @fn  Real Pass::getPointAttenuationQuadratic() const;
         * @brief   Gets point attenuation quadratic
         * @return  The point attenuation quadratic.
         */
        Real getPointAttenuationQuadratic() const;

        /**
         * @fn  void Pass::setPointAttenuation(bool enabled, 
         *      Real constant = 0.0f, Real linear = 1.0f, 
         *      Real quadratic = 0.0f);
         * @brief   Sets point attenuation
         * @param   enabled     True to enable, false to disable.
         * @param   constant    (Optional) The constant.
         * @param   linear      (Optional) The linear.
         * @param   quadratic   (Optional) The quadratic.
         */
        void setPointAttenuation(bool enabled, Real constant = 0.0f, 
            Real linear = 1.0f, Real quadratic = 0.0f);

        /**
         * @fn  Real Pass::getPointMinSize() const;
         * @brief   Gets point minimum size
         * @return  The point minimum size.
         */
        Real getPointMinSize() const;

        /**
         * @fn  void Pass::setPointMinSize(Real val);
         * @brief   Sets point minimum size
         * @param   val The value.
         */
        void setPointMinSize(Real val);

        /**
         * @fn  Real Pass::getPointMaxSize() const;
         * @brief   Gets point maximum size
         * @return  The point maximum size.
         */
        Real getPointMaxSize() const;

        /**
         * @fn  void Pass::setPointMaxSize(Real val);
         * @brief   Sets point maximum size
         * @param   val The value.
         */
        void setPointMaxSize(Real val);

    protected:
        /**
         * @fn  Pass::Pass(const String &name, Technique *tech);
         * @brief   构造函数
         * @param [in]  name    The name.
         * @param [in]  tech    If non-null, the technology.
         */
        Pass(const String &name, Technique *tech);

        /**
         * @fn  void Pass::getBlendFlags(BlendType type, BlendFactor &source, 
         *      BlendFactor &dest);
         * @brief   Gets blend flags
         * @param           type    The type.
         * @param [in,out]  source  Source for the.
         * @param [in,out]  dest    Destination for the.
         */
        void getBlendFlags(BlendType type, BlendFactor &source, 
            BlendFactor &dest);

    protected:
        GPUProgramPtr   mGPUProgram;    /**< 绑定到当前 Pass 的 GPU 程序对象 */
        GPUConstBuffers mConstBuffers;  /**< 常量缓冲区对象集合 */
        TextureUnits    mTextureUnits;  /**< TextureUnit 对象集合 */

        Technique   *mParent;   /**< 擁有該 Pass 對象的 Technique 對象 */
        String      mName;      /**< Pass 名稱 */

        //---------------------------------------
        // Command : ambient
        // Usage : ambient <red> <green> <blue> [<alpha>]|vertexColor
        // Parameters : vertexColor 存储在 mTracking
        ColorRGBA   mAmbient;

        //---------------------------------------
        // Command : diffuse
        // Usage : diffuse <red> <green> <blue> [<alpha>]|vertexColor
        // Parameters : vertexColor 存储在 mTracking
        ColorRGBA   mDiffuse;

        //---------------------------------------
        // Command : specular
        // Usage : specular <red> <green> <blue> [<alpha>]|vertexColor <shininess>
        // Parameters : vertexColor 存储在 mTracking
        ColorRGBA   mSpecular;
        Real        mShininess;

        //---------------------------------------
        // Command : emissive
        // Usage : emissive <red> <green> <blue> [<alpha>]|vertexColor
        // Parameters : vertexColor 存储在 mTracking
        ColorRGBA   mEmissive;

        TrackVertexColorType    mTracking;

        //---------------------------------------
        // Command : scene_blend
        // Usage : 
        //  #1 scene_blend <add|modulate|alpha_blend|color_blend>
        //  #2 scene_blend <src_factor> <dest_factor>
        // Parameters : 区分scene_blend和separate_scene_blend，存储在 mSeparateBlend
//         BlendFactor mSrcBlendFactor;
//         BlendFactor mDstBlendFactor;

        //---------------------------------------
        // Command : separate_scene_blend
        // Usage :
        //  #1 separate_scene_blend add modulate
        //  #2 separate_scene_blend <color_src_factor> <color_dest_factor> <alpha_src_factor> <alpha_dest_factor>
        // Parameters : 
        //  #1 color_src_factor 存储在 mSrcBlendFactor
        //  #2 color_dest_factor 存储在 mDstBlendFactor
        //  #3 区分scene_blend和separate_scene_blend，存储在 mSeparateBlend
//         BlendFactor mSrcBlendFactorAlpha;
//         BlendFactor mDstBlendFactorAlpha;

        //---------------------------------------
        // Command : scene_blend_op
        // Usage : scene_blend_op <add|subtract|reverse_subtract|min|max>
        // Parameters : 
        //  #1 区分scene_blend_op和separate_scene_blend_op，存储在 mSeparateBlendOperation
//         BlendOperation  mBlendOperation;

        //---------------------------------------
        // Command : separate_scene_blend_op
        // Usage : separate_scene_blend_op <colorOp> <alphaOp>
        // Parameters : 
        //  #1 colorOp 存储在 mBlendOperation
        //  #2 区分scene_blend和separate_scene_blend，存储在 mSeparateBlend
//         BlendOperation  mAlphaBlendOperation;

//         bool    mSeparateBlend;
//         bool    mSeparateBlendOperation;

        BlendMode  mBlendState;

        //---------------------------------------
        // Command : depth_check
        // Usage : depth_check <on|off>
        bool    mDepthCheck;

        //---------------------------------------
        // Command : depth_write
        // Usage : depth_write <on|off>
        bool    mDepthWrite;
        
        //---------------------------------------
        // Command : depth_func
        // Usage : depth_func <always_fail|always_pass|less|less_equal|equal|not_equal|greater_equal|greater>
        CompareFunction mDepthFunc;

        //---------------------------------------
        // Command : depth_bias
        // Usage : depth_bias <constant_bias> [<slopescale_bias>]
        Real   mDepthBiasConstant;
        Real   mDepthBiasSlopeScale;

        //---------------------------------------
        // Command : iteration_depth_bias
        // Usage : iteration_depth_bias <bias_per_iteration>
        Real   mDepthBiasPerIteration;

        //---------------------------------------
        // Command : alpha_rejection
        // Usage : alpha_rejection <function> <value>
        // Parameters : 
        //  #1 <function> 跟 depth_func的参数相同类型
        CompareFunction mAlphaRejectFunc;
        uint8_t         mAlphaRejectVal;

        //---------------------------------------
        // Command : alpha_to_coverage
        // Usage : alpha_to_coverage <on|off>
        bool            mAlpha2CoverageEnabled; /**< 是否开启A2C */

        //---------------------------------------
        // Command : light_scissor
        // Usage : light_scissor <on|off>
        bool    mLightScissoring;  /**< 是否开启光照裁剪 */

        //---------------------------------------
        // Command : light_clip_planes
        // Usage : light_clip_planes <on|off>
        bool    mLightClipPlanes;   /**< 是否开启光照裁剪平面 */

        //---------------------------------------
        // Command : lighting
        // Usage : lighting <on|off>
        bool    mLightingEnabled;   /**< 是否打开光照 */

        //---------------------------------------
        // Command : normalize_normals
        // Usage : normalize_normals <on|off>
        bool    mNormalizeNormals;  /**< 是否规范化法向量 */

        //---------------------------------------
        // Command : transparent_sorting
        // Usage : transparent_sorting <on|off|force>
        bool    mTransparentSorting;    /**< 是否半透明纹理排序 */
        bool    mTransparentSortingForced;  /**< 是否强制半透明纹理排序 */

        //---------------------------------------
        // Command : color_write
        // Usage : color_write <on|off>
        // 存储在 mBlendState 中
//         bool    mColorWrite;    /**< 是否写颜色值 */

        //---------------------------------------
        // Command : polygon_mode_overrideable
        // Usage : polygon_mode_overrideable <true|false>
        bool    mPolygonModeOverrideable;   /**< 是否覆盖当前pass的多边形渲染模式 */

        //---------------------------------------
        // Command : cull_hardware
        // Usage : cull_hardware <clockwise|anticlockwise|none>
        CullingMode         mCullMode;  /**< 背面剔除顶点的顺序 */

        //---------------------------------------
        // Command : cull_software
        // Usage : cull_software <back|front|none>
        ManualCullingMode   mManualCullMode;    /**< 软件剔除朝向面 */

        //---------------------------------------
        // Command : illumination_stage
        // Usage illumination_stage <ambient|per_light|decal>
        IlluminationStage   mIlluminationStage; /// 

        //---------------------------------------
        // Command : shading
        // Usage : shading <flat|gouraud|phong>
        ShadingMode           mShadingMode; /**< 着色模式 */

        //---------------------------------------
        // Command : polygon_mode
        // Usage : polygon_mode <solid|wireframe|points>
        PolygonMode         mPolygonMode;   /**< 多边形渲染模式 */

        //---------------------------------------
        // Command : fog_override
        // Usage : fog_override <true|false> [<type> <color> <density> <start> <end>]
        bool        mFogOverride;   /**< 当前pass是否覆盖场景的雾效果设置 */
        FogMode     mFogMode;
        ColorRGBA   mFogColor;
        Real        mFogStart;
        Real        mFogEnd;
        Real        mFogDensity;

        //---------------------------------------
        // Command : start_light
        // Usage : start_light <number>
        uint16_t    mStartLight;

        //---------------------------------------
        // Command : max_lights
        // Usage : max_lights <number>
        uint16_t    mMaxLights;     /**< 当前 pass 最大光数量 */

        //---------------------------------------
        // Command : iteration
        // Usage :
        //  #1 iteration <once|once_per_light> [lightType]
        //  #2 iteration <number> [per_light> [lightType]]
        //  #3 iteration <number> [<per_n_lights> <num_lights> [lightType]]
        size_t                  mPassIterationCount;
        uint16_t                mLightsPerIteration;
        LightType               mOnlyLightType;
        bool                    mIteratePerLight;
        bool                    mRunOnlyForOneLightType;

        //---------------------------------------
        // Command : point_sprites
        // Usage : point_sprites <on|off>
        bool        mPointSpritesEnabled;

        //---------------------------------------
        // Command : point_size
        // Usage : point_size <size>
        Real        mPointSize;

        //---------------------------------------
        // Command : point_size_attenuation
        // Usage : point_size_attenuation <on|off> [constant linear quadratic]
        // Parameters :
        //  #1 constant 存储在 mPointAttenuationCoeffs[0]
        //  #2 linear 存储在 mPointAttenuationCoeffs[1]
        //  #3 quadratic 存储在 mPointAttenuationCoeffs[2]
        bool        mPointAttenuationEnabled;
        Vector3     mPointAttenuationCoeffs;

        //---------------------------------------
        // Command : point_size_min
        // Usage : point_size_min <size>
        Real        mPointMinSize;

        //---------------------------------------
        // Command : point_size_max
        // Usage : point_size_max <size>
        Real        mPointMaxSize;
    };
}


#include "T3DPass.inl"


#endif  /*__T3D_PASS_H__*/
