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


#ifndef __T3D_RENDER_CAPABILITIES_H__
#define __T3D_RENDER_CAPABILITIES_H__

#include <sstream>
#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "T3DErrorDef.h"


namespace Tiny3D
{
    /**
     * @def CAPS_CATEGORY_SIZE
     * @brief   A macro that defines Capabilities category size
     */
    #define CAPS_CATEGORY_SIZE      4
    #define CAPS_BITSHIFT           (32 - CAPS_CATEGORY_SIZE)
    #define CAPS_CATEGORY_MASK      (((1 << CAPS_CATEGORY_SIZE) - 1) << CAPS_BITSHIFT)
    #define CAPS_VALUE(cat, val)    ((cat << CAPS_BITSHIFT) | (1 << val))

    /**
     * @enum    CapabilitiesCategory
     * @brief   能力值分组
     */
    enum CapabilitiesCategory : uint8_t
    {
        COMMON_1 = 0,   /**< 通用组1 */
        COMMON_2,       /**< 通用组2*/
        DIRECTX,        /**< DirectX */
        OPENGL,         /**< OpenGL */
        OPENGLES,       /**< OpenGL ES */
        VULKAN,         /**< Vulkan */
        METAL,          /**< Metal */
        CATEGORY_COUNT  /**< 分组数量 */
    };

