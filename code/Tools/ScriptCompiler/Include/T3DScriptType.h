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

#ifndef __T3D_SCRIPT_TYPE_H__
#define __T3D_SCRIPT_TYPE_H__


#include "T3DScriptPrerequisites.h"


namespace Tiny3D
{
    #define LOG_TAG                 "Compiler"
    #define CURRENT_VERSION_STR     "0.1.0"

    /**
     * @brief 符号ID
     */
    enum
    {
        TID_LBRACE = 0,     /// {
        TID_RBRACE,         /// }
        TID_COLON,          /// :
        TID_VARIABLE,       /// $...
        TID_WORD,           /// *
        TID_QUOTE,          /// "*"
        TID_NEWLINE,        /// \n
        TID_UNKNOWN,        ///
        TID_END
    };

    /**
     * @brief 符号结构
     */
    struct Token
    {
        String      lexeme; /// 符号的词素
        String      file;   /// 当前文件名
        uint32_t    type;   /// 符号对应的ID
        uint32_t    line;   /// 当前行号
    };

    typedef std::shared_ptr<Token>      TokenPtr;
    typedef std::vector<TokenPtr>       TokenList;
    typedef std::shared_ptr<TokenList>  TokenListPtr;

    /**
     * @brief 结点类型
     */
    enum ConcreteNodeType
    {
        CNT_VARIABLE,           /// 变量 $xxx
        CNT_VARIABLE_ASSIGN,    /// 变量赋值，set $xxx
        CNT_WORD,               /// *
        CNT_IMPORT,             /// import * from *
        CNT_QUOTE,              /// "*"
        CNT_LBRACE,             /// {
        CNT_RBRACE,             /// }
        CNT_COLON               /// :
    };

    struct ConcreteNode;

    typedef std::shared_ptr<ConcreteNode>       ConcreteNodePtr;
    typedef std::list<ConcreteNodePtr>          ConcreteNodeList;
    typedef std::shared_ptr<ConcreteNodeList>   ConcreteNodeListPtr;

    /**
     * @brief 语法树结点
     */
    struct ConcreteNode
    {
        String              token;      /// 符号名称
        String              file;       /// 脚本文件名
        uint32_t            line;       /// 当前符号行号
        ConcreteNodeType    type;       /// 结点类型
        ConcreteNodeList    children;   /// 子结点
        ConcreteNode        *parent;    /// 父结点
    };

    /**
     * @brief 操作码
     */
    enum OpCode
    {
        ID_MATERIAL = 3,
        ID_VERTEX_PROGRAM,
        ID_GEOMETRY_PROGRAM,
        ID_FRAGMENT_PROGRAM,
        ID_TECHNIQUE,
        ID_PASS,
        ID_TEXTURE_UNIT,
        ID_VERTEX_PROGRAM_REF,
        ID_GEOMETRY_PROGRAM_REF,
        ID_FRAGMENT_PROGRAM_REF,
        ID_SHADOW_CASTER_VERTEX_PROGRAM_REF,
        ID_SHADOW_CASTER_FRAGMENT_PROGRAM_REF,
        ID_SHADOW_RECEIVER_VERTEX_PROGRAM_REF,
        ID_SHADOW_RECEIVER_FRAGMENT_PROGRAM_REF,
        ID_SHADOW_CASTER_MATERIAL,
        ID_SHADOW_RECEIVER_MATERIAL,

        ID_LOD_VALUES,
        ID_LOD_STRATEGY,
        ID_LOD_DISTANCES,
        ID_RECEIVE_SHADOWS,
        ID_TRANSPARENCY_CASTS_SHADOWS,
        ID_SET_TEXTURE_ALIAS,

        ID_SOURCE,
        ID_ENTRY_POINT,
        ID_STAGE,
        ID_SYNTAX,
        ID_DEFAULT_PARAMS,
        ID_PARAM_INDEXED,
        ID_PARAM_NAMED,
        ID_PARAM_INDEXED_AUTO,
        ID_PARAM_NAMED_AUTO,

        ID_SCHEME,
        ID_LOD_INDEX,
        ID_GPU_VENDOR_RULE,
        ID_GPU_DEVICE_RULE,
        ID_INCLUDE,
        ID_EXCLUDE,

