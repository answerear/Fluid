#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain.
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)


set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../" CACHE PATH "Fluid install prefix")

project(Fluid)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)")
endif ()

if (CMAKE_SOURCE_DIR MATCHES " ")
    message("Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()

if (CMAKE_BINARY_DIR MATCHES " ")
    message("Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()


set(FLUID_OS "")

if (WIN32)
    # Windows
    message(STATUS "Platform : Windows")

    add_definitions(-DFLUID_OS_WINDOWS)
    add_definitions(-DFLUID_OS_DESKTOP)
    add_definitions(-D_HAS_EXCEPTIONS=0)

	add_definitions(/MP)

    set(FLUID_OS_WINDOWS TRUE CACHE STRING "Windows")
    set(FLUID_OS_DESKTOP TRUE CACHE STRING "Desktop")

    set(FLUID_OS "Windows" CACHE STRING "OS")

    set(SDL2LIB_SUFFIXES "prebuilt/win32/${MSVC_CXX_ARCHITECTURE_ID}")

    set(CMAKE_SYSTEM_VERSION 10.0.17763)
    set(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION 10.0.17763.0)

    add_compile_options(/wd4996)
#    set(CMAKE_CXX_FLAGS "-std=c++11")
elseif (ANDROID)
    # Android
    message(STATUS "Platform : Android")

    add_definitions(-DFLUID_OS_ANDROID)
    add_definitions(-DFLUID_OS_MOBILE)

    set(FLUID_OS_ANDROID TRUE CACHE STRING "Android")
    set(FLUID_OS_MOBILE TRUE CACHE STRING "Mobile")
    set(FLUID_OS "Android" CACHE STRING "OS")

    set(SDL2LIB_SUFFIXES "prebuilt/Android/${ANDROID_ABI}")

    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
elseif (APPLE AND IOS)
    # iOS
    message(STATUS "Platform : iOS")

    add_definitions(-DFLUID_OS_IOS)
    add_definitions(-DFLUID_OS_MOBILE)

    set(FLUID_OS_IOS TRUE CACHE STRING "iOS")
    set(FLUID_OS_MOBILE TRUE CACHE STRING "Mobile")
    set(FLUID_OS "iOS" CACHE STRING "OS")

    set(CMAKE_OSX_DEPLOYMENT_TARGET ${DEPLOYMENT_TARGET})

    set(SDL2LIB_SUFFIXES "prebuilt/iOS")

    set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-undefined-var-template")
elseif (APPLE AND NOT IOS)
    # Mac OS X
    message(STATUS "Platform : Mac OS X")

    add_definitions(-DT3D_OS_OSX)
    add_definitions(-DT3D_OS_DESKTOP)

    set(FLUID_OS_MACOSX TRUE CACHE STRING "Mac OS X")
    set(FLUID_OS_DESKTOP TRUE CACHE STRING "Desktop")
    set(FLUID_OS "OSX" CACHE STRING "OS")

    set(CMAKE_MACOSX_RPATH true)
    set(SDL2LIB_SUFFIXES "prebuilt/OSX")

    set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-undefined-var-template")
elseif (UNIX AND NOT APPLE)
    # Linux
    message(STATUS "Platform : Linux")

    add_definitions(-DFLUID_OS_LINUX)
    add_definitions(-DFLUID_OS_DESKTOP)

    set(FLUID_OS_LINUX TRUE CACHE STRING "Linux")
    set(FLUID_OS_DESKTOP TRUE CACHE STRING "Desktop")
    set(FLUID_OS "Linux" CACHE STRING "OS")

    set(SDL2LIB_SUFFIXES "prebuilt/Linux")

    set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wno-undefined-var-template")
endif (WIN32)


if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_definitions(-DFLUID_OS_X64)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    add_definitions(-DFLUID_OS_X86)
endif ()

if (FLUID_OS_IOS)
    # Because in iOS, there only support static library.
    option(FLUID_BUILD_SHARED_LIBS "Build shared libraries" TRUE)
else (FLUID_OS_IOS)
    option(FLUID_BUILD_SHARED_LIBS "Build shared libraries" TRUE)
endif (FLUID_OS_IOS)

if (NOT FLUID_OS_ANDROID)
    # In Android, this switch is setted by build.gradle in Android Studio.
    option(FLUID_BUILD_SHARED_LIBS "Build samples" TRUE)
endif (NOT FLUID_OS_ANDROID)


# Set all relative directory
set(FLUID_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin/${FLUID_OS}" CACHE PATH "Fluid binary path")
set(FLUID_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib/${FLUID_OS}" CACHE PATH "Fluid library path")
set(FLUID_INC_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Fluid include path")
set(FLUID_RES_DIR "${CMAKE_INSTALL_PREFIX}/assets" CACHE PATH "Fluid assets path")

# Set this directory for debugging app
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${FLUID_OS}" CACHE STRING "Fluid binaries files" FORCE)

message(STATUS "Runtime dir : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} BUILTTYPE)
    
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${BUILTTYPE} "${PROJECT_SOURCE_DIR}/bin/${FLUID_OS}/${OUTPUTCONFIG}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${BUILTTYPE} "${PROJECT_SOURCE_DIR}/lib/${FLUID_OS}/${OUTPUTCONFIG}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${BUILTTYPE} "${PROJECT_SOURCE_DIR}/lib/${FLUID_OS}/${OUTPUTCONFIG}")
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

# Set cmake module path.
set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Utils"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Packages"
    )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")


include(FindPkgMacros)
include(ProjectCMakeModule)


# Search SDL2 library for all projects.
set(SDL2DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL2" CACHE PATH "SDL2 library path")
find_package(SDL2)

set(GLM_HOME "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glm" CACHE PATH "glm library path")
find_package(glm)

# Project Platform
add_subdirectory(Platform)
# Project Fluid
add_subdirectory(Fluid)
# Project PDFDemo
add_subdirectory(PBFDemo)

# Set the dependencies for all projects.
add_dependencies(Fluid Platform)
add_dependencies(PBFDemo Fluid Platform)

