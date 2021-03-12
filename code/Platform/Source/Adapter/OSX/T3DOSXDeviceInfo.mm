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

#include "Adapter/OSX/T3DOSXDeviceInfo.h"
#include "Adapter/T3DFactoryInterface.h"
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/machine.h>
#include <sstream>

#import <AppKit/AppKit.h>

namespace Tiny3D
{
    OSXDeviceInfo::OSXDeviceInfo()
		: mOSVersion()
        , mSWVersion()
        , mHWVersion()
        , mCPUType()
		, mCPUCores(0)
		, mSystemRAM(0)
        , mScreenWidth(0)
        , mScreenHeight(0)
        , mScreenDPI(0.0f)
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

    OSXDeviceInfo::~OSXDeviceInfo()
    {

    }
    
    void OSXDeviceInfo::collectOSInfo()
    {
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        
        if (mSWVersion.empty())
        {
            NSBundle *bundle = [NSBundle mainBundle];
            if (bundle != nil)
            {
                NSString *str = [[bundle infoDictionary]
                                 objectForKey:@"CFBundleVersion"];
                if (str != nil)
                {
                    mSWVersion = [str UTF8String];
                }
            }
        }
        
        if (mOSVersion.empty())
        {
            NSString *ver = [[NSProcessInfo processInfo]
                             operatingSystemVersionString];
            mOSVersion = [ver UTF8String];
        }
        
        [pool release];
    }
    
    void OSXDeviceInfo::collectCPUInfo()
    {
        // CPU Type
        if (mCPUType.empty())
        {
            char buf[64];
            size_t buflen = 64;
            sysctlbyname("machdep.cpu.brand_string", &buf, &buflen, nullptr, 0);
            
            if (buflen != 0)
            {
                mCPUType = buf;
            }
        }
        
        // CPU Architecture
        if (mCPUArchitecture.empty())
        {
            cpu_type_t type;
            size_t size = sizeof(type);
            sysctlbyname("hw.cputype", &type, &size, nullptr, 0);
            cpu_subtype_t subtype;
            size = sizeof(subtype);
            sysctlbyname("hw.cpusubtype", &subtype, &size, nullptr, 0);
            std::stringstream ss;
            
            if (CPU_TYPE_X86 == type)
            {
                ss<<"x86";
            }
            else if (CPU_TYPE_X86_64 == type)
            {
                ss<<"x86_64";
            }
            else if (CPU_TYPE_ARM == type)
            {
                ss<<"ARM";
            }
            else if (CPU_TYPE_ARM64 == type)
            {
                ss<<"ARM64";
            }
            else if (CPU_TYPE_POWERPC == type)
            {
                ss<<"PowerPC";
            }
            else if (CPU_TYPE_POWERPC64 == type)
            {
                ss<<"PowerPC 64";
            }
            else if (CPU_TYPE_SPARC == type)
            {
                ss<<"Sparc";
            }
            else
            {
                ss<<"Unknown : "<<type;
            }
            
            if (CPU_SUBTYPE_386 == subtype)
            {
                ss<<"(386)";
            }
            else if (CPU_SUBTYPE_486 == subtype)
            {
                ss<<"(486)";
            }
            else if (CPU_SUBTYPE_586 == subtype)
            {
                ss<<"(586)";
            }
            else if (CPU_SUBTYPE_ARM_V6 == subtype)
            {
                ss<<"v6";
            }
            else if (CPU_SUBTYPE_ARM_V7 == subtype)
            {
                ss<<"v7";
            }
            else if (CPU_SUBTYPE_PENT == subtype)
            {
                ss<<"(Pentium)";
            }
            else if (CPU_SUBTYPE_PENTPRO == subtype)
            {
                ss<<"(Pentium Pro)";
            }
            else if (CPU_SUBTYPE_PENTII_M3 == subtype)
            {
                ss<<"(Pentium M3)";
            }
            else if (CPU_SUBTYPE_PENTII_M5 == subtype)
            {
                ss<<"(Pentium M5)";
            }
            else if (CPU_SUBTYPE_CELERON == subtype)
            {
                ss<<"(Celeron)";
            }
            else if (CPU_SUBTYPE_CELERON_MOBILE == subtype)
            {
                ss<<"(Celeron Mobile)";
            }
            else if (CPU_SUBTYPE_PENTIUM_3 == subtype)
            {
                ss<<"(Pentium 3)";
            }
            else if (CPU_SUBTYPE_PENTIUM_3_M == subtype)
            {
                ss<<"(Pentium 3 M)";
            }
            else if (CPU_SUBTYPE_PENTIUM_3_XEON == subtype)
            {
                ss<<"(Pentium 3 XEON)";
            }
            else if (CPU_SUBTYPE_PENTIUM_M == subtype)
            {
                ss<<"(Pentium M)";
            }
            else if (CPU_SUBTYPE_PENTIUM_4 == subtype)
            {
                ss<<"(Pentium 4)";
            }
            else if (CPU_SUBTYPE_PENTIUM_4_M == subtype)
            {
                ss<<"(Pentium 4 M)";
            }
            else if (CPU_SUBTYPE_ITANIUM == subtype)
            {
                ss<<"(Itanium)";
            }
            else if (CPU_SUBTYPE_ITANIUM_2 == subtype)
            {
                ss<<"(Itanium 2)";
            }
            else if (CPU_SUBTYPE_XEON == subtype)
            {
                ss<<"(XEON)";
            }
            else if (CPU_SUBTYPE_XEON_MP == subtype)
            {
                ss<<"(XEON MP)";
            }
            else if (CPU_SUBTYPE_ARM_V8 == subtype)
            {
                ss<<"v8";
            }
            else if (CPU_SUBTYPE_ARM64_V8 == subtype)
            {
                ss<<"v8";
            }
            else if (CPU_SUBTYPE_ARM64_ALL == subtype)
            {
                ss<<"64";
            }
            else
            {
                ss<<"("<<subtype<<")";
            }
            
            mCPUArchitecture = ss.str();
        }
        
        // CPU Cores
        if (mCPUCores == 0)
        {
            int cores = 0;
            size_t size = sizeof(cores);
            sysctlbyname("hw.physicalcpu", &cores, &size, nullptr, 0);
            mCPUCores = cores;
        }
    }
    