        ID_AMBIENT,
        ID_DIFFUSE,
        ID_SPECULAR,
        ID_EMISSIVE,
        ID_VERTEXCOLOUR,
        ID_SCENE_BLEND,
        ID_COLOUR_BLEND,
        ID_ONE,
        ID_ZERO,
        ID_DEST_COLOUR,
        ID_SRC_COLOUR,
        ID_ONE_MINUS_DEST_COLOUR,
        ID_ONE_MINUS_SRC_COLOUR,
        ID_DEST_ALPHA,
        ID_SRC_ALPHA,
        ID_ONE_MINUS_DEST_ALPHA,
        ID_ONE_MINUS_SRC_ALPHA,
        ID_SEPARATE_SCENE_BLEND,
        ID_SCENE_BLEND_OP,
        ID_REVERSE_SUBTRACT,
        ID_MIN,
        ID_MAX,
        ID_SEPARATE_SCENE_BLEND_OP,
        ID_DEPTH_CHECK,
        ID_DEPTH_WRITE,
        ID_DEPTH_FUNC,
        ID_DEPTH_BIAS,
        ID_ITERATION_DEPTH_BIAS,
        ID_ALWAYS_FAIL,
        ID_ALWAYS_PASS,
        ID_LESS_EQUAL,
        ID_LESS,
        ID_EQUAL,
        ID_NOT_EQUAL,
        ID_GREATER_EQUAL,
        ID_GREATER,
        ID_ALPHA_REJECTION,
        ID_ALPHA_TO_COVERAGE,
        ID_LIGHT_SCISSOR,
        ID_LIGHT_CLIP_PLANES,
        ID_TRANSPARENT_SORTING,
        ID_ILLUMINATION_STAGE,
        ID_DECAL,
        ID_CULL_HARDWARE,
        ID_CLOCKWISE,
        ID_ANTICLOCKWISE,
        ID_CULL_SOFTWARE,
        ID_BACK,
        ID_FRONT,
        ID_NORMALISE_NORMALS,
        ID_LIGHTING,
        ID_SHADING,
        ID_FLAT,
        ID_GOURAUD,
        ID_PHONG,
        ID_POLYGON_MODE,
        ID_SOLID,
        ID_WIREFRAME,
        ID_POINTS,
        ID_POLYGON_MODE_OVERRIDEABLE,
        ID_FOG_OVERRIDE,
        ID_NONE,
        ID_LINEAR,
        ID_EXP,
        ID_EXP2,
        ID_COLOUR_WRITE,
        ID_MAX_LIGHTS,
        ID_START_LIGHT,
        ID_ITERATION,
        ID_ONCE,
        ID_ONCE_PER_LIGHT,
        ID_PER_LIGHT,
        ID_PER_N_LIGHTS,
        ID_POINT,
        ID_SPOT,
        ID_DIRECTIONAL,
        ID_LIGHT_MASK,
        ID_POINT_SIZE,
        ID_POINT_SPRITES,
        ID_POINT_SIZE_ATTENUATION,
        ID_POINT_SIZE_MIN,
        ID_POINT_SIZE_MAX,

        ID_TEXTURE_ALIAS,
        ID_TEXTURE,
        ID_1D,
        ID_2D,
        ID_3D,
        ID_CUBIC,
        ID_2DARRAY,
        ID_UNLIMITED,
        ID_ALPHA,
        ID_GAMMA,
        ID_PIXELFORMAT,
        ID_ANIM_TEXTURE,
        ID_CUBIC_TEXTURE,
        ID_SEPARATE_UV,
        ID_COMBINED_UVW,
        ID_TEX_COORD_SET,
        ID_TEX_ADDRESS_MODE,
        ID_WRAP,
        ID_CLAMP,
        ID_BORDER,
        ID_MIRROR,
        ID_TEX_BORDER_COLOUR,
        ID_FILTERING,
        ID_BILINEAR,
        ID_TRILINEAR,
        ID_ANISOTROPIC,
        ID_CMPTEST,
//         ID_ON,
//         ID_OFF,
        ID_CMPFUNC,
        ID_MAX_ANISOTROPY,
        ID_MIPMAP_BIAS,
        ID_COLOUR_OP,
        ID_REPLACE,
        ID_ADD,
        ID_MODULATE,
        ID_ALPHA_BLEND,
        ID_COLOUR_OP_EX,
        ID_SOURCE1,
        ID_SOURCE2,
        ID_MODULATE_X2,
        ID_MODULATE_X4,
        ID_ADD_SIGNED,
        ID_ADD_SMOOTH,
        ID_SUBTRACT,
        ID_BLEND_DIFFUSE_COLOUR,
        ID_BLEND_DIFFUSE_ALPHA,
        ID_BLEND_TEXTURE_ALPHA,
        ID_BLEND_CURRENT_ALPHA,
        ID_BLEND_MANUAL,
        ID_DOT_PRODUCT,
        ID_SRC_CURRENT,
        ID_SRC_TEXTURE,
        ID_SRC_DIFFUSE,
        ID_SRC_SPECULAR,
        ID_SRC_MANUAL,
        ID_COLOUR_OP_MULTIPASS_FALLBACK,
        ID_ALPHA_OP_EX,
        ID_ENV_MAP,
        ID_SPHERICAL,
        ID_PLANAR,
        ID_CUBIC_REFLECTION,
        ID_CUBIC_NORMAL,
        ID_SCROLL,
        ID_SCROLL_ANIM,
        ID_ROTATE,
        ID_ROTATE_ANIM,
        ID_SCALE,
        ID_WAVE_XFORM,
        ID_SCROLL_X,
        ID_SCROLL_Y,
        ID_SCALE_X,
        ID_SCALE_Y,
        ID_SINE,
        ID_TRIANGLE,
        ID_SQUARE,
        ID_SAWTOOTH,
        ID_INVERSE_SAWTOOTH,
        ID_TRANSFORM,
        ID_BINDING_TYPE,
        ID_VERTEX,
        ID_FRAGMENT,
        ID_CONTENT_TYPE,
        ID_NAMED,
        ID_SHADOW,
        ID_TEXTURE_SOURCE,
        ID_SHARED_PARAMS,
        ID_SHARED_PARAM_NAMED,
        ID_SHARED_PARAMS_REF,