    /**
     * @enum    Capabilities
     * @brief   能力值
     */
    enum Capabilities : uint32_t
    {
        /**< 支持通过在索引缓冲中指定 -1 来启动新的渲染命令，在 Geometry Shader 中使用 */
        PRIMITIVE_RESTART = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 0),
        /**< 支持硬件生成压缩格式的 mipmap */
        AUTOMIPMAP_COMPRESSED = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 1),
        /**< 支持各向异性纹理过滤 */
        ANISOTROPY = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 2),
        /**< 支持设置线条宽度 */
        WIDE_LINES = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 3),
        /**< 支持32位索引缓冲 */
        INDEX_32BITS = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 4),
        /**< 支持 Atomic counters 缓冲 */
        ATOMIC_COUNTERS = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 5),
        /**< 支持前后两面模板缓冲独立更新方式 */
        TWO_SIDED_STENCIL = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 6),
        /**< 支持 wrap 模板缓冲值 */
        WRAP_STENCIL = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 7),
        /**< 支持硬件模板缓冲 */
        HWSTENCIL = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 8),
        /**< 硬件 Gamma 校正*/
        HW_GAMMA = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 9),
        /**< 支持硬件遮挡查询 */
        HWOCCLUSION = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 10),
        /**< 支持异步硬件遮挡查询 */
        HWOCCLUSION_ASYNCHRONOUS = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 11),
        /**< 支持渲染到顶点缓冲 */
        HWRENDER_TO_VERTEX_BUFFER = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 12),
        /**< 支持硬件渲染到纹理 */
        HWRENDER_TO_TEXTURE = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 13),
        /**< 支持硬件渲染到体积纹理 */
        HWRENDER_TO_TEXTURE_3D = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 14),
        /**< 支持浮点纹理和渲染目标 */
        TEXTURE_FLOAT = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 15),
        /**< 支持非2幂尺寸的纹理 */
        NON_POWER_OF_2_TEXTURES = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 16),
        /**< 支持体积纹理 */
        TEXTURE_3D = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 17),
        /**< 支持1维纹理 */
        TEXTURE_1D = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 18),
        /**< 支持用户定义裁剪平面 */
        USER_CLIP_PLANES = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 19),
        /**< 支持顶点使用 UBYTE4 格式 */
        VERTEX_FORMAT_UBYTE4 = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 20),
        /**< 支持无穷远平面 */
        INFINITE_FAR_PLANE = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 21),
        /**< 支持点精灵渲染 */
        POINT_SPRITES = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 22),
        /**< 支持点精灵需要的参数 */
        POINT_EXTENDED_PARAMETERS = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 23),
        /**< 支持顶点纹理拾取 */
        VERTEX_TEXTURE_FETCH = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 24),
        /**< 支持 mipmap LOD 偏差 */
        MIPMAP_LOD_BIAS = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 25),
        /**< 支持多渲染目标有不同色深 */
        MRT_DIFFERENT_BIT_DEPTHS = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 26),
        /**< 支持 A2C */
        ALPHA_TO_COVERAGE = CAPS_VALUE(CapabilitiesCategory::COMMON_1, 27),

        /**< 支持主的深度缓冲给渲染到纹理使用 */
        RTT_MAIN_DEPTHBUFFER_ATTACHABLE = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 0),
        /**< 支持宽高小于渲染到纹理的深度缓冲关联到渲染到纹理上使用 */
        RTT_DEPTHBUFFER_RESOLUTION_LESSEQUAL = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 1),
        /**< 支持顶点缓冲存储实例化数据 */
        VERTEX_BUFFER_INSTANCE_DATA = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 2),
        /**< 支持获取编译后着色器缓冲数据 */
        CAN_GET_COMPILED_SHADER_BUFFER = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 3),
        /**< 支持动态链接着色器或者着色器函数 */
        SHADER_SUBROUTINE = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 4),
        /**< 支持 Vertex Shader */
        VERTEX_SHADER = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 5),
        /**< 支持 Pixel Shader */
        PIXEL_SHADER = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 6),
        /**< 支持 Geometry Shader */
        GEOMETRY_SHADER = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 7),
        /**< 支持 Tessellation Hull Shader */
        TESSELLATION_HULL_SHADER = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 8),
        /**< 支持 Tessellation Domain Shader */
        TESSELLATION_DOMAIN_SHADER = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 9),
        /**< 支持 Compute Shader */
        COMPUTE_SHADER = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 10),
        /**< 支持纹理压缩 */
        TEXTURE_COMPRESSION = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 11),
        /**< 支持 DXT (MS DirectX) 纹理压缩 */
        TEXTURE_COMPRESSION_DXT = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 12),
        /**< BC4 和 BC5 格式 (DirectX feature level 10_0) */
        TEXTURE_COMPRESSION_BC4_BC5 = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 13),
        /**< BC6H 和 BC7 格式 (DirectX feature level 11_0) */
        TEXTURE_COMPRESSION_BC6_BC7 = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 14),
        /**< 支持 VTC (体积纹理, OpenGL) 压缩格式 */
        TEXTURE_COMPRESSION_VTC = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 15),
        /**< 支持 PVRTC (PowerVR iOS/Android) 压缩格式 */
        TEXTURE_COMPRESSION_PVRTC = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 16),
        /**< 支持 ASTC (iOS) 压缩格式 */
        TEXTURE_COMPRESSION_ASTC = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 17),
        /**< 支持 ATC (QUALCOMM AMD Adreno) 压缩格式 */
        TEXTURE_COMPRESSION_ATC = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 18),
        /**< 支持 ETC1 (Android) 压缩格式 */
        TEXTURE_COMPRESSION_ETC1 = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 19),
        /**< 支持 ETC2 (Android) 压缩格式 */
        TEXTURE_COMPRESSION_ETC2 = CAPS_VALUE(CapabilitiesCategory::COMMON_2, 20),
        
    };

    /**
     * @enum    GPUVendor
     * @brief   GPU 提供商枚举值
     */
    enum GPUVendor : uint32_t
    {
        UNKNOWN = 0,        /**< 未知设备提供商 */
        NVIDIA,             /**< 英伟达 */
        AMD,                /**< AMD */
        INTEL,              /**< 英特尔 */
        IMAGINATION_TECHNOLOGIES,   /**< Imagination Technologies */
        APPLE,              /**< 苹果软渲染 */
        NOKIA,              /**< 诺基亚 */
        MS_SOFTWARE,        /**< 微软软渲染 */
        MS_WARP,            /**< 微软的高性能软光栅化 WARP (Windows Advanced Rasterization Platform) */
        ARM,                /**< Mali */
        QUALCOMM,           /**< 高通 */
        MOZILLA,            /**< WebGL 基于 Mozilla/Firefox 核浏览器 */
        WEBKIT,             /**< WebGL 基于 WebKit/Chrome 核浏览器 */
        GPU_VENDOR_COUNT    /**< 设备提供商数量 */
    };

    /**
     * @struct  DriverVersion
     * @brief   驱动版本号.
     */
    struct T3D_ENGINE_API DriverVersion
    {
        /**
         * @fn  DriverVersion()
         * @brief   默认构造函数
         */
        DriverVersion() : major(0), minor(0), release(0), build(0)
        {}

        /**
         * @fn  String toString() const
         * @brief   把版本号转换成字符串
         * @return  返回一个字符串类型的版本号.
         */
        String toString() const
        {
            std::stringstream ss;
            ss << major << "." << minor << "." << release << "." << build;
            return ss.str();
        }

        /**
         * @fn  void fromString(const String &str)
         * @brief   从字符串设置版本号
         * @param [in]  str 字符串类型版本号.
         */
        void fromString(const String &str)
        {
            StringArray tokens = StringUtil::split(str, ".");
            if (!tokens.empty())
            {
                major = StringConverter::parseInt32(tokens[0]);
                if (tokens.size() > 1)
                    minor = StringConverter::parseInt32(tokens[1]);
                if (tokens.size() > 2)
                    release = StringConverter::parseInt32(tokens[2]);
                if (tokens.size() > 3)
                    build = StringConverter::parseInt32(tokens[3]);
            }
        }

        int32_t major;      /**< 主版本号 */
        int32_t minor;      /**< 次版本号 */
        int32_t release;    /**< 发布号 */
        int32_t build;      /**< 构建号 */
    };

    /**
     * @class   RendererCapabilities
     * @brief   渲染器能力值组.
     */
    class T3D_ENGINE_API RenderCapabilities : public Object
    {
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  static GPUVendor RendererCapabilities::vendorFromString(
         *      const String &str);
         * @brief   把字符串设备提供商名称转成枚举值
         * @param [in]  str 字符串.
         * @return  返回设备提供商枚举值.
         */
        static GPUVendor vendorFromString(const String &str);

        /**
         * @fn  static String 
         *      RendererCapabilities::vendorToString(GPUVendor vendor);
         * @brief   把枚举值设备提供商转成设备提供商名称
         * @param [in]  vendor  设备提供商枚举值.
         * @return  返回设备提供商名称.
         */
        static String vendorToString(GPUVendor vendor);

        /**
         * @fn  virtual RendererCapabilities::~RendererCapabilities();
         * @brief   析构函数
         */
        virtual ~RenderCapabilities();

        /**
         * @fn  const DriverVersion 
         *      RendererCapabilities::&getDriverVersion() const;
         * @brief   获取驱动版本号
         * @return  返回驱动版本号.
         */
        const DriverVersion &getDriverVersion() const;

        /**
         * @fn  GPUVendor RendererCapabilities::getVendor() const;
         * @brief   获取设备提供商枚举值
         * @return  返回设备提供商枚举值.
         */
        GPUVendor getVendor() const;

        /**
         * @fn  const String RendererCapabilities::&getDeviceName() const;
         * @brief   获取显示适配器名称
         * @return  返回显示适配器名称.
         */
        const String &getDeviceName() const;

        /**
         * @fn  const String RendererCapabilities::&getRendererName() const;
         * @brief   获取渲染器名称
         * @return  返回渲染器名称.
         */
        const String &getRendererName() const;

        /**
         * @fn  uint16_t RendererCapabilities::getNumTextureUnits() const;
         * @brief   获取纹理单元数量上限
         * @return  返回纹理单元数量上限.
         */
        uint16_t getNumTextureUnits() const;

        /**
         * @fn  uint16_t RendererCapabilities::getNumVertexTextureUnits() const;
         * @brief   Gets number vertex texture units
         * @return  The number vertex texture units.
         */
        uint16_t getNumVertexTextureUnits() const;

        /**
         * @fn  uint16_t RendererCapabilities::getStencilBufferBitDepth() const;
         * @brief   Gets stencil buffer bit depth
         * @return  The stencil buffer bit depth.
         */
        uint16_t getStencilBufferBitDepth() const;

        /**
         * @fn  uint16_t RendererCapabilities::getNumVertexBlendMatrices() const;
         * @brief   Gets number vertex blend matrices
         * @return  The number vertex blend matrices.
         */
        uint16_t getNumVertexBlendMatrices() const;

        /**
         * @fn  uint16_t RendererCapabilities::getNumMultiRenderTargets() const;
         * @brief   Gets number multi render targets
         * @return  The number multi render targets.
         */
        uint16_t getNumMultiRenderTargets() const;

        /**
         * @fn  uint16_t RendererCapabilities::getNumVertexAttributes() const;
         * @brief   Gets number vertex attributes
         * @return  The number vertex attributes.
         */
        uint16_t getNumVertexAttributes() const;

        /**
         * @fn  uint16_t RendererCapabilities::getVSConstantFloatCount() const;
         * @brief   Gets vs constant float count
         * @return  The vs constant float count.
         */
        uint16_t getVSConstantFloatCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getVSConstantIntCount() const;
         * @brief   Gets vs constant int count
         * @return  The vs constant int count.
         */
        uint16_t getVSConstantIntCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getVSConstantBoolCount() const;
         * @brief   Gets vs constant bool count
         * @return  The vs constant bool count.
         */
        uint16_t getVSConstantBoolCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getGSConstantFloatCount() const;
         * @brief   Gets gs constant float count
         * @return  The gs constant float count.
         */
        uint16_t getGSConstantFloatCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getGSConstantIntCount() const;
         * @brief   Gets gs constant int count
         * @return  The gs constant int count.
         */
        uint16_t getGSConstantIntCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getGSConstantBoolCount() const;
         * @brief   Gets gs constant bool count
         * @return  The gs constant bool count.
         */
        uint16_t getGSConstantBoolCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getPSConstantFloatCount() const;
         * @brief   Gets ps constant float count
         * @return  The ps constant float count.
         */
        uint16_t getPSConstantFloatCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getPSConstantIntCount() const;
         * @brief   Gets ps constant int count
         * @return  The ps constant int count.
         */
        uint16_t getPSConstantIntCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getPSConstantBoolCount() const;
         * @brief   Gets ps constant bool count
         * @return  The ps constant bool count.
         */
        uint16_t getPSConstantBoolCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getHSConstantFloatCount() const;
         * @brief   Gets hs constant float count
         * @return  The hs constant float count.
         */
        uint16_t getHSConstantFloatCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getHSConstantIntCount() const;
         * @brief   Gets hs constant int count
         * @return  The hs constant int count.
         */
        uint16_t getHSConstantIntCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getHSConstantBoolCount() const;
         * @brief   Gets hs constant bool count
         * @return  The hs constant bool count.
         */
        uint16_t getHSConstantBoolCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getDSConstantFloatCount() const;
         * @brief   Gets ds constant float count
         * @return  The ds constant float count.
         */
        uint16_t getDSConstantFloatCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getDSConstantIntCount() const;
         * @brief   Gets ds constant int count
         * @return  The ds constant int count.
         */
        uint16_t getDSConstantIntCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getDSConstantBoolCount() const;
         * @brief   Gets ds constant bool count
         * @return  The ds constant bool count.
         */
        uint16_t getDSConstantBoolCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getCSConstantFloatCount() const;
         * @brief   Gets create structure constant float count
         * @return  The create structure constant float count.
         */
        uint16_t getCSConstantFloatCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getCSConstantIntCount() const;
         * @brief   Gets create structure constant int count
         * @return  The create structure constant int count.
         */
        uint16_t getCSConstantIntCount() const;

        /**
         * @fn  uint16_t RendererCapabilities::getCSConstantBoolCount() const;
         * @brief   Gets create structure constant bool count
         * @return  The create structure constant bool count.
         */
        uint16_t getCSConstantBoolCount() const;

        /**
         * @fn  int32_t RendererCapabilities::getGSNumOutputVertices() const;
         * @brief   Gets gs number output vertices
         * @return  The gs number output vertices.
         */
        int32_t getGSNumOutputVertices() const;

        /**
         * @fn  Real RendererCapabilities::getMaxPointSize() const;
         * @brief   Gets maximum point size
         * @return  The maximum point size.
         */
        Real getMaxPointSize() const;

        /**
         * @fn  Real RendererCapabilities::getMaxAnisotropy() const;
         * @brief   Gets maximum anisotropy
         * @return  The maximum anisotropy.
         */
        Real getMaxAnisotropy() const;

        /**
         * @fn  bool RendererCapabilities::isNPOTLimited() const;
         * @brief   Query if this object is npot limited
         * @return  True if npot limited, false if not.
         */
        bool isNPOTLimited() const;

        /**
         * @fn  bool RendererCapabilities::hasCapabilities(
         *      Capabilities cap) const;
         * @brief   Query if 'cap' has capabilities
         * @param   cap The capability.
         * @return  True if capabilities, false if not.
         */
        bool hasCapabilities(Capabilities cap) const;

        /**
         * @fn  bool RendererCapabilities::isCapabilityRendererSpecific(
         *      Capabilities cap) const;
         * @brief   Query if 'cap' is capability renderer specific
         * @param   cap The capability.
         * @return  True if capability renderer specific, false if not.
         */
        bool isCapabilityRendererSpecific(Capabilities cap) const;

    protected:
        /**
         * @fn  RendererCapabilities::RendererCapabilities();
         * @brief   Default constructor
         */
        RenderCapabilities();

        /**
         * @fn  virtual TResult RendererCapabilities::init() = 0;
         * @brief   Initializes this object
         * @return  A TResult.
         */
        virtual TResult init() = 0;

        /**
         * @fn  void RendererCapabilities::setCapabiliy(Capabilities cap);
         * @brief   Sets a capability
         * @param   cap The capability.
         */
        void setCapability(Capabilities cap);

        /**
         * @fn  void RendererCapabilities::unsetCapability(Capabilities cap);
         * @brief   Unset capability
         * @param   cap The capability.
         */
        void unsetCapability(Capabilities cap);

        /**
         * @fn  static void RendererCapabilities::initVendorStrings();
         * @brief   Initializes the vendor strings
         */
        static void initVendorStrings();

    protected:
        static String GPUVendorStrings[GPU_VENDOR_COUNT];   /**< GPU提供商字符串列表 */

        DriverVersion   mDriverVersion;     /**< 驱动版本号 */
        GPUVendor       mVendor;            /**< GPU 厂商 */

        String      mDeviceName;            /**< 设备名称 */
        String      mRendererName;          /**< 渲染器名称 */

        uint16_t    mNumTextureUnits;       /**< 可用纹理单元数量 */
        uint16_t    mNumVertexTextureUnits; /**< 顶点纹理单元数量 */
        uint16_t    mStencilBufferBitDepth; /**< 模板缓冲色深 */
        uint16_t    mNumVertexBlendMatrices;/**< 用于硬件混合的矩阵数量 */
        uint16_t    mNumMultiRenderTargets; /**< 同时渲染目标的最大数量 */
        uint16_t    mNumVertexAttributes;   /**< 可用的顶点属性数量 */

        uint16_t    mVSConstantFloatCount;  /**< Vertex Shader 支持常量缓冲中浮点数数量 */
        uint16_t    mVSConstantIntCount;    /**< Vertex Shader 支持常量缓冲中整型数数量 */
        uint16_t    mVSConstantBoolCount;   /**< Vertex Shader 支持常量缓冲中布尔数数量 */
        uint16_t    mGSConstantFloatCount;  /**< Geometry Shader 支持常量缓冲中浮点数数量 */
        uint16_t    mGSConstantIntCount;    /**< Geometry Shader 支持常量缓冲中整型数数量 */
        uint16_t    mGSConstantBoolCount;   /**< Geometry Shader 支持常量缓冲中布尔数数量 */
        uint16_t    mPSConstantFloatCount;  /**< Pixel Shader 支持常量缓冲中浮点数数量 */
        uint16_t    mPSConstantIntCount;    /**< Pixel Shader 支持常量缓冲中整型数数量 */
        uint16_t    mPSConstantBoolCount;   /**< Pixel Shader 支持常量缓冲中布尔数数量 */
        uint16_t    mHSConstantFloatCount;  /**< Hull Shader 支持常量缓冲中浮点数数量 */
        uint16_t    mHSConstantIntCount;    /**< Hull Shader 支持常量缓冲中整型数数量 */
        uint16_t    mHSConstantBoolCount;   /**< Hull Shader 支持常量缓冲中布尔数数量 */
        uint16_t    mDSConstantFloatCount;  /**< Domain Shader 支持常量缓冲中浮点数数量 */
        uint16_t    mDSConstantIntCount;    /**< Domain Shader 支持常量缓冲中整型数数量 */
        uint16_t    mDSConstantBoolCount;   /**< Domain Shader 支持常量缓冲中布尔数数量 */
        uint16_t    mCSConstantFloatCount;  /**< Compute Shader 支持常量缓冲中浮点数数量 */
        uint16_t    mCSConstantIntCount;    /**< Compute Shader 支持常量缓冲中整型数数量 */
        uint16_t    mCSConstantBoolCount;   /**< Compute Shader 支持常量缓冲中布尔数数量 */

        int32_t     mGSNumOutputVertices;   /**< 几何着色器一次运行能输出最大顶点数量 */

        Real        mMaxPointSize;          /**< 点大小最大值 */
        Real        mMaxAnisotropy;         /**< 各向异性最大值 */
        bool        mNPOTLimited;           /**< 是否支持非2幂纹理 */

        uint32_t    mCapabilities[CATEGORY_COUNT];      /**< 能力值 */
        bool        mCategoryRelevant[CATEGORY_COUNT];  /**< 对应的能力值开启标记 */
    };
}


#include "T3DRenderCapabilities.inl"


#endif  /*__T3D_RENDER_CAPABILITIES_H__*/