    void OSXDeviceInfo::collectRAMInfo()
    {
        if (mSystemRAM == 0)
        {
            int mib[2];
            mib[0] = CTL_HW;
            mib[1] = HW_MEMSIZE;
            uint64_t totalMemory = 0;
            size_t size = sizeof(totalMemory);
            sysctl(mib, 2, &totalMemory, &size, nullptr, 0);
            mSystemRAM = (uint32_t)(totalMemory / (1024 * 1024));
        }
    }
    
    void OSXDeviceInfo::collectDeviceInfo()
    {
        // Device Version
        if (mHWVersion.empty())
        {
            char buf[64];
            size_t buflen = 64;
            
            int mib[2];
            mib[0] = CTL_HW;
            mib[1] = HW_MODEL;
            sysctl(mib, 2, buf, &buflen, nullptr, 0);
            if (buflen != 0)
                mHWVersion = mHWVersion + " " + String(buf);
        }
        
        // Device ID
        if (mDeviceID.empty())
        {
            NSString *ret = nil;
            io_service_t platformExpert ;
            platformExpert = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("IOPlatformExpertDevice")) ;
            
            if (platformExpert)
            {
                CFTypeRef serialNumberAsCFString ;
                serialNumberAsCFString = IORegistryEntryCreateCFProperty(platformExpert, CFSTR("IOPlatformUUID"), kCFAllocatorDefault, 0) ;
                if (serialNumberAsCFString)
                {
                    ret = [(NSString *)(CFStringRef)serialNumberAsCFString copy];
                    CFRelease(serialNumberAsCFString); serialNumberAsCFString = NULL;
                }
                
                IOObjectRelease(platformExpert); platformExpert = 0;
            }
            
            mDeviceID = [ret UTF8String];
            [ret release];
        }
    }
    
    void OSXDeviceInfo::collectScreenInfo()
    {
        NSRect screenRect = [NSScreen mainScreen].frame;
        CGFloat scale = 1.0f;
        
        if ([[NSScreen mainScreen] respondsToSelector:@selector(backingScaleFactor)])
        {
            scale = [[NSScreen mainScreen] backingScaleFactor];
        }
        
        NSValue *value = [[NSScreen mainScreen].deviceDescription objectForKey:NSDeviceResolution];
        NSSize size;
        [value getValue:&size size:sizeof(size)];
        mScreenDPI = size.width;
        
        mScreenWidth = scale * screenRect.size.width;
        mScreenHeight = scale * screenRect.size.height;
    }

    uint32_t OSXDeviceInfo::getPlatform() const
    {
        return E_PLATFORM_OSX;
    }

    const String &OSXDeviceInfo::getSoftwareVersion() const
    {
        return mSWVersion;
    }

    void OSXDeviceInfo::setSoftwareVersion(const char *version)
    {
        
    }

    const String &OSXDeviceInfo::getOSVersion() const
    {
        return mOSVersion;
    }

    const String &OSXDeviceInfo::getDeviceVersion() const
    {
        return mHWVersion;
    }
    
    const String &OSXDeviceInfo::getCPUArchitecture() const
    {
        return mCPUArchitecture;
    }

    int32_t OSXDeviceInfo::getScreenWidth() const
    {
        return mScreenWidth;
    }

    int32_t OSXDeviceInfo::getScreenHeight() const
    {
        return mScreenHeight;
    }

    float OSXDeviceInfo::getScreenDPI() const
    {
        return mScreenDPI;
    }