        ID_PARTICLE_SYSTEM,
        ID_EMITTER,
        ID_AFFECTOR,

        ID_COMPOSITOR,
        ID_TARGET,
        ID_TARGET_OUTPUT,

        ID_INPUT,
        ID_PREVIOUS,
        ID_TARGET_WIDTH,
        ID_TARGET_HEIGHT,
        ID_TARGET_WIDTH_SCALED,
        ID_TARGET_HEIGHT_SCALED,
        ID_COMPOSITOR_LOGIC,
        ID_TEXTURE_REF,
        ID_SCOPE_LOCAL,
        ID_SCOPE_CHAIN,
        ID_SCOPE_GLOBAL,
        ID_POOLED,
        //ID_GAMMA, - already registered for material
        ID_NO_FSAA,
        ID_DEPTH_POOL,
        ID_ONLY_INITIAL,
        ID_VISIBILITY_MASK,
        ID_LOD_BIAS,
        ID_MATERIAL_SCHEME,
        ID_SHADOWS_ENABLED,

        ID_CLEAR,
        ID_STENCIL,
        ID_RENDER_SCENE,
        ID_RENDER_QUAD,
        ID_IDENTIFIER,
        ID_FIRST_RENDER_QUEUE,
        ID_LAST_RENDER_QUEUE,
        ID_QUAD_NORMALS,
        ID_CAMERA_FAR_CORNERS_VIEW_SPACE,
        ID_CAMERA_FAR_CORNERS_WORLD_SPACE,

        ID_BUFFERS,
        ID_COLOUR,
        ID_DEPTH,
        ID_COLOUR_VALUE,
        ID_DEPTH_VALUE,
        ID_STENCIL_VALUE,

        ID_CHECK,
        ID_COMP_FUNC,
        ID_REF_VALUE,
        ID_MASK,
        ID_FAIL_OP,
        ID_KEEP,
        ID_INCREMENT,
        ID_DECREMENT,
        ID_INCREMENT_WRAP,
        ID_DECREMENT_WRAP,
        ID_INVERT,
        ID_DEPTH_FAIL_OP,
        ID_PASS_OP,
        ID_TWO_SIDED,
        ID_READ_BACK_AS_TEXTURE,
        // Suport for shader model 5.0
        // More program IDs
        ID_TESSELLATION_HULL_PROGRAM,
        ID_TESSELLATION_DOMAIN_PROGRAM,
        ID_COMPUTE_PROGRAM,
        ID_TESSELLATION_HULL_PROGRAM_REF,
        ID_TESSELLATION_DOMAIN_PROGRAM_REF,
        ID_COMPUTE_PROGRAM_REF,
        // More binding IDs
        ID_GEOMETRY,
        ID_TESSELLATION_HULL,
        ID_TESSELLATION_DOMAIN,
        ID_COMPUTE,

        // Support for subroutine
        ID_SUBROUTINE,

        // added during 1.11. re-sort for 1.12
        ID_LINE_WIDTH,
        ID_SAMPLER,
        ID_SAMPLER_REF,
        ID_THREAD_GROUPS,
        ID_RENDER_CUSTOM,

        ID_GPU_PROGRAM,
        ID_GPU_PROGRAM_REF,

        ID_GPU_CBUFFER,
        ID_GPU_CBUFFER_REF,
        ID_CBUFFER_SLOT,

        ID_RENDER_QUEUE,

        ID_END_BUILTIN_IDS
    };

    enum BuiltinValue
    {
        ID_ON = 1,
        ID_OFF = 2,
        ID_TRUE = 1,
        ID_FALSE = 2,
        ID_YES = 1,
        ID_NO = 2
    };

    enum BuiltinType
    {
        BT_NONE = 0,
        BT_REAL,
        BT_INT,
    };

