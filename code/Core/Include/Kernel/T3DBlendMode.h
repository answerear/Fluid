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


#ifndef __T3D_BLEND_MODE_H__
#define __T3D_BLEND_MODE_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"


namespace Tiny3D
{
    /**
     * @enum    LayerBlendType
     * @brief   纹理混合类型
     */
    enum class LayerBlendType : uint32_t
    {
        COLOR,
        ALPHA
    };

    /**
     * @enum    LayerBlendOperation
     * @brief   纹理混合操作
     */
    enum class LayerBlendOperation : uint32_t
    {
        REPLACE,      /// 用纹理覆盖所有
        ADD,          /// 把颜色分量叠加
        MODULATE,     /// 把颜色分量相乘
        ALPHA_BLEND   /// 根据纹理alpha通道叠加
    };

    /**
     * @enum    LayerBlendOperationEx
     * @brief   Values that represent layer blend operation Exceptions
     */
    enum class LayerBlendOperationEx : uint32_t
    {
        SOURCE1,
        SOURCE2,
        MODULATE,
        MODULATE_X2,
        MODULATE_X4,
        ADD,
        ADD_SIGNED,
        ADD_SMOOTH,
        SUBTRACT,
        BLEND_DIFFUSE_ALPHA,
        BLEND_TEXTURE_ALPHA,
        BLEND_CURRENT_ALPHA,
        BLEND_MANUAL,
        DOTPRODUCT,
        BLEND_DIFFUSE_COLOR
    };

    /**
     * @enum    LayerBlendSource
     * @brief   Values that represent layer blend sources
     */
    enum class LayerBlendSource : uint32_t
    {
        CURRENT,
        TEXTURE,
        DIFFUSE,
        SPECULAR,
        MANUAL
    };

    /**
     * @class   LayerBlendModeEx
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API LayerBlendModeEx
    {
    public:
        LayerBlendType          blendType;
        LayerBlendOperationEx   operation;
        LayerBlendSource        source1;
        LayerBlendSource        source2;

        ColorRGBA               colorArg1;
        ColorRGBA               colorArg2;
        Real                    alphaArg1;
        Real                    alphaArg2;
        Real                    factor;

        bool operator ==(const LayerBlendModeEx &other) const
        {
            if (blendType != other.blendType) return false;

            if (blendType == LayerBlendType::COLOR)
            {

                if (operation == other.operation &&
                    source1 == other.source1 &&
                    source2 == other.source2 &&
                    colorArg1 == other.colorArg1 &&
                    colorArg2 == other.colorArg2 &&
                    factor == other.factor)
                {
                    return true;
                }
            }
            else // if (blendType == LBT_ALPHA)
            {
                if (operation == other.operation &&
                    source1 == other.source1 &&
                    source2 == other.source2 &&
                    alphaArg1 == other.alphaArg1 &&
                    alphaArg2 == other.alphaArg2 &&
                    factor == other.factor)
                {
                    return true;
                }
            }
            return false;
        }

        bool operator !=(const LayerBlendModeEx &other) const
        {
            return !(*this == other);
        }
    };

    /**
     * @enum    BlendType
     * @brief   混合类型
     */
    enum class BlendType : uint32_t
    {
        /// 使用纹理上的alpha值来做混合计算，相当于：
        /// C_result = C_src * A_src + C_dst * (1 - A_src)
        TRANSPARENT_ALPHA,
        /// 使用纹理上的颜色值来做混合计算，相当于：
        /// C_result = C_src * C_src + C_dst * (1 - C_src)
        TRANSPARENT_COLOR,
        /// 把纹理颜色值直接叠加到现在渲染目标中的颜色值，相当于：
        /// C_result = C_src + C_dst
        ADD,
        /// 直接把纹理颜色值跟渲染目标中的颜色值相乘，相当于：
        /// C_result = C_src * C_dst
        MODULATE,
        /// 默认方式，直接用纹理颜色代替渲染目标的颜色
        REPLACE,
    };

    /**
     * @enum    BlendFactor
     * @brief   混合因子
     */
    enum class BlendFactor : uint32_t
    {
        ONE,                     /// 1.0
        ZERO,                    /// 0.0
        DEST_COLOR,              /// C_dst
        SOURCE_COLOR,            /// C_src
        ONE_MINUS_DEST_COLOR,    /// 1 - C_dst
        ONE_MINUS_SOURCE_COLOR,  /// 1 - C_src
        DEST_ALPHA,              /// A_dst
        SOURCE_ALPHA,            /// A_src
        ONE_MINUS_DEST_ALPHA,    /// 1 - A_dst
        ONE_MINUS_SOURCE_ALPHA   /// 1 - A_src
    };

    /**
     * @enum    BlendOperation
     * @brief   混合操作
     */
    enum class BlendOperation : uint32_t
    {
        ADD,                 /// C_result = C_src * F_src + C_dst * F_dst
        SUBTRACT,            /// C_result = C_src * F_src - C_dst * F_dst
        REVERSE_SUBTRACT,    /// C_result = C_dst * F_dst - C_src * F_src
        MIN,                 /// 
        MAX
    };

    /**
     * @struct  BlendState
     * @brief   A 3D engine api.
     */
    struct T3D_ENGINE_API BlendMode
    {
        bool    writeR;
        bool    writeG;
        bool    writeB;
        bool    writeA;

        BlendFactor sourceFactor;
        BlendFactor destFactor;
        BlendFactor sourceFactorAlpha;
        BlendFactor destFactorAlpha;

        BlendOperation  operation;
        BlendOperation  alphaOperation;

        BlendMode()
            : writeR(true)
            , writeG(true)
            , writeB(true)
            , writeA(true)
            , sourceFactor(BlendFactor::ONE)
            , destFactor(BlendFactor::ZERO)
            , sourceFactorAlpha(BlendFactor::ONE)
            , destFactorAlpha(BlendFactor::ZERO)
            , operation(BlendOperation::ADD)
            , alphaOperation(BlendOperation::ADD)
        {}

        bool isBlendingEnabled() const
        {
            return !(sourceFactor == BlendFactor::ONE
                && destFactor == BlendFactor::ZERO
                && sourceFactorAlpha == BlendFactor::ONE
                && destFactorAlpha == BlendFactor::ZERO);
        }
    };
}


#endif  /*__T3D_BLEND_MODE_H__*/
