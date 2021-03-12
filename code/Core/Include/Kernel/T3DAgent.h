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


#ifndef __T3D_ENGINE_H__
#define __T3D_ENGINE_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"
#include "ImageCodec/T3DImageCodec.h"


namespace Tiny3D
{
    /**
     * @class   Agent
     * @brief   引擎入口类
     */
    class T3D_ENGINE_API Agent : public Singleton<Agent>
    {
        T3D_DISABLE_COPY(Agent);
        T3D_DECLARE_CLASS();

    public:
        /**
         * @fn  Agent::Agent();
         * @brief   构造函数
         */
        Agent();

        /**
         * @fn  virtual Agent::~Agent();
         * @brief   析构函数
         */
        virtual ~Agent();

        /**
         * @fn  uint32_t Agent::getVersion() const;
         * @brief   获取版本号
         * @return  返回整数型版本号.
         */
        uint32_t getVersion() const;

        /**
         * @fn  const char Agent::*getVersionString() const;
         * @brief   获取版本号字符串
         * @return  返回字符串型版本号.
         */
        const char *getVersionString() const;

        /**
         * @fn  const char Agent::*getVersionName() const;
         * @brief   获取版本号别名
         * @return  返回版本号别名.
         */
        const char *getVersionName() const;

        /**
         * @fn  TResult Agent::init(const String &appPath, 
         *      bool autoCreateWindow, const String &config = "Tiny3D.cfg");
         * @brief   初始化引擎
         * @param [in]  appPath             : 应用程序路径.
         * @param [in]  autoCreateWindow    : 是否创建渲染窗口.
         * @param [in]  config              (Optional) : 配置文件.
         * @return  A TResult.
         * @remarks  引擎的一切应用都要在调用本接口之后才有效。.
         */
        TResult init(const String &appPath, bool autoCreateWindow,
            const String &config = "Tiny3D.cfg");

        /**
         * @fn  TResult Agent::createDefaultRenderWindow(RenderWindowPtr &window);
         * @brief   创建渲染窗口
         * @param [in,out]  window  The window.
         * @return  The new default render window.
         */
        TResult createDefaultRenderWindow(RenderWindowPtr &window);

        /**
         * @fn  TResult Agent::addRenderWindow(RenderWindowPtr window);
         * @brief   添加渲染窗口到引擎里面
         * @param [in]  window  : 渲染窗口对象.
         * @return  成功返回 T3D_OK.
         */
        TResult addRenderWindow(RenderWindowPtr window);

        /**
         * @fn  TResult Agent::removeRenderWindow(const String &name);
         * @brief   从引擎移除渲染窗口
         * @param [in]  name    : 渲染窗口名称.
         * @return  成功返回 T3D_OK.
         */
        TResult removeRenderWindow(const String &name);

        /**
         * @fn  RenderWindowPtr Agent::getRenderWindow(const String &name) const;
         * @brief   获取渲染窗口
         * @param [in]  name    : 渲染窗口名称.
         * @return  成功返回渲染窗口对象.
         */
        RenderWindowPtr getRenderWindow(const String &name) const;

        /**
         * @fn  RenderWindowPtr Agent::getDefaultRenderWindow() const
         * @brief   获取默认渲染窗口
         * @return  返回默认渲染窗口对象.
         */
        RenderWindowPtr getDefaultRenderWindow() const 
        { 
            return mDefaultWindow; 
        }

        /**
         * @fn  bool Agent::run();
         * @brief   运行引擎
         * @return  True if it succeeds, false if it fails.
         */
        bool run();

        /**
         * @fn  void Agent::renderOneFrame();
         * @brief   渲染一帧
         */
        void renderOneFrame();

        /**
         * @fn  void Agent::appDidEnterBackground();
         * @brief   程序进入后台调用本接口告知引擎
         */
        void appDidEnterBackground();

        /**
         * @fn  void Agent::appWillEnterForeground();
         * @brief   程序回到前台调用本接口告知引擎
         */
        void appWillEnterForeground();

        /**
         * @fn  TResult Agent::installPlugin(Plugin *plugin);
         * @brief   安装插件
         * @param [in]  plugin  : 对应的插件对象.
         * @return  成功返回 T3D_OK.
         */
        TResult installPlugin(Plugin *plugin);

        /**
         * @fn  TResult Agent::uninstallPlugin(Plugin *plugin);
         * @brief   卸载插件
         * @param [in]  plugin  : 对应的插件对象.
         * @return  成功返回 T3D_OK.
         */
        TResult uninstallPlugin(Plugin *plugin);

        /**
         * @fn  TResult Agent::loadPlugin(const String &name);
         * @brief   加载指定名称的插件
         * @param   name    The name.
         * @return  成功返回 T3D_OK.
         */
        TResult loadPlugin(const String &name);

        /**
         * @fn  TResult Agent::unloadPlugin(const String &name);
         * @brief   卸载指定名称的插件
         * @param   name    The name.
         * @return  A TResult.
         */
        TResult unloadPlugin(const String &name);

