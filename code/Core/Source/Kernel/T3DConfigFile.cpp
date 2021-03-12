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


#include "Kernel/T3DConfigFile.h"
#include "Support/tinyxml2/tinyxml2.h"
#include "T3DErrorDef.h"
#include "Resource/T3DArchive.h"
#include "Resource/T3DArchiveManager.h"
#include <sstream>

namespace Tiny3D
{
    #define TAG_NAME_PLIST          "plist"
    #define TAG_NAME_KEY            "key"

    #define TAG_NAME_STRING         "string"
    #define TAG_NAME_REAL           "real"
    #define TAG_NAME_INTEGER        "integer"
    #define TAG_NAME_TRUE           "true"
    #define TAG_NAME_FALSE          "false"
    #define TAG_NAME_DATE           "date"
    #define TAG_NAME_DATA           "data"
    #define TAG_NAME_ARRAY          "array"
    #define TAG_NAME_DICT           "dict"
    #define TAG_NAME_BOOL           "bool"

    //--------------------------------------------------------------------------

    ConfigFile::ConfigFile(const String &filename, 
        ArchivePtr archive /* = nullptr */)
        : mFilename(filename)
        , mArchive(archive)
    {

    }

    ConfigFile::~ConfigFile()
    {

    }

    //--------------------------------------------------------------------------

    TResult ConfigFile::loadXML(Settings &settings)
    {
        TResult ret = T3D_ERR_FAIL;

        do 
        {
            MemoryDataStream stream;
            char *content = nullptr;
            size_t contentSize = 0;

            if (mArchive != nullptr)
            {
                // 从档案结构系统中获取文件内容
                ret = mArchive->read(mFilename, stream);
                if (T3D_FAILED(ret))
                {
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE, 
                        "Read config file [%s] failed !",
                        mFilename.c_str());
                    break;
                }

                stream.getBuffer((uint8_t *&)content, contentSize);
            }
            else
            {
                // 配置文件不在某种档案结构管理里面，就在本地文件系统，直接访问。
                FileDataStream fs;
                if (!fs.open(mFilename.c_str(), 
                    FileDataStream::E_MODE_READ_ONLY))
                {
                    ret = T3D_ERR_FILE_NOT_EXIST;
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE, 
                        "Open config file [%s] failed !",
                        mFilename.c_str());
                    break;
                }

                contentSize = fs.size();
                content = new char[contentSize];
                if (fs.read(content, contentSize) != contentSize)
                {
                    fs.close();
                    ret = T3D_ERR_FILE_DATA_MISSING;
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE, 
                        "Read config file [%s] data failed !",
                        mFilename.c_str());
                    break;
                }

