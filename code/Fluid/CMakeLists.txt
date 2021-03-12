#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain.
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

set_project_name(T3DFluid)

message(STATUS "Generating project : ${BIN_NAME}")


if (MSVC)
    # Add definition only for Windows.
    if (TINY3D_BUILD_SHARED_LIBS)
        add_definitions(-D${LIB_NAME_TOUPPER}_EXPORT -D_USRDLL)
    endif (TINY3D_BUILD_SHARED_LIBS)

    # Disable some warning for protobuf
    add_definitions(
        /wd4244 # 'conversion' conversion from 'type1' to 'type2', possible loss of data
        /wd4267 # 'var' : conversion from 'size_t' to 'type', possible loss of data
        /wd4309 # 'conversion' : truncation of constant value
        /wd4800 # 'type' : forcing value to bool 'true' or 'false' (performance warning)
    )
endif (MSVC)


# Setup all cmake variables for this project.
set(TINY3D_PLATFORM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Platform")
set(TINY3D_MATH_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Math")
set(TINY3D_UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Utils")
set(TINY3D_LOG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Log")
set(TINY3D_FRAMEWORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Framework")
set(TINY3D_DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies")
set(TINY3D_CORE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Core")

# Setup search header path for this project.
include_directories(
    "${TINY3D_PLATFORM_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${SDL2_INCLUDE_DIR}"
    "${TINY3D_MATH_DIR}/include"
	"${TINY3D_UTILS_DIR}/include"
	"${TINY3D_LOG_DIR}/include"
	"${TINY3D_CORE_DIR}/include"
    "${TINY3D_FRAMEWORK_DIR}/include"
    )

#if (TINY3D_OS_WINDOWS)
#    set(TINY3D_ZLIB_LIBRARY "${TINY3D_DEP_DIR}/zlib/prebuilt/win32/${MSVC_CXX_ARCHITECTURE_ID}/zlibstatic.lib")
#endif (TINY3D_OS_WINDOWS)

# Setup header files for this project.
set_project_files(Include ${CMAKE_CURRENT_SOURCE_DIR}/Include/ .h)
#set_project_files(Include\\\\Kernel ${CMAKE_CURRENT_SOURCE_DIR}/Include/Kernel/ .h)


# Setup source files for this project.
set_project_files(Source ${CMAKE_CURRENT_SOURCE_DIR}/Source/ .cpp)
#set_project_files(Source\\\\Kernel ${CMAKE_CURRENT_SOURCE_DIR}/Source/Kernel/ .cpp)


# Setup all files for building this project.
if (TINY3D_BUILD_SHARED_LIBS)
    # Make dynamic library for this project.
    add_library(${LIB_NAME} SHARED ${SOURCE_FILES})
else (TINY3D_BUILD_SHARED_LIBS)
    # Make static library for this project.
    add_library(${LIB_NAME} STATIC ${SOURCE_FILES})
endif (TINY3D_BUILD_SHARED_LIBS)


if (TINY3D_OS_WINDOWS)
    # Windows

    # Setup link libraries for this project.
    if (MSVC_VERSION GREATER_EQUAL 1900)
        # Visual Studio version is 2015 or later.
        target_link_libraries(
            ${LIB_NAME}
            LINK_PRIVATE T3DPlatform
            LINK_PRIVATE T3DLog
            LINK_PRIVATE T3DUtils
            LINK_PRIVATE T3DFramework
            LINK_PRIVATE T3DMath
            LINK_PRIVATE T3DCore
            LINK_PRIVATE legacy_stdio_definitions
            )
    else ()
        # Visual Studio version is older than 2015
        target_link_libraries(
            ${LIB_NAME}
            LINK_PRIVATE T3DPlatform
            LINK_PRIVATE T3DLog
            LINK_PRIVATE T3DUtils
            LINK_PRIVATE T3DFramework
            LINK_PRIVATE T3DMath
            LINK_PRIVATE T3DCore
            )
    endif ()


    install(TARGETS ${LIB_NAME}
        RUNTIME DESTINATION bin/Debug CONFIGURATIONS Debug
        LIBRARY DESTINATION bin/Debug CONFIGURATIONS Debug
        ARCHIVE DESTINATION lib/Debug CONFIGURATIONS Debug
        )

    install(DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/ DESTINATION include/Core
        FILE_PERMISSIONS GROUP_READ OWNER_READ
        PATTERN "Android" EXCLUDE
        PATTERN "iOS" EXCLUDE
        PATTERN "Linux" EXCLUDE
        PATTERN "MacOSX" EXCLUDE
        PATTERN "Unix" EXCLUDE
        PATTERN "Windows" EXCLUDE
        PATTERN "Direct3D9" EXCLUDE
        PATTERN "Direct3D11" EXCLUDE
        PATTERN "OpenGL3Plus" EXCLUDE
        PATTERN "OpenGLES2" EXCLUDE
        PATTERN "OpenGLES3" EXCLUDE
        )

    add_custom_command(TARGET ${BIN_NAME}
        PRE_LINK
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_BINARY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_BINARY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
        )
elseif (TINY3D_OS_MACOSX)
    # Mac OS X

    target_link_libraries(
        ${LIB_NAME}
        LINK_PRIVATE ${SDL2_LIBRARY}
        LINK_PRIVATE ${SDL2_OSX_FRAMEWORKS}
#       LINK_PRIVATE z
        )
elseif (TINY3D_OS_LINUX)
    # Linux
    target_link_libraries(
        ${LIB_NAME}
        LINK_PRIVATE T3DPlatform
        LINK_PRIVATE T3DLog
        LINK_PRIVATE T3DUtils
        LINK_PRIVATE T3DFramework
        LINK_PRIVATE T3DMath
        LINK_PRIVATE T3DCore
#        LINK_PRIVATE ${SDL2_LIBRARY}
#       LINK_PRIVATE z
        )
elseif (TINY3D_OS_IOS)
    # iOS
    set(CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG "-Wl,-rpath")

    set_target_properties (${LIB_NAME} PROPERTIES
        BUILD_WITH_INSTALL_RPATH 1
        MACOSX_RPATH 1
        INSTALL_NAME_DIR "@rpath"
        )

    target_link_libraries(
        ${LIB_NAME}
        LINK_PRIVATE T3DPlatform
        LINK_PRIVATE T3DLog
        LINK_PRIVATE T3DUtils
        LINK_PRIVATE T3DFramework
        LINK_PRIVATE T3DMath
        LINK_PRIVATE T3DCore
        )
elseif (TINY3D_OS_ANDROID)
    # Android
    target_link_libraries(
        ${LIB_NAME}
        LINK_PRIVATE T3DPlatform
        LINK_PRIVATE T3DLog
        LINK_PRIVATE T3DUtils
        LINK_PRIVATE T3DFramework
        LINK_PRIVATE T3DMath
        LINK_PRIVATE T3DCore
#        LINK_PRIVATE ${SDL2_BINARY}
#       LINK_PRIVATE z
        )
    
    set(ANDROID_ASSETS_DIR "${CMAKE_CURRENT_BINARY_DIR}/../../../../../src/main/assets")
    
endif (TINY3D_OS_WINDOWS)


# Setup project folder
set_property(TARGET ${BIN_NAME} PROPERTY FOLDER "Kernel")


message(STATUS "Generating project : ${BIN_NAME} - done")