        /**
         * @fn  TResult Agent::addArchiveCreator(ArchiveCreator *creator);
         * @brief   添加档案结构构造器
         * @param [in,out]  creator If non-null, the creator.
         * @return  成功返回 T3D_OK.
         */
        TResult addArchiveCreator(ArchiveCreator *creator);

        /**
         * @fn  TResult Agent::removeArchiveCreator(ArchiveCreator *creator);
         * @brief   移除档案结构构造器
         * @param [in,out]  creator If non-null, the creator.
         * @return  成功返回 T3D_OK.
         */
        TResult removeArchiveCreator(ArchiveCreator *creator);

        /**
         * @fn  ArchivePtr Agent::getMainAssetsArchive(const String &path) const;
         * @brief   获取主资源的档案对象
         * @param [in]  path    : 档案结构内部相对路径.
         * @return  成功返回档案结构对象.
         */
        ArchivePtr getMainAssetsArchive(const String &path) const;

        /**
         * @fn  String Agent::getMainAssetsPath(const String &path) const;
         * @brief   根据输入路径，返回相应资源路径
         * @param [in]  path    : 资源相对路径.
         * @return  返回相关平台的绝对路径.
         *
         * ### remarks  使用该返回的路径才能访问到对应平台的资源.
         */
        String getMainAssetsPath(const String &path) const;

        /**
         * @fn  ArchivePtr Agent::getAssetsArchive(const String &filename) const;
         * @brief   获取文件所在的档案对象
         * @param [in]  filename    : 文件名.
         * @return  成功返回档案结构对象.
         */
        ArchivePtr getAssetsArchive(const String &filename) const;

        /**
         * @fn  TResult Agent::addImageCodec(ImageCodecBase::FileType type, 
         *      ImageCodecBasePtr codec);
         * @brief   添加图像编解码器
         * @param [in]  type    : 文件类型.
         * @param [in]  codec   : 要添加的图像编解码器对象.
         * @return  成功返回 T3D_OK.
         */
        TResult addImageCodec(ImageCodecBase::FileType type, 
            ImageCodecBasePtr codec);

        /**
         * @fn  TResult Agent::removeImageCodec(ImageCodecBase::FileType type);
         * @brief   移除图像编解码器
         * @param [in]  type    : 要移除的编解码器对应的文件类型.
         * @return  成功返回 T3D_OK.
         */
        TResult removeImageCodec(ImageCodecBase::FileType type);

        /**
         * @fn  void Agent::enumerateAvailableRenderers(
         *      Renderers &renderers) const;
         * @brief   枚举所有可用的渲染器
         * @param [in]  renderers   renderers : 返回所有可用渲染器列表.
         */
        void enumerateAvailableRenderers(Renderers &renderers) const;

        /**
         * @fn  TResult Agent::setActiveRenderer(RenderContextPtr renderer);
         * @brief   设置当前可用的渲染器
         * @param [in]  renderer    : 渲染器对象.
         * @return  成功返回 T3D_OK.
         */
        TResult setActiveRenderer(RenderContextPtr renderer);

        /**
         * @fn  RenderContextPtr Agent::getActiveRenderer() const;
         * @brief   获取当前可用的渲染器
         * @return  成功返回当前渲染器对象.
         */
        RenderContextPtr getActiveRenderer() const;

        /**
         * @fn  TResult Agent::addRenderer(RenderContextPtr renderer);
         * @brief   添加渲染器
         * @param [in]  renderer    : 要添加的渲染器对象.
         * @return  成功返回 T3D_OK.
         */
        TResult addRenderer(RenderContextPtr renderer);

        /**
         * @fn  TResult Agent::removeRenderer(RenderContextPtr renderer);
         * @brief   移除渲染器
         * @param [in]  renderer    : 要移除的渲染器对象.
         * @return  成功返回 T3D_OK.
         */
        TResult removeRenderer(RenderContextPtr renderer);

        /**
         * @fn  RenderContextPtr Agent::getRenderer(const String &name) const;
         * @brief   获取渲染器对象
         * @param [in]  name    : 渲染器名称.
         * @return  成功返回渲染器对象.
         */
        RenderContextPtr getRenderer(const String &name) const;

        /**
         * @fn  TResult Agent::setSceneManager(SceneManagerBasePtr mgr);
         * @brief   设置场景管理器
         * @param [in]  mgr : 场景管理器对象.
         * @return  成功返回 T3D_OK.
         * @remarks  如果没有外部插件设置特有的场景管理器，
         *           则内部会用默认场景 管理器来使用.
         */
        TResult setSceneManager(SceneManagerBasePtr mgr);

        /**
         * @fn  const String Agent::&getAppPath() const
         * @brief   获取应用程序路径，不包含程序名称
         * @return  The application path.
         */
        const String &getAppPath() const { return mAppPath; }

        /**
         * @fn  const String Agent::&getAppName() const
         * @brief   获取应用程序名称，不包含路径
         * @return  The application name.
         */
        const String &getAppName() const { return mAppName; }

