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


#ifndef __T3D_COMMON_H__
#define __T3D_COMMON_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"


namespace Tiny3D
{
    const String BLANKSTRING;

    enum ComponentOrder : uint32_t
    {
        INVALID = 0,
        TRANSFORM = 0x00000100L,
        CAMERA = TRANSFORM + 1,
        COLLIDER = CAMERA + 1,
        RENDERABLE = COLLIDER + 1,
    };

    /**
    * @enum    BuiltinType
    * @brief   GPU常量緩衝區中可使用的數據類型
    */
    enum class BuiltinType : uint32_t
    {
        NONE = 0,   /**< 未定義 */
        REAL,       /**< 實數型 */
        INT,        /**< 整型 */
        VECTOR4,    /**< 4D向量 */
        MATRIX4x4,  /**< 4x4矩陣 */
        MATRIX4x3,  /**< 4x3矩陣 */
    };

    /**
     * @enum    PixelFormat
     * @brief   Values that represent pixel formats
     */
    enum class PixelFormat : uint32_t
    {
        E_PF_UNKNOWN = 0,
        E_PF_PALETTE8,
        E_PF_R5G6B5,
        E_PF_A1R5G5B5,
        E_PF_A4R4G4B4,
        E_PF_R8G8B8,
        E_PF_B8G8R8,
        E_PF_A8R8G8B8,
        E_PF_B8G8R8A8,
        E_PF_X8R8G8B8,
        E_PF_B8G8R8X8,
    };

    /**
     * @enum    LightType
     * @brief   Values that represent light types
     */
    enum class LightType : uint32_t
    {
        POINT = 0,
        DIRECTIONAL,
        SPOTLIGHT
    };

    /**
     * @enum    CompareFunction
     * @brief   比较函数，用于深度缓冲测试和模板缓冲测试
     */
    enum class CompareFunction : uint32_t
    {
        ALWAYS_FAIL,
        ALWAYS_PASS,
        LESS,
        LESS_EQUAL,
        EQUAL,
        NOT_EQUAL,
        GREATER_EQUAL,
        GREATER
    };

    enum class StencilOp : uint32_t
    {
        KEEP,       /**< 保持现有的模板值 */
        ZERO,       /**< 将模板值置为0 */
        REPLACE,    /**< 将模板值设置为用 HWDepthStencilState::setStencilRef 函数设置的 ref 值*/
        INCR,       /**< 如果模板值不是最大值就将模板值+1 */
        INCR_WRAP,  /**< 与 INCR 一样将模板值+1，如果模板值已经是最大值则设为0 */
        DECR,       /**< 如果模板值不是最小值就将模板值-1 */
        DECR_WRAP,  /**< 与 DECR 一样将模板值-1，如果模板值已经是最小值则设为最大值 */
        INVERT      /**< 把模板值按位取反 */
    };

    /**
     * @typedef uint32_t TrackVertexColorType
     * @brief   Defines an alias representing type of the track vertex color
     */
    typedef uint32_t TrackVertexColorType;

    /**
     * @enum    TrackVertexColor
     * @brief   Values that represent track vertex colors
     */
    enum TrackVertexColor : uint32_t
    {
        NONE     = 0x0,
        AMBIENT  = 0x1,
        DIFFUSE  = 0x2,
        SPECULAR = 0x4,
        EMISSIVE = 0x8
    };

    /**
     * @enum    CullingMode
     * @brief   背面剔除模式
     */
    enum class CullingMode : uint32_t
    {
        NONE = 0,        /**< 不做消隐面剔除 */
        CLOCKWISE,       /**< 按照顶点顺时针顺序的消隐面剔除 */
        ANTICLOCKWISE,   /**< 按照顶点逆时针顺序的消隐面剔除 */
        MAX
    };

    /**
     * @enum    ManualCullingMode
     * @brief   Values that represent manual culling modes
     */
    enum class ManualCullingMode : uint32_t
    {
        NONE,
        BACK,
        FRONT
    };

    /**
     * @enum    ShadingMode
     * @brief   Values that represent shading modes
     */
    enum class ShadingMode : uint32_t
    {
        FLAT,
        GOURAUD,
        PHONG
    };

    /**
     * @brief 多边形渲染模式
     */
    enum class PolygonMode : uint32_t
    {
        NONE,
        POINT,             /**< 顶点模式 */
        WIREFRAME,         /**< 线框模式 */
        SOLID,             /**< 着色模式 */
        MAX
    };

