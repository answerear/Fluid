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

#include "Adapter/Android/T3DAndroidDeviceInfo.h"
#include "Adapter/T3DFactoryInterface.h"

#include <sys/types.h>
#include <sys/utsname.h>
#include <sstream>

#include <SDL.h>
#include "Adapter/Android/T3DJniApi.h"

namespace Tiny3D
{
    AndroidDeviceInfo::AndroidDeviceInfo()
        : mOSVersion()
        , mSWVersion()
        , mHWVersion()
        , mCPUType()
        , mCPUArchitecture()
        , mDeviceID()
        , mCPUCores(0)
        , mSystemRAM(0)
        , mScreenWidth(0)
        , mScreenHeight(0)
        , mScreenDPI(0.0f)
    {
        collectSystemInfo();
    }

    AndroidDeviceInfo::~AndroidDeviceInfo()
    {

    }

    void AndroidDeviceInfo::collectSystemInfo()
    {
        // Operating System 相关信息
        collectOSInfo();

        // CPU相关信息
        collectCPUInfo();

        // 内存相关信息
        collectRAMInfo();

        // 设备信息
        collectDeviceInfo();

        // 屏幕信息
        collectScreenInfo();
    }

    void AndroidDeviceInfo::collectOSInfo()
    {
        // Software Version
        JNIEnv *pEnv = (JNIEnv *)SDL_AndroidGetJNIEnv();
        if (pEnv != nullptr)
        {
            JNICallParam param;

            // Software Version
            if (GetClassStaticMethodID(pEnv, param, "com/tiny3d/lib/Tiny3DGlobal", "GetSoftwareVersion", "()Ljava/lang/String;"))
            {
                jstring jstr = (jstring)pEnv->CallStaticObjectMethod(param.classID, param.methodID);
                jboolean isCopy;
                const char *ver = pEnv->GetStringUTFChars(jstr, &isCopy);

                if (ver != nullptr)
                {
                    mSWVersion = ver;
                    pEnv->ReleaseStringUTFChars(jstr, ver);
                }

                pEnv->DeleteLocalRef(jstr);
            }
            DeleteLocalRef(pEnv, param);

            // OS Version
            if (GetClassStaticMethodID(pEnv, param, "com/tiny3d/lib/Tiny3DGlobal", "GetOSVersion", "()Ljava/lang/String;"))
            {
                jstring jstr = (jstring)pEnv->CallStaticObjectMethod(param.classID, param.methodID);
                jboolean isCopy;
                const char *ver = pEnv->GetStringUTFChars(jstr, &isCopy);

                if (ver != nullptr)
                {
                    mOSVersion = ver;
                    pEnv->ReleaseStringUTFChars(jstr, ver);
                }

                pEnv->DeleteLocalRef(jstr);
            }
            DeleteLocalRef(pEnv, param);
        }

        // Operating System Version
//        FILE *fp = nullptr;
//
//        do
//        {
//            fp = fopen("/proc/version", "r");
//            if (fp == nullptr)
//            {
//                break;
//            }
//
//            while (!feof(fp))
//            {
//                char buf[128] = {0};
//                fgets(buf, sizeof(buf)-1, fp);
//                mOSVersion = buf;
//                break;
//            }
//        } while(0);
//
//        if (fp != nullptr)
//        {
//            fclose(fp);
//        }
    }

    void AndroidDeviceInfo::collectCPUInfo()
    {
        struct utsname name;
        if (uname(&name) == 0)
        {
            mCPUArchitecture = name.machine;
        }

        JNIEnv *pEnv = (JNIEnv *)SDL_AndroidGetJNIEnv();
        if (pEnv != nullptr) {
            JNICallParam param;

            // Screen Width
            if (GetClassStaticMethodID(pEnv, param, "com/tiny3d/lib/Tiny3DGlobal", "GetCPUCores",
                                       "()I")) {
                mCPUCores = pEnv->CallStaticIntMethod(param.classID, param.methodID);
            }
            DeleteLocalRef(pEnv, param);
        }

        FILE *fp = nullptr;

        do
        {
            fp = fopen("/proc/cpuinfo", "r");
            if (fp == nullptr)
            {
                break;
            }

            while (!feof(fp))
            {
                char buf[128] = {0};
                fgets(buf, sizeof(buf)-1, fp);
                String name = buf;
                if (name.find("Processor") != String::npos)
                {
                    mCPUType = trim(name);
                    break;
                }
                else if (name.find("model name") != String::npos)
                {
                    mCPUType = trim(name);
                    break;
                }
            }
        } while(0);

        if (fp != nullptr)
        {
            fclose(fp);
        }
    }

    void AndroidDeviceInfo::collectRAMInfo()
    {
        FILE *fp = nullptr;

        do
        {
            fp = fopen("/proc/meminfo", "r");
            if (fp == nullptr)
            {
                break;
            }

            while (!feof(fp))
            {
                char buf[128] = {0};
                fgets(buf, sizeof(buf)-1, fp);
                String name = buf;
                if (name.find("MemTotal") != String::npos)
                {
                    String capacity = trim(name);
                    String total = capacity.substr(0, capacity.find("KB"));
                    int64_t memoryCapacity = atoi(total.c_str());
                    mSystemRAM = memoryCapacity / 1024;
                    break;
                }
            }
        } while(0);

        if (fp != nullptr)
        {
            fclose(fp);
        }
    }