    enum BuiltinConstantType
    {
        BCT_NONE,
        /// The current world matrix
        BCT_WORLD_MATRIX,
        /// The current world matrix, inverted
        BCT_INVERSE_WORLD_MATRIX,
        /** Provides transpose of world matrix.
        Equivalent to RenderMonkey's "WorldTranspose".
        */
        BCT_TRANSPOSE_WORLD_MATRIX,
        /// The current world matrix, inverted & transposed
        BCT_INVERSE_TRANSPOSE_WORLD_MATRIX,

        /// The current array of world matrices, as a 3x4 matrix, used for blending
        BCT_WORLD_MATRIX_ARRAY_3x4,
        /// The current array of world matrices, used for blending
        BCT_WORLD_MATRIX_ARRAY,
        /// The current array of world matrices transformed to an array of dual quaternions, represented as a 2x4 matrix
        BCT_WORLD_DUALQUATERNION_ARRAY_2x4,
        /// The scale and shear components of the current array of world matrices
        BCT_WORLD_SCALE_SHEAR_MATRIX_ARRAY_3x4,

        /// The current view matrix
        BCT_VIEW_MATRIX,
        /// The current view matrix, inverted
        BCT_INVERSE_VIEW_MATRIX,
        /** Provides transpose of view matrix.
        Equivalent to RenderMonkey's "ViewTranspose".
        */
        BCT_TRANSPOSE_VIEW_MATRIX,
        /** Provides inverse transpose of view matrix.
        Equivalent to RenderMonkey's "ViewInverseTranspose".
        */
        BCT_INVERSE_TRANSPOSE_VIEW_MATRIX,


        /// The current projection matrix
        BCT_PROJECTION_MATRIX,
        /** Provides inverse of projection matrix.
        Equivalent to RenderMonkey's "ProjectionInverse".
        */
        BCT_INVERSE_PROJECTION_MATRIX,
        /** Provides transpose of projection matrix.
        Equivalent to RenderMonkey's "ProjectionTranspose".
        */
        BCT_TRANSPOSE_PROJECTION_MATRIX,
        /** Provides inverse transpose of projection matrix.
        Equivalent to RenderMonkey's "ProjectionInverseTranspose".
        */
        BCT_INVERSE_TRANSPOSE_PROJECTION_MATRIX,


        /// The current view & projection matrices concatenated
        BCT_VIEWPROJ_MATRIX,
        /** Provides inverse of concatenated view and projection matrices.
        Equivalent to RenderMonkey's "ViewProjectionInverse".
        */
        BCT_INVERSE_VIEWPROJ_MATRIX,
        /** Provides transpose of concatenated view and projection matrices.
        Equivalent to RenderMonkey's "ViewProjectionTranspose".
        */
        BCT_TRANSPOSE_VIEWPROJ_MATRIX,
        /** Provides inverse transpose of concatenated view and projection matrices.
        Equivalent to RenderMonkey's "ViewProjectionInverseTranspose".
        */
        BCT_INVERSE_TRANSPOSE_VIEWPROJ_MATRIX,


        /// The current world & view matrices concatenated
        BCT_WORLDVIEW_MATRIX,
        /// The current world & view matrices concatenated, then inverted
        BCT_INVERSE_WORLDVIEW_MATRIX,
        /** Provides transpose of concatenated world and view matrices.
        Equivalent to RenderMonkey's "WorldViewTranspose".
        */
        BCT_TRANSPOSE_WORLDVIEW_MATRIX,
        /// The current world & view matrices concatenated, then inverted & transposed
        BCT_INVERSE_TRANSPOSE_WORLDVIEW_MATRIX,
        /// view matrices.


        /// The current world, view & projection matrices concatenated
        BCT_WORLDVIEWPROJ_MATRIX,
        /** Provides inverse of concatenated world, view and projection matrices.
        Equivalent to RenderMonkey's "WorldViewProjectionInverse".
        */
        BCT_INVERSE_WORLDVIEWPROJ_MATRIX,
        /** Provides transpose of concatenated world, view and projection matrices.
        Equivalent to RenderMonkey's "WorldViewProjectionTranspose".
        */
        BCT_TRANSPOSE_WORLDVIEWPROJ_MATRIX,
        /** Provides inverse transpose of concatenated world, view and projection
        matrices. Equivalent to RenderMonkey's "WorldViewProjectionInverseTranspose".
        */
        BCT_INVERSE_TRANSPOSE_WORLDVIEWPROJ_MATRIX,


        /// render target related values
        /** -1 if requires texture flipping, +1 otherwise. It's useful when you bypassed
        projection matrix transform, still able use this value to adjust transformed y position.
        */
        BCT_RENDER_TARGET_FLIPPING,

        /** -1 if the winding has been inverted (e.g. for reflections), +1 otherwise.
        */
        BCT_VERTEX_WINDING,

