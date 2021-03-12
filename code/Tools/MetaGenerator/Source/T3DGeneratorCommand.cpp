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


#include "T3DGeneratorCommand.h"


namespace Tiny3D
{
    bool GeneratorCommand::parse(int32_t argc, char* argv[], GeneratorOptions& options)
    {
        printCommand(argc, argv);

        if (argc < 2)
        {
            printHelp();
            return false;
        }

        bool bShowHelp = false;
        String ext;

        int i = 0;
        for (i = 1; i < argc; ++i)
        {
            const char* arg = argv[i];
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
                else if (arg[1] == 'd')
                {
                    options.mRemove = true;
                }
            }
            else if (options.mDir.length() == 0)
            {
                options.mDir = arg;
            }
        }

        if (bShowHelp || options.mDir.length() == 0)
        {
            printHelp();
            return false;
        }

        return true;
    }

    void GeneratorCommand::printCommand(int argc, char* argv[]) const
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

    void GeneratorCommand::printHelp() const
    {
        printf("Usage: meta-generator.exe <dir>\n");
        printf("Options:\n");
        printf("-?       : Display this help information.\n");
        printf("-v       : Verbose: print additional progress information\n");
        printf("-d       : Delete all *.meta files.\n");
        printf("\n");
    }
}


