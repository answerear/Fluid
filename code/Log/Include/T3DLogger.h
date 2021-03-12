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

#ifndef __T3D_LOGGER_H__
#define __T3D_LOGGER_H__


#include "T3DLogPrerequisites.h"


namespace Tiny3D
{
    class LogItem;
    class LogTask;

    class T3D_LOG_API Logger 
        : public Singleton<Logger>
        , public ITimerListener
    {
        T3D_DISABLE_COPY(Logger);

    public:
        enum Level
        {
            E_LEVEL_OFF = 0,        /// None log
            E_LEVEL_FATAL,          /// Fatal error
            E_LEVEL_CRITICAL,       /// Critical error
            E_LEVEL_ERROR,          /// Normal error
            E_LEVEL_WARNING,        /// Warning
            E_LEVEL_INFO,           /// Information
            E_LEVEL_DEBUG,          /// Debug
            E_LEVEL_MAX,            /// Max number of log level
        };

        static const char * const LEVEL_OFF;
        static const char * const LEVEL_FATAL;
        static const char * const LEVEL_CRITICAL;
        static const char * const LEVEL_ERROR;
        static const char * const LEVEL_WARNING;
        static const char * const LEVEL_INFO;
        static const char * const LEVEL_DEBUG;

        struct Strategy
        {
            Level       eLevel;         /// 当前日志输出的级别，高于该级别的日志都不输出
            uint32_t    unMaxCacheSize; /// 日志内容最大缓存内存大小，超过该大小，马上提交异步线程写回文件
            uint32_t    unMaxCacheTime; /// 日志内容缓存最长事件，超过该时间间隔，马上提交异步线程写回文件
            uint32_t    unExpired;      /// 过期时间，从今天开始回溯过去unExpired天
        };

    public:
        /**
         * @brief Constructor
         */
        Logger();

        /**
         * @brief Destructor
         */
        virtual ~Logger();

        /**
         * @brief 设置日志策略
         */
        void setStrategy(const Strategy &strategy);

        /**
         * @brief 设置当前日志输出的最高级别
         * @remarks 高于该级别的日志被忽略不输出
         */
        void setLevel(Level eLevel);

        /**
         * @brief 设置最大缓存大小
         * @remarks 大于该大小的缓存日志会马上提交异步线程写回文件
         */
        void setMaxCacheSize(uint32_t unMaxCacheSize);

        /**
         * @brief 设置最大缓存时间间隔
         * @remarks 超过该时间间隔缓存日志会马上提交异步线程写回文件
         */
        void setMaxCacheTime(uint32_t unMaxCacheTime);

        /**
         * @brief 设置过期时间，从今天开始回溯过去unExpired天
         */
        void setExpired(uint32_t unExpired);

        /**
         * @brief 启动日志模块
         * @param [in] appID : 标识当前应用程序的ID，以便区分日志文件
         * @param [in] tag : 额外的应用程序标签，给日志文件名附加额外信息以作区别
         * @param [in] force : 是否忽略日志级别，全量日志输出
         * @return 调用成功返回T3D_OK
         * @note 调用该函数前，请先通过setStrategy()或者setLevel()、
         *      setMaxCacheSize()、setMaxCacheTime()设置好日志输出策略，
         *      否则会用默认策略
         */
        TResult startup(ID appID, const String &tag, bool force = false, 
            bool outputConsole = false);

        /**
         * @brief 输出日志
         * @param [in] level : 输出日志相应级别
         * @param [in] filename : 输出日志的源码文件
         * @param [in] line : 输出日志对应源码文件的行数
         * @param [in] tag : 打个特殊标签，用于区分不同日志
         * @param [in] fmt : 格式化字符串
         * @param [in] var_list : 可变参数
         * @return void
         */
        void trace(Level level, const char *filename, int32_t line, 
            const char *tag, const char *fmt, ...);

        /**
         * @brief 关闭日志模块
         */
        void shutdown();

        /**
         * @brief 程序进入后台调用
         */
        void enterBackground();

        /**
         * @brief 程序回到前台调用
         */
        void enterForeground();

        /**
         * @brief 根据日志文本获取日志级别枚举值
         */
        Level toLevelValue(const String &level);

        /**
         * @brief 根据日志级别枚举值获取文本
         */
        String toLevelString(Level eLevel);

    private:
        /// 获取日志文件存放路径
        String getLogPath() const;

        /// 构造日志文件名
        String makeLogFileName(ID appID, const String &tag, const DateTime &dt);

        /// 打开日志文件
        bool openLogFile();
        /// 根据缓存缓冲区索引写文件
        void writeLogFile(std::vector<LogItem*> &cache);
        /// 关闭日志文件
        void closeLogFile();

        /// 把所有缓存都写回文件
        void flushCache();

        /// 启动写回缓存时间间隔定时器
        void startFlushTimer();
        /// 停止写回缓存时间间隔定时器
        void stopFlushTimer();

        /// 定时器回调，继承自RunLoopObserver
        virtual void onTimer(ID timerID, int32_t dt) override;

        String getFileName(const String &path) const;

        /// 异步线程调用的工作过程
        //static int32_t asyncWorkingProcedure(Logger *pThis);
        void workingProcedure();

        /// 启动异步任务，如果异步线程不存在则创建，如果线程被挂起，则唤醒
        void startAsyncTask();
        /// 停止异步任务
        void stopAsyncTask();
        /// 挂起异步任务线程
        void suspendAsyncTask();
        /// 唤醒异步任务线程
        void wakeAsyncTask();

        /// 提交检查过期日志异步任务
        void commitCheckExpiredTask();
        /// 提交把缓存写回文件异步任务
        void commitFlushCacheTask();

        /// 处理检查过期日志异步任务
        TResult processCheckExpiredTask(LogTask *task);
        /// 处理把缓存写回文件异步任务
        TResult processFlushCacheTask(LogTask *task);

    private:
        typedef TList<LogItem*>             ItemCache;
        typedef ItemCache::iterator         ItemCacheItr;
        typedef ItemCache::const_iterator   ItemCacheConstItr;

        typedef TList<LogTask*>             TaskQueue;
        typedef TaskQueue::iterator         TaskQueueItr;
        typedef TaskQueue::const_iterator   TaskQueueConstItr;

        ID                  mFlushCacheTimerID; /// 写回定时器ID

        ID                  mAppID;             /// 应用程序标识
        String              mTag;               /// 应用程序额外信息标签

        Strategy            mStrategy;          /// 日志输出相关策略

        DateTime            mCurLogFileTime;    /// 当前日志文件的时间，用于跨小时切换日志文件

        ItemCache           mItemCache;         /// 缓存日志记录，到达一定数量或者时间时提交异步写回处理
        TaskQueue           mTaskQueue;         /// 异步任务队列

        FileDataStream      mFileStream;        /// 文件输出对象

        TThread             mWorkingThread;     /// 异步工作线程，用于清除过期日志文件、写入日志文件等异步操作

        TMutex              mWaitMutex;     /// 用于挂起线程互斥量
        TCondVariable       mWaitCond;      /// 异步线程条件变量

        TMutex              mTaskMutex;         /// 异步任务互斥量

        int32_t             mTaskType;          /// 当前处理任务

        bool                mIsForced;          /// 是否强制输出
        bool                mIsOutputConsole;   /// 是否同步输出到控制台
        bool                mIsRunning;         /// 日志系统是否运行中
        bool                mIsTerminated;      /// 异步线程是否被终止
        bool                mIsSuspended;       /// 是否被挂起
    };
}

#define T3D_LOGGER          Tiny3D::Logger::getInstance()


#endif  /*__T3D_LOGGER_H__*/