    /**
     * @enum    IlluminationStage
     * @brief   Values that represent illumination stages
     */
    enum class IlluminationStage : uint32_t
    {
        UNKNOWN,
        AMBIENT,
        PER_LIGHT,
        DECAL
    };

    /**
     * @enum    FogMode
     * @brief   Values that represent fog modes
     */
    enum class FogMode : uint32_t
    {
        NONE,
        EXP,
        EXP2,
        LINEAR
    };

    /**
     * @enum    FilterType
     * @brief   Values that represent filter types
     */
    enum class FilterType : uint32_t
    {
        MIN,
        MAG,
        MIP
    };

    /**
     * @enum    FilterOptions
     * @brief   Values that represent filter options
     */
    enum class FilterOptions : uint32_t
    {
        NONE,
        POINT,
        LINEAR,
        ANISOTROPIC
    };

    enum class TexFilterOptions : uint32_t
    {
        NONE,
        BILINEAR,
        TRILINEAR,
        ANISOTROPIC
    };

    /**
     * @enum    TextureAddressMode
     * @brief   Values that represent texture address modes
     */
    enum class TextureAddressMode : uint32_t
    {
        UNKNOWN = 0,
        WRAP,
        MIRROR,
        CLAMP,
        BORDER,
    };

    /**
     * @struct  UVWAddressMode
     * @brief   An uvw address mode.
     */
    struct UVWAddressMode
    {
        TextureAddressMode u, v, w;

        UVWAddressMode()
            : u(TextureAddressMode::CLAMP)
            , v(TextureAddressMode::CLAMP)
            , w(TextureAddressMode::CLAMP)
        {}
    };

    /**
     * @enum    WaveformType
     * @brief   Values that represent waveform types
     */
    enum class WaveformType : uint32_t
    {
        SINE,
        TRIANGLE,
        SQUARE,
        SAWTOOTH,
        INVERSE_SAWTOOTH,
        PWM
    };

    enum class BuiltinConstantType : uint32_t
    {
        NONE = 0,
        /// The current world matrix
        WORLD_MATRIX,
        /// The current world matrix, inverted
        INVERSE_WORLD_MATRIX,
        /** Provides transpose of world matrix.
        Equivalent to RenderMonkey's "WorldTranspose".
        */
        TRANSPOSE_WORLD_MATRIX,
        /// The current world matrix, inverted & transposed
        INVERSE_TRANSPOSE_WORLD_MATRIX,

        /// The current array of world matrices, as a 3x4 matrix, used for blending
        WORLD_MATRIX_ARRAY_3x4,
        /// The current array of world matrices, used for blending
        WORLD_MATRIX_ARRAY,
        /// The current array of world matrices transformed to an array of dual quaternions, represented as a 2x4 matrix
        WORLD_DUALQUATERNION_ARRAY_2x4,
        /// The scale and shear components of the current array of world matrices
        WORLD_SCALE_SHEAR_MATRIX_ARRAY_3x4,

        /// The current view matrix
        VIEW_MATRIX,
        /// The current view matrix, inverted
        INVERSE_VIEW_MATRIX,
        /** Provides transpose of view matrix.
        Equivalent to RenderMonkey's "ViewTranspose".
        */
        TRANSPOSE_VIEW_MATRIX,
        /** Provides inverse transpose of view matrix.
        Equivalent to RenderMonkey's "ViewInverseTranspose".
        */
        INVERSE_TRANSPOSE_VIEW_MATRIX,


        /// The current projection matrix
        PROJECTION_MATRIX,
        /** Provides inverse of projection matrix.
        Equivalent to RenderMonkey's "ProjectionInverse".
        */
        INVERSE_PROJECTION_MATRIX,
        /** Provides transpose of projection matrix.
        Equivalent to RenderMonkey's "ProjectionTranspose".
        */
        TRANSPOSE_PROJECTION_MATRIX,
        /** Provides inverse transpose of projection matrix.
        Equivalent to RenderMonkey's "ProjectionInverseTranspose".
        */
        INVERSE_TRANSPOSE_PROJECTION_MATRIX,