    void AndroidDeviceInfo::collectDeviceInfo()
    {
        JNIEnv *pEnv = (JNIEnv *)SDL_AndroidGetJNIEnv();
        if (pEnv != nullptr)
        {
            JNICallParam param;

            // Device Name
            if (GetClassStaticMethodID(pEnv, param, "com/tiny3d/lib/Tiny3DGlobal", "GetDeviceName", "()Ljava/lang/String;"))
            {
                jstring jstr = (jstring)pEnv->CallStaticObjectMethod(param.classID, param.methodID);
                jboolean isCopy;
                const char *name = pEnv->GetStringUTFChars(jstr, &isCopy);
                if (name != nullptr)
                {
                    mHWVersion = name;
                    pEnv->ReleaseStringUTFChars(jstr, name);
                }

                pEnv->DeleteLocalRef(jstr);
            }
            DeleteLocalRef(pEnv, param);

            // Device ID
            if (GetClassStaticMethodID(pEnv, param, "com/tiny3d/lib/Tiny3DGlobal", "GetDeviceID", "()Ljava/lang/String;"))
            {
                jstring jstr = (jstring)pEnv->CallStaticObjectMethod(param.classID, param.methodID);
                jboolean isCopy;
                const char *deviceID = pEnv->GetStringUTFChars(jstr, &isCopy);
                if (deviceID != nullptr)
                {
                    mDeviceID = deviceID;
                    pEnv->ReleaseStringUTFChars(jstr, deviceID);
                }

                pEnv->DeleteLocalRef(jstr);
            }
            DeleteLocalRef(pEnv, param);
        }

        // Device ID
//        FILE *fp = nullptr;
//
//        do
//        {
//            fp = fopen("/sys/class/dmi/id/product_uuid", "r");
//            if (fp == nullptr)
//            {
//                break;
//            }
//
//            while (!feof(fp))
//            {
//                char buf[256] = {0};
//                fgets(buf, sizeof(buf)-1, fp);
//                mDeviceID = buf;
//                size_t len = mDeviceID.length();
//                mDeviceID.erase(len - 1);
//                break;
//            }
//        } while(0);
//
//        if (fp != nullptr)
//        {
//            fclose(fp);
//        }
    }

    void AndroidDeviceInfo::collectScreenInfo()
    {
        JNIEnv *pEnv = (JNIEnv *)SDL_AndroidGetJNIEnv();
        if (pEnv != nullptr)
        {
            JNICallParam param;

            // Screen Width
            if (GetClassStaticMethodID(pEnv, param, "com/tiny3d/lib/Tiny3DGlobal", "GetScreenWidth", "()I"))
            {
                mScreenWidth = pEnv->CallStaticIntMethod(param.classID, param.methodID);
            }
            DeleteLocalRef(pEnv, param);

            // Screen Height
            if (GetClassStaticMethodID(pEnv, param, "com/tiny3d/lib/Tiny3DGlobal", "GetScreenHeight", "()I"))
            {
                mScreenHeight = pEnv->CallStaticIntMethod(param.classID, param.methodID);
            }
            DeleteLocalRef(pEnv, param);

            // Screen DPI
            if (GetClassStaticMethodID(pEnv, param, "com/tiny3d/lib/Tiny3DGlobal", "GetScreenDPI", "()F"))
            {
                mScreenDPI = pEnv->CallStaticFloatMethod(param.classID, param.methodID);
            }
            DeleteLocalRef(pEnv, param);
        }
    }

    String AndroidDeviceInfo::trim(const String &text)
    {
        String name;

        do
        {
            size_t start = text.find(':') + 1;
            if (start == String::npos)
                break;

            while (text[start] == ' ')
            {
                start++;
            }

            size_t i = start;
            while (text[i] != '\n')
            {
                name.append(1, text[i]);
                i++;
            }
        } while(0);

        return name;
    }

    void AndroidDeviceInfo::getSoftwareVersionByJNI()
    {
        JNIEnv *pEnv = (JNIEnv *)SDL_AndroidGetJNIEnv();
        if (pEnv != nullptr)
        {
            JNICallParam param;
            if (GetClassStaticMethodID(pEnv, param, "com/tiny3d/lib/Tiny3DGlobal", "GetSoftwareVersion", "()Ljava/lang/String;"))
            {
                jstring jstr = (jstring)pEnv->CallStaticObjectMethod(param.classID, param.methodID);
                jboolean isCopy;
                const char *ver = pEnv->GetStringUTFChars(jstr, &isCopy);

                if (ver != nullptr)
                {
                    mSWVersion = ver;
                    pEnv->ReleaseStringUTFChars(jstr, ver);
                }

                pEnv->DeleteLocalRef(jstr);
            }

            DeleteLocalRef(pEnv, param);
        }
    }

    uint32_t AndroidDeviceInfo::getPlatform() const
    {
        return E_PLATFORM_ANDROID;
    }

    const String &AndroidDeviceInfo::getSoftwareVersion() const
    {
        return mSWVersion;
    }

    void AndroidDeviceInfo::setSoftwareVersion(const char *version)
    {

    }

    const String &AndroidDeviceInfo::getOSVersion() const
    {
        return mOSVersion;
    }

    const String &AndroidDeviceInfo::getDeviceVersion() const
    {
        return mHWVersion;
    }

    int32_t AndroidDeviceInfo::getScreenWidth() const
    {
        return mScreenWidth;
    }

    int32_t AndroidDeviceInfo::getScreenHeight() const
    {
        return mScreenHeight;
    }

    float AndroidDeviceInfo::getScreenDPI() const
    {
        return mScreenDPI;
    }

    const String &AndroidDeviceInfo::getCPUType() const
    {
        return mCPUType;
    }

    const String &AndroidDeviceInfo::getCPUArchitecture() const
    {
        return mCPUArchitecture;
    }

    int32_t AndroidDeviceInfo::getCPUCores() const
    {
        return mCPUCores;
    }

    uint32_t AndroidDeviceInfo::getSystemRAM() const
    {
        return mSystemRAM;
    }

    const String &AndroidDeviceInfo::getDeviceID() const
    {
        return mDeviceID;
    }
}
