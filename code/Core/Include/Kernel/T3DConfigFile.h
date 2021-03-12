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


#ifndef __T3D_CONFIG_FILE_H__
#define __T3D_CONFIG_FILE_H__


#include "T3DPrerequisites.h"
#include "T3DTypedef.h"


namespace tinyxml2
{
    class XMLDocument;
    class XMLElement;
}


namespace Tiny3D
{
    /**
     * @class   ConfigFile
     * @brief   配置文件类，用于读写配置文件，支持二进制和XML格式
     */
    class T3D_ENGINE_API ConfigFile
    {
    public:
        /**
         * @fn  ConfigFile::ConfigFile(const String &filename, 
         *      ArchivePtr archive = nullptr);
         * @brief   构造函数
         * @param [in]  filename    : 配置文件名.
         * @param [in]  archive     (Optional) : 配置文件所在的档案结构。 
         *              默认值为nullptr。 当为默认值时，filename 需要是绝对路径。 
         *              如果指定档案结构对象， 则 filename 是相对档案结构根
         *              目录的相对路径。.
         */
        ConfigFile(const String &filename, ArchivePtr archive = nullptr);

        /**
         * @fn  virtual ConfigFile::~ConfigFile();
         * @brief   析构函数
         */
        virtual ~ConfigFile();

        /**
         * @fn  TResult ConfigFile::loadXML(Settings &settings);
         * @brief   从XML格式文件加载
         * @param [in]  settings    settings : 设置项对象.
         * @return  调用成功返回T3D_OK。.
         */
        TResult loadXML(Settings &settings);

        /**
         * @fn  TResult ConfigFile::saveXML(const Settings &settings);
         * @brief   把设置项写到XML格式文件中
         * @param [in]  settings    : 要保存的设置项.
         * @return  调用成功返回true，否则返回false。.
         */
        TResult saveXML(const Settings &settings);

        /**
         * @fn  bool ConfigFile::loadBinary(Settings &settings);
         * @brief   从二进制格式文件加载
         * @param [in]  settings    settings : 设置项对象.
         * @return  调用成功返回true，否则返回false。.
         */
        bool loadBinary(Settings &settings);

        /**
         * @fn  bool ConfigFile::saveBinary(const Settings &settings);
         * @brief   把设置项写到二进制格式文件中
         * @param [in]  settings    : 要保存的设置项.
         * @return  调用成功返回true，否则返回false。.
         */
        bool saveBinary(const Settings &settings);

    protected:
        /**
         * @fn  TResult ConfigFile::parseXML(const tinyxml2::XMLDocument &doc, 
         *      Settings &settings);
         * @brief   解析 XML 格式
         * @param           doc         The document.
         * @param [in,out]  settings    Options for controlling the operation.
         * @return  A TResult.
         */
        TResult parseXML(
            const tinyxml2::XMLDocument &doc, Settings &settings);

        /**
         * @fn  TResult ConfigFile::parseXMLDict(
         *      const tinyxml2::XMLElement *root, VariantMap &dict);
         * @brief   解析 XML 格式字典结构容器
         * @param           root    The root.
         * @param [in,out]  dict    The dictionary.
         * @return  A TResult.
         */
        TResult parseXMLDict(
            const tinyxml2::XMLElement *root, VariantMap &dict);

        /**
         * @fn  TResult ConfigFile::parseXMLArray(
         *      const tinyxml2::XMLElement *root, VariantArray &arr);
         * @brief   解析 XML 格式数组结构容器
         * @param           root    The root.
         * @param [in,out]  arr     The array.
         * @return  A TResult.
         */
        TResult parseXMLArray(
            const tinyxml2::XMLElement *root, VariantArray &arr);

        /**
         * @fn  TResult ConfigFile::buildXML(tinyxml2::XMLDocument &doc, 
         *      const Settings &settings);
         * @brief   构建 XML 格式
         * @param [in,out]  doc         The document.
         * @param           settings    Options for controlling the operation.
         * @return  A TResult.
         */
        TResult buildXML(
            tinyxml2::XMLDocument &doc, const Settings &settings);

        /**
         * @fn  TResult ConfigFile::buildXMLDict(tinyxml2::XMLDocument &doc, 
         *      tinyxml2::XMLElement *root, const VariantMap &dict);
         * @brief   从字典结构容器构建XML
         * @param [in,out]  doc     The document.
         * @param [in,out]  root    If non-null, the root.
         * @param           dict    The dictionary.
         * @return  A TResult.
         */
        TResult buildXMLDict(tinyxml2::XMLDocument &doc, 
            tinyxml2::XMLElement *root,
            const VariantMap &dict);