        /// The current view & projection matrices concatenated
        VIEWPROJ_MATRIX,
        /** Provides inverse of concatenated view and projection matrices.
        Equivalent to RenderMonkey's "ViewProjectionInverse".
        */
        INVERSE_VIEWPROJ_MATRIX,
        /** Provides transpose of concatenated view and projection matrices.
        Equivalent to RenderMonkey's "ViewProjectionTranspose".
        */
        TRANSPOSE_VIEWPROJ_MATRIX,
        /** Provides inverse transpose of concatenated view and projection matrices.
        Equivalent to RenderMonkey's "ViewProjectionInverseTranspose".
        */
        INVERSE_TRANSPOSE_VIEWPROJ_MATRIX,


        /// The current world & view matrices concatenated
        WORLDVIEW_MATRIX,
        /// The current world & view matrices concatenated, then inverted
        INVERSE_WORLDVIEW_MATRIX,
        /** Provides transpose of concatenated world and view matrices.
        Equivalent to RenderMonkey's "WorldViewTranspose".
        */
        TRANSPOSE_WORLDVIEW_MATRIX,
        /// The current world & view matrices concatenated, then inverted & transposed
        INVERSE_TRANSPOSE_WORLDVIEW_MATRIX,
        /// view matrices.


        /// The current world, view & projection matrices concatenated
        WORLDVIEWPROJ_MATRIX,
        /** Provides inverse of concatenated world, view and projection matrices.
        Equivalent to RenderMonkey's "WorldViewProjectionInverse".
        */
        INVERSE_WORLDVIEWPROJ_MATRIX,
        /** Provides transpose of concatenated world, view and projection matrices.
        Equivalent to RenderMonkey's "WorldViewProjectionTranspose".
        */
        TRANSPOSE_WORLDVIEWPROJ_MATRIX,
        /** Provides inverse transpose of concatenated world, view and projection
        matrices. Equivalent to RenderMonkey's "WorldViewProjectionInverseTranspose".
        */
        INVERSE_TRANSPOSE_WORLDVIEWPROJ_MATRIX,


        /// render target related values
        /** -1 if requires texture flipping, +1 otherwise. It's useful when you bypassed
        projection matrix transform, still able use this value to adjust transformed y position.
        */
        RENDER_TARGET_FLIPPING,

        /** -1 if the winding has been inverted (e.g. for reflections), +1 otherwise.
        */
        VERTEX_WINDING,

        /// Fog colour
        FOG_COLOUR,
        /// Fog params: density, linear start, linear end, 1/(end-start)
        FOG_PARAMS,


        /// Surface ambient colour, as set in Pass::setAmbient
        SURFACE_AMBIENT_COLOUR,
        /// Surface diffuse colour, as set in Pass::setDiffuse
        SURFACE_DIFFUSE_COLOUR,
        /// Surface specular colour, as set in Pass::setSpecular
        SURFACE_SPECULAR_COLOUR,
        /// Surface emissive colour, as set in Pass::setSelfIllumination
        SURFACE_EMISSIVE_COLOUR,
        /// Surface shininess, as set in Pass::setShininess
        SURFACE_SHININESS,
        /// Surface alpha rejection value, not as set in Pass::setAlphaRejectionValue, but a floating number between 0.0f and 1.0f instead (255.0f / Pass::getAlphaRejectionValue())
        SURFACE_ALPHA_REJECTION_VALUE,


        /// The number of active light sources (better than gl_MaxLights)
        LIGHT_COUNT,


        /// The ambient light colour set in the scene
        AMBIENT_LIGHT_COLOUR,

