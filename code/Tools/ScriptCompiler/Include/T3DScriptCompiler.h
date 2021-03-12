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

#ifndef __T3D_SCRIPT_COMPILER_H__
#define __T3D_SCRIPT_COMPILER_H__


#include "T3DScriptPrerequisites.h"
#include "T3DScriptASTree.h"


namespace Tiny3D
{
    class ScriptLexer;
    class ScriptParser;
    class ScriptTranslator;
//     class SamplerTranslator;
//     class GPUProgramTranslator;

    class ScriptCompiler
    {
        friend class AbstractTreeBuilder;

    public:
        typedef std::unordered_map<String, uint32_t> IdMap;

        typedef std::list<String> StringList;

        struct Options
        {
            enum Flags
            {
                OPT_PRINT_VERSION   = (1 << 0), /// 输出版本号
                OPT_PRINT_HELP      = (1 << 1), /// 输出帮助信息
                OPT_PROJECT_DIR     = (1 << 2), /// 工程目录
                OPT_OUTPUT_DIR      = (1 << 3), /// 输出文件夹
                OPT_LINK            = (1 << 4), /// 链接所有文件成一个文件
            };

            Options()
                : options(OPT_PRINT_HELP)
                , optimizeLevel(0)
                , enableDebugInfo(false)
                , isBinary(false)
            {

            }

            bool shouldPrintVersion() const
            {
                return (OPT_PRINT_VERSION & options) == OPT_PRINT_VERSION;
            }

            bool shouldPrintUsage() const
            {
                return (OPT_PRINT_HELP & options) == OPT_PRINT_HELP;
            }

            bool needLink() const
            {
                return (OPT_LINK & options) == OPT_LINK;
            }

            bool hasOutputDir() const
            {
                return (OPT_OUTPUT_DIR & options) == OPT_OUTPUT_DIR;
            }

            bool hasProjectDir() const
            {
                return (OPT_PROJECT_DIR & options) == OPT_PROJECT_DIR;
            }

            uint32_t    options;        /**< 编译选项 */
            uint32_t    optimizeLevel;  /**< 优化级别，0 to 3 */
            bool        enableDebugInfo;/**< HLSL转换到目标平台着色器语言时是否输出调试信息 */
            bool        isBinary;       /**< 是否二进制文件 */
            StringList  inFiles;        /**< 输入文件列表 */
            String      projDir;        /**< 工程目录 */
            String      outDir;         /**< 输出文件夹路径 */
            String      outFile;        /**< 连接输出成一个文件时使用的文件名 */
            String      target;         /**< 目标输出平台 */
        };

    public:
        /**
         * @brief 构造函数
         */
        ScriptCompiler();

        /**
         * @brief 析构函数
         */
        virtual ~ScriptCompiler();

        /**
         * @brief 编译脚本
         */
        bool compile(int32_t argc, const char *argv[]);

        /**
         * @brief 转换着色器语言到目标平台语言
         * @param [in] source : 着色器源码文件
         * @param [in] target : 目标平台
         * @param [in] stage : 渲染阶段
         * @param [in] entry : 着色器程序入口
         * @return 转换成功返回true
         */
        bool translate(ObjectAbstractNode *obj, const String &source,
            const String &target, const String &stage, const String &entry);

        /**
         * @brief 获取对应结点翻译器
         */
        ScriptTranslator *getTranslator(const AbstractNodePtr &node) const;

    protected:
        /**
         * @brief 打印使用方法
         */
        void printUsage();

        /**
         * @brief 打印版本号
         */
        void printVersion();

        /**
         * @brief 解析参数
         */
        bool parse(int32_t argc, const char *argv[], Options &opt);

        /**
         * @brief 编译源码，生成二进制码流
         * @param [in] opt : 编译选项
         * @return 编译成功返回true
         */
        bool compile(const Options &opt);

        /**
         * @brief 编译单个脚本文件
         * @param [in] input : 要编译的源码文件
         * @param [in] output : 编译后生成的文件全路径
         * @return 编译成功返回true
         */
        bool compile(const String &input, const String &output);

        /**
         * @brief 链接所有目标文件，生成最终文件
         */
        bool link(const String &outDir, const String &output);

        // 读取输入脚本内容
        bool readSourceFile(String &content, const String &input);

        // 处理导入AST结点
        bool processImports(AbstractNodeList &nodes);

        // 加载导入文件，并且生成对应的抽象语法树
        bool loadImportPath(const String &name, AbstractNodeListPtr &ast);

        // 根据给定的target在nodes中查找到对应的AST
        bool locateTarget(const AbstractNodeList& nodes, const String &target, AbstractNodeList &ast);

        // 处理对象AST结点
        bool processObjects(AbstractNodeList& nodes, const AbstractNodeList &top);

        // 合并基类和子类对象，生成一个完整新对象
        bool overlayObject(const AbstractNode &source, ObjectAbstractNode& dest);

        // 处理变量替换
        bool processVariables(AbstractNodeList& nodes);

        // 对应类型脚本是否包含不符合该脚本类型的对象
        bool isNameExcluded(const ObjectAbstractNode& node, AbstractNode *parent);

        // 初始化操作码
        void initWordMap();

        // 从文件路径中获取文件名
        void getFileName(const String &filepath, String &path, String &name) const;

        // 从完整文件名中获取文件名和文件扩展名
        void getFileTitle(const String &filename, String &title, String &ext) const;

        // 创建脚本转换器
        void initTranslators();

        // 生成目标文件
        bool generateObjectFile(AbstractNodeListPtr &ast, const String &output);

        // 初始化像素格式
        void initPixelFormat();

        // 修正 SpirV-Cross 转成 HLSL 语义字段错误的 bug
        void fixSpirVCrossForHLSLSemantics(String &content);

    protected:
        struct T3DFileHeader
        {
            char        magic[4];       /// 文件标识
            uint32_t    subtype;
            uint32_t    version;        /// 文件版本号
            uint32_t    fileSize;       /// 文件大小
        };

    public:
        IdMap   mIds;
        IdMap   mPixelFormat;

    protected:
        typedef std::map<String, String> Environment;

        typedef std::map<String, AbstractNodeListPtr> ImportCacheMap;
        typedef std::multimap<String, String> ImportRequestMap;

        Environment             mEnv;
        ImportCacheMap          mImports;
        ImportRequestMap        mImportRequests;
        AbstractNodeList        mImportTable;

        ScriptTranslator     *mMaterialTranslator;
        ScriptTranslator     *mTechniqueTranslator;
        ScriptTranslator     *mPassTranslator;
        ScriptTranslator     *mTexUnitTranslator;
        ScriptTranslator     *mSamplerTranslator;
        ScriptTranslator     *mGPUTransltor;

        ScriptLexer             *mLexer;
        ScriptParser            *mParser;

        String                  mShaderModel;
        String                  mTarget;
        String                  mProjDir;   /**< 当前编译文件路径 */
        String                  mOutDir;

        uint32_t                mOptimizationLevel;
        bool                    mEnableDebugInfo;
        bool                    mIsBinary;
    };
}


#endif  /*__T3D_SCRIPT_COMPILER_H__*/
