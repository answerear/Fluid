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


#include "T3DMetaGenerator.h"
#include "T3DGeneratorCommand.h"
#include "T3DGeneratorOptions.h"
#include "FileScriptObject.pb.h"
#include <google/protobuf/util/json_util.h>


namespace Tiny3D
{
    #define T3D_FILE_MAGIC              "T3D"
    #define T3D_FILE_VERSION_0_0_1      0x00000100
    #define T3D_FILE_CURRENT_VERSION    T3D_FILE_VERSION_0_0_1

    MetaGenerator::MetaGenerator()
    {

    }

    MetaGenerator::~MetaGenerator()
    {

    }

    TResult MetaGenerator::execute(int32_t argc, char* argv[])
    {
        TResult ret = T3D_OK;

        do 
        {
            GeneratorOptions opts;
            GeneratorCommand cmd;

            bool rt = cmd.parse(argc, argv, opts);
            if (!rt)
            {
                break;
            }

            ret = process(opts.mDir, opts.mRemove);
        } while (0);

        return ret;
    }

    TResult MetaGenerator::process(const String& path, bool isClear /* = false */)
    {
        TResult ret = T3D_OK;

        String fullpath = path + Dir::getNativeSeparator() + "*.*";
        Dir dir;
        bool working = dir.findFile(fullpath);

        while (working)
        {
            working = dir.findNextFile();

            if (dir.isDots())
            {
                // . or ..
                continue;
            }
            else if (dir.isDirectory())
            {
                // directory
                if (!isClear)
                {
                    const String &path = dir.getFilePath();
                    const String &name = dir.getFileName();
                    generate(path, name, true);
                }

                process(dir.getFilePath(), isClear);
            }
            else
            {
                // file
                const String &path = dir.getFilePath();
                const String &name = dir.getFileName();
                
                if (isClear)
                {
                    // delete *.meta
                    if (isMetaFile(name))
                    {
                        clear(path);
                    }
                }
                else
                {
                    // generate *.meta
                    if (!isMetaFile(name))
                    {
                        generate(path, name, false);
                    }
                    else
                    {
                        // 有元文件，如果没有资源文件，则删掉元文件
                        const String& title = dir.getFileTitle();
                        String path = dir.getRoot() + title;
                        if (!Dir::exists(path))
                        {
                            Dir::remove(dir.getFilePath());
                        }
                    }
                }
            }
        }

        dir.close();

        return ret;
    }

    bool MetaGenerator::isMetaFile(const String& name) const
    {
        bool ret = false;

        int32_t pos = name.find_last_of('.');

        if (pos != String::npos)
        {
            String ext = name.substr(pos);

            if (ext == ".meta")
            {
                ret = true;
            }
        }

        return ret;
    }

    void MetaGenerator::generate(const String &path, const String &name, bool isDir)
    {
        String fullpath = path + ".meta";

        if (!Dir::exists(fullpath))
        {
            Script::FileFormat::FileMeta file;
            Script::FileFormat::FileHeader *header = file.mutable_header();
            header->set_magic(T3D_FILE_MAGIC);
            header->set_type(Script::FileFormat::FileHeader_FileType_Meta);
            header->set_version(T3D_FILE_CURRENT_VERSION);

            String uuid = UUID::generate();
            Script::MetaSystem::MetaData* meta = file.mutable_meta();
            meta->set_uuid(uuid.c_str());
            meta->set_name(name.c_str());

            if (isDir)
            {
                meta->set_type(Script::MetaSystem::MetaData_FileType_Dir);
            }
            else
            {
                meta->set_type(Script::MetaSystem::MetaData_FileType_File);
            }

            FileDataStream fs;

            if (fs.open(fullpath.c_str(), FileDataStream::E_MODE_TEXT | FileDataStream::E_MODE_WRITE_ONLY))
            {
                String content;
                google::protobuf::util::JsonOptions opts;
                opts.add_whitespace = true;
                opts.always_print_enums_as_ints = false;
                opts.always_print_primitive_fields = true;
                google::protobuf::util::Status status = google::protobuf::util::MessageToJsonString(file, &content, opts);

                fs.write((void*)content.c_str(), content.length());
                fs.close();
            }
        }
    }

    void MetaGenerator::clear(const String& path)
    {
        if (Dir::exists(path))
        {
            Dir::remove(path);
        }
    }
}