        /// Light diffuse colour (index determined by setAutoConstant call)
        LIGHT_DIFFUSE_COLOUR,
        /// Light specular colour (index determined by setAutoConstant call)
        LIGHT_SPECULAR_COLOUR,
        /// Light attenuation parameters, Vector4(range, constant, linear, quadric)
        LIGHT_ATTENUATION,
        /** Spotlight parameters, Vector4(innerFactor, outerFactor, falloff, isSpot)
        innerFactor and outerFactor are cos(angle/2)
        The isSpot parameter is 0.0f for non-spotlights, 1.0f for spotlights.
        Also for non-spotlights the inner and outer factors are 1 and nearly 1 respectively
        */
        SPOTLIGHT_PARAMS,
        /// A light position in world space (index determined by setAutoConstant call)
        LIGHT_POSITION,
        /// A light position in object space (index determined by setAutoConstant call)
        LIGHT_POSITION_OBJECT_SPACE,
        /// A light position in view space (index determined by setAutoConstant call)
        LIGHT_POSITION_VIEW_SPACE,
        /// A light direction in world space (index determined by setAutoConstant call)
        LIGHT_DIRECTION,
        /// A light direction in object space (index determined by setAutoConstant call)
        LIGHT_DIRECTION_OBJECT_SPACE,
        /// A light direction in view space (index determined by setAutoConstant call)
        LIGHT_DIRECTION_VIEW_SPACE,
        /** The distance of the light from the center of the object
        a useful approximation as an alternative to per-vertex distance
        calculations.
        */
        LIGHT_DISTANCE_OBJECT_SPACE,
        /** Light power level, a single scalar as set in Light::setPowerScale  (index determined by setAutoConstant call) */
        LIGHT_POWER_SCALE,
        /// Light diffuse colour pre-scaled by Light::setPowerScale (index determined by setAutoConstant call)
        LIGHT_DIFFUSE_COLOUR_POWER_SCALED,
        /// Light specular colour pre-scaled by Light::setPowerScale (index determined by setAutoConstant call)
        LIGHT_SPECULAR_COLOUR_POWER_SCALED,
        /// Array of light diffuse colours (count set by extra param)
        LIGHT_DIFFUSE_COLOUR_ARRAY,
        /// Array of light specular colours (count set by extra param)
        LIGHT_SPECULAR_COLOUR_ARRAY,
        /// Array of light diffuse colours scaled by light power (count set by extra param)
        LIGHT_DIFFUSE_COLOUR_POWER_SCALED_ARRAY,
        /// Array of light specular colours scaled by light power (count set by extra param)
        LIGHT_SPECULAR_COLOUR_POWER_SCALED_ARRAY,
        /// Array of light attenuation parameters, Vector4(range, constant, linear, quadric) (count set by extra param)
        LIGHT_ATTENUATION_ARRAY,
        /// Array of light positions in world space (count set by extra param)
        LIGHT_POSITION_ARRAY,
        /// Array of light positions in object space (count set by extra param)
        LIGHT_POSITION_OBJECT_SPACE_ARRAY,
        /// Array of light positions in view space (count set by extra param)
        LIGHT_POSITION_VIEW_SPACE_ARRAY,
        /// Array of light directions in world space (count set by extra param)
        LIGHT_DIRECTION_ARRAY,
        /// Array of light directions in object space (count set by extra param)
        LIGHT_DIRECTION_OBJECT_SPACE_ARRAY,
        /// Array of light directions in view space (count set by extra param)
        LIGHT_DIRECTION_VIEW_SPACE_ARRAY,
        /** Array of distances of the lights from the center of the object
        a useful approximation as an alternative to per-vertex distance
        calculations. (count set by extra param)
        */
        LIGHT_DISTANCE_OBJECT_SPACE_ARRAY,
        /** Array of light power levels, a single scalar as set in Light::setPowerScale
        (count set by extra param)
        */
        LIGHT_POWER_SCALE_ARRAY,
        /** Spotlight parameters array of Vector4(innerFactor, outerFactor, falloff, isSpot)
        innerFactor and outerFactor are cos(angle/2)
        The isSpot parameter is 0.0f for non-spotlights, 1.0f for spotlights.
        Also for non-spotlights the inner and outer factors are 1 and nearly 1 respectively.
        (count set by extra param)
        */
        SPOTLIGHT_PARAMS_ARRAY,

        /** The derived ambient light colour, with 'r', 'g', 'b' components filled with
        product of surface ambient colour and ambient light colour, respectively,
        and 'a' component filled with surface ambient alpha component.
        */
        DERIVED_AMBIENT_LIGHT_COLOUR,
        /** The derived scene colour, with 'r', 'g' and 'b' components filled with sum
        of derived ambient light colour and surface emissive colour, respectively,
        and 'a' component filled with surface diffuse alpha component.
        */
        DERIVED_SCENE_COLOUR,

        /** The derived light diffuse colour (index determined by setAutoConstant call),
        with 'r', 'g' and 'b' components filled with product of surface diffuse colour,
        light power scale and light diffuse colour, respectively, and 'a' component filled with surface
        diffuse alpha component.
        */
        DERIVED_LIGHT_DIFFUSE_COLOUR,
        /** The derived light specular colour (index determined by setAutoConstant call),
        with 'r', 'g' and 'b' components filled with product of surface specular colour
        and light specular colour, respectively, and 'a' component filled with surface
        specular alpha component.
        */
        DERIVED_LIGHT_SPECULAR_COLOUR,

