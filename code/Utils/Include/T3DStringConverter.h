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

#ifndef __T3D_STRING_CONVERTER_H__
#define __T3D_STRING_CONVERTER_H__


#include "T3DUtilsPrerequisites.h"
#include "T3DFix32.h"
#include "T3DFix64.h"


namespace Tiny3D
{
    class T3D_UTILS_API StringConverter
    {
    public:
        /**
         * @brief 把单精度浮点数转换成字符串
         * @param [in] val : 单精度浮点数值
         * @param [in] precision : 精度
         * @param [in] width : 最大宽度
         * @param [in] fill : 不足宽度时填充的字符
         * @param [in] flags : 标记，请参考std::ios::fmtflags
         * @return 返回字符串对象
         */
        static String toString(float32_t val, uint16_t precision = 6,
            uint16_t width = 0, char fill = ' ',
            std::ios::fmtflags flags = std::ios::fmtflags(0));

        /**
         * @brief 把双精度浮点数转换成字符串
         * @param [in] val : 单精度浮点数值
         * @param [in] precision : 精度
         * @param [in] width : 最大宽度
         * @param [in] fill : 不足宽度时填充的字符
         * @param [in] flags : 标记，请参考std::ios::fmtflags
         * @return 返回字符串对象
         */
        static String toString(float64_t val, uint16_t precision = 6,
            uint16_t width = 0, char fill = ' ',
            std::ios::fmtflags flags = std::ios::fmtflags(0));

        /**
         * @brief 把32位定点数转换成字符串
         * @param [in] val : 32位定点数值
         * @param [in] precision : 精度
         * @param [in] width : 最大宽度
         * @param [in] fill : 不足宽度时填充的字符
         * @param [in] flags : 标记，请参考std::ios::fmtflags
         * @return 返回字符串对象
         */
        static String toString(fix32_t val, uint16_t precision = 6,
            uint16_t width = 0, char fill = ' ',
            std::ios::fmtflags flags = std::ios::fmtflags(0));

        /**
         * @brief 把64位定点数转换成字符串
         * @param [in] val : 32位定点数值
         * @param [in] precision : 精度
         * @param [in] width : 最大宽度
         * @param [in] fill : 不足宽度时填充的字符
         * @param [in] flags : 标记，请参考std::ios::fmtflags
         * @return 返回字符串对象
         */
        static String toString(fix64_t val, uint16_t precision = 6,
            uint16_t width = 0, char fill = ' ',
            std::ios::fmtflags flags = std::ios::fmtflags(0));

        /**
         * @brief 把32位整型转换成字符串
         * @param [in] val : 32位整型数值
         * @param [in] width : 最大宽度
         * @param [in] fill : 不足宽度时填充的字符
         * @param [in] flags : 标记，请参考std::ios::fmtflags
         * @return 返回字符串对象
         */
        static String toString(int32_t val, 
            uint16_t width = 0, char fill = ' ', 
            std::ios::fmtflags flags = std::ios::fmtflags(0));

        /**
         * @brief 把32位无符号整型转换成字符串
         * @param [in] val : 32位无符号整型数值
         * @param [in] width : 最大宽度
         * @param [in] fill : 不足宽度时填充的字符
         * @param [in] flags : 标记，请参考std::ios::fmtflags
         * @return 返回字符串对象
         */
        static String toString(uint32_t val, 
            uint16_t width = 0, char fill = ' ', 
            std::ios::fmtflags flags = std::ios::fmtflags(0));

        /**
         * @brief 把长度相关整型转换成字符串
         * @param [in] val : 长度相关整型数值
         * @param [in] width : 最大宽度
         * @param [in] fill : 不足宽度时填充的字符
         * @param [in] flags : 标记，请参考std::ios::fmtflags
         * @return 返回字符串对象
         */
//         static String toString(size_t val,
//             uint16_t width = 0, char fill = ' ',
//             std::ios::fmtflags flags = std::ios::fmtflags(0));

