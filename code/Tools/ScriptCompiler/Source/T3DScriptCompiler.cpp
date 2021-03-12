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


#include "T3DScriptCompiler.h"
#include "T3DScriptLexer.h"
#include "T3DScriptParser.h"
#include "T3DScriptError.h"
#include "T3DScriptTranslator.h"
#include "FileScriptObject.pb.h"
#include <google/protobuf/util/json_util.h>

namespace Tiny3D
{
    #define SCC_VERSION_00000100            0x00000100
    #define SCC_CURRENT_VERSION             SCC_VERSION_00000100
    #define T3D_FILE_MAGIC                  "T3D"
    #define T3D_FILE_SUBTYPE_SCC            0x00000001

    //--------------------------------------------------------------------------

    ScriptCompiler::ScriptCompiler()
        : mMaterialTranslator(nullptr)
        , mTechniqueTranslator(nullptr)
        , mPassTranslator(nullptr)
        , mTexUnitTranslator(nullptr)
        , mSamplerTranslator(nullptr)
        , mGPUTransltor(nullptr)
        , mLexer(nullptr)
        , mParser(nullptr)
        , mOptimizationLevel(0)
        , mEnableDebugInfo(true)
        , mIsBinary(false)
    {
        mLexer = new ScriptLexer();
        mParser = new ScriptParser(this);

        initWordMap();
        initPixelFormat();
        initTranslators();
    }

    //--------------------------------------------------------------------------

    ScriptCompiler::~ScriptCompiler()
    {
        delete mPassTranslator;
        delete mTechniqueTranslator;
        delete mMaterialTranslator;
        delete mTexUnitTranslator;
        delete mSamplerTranslator;

        delete mLexer;
        mLexer = nullptr;

        delete mParser;
        mParser = nullptr;
    }

    //--------------------------------------------------------------------------

    void ScriptCompiler::initTranslators()
    {
        mMaterialTranslator = new MaterialTranslator();
        mTechniqueTranslator = new TechniqueTranslator();
        mPassTranslator = new PassTranslator();
        mTexUnitTranslator = new TextureUnitTranslator();
        mSamplerTranslator = new SamplerTranslator();
        mGPUTransltor = new GPUProgramTranslator();
    }

    //--------------------------------------------------------------------------

