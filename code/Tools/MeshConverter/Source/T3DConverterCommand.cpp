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


#include "T3DConverterCommand.h"
#include "T3DConverterOptions.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    bool ConverterCommand::parse(int32_t argc, char *argv[], 
        ConverterOptions &options)
    {
        printCommand(argc, argv);

        if (argc < 3)
        {
            printHelp();
            return false;
        }

        bool bShowHelp = false;
        String ext;

        int i = 0;
        for (i = 1; i < argc; ++i)
        {
            const char *arg = argv[i];
            int len = strlen(arg);
            if (len > 1 && arg[0] == '-')
            {
                if (arg[1] == '?')
                {
                    bShowHelp = true;
                }
                else if (arg[1] == 'v')
                {
                    options.mVerbose = true;
                }
                else if (arg[1] == 'i')
                {
                    options.mSrcFileType = parseFileType(argv[++i]);
                }
                else if (arg[1] == 'o')
                {
                    options.mDstFileType = parseFileType(argv[++i]);
                    ext = argv[i];
                }
                else if (arg[1] == 'b')
                {
                    options.mBoundType = parseBoundType(argv[++i]);
                }
                else if (arg[1] == 'm')
                {
                    options.mHasVertexShared = parseVertexShared(argv[++i]);
                }
                else if (arg[1] == 'f')
                {
                    options.mExtraPath = argv[++i];
                }
            }
            else if (options.mSrcPath.length() == 0)
            {
                options.mSrcPath = arg;
            }
            else if (options.mDstPath.length() == 0)
            {
                options.mDstPath = arg;
            }
        }

        if (bShowHelp || options.mSrcPath.length() == 0)
        {
            printHelp();
            return false;
        }

        if (options.mDstPath.length() == 0)
        {
            const String &srcPath = options.mSrcPath;
            int pos = srcPath.rfind('.');
            options.mDstPath = srcPath.substr(0, pos);

            switch (options.mDstFileType)
            {
            case MeshFileType::FBX:
                options.mDstPath += ".fbx";
                break;
            case MeshFileType::OGRE:
                options.mDstPath += ".mesh";
                break;
            case MeshFileType::T3B:
                options.mDstPath += ".t3d";
                break;
            case MeshFileType::T3T:
                options.mDstPath += ".t3d";
                break;
            }
        }

        return true;
    }

    //--------------------------------------------------------------------------

    void ConverterCommand::printCommand(int argc, char *argv[]) const
    {
        int i = 0;

        for (i = 1; i < argc; ++i)
        {
            if (i > 1)
                printf(" ");
            printf(argv[i]);
        }

        printf("\n");
    }

    //--------------------------------------------------------------------------

    void ConverterCommand::printHelp() const
    {
        printf("Usage: mesh-conv.exe [options] <input> [<output>]\n");
        printf("\n");
        printf("Options:\n");
        printf("-?       : Display this help information.\n");
        printf("-i <type>: Set the type of the input file to <type>\n");
        printf("\t<type> : This type should be \"FBX\" (fbx), \"OGRE\" (mesh).\n");
        printf("-o <type>: Set the type of the output file to <type>\n");
        printf("\t<type> : This type should be \"t3b\" (Tiny3D binary), \"t3t\" (Tiny3D text).\n");
        printf("-b <type>: Set the type of the bounding box to <type>\n");
        printf("\t<type> : This type should be \"sphere\" or \"AABB\".\n");
        printf("-m <type>: This type should control file mode.\n");
        printf("\t<type> : This type should be \"shared\" or \"original\".\n");
        printf("\t              shared - Merge different meshes in one *.fbx file into one model file and all meshes share one vertex buffer.\n");
        printf("\t              original - Maintain meshes original structure.\n");
        printf("-f <filename>: This option is material file when input file type is OGRE.\n");
        printf("-v       : Verbose: print additional progress information\n");
        printf("\n");
        printf("<input>  : The filename of the file to convert.\n");
        printf("<output> : The filename of the converted file.\n");
        printf("\n");
//         printf("<type>   : FBX, T3B (binary) or T3T (text).\n");
    }

    //--------------------------------------------------------------------------

    MeshFileType ConverterCommand::parseFileType(const char *argv) const
    {
        MeshFileType type = MeshFileType::FBX;

        if (stricmp(argv, "fbx") == 0)
            type = MeshFileType::FBX;
        else if (stricmp(argv, "ogre") == 0)
            type = MeshFileType::OGRE;
        else if (stricmp(argv, "t3b") == 0)
            type = MeshFileType::T3B;
        else if (stricmp(argv, "t3t") == 0)
            type = MeshFileType::T3T;

        return type;
    }

    //--------------------------------------------------------------------------

    BoundType ConverterCommand::parseBoundType(const char *argv) const
    {
        BoundType type = BoundType::SPHERE;

        if (stricmp(argv, "sphere") == 0)
            type = BoundType::SPHERE;
        else if (stricmp(argv, "aabb") == 0)
            type = BoundType::AABB;

        return type;
    }

    //--------------------------------------------------------------------------

    bool ConverterCommand::parseVertexShared(const char *argv) const
    {
        bool hasVertexShared = false;

        if (stricmp(argv, "shared") == 0)
        {
            hasVertexShared = true;
        }
        else if (stricmp(argv, "original") == 0)
        {
            hasVertexShared = false;
        }

        return hasVertexShared;
    }
}

