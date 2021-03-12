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

#include "Adapter/Windows/T3DWin32DeviceInfo.h"
#include "Adapter/T3DFactoryInterface.h"
#include <windows.h>
#include <sstream>
#include <IPHlpApi.h>

#pragma comment(lib, "IPHLPAPI.lib")


namespace Tiny3D
{
    #define __USE_MAC_FOR_DEVICE_ID__                   0
    #define __USE_CPUID_FOR_DEVICE_ID__                 0
    #define __USE_MAINBOARD_UUID_FOR_DEVICE_ID__        1

    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(Win32DeviceInfo, IDeviceInfo);

    //--------------------------------------------------------------------------

    Win32DeviceInfo::Win32DeviceInfo()
        : mSWVersion()
        , mOSVersion()
        , mHWVersion()
        , mCPUType()
        , mCPUArchitecture()
        , mCPUCores(0)
        , mSystemRAM(0)
        , mScreenWidth(0)
        , mScreenHeight(0)
        , mScreenDPI(0.0f)
    {
        collectSystemInfo();
    }

    //--------------------------------------------------------------------------

    Win32DeviceInfo::~Win32DeviceInfo()
    {

    }

    //--------------------------------------------------------------------------

    void Win32DeviceInfo::collectSystemInfo()
    {
        // 收集操作系统信息
        collectOSInfo();

        // 收集CPU信息
        collectCPUInfo();

        // 收集系统RAM信息
        collectRAMInfo();

        // 收集设备信息
        collectDeviceInfo();

        // 收集屏幕信息
        collectScreenInfo();
    }

    //--------------------------------------------------------------------------