        /**
         * @fn  TResult ConfigFile::buildXMLArray(tinyxml2::XMLDocument &doc, 
         *      tinyxml2::XMLElement *root, const VariantArray &arr);
         * @brief   从数组结构容器构建XML
         * @param [in,out]  doc     The document.
         * @param [in,out]  root    If non-null, the root.
         * @param           arr     The array.
         * @return  A TResult.
         */
        TResult buildXMLArray(tinyxml2::XMLDocument &doc, 
            tinyxml2::XMLElement *root,
            const VariantArray &arr);

        /**
         * @fn  TResult ConfigFile::buildXMLList(tinyxml2::XMLDocument &doc, 
         *      tinyxml2::XMLElement *root, const VariantList &list);
         * @brief   Builds XML list
         * @param [in,out]  doc     The document.
         * @param [in,out]  root    If non-null, the root.
         * @param           list    The list.
         * @return  A TResult.
         */
        TResult buildXMLList(tinyxml2::XMLDocument &doc,
            tinyxml2::XMLElement *root,
            const VariantList &list);

        /**
         * @fn  TResult ConfigFile::buildXMLVariant(tinyxml2::XMLDocument &doc, 
         *      tinyxml2::XMLElement *root, const Variant &value);
         * @brief   根据可变类型对象构建XML
         * @param [in,out]  doc     The document.
         * @param [in,out]  root    If non-null, the root.
         * @param           value   The value.
         * @return  A TResult.
         */
        TResult buildXMLVariant(tinyxml2::XMLDocument &doc, 
            tinyxml2::XMLElement *root,
            const Variant &value);

        /**
         * @fn  bool ConfigFile::parseBinary(DataStream &stream, 
         *      Settings &settings);
         * @brief   解析二进制格式
         * @param [in,out]  stream      The stream.
         * @param [in,out]  settings    Options for controlling the operation.
         * @return  True if it succeeds, false if it fails.
         */
        bool parseBinary(DataStream &stream, Settings &settings);

        /**
         * @fn  bool ConfigFile::parseBinDict(DataStream &stream, 
         *      VariantMap &dict);
         * @brief   解析二进制格式字段结构容器
         * @param [in,out]  stream  The stream.
         * @param [in,out]  dict    The dictionary.
         * @return  True if it succeeds, false if it fails.
         */
        bool parseBinDict(DataStream &stream, VariantMap &dict);

        /**
         * @fn  bool ConfigFile::parseBinArray(DataStream &stream, 
         *      VariantArray &arr);
         * @brief   解析二进制格式数组结构容器
         * @param [in,out]  stream  The stream.
         * @param [in,out]  arr     The array.
         * @return  True if it succeeds, false if it fails.
         */
        bool parseBinArray(DataStream &stream, VariantArray &arr);

        /**
         * @fn  bool ConfigFile::buildBinDict(DataStream &stream, 
         *      const VariantMap &dict);
         * @brief   用字典结构容器构建二进制数据
         * @param [in,out]  stream  The stream.
         * @param           dict    The dictionary.
         * @return  True if it succeeds, false if it fails.
         */
        bool buildBinDict(DataStream &stream, const VariantMap &dict);

        /**
         * @fn  bool ConfigFile::buildBinArray(DataStream &stream, 
         *      const VariantArray &arr);
         * @brief   用数组结构容器构建二进制数据
         * @param [in,out]  stream  The stream.
         * @param           arr     The array.
         * @return  True if it succeeds, false if it fails.
         */
        bool buildBinArray(DataStream &stream, const VariantArray &arr);

        /**
         * @fn  bool ConfigFile::buildBinVariant(DataStream &stream, 
         *      const Variant &value);
         * @brief   用可变类型对象构建二进制数据
         * @param [in,out]  stream  The stream.
         * @param           value   The value.
         * @return  True if it succeeds, false if it fails.
         */
        bool buildBinVariant(DataStream &stream, const Variant &value);

    private:
        String      mFilename;  /**< 配置文件名 */
        ArchivePtr  mArchive;   /**< 配置文件所在的档案结构对象 */
    };
}


#endif  /*__T3D_CONFIG_FILE_H__*/