        /// Fog colour
        BCT_FOG_COLOUR,
        /// Fog params: density, linear start, linear end, 1/(end-start)
        BCT_FOG_PARAMS,


        /// Surface ambient colour, as set in Pass::setAmbient
        BCT_SURFACE_AMBIENT_COLOUR,
        /// Surface diffuse colour, as set in Pass::setDiffuse
        BCT_SURFACE_DIFFUSE_COLOUR,
        /// Surface specular colour, as set in Pass::setSpecular
        BCT_SURFACE_SPECULAR_COLOUR,
        /// Surface emissive colour, as set in Pass::setSelfIllumination
        BCT_SURFACE_EMISSIVE_COLOUR,
        /// Surface shininess, as set in Pass::setShininess
        BCT_SURFACE_SHININESS,
        /// Surface alpha rejection value, not as set in Pass::setAlphaRejectionValue, but a floating number between 0.0f and 1.0f instead (255.0f / Pass::getAlphaRejectionValue())
        BCT_SURFACE_ALPHA_REJECTION_VALUE,


        /// The number of active light sources (better than gl_MaxLights)
        BCT_LIGHT_COUNT,


        /// The ambient light colour set in the scene
        BCT_AMBIENT_LIGHT_COLOUR,

        /// Light diffuse colour (index determined by setAutoConstant call)
        BCT_LIGHT_DIFFUSE_COLOUR,
        /// Light specular colour (index determined by setAutoConstant call)
        BCT_LIGHT_SPECULAR_COLOUR,
        /// Light attenuation parameters, Vector4(range, constant, linear, quadric)
        BCT_LIGHT_ATTENUATION,
        /** Spotlight parameters, Vector4(innerFactor, outerFactor, falloff, isSpot)
        innerFactor and outerFactor are cos(angle/2)
        The isSpot parameter is 0.0f for non-spotlights, 1.0f for spotlights.
        Also for non-spotlights the inner and outer factors are 1 and nearly 1 respectively
        */
        BCT_SPOTLIGHT_PARAMS,
        /// A light position in world space (index determined by setAutoConstant call)
        BCT_LIGHT_POSITION,
        /// A light position in object space (index determined by setAutoConstant call)
        BCT_LIGHT_POSITION_OBJECT_SPACE,
        /// A light position in view space (index determined by setAutoConstant call)
        BCT_LIGHT_POSITION_VIEW_SPACE,
        /// A light direction in world space (index determined by setAutoConstant call)
        BCT_LIGHT_DIRECTION,
        /// A light direction in object space (index determined by setAutoConstant call)
        BCT_LIGHT_DIRECTION_OBJECT_SPACE,
        /// A light direction in view space (index determined by setAutoConstant call)
        BCT_LIGHT_DIRECTION_VIEW_SPACE,
        /** The distance of the light from the center of the object
        a useful approximation as an alternative to per-vertex distance
        calculations.
        */
        BCT_LIGHT_DISTANCE_OBJECT_SPACE,
        /** Light power level, a single scalar as set in Light::setPowerScale  (index determined by setAutoConstant call) */
        BCT_LIGHT_POWER_SCALE,
        /// Light diffuse colour pre-scaled by Light::setPowerScale (index determined by setAutoConstant call)
        BCT_LIGHT_DIFFUSE_COLOUR_POWER_SCALED,
        /// Light specular colour pre-scaled by Light::setPowerScale (index determined by setAutoConstant call)
        BCT_LIGHT_SPECULAR_COLOUR_POWER_SCALED,
        /// Array of light diffuse colours (count set by extra param)
        BCT_LIGHT_DIFFUSE_COLOUR_ARRAY,
        /// Array of light specular colours (count set by extra param)
        BCT_LIGHT_SPECULAR_COLOUR_ARRAY,
        /// Array of light diffuse colours scaled by light power (count set by extra param)
        BCT_LIGHT_DIFFUSE_COLOUR_POWER_SCALED_ARRAY,
        /// Array of light specular colours scaled by light power (count set by extra param)
        BCT_LIGHT_SPECULAR_COLOUR_POWER_SCALED_ARRAY,
        /// Array of light attenuation parameters, Vector4(range, constant, linear, quadric) (count set by extra param)
        BCT_LIGHT_ATTENUATION_ARRAY,
        /// Array of light positions in world space (count set by extra param)
        BCT_LIGHT_POSITION_ARRAY,
        /// Array of light positions in object space (count set by extra param)
        BCT_LIGHT_POSITION_OBJECT_SPACE_ARRAY,
        /// Array of light positions in view space (count set by extra param)
        BCT_LIGHT_POSITION_VIEW_SPACE_ARRAY,
        /// Array of light directions in world space (count set by extra param)
        BCT_LIGHT_DIRECTION_ARRAY,
        /// Array of light directions in object space (count set by extra param)
        BCT_LIGHT_DIRECTION_OBJECT_SPACE_ARRAY,
        /// Array of light directions in view space (count set by extra param)
        BCT_LIGHT_DIRECTION_VIEW_SPACE_ARRAY,
        /** Array of distances of the lights from the center of the object
        a useful approximation as an alternative to per-vertex distance
        calculations. (count set by extra param)
        */
        BCT_LIGHT_DISTANCE_OBJECT_SPACE_ARRAY,
        /** Array of light power levels, a single scalar as set in Light::setPowerScale
        (count set by extra param)
        */
        BCT_LIGHT_POWER_SCALE_ARRAY,
        /** Spotlight parameters array of Vector4(innerFactor, outerFactor, falloff, isSpot)
        innerFactor and outerFactor are cos(angle/2)
        The isSpot parameter is 0.0f for non-spotlights, 1.0f for spotlights.
        Also for non-spotlights the inner and outer factors are 1 and nearly 1 respectively.
        (count set by extra param)
        */
        BCT_SPOTLIGHT_PARAMS_ARRAY,

