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


#include "Serializer/T3DSerializerManager.h"
#include "Serializer/T3DBinMaterialReader.h"
#include "Serializer/T3DBinMaterialWriter.h"
#include "Serializer/T3DJSONMaterialReader.h"
#include "Serializer/T3DJSONMaterialWriter.h"
#include "Serializer/T3DBinModelReader.h"
#include "Serializer/T3DBinModelWriter.h"
#include "Serializer/T3DJSONModelReader.h"
#include "Serializer/T3DJSONModelWriter.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(SerializerManager, Object);

    T3D_INIT_SINGLETON(SerializerManager);

    //--------------------------------------------------------------------------

    SerializerManagerPtr SerializerManager::create()
    {
        SerializerManagerPtr mgr = new SerializerManager();
        mgr->release();
        return mgr;
    }

    //--------------------------------------------------------------------------

    SerializerManager::SerializerManager()
        : mFileMode(FileMode::TEXT)
    {
        constructBuiltinConstantMap();
    }

    //--------------------------------------------------------------------------

    void SerializerManager::constructBuiltinConstantMap()
    {
        mBuiltinConstantMap[BuiltinConstantType::WORLD_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_WORLD_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::TRANSPOSE_WORLD_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_TRANSPOSE_WORLD_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);

        mBuiltinConstantMap[BuiltinConstantType::WORLD_MATRIX_ARRAY_3x4] = BuiltinConstantDefinition(12, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::WORLD_MATRIX_ARRAY] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::WORLD_DUALQUATERNION_ARRAY_2x4] = BuiltinConstantDefinition(8, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::WORLD_SCALE_SHEAR_MATRIX_ARRAY_3x4] = BuiltinConstantDefinition(9, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::VIEW_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_VIEW_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::TRANSPOSE_VIEW_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_TRANSPOSE_VIEW_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);

        mBuiltinConstantMap[BuiltinConstantType::PROJECTION_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_PROJECTION_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::TRANSPOSE_PROJECTION_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_TRANSPOSE_PROJECTION_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);

        mBuiltinConstantMap[BuiltinConstantType::VIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_VIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::TRANSPOSE_VIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_TRANSPOSE_VIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);

        mBuiltinConstantMap[BuiltinConstantType::WORLDVIEW_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_WORLDVIEW_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::TRANSPOSE_WORLDVIEW_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_TRANSPOSE_WORLDVIEW_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);

        mBuiltinConstantMap[BuiltinConstantType::WORLDVIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_WORLDVIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::TRANSPOSE_WORLDVIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_TRANSPOSE_WORLDVIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::NONE);

        mBuiltinConstantMap[BuiltinConstantType::RENDER_TARGET_FLIPPING] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::VERTEX_WINDING] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);

        mBuiltinConstantMap[BuiltinConstantType::FOG_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::FOG_PARAMS] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);

        mBuiltinConstantMap[BuiltinConstantType::SURFACE_AMBIENT_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::SURFACE_DIFFUSE_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::SURFACE_SPECULAR_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::SURFACE_EMISSIVE_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::SURFACE_SHININESS] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::SURFACE_ALPHA_REJECTION_VALUE] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);

        mBuiltinConstantMap[BuiltinConstantType::LIGHT_COUNT] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);

        mBuiltinConstantMap[BuiltinConstantType::AMBIENT_LIGHT_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DIFFUSE_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_SPECULAR_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_ATTENUATION] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::SPOTLIGHT_PARAMS] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_POSITION] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_POSITION_OBJECT_SPACE] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_POSITION_VIEW_SPACE] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DIRECTION] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DIRECTION_OBJECT_SPACE] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DIRECTION_VIEW_SPACE] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DISTANCE_OBJECT_SPACE] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_POWER_SCALE] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DIFFUSE_COLOUR_POWER_SCALED] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_SPECULAR_COLOUR_POWER_SCALED] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DIFFUSE_COLOUR_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_SPECULAR_COLOUR_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DIFFUSE_COLOUR_POWER_SCALED_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_SPECULAR_COLOUR_POWER_SCALED_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_ATTENUATION_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_POSITION_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_POSITION_OBJECT_SPACE_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_POSITION_VIEW_SPACE_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DIRECTION_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DIRECTION_OBJECT_SPACE_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DIRECTION_VIEW_SPACE_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_DISTANCE_OBJECT_SPACE_ARRAY] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_POWER_SCALE_ARRAY] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::SPOTLIGHT_PARAMS_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);

        mBuiltinConstantMap[BuiltinConstantType::DERIVED_AMBIENT_LIGHT_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::DERIVED_SCENE_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::DERIVED_LIGHT_DIFFUSE_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::DERIVED_LIGHT_SPECULAR_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::DERIVED_LIGHT_DIFFUSE_COLOUR_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::DERIVED_LIGHT_SPECULAR_COLOUR_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);

        mBuiltinConstantMap[BuiltinConstantType::LIGHT_NUMBER] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_CASTS_SHADOWS] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_CASTS_SHADOWS_ARRAY] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::INT);

        mBuiltinConstantMap[BuiltinConstantType::SHADOW_EXTRUSION_DISTANCE] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::CAMERA_POSITION] = BuiltinConstantDefinition(3, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::CAMERA_POSITION_OBJECT_SPACE] = BuiltinConstantDefinition(3, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::TEXTURE_VIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::TEXTURE_VIEWPROJ_MATRIX_ARRAY] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::TEXTURE_WORLDVIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::TEXTURE_WORLDVIEWPROJ_MATRIX_ARRAY] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::SPOTLIGHT_VIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::SPOTLIGHT_VIEWPROJ_MATRIX_ARRAY] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::SPOTLIGHT_WORLDVIEWPROJ_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::SPOTLIGHT_WORLDVIEWPROJ_MATRIX_ARRAY] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::CUSTOM] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);  // *** needs to be tested
        mBuiltinConstantMap[BuiltinConstantType::TIME] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::TIME_0_X] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::COSTIME_0_X] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::SINTIME_0_X] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::TANTIME_0_X] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::TIME_0_X_PACKED] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::TIME_0_1] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::COSTIME_0_1] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::SINTIME_0_1] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::TANTIME_0_1] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::TIME_0_1_PACKED] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::TIME_0_2PI] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::COSTIME_0_2PI] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::SINTIME_0_2PI] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::TANTIME_0_2PI] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::TIME_0_2PI_PACKED] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::FRAME_TIME] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::REAL);
        mBuiltinConstantMap[BuiltinConstantType::FPS] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::VIEWPORT_WIDTH] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::VIEWPORT_HEIGHT] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_VIEWPORT_WIDTH] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_VIEWPORT_HEIGHT] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::VIEWPORT_SIZE] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::VIEW_DIRECTION] = BuiltinConstantDefinition(3, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::VIEW_SIDE_VECTOR] = BuiltinConstantDefinition(3, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::VIEW_UP_VECTOR] = BuiltinConstantDefinition(3, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::FOV] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::NEAR_CLIP_DISTANCE] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::FAR_CLIP_DISTANCE] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::PASS_NUMBER] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::PASS_ITERATION_NUMBER] = BuiltinConstantDefinition(1, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::ANIMATION_PARAMETRIC] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::TEXEL_OFFSETS] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::SCENE_DEPTH_RANGE] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::SHADOW_SCENE_DEPTH_RANGE] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::SHADOW_SCENE_DEPTH_RANGE_ARRAY] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::SHADOW_COLOUR] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::TEXTURE_SIZE] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::INVERSE_TEXTURE_SIZE] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::PACKED_TEXTURE_SIZE] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::TEXTURE_MATRIX] = BuiltinConstantDefinition(16, BuiltinType::REAL, BuiltinType::INT);
        mBuiltinConstantMap[BuiltinConstantType::LOD_CAMERA_POSITION] = BuiltinConstantDefinition(3, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::LOD_CAMERA_POSITION_OBJECT_SPACE] = BuiltinConstantDefinition(3, BuiltinType::REAL, BuiltinType::NONE);
        mBuiltinConstantMap[BuiltinConstantType::LIGHT_CUSTOM] = BuiltinConstantDefinition(4, BuiltinType::REAL, BuiltinType::INT);
    }

    //--------------------------------------------------------------------------

    TResult SerializerManager::parseMaterial(
        DataStream &stream, Material *material)
    {
        MaterialReaderPtr reader;

        switch (mFileMode)
        {
        case FileMode::BINARY:
            {
                reader = BinMaterialReader::create(mBuiltinConstantMap);
            }
            break;
        case FileMode::TEXT:
            {
                reader = JsonMaterialReader::create(mBuiltinConstantMap);
            }
            break;
        default:
            {
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Invalid file mode of material !");
            }
            break;
        }

        TResult ret = T3D_OK;

        if (reader != nullptr)
        {
            ret = reader->parse(stream, material);
        }
        else
        {
            ret = T3D_ERR_INVALID_POINTER;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult SerializerManager::serializeMaterial(
        DataStream &stream, Material *material)
    {
        MaterialWriterPtr writer;

        switch (mFileMode)
        {
        case FileMode::BINARY:
            {
                writer = BinMaterialWriter::create();
            }
            break;
        case FileMode::TEXT:
            {
                writer = JsonMaterialWriter::create();
            }
            break;
        default:
            {
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Invalid file mode of material !");
            }
            break;
        }

        TResult ret = T3D_OK;

        if (writer != nullptr)
        {
            ret = writer->serialize(stream, material);
        }
        else
        {
            ret = T3D_ERR_INVALID_POINTER;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult SerializerManager::parseModel(DataStream &stream, Model *model)
    {
        ModelReaderPtr reader;

        switch (mFileMode)
        {
        case FileMode::BINARY:
            {
                reader = BinModelReader::create();
            }
            break;
        case FileMode::TEXT:
            {
                reader = JsonModelReader::create();
            }
            break;
        default:
            {
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Invalid file mode of model !");
            }
            break;
        }

        TResult ret = T3D_OK;

        if (reader != nullptr)
        {
            ret = reader->parse(stream, model);
        }
        else
        {
            ret = T3D_ERR_INVALID_POINTER;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult SerializerManager::serializeModel(DataStream &stream, Model *model)
    {
        ModelWriterPtr writer;

        switch (mFileMode)
        {
        case FileMode::BINARY:
            {
                writer = BinModelWriter::create();
            }
            break;
        case FileMode::TEXT:
            {
                writer = JsonModelWriter::create();
            }
            break;
        default:
            {
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Invalid file mode of model !");
            }
            break;
        }

        TResult ret = T3D_OK;

        if (writer != nullptr)
        {
            ret = writer->serialize(stream, model);
        }
        else
        {
            ret = T3D_ERR_INVALID_POINTER;
        }

        return ret;
    }
}