    void Win32DeviceInfo::collectOSInfo()
    {
        // Software Version
        if (mSWVersion.empty())
        {
            do
            {
                char strfile[MAX_PATH];
                //这里取得自己的文件名
                GetModuleFileName(NULL, strfile, sizeof(strfile));

                DWORD dwVersize = 0;
                DWORD dwHandle = 0;

                dwVersize = GetFileVersionInfoSize(strfile, &dwHandle);
                if (dwVersize == 0)
                {
                    break;
                }

                char szVerBuf[64] = { 0 };
                if (GetFileVersionInfo(strfile, 0, dwVersize, szVerBuf))
                {
                    VS_FIXEDFILEINFO* pInfo;
                    UINT nInfoLen;

                    if (VerQueryValue(szVerBuf, "\\",
                        (LPVOID*)&pInfo, &nInfoLen))
                    {
                        int nHMS = HIWORD(pInfo->dwFileVersionMS);
                        int nLMS = LOWORD(pInfo->dwFileVersionMS);
                        int nHLS = HIWORD(pInfo->dwFileVersionLS);
                        int nLLS = LOWORD(pInfo->dwFileVersionLS);

                        char verBuf[256];
                        memset(verBuf, 0, 256);
                        snprintf(verBuf, 199, "%d.%d.%d", nHMS, nLMS, nHLS);
                        mSWVersion = verBuf;
                    }
                }
            } while (0);
        }

        // Operating System
        if (mOSVersion.empty())
        {
            do
            {
                PVOID oldWow64State = NULL;

                HKEY hKey;
                LONG lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                    "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                    0,
                    KEY_ALL_ACCESS | KEY_WOW64_64KEY,
                    &hKey);
                if (lResult != ERROR_SUCCESS)
                    break;

                DWORD dwType;
                DWORD dwSize;
                char szName[64];

                // 获取操作系统名称
                dwSize = 64;
                lResult = RegQueryValueEx(hKey, "ProductName", NULL,
                    &dwType, (BYTE *)szName, &dwSize);
                if (lResult != ERROR_SUCCESS)
                {
                    RegCloseKey(hKey);
                    break;
                }

                // 获取CSDVersion
                dwSize = 64;
                char szCSDVersion[64];
                lResult = RegQueryValueEx(hKey, "CSDVersion", NULL,
                    &dwType, (BYTE *)szCSDVersion, &dwSize);
                if (lResult != ERROR_SUCCESS)
                {
                    RegCloseKey(hKey);
                    break;
                }

                // 获取CurrentVersion
                dwSize = 64;
                char szVersion[64];
                lResult = RegQueryValueEx(hKey, "CurrentVersion", NULL,
                    &dwType, (BYTE *)szVersion, &dwSize);
                if (lResult != ERROR_SUCCESS)
                {
                    RegCloseKey(hKey);
                    break;
                }

                // 获取CurrentBuildNumber
                dwSize = 64;
                char szBuild[64];
                lResult = RegQueryValueEx(hKey, "CurrentBuild", NULL,
                    &dwType, (BYTE *)szBuild, &dwSize);
                if (lResult != ERROR_SUCCESS)
                {
                    RegCloseKey(hKey);
                    break;
                }

                RegCloseKey(hKey);

                mOSVersion = String(szName) + " " + String(szCSDVersion) + " ("
                    + String(szVersion) + ") Build" + String(szBuild);
            } while (0);

            if (mOSVersion.empty())
            {
                mOSVersion = getOSInfo();
            }
        }
    }

    //--------------------------------------------------------------------------

    void Win32DeviceInfo::collectCPUInfo()
    {
        SYSTEM_INFO info;
        ::GetSystemInfo(&info);

        // CPU Type
        if (mCPUType.empty())
        {
            do
            {
                char strBuf[100];
                HKEY hKey;
                DWORD dwSize;
                LONG lReturn = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                    "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                    0,
                    KEY_READ,
                    &hKey);

                if (lReturn != ERROR_SUCCESS)
                {
                    break;
                }

                lReturn = RegQueryValueEx(hKey, "ProcessorNameString",
                    NULL, NULL, (BYTE *)strBuf, &dwSize);

                if (lReturn != ERROR_SUCCESS)
                {
                    break;
                }

                RegCloseKey(hKey);

                mCPUType = strBuf;
            } while (0);

            if (mCPUType.empty())
            {
                if (info.dwProcessorType == PROCESSOR_INTEL_386)
                {
                    mCPUType = "Intel 386";
                }
                else if (info.dwProcessorType == PROCESSOR_INTEL_486)
                {
                    mCPUType = "Intel 486";
                }
                else if (info.dwProcessorType == PROCESSOR_INTEL_PENTIUM)
                {
                    mCPUType = "Intel Pentium";
                }
                else if (info.dwProcessorType == PROCESSOR_INTEL_IA64)
                {
                    mCPUType = "Intel Itanium";
                }
                else if (info.dwProcessorType == PROCESSOR_AMD_X8664)
                {
                    mCPUType = "AMD x86_64";
                }
                else
                {
                    std::stringstream ss;
                    ss << info.dwProcessorType;
                    mCPUType = ss.str();
                }
            }
        }

        // CPU Architecture
        if (mCPUArchitecture.empty())
        {
            std::stringstream ss;

            // CPU Architecture
            if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
            {
                ss << "CPU Architecture : x64 (AMD or Intel)";
            }
            else if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM)
            {
                ss << "CPU Architecture : ARM";
            }
            else if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
            {
                ss << "CPU Architecture : Intel Itanium";
            }
            else if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
            {
                ss << "CPU Architecture : Intel";
            }
            else
            {
                ss << "Unknown architecture";
            }

            mCPUArchitecture = ss.str();
        }

        // CPU Cores
        if (mCPUCores == 0)
        {
            mCPUCores = info.dwNumberOfProcessors;
        }
    }

    //--------------------------------------------------------------------------

    void Win32DeviceInfo::collectRAMInfo()
    {
        if (mSystemRAM == 0)
        {
            MEMORYSTATUSEX statex;
            statex.dwLength = sizeof(statex);
            GlobalMemoryStatusEx(&statex);
            mSystemRAM = statex.ullTotalPhys / (1024 * 1024);
        }
    }

    //--------------------------------------------------------------------------

    void Win32DeviceInfo::collectDeviceInfo()
    {
        // Device Version
        if (mHWVersion.empty())
        {
            OSVERSIONINFOEX os;
            os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
            String version;

            if (::GetVersionEx((OSVERSIONINFO *)&os))
            {
                std::stringstream ss;
                ss << os.dwMajorVersion << "." << os.dwMinorVersion
                    << "." << os.dwBuildNumber;
                mHWVersion = ss.str();
            }
        }

        // Device ID
        if (mDeviceID.empty())
        {
#if __USE_MAC_FOR_DEVICE_ID__
            mDeviceID = getMacAddress();
#elif __USE_CPUID_FOR_DEVICE_ID__
            mDeviceID = getCPUID();
#elif __USE_MAINBOARD_UUID_FOR_DEVICE_ID__
            mDeviceID = getMainboardUUID();
#endif
        }
    }

    //--------------------------------------------------------------------------

    void Win32DeviceInfo::collectScreenInfo()
    {
        mScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
        mScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);

        HDC hdcScreen = GetDC(NULL);
        // Pixel per inch
        double fDPIX = (double)GetDeviceCaps(hdcScreen, LOGPIXELSX);
        double fDPIY = (double)GetDeviceCaps(hdcScreen, LOGPIXELSY);
        ReleaseDC(NULL, hdcScreen);

        mScreenDPI = (float)fDPIX;
    }

    //--------------------------------------------------------------------------

    uint32_t Win32DeviceInfo::getPlatform() const
    {
        return E_PLATFORM_WIN32;
    }

    //--------------------------------------------------------------------------

    const String &Win32DeviceInfo::getSoftwareVersion() const
    {
        return mSWVersion;
    }

    //--------------------------------------------------------------------------

    void Win32DeviceInfo::setSoftwareVersion(const char *version)
    {
        mSWVersion = version;
    }

    //--------------------------------------------------------------------------

    const String &Win32DeviceInfo::getOSVersion() const
    {
        return mOSVersion;
    }

    //--------------------------------------------------------------------------

    String Win32DeviceInfo::getOSInfo() const
    {
        SYSTEM_INFO info;
        ::GetSystemInfo(&info);
        OSVERSIONINFOEX os;
        os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        String version;

        if (::GetVersionEx((OSVERSIONINFO *)&os))
        {
            // 下面根据版本信息判断操作系统名称
            if (os.dwMajorVersion == 10)
            {
                if (os.dwMinorVersion == 0)
                {
                    if (os.wProductType == VER_NT_WORKSTATION)
                    {
                        // Windows 10
                        version = "Windows 10";
                    }
                    else
                    {
                        // Windows Server 2016
                        version = "Windows Server 2016";
                    }
                }
            }
            else if (os.dwMajorVersion == 6)
            {
                if (os.dwMinorVersion == 3)
                {
                    if (os.wProductType == VER_NT_WORKSTATION)
                    {
                        // Windows 8.1
                        version = "Windows 8.1";
                    }
                    else
                    {
                        // Windows Server 2012 R2
                        version = "Windows Server 2012 R2";
                    }
                }
                else if (os.dwMinorVersion == 2)
                {
                    if (os.wProductType == VER_NT_WORKSTATION)
                    {
                        // Windows 8
                        version = "Windows 8";
                    }
                    else
                    {
                        // Windows Server 2012
                        version = "Windows Server 2012";
                    }
                }
                else if (os.dwMinorVersion == 1)
                {
                    if (os.wProductType == VER_NT_WORKSTATION)
                    {
                        // Windows 7
                        version = "Windows 7";
                    }
                    else
                    {
                        // Windows Server 2008 R2
                        version = "Windows Server 2008 R2";
                    }
                }
                else if (os.dwMinorVersion == 0)
                {
                    if (os.wProductType == VER_NT_WORKSTATION)
                    {
                        // Windows Vista
                        version = "Windows Vista";

                        if (os.wSuiteMask == VER_SUITE_PERSONAL)
                        {
                            // Home
                            version = version + " Home";
                        }
                    }
                    else
                    {
                        // Windows Server 2008
                        version = "Windows Server 2008";

                        if (os.wSuiteMask == VER_SUITE_DATACENTER)
                        {
                            // Datacenter Server
                            version = version + " Datacenter Server";
                        }
                        else if (os.wSuiteMask == VER_SUITE_ENTERPRISE)
                        {
                            // Enterprise
                            version = version + "Enterprise";
                        }
                    }
                }
            }
            else if (os.dwMajorVersion == 5)
            {
                if (os.dwMinorVersion == 2)
                {
                    if (GetSystemMetrics(SM_SERVERR2) != 0)
                    {
                        // Windows Server 2003 R2
                        version = "Windows Server 2003 R2";

                        if (os.wSuiteMask == VER_SUITE_STORAGE_SERVER)
                        {
                            // Storage Server
                            version = version + " Storage Server";
                        }
                    }
                    else if (os.wSuiteMask & VER_SUITE_WH_SERVER)
                    {
                        // Windows Home Server
                        version = "Windows Home Server";
                    }
                    else if (GetSystemMetrics(SM_SERVERR2) == 0)
                    {
                        // Windows Server 2003
                        version = "Windows Server 2003";

                        if (os.wSuiteMask == VER_SUITE_BLADE)
                        {
                            // Web Edition
                            version = version + " Web Edition";
                        }
                        else if (os.wSuiteMask == VER_SUITE_COMPUTE_SERVER)
                        {
                            // Compute Cluster Edition
                            version = version + " Compute Cluster Edition";
                        }
                        else if (os.wSuiteMask == VER_SUITE_STORAGE_SERVER)
                        {
                            // Storage Server
                            version = version + " Storage Server";
                        }
                        else if (os.wSuiteMask == VER_SUITE_DATACENTER)
                        {
                            // Datacenter Edition
                            version = version + " Datacenter Edition";
                        }
                        else if (os.wSuiteMask == VER_SUITE_ENTERPRISE)
                        {
                            // Enterprise Edition
                            version = version + " Enterprise Edition";
                        }
                    }
                    else if ((os.wProductType == VER_NT_WORKSTATION)
                        && (info.wProcessorArchitecture
                            == PROCESSOR_ARCHITECTURE_AMD64))
                    {
                        // Windows XP Professional x64 Edition
                        version = "Windows XP Professional x64 Edition";
                    }
                }
                else if (os.dwMinorVersion == 1)
                {
                    // Windows XP
                    version = "Windows XP";

                    if (os.wSuiteMask == VER_SUITE_EMBEDDEDNT)
                        version = version + " Embedded";
                    else if (os.wSuiteMask == VER_SUITE_PERSONAL)
                        version = version + " Home Edition";
                    else
                        version = version + " Professional";
                }
                else if (os.dwMinorVersion == 0)
                {
                    // Windows 2000
                    version = "Windows 2000";

                    if (os.wSuiteMask == VER_SUITE_ENTERPRISE)
                    {
                        // Windows 2000 Advanced Server
                        version = version + " Advanced Server";
                    }
                }
            }

            if (version.empty())
            {
                // 未知版本，直接输出版本号
                std::stringstream ss;
                ss << os.dwMajorVersion << "." << os.dwMinorVersion
                    << "." << os.dwBuildNumber;
                version = ss.str();
            }
            else
            {
                std::stringstream ss;
                ss << version << " Build " << os.dwBuildNumber;
                version = ss.str();
            }
        }

        return version;
    }

    //--------------------------------------------------------------------------

    const String &Win32DeviceInfo::getDeviceVersion() const
    {
        return mHWVersion;
    }

    //--------------------------------------------------------------------------

    int32_t Win32DeviceInfo::getScreenWidth() const
    {
        return mScreenWidth;
    }

    //--------------------------------------------------------------------------

    int32_t Win32DeviceInfo::getScreenHeight() const
    {
        return mScreenHeight;
    }

    //--------------------------------------------------------------------------

    float Win32DeviceInfo::getScreenDPI() const
    {
        return mScreenDPI;
    }

    //--------------------------------------------------------------------------

    const String &Win32DeviceInfo::getCPUType() const
    {
        return mCPUType;
    }

    //--------------------------------------------------------------------------

    const String &Win32DeviceInfo::getCPUArchitecture() const
    {
        return mCPUArchitecture;
    }

    //--------------------------------------------------------------------------

    int32_t Win32DeviceInfo::getCPUCores() const
    {
        return mCPUCores;
    }

    //--------------------------------------------------------------------------

    uint64_t Win32DeviceInfo::getSystemRAM() const
    {
        return mSystemRAM;
    }

    //--------------------------------------------------------------------------

    const String &Win32DeviceInfo::getDeviceID() const
    {
        return mDeviceID;
    }

    //--------------------------------------------------------------------------

    String Win32DeviceInfo::getMacAddress() const
    {
        String macdress;

        do
        {
            PIP_ADAPTER_INFO pAdapterInfo;
            DWORD AdapterInfoSize;
            char szMac[32] = { 0 };
            DWORD Err;

            AdapterInfoSize = 0;
            Err = GetAdaptersInfo(NULL, &AdapterInfoSize);

            if ((Err != 0) && (Err != ERROR_BUFFER_OVERFLOW))
            {
                break;
            }

            //   分配网卡信息内存  
            pAdapterInfo = (PIP_ADAPTER_INFO)GlobalAlloc(GPTR, AdapterInfoSize);
            if (pAdapterInfo == NULL)
            {
                break;
            }

            if (GetAdaptersInfo(pAdapterInfo, &AdapterInfoSize) != 0)
            {
                GlobalFree(pAdapterInfo);
                break;
            }

            std::string strMac;
            for (PIP_ADAPTER_INFO pAdapter = pAdapterInfo; pAdapter != NULL; pAdapter = pAdapter->Next)
            {
                // 确保是以太网 
                if (pAdapter->Type != MIB_IF_TYPE_ETHERNET)
                    continue;

                // 确保MAC地址的长度为 00-00-00-00-00-00 
                if (pAdapter->AddressLength != 6)
                    continue;

                char acMAC[128] = { 0 };

                sprintf(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
                    (int)(pAdapter->Address[0]),
                    (int)(pAdapter->Address[1]),
                    (int)(pAdapter->Address[2]),
                    (int)(pAdapter->Address[3]),
                    (int)(pAdapter->Address[4]),
                    (int)(pAdapter->Address[5]));

                macdress = acMAC;
                break;
            }

            GlobalFree(pAdapterInfo);
        } while (0);

        return macdress;
    }

    //--------------------------------------------------------------------------

    String Win32DeviceInfo::getCPUID() const
    {
        unsigned long s1 = 0;
        unsigned long s2 = 0;
        unsigned long s3 = 0;
        unsigned long s4 = 0;

#if defined (T3D_OS_X86)
        __asm
        {
            mov eax, 00h
            xor edx, edx
            cpuid
            mov s1, edx
            mov s2, eax
        }
        __asm
        {
            mov eax, 01h
            xor ecx, ecx
            xor edx, edx
            cpuid
            mov s3, edx
            mov s4, ecx
        }
#endif

        char buf[100];
        sprintf(buf, "%08X%08X%08X%08X", s1, s2, s3, s4);
        return buf;
    }

    //--------------------------------------------------------------------------

    String Win32DeviceInfo::getMainboardUUID() const
    {
        char lpszBaseBoard[128] = { 0 };
        BOOL   bret = FALSE;
        HANDLE hReadPipe = NULL; //读取管道
        HANDLE hWritePipe = NULL; //写入管道
        PROCESS_INFORMATION pi;   //进程信息

        do
        {
            const long MAX_COMMAND_SIZE = 10000; // 命令行输出缓冲大小	
            char szFetCmd[] = "wmic csproduct get UUID"; // 获取主板序列号命令行	
            const String strEnSearch = "UUID"; // 主板序列号的前导信息


            STARTUPINFO			si;	  //控制命令行窗口信息
            SECURITY_ATTRIBUTES sa;   //安全属性

            char			szBuffer[MAX_COMMAND_SIZE + 1] = { 0 }; // 放置命令行结果的输出缓冲区
            String			strBuffer;
            unsigned long	count = 0;
            size_t			ipos = 0;

            memset(&pi, 0, sizeof(pi));
            memset(&si, 0, sizeof(si));
            memset(&sa, 0, sizeof(sa));

            pi.hProcess = NULL;
            pi.hThread = NULL;
            si.cb = sizeof(STARTUPINFO);
            sa.nLength = sizeof(SECURITY_ATTRIBUTES);
            sa.lpSecurityDescriptor = NULL;
            sa.bInheritHandle = TRUE;

            //1.0 创建管道
            bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
            if (!bret)
            {
                break;
            }

            //2.0 设置命令行窗口的信息为指定的读写管道
            GetStartupInfo(&si);
            si.hStdError = hWritePipe;
            si.hStdOutput = hWritePipe;
            si.wShowWindow = SW_HIDE; //隐藏命令行窗口
            si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

            //3.0 创建获取命令行的进程
            bret = CreateProcess(NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
            if (!bret)
            {
                break;
            }

            //4.0 读取返回的数据
            WaitForSingleObject(pi.hProcess, 500/*INFINITE*/);
            bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
            if (!bret)
            {
                break;
            }

            //5.0 查找主板序列号
            bret = FALSE;
            strBuffer = szBuffer;
            ipos = strBuffer.find(strEnSearch);

            if (ipos < 0) // 没有找到
            {
                break;
            }
            else
            {
                strBuffer = strBuffer.substr(ipos + strEnSearch.length());
            }

            memset(szBuffer, 0x00, sizeof(szBuffer));
            strcpy_s(szBuffer, strBuffer.c_str());

            //去掉中间的空格 \r \n
            int j = 0;
            for (int i = 0; i < strlen(szBuffer); i++)
            {
                if (szBuffer[i] != ' ' && szBuffer[i] != '\n' && szBuffer[i] != '\r')
                {
                    lpszBaseBoard[j] = szBuffer[i];
                    j++;
                }
            }

            bret = TRUE;
        } while (0);

        //关闭所有的句柄
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        
        return lpszBaseBoard;
    }
}