        /** The derived ambient light colour, with 'r', 'g', 'b' components filled with
        product of surface ambient colour and ambient light colour, respectively,
        and 'a' component filled with surface ambient alpha component.
        */
        BCT_DERIVED_AMBIENT_LIGHT_COLOUR,
        /** The derived scene colour, with 'r', 'g' and 'b' components filled with sum
        of derived ambient light colour and surface emissive colour, respectively,
        and 'a' component filled with surface diffuse alpha component.
        */
        BCT_DERIVED_SCENE_COLOUR,

        /** The derived light diffuse colour (index determined by setAutoConstant call),
        with 'r', 'g' and 'b' components filled with product of surface diffuse colour,
        light power scale and light diffuse colour, respectively, and 'a' component filled with surface
        diffuse alpha component.
        */
        BCT_DERIVED_LIGHT_DIFFUSE_COLOUR,
        /** The derived light specular colour (index determined by setAutoConstant call),
        with 'r', 'g' and 'b' components filled with product of surface specular colour
        and light specular colour, respectively, and 'a' component filled with surface
        specular alpha component.
        */
        BCT_DERIVED_LIGHT_SPECULAR_COLOUR,

        /// Array of derived light diffuse colours (count set by extra param)
        BCT_DERIVED_LIGHT_DIFFUSE_COLOUR_ARRAY,
        /// Array of derived light specular colours (count set by extra param)
        BCT_DERIVED_LIGHT_SPECULAR_COLOUR_ARRAY,
        /** The absolute light number of a local light index. Each pass may have
        a number of lights passed to it, and each of these lights will have
        an index in the overall light list, which will differ from the local
        light index due to factors like setStartLight and setIteratePerLight.
        This binding provides the global light index for a local index.
        */
        BCT_LIGHT_NUMBER,
        /// Returns (int) 1 if the  given light casts shadows, 0 otherwise (index set in extra param)
        BCT_LIGHT_CASTS_SHADOWS,
        /// Returns (int) 1 if the  given light casts shadows, 0 otherwise (index set in extra param)
        BCT_LIGHT_CASTS_SHADOWS_ARRAY,