        /**
         * @brief 把OS字长相关有符号整型转换成字符串
         * @param [in] val : OS字长相关有符号整型数值
         * @param [in] width : 最大宽度
         * @param [in] fill : 不足宽度时填充的字符
         * @param [in] flags : 标记，请参考std::ios::fmtflags
         * @return 返回字符串对象
         */
        static String toString(long_t val,
            uint16_t width = 0, char fill = ' ',
            std::ios::fmtflags flags = std::ios::fmtflags(0));

        /**
         * @brief 把OS字长相关无符号整型转换成字符串
         * @param [in] val : OS字长相关无符号整型数值
         * @param [in] width : 最大宽度
         * @param [in] fill : 不足宽度时填充的字符
         * @param [in] flags : 标记，请参考std::ios::fmtflags
         * @return 返回字符串对象
         */
        static String toString(ulong_t val,
            uint16_t width = 0, char fill = ' ',
            std::ios::fmtflags flags = std::ios::fmtflags(0));

        /**
         * @brief 把布尔型转换成字符串
         * @param [in] val : 布尔型数值
         * @param [in] width : 最大宽度
         * @param [in] fill : 不足宽度时填充的字符
         * @param [in] flags : 标记，请参考std::ios::fmtflags
         * @return 返回字符串对象
         */
        static String toString(bool val,
            uint16_t width = 0, char fill = ' ',
            std::ios::fmtflags flags = std::ios::fmtflags(0));

        /**
         * @brief 把一个字符串转换成一个单精度浮点数
         * @param [in] val : 字符串
         * @param [in] defaultValue : 默认值
         * @return 返回一个单精度浮点数
         */
        static float32_t parseSingle(const String &val, 
            float32_t defaultValue = 0.0f);

        /**
         * @brief 把一个字符串转换成一个双精度浮点数
         * @param [in] val : 字符串
         * @param [in] defaultValue : 默认值
         * @return 返回一个双精度浮点数
         */
        static float64_t parseDouble(const String &val,
            float64_t defaultValue = 0.0);

        /**
         * @brief 把一个字符串转换成一个有符号32位整型数
         * @param [in] val : 字符串
         * @param [in] defaultValue : 默认值
         * @return 返回一个有符号32位整型数
         */
        static int32_t parseInt32(const String &val, 
            int32_t defaultValue = 0);

        /**
         * @brief 把一个字符串转换成一个无符号32位整型数
         * @param [in] val : 字符串
         * @param [in] defaultValue : 默认值
         * @return 返回一个无符号32位整型数
         */
        static uint32_t parseUInt32(const String &val, 
            uint32_t defaultValue = 0);

        /**
         * @brief 把一个字符串转换成一个有符号系统字长整型数
         * @param [in] val : 字符串
         * @param [in] defaultValue : 默认值
         * @return 返回一个有符号系统字长整型数
         */
        static long_t parseLong(const String &val, 
            long_t defaultValue = 0);

        /**
         * @brief 把一个字符串转换成一个无符号系统字长整型数
         * @param [in] val : 字符串
         * @param [in] defaultValue : 默认值
         * @return 返回一个无符号系统字长整型数
         */
        static ulong_t parseULong(const String &val, 
            ulong_t defaultValue = 0);

        /**
         * @brief 把一个字符串转换成一个长度整型数
         * @param [in] val : 字符串
         * @param [in] defaultValue : 默认值
         * @return 返回一个长度整型数
         */
        static size_t parseSizeT(const String &val, 
            size_t defaultValue = 0);

        /**
         * @brief 把一个字符串转换成一个布尔类型数
         * @param [in] val : 字符串
         * @param [in] defaultValue : 默认值
         * @return 返回一个布尔类型数
         */
        static bool parseBool(const String &val, 
            bool defaultValue = false);

        /**
         * @brief 是否数字
         * @param [in] val : 数字字符串
         * @return 是数字返回true
         */
        static bool isNumber(const String& val);
    };
}


#endif  /*__T3D_STRING_CONVERTER_H__*/