        /// Array of derived light diffuse colours (count set by extra param)
        DERIVED_LIGHT_DIFFUSE_COLOUR_ARRAY,
        /// Array of derived light specular colours (count set by extra param)
        DERIVED_LIGHT_SPECULAR_COLOUR_ARRAY,
        /** The absolute light number of a local light index. Each pass may have
        a number of lights passed to it, and each of these lights will have
        an index in the overall light list, which will differ from the local
        light index due to factors like setStartLight and setIteratePerLight.
        This binding provides the global light index for a local index.
        */
        LIGHT_NUMBER,
        /// Returns (int) 1 if the  given light casts shadows, 0 otherwise (index set in extra param)
        LIGHT_CASTS_SHADOWS,
        /// Returns (int) 1 if the  given light casts shadows, 0 otherwise (index set in extra param)
        LIGHT_CASTS_SHADOWS_ARRAY,


        /** The distance a shadow volume should be extruded when using
        finite extrusion programs.
        */
        SHADOW_EXTRUSION_DISTANCE,
        /// The current camera's position in world space
        CAMERA_POSITION,
        /// The current camera's position in object space 
        CAMERA_POSITION_OBJECT_SPACE,
        /// The view/projection matrix of the assigned texture projection frustum
        TEXTURE_VIEWPROJ_MATRIX,
        /// Array of view/projection matrices of the first n texture projection frustums
        TEXTURE_VIEWPROJ_MATRIX_ARRAY,
        /** The view/projection matrix of the assigned texture projection frustum,
        combined with the current world matrix
        */
        TEXTURE_WORLDVIEWPROJ_MATRIX,
        /// Array of world/view/projection matrices of the first n texture projection frustums
        TEXTURE_WORLDVIEWPROJ_MATRIX_ARRAY,
        /// The view/projection matrix of a given spotlight
        SPOTLIGHT_VIEWPROJ_MATRIX,
        /// Array of view/projection matrix of a given spotlight
        SPOTLIGHT_VIEWPROJ_MATRIX_ARRAY,
        /** The view/projection matrix of a given spotlight projection frustum,
        combined with the current world matrix
        */
        SPOTLIGHT_WORLDVIEWPROJ_MATRIX,
        /** An array of the view/projection matrix of a given spotlight projection frustum,
         combined with the current world matrix
         */
        SPOTLIGHT_WORLDVIEWPROJ_MATRIX_ARRAY,
        /// A custom parameter which will come from the renderable, using 'data' as the identifier
        CUSTOM,
        /** provides current elapsed time
        */
        TIME,
        /** Single float value, which repeats itself based on given as
        parameter "cycle time". Equivalent to RenderMonkey's "Time0_X".
        */
        TIME_0_X,
        /// Cosine of "Time0_X". Equivalent to RenderMonkey's "CosTime0_X".
        COSTIME_0_X,
        /// Sine of "Time0_X". Equivalent to RenderMonkey's "SinTime0_X".
        SINTIME_0_X,
        /// Tangent of "Time0_X". Equivalent to RenderMonkey's "TanTime0_X".
        TANTIME_0_X,
        /** Vector of "Time0_X", "SinTime0_X", "CosTime0_X",
        "TanTime0_X". Equivalent to RenderMonkey's "Time0_X_Packed".
        */
        TIME_0_X_PACKED,
        /** Single float value, which represents scaled time value [0..1],
        which repeats itself based on given as parameter "cycle time".
        Equivalent to RenderMonkey's "Time0_1".
        */
        TIME_0_1,
        /// Cosine of "Time0_1". Equivalent to RenderMonkey's "CosTime0_1".
        COSTIME_0_1,
        /// Sine of "Time0_1". Equivalent to RenderMonkey's "SinTime0_1".
        SINTIME_0_1,
        /// Tangent of "Time0_1". Equivalent to RenderMonkey's "TanTime0_1".
        TANTIME_0_1,
        /** Vector of "Time0_1", "SinTime0_1", "CosTime0_1",
        "TanTime0_1". Equivalent to RenderMonkey's "Time0_1_Packed".
        */
        TIME_0_1_PACKED,
        /**	Single float value, which represents scaled time value [0..2*Pi],
        which repeats itself based on given as parameter "cycle time".
        Equivalent to RenderMonkey's "Time0_2PI".
        */
        TIME_0_2PI,
        /// Cosine of "Time0_2PI". Equivalent to RenderMonkey's "CosTime0_2PI".
        COSTIME_0_2PI,
        /// Sine of "Time0_2PI". Equivalent to RenderMonkey's "SinTime0_2PI".
        SINTIME_0_2PI,
        /// Tangent of "Time0_2PI". Equivalent to RenderMonkey's "TanTime0_2PI".
        TANTIME_0_2PI,
        /** Vector of "Time0_2PI", "SinTime0_2PI", "CosTime0_2PI",
        "TanTime0_2PI". Equivalent to RenderMonkey's "Time0_2PI_Packed".
        */
        TIME_0_2PI_PACKED,
        /// provides the scaled frame time, returned as a floating point value.
        FRAME_TIME,
        /// provides the calculated frames per second, returned as a floating point value.
        FPS,
        /// viewport-related values
        /** Current viewport width (in pixels) as floating point value.
        Equivalent to RenderMonkey's "ViewportWidth".
        */
        VIEWPORT_WIDTH,
        /** Current viewport height (in pixels) as floating point value.
        Equivalent to RenderMonkey's "ViewportHeight".
        */
        VIEWPORT_HEIGHT,
        /** This variable represents 1.0/ViewportWidth.
        Equivalent to RenderMonkey's "ViewportWidthInverse".
        */
        INVERSE_VIEWPORT_WIDTH,
        /** This variable represents 1.0/ViewportHeight.
        Equivalent to RenderMonkey's "ViewportHeightInverse".
        */
        INVERSE_VIEWPORT_HEIGHT,
        /** Packed of "ViewportWidth", "ViewportHeight", "ViewportWidthInverse",
        "ViewportHeightInverse".
        */
        VIEWPORT_SIZE,