        /** The distance a shadow volume should be extruded when using
        finite extrusion programs.
        */
        BCT_SHADOW_EXTRUSION_DISTANCE,
        /// The current camera's position in world space
        BCT_CAMERA_POSITION,
        /// The current camera's position in object space 
        BCT_CAMERA_POSITION_OBJECT_SPACE,
        /// The view/projection matrix of the assigned texture projection frustum
        BCT_TEXTURE_VIEWPROJ_MATRIX,
        /// Array of view/projection matrices of the first n texture projection frustums
        BCT_TEXTURE_VIEWPROJ_MATRIX_ARRAY,
        /** The view/projection matrix of the assigned texture projection frustum,
        combined with the current world matrix
        */
        BCT_TEXTURE_WORLDVIEWPROJ_MATRIX,
        /// Array of world/view/projection matrices of the first n texture projection frustums
        BCT_TEXTURE_WORLDVIEWPROJ_MATRIX_ARRAY,
        /// The view/projection matrix of a given spotlight
        BCT_SPOTLIGHT_VIEWPROJ_MATRIX,
        /// Array of view/projection matrix of a given spotlight
        BCT_SPOTLIGHT_VIEWPROJ_MATRIX_ARRAY,
        /** The view/projection matrix of a given spotlight projection frustum,
        combined with the current world matrix
        */
        BCT_SPOTLIGHT_WORLDVIEWPROJ_MATRIX,
        /** An array of the view/projection matrix of a given spotlight projection frustum,
         combined with the current world matrix
         */
        BCT_SPOTLIGHT_WORLDVIEWPROJ_MATRIX_ARRAY,
        /// A custom parameter which will come from the renderable, using 'data' as the identifier
        BCT_CUSTOM,
        /** provides current elapsed time
        */
        BCT_TIME,
        /** Single float value, which repeats itself based on given as
        parameter "cycle time". Equivalent to RenderMonkey's "Time0_X".
        */
        BCT_TIME_0_X,
        /// Cosine of "Time0_X". Equivalent to RenderMonkey's "CosTime0_X".
        BCT_COSTIME_0_X,
        /// Sine of "Time0_X". Equivalent to RenderMonkey's "SinTime0_X".
        BCT_SINTIME_0_X,
        /// Tangent of "Time0_X". Equivalent to RenderMonkey's "TanTime0_X".
        BCT_TANTIME_0_X,
        /** Vector of "Time0_X", "SinTime0_X", "CosTime0_X",
        "TanTime0_X". Equivalent to RenderMonkey's "Time0_X_Packed".
        */
        BCT_TIME_0_X_PACKED,
        /** Single float value, which represents scaled time value [0..1],
        which repeats itself based on given as parameter "cycle time".
        Equivalent to RenderMonkey's "Time0_1".
        */
        BCT_TIME_0_1,
        /// Cosine of "Time0_1". Equivalent to RenderMonkey's "CosTime0_1".
        BCT_COSTIME_0_1,
        /// Sine of "Time0_1". Equivalent to RenderMonkey's "SinTime0_1".
        BCT_SINTIME_0_1,
        /// Tangent of "Time0_1". Equivalent to RenderMonkey's "TanTime0_1".
        BCT_TANTIME_0_1,
        /** Vector of "Time0_1", "SinTime0_1", "CosTime0_1",
        "TanTime0_1". Equivalent to RenderMonkey's "Time0_1_Packed".
        */
        BCT_TIME_0_1_PACKED,
        /**	Single float value, which represents scaled time value [0..2*Pi],
        which repeats itself based on given as parameter "cycle time".
        Equivalent to RenderMonkey's "Time0_2PI".
        */
        BCT_TIME_0_2PI,
        /// Cosine of "Time0_2PI". Equivalent to RenderMonkey's "CosTime0_2PI".
        BCT_COSTIME_0_2PI,
        /// Sine of "Time0_2PI". Equivalent to RenderMonkey's "SinTime0_2PI".
        BCT_SINTIME_0_2PI,
        /// Tangent of "Time0_2PI". Equivalent to RenderMonkey's "TanTime0_2PI".
        BCT_TANTIME_0_2PI,
        /** Vector of "Time0_2PI", "SinTime0_2PI", "CosTime0_2PI",
        "TanTime0_2PI". Equivalent to RenderMonkey's "Time0_2PI_Packed".
        */
        BCT_TIME_0_2PI_PACKED,
        /// provides the scaled frame time, returned as a floating point value.
        BCT_FRAME_TIME,
        /// provides the calculated frames per second, returned as a floating point value.
        BCT_FPS,
        /// viewport-related values
        /** Current viewport width (in pixels) as floating point value.
        Equivalent to RenderMonkey's "ViewportWidth".
        */
        BCT_VIEWPORT_WIDTH,
        /** Current viewport height (in pixels) as floating point value.
        Equivalent to RenderMonkey's "ViewportHeight".
        */
        BCT_VIEWPORT_HEIGHT,
        /** This variable represents 1.0/ViewportWidth.
        Equivalent to RenderMonkey's "ViewportWidthInverse".
        */
        BCT_INVERSE_VIEWPORT_WIDTH,
        /** This variable represents 1.0/ViewportHeight.
        Equivalent to RenderMonkey's "ViewportHeightInverse".
        */
        BCT_INVERSE_VIEWPORT_HEIGHT,
        /** Packed of "ViewportWidth", "ViewportHeight", "ViewportWidthInverse",
        "ViewportHeightInverse".
        */
        BCT_VIEWPORT_SIZE,

        /// view parameters
        /** This variable provides the view direction vector (world space).
        Equivalent to RenderMonkey's "ViewDirection".
        */
        BCT_VIEW_DIRECTION,
        /** This variable provides the view side vector (world space).
        Equivalent to RenderMonkey's "ViewSideVector".
        */
        BCT_VIEW_SIDE_VECTOR,
        /** This variable provides the view up vector (world space).
        Equivalent to RenderMonkey's "ViewUpVector".
        */
        BCT_VIEW_UP_VECTOR,
        /** This variable provides the field of view as a floating point value.
        Equivalent to RenderMonkey's "FOV".
        */
        BCT_FOV,
        /**	This variable provides the near clip distance as a floating point value.
        Equivalent to RenderMonkey's "NearClipPlane".
        */
        BCT_NEAR_CLIP_DISTANCE,
        /**	This variable provides the far clip distance as a floating point value.
        Equivalent to RenderMonkey's "FarClipPlane".
        */
        BCT_FAR_CLIP_DISTANCE,

