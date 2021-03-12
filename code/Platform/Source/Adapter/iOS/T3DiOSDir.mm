/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2017  Answer Wong
 * For latest info, see https://github.com/asnwerear/Tiny3D
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

#include "Adapter/iOS/T3DiOSDir.h"
#include <sys/stat.h>
#include <unistd.h>
#import <Foundation/Foundation.h>

namespace Tiny3D
{
    iOSDir::iOSDir()
    {
        
    }
    
    iOSDir::~iOSDir()
    {
        
    }

    long_t iOSDir::getCreationTime() const
    {
        long_t timestamp = 0;
        
        do
        {
            struct stat s;
            String strPath = m_strRoot + String(m_pDirent->d_name);
            int result = stat(strPath.c_str(), &s);
            if (result != 0)
                break;
            timestamp = (long_t)s.st_ctime;
        } while (0);
        
        return timestamp;
    }
    
    long_t iOSDir::getLastAccessTime() const
    {
        long_t timestamp = 0;
        
        do
        {
            struct stat s;
            String strPath = m_strRoot + String(m_pDirent->d_name);
            int result = stat(strPath.c_str(), &s);
            if (result != 0)
                break;
            timestamp = (long_t)s.st_atime;
        } while (0);
        
        
        return timestamp;
    }
    
    long_t iOSDir::getLastWriteTime() const
    {
        long_t timestamp = 0;
        
        do
        {
            struct stat s;
            String strPath = m_strRoot + String(m_pDirent->d_name);
            int result = stat(strPath.c_str(), &s);
            if (result != 0)
                break;
            timestamp = (long_t)s.st_mtime;
        } while (0);
        
        return timestamp;
    }
    
    String iOSDir::getCachePath() const
    {
        String cachePath;
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        NSArray *pathes = NSSearchPathForDirectoriesInDomains(NSCachesDirectory,
                                                              NSUserDomainMask,
                                                              YES);
        
        if ([pathes count] > 0)
        {
            NSString *path = [pathes objectAtIndex:0];
            cachePath = [path UTF8String];
        }
        
        [pool release];
        return cachePath;
    }
    
    String iOSDir::getAppPath() const
    {
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        NSString *path = [[NSBundle mainBundle] resourcePath];
        String appPath = [path UTF8String];
        [pool release];
        return appPath;
    }
    
    String iOSDir::getLibraryPath() const
    {
        return getAppPath();
    }
    
    String iOSDir::getWritablePath() const
    {
        String writablePath;
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        NSArray *pathes = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
                                                             NSUserDomainMask,
                                                             YES);
        if ([pathes count] > 0)
        {
            NSString *path = [pathes objectAtIndex:0];
            writablePath = [path UTF8String];
        }
        
        [pool release];
        return writablePath;
    }
}