//    const String &OSXDeviceInfo::getMacAddress() const
//    {
//        if (mMacAddress.empty())
//        {
//            NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
//            kern_return_t kr;
//            CFMutableDictionaryRef matchDict;
//            io_iterator_t iterator;
//            io_registry_entry_t entry;
//
//            matchDict = IOServiceMatching("IOEthernetInterface");
//            kr = IOServiceGetMatchingServices(kIOMasterPortDefault, matchDict, &iterator);
//
//            NSDictionary *resultInfo = nil;
//
//            while ((entry = IOIteratorNext(iterator)) != 0)
//            {
//                CFMutableDictionaryRef properties=NULL;
//                kr = IORegistryEntryCreateCFProperties(entry,
//                                                       &properties,
//                                                       kCFAllocatorDefault,
//                                                       kNilOptions);
//                if (properties)
//                {
//                    resultInfo = (NSDictionary *)properties;
//                    NSString *bsdName = [resultInfo objectForKey:@"BSD Name"];
//                    NSData *macData = [resultInfo objectForKey:@"IOMACAddress"];
//                    if (!macData)
//                    {
//                        continue;
//                    }
//
//                    NSMutableString *macAddress = [[NSMutableString alloc] init];
//                    uint8_t *bytes = (uint8_t *)[macData bytes];
//                    for (int i = 0; i < macData.length - 1; i++)
//                    {
//                        [macAddress appendFormat:@"%02x", *(bytes+i)];
//                        [macAddress appendString:@"-"];
//                    }
//
//                    [macAddress appendFormat:@"%02x", *(bytes + macData.length - 1)];
//
//                    //打印Mac地址
//                    if (bsdName && macAddress)
//                    {
//                        mMacAddress = [macAddress UTF8String];
//                    }
//
//                    [macAddress release];
//                    CFRelease(properties);
//                    break;
//                }
//            }
//
//            IOObjectRelease(iterator);
//            [pool release];
//        }
//
//        return mMacAddress;
//    }

    const String &OSXDeviceInfo::getCPUType() const
    {
        return mCPUType;
    }

    int32_t OSXDeviceInfo::getCPUCores() const
    {
        return mCPUCores;
    }

    uint32_t OSXDeviceInfo::getSystemRAM() const
    {
        return mSystemRAM;
    }

    const String &OSXDeviceInfo::getDeviceID() const
    {
        return mDeviceID;
    }
}
