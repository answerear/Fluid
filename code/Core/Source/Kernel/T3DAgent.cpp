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

#include <sstream>
#include "T3DErrorDef.h"

#include "Kernel/T3DAgent.h"
#include "Kernel/T3DPlugin.h"
#include "Kernel/T3DConfigFile.h"
#include "Kernel/T3DCommon.h"

#include "ImageCodec/T3DImageCodec.h"

#include "Resource/T3DArchive.h"
#include "Resource/T3DArchiveCreator.h"
#include "Resource/T3DArchiveManager.h"
#include "Resource/T3DDylib.h"
#include "Resource/T3DDylibManager.h"
#include "Resource/T3DMaterial.h"
#include "Resource/T3DMaterialManager.h"
#include "Resource/T3DModel.h"
#include "Resource/T3DModelManager.h"
#include "Resource/T3DTexture.h"
#include "Resource/T3DTextureManager.h"
#include "Resource/T3DGPUProgram.h"
#include "Resource/T3DGPUProgramCreator.h"
#include "Resource/T3DGPUProgramManager.h"
#include "Resource/T3DGPUConstBuffer.h"
#include "Resource/T3DGPUConstBufferManager.h"

#include "Memory/T3DObjectTracer.h"

#include "Render/T3DRenderContext.h"

#include "Scene/T3DSceneManager.h"
#include "Scene/T3DDefaultSceneMgr.h"

#include "Serializer/T3DSerializerManager.h"

#include "Component/T3DTransform3D.h"
#include "Component/T3DComponentCreator.h"
#include "Component/T3DCamera.h"
#include "Bound/T3DBound.h"
#include "Component/T3DRenderable.h"


namespace Tiny3D
{
    #define T3D_VERSION_0_0_0_1_STR         "0.0.0.1"
    #define T3D_VERSION_0_0_0_1_VAL         0x00000001
    #define T3D_VERSION_0_0_0_1_NAME        "Scorpius"

    #define T3D_VERSION_STR                 T3D_VERSION_0_0_0_1_STR
    #define T3D_VERSION_VAL                 T3D_VERSION_0_0_0_1_VAL
    #define T3D_VERSION_NAME                T3D_VERSION_0_0_0_1_NAME

    typedef TResult (*DLL_START_PLUGIN)(void);
    typedef TResult (*DLL_STOP_PLUGIN)(void);

    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(Agent);
    T3D_IMPLEMENT_CLASS_0(Agent);

    //--------------------------------------------------------------------------

    Agent::Agent()
        : mLogger(nullptr)
        , mEventMgr(nullptr)
        , mObjTracer(nullptr)
        , mDefaultWindow(nullptr)
        , mArchiveMgr(nullptr)
        , mDylibMgr(nullptr)
        , mSerialierMgr(nullptr)
        , mShaderMgr(nullptr)
        , mGPUProgramMgr(nullptr)
        , mGPUConstBufferMgr(nullptr)
        , mImageCodec(nullptr)
        , mActiveRenderer(nullptr)
        , mSceneMgr(nullptr)
        , mComponentCreator(nullptr)
        , mIsRunning(false)
    {
    }

    //--------------------------------------------------------------------------

    Agent::~Agent()
    {
        mComponentCreator = nullptr;
        mSceneMgr = nullptr;
        mActiveRenderer = nullptr;
        mDefaultWindow = nullptr;

        mMaterialMgr->unloadAllResources();
        mModelMgr->unloadAllResources();
        mGPUConstBufferMgr->unloadAllResources();
        mGPUProgramMgr->unloadAllResources();
        mShaderMgr->unloadAllResources();
        mTextureMgr->unloadAllResources();
        mArchiveMgr->unloadAllResources();

        unloadPlugins();

        mDylibMgr->unloadAllResources();

        mShaderMgr = nullptr;
        mGPUConstBufferMgr = nullptr;
        mGPUProgramMgr = nullptr;
        mMaterialMgr = nullptr;
        mModelMgr = nullptr;
        mTextureMgr = nullptr;
        mSerialierMgr = nullptr;
        mDylibMgr = nullptr;
        mArchiveMgr = nullptr;

        mImageCodec = nullptr;

        T3D_SAFE_DELETE(mEventMgr);

        mObjTracer->dumpMemoryInfo();
        T3D_SAFE_DELETE(mObjTracer);

        mLogger->shutdown();
        T3D_SAFE_DELETE(mLogger);
    }

