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


#ifndef __T3D_TEXTURE_UNIT_H__
#define __T3D_TEXTURE_UNIT_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "T3DObject.h"
#include "Resource/T3DTexture.h"
#include "Kernel/T3DCommon.h"
#include "Kernel/T3DBlendMode.h"


namespace Tiny3D
{
    /**
     * @class   TextureUnit
     * @brief   A 3D engine api.
     */
    class T3D_ENGINE_API TextureUnit : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @enum    BindingType
         * @brief   描述纹理绑定到渲染流水线中可编程流水线阶段上
         */
        enum class BindingType : uint32_t
        {
            FRAGMENT = 0,
            VERTEX,
            GEOMETRY,
            TESSELATION_HULL,
            TESSELATION_DOMAIN,
            COMPUTE
        };

        /**
         * @enum    ContentType
         * @brief   描述纹理内容的标识
         */
        enum class ContentType : uint32_t
        {
            NAMED = 0,    /// 通过名字标识纹理
            SHADOW,       /// 阴影纹理
        };

        /**
         * @enum    EffectType
         * @brief   纹理效果
         * @remarks 可编程渲染管线下无效，可以使用 vertex/fragment shader 实现
         */
        enum class EffectType : uint32_t
        {
            ENVIRONMENT_MAP = 0,   /// 环境映射
            PROJECTIVE_TEXTURE,    /// 投影纹理映射
            UVSCROLL,
            USCROLL,
            VSCROLL,
            ROTATE,
            TRANSFORM
        };

        /**
         * @enum    EnvMapType
         * @brief   Values that represent Environment map types
         */
        enum class EnvMapType : uint32_t
        {
            PLANAR = 0,
            CURVED,
            REFLECTION,
            NORMAL
        };

        /**
         * @enum    TransformType
         * @brief   Values that represent transform types
         */
        enum class TransformType : uint32_t
        {
            TRANSLATE_U = 0,
            TRANSLATE_V,
            SCALE_U,
            SCALE_V,
            ROTATE
        };

        /**
         * @enum    TextureCubeFace
         * @brief   Values that represent texture cube faces
         */
        enum class TextureCubeFace : uint32_t
        {
            FRONT = 0,
            BACK,
            LEFT,
            RIGHT,
            UP,
            DOWN
        };

        /**
         * @struct  TextureEffect
         * @brief   A texture effect.
         */
        struct TextureEffect
        {
            EffectType      type;
            int32_t         subtype;
            Real            arg1, arg2;
            WaveformType    waveType;
            Real            base;
            Real            frequency;
            Real            phase;
            Real            amplitude;
        };

    public:
        /**
         * @fn  static TextureUnitPtr TextureUnit::create(const String &name, 
         *      Pass *pass);
         * @brief   创建 TextureUnit 对象
         * @param           name    The name.
         * @param [in,out]  pass    If non-null, the pass.
         * @return  A TextureUnitPtr.
         */
        static TextureUnitPtr create(const String &name, Pass *pass);

        /**
         * @fn  virtual TextureUnit::~TextureUnit();
         * @brief   析构函数
         */
        virtual ~TextureUnit();

        /**
         * @fn  const String TextureUnit::&getName() const;
         * @brief   Gets the name
         * @return  The name.
         */
        const String &getName() const;

        /**
         * @fn  void TextureUnit::setSampler(SamplerPtr sampler);
         * @brief   Sets a sampler
         * @param   name    The name.
         */
        void setSampler(SamplerPtr sampler);

        /**
         * @fn  SamplerPtr TextureUnit::getSampler();
         * @brief   Gets the sampler
         * @return  The sampler.
         */
        SamplerPtr getSampler();

        /**
         * @fn  const String TextureUnit::&getTextureName() const;
         * @brief   Gets texture name
         * @return  The texture name.
         */
        const String &getTextureName() const;

        /**
         * @fn  void TextureUnit::setTextureName(const String &name);
         * @brief   Sets texture name
         * @param   name    The name.
         */
        void setTextureName(const String &name);

        /**
         * @fn  TexturePtr TextureUnit::getTexture();
         * @brief   Gets the texture
         * @return  The texture.
         */
        TexturePtr getTexture();

    protected:
        /**
         * @fn  TextureUnit::TextureUnit(const String &name, Pass *pass);
         * @brief   构造函数
         * @param           name    The name.
         * @param [in,out]  pass    If non-null, the pass.
         */
        TextureUnit(const String &name, Pass *pass);

    protected:
        typedef TMultimap<EffectType, TextureEffect>    EffectMap;
        typedef EffectMap::iterator                     EffectMapItr;
        typedef EffectMap::const_iterator               EffectMapConstItr;
        typedef EffectMap::value_type                   EffectMapValue;

        typedef TArray<TexturePtr>                      Textures;
        typedef Textures::iterator                      TexturesItr;
        typedef Textures::const_iterator                TexturesConstItr;

        Pass        *mParent;           /**< 当前纹理单元所属的pass对象 */

        String      mName;              /**< 纹理单元名称 */

        SamplerPtr  mSampler;           /**< 纹理采样器对象 */

        //---------------------------------------
        // Command : texture_alias
        // Usage : texture_alias <name>
        String      mNameAlias;         /**< 纹理单元别名 */

        //---------------------------------------
        // Command : texture
        // Usage : texture <texturename> [<type>] [unlimited|numMipmaps] [alpha] [<PixelFormat>] [gamma]
        // Parameters : 
        //  #1 texturename 存放在 mFrames 中
        TextureType mTextureType;       /// 纹理类型
        PixelFormat mTextureFormat;     /// 纹理格式
        int32_t     mSrcMipmaps;        /// 原纹理的mipmaps数量
        bool        mIsAlpha;           /// 纹理是否用于亮度的
        bool        mHWGamma;           /// 是否开启硬件gamma校正
        bool        mCubic;             /// 是否cubemap

