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


#include "Adapter/Common/T3DSDLApplication.h"
#include "T3DPlatformErrorDef.h"
#include "T3DApplication.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    static int AppEventWatcher(void *userdata, SDL_Event *event)
    {
        switch (event->type)
        {
        case SDL_APP_DIDENTERBACKGROUND:
            {
                T3D_APPLICATION.applicationDidEnterBackground();
            }
            break;
        case SDL_APP_WILLENTERFOREGROUND:
            {
                T3D_APPLICATION.applicationWillEnterForeground();
            }
            break;
        case SDL_APP_TERMINATING:
            {
                T3D_APPLICATION.applicationWillTerminate();
            }
            break;
        case SDL_APP_LOWMEMORY:
            {
                T3D_APPLICATION.applicationLowMemory();
            }
            break;
        }
        
        return 0;
    }

    //--------------------------------------------------------------------------

    T3D_IMPLEMENT_CLASS_1(SDLApplication, IApplication);

    //--------------------------------------------------------------------------

    SDLApplication::SDLApplication()
    {

    }

    //--------------------------------------------------------------------------

    SDLApplication::~SDLApplication()
    {

    }

    //--------------------------------------------------------------------------

    TResult SDLApplication::init()
    {
        TResult ret = T3D_ERR_FAIL;

        do 
        {
            if (SDL_Init(0) != 0)
            {
                const char *error = SDL_GetError();
                break;
            }

            if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
            {
                const char *error = SDL_GetError();
                break;
            }
            
            SDL_AddEventWatch(AppEventWatcher, nullptr);

            ret = T3D_OK;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool SDLApplication::pollEvents()
    {
        bool ret = true;
        SDL_Event ev;

        while (SDL_PollEvent(&ev) != 0)
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                {
                    ret = false;
                }
                break;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    void SDLApplication::release()
    {
        SDL_Quit();
    }

    //--------------------------------------------------------------------------

    void *SDLApplication::getNativeAppObject()
    {
        return nullptr;
    }
}

