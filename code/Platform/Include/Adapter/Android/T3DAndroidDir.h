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

#ifndef __T3D_ANDROID_DIR_H__
#define __T3D_ANDROID_DIR_H__

#include "Adapter/Unix/T3DUnixDir.h"

namespace Tiny3D
{
    class AndroidDir : public UnixDir
    {
    public:
		AndroidDir();
        virtual ~AndroidDir();
		
		virtual long_t getCreationTime() const override;
		
		virtual long_t getLastAccessTime() const override;
		
		virtual long_t getLastWriteTime() const override;
		
		/**
		 * @brief 获取应用程序缓存数据存储路径，不同平台指定对应的路径
		 * @return 返回应用程序缓存数据存储路径.
		 */
		virtual String getCachePath() const override;
		
		/**
		 * @brief 获取应用程序路径
		 * @return 返回应用程序路径
		 */
		virtual String getAppPath() const override;
        
        /**
         * @brief 获取应用程序可写路径，不同平台指定对应的路径
         * @return 返回应用程序可写路径.
         */
        virtual String getWritablePath() const override;

		/**
         * @brief 获取动态库路径
         * @return 返回动态库路径
         * @remarks 本接口在android上才有效，其他平台跟getAppPath()相同
         */
		virtual String getLibraryPath() const override;

	protected:
    	String	mApkPath;
    };
}


#endif  /*__T3D_ANDROID_DIR_H__*/