        /// view parameters
        /** This variable provides the view direction vector (world space).
        Equivalent to RenderMonkey's "ViewDirection".
        */
        VIEW_DIRECTION,
        /** This variable provides the view side vector (world space).
        Equivalent to RenderMonkey's "ViewSideVector".
        */
        VIEW_SIDE_VECTOR,
        /** This variable provides the view up vector (world space).
        Equivalent to RenderMonkey's "ViewUpVector".
        */
        VIEW_UP_VECTOR,
        /** This variable provides the field of view as a floating point value.
        Equivalent to RenderMonkey's "FOV".
        */
        FOV,
        /**	This variable provides the near clip distance as a floating point value.
        Equivalent to RenderMonkey's "NearClipPlane".
        */
        NEAR_CLIP_DISTANCE,
        /**	This variable provides the far clip distance as a floating point value.
        Equivalent to RenderMonkey's "FarClipPlane".
        */
        FAR_CLIP_DISTANCE,

        /** provides the pass index number within the technique
        of the active materil.
        */
        PASS_NUMBER,

        /** provides the current iteration number of the pass. The iteration
        number is the number of times the current render operation has
        been drawn for the active pass.
        */
        PASS_ITERATION_NUMBER,


        /** Provides a parametric animation value [0..1], only available
        where the renderable specifically implements it.
        */
        ANIMATION_PARAMETRIC,

        /** Provides the texel offsets required by this rendersystem to map
        texels to pixels. Packed as
        float4(absoluteHorizontalOffset, absoluteVerticalOffset,
        horizontalOffset / viewportWidth, verticalOffset / viewportHeight)
        */
        TEXEL_OFFSETS,

        /** Provides information about the depth range of the scene as viewed
        from the current camera.
        Passed as float4(minDepth, maxDepth, depthRange, 1 / depthRange)
        */
        SCENE_DEPTH_RANGE,

        /** Provides information about the depth range of the scene as viewed
        from a given shadow camera. Requires an index parameter which maps
        to a light index relative to the current light list.
        Passed as float4(minDepth, maxDepth, depthRange, 1 / depthRange)
        */
        SHADOW_SCENE_DEPTH_RANGE,

