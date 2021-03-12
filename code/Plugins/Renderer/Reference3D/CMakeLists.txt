#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain. 
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

set_project_name(R3DRenderer)

if (MSVC)
    if (TINY3D_BUILD_SHARED_LIBS)
        add_definitions(-D${LIB_NAME_TOUPPER}_EXPORT -D_USRDLL)
    endif (TINY3D_BUILD_SHARED_LIBS)
endif (MSVC)


# Setup project include files path
include_directories(
    "${TINY3D_CORE_SOURCE_DIR}/Include"
    "${TINY3D_MATH_SOURCE_DIR}/Include"
    "${TINY3D_FRAMEWORK_SOURCE_DIR}/Include"
    "${TINY3D_PLATFORM_SOURCE_DIR}/Include"
    "${TINY3D_LOG_SOURCE_DIR}/Include"
	"${TINY3D_UTILS_SOURCE_DIR}/Include"
    "${SDL2_INCLUDE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    )


# Setup project header files
set_project_files(Include ${CMAKE_CURRENT_SOURCE_DIR}/Include/ .h)

# Setup project source files
set_project_files(Source ${CMAKE_CURRENT_SOURCE_DIR}/Source/ .cpp)


#if (TINY3D_BUILD_SHARED_LIBS)
    add_library(${LIB_NAME} SHARED ${SOURCE_FILES})
#else (TINY3D_BUILD_SHARED_LIBS)
#    add_library(${LIB_NAME} STATIC ${SOURCE_FILES})
#endif (TINY3D_BUILD_SHARED_LIBS)

if (TINY3D_OS_IOS)
    set(CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG "-Wl,-rpath")

    set_target_properties (${LIB_NAME} PROPERTIES
        BUILD_WITH_INSTALL_RPATH 1
        MACOSX_RPATH 1
        INSTALL_NAME_DIR "@rpath"
        )
elseif (TINY3D_OS_MACOSX)
else (TIN3YD_OS_IOS)
endif (TINY3D_OS_IOS)

target_link_libraries(
    ${LIB_NAME}
    LINK_PRIVATE T3DPlatform
    LINK_PRIVATE T3DMath
	LINK_PRIVATE T3DUtils
    LINK_PRIVATE T3DLog
    LINK_PRIVATE T3DCore
    )

if (TINY3D_OS_LINUX)
    add_custom_command(TARGET ${BIN_NAME}
        POST_BUILD
        #COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Plugins"
        #COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/lib${BIN_NAME}.so" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Plugins/lib${BIN_NAME}.so"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/lib${BIN_NAME}.so" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib${BIN_NAME}.so"
        )
endif (TINY3D_OS_LINUX)

# Setup project folder
set_property(TARGET ${LIB_NAME} PROPERTY FOLDER "Plugins/Renderer")

#install(TARGETS ${LIB_NAME}
#    RUNTIME DESTINATION bin/Debug CONFIGURATIONS Debug
#    LIBRARY DESTINATION bin/Debug CONFIGURATIONS Debug
#    )
