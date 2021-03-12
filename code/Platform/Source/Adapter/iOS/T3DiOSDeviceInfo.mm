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

#include "Adapter/iOS/T3DiOSDeviceInfo.h"
#include "Adapter/T3DFactoryInterface.h"
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/utsname.h>
#include <mach/mach_host.h>
#include <sstream>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "UICKeyChainStore.h"

namespace Tiny3D
{
    NSString *getAccessGroup()
    {
        NSDictionary *query = [NSDictionary dictionaryWithObjectsAndKeys:
                               (NSString *)kSecClassGenericPassword,
                               kSecClass,
                               @"bundleSeedID",
                               kSecAttrAccount,
                               @"",
                               kSecAttrService,
                               (id)kCFBooleanTrue,
                               kSecReturnAttributes,
                               nil];
        CFDictionaryRef result = nil;
        OSStatus status = SecItemCopyMatching((CFDictionaryRef)query,
                                              (CFTypeRef *)&result);
        if (status == errSecItemNotFound)
            status = SecItemAdd((CFDictionaryRef)query, (CFTypeRef *)&result);
        if (status != errSecSuccess)
            return nil;
        
        NSString *accessGroup = [NSString
                                 stringWithString:[(NSDictionary *)result
                                                   objectForKey:(NSString*)kSecAttrAccessGroup]];
        CFRelease(result);
        return accessGroup;
    }
    
    iOSDeviceInfo::iOSDeviceInfo()
        : mCPUCores(0)
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

    iOSDeviceInfo::~iOSDeviceInfo()
    {

    }
    
    void iOSDeviceInfo::collectOSInfo()
    {
        // Software Version
        if (mSWVersion.empty())
        {
            NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
            NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
            NSString *version = [infoDictionary objectForKey:@"CFBundleVersion"];
            mSWVersion = [version UTF8String];
            [pool release];
        }
        
        // Operating System Version
        if (mOSVersion.empty())
        {
            NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
            String name = [[UIDevice currentDevice].systemName UTF8String];
            String version = [[UIDevice currentDevice].systemVersion UTF8String];
            [pool release];
            mOSVersion = name + " " + version;
        }
        
    }
    
    void iOSDeviceInfo::collectCPUInfo()
    {
        // CPU Type
        if (mCPUType.empty())
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
            }
            else
            {
                ss<<"("<<subtype<<")";
            }
            