        /** Provides an array of information about the depth range of the scene as viewed
         from a given shadow camera. Requires an index parameter which maps
         to a light index relative to the current light list.
         Passed as float4(minDepth, maxDepth, depthRange, 1 / depthRange)
        */
        SHADOW_SCENE_DEPTH_RANGE_ARRAY,

        /** Provides the fixed shadow colour as configured via SceneManager::setShadowColour;
        useful for integrated modulative shadows.
        */
        SHADOW_COLOUR,
        /** Provides texture size of the texture unit (index determined by setAutoConstant
        call). Packed as float4(width, height, depth, 1)
        */
        TEXTURE_SIZE,
        /** Provides inverse texture size of the texture unit (index determined by setAutoConstant
        call). Packed as float4(1 / width, 1 / height, 1 / depth, 1)
        */
        INVERSE_TEXTURE_SIZE,
        /** Provides packed texture size of the texture unit (index determined by setAutoConstant
        call). Packed as float4(width, height, 1 / width, 1 / height)
        */
        PACKED_TEXTURE_SIZE,

        /** Provides the current transform matrix of the texture unit (index determined by setAutoConstant
        call), as seen by the fixed-function pipeline.
        */
        TEXTURE_MATRIX,

        /** Provides the position of the LOD camera in world space, allowing you
        to perform separate LOD calculations in shaders independent of the rendering
        camera. If there is no separate LOD camera then this is the real camera
        position. See Camera::setLodCamera.
        */
        LOD_CAMERA_POSITION,
        /** Provides the position of the LOD camera in object space, allowing you
        to perform separate LOD calculations in shaders independent of the rendering
        camera. If there is no separate LOD camera then this is the real camera
        position. See Camera::setLodCamera.
        */
        LOD_CAMERA_POSITION_OBJECT_SPACE,
        /** Binds custom per-light constants to the shaders. */
        LIGHT_CUSTOM,

        UNKNOWN = 999
    };

    struct BuiltinConstantDefinition
    {
        uint8_t             elementCount;
        BuiltinType         elementType;
        BuiltinType         extraType;

        BuiltinConstantDefinition()
            : elementCount(0)
            , elementType(BuiltinType::NONE)
            , extraType(BuiltinType::NONE)
        {}

        BuiltinConstantDefinition(uint8_t c, BuiltinType elementT, BuiltinType extraT)
            : elementCount(c)
            , elementType(elementT)
            , extraType(extraT)
        {}

        BuiltinConstantDefinition(const BuiltinConstantDefinition &other)
            : elementCount(other.elementCount)
            , elementType(other.elementType)
            , extraType(other.extraType)
        {}

        BuiltinConstantDefinition &operator =(const BuiltinConstantDefinition &other)
        {
            elementCount = other.elementCount;
            elementType = other.elementType;
            extraType = other.extraType;
            return *this;
        }
    };


    typedef TMap<BuiltinConstantType, BuiltinConstantDefinition>    BuiltinConstantMap;
    typedef BuiltinConstantMap::iterator        BuiltinConstantMapItr;
    typedef BuiltinConstantMap::const_iterator  BuiltinConstantMapConstItr;
    typedef BuiltinConstantMap::value_type      BuiltinConstantMapValue;


    /**
     * @enum    FileSubType
     * @brief   Values that represent file sub types
     */
    //enum FileSubType : uint32_t
    //{
    //    E_FST_SCRIPT = 0x00000001,
    //};

    #define T3D_FILE_MAGIC                   "T3D"

    #define T3D_FILE_SCC_VERSION_00000100   0x00000100
    #define T3D_FILE_SCC_VERSION            T3D_FILE_SCC_VERSION_00000100

    #define T3D_FILE_MDL_VERSION_00000100   0x00000100
    #define T3D_FILE_MDL_VERSION            T3D_FILE_MDL_VERSION_00000100

    #define T3D_FILE_SUBTYPE_SCC            0x00000001
    #define T3D_FILE_SUBTYPE_MDL            0x00000002
    #define T3D_FILE_SUBTYPE_SCN            0x00000003

    /**
     * @struct  T3DFileHeader
     * @brief   A 3D file header.
     */
    struct T3DFileHeader
    {
        char        magic[4];   /**< 文件魔数，用于标识文件 */
        uint32_t    subtype;    /**< The subtype */
        uint32_t    version;    /**< 文件版本号 */
        uint32_t    filesize;   /**< 文件大小 */
    };
}


#endif  /*__T3D_COMMON_H__*/