        /**
         * @fn  const String Agent::&getPluginsPath() const
         * @brief   获取插件路径
         * @return  The plugins path.
         */
        const String &getPluginsPath() const { return mPluginsPath; }

        void setComponentCreator(ComponentCreator *creator);

        ComponentCreatorPtr getComponentCreator() const;

    protected:
        /**
         * @fn  TResult Agent::initApplication();
         * @brief   初始化应用程序
         * @return  A TResult.
         */
        TResult initApplication();

        /**
         * @fn  TResult Agent::initLogSystem();
         * @brief   初始化日志系统
         * @return  A TResult.
         */
        TResult initLogSystem();

        /**
         * @fn  TResult Agent::initEventSystem();
         * @brief   初始化事件系统
         * @return  A TResult.
         */
        TResult initEventSystem();

        /**
         * @fn  TResult Agent::initObjectTracer();
         * @brief   初始化对象跟踪器
         * @return  A TResult.
         */
        TResult initObjectTracer();

        /**
         * @fn  TResult Agent::initManagers();
         * @brief   初始化各种管理器
         * @return  A TResult.
         */
        TResult initManagers();

        /**
         * @fn  TResult Agent::loadConfig(const String &cfgPath);
         * @brief   加载配置文件
         * @param [in]  cfgPath : 配置文件名.
         * @return  调用成功返回 T3D_OK.
         */
        TResult loadConfig(const String &cfgPath);

        /**
         * @fn  TResult Agent::loadPlugins();
         * @brief   加载配置文件中指定的插件
         * @return  调用成功返回 T3D_OK.
         */
        TResult loadPlugins();

        /**
         * @fn  TResult Agent::unloadPlugins();
         * @brief   卸载所有插件
         * @return  调用成功返回 T3D_OK.
         */
        TResult unloadPlugins();

        /**
         * @fn  TResult Agent::initAssets();
         * @brief   初始化资源
         * @return  调用成功返回 T3D_OK.
         */
        TResult initAssets();

        /**
         * @fn  TResult Agent::initRenderer();
         * @brief   初始化渲染器
         * @return  成功返回 T3D_OK.
         */
        TResult initRenderer();

        /**
         * @fn  TResult Agent::initSceneManager();
         * @brief   初始化场景管理器
         * @return  成功返回 T3D_OK.
         */
        TResult initSceneManager();

    protected:
        typedef TMap<String, Plugin*>       Plugins;
        typedef Plugins::iterator           PluginsItr;
        typedef Plugins::const_iterator     PluginsConstItr;
        typedef Plugins::value_type         PluginsValue;

        typedef TMap<String, DylibPtr>      Dylibs;
        typedef Dylibs::iterator            DylibsItr;
        typedef Dylibs::const_iterator      DylibsConstItr;
        typedef Dylibs::value_type          DylibsValue;

        Logger                  *mLogger;           /**< 日志对象 */
        EventManager            *mEventMgr;         /**< 事件管理器对象 */
        ObjectTracer            *mObjTracer;        /**< 对象内存跟踪 */

        RenderWindowPtr         mDefaultWindow;     /**< 默认渲染窗口 */

        ArchiveManagerPtr           mArchiveMgr;        /**< 档案管理对象 */
        DylibManagerPtr             mDylibMgr;          /**< 动态库管理对象 */
        SerializerManagerPtr        mSerialierMgr;      /**< 序列化管理器对象 */
        MaterialManagerPtr          mMaterialMgr;       /**< 材质资源管理对象 */
        ModelManagerPtr             mModelMgr;          /**< 模型资源管理对象 */
        TextureManagerPtr           mTextureMgr;        /**< 纹理资源管理对象 */
        ShaderManagerPtr            mShaderMgr;         /**< 着色器管理对象 */
        GPUProgramManagerPtr        mGPUProgramMgr;     /**< GPU 程序管理对象 */
        GPUConstBufferManagerPtr    mGPUConstBufferMgr; /**< GPU 常量缓冲区管理对象 */

        ImageCodecPtr           mImageCodec;        /**< 图像编解码器对象 */

        RenderContextPtr             mActiveRenderer;    /**< 当前渲染器对象 */
        SceneManagerPtr         mSceneMgr;

        ComponentCreatorPtr     mComponentCreator;

        Plugins                 mPlugins;           /**< 安装的插件列表 */
        Dylibs                  mDylibs;            /**< 加载的动态库列表 */
        Renderers               mRenderers;         /**< 渲染器列表 */

        String                  mAppPath;           /**< 程序路径 */
        String                  mAppName;           /**< 程序名称 */
        String                  mPluginsPath;       /**< 插件路径 */

        Settings                mSettings;          /**< 引擎配置项 */

        bool                    mIsRunning;         /**< 引擎是否在运行中 */
    };

    #define T3D_AGENT      (Agent::getInstance())
}


#endif  /*__T3D_APP_EVENT_LISTENER_H__*/
