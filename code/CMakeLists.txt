#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain.
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)


set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../" CACHE PATH "Tiny3D install prefix")

project(Tiny3D)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)")
endif ()

if (CMAKE_SOURCE_DIR MATCHES " ")
    message("Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()

if (CMAKE_BINARY_DIR MATCHES " ")
    message("Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()


set(TINY3D_OS "")

if (WIN32)
    # Windows
    message(STATUS "Platform : Windows")

    add_definitions(-DT3D_OS_WINDOWS)
    add_definitions(-DT3D_OS_DESKTOP)
    add_definitions(-D_HAS_EXCEPTIONS=0)

	add_definitions(/MP)

    set(TINY3D_OS_WINDOWS TRUE CACHE STRING "Windows")
    set(TINY3D_OS_DESKTOP TRUE CACHE STRING "Desktop")

    set(TINY3D_OS "Windows" CACHE STRING "OS")

    set(SDL2LIB_SUFFIXES "prebuilt/win32/${MSVC_CXX_ARCHITECTURE_ID}")
    set(PROTOBUF_SUFFIXES "prebuilt/Windows/${MSVC_CXX_ARCHITECTURE_ID}")

    set(CMAKE_SYSTEM_VERSION 10.0.17763)
    set(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION 10.0.17763.0)

    add_compile_options(/wd4996)
#    set(CMAKE_CXX_FLAGS "-std=c++11")
elseif (ANDROID)
    # Android
    message(STATUS "Platform : Android")

    add_definitions(-DT3D_OS_ANDROID)
    add_definitions(-DT3D_OS_MOBILE)

    set(TINY3D_OS_ANDROID TRUE CACHE STRING "Android")
    set(TINY3D_OS_MOBILE TRUE CACHE STRING "Mobile")
    set(TINY3D_OS "Android" CACHE STRING "OS")

    set(SDL2LIB_SUFFIXES "prebuilt/Android/${ANDROID_ABI}")
    set(PROTOBUF_SUFFIXES "prebuilt/Android/${ANDROID_ABI}")

    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
elseif (APPLE AND IOS)
    # iOS
    message(STATUS "Platform : iOS")

    add_definitions(-DT3D_OS_IOS)
    add_definitions(-DT3D_OS_MOBILE)

    set(TINY3D_OS_IOS TRUE CACHE STRING "iOS")
    set(TINY3D_OS_MOBILE TRUE CACHE STRING "Mobile")
    set(TINY3D_OS "iOS" CACHE STRING "OS")

    set(CMAKE_OSX_DEPLOYMENT_TARGET ${DEPLOYMENT_TARGET})

    set(SDL2LIB_SUFFIXES "prebuilt/iOS")
    set(PROTOBUF_SUFFIXES "prebuilt/iOS")

    set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-undefined-var-template")
elseif (APPLE AND NOT IOS)
    # Mac OS X
    message(STATUS "Platform : Mac OS X")

    add_definitions(-DT3D_OS_OSX)
    add_definitions(-DT3D_OS_DESKTOP)

    set(TINY3D_OS_MACOSX TRUE CACHE STRING "Mac OS X")
    set(TINY3D_OS_DESKTOP TRUE CACHE STRING "Desktop")
    set(TINY3D_OS "OSX" CACHE STRING "OS")

    set(CMAKE_MACOSX_RPATH true)
    set(SDL2LIB_SUFFIXES "prebuilt/OSX")
    set(PROTOBUF_SUFFIXES "prebuilt/OSX")

    set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-undefined-var-template")
elseif (UNIX AND NOT APPLE)
    # Linux
    message(STATUS "Platform : Linux")

    add_definitions(-DT3D_OS_LINUX)
    add_definitions(-DT3D_OS_DESKTOP)

    set(TINY3D_OS_LINUX TRUE CACHE STRING "Linux")
    set(TINY3D_OS_DESKTOP TRUE CACHE STRING "Desktop")
    set(TINY3D_OS "Linux" CACHE STRING "OS")

    set(SDL2LIB_SUFFIXES "prebuilt/Linux")
    set(PROTOBUF_SUFFIXES "prebuilt/Linux")

    set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wno-undefined-var-template")
endif (WIN32)


if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_definitions(-DT3D_OS_X64)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    add_definitions(-DT3D_OS_X86)
endif ()

if (TINY3D_OS_IOS)
    # Because in iOS, there only support static library.
    option(TINY3D_BUILD_SHARED_LIBS "Build shared libraries" TRUE)
else (TINY3D_OS_IOS)
    option(TINY3D_BUILD_SHARED_LIBS "Build shared libraries" TRUE)
endif (TINY3D_OS_IOS)

if (NOT TINY3D_OS_ANDROID)
    # In Android, this switch is setted by build.gradle in Android Studio.
    option(TINY3D_BUILD_SAMPLES "Build samples" TRUE)
endif (NOT TINY3D_OS_ANDROID)

if (TINY3D_OS_DESKTOP)
    option(TINY3D_BUILD_TOOLS "Build tools" TRUE)
else (TINY3D_OS_DESKTOP)
    option(TINY3D_BUILD_TOOLS "Build tools" FALSE)
endif (TINY3D_OS_DESKTOP)

# Set all relative directory
set(TINY3D_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin/${TINY3D_OS}" CACHE PATH "Tiny3D binary path")
set(TINY3D_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib/${TINY3D_OS}" CACHE PATH "Tiny3D library path")
set(TINY3D_INC_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Tiny3D include path")
set(TINY3D_RES_DIR "${CMAKE_INSTALL_PREFIX}/assets" CACHE PATH "Tiny3D assets path")

# Set this directory for debugging app
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TINY3D_OS}" CACHE STRING "Tiny3D binaries files" FORCE)

message(STATUS "Runtime dir : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} BUILTTYPE)
    
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${BUILTTYPE} "${PROJECT_SOURCE_DIR}/bin/${TINY3D_OS}/${OUTPUTCONFIG}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${BUILTTYPE} "${PROJECT_SOURCE_DIR}/lib/${TINY3D_OS}/${OUTPUTCONFIG}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${BUILTTYPE} "${PROJECT_SOURCE_DIR}/lib/${TINY3D_OS}/${OUTPUTCONFIG}")
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

# Set cmake module path.
set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Utils"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Packages"
    )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

# Platform error code
add_definitions(-DT3D_ERR_PLATFORM=0x00001000)
# Log error code
add_definitions(-DT3D_ERR_LOG=0x00002000)
# Framework error code
add_definitions(-DT3D_ERR_FRAMEWORK=0x00003000)
# Core error code
add_definitions(-DT3D_ERR_CORE=0x00004000)
# Plugin error code
add_definitions(-DT3D_ERR_PLUGINS=0x00010000)

include(FindPkgMacros)
include(ProjectCMakeModule)


# Search SDL2 library for all projects.
set(SDL2DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL2" CACHE PATH "SDL2 library path")
find_package(SDL2)

# Search protobuf library for all projects.
#set(PROTOBUF_HOME "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/protobuf" CACHE PATH "protobuf library path")
#find_package(protobuf)

# Search rapidjson library for all projects.
#set(RAPIDJSON_HOME "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/rapidjson" CACHE PATH "rapidjson library path")
#find_package(rapidjson)

# Third Parties
# Project protobuf
option (protobuf_BUILD_LITE_LIBRARIES "Build protobuf-lite library" OFF)
set(PROTOBUF_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/protobuf/src")
add_subdirectory(protobuf)


# Setup project folder
if (protobuf_BUILD_LITE_LIBRARIES)
    set_property(TARGET libprotobuf-lite PROPERTY FOLDER "External/protobuf")
    set (PROTOBUF_LIBRARY libprotobuf-lite)
else (protobuf_BUILD_LITE_LIBRARIES)
    set_property(TARGET libprotobuf PROPERTY FOLDER "External/protobuf")
    set_property(TARGET libprotobuf-lite PROPERTY FOLDER "External/protobuf")
    set (PROTOBUF_LIBRARY libprotobuf)
endif (protobuf_BUILD_LITE_LIBRARIES)

# Project Platform
add_subdirectory(Platform)
# Project Log
add_subdirectory(Log)
# Project Utils
add_subdirectory(Utils)
# Project Framework
add_subdirectory(Framework)
# Project Math
add_subdirectory(Math)
# Project Core
add_subdirectory(Core)
# Project Fluid
add_subdirectory(Fluid)


#foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
#    string(TOUPPER ${OUTPUTCONFIG} BUILTTYPE)
#    set(RUNTIME_OUTPUT_DIR_TEMP_${BUILTTYPE} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_${BUILTTYPE}}")
#    set(LIBRARY_OUTPUT_DIR_TEMP_${BUILTTYPE} "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_${BUILTTYPE}}")
#    set(ARCHIVE_OUTPUT_DIR_TEMP_${BUILTTYPE} "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${BUILTTYPE}}")
#    
#    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${BUILTTYPE} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_${BUILTTYPE}}/Plugins")
#    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${BUILTTYPE} "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_${BUILTTYPE}}/Plugins")
#    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${BUILTTYPE} "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${BUILTTYPE}}/Plugins")
#endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

# Project plugins
add_subdirectory(Plugins)

#foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
#    string(TOUPPER ${OUTPUTCONFIG} BUILTTYPE)
#    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${BUILTTYPE} "${RUNTIME_OUTPUT_DIR_TEMP_${BUILTTYPE}}")
#    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${BUILTTYPE} "${LIBRARY_OUTPUT_DIR_TEMP_${BUILTTYPE}}")
#    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${BUILTTYPE} "${ARCHIVE_OUTPUT_DIR_TEMP_${BUILTTYPE}}")
#endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

# Set the dependencies for all projects.
add_dependencies(T3DLog T3DPlatform)
add_dependencies(T3DUtils T3DLog T3DPlatform)
add_dependencies(T3DMath T3DLog T3DPlatform)
add_dependencies(T3DFramework T3DLog T3DPlatform)
add_dependencies(T3DCore ${PROTOBUF_LIBRARY} T3DMath T3DFramework T3DUtils T3DLog T3DPlatform)
add_dependencies(T3DFluid T3DCore)

if (TINY3D_BUILD_TOOLS)
    add_subdirectory(Tools)
    add_dependencies(ScriptCompiler T3DCore)

    add_dependencies(ShaderCross T3DCore)
endif(TINY3D_BUILD_TOOLS)

if (TINY3D_BUILD_SAMPLES)
    # Build samples. Set all projects of samples.
    add_subdirectory(Samples)
    add_dependencies(HelloApp T3DCore)
    add_dependencies(PlatformApp T3DCore)
    add_dependencies(FrameworkApp T3DCore)
    add_dependencies(GeometryApp T3DCore)
    add_dependencies(TextureApp T3DCore)
	add_dependencies(FluidApp T3DCore T3DFluid)
    if (TINY3D_OS_DESKTOP)
        add_dependencies(TransformationApp T3DMath T3DLog T3DPlatform)
        add_dependencies(IntersectionApp T3DMath T3DLog T3DPlatform)
    endif (TINY3D_OS_DESKTOP)
endif (TINY3D_BUILD_SAMPLES)