                fs.close();
            }
            
            // 解析 XML 格式
            tinyxml2::XMLDocument doc;
            if (doc.Parse(content, contentSize) != tinyxml2::XML_NO_ERROR)
            {
                ret = T3D_ERR_CFG_FILE_PARSING_XML;
                T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE,
                    "Parse xml config file [%s] failed !",
                    mFilename.c_str());
                break;
            }

            ret = parseXML(doc, settings);
        } while (0);

        return ret;
    }

    TResult ConfigFile::parseXML(const tinyxml2::XMLDocument &doc, 
        Settings &settings)
    {
        TResult ret = T3D_OK;

        do 
        {
            const tinyxml2::XMLElement *plist 
                = doc.FirstChildElement(TAG_NAME_PLIST);
            if (plist == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE,
                    "Parse xml file [%s] failed ! Get xml node \
                    [plist] failed !", mFilename.c_str());
                break;
            }

            const tinyxml2::XMLElement *root 
                = plist->FirstChildElement(TAG_NAME_DICT);
            if (root == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE, 
                    "Parse xml file [%s] failed ! Get xml node \
                    [dict] failed !", mFilename.c_str());
                break;
            }

            ret = parseXMLDict(root, settings);
        } while (0);

        return ret;
    }

    TResult ConfigFile::parseXMLDict(const tinyxml2::XMLElement *root, 
        VariantMap &dict)
    {
        TResult ret = T3D_OK;

        bool bKeyFound = false;
        String key;
        const tinyxml2::XMLElement *child = root->FirstChildElement();

        while (child != nullptr)
        {
            String name = child->Name();

            if (name == TAG_NAME_KEY)   // key
            {
                if (bKeyFound)
                {
                    // wrong format
                    ret = T3D_ERR_CFG_FILE_XML_FORMAT;
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE,
                        "Parse xml file [%s] failed ! Error key  node !", 
                        mFilename.c_str());
                    break;
                }
                else
                {
                    // store tag value
                    key = child->GetText();
                    bKeyFound = true;
                }
            }
            else if (name == TAG_NAME_DICT) // dict
            {
                if (bKeyFound)
                {
                    bKeyFound = false;
                    VariantMap subDict;
                    ret = parseXMLDict(child, subDict);
                    if (ret == T3D_OK)
                        dict.insert(VariantMapValue(key, subDict));
                    else
                        break;
                }
                else
                {
                    // wrong format
                    ret = T3D_ERR_CFG_FILE_XML_FORMAT;
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE, 
                        "Parse xml file [%s] failed ! Error dict node !");
                    break;
                }
            }
            else if (name == TAG_NAME_ARRAY)    // array
            {
                if (bKeyFound)
                {
                    bKeyFound = false;
                    VariantArray subArray;
                    ret = parseXMLArray(child, subArray);
                    if (ret == T3D_OK)
                        dict.insert(VariantMapValue(key, subArray));
                    else
                        break;
                }
                else
                {
                    // wrong format
                    ret = T3D_ERR_CFG_FILE_XML_FORMAT;
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE, 
                        "Parse xml file [%s] failed ! Error array node !");
                    break;
                }
            }
            else if (name == TAG_NAME_STRING)
            {
                if (bKeyFound)
                {
                    bKeyFound = false;
                    String val = child->GetText();
                    dict.insert(VariantMapValue(key, val));
                }
                else
                {
                    ret = T3D_ERR_CFG_FILE_XML_FORMAT;
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE, 
                        "Parse xml file [%s] failed ! Error string node !");
                    break;
                }
            }
            else if (name == TAG_NAME_INTEGER)
            {
                if (bKeyFound)
                {
                    bKeyFound = false;
                    long_t val = atol(child->GetText());
                    dict.insert(VariantMapValue(key, (int64_t)val));
                }
                else
                {
                    ret = T3D_ERR_CFG_FILE_XML_FORMAT;
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE, 
                        "Parse xml file [%s] failed ! Error integer node !");
                    break;
                }
            }
            else if (name == TAG_NAME_REAL)
            {
                if (bKeyFound)
                {
                    bKeyFound = false;
                    Real val = Real(atof(child->GetText()));
                    dict.insert(VariantMapValue(key, val));
                }
                else
                {
                    ret = T3D_ERR_CFG_FILE_XML_FORMAT;
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE, 
                        "Parse xml file [%s] failed ! Error real node !");
                    break;
                }
            }
            else if (name == TAG_NAME_TRUE || name == TAG_NAME_FALSE)
            {
                if (bKeyFound)
                {
                    bKeyFound = false;
                    bool val = (name == TAG_NAME_TRUE);
                    dict.insert(VariantMapValue(key, val));
                }
                else
                {
                    ret = T3D_ERR_CFG_FILE_XML_FORMAT;
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE, 
                        "Parse xml file [%s] failed ! Error boolean node !");
                    break;
                }
            }
            else if (name == TAG_NAME_DATE)
            {
            }
            else if (name == TAG_NAME_DATA)
            {
            }

            child = child->NextSiblingElement();
        }

        return ret;
    }

    TResult ConfigFile::parseXMLArray(const tinyxml2::XMLElement *root, 
        VariantArray &arr)
    {
        TResult ret = T3D_OK;

        String key;
        const tinyxml2::XMLElement *child = root->FirstChildElement();

        while (child != nullptr)
        {
            String name = child->Name();

            if (name == TAG_NAME_DICT)
            {
                VariantMap subDict;
                ret = parseXMLDict(child, subDict);
                if (ret == T3D_OK)
                    arr.push_back(subDict);
                else
                    break;
            }
            else if (name == TAG_NAME_ARRAY)
            {
                VariantArray subArray;
                ret = parseXMLArray(child, subArray);
                if (ret == T3D_OK)
                    arr.push_back(subArray);
                else
                    break;
            }
            else if (name == TAG_NAME_TRUE)
            {
                bool val = true;
                arr.push_back(val);
            }
            else if (name == TAG_NAME_FALSE)
            {
                bool val = false;
                arr.push_back(val);
            }
            else if (name == TAG_NAME_INTEGER)
            {
                long_t val = atol(child->GetText());
                arr.push_back((int64_t)val);
            }
            else if (name == TAG_NAME_REAL)
            {
                Real val = Real(atof(child->GetText()));
                arr.push_back(val);
            }
            else if (name == TAG_NAME_STRING)
            {
                String val = child->GetText();
                arr.push_back(val);
            }
            else if (name == TAG_NAME_DATE)
            {

            }
            else if (name == TAG_NAME_DATA)
            {

            }

            child = child->NextSiblingElement();
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    TResult ConfigFile::saveXML(const Settings &settings)
    {
        TResult ret = T3D_OK;
        
        do 
        {
            // 构建 XML 格式文件
            tinyxml2::XMLDocument doc;
            ret = buildXML(doc, settings);
            if (T3D_FAILED(ret))
            {
                break;
            }

            // 构造内存文件，下面再根据具体的情况是写入对应的档案文件中
            tinyxml2::XMLPrinter printer;
            if (!doc.Accept(&printer))
            {
                ret = T3D_ERR_CFG_FILE_XML_FORMAT;
                T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE, 
                    "Write config file [%s] to memory failed !",
                    mFilename.c_str());
                break;
            }

            const char *content = printer.CStr();
            size_t contentSize = printer.CStrSize();

            if (mArchive != nullptr)
            {
                // 保存到档案系统中的文件
                MemoryDataStream stream((uchar_t*)content, contentSize);
                ret = mArchive->write(mFilename, stream);
                if (T3D_FAILED(ret))
                {
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE,
                        "Write config file [%s] failed !", mFilename.c_str());
                    break;
                }
            }
            else
            {
                // 保存到本地文件系统中的文件
                FileDataStream fs;
                if (!fs.open(mFilename.c_str(), FileDataStream::E_MODE_WRITE_ONLY))
                {
                    ret = T3D_ERR_FILE_NOT_EXIST;
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE,
                        "Open config file [%s] failed !", mFilename.c_str());
                    break;
                }

                if (fs.write((void *)content, contentSize) != contentSize)
                {
                    fs.close();
                    ret = T3D_ERR_FILE_DATA_MISSING;
                    T3D_LOG_ERROR(LOG_TAG_CONFIG_FILE,
                        "Write config file [%s] failed !", mFilename.c_str());
                    break;
                }

                fs.close();
            }
        } while (0);
        
        return ret;
    }

    TResult ConfigFile::buildXML(tinyxml2::XMLDocument &doc, 
        const Settings &settings)
    {
        tinyxml2::XMLDeclaration *decl = doc.NewDeclaration();
        doc.LinkEndChild(decl);

        // plist tag
        tinyxml2::XMLElement *plist = doc.NewElement(TAG_NAME_PLIST);
        doc.LinkEndChild(plist);

        // root tag
        tinyxml2::XMLElement *root = doc.NewElement(TAG_NAME_DICT);

        TResult ret = buildXMLDict(doc, root, settings);

        if (ret == T3D_OK)
        {
            plist->LinkEndChild(root);
        }

        return ret;
    }

    TResult ConfigFile::buildXMLDict(tinyxml2::XMLDocument &doc,
        tinyxml2::XMLElement *root, const VariantMap &dict)
    {
        TResult ret = T3D_OK;
        VariantMapConstItr itr = dict.begin();

        while (itr != dict.end())
        {
            tinyxml2::XMLElement *child = doc.NewElement(TAG_NAME_KEY);

            const Variant &key = itr->first;
            const Variant &value = itr->second;

            tinyxml2::XMLText *text = doc.NewText(key.stringValue().c_str());
            child->LinkEndChild(text);
            root->LinkEndChild(child);

            ret = buildXMLVariant(doc, root, value);
            if (T3D_FAILED(ret))
                break;

            ++itr;
        }

        return ret;
    }

    TResult ConfigFile::buildXMLArray(tinyxml2::XMLDocument &doc,
        tinyxml2::XMLElement *root, const VariantArray &arr)
    {
        TResult ret = T3D_OK;
//         tinyxml2::XMLElement *child = nullptr;
        VariantArrayConstItr itr = arr.begin();

        while (itr != arr.end())
        {
            const Variant &value = *itr;

            ret = buildXMLVariant(doc, root, value);
            if (T3D_FAILED(ret))
                break;

            ++itr;
        }

        return ret;
    }

    TResult ConfigFile::buildXMLList(tinyxml2::XMLDocument &doc, 
        tinyxml2::XMLElement *root, const VariantList &list)
    {
        TResult ret = T3D_OK;
//         tinyxml2::XMLElement *child = nullptr;
        VariantListConstItr itr = list.begin();

        while (itr != list.end())
        {
            const Variant &value = *itr;

            ret = buildXMLVariant(doc, root, value);
            if (T3D_FAILED(ret))
                break;

            ++itr;
        }

        return ret;
    }

    TResult ConfigFile::buildXMLVariant(tinyxml2::XMLDocument &doc, 
        tinyxml2::XMLElement *root, const Variant &value)
    {
        TResult ret = T3D_OK;

        do 
        {
            tinyxml2::XMLElement *child = nullptr;
            tinyxml2::XMLText *text = nullptr;

            if (value.valueType() == Variant::Type::E_BOOL)
            {
                bool val = value.boolValue();

                if (val)
                    child = doc.NewElement(TAG_NAME_TRUE);
                else
                    child = doc.NewElement(TAG_NAME_FALSE);

                root->LinkEndChild(child);
            }
            else if (value.valueType() == Variant::Type::E_INT8
                || value.valueType() == Variant::Type::E_UINT8
                || value.valueType() == Variant::Type::E_INT16
                || value.valueType() == Variant::Type::E_UINT16
                || value.valueType() == Variant::Type::E_INT32
                || value.valueType() == Variant::Type::E_UINT32
                || value.valueType() == Variant::Type::E_INT64
                || value.valueType() == Variant::Type::E_UINT64
                || value.valueType() == Variant::Type::E_LONG
                || value.valueType() == Variant::Type::E_ULONG)
            {
                long_t val = value.longValue();
                child = doc.NewElement(TAG_NAME_INTEGER);
//                 char buf[64] = { 0 };
//                 snprintf(buf, sizeof(buf) - 1, "%ld", val);
                std::stringstream ss;
                ss << val;
                text = doc.NewText(ss.str().c_str());
                child->LinkEndChild(text);
                root->LinkEndChild(child);
            }
            else if (value.valueType() == Variant::Type::E_FLOAT32
                || value.valueType() == Variant::Type::E_FLOAT64
                || value.valueType() == Variant::Type::E_FIX32
                || value.valueType() == Variant::Type::E_FIX64)
            {
                Real val = value.float32Value();
                child = doc.NewElement(TAG_NAME_REAL);
                char buf[64] = { 0 };
                snprintf(buf, sizeof(buf) - 1, "%f", val);
                text = doc.NewText(buf);
                child->LinkEndChild(text);
                root->LinkEndChild(child);
            }
            else if (value.valueType() == Variant::Type::E_STRING)
            {
                String val = value.stringValue();
                child = doc.NewElement(TAG_NAME_STRING);
                text = doc.NewText(val.c_str());
                child->LinkEndChild(text);
                root->LinkEndChild(child);
            }
            else if (value.valueType() == Variant::Type::E_ARRAY)
            {
                const VariantArray &val = value.arrayValue();
                child = doc.NewElement(TAG_NAME_ARRAY);
                ret = buildXMLArray(doc, child, val);
                if (ret == T3D_OK)
                    root->LinkEndChild(child);
                else
                    break;
            }
            else if (value.valueType() == Variant::Type::E_LIST)
            {
                const VariantList &val = value.listValue();
                child = doc.NewElement(TAG_NAME_ARRAY);
                ret = buildXMLList(doc, child, val);
                if (ret == T3D_OK)
                    root->LinkEndChild(child);
                else
                    break;
            }
            else if (value.valueType() == Variant::Type::E_MAP)
            {
                const VariantMap &val = value.mapValue();
                child = doc.NewElement(TAG_NAME_DICT);
                ret = buildXMLDict(doc, child, val);
                if (ret == T3D_OK)
                    root->LinkEndChild(child);
                else
                    break;
            }
        } while (0);

        return ret;
    }
}
