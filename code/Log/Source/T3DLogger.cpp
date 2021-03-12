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

#include "T3DLogger.h"
#include "T3DLogItem.h"
#include "T3DLogTask.h"
#include <sstream>
#include <stdarg.h>
#include <functional>
#include <chrono>


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(Logger);

    //--------------------------------------------------------------------------

    const char * const Logger::LEVEL_OFF = "OFF";
    const char * const Logger::LEVEL_FATAL = "FATAL";
    const char * const Logger::LEVEL_CRITICAL = "CRITICAL";
    const char * const Logger::LEVEL_ERROR = "ERROR";
    const char * const Logger::LEVEL_WARNING = "WARNING";
    const char * const Logger::LEVEL_INFO = "INFO";
    const char * const Logger::LEVEL_DEBUG = "DEBUG";

    //--------------------------------------------------------------------------

    Logger::Logger()
        : mFlushCacheTimerID(T3D_INVALID_TIMER_ID)
        , mAppID(0)
        , mTag("tag")
        , mTaskType(LogTask::E_TYPE_NONE)
        , mIsForced(false)
        , mIsRunning(false)
        , mIsTerminated(false)
        , mIsSuspended(false)
    {
        mStrategy.eLevel = E_LEVEL_WARNING;
        mStrategy.unExpired = 7;
        mStrategy.unMaxCacheSize = 50;
        mStrategy.unMaxCacheTime = 1000 * 5;
    }

    //--------------------------------------------------------------------------

    Logger::~Logger()
    {

    }

    //--------------------------------------------------------------------------

    void Logger::setLevel(Level eLevel)
    {
        if (eLevel != mStrategy.eLevel)
        {
            if (mIsRunning)
            {
                if (mStrategy.eLevel == E_LEVEL_OFF)
                {
                    mStrategy.eLevel = eLevel;
                    startup(mAppID, mTag, mIsForced);
                }
                else if (eLevel == E_LEVEL_OFF)
                {
                    shutdown();
                    mStrategy.eLevel = eLevel;
                }
            }

            mStrategy.eLevel = eLevel;
        }
    }

    //--------------------------------------------------------------------------

    void Logger::setMaxCacheSize(uint32_t unMaxCacheSize)
    {
        mStrategy.unMaxCacheSize = unMaxCacheSize;
    }

    //--------------------------------------------------------------------------

    void Logger::setExpired(uint32_t unExpired)
    {
        mStrategy.unExpired = unExpired;
    }

    //--------------------------------------------------------------------------

    void Logger::setMaxCacheTime(uint32_t unMaxCacheTime)
    {
        if (unMaxCacheTime != mStrategy.unMaxCacheTime)
        {
            mStrategy.unMaxCacheTime = unMaxCacheTime;

            stopFlushTimer();
            startFlushTimer();
        }
    }

    //--------------------------------------------------------------------------

    void Logger::setStrategy(const Strategy &strategy)
    {
        setMaxCacheSize(strategy.unMaxCacheSize);
        setMaxCacheTime(strategy.unMaxCacheTime);
        setExpired(strategy.unExpired);
        setLevel(strategy.eLevel);
    }

    //--------------------------------------------------------------------------

    TResult Logger::startup(ID appID, const String &tag,
        bool force /* = false */, bool outputConsole /* = false */)
    {
        mAppID = appID;
        mTag = tag;
        mIsForced = force;
        mIsOutputConsole = outputConsole;

        if (mStrategy.eLevel != E_LEVEL_OFF || force)
        {
            /// 不是关闭日志输出，需要先打开日志
            if (openLogFile())
            {
                /// 启动定时器，定时提交写回异步任务
                stopFlushTimer();
                startFlushTimer();
            }
        }

        /// 不管是否要输出日志，都提交一个检查过期日志文件的异步任务
        commitCheckExpiredTask();

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    void Logger::trace(Level level, const char *filename, int32_t line,
        const char *tag, const char *fmt, ...)
    {
        if (!mIsForced && level > mStrategy.eLevel)
            return;

        va_list args;
        char content[2048] = {0};

        va_start(args, fmt);
        vsnprintf(content, sizeof(content)-1, fmt, args);
        va_end(args);

        /// 截取路径，直接获取源码文件名
        String name = getFileName(filename);

        /// 生成一条日志项
        LogItem *item = new LogItem(level, name.c_str(), line, tag, content);

        /// 输出到控制台
        if (mIsOutputConsole)
        {
            item->outputConsole();
        }

        mItemCache.push_back(item);

        if (mItemCache.size() >= mStrategy.unMaxCacheSize)
        {
            commitFlushCacheTask();
        }
    }

    //--------------------------------------------------------------------------

    void Logger::shutdown()
    {
        /// 停止缓存写回文件间隔定时器
        stopFlushTimer();

        /// 把所有缓存都同步写回文件中
        flushCache();

        /// 关闭文件
        closeLogFile();
    }

    //--------------------------------------------------------------------------

    void Logger::enterBackground()
    {
        // 强制输出缓存中日志到文件中
        if (mStrategy.eLevel != E_LEVEL_OFF || mIsForced)
        {
            stopFlushTimer();
            flushCache();
            closeLogFile();
        }
    }

    //--------------------------------------------------------------------------

    void Logger::enterForeground()
    {
        // 重启写日志定时器
        if (mStrategy.eLevel != E_LEVEL_OFF || mIsForced)
        {
            openLogFile();
            startFlushTimer();
        }
    }

    //--------------------------------------------------------------------------

    Logger::Level Logger::toLevelValue(const String &level)
    {
        Level eLevel = E_LEVEL_OFF;

        if (LEVEL_OFF == level)
        {
            eLevel = E_LEVEL_OFF;
        }
        else if (LEVEL_FATAL == level)
        {
            eLevel = E_LEVEL_FATAL;
        }
        else if (LEVEL_CRITICAL == level)
        {
            eLevel = E_LEVEL_CRITICAL;
        }
        else if (LEVEL_ERROR == level)
        {
            eLevel = E_LEVEL_ERROR;
        }
        else if (LEVEL_WARNING == level)
        {
            eLevel = E_LEVEL_WARNING;
        }
        else if (LEVEL_INFO == level)
        {
            eLevel = E_LEVEL_INFO;
        }
        else if (LEVEL_DEBUG == level)
        {
            eLevel = E_LEVEL_DEBUG;
        }

        return eLevel;
    }

    //--------------------------------------------------------------------------

    String Logger::toLevelString(Level eLevel)
    {
        String level[E_LEVEL_MAX] =
        {
            LEVEL_OFF, LEVEL_FATAL, LEVEL_CRITICAL, LEVEL_ERROR,
            LEVEL_WARNING, LEVEL_INFO, LEVEL_DEBUG
        };

        return level[eLevel];
    }

    //--------------------------------------------------------------------------

    String Logger::getLogPath() const
    {
        String cachePath = Dir::getCachePath();
        String path = cachePath + Dir::getNativeSeparator() + "Log";
        return path;
    }

    //--------------------------------------------------------------------------

    String Logger::makeLogFileName(uint32_t appID, const String &tag,
        const DateTime &dt)
    {
        String logPath = getLogPath();

        std::stringstream ss;
        ss << appID << "_" << tag << "_";
        ss << dt.dateToString(DateTime::DateFormat::YY_MM_DD);
        ss << "_" << dt.Hour() << ".log";

        String fullPath = logPath + Dir::getNativeSeparator() + ss.str();
        return fullPath;
    }

    //--------------------------------------------------------------------------

    bool Logger::openLogFile()
    {
        /// 先创建日志文件夹
        String logPath = getLogPath();
        Dir dir;
        dir.makeDir(logPath);

        DateTime dt = DateTime::currentDateTime();
        String filename = makeLogFileName(mAppID, mTag, dt);
        bool ret = mFileStream.open(filename.c_str(),
            FileDataStream::E_MODE_APPEND | FileDataStream::E_MODE_TEXT);
        if (ret)
        {
            mCurLogFileTime = dt;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    void Logger::writeLogFile(TArray<LogItem*> &cache)
    {
        TArray<LogItem*>::iterator itr = cache.begin();

        while (itr != cache.end() && !mIsTerminated)
        {
            LogItem *item = *itr;

            if (item->getHour() != mCurLogFileTime.Hour())
            {
                // 跨越到下一个小时，重新写一个新文件
                closeLogFile();
                openLogFile();
            }

            item->outputFile(mFileStream);
            delete item;
            ++itr;
        }

        cache.clear();
    }

    //--------------------------------------------------------------------------

    void Logger::closeLogFile()
    {
        if (mFileStream.isOpened())
        {
            mFileStream.flush();
            mFileStream.close();
        }
    }

    //--------------------------------------------------------------------------

    void Logger::flushCache()
    {
        /// 先停止后台工作线程，同步写回所有数据
        stopAsyncTask();

        /// 设置当前日志级别，直接先关闭，避免再写入日志
        Level eLevel = mStrategy.eLevel;
        mStrategy.eLevel = E_LEVEL_OFF;

        TArray<LogItem *> cache(mItemCache.size());
        TArray<LogItem *>::iterator itr = cache.begin();
        while (itr != cache.end())
        {
            *itr = mItemCache.front();
            mItemCache.pop_front();
            ++itr;
        }

        writeLogFile(cache);

        /// 恢复当前日志级别
        mStrategy.eLevel = eLevel;
    }

    //--------------------------------------------------------------------------

    void Logger::startFlushTimer()
    {
        mFlushCacheTimerID = T3D_TIMER_MGR.startTimer(mStrategy.unMaxCacheTime,
            true, this);
    }

    //--------------------------------------------------------------------------

    void Logger::stopFlushTimer()
    {
        if (mFlushCacheTimerID != T3D_INVALID_TIMER_ID)
        {
            T3D_TIMER_MGR.stopTimer(mFlushCacheTimerID);
            mFlushCacheTimerID = T3D_INVALID_TIMER_ID;
        }
    }

    //--------------------------------------------------------------------------

    void Logger::onTimer(ID timerID, int32_t dt)
    {
        if (timerID == mFlushCacheTimerID)
        {
            commitFlushCacheTask();
        }
    }

    //--------------------------------------------------------------------------

    String Logger::getFileName(const String &path) const
    {
        String name;
        size_t pos = path.rfind("\\");
        if (pos == String::npos)
        {
            pos = path.rfind("/");
        }
        if (pos != String::npos)
        {
            name = path.substr(pos+1);
        }

        return name;
    }

    //--------------------------------------------------------------------------

//     int32_t Logger::asyncWorkingProcedure(Logger *pThis)
//     {
//         return pThis->workingProcedure();
//     }

    //--------------------------------------------------------------------------

//     int32_t Logger::workingProcedure()
    void Logger::workingProcedure()
    {
//         int32_t ret = 0;

        while (1)
        {
            LogTask *task = nullptr;

            mTaskMutex.lock();

            if (!mTaskQueue.empty())
            {
                task = mTaskQueue.front();
                mTaskQueue.pop_front();
            }

            mTaskMutex.unlock();

            if (task != nullptr)
            {
                switch (task->getType())
                {
                case LogTask::E_TYPE_CHECK_EXPIRED:
                    processCheckExpiredTask(task);
                    break;
                case LogTask::E_TYPE_FLUSH_CACHE:
                    processFlushCacheTask(task);
                    break;
                default:
                    break;
                }
            }

            if (mIsTerminated)
            {
//                 ret = -1;
                break;
            }

            mTaskMutex.lock();
            bool isTaskEmpty = mTaskQueue.empty();
            mTaskMutex.unlock();

            if (isTaskEmpty)
            {
                suspendAsyncTask();
            }
            else
            {
                // 挂起10ms
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }

//         return ret;
    }

    //--------------------------------------------------------------------------

    void Logger::startAsyncTask()
    {
        if (!mWorkingThread.joinable())
        {
            /// 启动异步线程
            mWorkingThread = std::thread(std::bind(&Logger::workingProcedure, this));
            mIsRunning = true;
            mIsTerminated = false;
            mTaskType = LogTask::E_TYPE_NONE;
        }
        else
        {
            // 异步线程已经启动了
            if (mIsSuspended)
            {
                // 异步线程被挂起，则唤醒
                wakeAsyncTask();
            }
        }
    }

    //--------------------------------------------------------------------------

    void Logger::stopAsyncTask()
    {
        if (mIsRunning && mWorkingThread.joinable())
        {
            mIsTerminated = true;

            if (mIsSuspended)
            {
                // 异步任务线程挂起中，直接唤醒
                wakeAsyncTask();
            }

            // 没挂起，直接停掉
            mWorkingThread.join();
            mIsRunning = false;
            mIsTerminated = false;
        }
    }

    //--------------------------------------------------------------------------

    void Logger::suspendAsyncTask()
    {
        TAutoLock<TMutex> lock(mWaitMutex);
        mIsSuspended = true;
        while (mIsSuspended)
        {
            mWaitCond.wait(lock);
        }
    }

    //--------------------------------------------------------------------------

    void Logger::wakeAsyncTask()
    {
        TAutoLock<TMutex> lock(mWaitMutex);
        mIsSuspended = false;
        mWaitCond.notify_all();
    }

    //--------------------------------------------------------------------------

    void Logger::commitCheckExpiredTask()
    {
        LogTaskCheckExpired *task = new LogTaskCheckExpired(mStrategy.unExpired);

        mTaskMutex.lock();
        mTaskQueue.push_back(task);
        mTaskMutex.unlock();

        startAsyncTask();
    }

    //--------------------------------------------------------------------------

    void Logger::commitFlushCacheTask()
    {
        LogTaskFlushCache *task = new LogTaskFlushCache(mItemCache.size());
        LogTaskFlushCache::ItemCacheItr itr = task->mItemCache.begin();

        while (!mItemCache.empty())
        {
            *itr = mItemCache.front();
            ++itr;
            mItemCache.pop_front();
        }

        mTaskMutex.lock();
        mTaskQueue.push_back(task);
        mTaskMutex.unlock();

        startAsyncTask();
    }

    //--------------------------------------------------------------------------

    TResult Logger::processCheckExpiredTask(LogTask *task)
    {
        mTaskType = LogTask::E_TYPE_CHECK_EXPIRED;
        uint64_t currentTime = DateTime::currentSecsSinceEpoch();

        Dir dir;
        String logPath = getLogPath();

        String path = logPath + Dir::getNativeSeparator() + "*.log";

        bool working = dir.findFile(path);
        while (working)
        {
            working = dir.findNextFile();

            if (working)
            {
                String filename = dir.getFileName();

                const int32_t oneDay = 24 * 60 * 60;
                const int32_t maxOutdate = mStrategy.unExpired * oneDay;
                time_t lastTime = dir.getLastWriteTime();
                time_t dt = currentTime - lastTime;
                if (dt >= maxOutdate)
                {
                    Dir::remove(dir.getFilePath().c_str());
                }
            }
        }

        dir.close();

        delete task;
        mTaskType = LogTask::E_TYPE_NONE;

        return T3D_OK;
    }

    //--------------------------------------------------------------------------

    TResult Logger::processFlushCacheTask(LogTask *task)
    {
        mTaskType = LogTask::E_TYPE_FLUSH_CACHE;

        writeLogFile(((LogTaskFlushCache *)task)->mItemCache);

        delete task;
        mTaskType = LogTask::E_TYPE_NONE;

        return T3D_OK;
    }
}
