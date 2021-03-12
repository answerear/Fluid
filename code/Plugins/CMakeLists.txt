#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain. 
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

set(TINY3D_DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies")

add_definitions(-DT3D_ERR_RENDERER=T3D_ERR_PLUGINS)
add_definitions(-DT3D_ERR_ARCHIVE=T3D_ERR_PLUGINS+0x00001000)
add_definitions(-DT3D_ERR_IMAGE_CODEC=T3D_ERR_PLUGINS+0x00002000)


add_subdirectory(Renderer)
add_subdirectory(Archive)
add_subdirectory(ImageCodec)
