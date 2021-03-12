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


#include "Resource/T3DTextureManager.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    T3D_INIT_SINGLETON(TextureManager);
    T3D_IMPLEMENT_CLASS_1(TextureManager, ResourceManager);

    //--------------------------------------------------------------------------

    TextureManagerPtr TextureManager::create()
    {
        TextureManagerPtr mgr = new TextureManager();
        mgr->release();
        return mgr;
    }

    //--------------------------------------------------------------------------

    TextureManager::TextureManager()
        : mDefaultMipMaps(1)
    {

    }

    //--------------------------------------------------------------------------

    TextureManager::~TextureManager()
    {

    }

    //--------------------------------------------------------------------------

    TexturePtr TextureManager::loadTexture(const String &name, 
        HardwareBuffer::Usage usage /* = HardwareBuffer::Usage::STATIC */, 
        uint32_t access /* = HardwareBuffer::AccessMode::CPU_NONE */, 
        size_t mipmaps /* = 1 */, 
        Texture::TexUsage texUsage /* = Texture::E_TU_DEFAULT */, 
        TextureType texType /* = E_TEX_TYPE_2D */)
    {
        return smart_pointer_cast<Texture>(ResourceManager::load(
            name, 8, 0, 0, usage, access, mipmaps, PixelFormat::E_PF_A8R8G8B8, 
            texUsage, texType));
    }

    //--------------------------------------------------------------------------

    TexturePtr TextureManager::loadTexture(const String &name, 
        size_t width, 
        size_t height, 
        HardwareBuffer::Usage usage /* = HardwareBuffer::Usage::STATIC */,
        uint32_t access /* = HardwareBuffer::AccessMode::CPU_NONE */, 
        size_t mipmaps /* = 1 */,
        PixelFormat format /* = PixelFormat::E_PF_A8R8G8B8 */, 
        Texture::TexUsage texUsage /* = Texture::E_TU_BLANK */, 
        TextureType texType /* = Texture::E_TEX_TYPE_2D */)
    {
        return smart_pointer_cast<Texture>(ResourceManager::load(
            name, 8, width, height, usage, access, mipmaps, format, texUsage, 
            texType));
    }

    //--------------------------------------------------------------------------

    ResourcePtr TextureManager::create(const String &name, int32_t argc, 
        va_list args)
    {
        ResourcePtr res;

        if (argc == 8)
        {
            size_t width = va_arg(args, size_t);
            size_t height = va_arg(args, size_t);
            HardwareBuffer::Usage usage = va_arg(args, HardwareBuffer::Usage);
            uint32_t access = va_arg(args, uint32_t);
            size_t numMipMaps = va_arg(args, size_t);
            PixelFormat format = va_arg(args, PixelFormat);
            Texture::TexUsage texUsage = va_arg(args, Texture::TexUsage);
            TextureType texType = va_arg(args, TextureType);
            numMipMaps = (numMipMaps == -1 ? mDefaultMipMaps : numMipMaps);
            res = Texture::create(name, usage, access, numMipMaps, 
                width, height, texUsage, texType, format);
        }

        return res;
    }

    //--------------------------------------------------------------------------

    TResult TextureManager::unloadTexture(TexturePtr texture)
    {
        return unload(texture);
    }
}