        //---------------------------------------
        // Command : anim_texture
        // Usage : 
        //  #1 anim_texture <base_name> <num_frames> <duration>
        //  #2 anim_texture <frame1> <frame2> ... <duration>
        uint16_t    mCurrentFrame;      /// 当前帧计数
        Real        mAnimDuration;      /// 动画持续时长
//         StringArray mFrames;
        Textures    mFrames;

        //---------------------------------------
        // Command : cubic_texture
        // Usage : 
        //  #1 cubic_texture <base_name> <combineUVW|separateUV>
        //  #2 cubic_texture <front> <back> <left> <right> <up><down> separateUV
        // Parameters : 
        //  #1 所有的都跟 anim_texture 共用
        //  #2 combineUVW 设置 mTextureType 为 E_TEX_TYPE_CUBE_MAP
        //  #3 separateUV 设置 mTextureType 为 E_TEX_TYPE_2D
        
        //---------------------------------------
        // Command : binding_type
        // Usage : binding_type <vertex|fragment>
        BindingType     mBindingType;   /// 纹理绑定到渲染流水线可编程阶段

        //---------------------------------------
        // Command : content_type
        // Usage : content_type <named|shadow>
        ContentType     mContentType;   /// 纹理标识方式，普通加载的还是自动创建的

        //---------------------------------------
        // Command : tex_coord_set
        // Usage : tex_coord_set <set_num>
        uint32_t    mTexCoordSetIndex;  /// 当前材质使用的纹理层级索引

        //---------------------------------------
        // Command : tex_address_mode
        // Usage : 
        //  #1 tex_address_mode <uvw_mode>
        //  #2 tex_address_mode <u_mode> <v_mode> [<w_mode>]
        UVWAddressMode  mAddressMode;   /// 3个维度的纹理寻址模式

        //---------------------------------------
        // Command : tex_border_color
        // Usage : tex_border_color <red> <green> <blue> [<alpha>]
        ColorRGBA   mBorderColor;       /// border 模式下的边缘颜色

        //---------------------------------------
        // Command : filtering
        // Usage : 
        //  #1 filtering <none|bilinear|trilinear|anisotropic>
        //  #2 filtering <minification> <magnification> <mip>
        FilterOptions   mMinFilter;
        FilterOptions   mMagFilter;
        FilterOptions   mMipFilter;
        bool            mIsDefaultFiltering;

        //---------------------------------------
        // Command : compare_test
        // Usage : compare_test <on|off>
        bool            mCompareEnabled;

        //---------------------------------------
        // Command : compare_func
        // Usage : compare_func <always_fail|always_pass|less|less_equal|equal|not_equal|greater_equal|greater>
        CompareFunction mCompareFunc;

        //---------------------------------------
        // Command : max_anisotropy
        // Usage : max_anisotropy <value>
        uint32_t        mMaxAnisotropy;
        bool            mIsDefaultAniso;

        //---------------------------------------
        // Command : mipmap_bias
        // Usage : mipmap_bias <value>
        Real        mMipmapBias;

        //---------------------------------------
        // Command : color_op
        // Usage : color_op <replace|add|modulate|alpha_blend>
        // Parameters :
        //  #1 replace 相当于 color_op_ex source1 src_texture src_current
        //  #2 add 相当于 color_op_ex add src_texture src_current
        //  #3 modulate 相当于 color_op_ex modulate src_textuer src_current
        //  #4 alpha_blend 相当于 color_op_ex blend_texture_alpha src_texture src_current

        //---------------------------------------
        // Command : color_op_ex
        // Usage : color_op_ex <operation> <source1> <source2> [<manual_factor>] [<manual_color1>] [<manual_color2>]
        LayerBlendModeEx    mColorBlendMode;

        //---------------------------------------
        // Command : color_op_multipass_fallback
        // Usage : color_op_multipass_fallback <src_factor> <dest_factor>
        BlendFactor         mColorBlendFallbackSrc;
        BlendFactor         mColorBlendFallbackDst;

        //---------------------------------------
        // Command : env_map
        // Usage : env_map <off|spherical|planar|cubic_reflection|cubic_normal>
        EffectMap           mEffects;

        //---------------------------------------
        // Command : scroll
        // Usage : scroll <x> <y>
        Real                mUOffset;
        Real                mVOffset;

        //---------------------------------------
        // Command : scroll_anim
        // Usage : scroll_anim <xspeed> <yspeed>
        // Parameters : 存储在 mEffects 里

        //---------------------------------------
        // Command : rotate
        // Usage : rotate <angle>
        Radian              mRotate;

        //---------------------------------------
        // Command : rotate_anim
        // Usage : rotate_anim <revs_per_second>
        // Parameters : 存储在 mEffects 里

        //---------------------------------------
        // Command : scale
        // Usage : scale <x_scale> <y_scale>
        Real                mUScale;
        Real                mVScale;

        //---------------------------------------
        // Command : wave_xform
        // Usage : wave_xform <xform_type> <wave_type> <base> <frequency> <phase> <amplitude>
        // Parameters : 存储在 mEffects 里

        //---------------------------------------
        // Command transform
        // Usage : transform m00 m01 m02 m03 m10 m11 m12 m13 m20 m21 m22 m23 m30 m31 m32 m33
        Matrix4             mTexMatrix;
    };
}


#include "T3DTextureUnit.inl"


#endif  /*__T3D_TEXTURE_UNIT_H__*/