            mCPUType = ss.str();
            mCPUArchitecture = mCPUType;
        }
        
        // CPU Cores
        if (mCPUCores == 0)
        {
            NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
            mCPUCores = (int32_t)[NSProcessInfo processInfo].processorCount;
            [pool release];
        }
    }
    
    void iOSDeviceInfo::collectRAMInfo()
    {
        if (mSystemRAM == 0)
        {
            NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
            int64_t size = [NSProcessInfo processInfo].physicalMemory;
            [pool release];
            mSystemRAM = (uint32_t)(size / (1024 * 1024));
        }
    }
    
    void iOSDeviceInfo::collectDeviceInfo()
    {
        // Device Version
        if (mHWVersion.empty())
        {
            struct utsname systemInfo;
            uname(&systemInfo);
            String machine = systemInfo.machine;
            
            if (machine == "iPhone3,1")
                mHWVersion = "iPhone 4";
            else if (machine == "iPhone3,2")
                mHWVersion = "iPhone 4";
            else if (machine == "iPhone3,3")
                mHWVersion = "iPhone 4";
            else if (machine == "iPhone4,1")
                mHWVersion = "iPhone 4S";
            else if (machine == "iPhone5,1")
                mHWVersion = "iPhone 5";
            else if (machine == "iPhone5,2")
                mHWVersion = "iPhone 5 (GSM+CDMA)";
            else if (machine == "iPhone5,3")
                mHWVersion = "iPhone 5c (GSM)";
            else if (machine == "iPhone5,4")
                mHWVersion = "iPhone 5c (GSM+CDMA)";
            else if (machine == "iPhone6,1")
                mHWVersion = "iPhone 5s (GSM)";
            else if (machine == "iPhone6,2")
                mHWVersion = "iPhone 5s (GSM+CDMA)";
            else if (machine == "iPhone7,1")
                mHWVersion = "iPhone 6 Plus";
            else if (machine == "iPhone7,2")
                mHWVersion = "iPhone 6";
            else if (machine == "iPhone8,1")
                mHWVersion = "iPhone 6s";
            else if (machine == "iPhone8,2")
                mHWVersion = "iPhone 6s Plus";
            else if (machine == "iPhone8,4")
                mHWVersion = "iPhone SE";
            // 日行两款手机型号均为日本独占，可能使用索尼FeliCa支付方案而不是苹果支付
            else if (machine == "iPhone9,1")
                mHWVersion = "国行、日版、港行iPhone 7";
            else if (machine == "iPhone9,2")
                mHWVersion = "港行、国行iPhone 7 Plus";
            else if (machine == "iPhone9,3")
                mHWVersion = "美版、台版iPhone 7";
            else if (machine == "iPhone9,4")
                mHWVersion = "美版、台版iPhone 7 Plus";
            else if (machine == "iPhone10,1")
                mHWVersion = "国行(A1863)、日行(A1906)iPhone 8";
            else if (machine == "iPhone10,4")
                mHWVersion = "美版(Global/A1905)iPhone 8";
            else if (machine == "iPhone10,2")
                mHWVersion = "国行(A1864)、日行(A1898)iPhone 8 Plus";
            else if (machine == "iPhone10,5")
                mHWVersion = "美版(Global/A1897)iPhone 8 Plus";
            else if (machine == "iPhone10,3")
                mHWVersion = "国行(A1865)、日行(A1902)iPhone X";
            else if (machine == "iPhone10,6")
                mHWVersion = "美版(Global/A1901)iPhone X";
            else if (machine == "iPod1,1")
                mHWVersion = "iPod Touch 1G";
            else if (machine == "iPod2,1")
                mHWVersion = "iPod Touch 2G";
            else if (machine == "iPod3,1")
                mHWVersion = "iPod Touch 3G";
            else if (machine == "iPod4,1")
                mHWVersion = "iPod Touch 4G";
            else if (machine == "iPod5,1")
                mHWVersion = "iPod Touch (5 Gen)";
            else if (machine == "iPad1,1")
                mHWVersion = "iPad";
            else if (machine == "iPad1,2")
                mHWVersion = "iPad 3G";
            else if (machine == "iPad2,1")
                mHWVersion = "iPad 2 (WiFi)";
            else if (machine == "iPad2,2")
                mHWVersion = "iPad 2";
            else if (machine == "iPad2,3")
                mHWVersion = "iPad 2 (CDMA)";
            else if (machine == "iPad2,4")
                mHWVersion = "iPad 2";
            else if (machine == "iPad2,5")
                mHWVersion = "iPad Mini (WiFi)";
            else if (machine == "iPad2,6")
                mHWVersion = "iPad Mini";
            else if (machine == "iPad2,7")
                mHWVersion = "iPad Mini (GSM+CDMA)";
            else if (machine == "iPad3,1")
                mHWVersion = "iPad 3 (WiFi)";
            else if (machine == "iPad3,2")
                mHWVersion = "iPad 3 (GSM+CDMA)";
            else if (machine == "iPad3,3")
                mHWVersion = "iPad 3";
            else if (machine == "iPad3,4")
                mHWVersion = "iPad 4 (WiFi)";
            else if (machine == "iPad3,5")
                mHWVersion = "iPad 4";
            else if (machine == "iPad3,6")
                mHWVersion = "iPad 4 (GSM+CDMA)";
            else if (machine == "iPad4,1")
                mHWVersion = "iPad Air (WiFi)";
            else if (machine == "iPad4,2")
                mHWVersion = "iPad Air (Cellular)";
            else if (machine == "iPad4,4")
                mHWVersion = "iPad Mini 2 (WiFi)";
            else if (machine == "iPad4,5")
                mHWVersion = "iPad Mini 2 (Cellular)";
            else if (machine == "iPad4,6")
                mHWVersion = "iPad Mini 2";
            else if (machine == "iPad4,7")
                mHWVersion = "iPad Mini 3";
            else if (machine == "iPad4,8")
                mHWVersion = "iPad Mini 3";
            else if (machine == "iPad4,9")
                mHWVersion = "iPad Mini 3";
            else if (machine == "iPad5,1")
                mHWVersion = "iPad Mini 4 (WiFi)";
            else if (machine == "iPad5,2")
                mHWVersion = "iPad Mini 4 (LTE)";
            else if (machine == "iPad5,3")
                mHWVersion = "iPad Air 2";
            else if (machine == "iPad5,4")
                mHWVersion = "iPad Air 2";
            else if (machine == "iPad6,3")
                mHWVersion = "iPad Pro 9.7";
            else if (machine == "iPad6,4")
                mHWVersion = "iPad Pro 9.7";
            else if (machine == "iPad6,7")
                mHWVersion = "iPad Pro 12.9";
            else if (machine == "iPad6,8")
                mHWVersion = "iPad Pro 12.9";
            else if (machine == "iPad6,11")
                mHWVersion = "iPad 5 (WiFi)";
            else if (machine == "iPad6,12")
                mHWVersion = "iPad 5 (Cellular)";
            else if (machine == "iPad7,1")
                mHWVersion = "iPad Pro 12.9 inch 2nd gen (WiFi)";
            else if (machine == "iPad7,2")
                mHWVersion = "iPad Pro 12.9 inch 2nd gen (Cellular)";
            else if (machine == "iPad7,3")
                mHWVersion = "iPad Pro 10.5 inch (WiFi)";
            else if (machine == "iPad7,4")
                mHWVersion = "iPad Pro 10.5 inch (Cellular)";
            else if (machine == "AppleTV2,1")
                mHWVersion = "Apple TV 2";
            else if (machine == "AppleTV3,1")
                mHWVersion = "Apple TV 3";
            else if (machine == "AppleTV3,2")
                mHWVersion = "Apple TV 3";
            else if (machine == "AppleTV5,3")
                mHWVersion = "Apple TV 4";
            else if (machine == "i386")
                mHWVersion = "Simulator";
            else if (machine == "x86_64")
                mHWVersion = "Simulator";
        }
        
        // Device ID
        if (mDeviceID.empty())
        {
            NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
            
            NSString *accessGroup = getAccessGroup();
            UICKeyChainStore *keychain = [UICKeyChainStore
                                          keyChainStoreWithService:accessGroup];
            NSString *Identifier = [keychain stringForKey:@"uuid"];
            
            if (nil == Identifier || [Identifier isEqualToString:@""])
            {
                NSString *uuid = [[[UIDevice currentDevice] identifierForVendor]
                                  UUIDString];
                Identifier = uuid;
                keychain[@"uuid"] = Identifier;
            }
            
            mDeviceID = [Identifier UTF8String];
            [pool release];
        }
    }
    
    void iOSDeviceInfo::collectScreenInfo()
    {
        // Screen Size
        CGSize size = [UIScreen mainScreen].bounds.size;
        CGFloat scale = 1.0f;
        
        if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)])
        {
            scale = [UIScreen mainScreen].scale;
        }
        
        mScreenWidth = scale * size.width;
        mScreenHeight = scale * size.height;
        
        // Screen DPI
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
        {
            mScreenDPI = 132 * scale;
        }
        else if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
        {
            mScreenDPI = 163 * scale;
        }
        else
        {
            mScreenDPI = 160 * scale;
        }
    }

    uint32_t iOSDeviceInfo::getPlatform() const
    {
        return E_PLATFORM_IOS;
    }

    const String &iOSDeviceInfo::getSoftwareVersion() const
    {
        return mSWVersion;
    }

    void iOSDeviceInfo::setSoftwareVersion(const char *version)
    {
        
    }

    const String &iOSDeviceInfo::getOSVersion() const
    {
        return mOSVersion;
    }

    const String &iOSDeviceInfo::getDeviceVersion() const
    {
        return mHWVersion;
    }

    int32_t iOSDeviceInfo::getScreenWidth() const
    {
        return mScreenWidth;
    }

    int32_t iOSDeviceInfo::getScreenHeight() const
    {
        return mScreenHeight;
    }

    float iOSDeviceInfo::getScreenDPI() const
    {
        return mScreenDPI;
    }

    const String &iOSDeviceInfo::getCPUType() const
    {
        return mCPUType;
    }
    
    const String &iOSDeviceInfo::getCPUArchitecture() const
    {
        return mCPUArchitecture;
    }

    int32_t iOSDeviceInfo::getCPUCores() const
    {
        return mCPUCores;
    }

    uint32_t iOSDeviceInfo::getSystemRAM() const
    {
        return mSystemRAM;
    }

    const String &iOSDeviceInfo::getDeviceID() const
    {
        return mDeviceID;
    }
}
