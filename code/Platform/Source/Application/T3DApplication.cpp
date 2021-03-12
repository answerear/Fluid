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


#include "T3DApplication.h"
#include "T3DSystem.h"
#include "Adapter/T3DFactoryInterface.h"
#include "Adapter/T3DApplicationInterface.h"
#include "T3DPlatformErrorDef.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(Application);
    T3D_IMPLEMENT_CLASS_0(Application);

    //--------------------------------------------------------------------------

    Application::Application()
        : mSystem(new System())
    {
        mApp = T3D_PLATFORM_FACTORY.createPlatformApplication();
    }

    //--------------------------------------------------------------------------

    Application::~Application()
    {
        T3D_SAFE_DELETE(mApp);
        T3D_SAFE_DELETE(mSystem);
    }

    //--------------------------------------------------------------------------

    TResult Application::init()
    {
        TResult ret = T3D_ERR_FAIL;

        do 
        {
            if (mApp == nullptr || mSystem == nullptr)
            {
                ret = T3D_ERR_INVALID_POINTER;
                break;
            }

            ret = mApp->init();
            if (T3D_FAILED(ret))
                break;

            ret = mSystem->init();
            if (T3D_FAILED(ret))
                break;
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool Application::pollEvents()
    {
        bool ret = false;

        if (mApp != nullptr)
        {
            ret = mApp->pollEvents();
        }

        if (ret)
        {
            // 系统平台层轮询
            T3D_SYSTEM.poll();
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    void Application::release()
    {
        if (mApp != nullptr)
        {
            mApp->release();
        }
    }

    //--------------------------------------------------------------------------

    void *Application::getNativeAppObject()
    {
        if (mApp != nullptr)
        {
            return mApp->getNativeAppObject();
        }

        return nullptr;
    }
}
