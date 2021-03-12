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

#ifndef __T3D_LOG_H__
#define __T3D_LOG_H__


#include <T3DLogger.h>
#include <T3DLogErrorDef.h>

#define __T3D_OPEN_LOG__


#if defined (__T3D_OPEN_LOG__)

    #define T3D_LOG_TO_LEVEL_STR(l) \
        ((Tiny3D::Logger::getInstancePtr() != nullptr) ? \
        T3D_LOGGER.toLevelString(l) : Tiny3D::Logger::LEVEL_OFF);

    #define T3D_LOG_TO_LEVEL_VALUE(l) \
        ((Tiny3D::Logger::getInstancePtr() != nullptr) ? \
        T3D_LOGGER.toLevelValue(l) : Tiny3D::Logger::E_LEVEL_OFF);

    #define T3D_LOG_SET_LEVEL(l)    \
        if (Tiny3D::Logger::getInstancePtr() != nullptr)    \
        {    \
            T3D_LOGGER.setLevel(l); \
        }

    #define T3D_LOG_SET_EXPIRED(e)    \
        if (Tiny3D::Logger::getInstancePtr() != nullptr)    \
        {    \
            T3D_LOGGER.setExpired(e); \
        }

    #define T3D_LOG_SET_MAX_CACHE_SIZE(s)    \
        if (Tiny3D::Logger::getInstancePtr() != nullptr)    \
        {    \
            T3D_LOGGER.setMaxCacheSize(s); \
        }

    #define T3D_LOG_SET_MAX_CACHE_TIME(t)    \
        if (Tiny3D::Logger::getInstancePtr() != nullptr)    \
        {    \
            T3D_LOGGER.setMaxCacheTime(t); \
        }

    #define T3D_LOG_STARTUP(app_id, tag, force_output, output_console)  \
         if (Tiny3D::Logger::getInstancePtr() != nullptr)    \
         {   \
             T3D_LOGGER.startup(app_id, tag, force_output, output_console);  \
         }

    #define T3D_LOG_SHUTDOWN()  \
         if (Tiny3D::Logger::getInstancePtr() != nullptr)    \
         {   \
             T3D_LOGGER.shutdown();  \
         }

    #define T3D_LOG_ENTER_BACKGROUND()  \
         if (Tiny3D::Logger::getInstancePtr() != nullptr)    \
         {   \
             T3D_LOGGER.enterBackground();   \
         }

    #define T3D_LOG_ENTER_FOREGROUND()  \
         if (Tiny3D::Logger::getInstancePtr() != nullptr)    \
         {   \
             T3D_LOGGER.enterForeground();   \
         }

    #define T3D_LOG_TRACE(level, tag, fmt, ...)  \
         if (Tiny3D::Logger::getInstancePtr() != nullptr)    \
         {   \
             T3D_LOGGER.trace(level, __FILE__, __LINE__, tag, fmt, ##__VA_ARGS__);    \
         }

    #define T3D_LOG_FATAL(tag, fmt, ...)         \
        T3D_LOG_TRACE(Tiny3D::Logger::E_LEVEL_FATAL, tag, fmt, ##__VA_ARGS__)

    #define T3D_LOG_CRITICAL(tag, fmt, ...)      \
        T3D_LOG_TRACE(Tiny3D::Logger::E_LEVEL_CRITICAL, tag, fmt, ##__VA_ARGS__)

    #define T3D_LOG_ERROR(tag, fmt, ...)         \
        T3D_LOG_TRACE(Tiny3D::Logger::E_LEVEL_ERROR, tag, fmt, ##__VA_ARGS__)

    #define T3D_LOG_WARNING(tag, fmt, ...)       \
        T3D_LOG_TRACE(Tiny3D::Logger::E_LEVEL_WARNING, tag, fmt, ##__VA_ARGS__)

    #define T3D_LOG_INFO(tag, fmt, ...)          \
        T3D_LOG_TRACE(Tiny3D::Logger::E_LEVEL_INFO, tag, fmt, ##__VA_ARGS__)

    #define T3D_LOG_DEBUG(tag, fmt, ...)         \
        T3D_LOG_TRACE(Tiny3D::Logger::E_LEVEL_DEBUG, tag, fmt, ##__VA_ARGS__)

#else
    #define T3D_LOG_TO_LEVEL_STR(l)
    #define T3D_LOG_TO_LEVEL_VALUE(l)
    #define T3D_LOG_SET_LEVEL(l)
    #define T3D_LOG_SET_EXPIRED(e)
    #define T3D_LOG_SET_MAX_CACHE_SIZE(s)
    #define T3D_LOG_SET_MAX_CACHE_TIME(t)
    #define T3D_LOG_STARTUP(app_id, tag, force_output, output_console)
    #define T3D_LOG_SHUTDOWN()
    #define T3D_LOG_ENTER_BACKGROUND()
    #define T3D_LOG_ENTER_FOREGROUND()
    #define T3D_LOG_TRACE(level, tag, fmt, ...)
    #define T3D_LOG_FATAL(tag, fmt, ...)
    #define T3D_LOG_CRITICAL(tag, fmt, ...)
    #define T3D_LOG_ERROR(tag, fmt, ...)
    #define T3D_LOG_WARNING(tag, fmt, ...)
    #define T3D_LOG_INFO(tag, fmt, ...)
    #define T3D_LOG_DEBUG(tag, fmt, ...)
#endif


#endif  /*__T3D_LOG_H__*/