    //--------------------------------------------------------------------------

    uint32_t Agent::getVersion() const
    {
        return T3D_VERSION_VAL;
    }

    //--------------------------------------------------------------------------

    const char *Agent::getVersionString() const
    {
        return T3D_VERSION_STR;
    }

    //--------------------------------------------------------------------------

    const char *Agent::getVersionName() const
    {
        return T3D_VERSION_NAME;
    }

    //--------------------------------------------------------------------------

    TResult Agent::init(const String &appPath, bool autoCreateWindow,
        const String &config /* = "Tiny3D.cfg" */)
    {
        TResult ret = T3D_OK;

        do
        {
#if !defined (T3D_OS_ANDROID)
            // 获取应用程序路径、应用程序名称
            StringUtil::split(appPath, mAppPath, mAppName);
#endif

            // 初始化应用程序框架，这个需要放在最前面，否则平台相关接口均不能用
            ret = initApplication();
            if (T3D_FAILED(ret))
            {
                break;
            }

            // 初始化日志系统，这个需要放在前面，避免日志无法输出
            ret = initLogSystem();
            if (T3D_FAILED(ret))
            {
                break;
            }

#if defined (T3D_OS_ANDROID)
            mAppPath = Dir::getAppPath();

            // Android 单独设置插件路径，不使用配置文件里面设置的路径
            // 因为android的插件在/data/data/appname/lib文件下
            mPluginsPath = Dir::getLibraryPath();
#endif

            // 初始化事件系统
            ret = initEventSystem();
            if (T3D_FAILED(ret))
            {
                break;
            }

            // 初始化对象追踪器
            ret = initObjectTracer();
            if (T3D_FAILED(ret))
            {
                break;
            }

            // 初始化各种管理器
            ret = initManagers();
            if (T3D_FAILED(ret))
            {
                break;
            }

            // 加载配置文件
            ret = loadConfig(config);
            if (T3D_FAILED(ret))
            {
                break;
            }

            // 加载配置文件中指定的插件
            ret = loadPlugins();
            if (T3D_FAILED(ret))
            {
                break;
            }

            // 初始化资源
            ret = initAssets();
            if (T3D_FAILED(ret))
            {
                break;
            }

            // 初始化渲染器
            ret = initRenderer();
            if (T3D_FAILED(ret))
            {
                break;
            }

            if (autoCreateWindow)
            {
                // 创建渲染窗口
                RenderWindowPtr window;
                ret = createDefaultRenderWindow(window);
                if (T3D_FAILED(ret))
                {
                    break;
                }

                addRenderWindow(window);
            }

            // 如果没有场景管理器，则初始化场景管理器
            ret = initSceneManager();
            if (T3D_FAILED(ret))
            {
                break;
            }

            mIsRunning = true;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::createDefaultRenderWindow(RenderWindowPtr &window)
    {
        TResult ret = T3D_OK;

        do
        {
            Settings &settings = mSettings["Render"].mapValue();

            RenderWindowCreateParam param;

            // 窗口标题
            param.windowTitle = settings["Title"].stringValue();
            // 窗口位置
            param.windowLeft = settings["x"].int32Value();
            param.windowTop = settings["y"].int32Value();
            // 窗口大小
            param.windowWidth = settings["Width"].int32Value();
            param.windowHeight = settings["Height"].int32Value();
            // 是否全屏
            param.fullscreen = settings["FullScreen"].boolValue();
            // 色深，如果是非全屏，自动跟桌面一样
            param.colorDepth = settings["ColorDepth"].int32Value();
            // 图标路径
            param.iconPath = settings["Icon"].stringValue();

            RenderWindowCreateParamEx paramEx;

            // 抗锯齿
            paramEx["MultiSampleQuality"] = settings["MultiSampleQuality"];
            // 垂直同步
            paramEx["VSync"] = settings["VSync"];

            std::stringstream ss;
            ss << "Tiny3D " << getVersionName() << "(" << getVersionString();
            ss << ")" << " - " << param.windowTitle;
            param.windowTitle = ss.str();
            window = mActiveRenderer->createRenderWindow(param.windowTitle, 
                param, paramEx);
            if (window == nullptr)
            {
                ret = T3D_ERR_RENDER_CREATE_WINDOW;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Create render window failed !");
                break;
            }

            mDefaultWindow = window;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::addRenderWindow(RenderWindowPtr window)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (mActiveRenderer == nullptr)
            {
                ret = T3D_ERR_SYS_NOT_INIT;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Do not set active renderer !");
                break;
            }

            ret = mActiveRenderer->attachRenderTarget(window);
        } while (0);
        
        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::removeRenderWindow(const String &name)
    {
        TResult ret = T3D_OK;

        do
        {
            if (mActiveRenderer == nullptr)
            {
                ret = T3D_ERR_SYS_NOT_INIT;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Do not set active renderer !");
                break;
            }

            ret = mActiveRenderer->detachRenderTarget(name);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    RenderWindowPtr Agent::getRenderWindow(const String &name) const
    {
        RenderWindowPtr window = nullptr;
        
        if (mActiveRenderer == nullptr)
        {
            T3D_LOG_ERROR(LOG_TAG_ENGINE, "Do not set active renderer !");
        }
        else
        {
            window = mActiveRenderer->getRenderTarget(name);
        }

        return window;
    }

    //--------------------------------------------------------------------------

    bool Agent::run()
    {
        Application *theApp = Application::getInstancePtr();
        theApp->applicationDidFinishLaunching();

        while (mIsRunning)
        {
            // 轮询系统事件
            mIsRunning = theApp->pollEvents();

            if (!mIsRunning)
                break;

            // 事件系统派发事件
            T3D_EVENT_MGR.dispatchEvent();

            // 更新场景树
            mSceneMgr->update();

            // 渲染一帧
            renderOneFrame();
        }

        theApp->applicationWillTerminate();

        return true;
    }

    void Agent::renderOneFrame()
    {
        if (mActiveRenderer != nullptr)
        {
            mActiveRenderer->renderAllTargets();
        }
    }

    //--------------------------------------------------------------------------

    void Agent::appWillEnterForeground()
    {
        T3D_LOG_ENTER_FOREGROUND();
    }

    //--------------------------------------------------------------------------

    void Agent::appDidEnterBackground()
    {
        T3D_LOG_ENTER_BACKGROUND();
    }

    //--------------------------------------------------------------------------

    TResult Agent::installPlugin(Plugin *plugin)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (plugin == nullptr)
            {
                // 空指针
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Invalid plugin !!!");
                break;
            }

            auto rval 
                = mPlugins.insert(PluginsValue(plugin->getName(), plugin));
            if (!rval.second)
            {
                ret = T3D_ERR_PLG_DUPLICATED;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Duplicated plugin [%s] !",
                    plugin->getName().c_str());
                break;
            }

            // 安装插件
            ret = plugin->install();
            if (T3D_FAILED(ret))
            {
                mPlugins.erase(plugin->getName());
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Install plugin [%s] failed !",
                    plugin->getName().c_str());
                break;
            }

            // 启动插件
            ret = plugin->startup();
            if (T3D_FAILED(ret))
            {
                mPlugins.erase(plugin->getName());
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Startup plugin [%s] failed !",
                    plugin->getName().c_str());
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::uninstallPlugin(Plugin *plugin)
    {
        TResult ret = T3D_OK;

        do 
        {
            if (plugin == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Invalid plugin !!!");
                break;
            }

            ret = plugin->shutdown();
            if (T3D_FAILED(ret))
            {
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Shutdown plugin [%s] failed !",
                    plugin->getName().c_str());
                break;
            }

            ret = plugin->uninstall();
            if (T3D_FAILED(ret))
            {

                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Uninstall plugin [%s] failed !",
                    plugin->getName().c_str())
                break;
            }

            mPlugins.erase(plugin->getName());
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::loadPlugin(const String &name)
    {
        T3D_LOG_INFO(LOG_TAG_ENGINE, "Load plugin %s ...", name.c_str());

        TResult ret = T3D_OK;

        do 
        {
            auto rval = mDylibs.find(name);
            if (rval != mDylibs.end())
            {
                // 已经加载过了，直接返回吧
                T3D_LOG_INFO(LOG_TAG_ENGINE, "Load plugin [%s] , \
                    but it already loaded !", name.c_str());
                break;
            }
            
            DylibPtr dylib = DylibManager::getInstance().loadDylib(name);
            if (dylib == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                break;
            }

            if (dylib->getType() != Resource::Type::E_RT_DYLIB)
            {
                ret = T3D_ERR_PLG_NOT_DYLIB;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Load plugin [%s] failed !", 
                    name.c_str());
                break;
            }

            DLL_START_PLUGIN pFunc 
                = (DLL_START_PLUGIN)(dylib->getSymbol("dllStartPlugin"));
            if (pFunc == nullptr)
            {
                ret = T3D_ERR_PLG_NO_FUNCTION;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, 
                    "Load plugin [%s] get function dllStartPlugin failed !", 
                    name.c_str());
                break;
            }

            ret = pFunc();
            if (T3D_FAILED(ret))
            {
                break;
            }

            mDylibs.insert(DylibsValue(dylib->getName(), dylib));
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::unloadPlugin(const String &name)
    {
        T3D_LOG_INFO(LOG_TAG_ENGINE, "Unload plugin %s ...", name.c_str());

        TResult ret = T3D_OK;

        do 
        {
            DylibsItr itr = mDylibs.find(name);
            if (itr == mDylibs.end())
            {
                ret = T3D_ERR_PLG_NOT_EXISTS;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Unload plugin [%s] , \
                    it don't exist !", name.c_str());
                break;
            }

            DylibPtr dylib = itr->second;
            DLL_STOP_PLUGIN pFunc 
                = (DLL_STOP_PLUGIN)(dylib->getSymbol("dllStopPlugin"));
            if (pFunc == nullptr)
            {
                ret = T3D_ERR_PLG_NO_FUNCTION;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Unload plugin [%s], \
                    get function dllStopPlugin failed !", name.c_str());
                break;
            }

            ret = pFunc();
            if (T3D_FAILED(ret))
            {
                break;
            }

            mDylibs.erase(itr);
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::addArchiveCreator(ArchiveCreator *creator)
    {
        TResult ret = T3D_OK;
        mArchiveMgr->addArchiveCreator(creator);
        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::removeArchiveCreator(ArchiveCreator *creator)
    {
        TResult ret = T3D_OK;
        mArchiveMgr->removeArchiveCreator(creator->getType());
        return ret;
    }

    //--------------------------------------------------------------------------

    ArchivePtr Agent::getMainAssetsArchive(const String &path) const
    {
        ArchivePtr archive = nullptr;

        if (mArchiveMgr != nullptr)
        {
            String fullpath = getMainAssetsPath(path);
#if defined T3D_OS_ANDROID
            mArchiveMgr->getArchive(mAppPath, fullpath, archive);
#else
            String name = mAppPath + "Assets";
            mArchiveMgr->getArchive(name, fullpath, archive);
#endif
        }

        return archive;
    }

    //--------------------------------------------------------------------------

    String Agent::getMainAssetsPath(const String &path) const
    {
#if defined T3D_OS_ANDROID
        String fullpath = "assets/" + path;
#else
        const String &fullpath = path;
#endif
        return fullpath;
    }

    //--------------------------------------------------------------------------

    ArchivePtr Agent::getAssetsArchive(const String &filename) const
    {
        bool found = false;
        ArchivePtr archive;

        if (mArchiveMgr != nullptr)
        {
            String fullpath = getMainAssetsPath(filename);
#if defined T3D_OS_ANDROID
            found = mArchiveMgr->getArchive(mAppPath, fullpath, archive);
#else
            String name = mAppPath + "Assets";
            found = mArchiveMgr->getArchive(name, fullpath, archive);
#endif

            if (!found)
            {
                // 主的没找到，只能循环查找
                found = mArchiveMgr->getArchive(filename, archive);
            }
        }

        return archive;
    }

    //--------------------------------------------------------------------------

    TResult Agent::addImageCodec(ImageCodecBase::FileType type,
        ImageCodecBasePtr codec)
    {
        return mImageCodec->addImageCodec(type, codec);
    }

    //--------------------------------------------------------------------------

    TResult Agent::removeImageCodec(ImageCodecBase::FileType type)
    {
        return mImageCodec->removeImageCodec(type);
    }

    //--------------------------------------------------------------------------

    void Agent::enumerateAvailableRenderers(Renderers &renderers) const
    {
        renderers.clear();
        renderers = mRenderers;
    }

    //--------------------------------------------------------------------------

    TResult Agent::setActiveRenderer(RenderContextPtr renderer)
    {
        TResult ret = T3D_OK;

        if (mActiveRenderer != renderer)
        {
            if (mActiveRenderer != nullptr)
            {
                mActiveRenderer->destroy();
            }

            ret = renderer->init();

            if (ret == T3D_OK)
            {
                mActiveRenderer = renderer;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    RenderContextPtr Agent::getActiveRenderer() const
    {
        return mActiveRenderer;
    }

    //--------------------------------------------------------------------------

    TResult Agent::addRenderer(RenderContextPtr renderer)
    {
        const String &name = renderer->getName();
        auto r = mRenderers.insert(RenderersValue(name, renderer));
        if (r.second)
        {
            return T3D_OK;
        }

        return T3D_ERR_DUPLICATED_ITEM;
    }

    //--------------------------------------------------------------------------

    TResult Agent::removeRenderer(RenderContextPtr renderer)
    {
        auto itr = mRenderers.find(renderer->getName());

        if (itr == mRenderers.end())
        {
            return T3D_ERR_NOT_FOUND;
        }

        mRenderers.erase(itr);

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    RenderContextPtr Agent::getRenderer(const String &name) const
    {
        RenderContextPtr renderer = nullptr;
        auto itr = mRenderers.find(name);

        if (itr != mRenderers.end())
        {
            renderer = itr->second;
        }

        return renderer;
    }

    //--------------------------------------------------------------------------

    TResult Agent::setSceneManager(SceneManagerBasePtr mgr)
    {
        mSceneMgr = nullptr;
        mSceneMgr = SceneManager::create(mgr);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    void Agent::setComponentCreator(ComponentCreator *creator)
    {
        mComponentCreator = creator;
    }

    //--------------------------------------------------------------------------

    ComponentCreatorPtr Agent::getComponentCreator() const
    {
        return mComponentCreator;
    }

    //--------------------------------------------------------------------------

    TResult Agent::initApplication()
    {
        TResult ret = T3D_OK;

        do
        {
            Application *theApp = Application::getInstancePtr();
            if (theApp == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                break;
            }

            ret = theApp->init();
            if (T3D_FAILED(ret))
            {
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::initLogSystem()
    {
        TResult ret = T3D_ERR_FAIL;

        mLogger = new Logger();

        if (mLogger != nullptr)
        {
            ret = mLogger->startup(1000, "Agent", true, true);
        }

        T3D_LOG_INFO(LOG_TAG_ENGINE, 
            "Start Tiny3D - %s(%s) ...... version %s",
            getVersionName(), getVersionString(),
            T3D_DEVICE_INFO.getSoftwareVersion().c_str());

        T3D_LOG_INFO(LOG_TAG_ENGINE, "System Information : \n%s",
            T3D_DEVICE_INFO.getSystemInfo().c_str());

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::initEventSystem()
    {
        mEventMgr = new EventManager(10);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult Agent::initObjectTracer()
    {
        mObjTracer = new ObjectTracer(true);
        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult Agent::initManagers()
    {
        mImageCodec = ImageCodec::create();
        mArchiveMgr = ArchiveManager::create();
        mDylibMgr = DylibManager::create();
        mSerialierMgr = SerializerManager::create();
        mTextureMgr = TextureManager::create();
        mShaderMgr = ShaderManager::create();
        mGPUConstBufferMgr = GPUConstBufferManager::create();
        mGPUProgramMgr = GPUProgramManager::create();
        mMaterialMgr = MaterialManager::create();
        mModelMgr = ModelManager::create();

        mComponentCreator = ComponentCreator::create();

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult Agent::loadConfig(const String &cfgPath)
    {
        TResult ret = T3D_OK;

#if defined (T3D_OS_ANDROID)
        // Android，只能读取apk包里面的文件
        ret = loadPlugin("ZipArchive");
        if (T3D_FAILED(ret))
        {
            return ret;
        }

        String apkPath = Dir::getAppPath();
        ArchivePtr archive = mArchiveMgr->loadArchive(apkPath, "Zip");
        ConfigFile cfgFile("assets/" + cfgPath, archive);
        ret = cfgFile.loadXML(mSettings);
#else
        // 其他不需要从 apk 包里面读取文件的
        String path = mAppPath + cfgPath;
        ConfigFile cfgFile(path);
        ret = cfgFile.loadXML(mSettings);
#endif

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::loadPlugins()
    {
        TResult ret = T3D_OK;

        do 
        {
            Settings &pluginSettings = mSettings["Plugins"].mapValue();
            String s("Path");
            Variant key(s);
            Settings::const_iterator itr = pluginSettings.find(key);
            if (itr == pluginSettings.end())
            {
                ret = T3D_ERR_PLG_NO_PATH;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Load plguins - \
                    The plugin path don't set !");
                break;
            }

#if !defined (T3D_OS_ANDROID)
            mPluginsPath = mAppPath + Dir::getNativeSeparator()
                + itr->second.stringValue();
#endif

            key.setString("List");
            itr = pluginSettings.find(key);

            if (itr == pluginSettings.end())
            {
                // 虽然没有获取到任何插件，但是仍然是合法的，正常返回
                ret = T3D_OK;
                break;
            }

            const VariantArray &plugins = itr->second.arrayValue();
            VariantArrayConstItr i = plugins.begin();

            while (i != plugins.end())
            {
                String name = i->stringValue();
                ret = loadPlugin(name);
                if (T3D_FAILED(ret))
                {
                    break;
                }

                ++i;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::unloadPlugins()
    {
        TResult ret = T3D_OK;

        DylibsItr itr = mDylibs.begin();
        while (itr != mDylibs.end())
        {
            DylibPtr dylib = itr->second;
            DLL_STOP_PLUGIN pFunc 
                = (DLL_STOP_PLUGIN)(dylib->getSymbol("dllStopPlugin"));
            if (pFunc != nullptr)
            {
                ret = pFunc();
                if (ret == T3D_OK)
                {
                    DylibManager::getInstance().unloadDylib(dylib);
                }
            }
            ++itr;
        }

        mDylibs.clear();

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::initAssets()
    {
        TResult ret = T3D_OK;

        do 
        {
#if defined (T3D_OS_ANDROID)
            // Android需要加载apk里面的资源，所以设置的是zip文件里面的assets
            ArchivePtr archive = mArchiveMgr->loadArchive(mAppPath, "Zip");
#else
            String path = mAppPath + "Assets";
            ArchivePtr archive = mArchiveMgr->loadArchive(path, "FileSystem");
            
            Settings &assets = mSettings["Assets"].mapValue();
            auto itr = assets.begin();
            while (itr != assets.end())
            {
                String subpath = path + Dir::getNativeSeparator() + itr->first.stringValue();
                String achiveType = itr->second.stringValue();
                archive = mArchiveMgr->loadArchive(subpath, achiveType);
                ++itr;
            }

            // 加入内置资源路径
            String subpath = path + Dir::getNativeSeparator() + "builtin";
            String archiveType = "FileSystem";
            archive = mArchiveMgr->loadArchive(subpath, archiveType);

            subpath = path + Dir::getNativeSeparator() + "builtin/program";
            archiveType = "FileSystem";
            archive = mArchiveMgr->loadArchive(subpath, archiveType);
#endif
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::initRenderer()
    {
        TResult ret = T3D_OK;

        do 
        {
            Settings settings = mSettings["Render"].mapValue();
            String rendererName = settings["Renderer"].stringValue();

            // 设置当前要使用的渲染器
            RenderContextPtr renderer = getRenderer(rendererName);
            if (renderer == nullptr)
            {
                ret = T3D_ERR_PLG_NOT_LOADED;
                T3D_LOG_ERROR(LOG_TAG_ENGINE, "Renderer [%s] did not load !",
                    rendererName.c_str());
                break;
            }

            ret = setActiveRenderer(renderer);
            if (T3D_FAILED(ret))
            {
                break;
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult Agent::initSceneManager()
    {
        TResult ret = T3D_OK;

        if (mSceneMgr == nullptr)
        {
            // 没有设置过场景管理器，只能引擎代劳，用个默认的吧
            ret = setSceneManager(DefaultSceneMgr::create());
        }

        return ret;
    }
}