    ScriptTranslator *ScriptCompiler::getTranslator(const AbstractNodePtr &node) const
    {
        ScriptTranslator *translator = nullptr;

        if (node->type == ANT_OBJECT)
        {
            ObjectAbstractNode *obj = static_cast<ObjectAbstractNode*>(node.get());
            ObjectAbstractNode *parent = obj->parent ? static_cast<ObjectAbstractNode*>(obj->parent) : nullptr;
            if (obj->id == ID_MATERIAL)
            {
                translator = mMaterialTranslator;
            }
            else if (obj->id == ID_TECHNIQUE)
            {
                translator = mTechniqueTranslator;
            }
            else if (obj->id == ID_PASS)
            {
                translator = mPassTranslator;
            }
            else if (obj->id == ID_TEXTURE_UNIT)
            {
                translator = mTexUnitTranslator;
            }
            else if (obj->id == ID_SAMPLER)
            {
                translator = mSamplerTranslator;
            }
            else if (obj->id == ID_FRAGMENT_PROGRAM ||
                obj->id == ID_VERTEX_PROGRAM ||
                obj->id == ID_GEOMETRY_PROGRAM ||
                obj->id == ID_TESSELLATION_HULL_PROGRAM ||
                obj->id == ID_TESSELLATION_DOMAIN_PROGRAM ||
                obj->id == ID_COMPUTE_PROGRAM)
            {
                translator = mGPUTransltor;
            }
            else if (obj->id == ID_VERTEX_PROGRAM_REF
                || obj->id == ID_FRAGMENT_PROGRAM_REF
                || obj->id == ID_GEOMETRY_PROGRAM_REF
                || obj->id == ID_TESSELLATION_HULL_PROGRAM_REF
                || obj->id == ID_TESSELLATION_DOMAIN_PROGRAM_REF
                || obj->id == ID_COMPUTE_PROGRAM_REF
                || obj->id == ID_SHADOW_CASTER_VERTEX_PROGRAM_REF
                || obj->id == ID_SHADOW_CASTER_FRAGMENT_PROGRAM_REF)
            {
                translator = mGPUTransltor;
            }
            else if (obj->id == ID_GPU_PROGRAM
                || obj->id == ID_GPU_PROGRAM_REF
                || obj->id == ID_GPU_CBUFFER
                || obj->id == ID_GPU_CBUFFER_REF)
            {
                translator = mGPUTransltor;
            }
        }
        else if (node->type == ANT_PROPERTY)
        {
            PropertyAbstractNode *prop = static_cast<PropertyAbstractNode*>(node.get());

            switch (prop->id)
            {
            case ID_TEX_ADDRESS_MODE:
            case ID_TEX_BORDER_COLOUR:
            case ID_FILTERING:
            case ID_CMPTEST:
            case ID_CMPFUNC:
            case ID_COMP_FUNC:
            case ID_MAX_ANISOTROPY:
            case ID_MIPMAP_BIAS:
                translator = mSamplerTranslator;
                break;
            }
        }

        return translator;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::compile(int32_t argc, const char *argv[])
    {
        bool ret = false;

        do 
        {
            Options opt;
            ret = parse(argc, argv, opt);
            if (!ret)
            {
                printUsage();
                break;
            }

            if (opt.shouldPrintUsage())
            {
                printUsage();
                break;
            }
            else if (opt.shouldPrintVersion())
            {
                printVersion();
            }
            else
            {
                ret = compile(opt);
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void ScriptCompiler::printUsage()
    {
        printf("Usage : ");
        printf("  scc input_files -t target -m [options]");
        printf("    input_files : The source file.");
        printf("    -t : Target shading language : glsl, hlsl, essl, dxil, spirv, msl_macos, msl_ios");
        printf("    -m : Set the shader model version.");
        printf("    Options : ");
        printf("      -v : Print version.");
        printf("      -h : Print help.");
        printf("      -p : Set the directory of the project. If this options is set, all input files in the list will be relative path.");
        printf("      -d : Set the directory of output files. If \'-p\' is set, this path will be relative to the project path.");
        printf("      -l : Set the link file and link all script binary file (*.tsc) to one file. Default is not linking.");
        printf("      -On : n is the optimization level from 0 to 3.");
        printf("      -D : Translate high level shader language to target shader language with debug information.");
        printf("      -b : Output file in binary file format. Default is json file format.");
    }

    //--------------------------------------------------------------------------

    void ScriptCompiler::printVersion()
    {
        printf("Version : %s", CURRENT_VERSION_STR);
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::parse(int32_t argc, const char *argv[], Options &opt)
    {
        bool ret = true;

        opt.options = 0;

        do 
        {
            if (argc == 0)
            {
                // 没参数，只能直接打印帮助，让用户知道如何使用
                opt.options = Options::OPT_PRINT_HELP;
                break;
            }

            int i = 0;

            while (i < argc)
            {
                if (strcmp(argv[i], "-h") == 0)
                {
                    // 打印帮助信息
                    opt.options = Options::OPT_PRINT_HELP;
                }
                else if (strcmp(argv[i], "-v") == 0)
                {
                    // 打印版本号
                    opt.options = Options::OPT_PRINT_VERSION;
                }
                else if (strcmp(argv[i], "-p") == 0)
                {
                    // 设置工程目录
                    opt.options |= Options::OPT_PROJECT_DIR;

                    if (argc - 1 == i)
                    {
                        // 参数不够
                        T3D_LOG_ERROR(LOG_TAG, "Missing project directory !");
                        ret = false;
                        break;
                    }

                    ++i;
                    opt.projDir = argv[i];
                }
                else if (strcmp(argv[i], "-l") == 0)
                {
                    // 设置输出文件名
                    opt.options |= Options::OPT_LINK;

                    if (argc - 1 == i)
                    {
                        // 参数不够
                        T3D_LOG_ERROR(LOG_TAG, "Missing linking file name (*.tsc) !");
                        ret = false;
                        break;
                    }

                    ++i;
                    opt.outFile = argv[i];
                }
                else if (strcmp(argv[i], "-d") == 0)
                {
                    // 设置输出文件夹
                    opt.options |= Options::OPT_OUTPUT_DIR;

                    if (argc - 1 == i)
                    {
                        // 参数不够
                        T3D_LOG_ERROR(LOG_TAG, "Missing output directory for link file !");
                        ret = false;
                        break;
                    }

                    ++i;
                    opt.outDir = argv[i];
                }
                else if (strcmp(argv[i], "-t") == 0)
                {
                    if (argc - 1 == i)
                    {
                        // 参数不够
                        T3D_LOG_ERROR(LOG_TAG, "Missing target !");
                        ret = false;
                        break;
                    }

                    ++i;
                    opt.target = argv[i];
                    mTarget = opt.target;
                }
                else if (strcmp(argv[i], "-m") == 0)
                {
                    if (argc - 1 == i)
                    {
                        // 参数不够
                        T3D_LOG_ERROR(LOG_TAG, "Missing shader model !");
                        ret = false;
                        break;
                    }

                    ++i;
                    mShaderModel = argv[i];
                }
                else if (strncmp(argv[i], "-O", 2) == 0)
                {
                    opt.optimizeLevel = atoi(argv[i] + 2);
                }
                else if (strcmp(argv[i], "-D") == 0)
                {
                    opt.enableDebugInfo = true;
                }
                else if (strcmp(argv[i], "-b") == 0)
                {
                    opt.isBinary = true;
                }
                else
                {
                    // 输入文件列表
                    opt.inFiles.push_back(argv[i]);
                }

                ++i;
            }

            if (!ret)
            {
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::compile(const Options &opt)
    {
        bool ret = false;

        T3D_LOG_INFO(LOG_TAG, "1>---------- Build started: ----------");

        size_t success = 0;
        size_t failure = 0;

        do 
        {
            String outDir;

            auto itr = opt.inFiles.begin();

            for (itr = opt.inFiles.begin(); itr != opt.inFiles.end(); ++itr)
            {
                // 构造输入文件完整路径
                String input;
                if (opt.hasProjectDir())
                {
                    input = opt.projDir + "/" + *itr;
                }
                else
                {
                    input = *itr;
                }

                // 解析出路径、文件名、文件扩展名
                String path;
                String filename;
                getFileName(input, path, filename);
                String title;
                String ext;
                getFileTitle(filename, title, ext);

                // 保存当前源码路径，用于后续import的导入依赖脚本源码文件
                mProjDir = path;

                T3D_LOG_INFO(LOG_TAG, "1>%s compiling ...", filename.c_str());

                String output;
                if (opt.hasOutputDir())
                {
                    output = opt.outDir + "/" + title + ".t3d";
                    outDir = opt.outDir;
                    mOutDir = outDir;
                }
                else
                {
                    output = path + "/" + title + ".t3d";
                    outDir = path;
                    mOutDir = path;
                }

                // 如果优化开启，则忽略调试信息，自动关闭调试信息
                if (opt.optimizeLevel != 0)
                {
                    mEnableDebugInfo = false;
                }
                else
                {
                    mEnableDebugInfo = opt.enableDebugInfo;
                }

                mOptimizationLevel = opt.optimizeLevel;

                mIsBinary = opt.isBinary;

                ret = compile(input, output);
                if (!ret)
                {
                    // 失败了
                    failure++;
                    T3D_LOG_INFO(LOG_TAG, "1>%s compiling failed !", filename.c_str());
                }
                else
                {
                    success++;
                    T3D_LOG_INFO(LOG_TAG, "1>%s compiling done !", filename.c_str());
                }
            }

            if (!ret)
            {
                // 编译失败了
                break;
            }

            // 链接
            if (opt.needLink())
            {
                String output = outDir + "/" + opt.outFile;
                ret = link(outDir, output);
            }
        } while (0);

        T3D_LOG_INFO(LOG_TAG, "========== Build: %d succeeded , %d failed ==========", success, failure);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::compile(const String &input, const String &output)
    {
        bool ret = false;

        do
        {
            // 读取源码
            String content;
            ret = readSourceFile(content, input);
            if (!ret)
            {
                break;
            }

            // 词法分析
            TokenListPtr tokens = ScriptLexer::getInstance().tokenize(content, input);

            // 语法分析
            AbstractNodeListPtr ast;
            ret = ScriptParser::getInstance().parse(tokens, ast);
            if (!ret)
            {
                break;
            }

            // 处理导入模块
            ret = processImports(*ast);
            if (!ret)
            {
                break;
            }

            // 处理对象，主要是处理对象继承属性
            ret = processObjects(*ast, *ast);
            if (!ret)
            {
                break;
            }

            // 处理变量，替换掉变量
            ret = processVariables(*ast);
            if (!ret)
            {
                break;
            }

            ret = generateObjectFile(ast, output);
            if (!ret)
            {
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::link(const String &outDir, const String &output)
    {
        bool ret = false;

        do 
        {
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::readSourceFile(String &content, const String &input)
    {
        bool ret = false;

        FileDataStream fs;
        uint8_t *data = nullptr;

        do 
        {
            if (!Dir::exists(input))
            {
                T3D_LOG_ERROR("Compiler", "%s does not exist !", input.c_str());
                ret = false;
                break;
            }

            // 打开文件
            if (!fs.open(input.c_str(), FileDataStream::E_MODE_READ_ONLY))
            {
                T3D_LOG_ERROR("Compiler", "Open %s failed !", input.c_str());
                ret = false;
                break;
            }

            // 读取文件
            size_t size = (size_t)fs.size();
            data = new uint8_t[size];
            size_t bytesOfRead = fs.read(data, size);
            if (size != bytesOfRead)
            {
                T3D_LOG_ERROR("Compiler", "Read %s data failed !", input.c_str());
                ret = false;
                break;
            }

            fs.close();

            content.assign((const char *)data, size);

            delete[]data;
            data = nullptr;

            ret = true;
        } while (0);


        if (fs.isOpened())
        {
            fs.close();
        }

        if (data != nullptr)
        {
            delete[]data;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::processImports(AbstractNodeList &nodes)
    {
        bool ret = true;

        // We only need to iterate over the top-level of nodes
        AbstractNodeList::iterator i = nodes.begin();
        while (i != nodes.end())
        {
            // We move to the next node here and save the current one.
            // If any replacement happens, then we are still assured that
            // i points to the node *after* the replaced nodes, no matter
            // how many insertions and deletions may happen
            AbstractNodeList::iterator cur = i++;
            if ((*cur)->type == ANT_IMPORT)
            {
                ImportAbstractNode *import = (ImportAbstractNode*)(*cur).get();
                // Only process if the file's contents haven't been loaded
                if (mImports.find(import->source) == mImports.end())
                {
                    // Load the script
                    AbstractNodeListPtr importedNodes;
                    ret  = loadImportPath(import->source, importedNodes);
                    if (ret && importedNodes && !importedNodes->empty())
                    {
                        processImports(*importedNodes);
                        processObjects(*importedNodes, *importedNodes);
                    }
                    if (ret && importedNodes && !importedNodes->empty())
                        mImports.insert(std::make_pair(import->source, importedNodes));
                }

                // Handle the target request now
                // If it is a '*' import we remove all previous requests and just use the '*'
                // Otherwise, ensure '*' isn't already registered and register our request
                if (import->target == "*")
                {
                    mImportRequests.erase(mImportRequests.lower_bound(import->source),
                        mImportRequests.upper_bound(import->source));
                    mImportRequests.insert(std::make_pair(import->source, "*"));
                }
                else
                {
                    ImportRequestMap::iterator iter = mImportRequests.lower_bound(import->source),
                        end = mImportRequests.upper_bound(import->source);
                    if (iter == end || iter->second != "*")
                    {
                        mImportRequests.insert(std::make_pair(import->source, import->target));
                    }
                }

                nodes.erase(cur);
            }
        }

        // All import nodes are removed
        // We have cached the code blocks from all the imported scripts
        // We can process all import requests now
        for (ImportCacheMap::iterator it = mImports.begin(); it != mImports.end(); ++it)
        {
            ImportRequestMap::iterator j = mImportRequests.lower_bound(it->first),
                end = mImportRequests.upper_bound(it->first);
            if (j != end)
            {
                if (j->second == "*")
                {
                    // Insert the entire AST into the import table
                    mImportTable.insert(mImportTable.begin(), it->second->begin(), it->second->end());
                    continue; // Skip ahead to the next file
                }
                else
                {
                    for (; j != end; ++j)
                    {
                        // Locate this target and insert it into the import table
                        AbstractNodeList newNodes;
                        ret = locateTarget(*it->second, j->second, newNodes);
                        if (ret && !newNodes.empty())
                            mImportTable.insert(mImportTable.begin(), newNodes.begin(), newNodes.end());
                    }
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::loadImportPath(const String &name, AbstractNodeListPtr &ast)
    {
        AbstractNodeListPtr retval;
        ConcreteNodeListPtr nodes;

        bool ret = false;

        do 
        {
            String input = mProjDir + "/" + name;
            String content;
            ret = readSourceFile(content, input);
            if (!ret)
            {
                break;
            }

            // 词法分析
            TokenListPtr tokens = ScriptLexer::getInstance().tokenize(content, input);

            // 语法分析
            ret = ScriptParser::getInstance().parse(tokens, ast);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::locateTarget(const AbstractNodeList& nodes, const String &target, AbstractNodeList &ast)
    {
        auto iter = nodes.end();

        // Search for a top-level object node
        for (auto i = nodes.begin(); i != nodes.end(); ++i)
        {
            if ((*i)->type == ANT_OBJECT)
            {
                ObjectAbstractNode *impl = (ObjectAbstractNode*)(*i).get();
                if (impl->name == target)
                    iter = i;
            }
        }

        if (iter != nodes.end())
        {
            ast.push_back(*iter);
        }

        return true;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::processObjects(AbstractNodeList& nodes, const AbstractNodeList &top)
    {
        bool ret = true;

        for (AbstractNodeList::iterator i = nodes.begin(); i != nodes.end(); ++i)
        {
            if ((*i)->type == ANT_OBJECT)
            {
                ObjectAbstractNode *obj = (ObjectAbstractNode*)(*i).get();

                // Overlay base classes in order.
                for (std::vector<String>::const_iterator baseIt = obj->bases.begin(), end_it = obj->bases.end(); baseIt != end_it; ++baseIt)
                {
                    const String& base = *baseIt;
                    // Check the top level first, then check the import table
                    AbstractNodeList newNodes;
                    ret = locateTarget(top, base, newNodes);
                    if (ret && newNodes.empty())
                        ret = locateTarget(mImportTable, base, newNodes);

                    if (ret && !newNodes.empty()) 
                    {
                        for (AbstractNodeList::iterator j = newNodes.begin(); j != newNodes.end(); ++j) 
                        {
                            ret = overlayObject(**j, *obj);
                        }
                    }
                    else 
                    {
                        ScriptError::printError(CERR_OBJECTBASENOTFOUND, base, obj->file, obj->line);
                    }
                }

                // Recurse into children
                ret = processObjects(obj->children, top);
                if (!ret)
                {
                    break;
                }

                // Overrides now exist in obj's overrides list. These are non-object nodes which must now
                // Be placed in the children section of the object node such that overriding from parents
                // into children works properly.
                obj->children.insert(obj->children.begin(), obj->overrides.begin(), obj->overrides.end());
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::overlayObject(const AbstractNode &source, ObjectAbstractNode& dest)
    {
        bool ret = true;

        if (source.type == ANT_OBJECT)
        {
            const ObjectAbstractNode& src = static_cast<const ObjectAbstractNode&>(source);

            // Overlay the environment of one on top the other first
            for (std::map<String, String>::const_iterator i = src.getVariables().begin(); i != src.getVariables().end(); ++i)
            {
                std::pair<bool, String> var = dest.getVariable(i->first);
                if (!var.first)
                    dest.setVariable(i->first, i->second);
            }

            // Create a vector storing each pairing of override between source and destination
            std::vector<std::pair<AbstractNodePtr, AbstractNodeList::iterator> > overrides;
            // A list of indices for each destination node tracks the minimum
            // source node they can index-match against
            std::map<ObjectAbstractNode*, size_t> indices;
            // A map storing which nodes have overridden from the destination node
            std::map<ObjectAbstractNode*, bool> overridden;

            // Fill the vector with objects from the source node (base)
            // And insert non-objects into the overrides list of the destination
            AbstractNodeList::iterator insertPos = dest.children.begin();
            for (AbstractNodeList::const_iterator i = src.children.begin(); i != src.children.end(); ++i)
            {
                if ((*i)->type == ANT_OBJECT)
                {
                    overrides.push_back(std::make_pair(*i, dest.children.end()));
                }
                else
                {
                    AbstractNodePtr newNode((*i)->clone());
                    newNode->parent = &dest;
                    dest.overrides.push_back(newNode);
                }
            }

            // Track the running maximum override index in the name-matching phase
            size_t maxOverrideIndex = 0;

            // Loop through destination children searching for name-matching overrides
            for (AbstractNodeList::iterator i = dest.children.begin(); i != dest.children.end(); )
            {
                if ((*i)->type == ANT_OBJECT)
                {
                    // Start tracking the override index position for this object
                    size_t overrideIndex = 0;

                    ObjectAbstractNode *node = static_cast<ObjectAbstractNode*>((*i).get());
                    indices[node] = maxOverrideIndex;
                    overridden[node] = false;

                    // special treatment for materials with * in their name
                    bool nodeHasWildcard = node->name.find('*') != String::npos;

                    // Find the matching name node
                    for (size_t j = 0; j < overrides.size(); ++j)
                    {
                        ObjectAbstractNode *temp = static_cast<ObjectAbstractNode*>(overrides[j].first.get());
                        // Consider a match a node that has a wildcard and matches an input name
                        bool wildcardMatch = nodeHasWildcard &&
                            (StringUtil::match(temp->name, node->name, true) ||
                            (node->name.size() == 1 && temp->name.empty()));
                        if (temp->cls == node->cls && !node->name.empty() && (temp->name == node->name || wildcardMatch))
                        {
                            // Pair these two together unless it's already paired
                            if (overrides[j].second == dest.children.end())
                            {
                                AbstractNodeList::iterator currentIterator = i;
                                ObjectAbstractNode *currentNode = node;
                                if (wildcardMatch)
                                {
                                    //If wildcard is matched, make a copy of current material and put it before the iterator, matching its name to the parent. Use same reinterpret cast as above when node is set
                                    AbstractNodePtr newNode((*i)->clone());
                                    currentIterator = dest.children.insert(currentIterator, newNode);
                                    currentNode = static_cast<ObjectAbstractNode*>((*currentIterator).get());
                                    currentNode->name = temp->name;//make the regex match its matcher
                                }
                                overrides[j] = std::make_pair(overrides[j].first, currentIterator);
                                // Store the max override index for this matched pair
                                overrideIndex = j;
                                overrideIndex = maxOverrideIndex = std::max(overrideIndex, maxOverrideIndex);
                                indices[currentNode] = overrideIndex;
                                overridden[currentNode] = true;
                            }
                            else
                            {
                                ScriptError::printError(CERR_DUPLICATEOVERRIDE, node->cls, node->file, node->line);
                            }

                            if (!wildcardMatch)
                                break;
                        }
                    }

                    if (nodeHasWildcard)
                    {
                        //if the node has a wildcard it will be deleted since it was duplicated for every match
                        AbstractNodeList::iterator deletable = i++;
                        dest.children.erase(deletable);
                    }
                    else
                    {
                        ++i; //Behavior in absence of regex, just increment iterator
                    }
                }
                else
                {
                    ++i; //Behavior in absence of replaceable object, just increment iterator to find another
                }
            }

            // Now make matches based on index
            // Loop through destination children searching for index-matching overrides
            for (AbstractNodeList::iterator i = dest.children.begin(); i != dest.children.end(); ++i)
            {
                if ((*i)->type == ANT_OBJECT)
                {
                    ObjectAbstractNode *node = static_cast<ObjectAbstractNode*>((*i).get());
                    if (!overridden[node])
                    {
                        // Retrieve the minimum override index from the map
                        size_t overrideIndex = indices[node];

                        if (overrideIndex < overrides.size())
                        {
                            // Search for minimum matching override
                            for (size_t j = overrideIndex; j < overrides.size(); ++j)
                            {
                                ObjectAbstractNode *temp = static_cast<ObjectAbstractNode*>(overrides[j].first.get());
                                if (temp->name.empty() && node->name.empty() && temp->cls == node->cls && overrides[j].second == dest.children.end())
                                {
                                    overrides[j] = std::make_pair(overrides[j].first, i);
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            // Loop through overrides, either inserting source nodes or overriding
            insertPos = dest.children.begin();
            for (size_t i = 0; i < overrides.size(); ++i)
            {
                if (overrides[i].second != dest.children.end())
                {
                    // Override the destination with the source (base) object
                    ret = overlayObject(*overrides[i].first,
                        static_cast<ObjectAbstractNode&>(**overrides[i].second));
                    insertPos = overrides[i].second;
                    insertPos++;
                }
                else
                {
                    // No override was possible, so insert this node at the insert position
                    // into the destination (child) object
                    AbstractNodePtr newNode(overrides[i].first->clone());
                    newNode->parent = &dest;
                    if (insertPos != dest.children.end())
                    {
                        dest.children.insert(insertPos, newNode);
                    }
                    else
                    {
                        dest.children.push_back(newNode);
                    }
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::processVariables(AbstractNodeList& nodes)
    {
        bool ret = true;

        AbstractNodeList::iterator i = nodes.begin();
        while (i != nodes.end())
        {
            AbstractNodeList::iterator cur = i;
            ++i;

            if ((*cur)->type == ANT_OBJECT)
            {
                // Only process if this object is not abstract
                ObjectAbstractNode *obj = (ObjectAbstractNode*)(*cur).get();
                if (!obj->abstrct)
                {
                    ret = processVariables(obj->children);
                    if (!ret)
                        break;
                    ret = processVariables(obj->values);
                    if (!ret)
                        break;
                }
            }
            else if ((*cur)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode *prop = (PropertyAbstractNode*)(*cur).get();
                ret = processVariables(prop->values);
                if (!ret)
                    break;
            }
            else if ((*cur)->type == ANT_VARIABLE_ACCESS)
            {
                VariableAccessAbstractNode *var = (VariableAccessAbstractNode*)(*cur).get();

                // Look up the enclosing scope
                ObjectAbstractNode *scope = 0;
                AbstractNode *temp = var->parent;
                while (temp)
                {
                    if (temp->type == ANT_OBJECT)
                    {
                        scope = (ObjectAbstractNode*)temp;
                        break;
                    }
                    temp = temp->parent;
                }

                // Look up the variable in the environment
                std::pair<bool, String> varAccess;
                if (scope)
                    varAccess = scope->getVariable(var->name);
                if (!scope || !varAccess.first)
                {
                    std::map<String, String>::iterator k = mEnv.find(var->name);
                    varAccess.first = k != mEnv.end();
                    if (varAccess.first)
                        varAccess.second = k->second;
                }

                if (varAccess.first)
                {
                    // Found the variable, so process it and insert it into the tree
                    AbstractNodeListPtr ast;
                    TokenListPtr tokens = ScriptLexer::getInstance().tokenize(varAccess.second, var->file);
                    ret = ScriptParser::getInstance().parseChunk(tokens, ast);
                    if (!ret)
                    {
                        break;
                    }

                    // Set up ownership for these nodes
                    for (AbstractNodeList::iterator j = ast->begin(); j != ast->end(); ++j)
                        (*j)->parent = var->parent;

                    // Recursively handle variable accesses within the variable expansion
                    ret = processVariables(*ast);
                    if (!ret)
                        break;

                    // Insert the nodes in place of the variable
                    nodes.insert(cur, ast->begin(), ast->end());
                }
                else
                {
                    // Error
                    ScriptError::printError(CERR_UNDEFINEDVARIABLE, var->name, var->file, var->line);
                    ret = false;
                    break;
                }

                // Remove the variable node
                nodes.erase(cur);
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::isNameExcluded(const ObjectAbstractNode& node, AbstractNode* parent)
    {
        // Run past the listener
        bool excludeName = false;

        // Process the built-in name exclusions
        if (node.id == ID_EMITTER || node.id == ID_AFFECTOR)
        {
            // emitters or affectors inside a particle_system are excluded
            while (parent && parent->type == ANT_OBJECT)
            {
                ObjectAbstractNode *obj = static_cast<ObjectAbstractNode*>(parent);
                if (obj->id == ID_PARTICLE_SYSTEM)
                    return true;
                parent = obj->parent;
            }
        }
        else if (node.id == ID_PASS)
        {
            // passes inside compositors are excluded
            while (parent && parent->type == ANT_OBJECT)
            {
                ObjectAbstractNode *obj = static_cast<ObjectAbstractNode*>(parent);
                if (obj->id == ID_COMPOSITOR)
                    return true;
                parent = obj->parent;
            }
        }
        else if (node.id == ID_TEXTURE_SOURCE)
        {
            // Parent must be texture_unit
            while (parent && parent->type == ANT_OBJECT)
            {
                ObjectAbstractNode *obj = static_cast<ObjectAbstractNode*>(parent);
                if (obj->id == ID_TEXTURE_UNIT)
                    return true;
                parent = obj->parent;
            }
        }

        return false;
    }

    bool ScriptCompiler::generateObjectFile(AbstractNodeListPtr &ast, const String &output)
    {
        bool ret = false;

        do 
        {
            MemoryDataStream stream(10*1024*1024);

            uint8_t *buffer = nullptr;
            size_t bufSize = 0;
            stream.getBuffer(buffer, bufSize);

            uint8_t* data = nullptr;
            size_t dataLen = 0;

            // 写文件头
            T3DFileHeader header;
            Script::FileFormat::FileMaterial file;

            Script::MaterialSystem::Material *material = nullptr;

            if (mIsBinary)
            {
                memcpy(header.magic, T3D_FILE_MAGIC, 3);
                header.magic[3] = 0;
                header.subtype = T3D_FILE_SUBTYPE_SCC;
                header.version = SCC_CURRENT_VERSION;
                header.fileSize = sizeof(header);

                data = buffer + sizeof(header);
                dataLen = bufSize - sizeof(header);

                material = new Script::MaterialSystem::Material();
            }
            else
            {
                Script::FileFormat::FileHeader *fileHeader = file.mutable_header();
                fileHeader->set_magic(T3D_FILE_MAGIC);
                fileHeader->set_type(Script::FileFormat::FileHeader::FileType::FileHeader_FileType_Material);
                fileHeader->set_version(SCC_CURRENT_VERSION);

                material = file.mutable_material();
            }
            
            ret = true;


            for (auto i = ast->begin(); i != ast->end(); ++i)
            {
                if ((*i)->type == ANT_OBJECT 
                    && static_cast<ObjectAbstractNode*>((*i).get())->abstrct)
                    continue;
                
                ScriptTranslator *translator = getTranslator(*i);
                
                if (translator)
                {
                    ret = translator->translate(this, material, *i);
                }
                else
                {
                    ret = false;
                    break;
                }

                if (!ret)
                {
                    break;
                }

                if (mIsBinary)
                {
                    ret = material->SerializeToArray(data, dataLen);
                    if (!ret)
                        break;

                    uint32_t len = (uint32_t)material->ByteSizeLong();
                    header.fileSize += len;
                    data += len;
                    dataLen -= len;
                }
            }

            if (!ret)
            {
                break;
            }

            FileDataStream fs;
            if (!fs.open(output.c_str(), FileDataStream::E_MODE_WRITE_ONLY))
            {
                ret = false;
                break;
            }

            if (mIsBinary)
            {
                stream.seek(0, false);
                stream.write(&header, sizeof(header));

                fs.write(buffer, header.fileSize);
            }
            else
            {
                String str;
                google::protobuf::util::JsonOptions opts;
                opts.add_whitespace = true;
                opts.always_print_enums_as_ints = false;
                opts.always_print_primitive_fields = true;
                google::protobuf::util::Status status = google::protobuf::util::MessageToJsonString(file, &str, opts);

                fs.write((void*)str.c_str(), str.length());
            }
            
            fs.close();

        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void ScriptCompiler::initPixelFormat()
    {
        enum PixelFormat
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

        mPixelFormat["PF_UNKNOWN"] = PixelFormat::E_PF_UNKNOWN;
        mPixelFormat["PF_PALETTE8"] = PixelFormat::E_PF_PALETTE8;
        mPixelFormat["PF_R5G6B5"] = PixelFormat::E_PF_R5G6B5;
        mPixelFormat["PF_A1R5G5B5"] = PixelFormat::E_PF_A1R5G5B5;
        mPixelFormat["PF_A4R4G4B4"] = PixelFormat::E_PF_A4R4G4B4;
        mPixelFormat["PF_R8G8B8"] = PixelFormat::E_PF_R8G8B8;
        mPixelFormat["PF_B8G8R8"] = PixelFormat::E_PF_B8G8R8;
        mPixelFormat["PF_A8R8G8B8"] = PixelFormat::E_PF_A8R8G8B8;
        mPixelFormat["PF_B8G8R8A8"] = PixelFormat::E_PF_B8G8R8A8;
        mPixelFormat["PF_X8R8G8B8"] = PixelFormat::E_PF_X8R8G8B8;
        mPixelFormat["PF_B8G8R8X8"] = PixelFormat::E_PF_B8G8R8X8;
    }

    //--------------------------------------------------------------------------

    void ScriptCompiler::initWordMap()
    {
        mIds["on"] = ID_ON;
        mIds["off"] = ID_OFF;
        mIds["true"] = ID_TRUE;
        mIds["false"] = ID_FALSE;
        mIds["yes"] = ID_YES;
        mIds["no"] = ID_NO;

        // Material ids
        mIds["material"] = ID_MATERIAL;
        mIds["vertex_program"] = ID_VERTEX_PROGRAM;
        mIds["geometry_program"] = ID_GEOMETRY_PROGRAM;
        mIds["fragment_program"] = ID_FRAGMENT_PROGRAM;
        mIds["tessellation_hull_program"] = ID_TESSELLATION_HULL_PROGRAM;
        mIds["tessellation_domain_program"] = ID_TESSELLATION_DOMAIN_PROGRAM;
        mIds["compute_program"] = ID_COMPUTE_PROGRAM;
        mIds["technique"] = ID_TECHNIQUE;
        mIds["pass"] = ID_PASS;
        mIds["texture_unit"] = ID_TEXTURE_UNIT;
        mIds["vertex_program_ref"] = ID_VERTEX_PROGRAM_REF;
        mIds["geometry_program_ref"] = ID_GEOMETRY_PROGRAM_REF;
        mIds["fragment_program_ref"] = ID_FRAGMENT_PROGRAM_REF;
        mIds["tessellation_hull_program_ref"] = ID_TESSELLATION_HULL_PROGRAM_REF;
        mIds["tessellation_domain_program_ref"] = ID_TESSELLATION_DOMAIN_PROGRAM_REF;
        mIds["compute_program_ref"] = ID_COMPUTE_PROGRAM_REF;
        mIds["shadow_caster_vertex_program_ref"] = ID_SHADOW_CASTER_VERTEX_PROGRAM_REF;
        mIds["shadow_caster_fragment_program_ref"] = ID_SHADOW_CASTER_FRAGMENT_PROGRAM_REF;
        mIds["shadow_receiver_vertex_program_ref"] = ID_SHADOW_RECEIVER_VERTEX_PROGRAM_REF;
        mIds["shadow_receiver_fragment_program_ref"] = ID_SHADOW_RECEIVER_FRAGMENT_PROGRAM_REF;

        mIds["lod_values"] = ID_LOD_VALUES;
        mIds["lod_strategy"] = ID_LOD_STRATEGY;
        mIds["lod_distances"] = ID_LOD_DISTANCES;
        mIds["receive_shadows"] = ID_RECEIVE_SHADOWS;
        mIds["transparency_casts_shadows"] = ID_TRANSPARENCY_CASTS_SHADOWS;
        mIds["set_texture_alias"] = ID_SET_TEXTURE_ALIAS;

        mIds["source"] = ID_SOURCE;
        mIds["target"] = ID_TARGET;
        mIds["entry_point"] = ID_ENTRY_POINT;
        mIds["stage"] = ID_STAGE;
        mIds["syntax"] = ID_SYNTAX;
        mIds["default_params"] = ID_DEFAULT_PARAMS;
        mIds["param_indexed"] = ID_PARAM_INDEXED;
        mIds["param_named"] = ID_PARAM_NAMED;
        mIds["param_indexed_auto"] = ID_PARAM_INDEXED_AUTO;
        mIds["param_named_auto"] = ID_PARAM_NAMED_AUTO;

        mIds["scheme"] = ID_SCHEME;
        mIds["lod_index"] = ID_LOD_INDEX;
        mIds["shadow_caster_material"] = ID_SHADOW_CASTER_MATERIAL;
        mIds["shadow_receiver_material"] = ID_SHADOW_RECEIVER_MATERIAL;
        mIds["gpu_vendor_rule"] = ID_GPU_VENDOR_RULE;
        mIds["gpu_device_rule"] = ID_GPU_DEVICE_RULE;
        mIds["include"] = ID_INCLUDE;
        mIds["exclude"] = ID_EXCLUDE;

        mIds["ambient"] = ID_AMBIENT;
        mIds["diffuse"] = ID_DIFFUSE;
        mIds["specular"] = ID_SPECULAR;
        mIds["emissive"] = ID_EMISSIVE;
        mIds["vertexcolour"] = ID_VERTEXCOLOUR;
        mIds["scene_blend"] = ID_SCENE_BLEND;
        mIds["colour_blend"] = ID_COLOUR_BLEND;
        mIds["one"] = ID_ONE;
        mIds["zero"] = ID_ZERO;
        mIds["dest_colour"] = ID_DEST_COLOUR;
        mIds["src_colour"] = ID_SRC_COLOUR;
        mIds["one_minus_src_colour"] = ID_ONE_MINUS_SRC_COLOUR;
        mIds["one_minus_dest_colour"] = ID_ONE_MINUS_DEST_COLOUR;
        mIds["dest_alpha"] = ID_DEST_ALPHA;
        mIds["src_alpha"] = ID_SRC_ALPHA;
        mIds["one_minus_dest_alpha"] = ID_ONE_MINUS_DEST_ALPHA;
        mIds["one_minus_src_alpha"] = ID_ONE_MINUS_SRC_ALPHA;
        mIds["separate_scene_blend"] = ID_SEPARATE_SCENE_BLEND;
        mIds["scene_blend_op"] = ID_SCENE_BLEND_OP;
        mIds["reverse_subtract"] = ID_REVERSE_SUBTRACT;
        mIds["min"] = ID_MIN;
        mIds["max"] = ID_MAX;
        mIds["separate_scene_blend_op"] = ID_SEPARATE_SCENE_BLEND_OP;
        mIds["depth_check"] = ID_DEPTH_CHECK;
        mIds["depth_write"] = ID_DEPTH_WRITE;
        mIds["depth_func"] = ID_DEPTH_FUNC;
        mIds["depth_bias"] = ID_DEPTH_BIAS;
        mIds["iteration_depth_bias"] = ID_ITERATION_DEPTH_BIAS;
        mIds["always_fail"] = ID_ALWAYS_FAIL;
        mIds["always_pass"] = ID_ALWAYS_PASS;
        mIds["less_equal"] = ID_LESS_EQUAL;
        mIds["less"] = ID_LESS;
        mIds["equal"] = ID_EQUAL;
        mIds["not_equal"] = ID_NOT_EQUAL;
        mIds["greater_equal"] = ID_GREATER_EQUAL;
        mIds["greater"] = ID_GREATER;
        mIds["alpha_rejection"] = ID_ALPHA_REJECTION;
        mIds["alpha_to_coverage"] = ID_ALPHA_TO_COVERAGE;
        mIds["light_scissor"] = ID_LIGHT_SCISSOR;
        mIds["light_clip_planes"] = ID_LIGHT_CLIP_PLANES;
        mIds["transparent_sorting"] = ID_TRANSPARENT_SORTING;
        mIds["illumination_stage"] = ID_ILLUMINATION_STAGE;
        mIds["decal"] = ID_DECAL;
        mIds["cull_hardware"] = ID_CULL_HARDWARE;
        mIds["clockwise"] = ID_CLOCKWISE;
        mIds["anticlockwise"] = ID_ANTICLOCKWISE;
        mIds["cull_software"] = ID_CULL_SOFTWARE;
        mIds["back"] = ID_BACK;
        mIds["front"] = ID_FRONT;
        mIds["normalise_normals"] = ID_NORMALISE_NORMALS;
        mIds["lighting"] = ID_LIGHTING;
        mIds["shading"] = ID_SHADING;
        mIds["flat"] = ID_FLAT;
        mIds["gouraud"] = ID_GOURAUD;
        mIds["phong"] = ID_PHONG;
        mIds["polygon_mode"] = ID_POLYGON_MODE;
        mIds["solid"] = ID_SOLID;
        mIds["wireframe"] = ID_WIREFRAME;
        mIds["points"] = ID_POINTS;
        mIds["polygon_mode_overrideable"] = ID_POLYGON_MODE_OVERRIDEABLE;
        mIds["fog_override"] = ID_FOG_OVERRIDE;
        mIds["none"] = ID_NONE;
        mIds["linear"] = ID_LINEAR;
        mIds["exp"] = ID_EXP;
        mIds["exp2"] = ID_EXP2;
        mIds["colour_write"] = ID_COLOUR_WRITE;
        mIds["max_lights"] = ID_MAX_LIGHTS;
        mIds["start_light"] = ID_START_LIGHT;
        mIds["iteration"] = ID_ITERATION;
        mIds["once"] = ID_ONCE;
        mIds["once_per_light"] = ID_ONCE_PER_LIGHT;
        mIds["per_n_lights"] = ID_PER_N_LIGHTS;
        mIds["per_light"] = ID_PER_LIGHT;
        mIds["point"] = ID_POINT;
        mIds["spot"] = ID_SPOT;
        mIds["directional"] = ID_DIRECTIONAL;
        mIds["light_mask"] = ID_LIGHT_MASK;
        mIds["point_size"] = ID_POINT_SIZE;
        mIds["point_sprites"] = ID_POINT_SPRITES;
        mIds["point_size_min"] = ID_POINT_SIZE_MIN;
        mIds["point_size_max"] = ID_POINT_SIZE_MAX;
        mIds["point_size_attenuation"] = ID_POINT_SIZE_ATTENUATION;

        mIds["texture_alias"] = ID_TEXTURE_ALIAS;
        mIds["texture"] = ID_TEXTURE;
        mIds["1d"] = ID_1D;
        mIds["2d"] = ID_2D;
        mIds["3d"] = ID_3D;
        mIds["cubic"] = ID_CUBIC;
        mIds["unlimited"] = ID_UNLIMITED;
        mIds["2darray"] = ID_2DARRAY;
        mIds["alpha"] = ID_ALPHA;
        mIds["gamma"] = ID_GAMMA;
        mIds["anim_texture"] = ID_ANIM_TEXTURE;
        mIds["cubic_texture"] = ID_CUBIC_TEXTURE;
        mIds["separateUV"] = ID_SEPARATE_UV;
        mIds["combinedUVW"] = ID_COMBINED_UVW;
        mIds["tex_coord_set"] = ID_TEX_COORD_SET;
        mIds["tex_address_mode"] = ID_TEX_ADDRESS_MODE;
        mIds["wrap"] = ID_WRAP;
        mIds["clamp"] = ID_CLAMP;
        mIds["mirror"] = ID_MIRROR;
        mIds["border"] = ID_BORDER;
        mIds["tex_border_colour"] = ID_TEX_BORDER_COLOUR;
        mIds["filtering"] = ID_FILTERING;
        mIds["bilinear"] = ID_BILINEAR;
        mIds["trilinear"] = ID_TRILINEAR;
        mIds["anisotropic"] = ID_ANISOTROPIC;
        mIds["compare_test"] = ID_CMPTEST;
        mIds["compare_func"] = ID_CMPFUNC;
        mIds["max_anisotropy"] = ID_MAX_ANISOTROPY;
        mIds["mipmap_bias"] = ID_MIPMAP_BIAS;
        mIds["colour_op"] = ID_COLOUR_OP;
        mIds["replace"] = ID_REPLACE;
        mIds["add"] = ID_ADD;
        mIds["modulate"] = ID_MODULATE;
        mIds["alpha_blend"] = ID_ALPHA_BLEND;
        mIds["colour_op_ex"] = ID_COLOUR_OP_EX;
        mIds["source1"] = ID_SOURCE1;
        mIds["source2"] = ID_SOURCE2;
        mIds["modulate"] = ID_MODULATE;
        mIds["modulate_x2"] = ID_MODULATE_X2;
        mIds["modulate_x4"] = ID_MODULATE_X4;
        mIds["add"] = ID_ADD;
        mIds["add_signed"] = ID_ADD_SIGNED;
        mIds["add_smooth"] = ID_ADD_SMOOTH;
        mIds["subtract"] = ID_SUBTRACT;
        mIds["blend_diffuse_alpha"] = ID_BLEND_DIFFUSE_ALPHA;
        mIds["blend_texture_alpha"] = ID_BLEND_TEXTURE_ALPHA;
        mIds["blend_current_alpha"] = ID_BLEND_CURRENT_ALPHA;
        mIds["blend_manual"] = ID_BLEND_MANUAL;
        mIds["dotproduct"] = ID_DOT_PRODUCT;
        mIds["blend_diffuse_colour"] = ID_BLEND_DIFFUSE_COLOUR;
        mIds["src_current"] = ID_SRC_CURRENT;
        mIds["src_texture"] = ID_SRC_TEXTURE;
        mIds["src_diffuse"] = ID_SRC_DIFFUSE;
        mIds["src_specular"] = ID_SRC_SPECULAR;
        mIds["src_manual"] = ID_SRC_MANUAL;
        mIds["colour_op_multipass_fallback"] = ID_COLOUR_OP_MULTIPASS_FALLBACK;
        mIds["alpha_op_ex"] = ID_ALPHA_OP_EX;
        mIds["env_map"] = ID_ENV_MAP;
        mIds["spherical"] = ID_SPHERICAL;
        mIds["planar"] = ID_PLANAR;
        mIds["cubic_reflection"] = ID_CUBIC_REFLECTION;
        mIds["cubic_normal"] = ID_CUBIC_NORMAL;
        mIds["scroll"] = ID_SCROLL;
        mIds["scroll_anim"] = ID_SCROLL_ANIM;
        mIds["rotate"] = ID_ROTATE;
        mIds["rotate_anim"] = ID_ROTATE_ANIM;
        mIds["scale"] = ID_SCALE;
        mIds["wave_xform"] = ID_WAVE_XFORM;
        mIds["scroll_x"] = ID_SCROLL_X;
        mIds["scroll_y"] = ID_SCROLL_Y;
        mIds["scale_x"] = ID_SCALE_X;
        mIds["scale_y"] = ID_SCALE_Y;
        mIds["sine"] = ID_SINE;
        mIds["triangle"] = ID_TRIANGLE;
        mIds["sawtooth"] = ID_SAWTOOTH;
        mIds["square"] = ID_SQUARE;
        mIds["inverse_sawtooth"] = ID_INVERSE_SAWTOOTH;
        mIds["transform"] = ID_TRANSFORM;
        mIds["binding_type"] = ID_BINDING_TYPE;
        mIds["vertex"] = ID_VERTEX;
        mIds["fragment"] = ID_FRAGMENT;
        mIds["geometry"] = ID_GEOMETRY;
        mIds["tessellation_hull"] = ID_TESSELLATION_HULL;
        mIds["tessellation_domain"] = ID_TESSELLATION_DOMAIN;
        mIds["compute"] = ID_COMPUTE;
        mIds["content_type"] = ID_CONTENT_TYPE;
        mIds["named"] = ID_NAMED;
        mIds["shadow"] = ID_SHADOW;
        mIds["texture_source"] = ID_TEXTURE_SOURCE;
        mIds["shared_params"] = ID_SHARED_PARAMS;
        mIds["shared_param_named"] = ID_SHARED_PARAM_NAMED;
        mIds["shared_params_ref"] = ID_SHARED_PARAMS_REF;

        // Particle system
        mIds["particle_system"] = ID_PARTICLE_SYSTEM;
        mIds["emitter"] = ID_EMITTER;
        mIds["affector"] = ID_AFFECTOR;

        // Compositor
        mIds["compositor"] = ID_COMPOSITOR;
        mIds["target"] = ID_TARGET;
        mIds["target_output"] = ID_TARGET_OUTPUT;

        mIds["input"] = ID_INPUT;
        mIds["none"] = ID_NONE;
        mIds["previous"] = ID_PREVIOUS;
        mIds["target_width"] = ID_TARGET_WIDTH;
        mIds["target_height"] = ID_TARGET_HEIGHT;
        mIds["target_width_scaled"] = ID_TARGET_WIDTH_SCALED;
        mIds["target_height_scaled"] = ID_TARGET_HEIGHT_SCALED;
        mIds["pooled"] = ID_POOLED;
        //mIds["gamma"] = ID_GAMMA; - already registered
        mIds["no_fsaa"] = ID_NO_FSAA;
        mIds["depth_pool"] = ID_DEPTH_POOL;

        mIds["texture_ref"] = ID_TEXTURE_REF;
        mIds["local_scope"] = ID_SCOPE_LOCAL;
        mIds["chain_scope"] = ID_SCOPE_CHAIN;
        mIds["global_scope"] = ID_SCOPE_GLOBAL;
        mIds["compositor_logic"] = ID_COMPOSITOR_LOGIC;

        mIds["only_initial"] = ID_ONLY_INITIAL;
        mIds["visibility_mask"] = ID_VISIBILITY_MASK;
        mIds["lod_bias"] = ID_LOD_BIAS;
        mIds["material_scheme"] = ID_MATERIAL_SCHEME;
        mIds["shadows"] = ID_SHADOWS_ENABLED;

        mIds["clear"] = ID_CLEAR;
        mIds["stencil"] = ID_STENCIL;
        mIds["render_scene"] = ID_RENDER_SCENE;
        mIds["render_quad"] = ID_RENDER_QUAD;
        mIds["identifier"] = ID_IDENTIFIER;
        mIds["first_render_queue"] = ID_FIRST_RENDER_QUEUE;
        mIds["last_render_queue"] = ID_LAST_RENDER_QUEUE;
        mIds["quad_normals"] = ID_QUAD_NORMALS;
        mIds["camera_far_corners_view_space"] = ID_CAMERA_FAR_CORNERS_VIEW_SPACE;
        mIds["camera_far_corners_world_space"] = ID_CAMERA_FAR_CORNERS_WORLD_SPACE;

        mIds["buffers"] = ID_BUFFERS;
        mIds["colour"] = ID_COLOUR;
        mIds["depth"] = ID_DEPTH;
        mIds["colour_value"] = ID_COLOUR_VALUE;
        mIds["depth_value"] = ID_DEPTH_VALUE;
        mIds["stencil_value"] = ID_STENCIL_VALUE;

        mIds["check"] = ID_CHECK;
        mIds["comp_func"] = ID_COMP_FUNC;
        mIds["ref_value"] = ID_REF_VALUE;
        mIds["mask"] = ID_MASK;
        mIds["fail_op"] = ID_FAIL_OP;
        mIds["keep"] = ID_KEEP;
        mIds["increment"] = ID_INCREMENT;
        mIds["decrement"] = ID_DECREMENT;
        mIds["increment_wrap"] = ID_INCREMENT_WRAP;
        mIds["decrement_wrap"] = ID_DECREMENT_WRAP;
        mIds["invert"] = ID_INVERT;
        mIds["depth_fail_op"] = ID_DEPTH_FAIL_OP;
        mIds["pass_op"] = ID_PASS_OP;
        mIds["two_sided"] = ID_TWO_SIDED;
        mIds["read_back_as_texture"] = ID_READ_BACK_AS_TEXTURE;

        mIds["subroutine"] = ID_SUBROUTINE;

        mIds["line_width"] = ID_LINE_WIDTH;
        mIds["sampler"] = ID_SAMPLER;
        mIds["sampler_ref"] = ID_SAMPLER_REF;
        mIds["thread_groups"] = ID_THREAD_GROUPS;
        mIds["render_custom"] = ID_RENDER_CUSTOM;

        mIds["gpu_program"] = ID_GPU_PROGRAM;
        mIds["gpu_program_ref"] = ID_GPU_PROGRAM_REF;

        mIds["gpu_cbuffer"] = ID_GPU_CBUFFER;
        mIds["gpu_cbuffer_ref"] = ID_GPU_CBUFFER_REF;
        mIds["slot"] = ID_CBUFFER_SLOT;

        mIds["render_queue"] = ID_RENDER_QUEUE;
    }

    void ScriptCompiler::getFileName(const String &filepath, String &path, String &name) const
    {
        String::size_type pos = filepath.find_last_of('/');

        if (pos == String::npos)
        {
            pos = filepath.find_last_of('\\');
        }

        if (pos == String::npos)
        {
            name = filepath;
            path = "";
        }
        else
        {
            path = filepath.substr(0, pos);
            name = filepath.substr(pos+1);
        }
    }

    void ScriptCompiler::getFileTitle(const String &filename, String &title, String &ext) const
    {
        String::size_type pos = filename.find_last_of('.');

        if (pos == String::npos)
        {
            title = filename;
            ext = "";
        }
        else
        {
            title = filename.substr(0, pos);
            ext = filename.substr(pos+1);
        }
    }

    //--------------------------------------------------------------------------

    bool ScriptCompiler::translate(ObjectAbstractNode *obj,
        const String &source, const String &target,  const String &stage, 
        const String &entry)
    {
        bool ret = false;

        do 
        {
            String filename = source;

            using namespace ShaderConductor;

            Compiler::SourceDesc sourceDesc{};
            Compiler::TargetDesc targetDesc{};

            // Stage
            if (stage == "vs")
            {
                sourceDesc.stage = ShaderStage::VertexShader;
            }
            else if (stage == "ps")
            {
                sourceDesc.stage = ShaderStage::PixelShader;
            }
            else if (stage == "gs")
            {
                sourceDesc.stage = ShaderStage::GeometryShader;
            }
            else if (stage == "hs")
            {
                sourceDesc.stage = ShaderStage::HullShader;
            }
            else if (stage == "ds")
            {
                sourceDesc.stage = ShaderStage::DomainShader;
            }
            else if (stage == "cs")
            {
                sourceDesc.stage = ShaderStage::ComputeShader;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, obj->name,
                    obj->file, obj->line, "Invalid shading stage !");
                break;
            }

            // Entry
            sourceDesc.entryPoint = entry.c_str();
            targetDesc.version = mShaderModel.c_str();

            String language = target;

            if (target.empty())
            {
                language = mTarget;
            }

            // Target
            if (language == "dxil")
            {
                targetDesc.language = ShadingLanguage::Dxil;
            }
            else if (language == "spirv")
            {
                targetDesc.language = ShadingLanguage::SpirV;
            }
            else if (language == "hlsl")
            {
                targetDesc.language = ShadingLanguage::Hlsl;
            }
            else if (language == "glsl")
            {
                targetDesc.language = ShadingLanguage::Glsl;
            }
            else if (language == "essl")
            {
                targetDesc.language = ShadingLanguage::Essl;
            }
            else if (language == "msl_macos")
            {
                targetDesc.language = ShadingLanguage::Msl_macOS;
            }
            else if (language == "msl_ios")
            {
                targetDesc.language = ShadingLanguage::Msl_iOS;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, obj->name,
                    obj->file, obj->line, "Invalid target shading language !");
                break;
            }

            T3D_LOG_INFO(LOG_TAG, "%s translating to %s for %s stage ...", filename.c_str(), language.c_str(), stage.c_str());

            // Read source file content
            String inpath = mProjDir + Dir::getNativeSeparator() + source;

            FileDataStream infile;

            if (!infile.open(inpath.c_str(), FileDataStream::E_MODE_READ_ONLY|FileDataStream::E_MODE_TEXT))
            {
                T3D_LOG_ERROR("Compiler",
                    "Invalid shader file path [%s] ! ", inpath.c_str());
                break;
            }

            String content;
            content.resize(infile.size());
            infile.read(&content[0], content.size());
            infile.close();

            sourceDesc.source = content.c_str();
            sourceDesc.fileName = inpath.c_str();

            Compiler::Options opt;
            opt.packMatricesInRowMajor = false;
            opt.optimizationLevel = mOptimizationLevel;
            opt.enableDebugInfo = mEnableDebugInfo;
            const auto result = Compiler::Compile(sourceDesc, opt, targetDesc);

            if (result.errorWarningMsg != nullptr)
            {
                const char* msg = reinterpret_cast<const char*>(result.errorWarningMsg->Data());
                T3D_LOG_ERROR("Compiler", "Error or warning from shader compiler: %s", std::string(msg, msg + result.errorWarningMsg->Size()).c_str());
            }

            if (result.target != nullptr)
            {
                size_t len = source.find_last_of('.');
                String title = len != String::npos ? source.substr(0, len) : source;
                String outpath = mOutDir + Dir::getNativeSeparator() + title + "." + stage;

                FileDataStream outfile;

                if (!outfile.open(outpath.c_str(), FileDataStream::E_MODE_TEXT |FileDataStream::E_MODE_WRITE_ONLY))
                {
                    T3D_LOG_ERROR("Compiler", "[%s] Create output file failed !", outpath.c_str());
                    DestroyBlob(result.errorWarningMsg);
                    DestroyBlob(result.target);
                    break;
                }

                if (language == "hlsl")
                {
                    // ShaderConductor 有 bug，没有把 hlsl 的 Semantic 记录下来 写回去，
                    // 所以这里做一次替换，以修复转出来的 hlsl 错误的 Semantic 修饰
                    String content((const char *)result.target->Data(), result.target->Size());
                    fixSpirVCrossForHLSLSemantics(content);
                    outfile.write((void*)content.c_str(), content.length());
                }
                else
                {
                    outfile.write((void*)result.target->Data(), result.target->Size());
                }

                outfile.close();
            }

            DestroyBlob(result.errorWarningMsg);
            DestroyBlob(result.target);

            ret = true;

            T3D_LOG_INFO(LOG_TAG, "%s translating done !", filename.c_str());
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    void ScriptCompiler::fixSpirVCrossForHLSLSemantics(String &content)
    {
        String::size_type p0 = 0;
        while (1)
        {
            String::size_type startPos = content.find(" : TEXCOORD", p0);
            if (startPos == String::npos)
                break;

            String::size_type endPos = content.find_first_of(';', startPos);
            if (endPos == String::npos)
                break;

            String::size_type p1 = content.rfind('_', startPos);
            if (p1 == String::npos)
                break;

            String semantic = content.substr(p1 + 1, startPos - p1 - 1);
            content.replace(startPos + 3, endPos - startPos - 3, semantic);
            p0 = endPos + 1;
        }
    }
}

