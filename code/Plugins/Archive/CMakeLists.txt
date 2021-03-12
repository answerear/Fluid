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


add_definitions(-DT3D_ERR_FS_ARCHIVE=T3D_ERR_ARCHIVE)
add_definitions(-DT3D_ERR_ZIP_ARCHIVE=T3D_ERR_ARCHIVE+0x00000200)

add_subdirectory(FileSystem)
add_subdirectory(Zip)