        /** provides the pass index number within the technique
        of the active materil.
        */
        BCT_PASS_NUMBER,

        /** provides the current iteration number of the pass. The iteration
        number is the number of times the current render operation has
        been drawn for the active pass.
        */
        BCT_PASS_ITERATION_NUMBER,


        /** Provides a parametric animation value [0..1], only available
        where the renderable specifically implements it.
        */
        BCT_ANIMATION_PARAMETRIC,

        /** Provides the texel offsets required by this rendersystem to map
        texels to pixels. Packed as
        float4(absoluteHorizontalOffset, absoluteVerticalOffset,
        horizontalOffset / viewportWidth, verticalOffset / viewportHeight)
        */
        BCT_TEXEL_OFFSETS,

        /** Provides information about the depth range of the scene as viewed
        from the current camera.
        Passed as float4(minDepth, maxDepth, depthRange, 1 / depthRange)
        */
        BCT_SCENE_DEPTH_RANGE,

        /** Provides information about the depth range of the scene as viewed
        from a given shadow camera. Requires an index parameter which maps
        to a light index relative to the current light list.
        Passed as float4(minDepth, maxDepth, depthRange, 1 / depthRange)
        */
        BCT_SHADOW_SCENE_DEPTH_RANGE,

        /** Provides an array of information about the depth range of the scene as viewed
         from a given shadow camera. Requires an index parameter which maps
         to a light index relative to the current light list.
         Passed as float4(minDepth, maxDepth, depthRange, 1 / depthRange)
        */
        BCT_SHADOW_SCENE_DEPTH_RANGE_ARRAY,

        /** Provides the fixed shadow colour as configured via SceneManager::setShadowColour;
        useful for integrated modulative shadows.
        */
        BCT_SHADOW_COLOUR,
        /** Provides texture size of the texture unit (index determined by setAutoConstant
        call). Packed as float4(width, height, depth, 1)
        */
        BCT_TEXTURE_SIZE,
        /** Provides inverse texture size of the texture unit (index determined by setAutoConstant
        call). Packed as float4(1 / width, 1 / height, 1 / depth, 1)
        */
        BCT_INVERSE_TEXTURE_SIZE,
        /** Provides packed texture size of the texture unit (index determined by setAutoConstant
        call). Packed as float4(width, height, 1 / width, 1 / height)
        */
        BCT_PACKED_TEXTURE_SIZE,

        /** Provides the current transform matrix of the texture unit (index determined by setAutoConstant
        call), as seen by the fixed-function pipeline.
        */
        BCT_TEXTURE_MATRIX,

        /** Provides the position of the LOD camera in world space, allowing you
        to perform separate LOD calculations in shaders independent of the rendering
        camera. If there is no separate LOD camera then this is the real camera
        position. See Camera::setLodCamera.
        */
        BCT_LOD_CAMERA_POSITION,
        /** Provides the position of the LOD camera in object space, allowing you
        to perform separate LOD calculations in shaders independent of the rendering
        camera. If there is no separate LOD camera then this is the real camera
        position. See Camera::setLodCamera.
        */
        BCT_LOD_CAMERA_POSITION_OBJECT_SPACE,
        /** Binds custom per-light constants to the shaders. */
        BCT_LIGHT_CUSTOM,

        BCT_UNKNOWN = 999
    };

    struct BuiltinConstantDefinition
    {
        BuiltinConstantType type;
        String              name;
        uint32_t            elementCount;
        BuiltinType         elementType;
        BuiltinType         extraType;

        BuiltinConstantDefinition()
            : type(BCT_UNKNOWN)
            , elementCount(0)
            , elementType(BT_NONE)
            , extraType(BT_NONE)
        {}

        BuiltinConstantDefinition(BuiltinConstantType t, const String &n, uint32_t c, BuiltinType elementT, BuiltinType extraT)
            : type(t)
            , name(n)
            , elementCount(c)
            , elementType(elementT)
            , extraType(extraT)
        {}

        BuiltinConstantDefinition(const BuiltinConstantDefinition &other)
            : type(other.type)
            , name(other.name)
            , elementCount(other.elementCount)
            , elementType(other.elementType)
            , extraType(other.extraType)
        {}

        BuiltinConstantDefinition &operator =(const BuiltinConstantDefinition &other)
        {
            type = other.type;
            name = other.name;
            elementCount = other.elementCount;
            elementType = other.elementType;
            extraType = other.extraType;
            return *this;
        }
    };
}


#endif  /*__T3D_SCRIPT_TYPE_H__*/
