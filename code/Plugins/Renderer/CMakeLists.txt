#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain. 
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------


set(TINY3D_CORE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Core" CACHE PATH "Tiny3D core source path")
set(TINY3D_MATH_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Math" CACHE PATH "Tiny3D math source path")
set(TINY3D_FRAMEWORK_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Framework" CACHE PATH "Tiny3D framework source path")
set(TINY3D_UTILS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Utils" CACHE PATH "Tiny3D utils source path")
set(TINY3D_LOG_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Log" CACHE PATH "Tiny3D log source path")
set(TINY3D_PLATFORM_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Platform" CACHE PATH "Tiny3D platform source path")


set (TINY3D_BUILD_RENDERSYSTEM_R3D FALSE CACHE STRING "Reference3D")

add_definitions(-DT3D_ERR_R3D_RENDERER=T3D_ERR_RENDERER)
add_definitions(-DT3D_ERR_D3D9_RENDERER=T3D_ERR_RENDERER+0x00000100)
add_definitions(-DT3D_ERR_D3D11_RENDERER=T3D_ERR_RENDERER+0x00000200)
add_definitions(-DT3D_ERR_GL3_RENDERER=T3D_ERR_RENDERER+0x00000300)
add_definitions(-DT3D_ERR_EGL2_RENDERER=T3D_ERR_RENDERER+0x00000400)
add_definitions(-DT3D_ERR_EGL3_RENDERER=T3D_ERR_RENDERER+0x00000500)
add_definItions(-DT3D_ERR_METAL_RENDERER=T3D_ERR_RENDERER+0x00000600)
add_definItions(-DT3D_ERR_VULKAN_RENDERER=T3D_ERR_RENDERER+0x00000700)

set (TINY3D_BUILD_RENDERSYSTEM_R3D FALSE CACHE STRING "RT3DR3DRenderer")
set (TINY3D_BUILD_RENDERSYSTEM_D3D9 FALSE CACHE STRING "T3DD3D9Renderer")
set (TINY3D_BUILD_RENDERSYSTEM_D3D11 FALSE CACHE STRING "T3DD3D11Renderer")
set (TINY3D_BUILD_RENDERSYSTEM_GL3PLUS FALSE CACHE STRING "T3DGL3Renderer")
set (TINY3D_BUILD_RENDERSYSTEM_GLES2 FALSE CACHE STRING "T3DGLES2Renderer")
set (TINY3D_BUILD_RENDERSYSTEM_GLES3 FALSE CACHE STRING "T3DGLES3Renderer")
set (TINY3D_BUILD_RENDEERSYSTEM_VULKAN FALSE CACHE STRING "T3DVulkanRenderer")
set (TINY3D_BUILD_RENDERSYSTEM_METAL FALSE CACHE STRING "T3DMetalRenderer")


if (TINY3D_OS_WINDOWS)
#    set (TINY3D_BUILD_RENDERSYSTEM_D3D9 TRUE)
    set (TINY3D_BUILD_RENDERSYSTEM_D3D11 TRUE)
    set (TINY3D_BUILD_RENDERSYSTEM_GL3PLUS TRUE)
    set (TINY3D_BUILD_RENDERSYSTEM_VULKAN TRUE)
elseif (TINY3D_OS_ANDROID)
#    set (TINY3D_BUILD_RENDERSYSTEM_GLES2 TRUE)
#    set (TINY3D_BUILD_RENDERSYSTEM_GLES3 TRUE)
#    set (TINY3D_BUILD_RENDERSYSTEM_VULKAN TRUE CACHE STRING "T3DVulkanRenderer")
elseif (TINY3D_OS_IOS)
#    set (TINY3D_BUILD_RENDERSYSTEM_GLES2 TRUE CACHE STRING "T3DGLES2Renderer")
#    set (TINY3D_BUILD_RENDERSYSTEM_GLES3 TRUE CACHE STRING "T3DGLES3Renderer")
#    set (TINY3D_BUILD_RENDERSYSTEM_METAL TRUE)
elseif (TINY3D_OS_OSX)
    set (TINY3D_BUILD_RENDERSYSTEM_GL3PLUS TRUE CACHE STRING "T3DGL3Renderer")
    set (TINY3D_BUILD_RENDERSYSTEM_METAL TRUE CACHE STRING "T3DMetalRenderer")
elseif (TINY3D_OS_LINUX)
#    set (TINY3D_BUILD_RENDERSYSTEM_GL3PLUS TRUE CACHE STRING "T3DGL3Renderer")
#    set (TINY3D_BUILD_RENDERSYSTEM_VULKAN TRUE CACHE STRING "T3DVulkanRenderer")
endif (TINY3D_OS_WINDOWS)


if (TINY3D_BUILD_RENDERSYSTEM_R3D)
    add_subdirectory(Reference3D)
    add_dependencies(R3DRenderer T3DCore T3DMath T3DLog T3DPlatform)
endif (TINY3D_BUILD_RENDERSYSTEM_R3D)

if (TINY3D_BUILD_RENDERSYSTEM_D3D9)
    find_package(DirectX)

    if (NOT DirectX9_FOUND)
        message(STATUS "Could not find dependency: DirectX")
        message(STATUS "Skipping Direct3D9 rendersystem build")
        set(TINY3D_BUILD_RENDERSYSTEM_D3D9 FALSE)
    else ()
        add_subdirectory(Direct3D9)
        add_dependencies(D3D9Renderer T3DCore T3DMath T3DLog T3DPlatform)
    endif ()
endif (TINY3D_BUILD_RENDERSYSTEM_D3D9)


if (TINY3D_BUILD_RENDERSYSTEM_D3D11)
    find_package(DirectX11)

    if (NOT DirectX11_FOUND)
        message(STATUS "Could not find dependency: DirectX11")
        message(STATUS "Skipping Direct3D11 rendersystem build")
        set(TINY3D_BUILD_RENDERSYSTEM_D3D11 FALSE)
    else ()
        add_subdirectory(Direct3D11)
        add_dependencies(D3D11Renderer T3DCore T3DMath T3DLog T3DPlatform)
    endif ()
endif (TINY3D_BUILD_RENDERSYSTEM_D3D11)


if (TINY3D_BUILD_RENDERSYSTEM_GL3PLUS)
    find_package(OpenGL)

    if (NOT OPENGL_FOUND)
        message(STATUS "Could not find dependency: OpenGL 3+")
        message(STATUS "Skipping OpenGL3Plus rendersystem build")
        set(TINY3D_BUILD_RENDERSYSTEM_GL3PLUS FALSE)
    else ()
        add_subdirectory(OpenGL3)
        add_dependencies(GL3Renderer T3DCore T3DMath T3DLog T3DPlatform)
    endif ()
endif (TINY3D_BUILD_RENDERSYSTEM_GL3PLUS)


if (TINY3D_BUILD_RENDERSYSTEM_GLES2)
    find_package(OpenGLES2)

    if (NOT OPENGLES2_FOUND)
        message(STATUS "Could not find dependency: OpenGLES 2")
        message(STATUS "Skipping OpenGLES2 rendersystem build")
        set(TINY3D_BUILD_RENDERSYSTEM_GLES2 FALSE)
    else ()
        add_subdirectory(OpenGLES2)
        add_dependencies(GLES2Renderer T3DCore T3DMath T3DLog T3DPlatform)
    endif ()
endif (TINY3D_BUILD_RENDERSYSTEM_GLES2)


if (TINY3D_BUILD_RENDERSYSTEM_GLES3)
    find_package(OpenGLES3)

    if (NOT OPENGLES3_FOUND)
        message(STATUS "Could not find dependency: OpenGLES 3")
        message(STATUS "Skipping OpenGLES3 rendersystem build")
        set(TINY3D_BUILD_RENDERSYSTEM_GLES3 FALSE)
    else ()
        add_subdirectory(OpenGLES3)
        add_dependencies(GLES3Renderer T3DCore T3DMath T3DLog T3DPlatform)
    endif ()
endif (TINY3D_BUILD_RENDERSYSTEM_GLES3)

if (TINY3D_BUILD_RENDEERSYSTEM_VULKAN)
    find_package(Vulkan)
    
    if (NOT VULKAN_FOUND)
        message(STATUS "Could not find dependency: Vulkan")
        message(STATUS "Skipping Vulkan rendersystem build")
        set(TINY3D_BUILD_RENDERSYSTEM_GLES3 FALSE)
    else ()
        add_subdirectory(Vulkan)
        add_dependencies(VulkanRenderer T3DCore T3DMath T3DLog T3DPlatform)
    endif ()
endif (TINY3D_BUILD_RENDEERSYSTEM_VULKAN)

if (TINY3D_BUILD_RENDERSYSTEM_METAL)
    find_package(Metal)
    
    if (NOT METAL_FOUND)
        message(STATUS "Could not find dependency: Metal")
        message(STATUS "Skipping Metal rendersystem build")
        set(TINY3D_BUILD_RENDERSYSTEM_METAL FALSE)
    else ()
        add_subdirectory(Metal)
        add_dependencies(MetalRenderer T3DCore T3DMath T3DLog T3DPlatform)
    endif ()
endif (TINY3D_BUILD_RENDERSYSTEM_METAL)
