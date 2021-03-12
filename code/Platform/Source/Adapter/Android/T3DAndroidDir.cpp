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

#include "Adapter/Android/T3DAndroidDir.h"
#include <sys/stat.h>
#include <unistd.h>

#include <SDL.h>
#include "Adapter/Android/T3DJniApi.h"

namespace Tiny3D
{
    AndroidDir::AndroidDir()
    {
        JNIEnv *pEnv = (JNIEnv *)SDL_AndroidGetJNIEnv();
        if (pEnv != nullptr) {
            JNICallParam param;

            // Software Version
            if (GetClassStaticMethodID(pEnv, param, "com/tiny3d/lib/Tiny3DGlobal",
                                       "GetApkPath", "()Ljava/lang/String;")) {
                jstring jstr = (jstring) pEnv->CallStaticObjectMethod(param.classID,
                                                                      param.methodID);
                jboolean isCopy;
                const char *apkPath = pEnv->GetStringUTFChars(jstr, &isCopy);

                if (apkPath != nullptr) {
                    mApkPath = apkPath;
                    pEnv->ReleaseStringUTFChars(jstr, apkPath);
                }

                pEnv->DeleteLocalRef(jstr);
            }
            DeleteLocalRef(pEnv, param);
        }
    }

    AndroidDir::~AndroidDir()
    {
        
    }

    long_t AndroidDir::getCreationTime() const
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
    
    long_t AndroidDir::getLastAccessTime() const
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
    
    long_t AndroidDir::getLastWriteTime() const
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
    
    String AndroidDir::getCachePath() const
    {
        String internalPath = SDL_AndroidGetInternalStoragePath();
        size_t pos = internalPath.rfind("/");
        String appPath = internalPath.substr(0, pos);
        return appPath + "/cache";
    }
    
    String AndroidDir::getAppPath() const
    {
        return mApkPath;
    }
    
    String AndroidDir::getWritablePath() const
    {
        String externalPath = SDL_AndroidGetInternalStoragePath();
        return externalPath;
    }

    String AndroidDir::getLibraryPath() const
    {
        String internalPath = SDL_AndroidGetInternalStoragePath();
        size_t pos = internalPath.rfind("/");
        String appPath = internalPath.substr(0, pos);
        return appPath + "/lib";
    }
}

