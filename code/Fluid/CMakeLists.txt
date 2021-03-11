#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain.
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

set_project_name(Fluid)

message(STATUS "Generating project : ${BIN_NAME}")


if (MSVC)
    # Add definition only for Windows.
    if (FLUID_BUILD_SHARED_LIBS)
        add_definitions(-D${LIB_NAME_TOUPPER}_EXPORT -D_USRDLL)
    endif (FLUID_BUILD_SHARED_LIBS)

    # Disable some warning for protobuf
    add_definitions(
        /wd4244 # 'conversion' conversion from 'type1' to 'type2', possible loss of data
        /wd4267 # 'var' : conversion from 'size_t' to 'type', possible loss of data
        /wd4309 # 'conversion' : truncation of constant value
        /wd4800 # 'type' : forcing value to bool 'true' or 'false' (performance warning)
    )
endif (MSVC)


# Setup all cmake variables for this project.
set(FLUID_DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies")


# Setup search header path for this project.
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${SDL2_INCLUDE_DIR}"
    )

#if (FLUID_OS_WINDOWS)
#    set(TINY3D_ZLIB_LIBRARY "${TINY3D_DEP_DIR}/zlib/prebuilt/win32/${MSVC_CXX_ARCHITECTURE_ID}/zlibstatic.lib")
#endif (FLUID_OS_WINDOWS)

# Setup header files for this project.
set_project_files(Include ${CMAKE_CURRENT_SOURCE_DIR}/Include/ .h)
#set_project_files(Include\\\\Kernel ${CMAKE_CURRENT_SOURCE_DIR}/Include/Kernel/ .h)


# Setup source files for this project.
set_project_files(Source ${CMAKE_CURRENT_SOURCE_DIR}/Source/ .cpp)
#set_project_files(Source\\\\Kernel ${CMAKE_CURRENT_SOURCE_DIR}/Source/Kernel/ .cpp)


# Setup all files for building this project.
if (FLUID_BUILD_SHARED_LIBS)
    # Make dynamic library for this project.
    add_library(${LIB_NAME} SHARED ${SOURCE_FILES})
else (FLUID_BUILD_SHARED_LIBS)
    # Make static library for this project.
    add_library(${LIB_NAME} STATIC ${SOURCE_FILES})
endif (FLUID_BUILD_SHARED_LIBS)


if (FLUID_OS_WINDOWS)
    # Windows

    # Setup link libraries for this project.
    if (MSVC_VERSION GREATER_EQUAL 1900)
        # Visual Studio version is 2015 or later.
        target_link_libraries(
            ${LIB_NAME}
            LINK_PRIVATE legacy_stdio_definitions
            LINK_PRIVATE ${SDL2_LIBRARY}
            )
    else ()
        # Visual Studio version is older than 2015
        target_link_libraries(
            ${LIB_NAME}
            LINK_PRIVATE ${SDL2_LIBRARY}
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
        LINK_PRIVATE ${SDL2_LIBRARY}
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
        )
elseif (TINY3D_OS_ANDROID)
    # Android
    target_link_libraries(
        ${LIB_NAME}
        LINK_PRIVATE ${SDL2_BINARY}
#       LINK_PRIVATE z
        )
    
    set(ANDROID_ASSETS_DIR "${CMAKE_CURRENT_BINARY_DIR}/../../../../../src/main/assets")
    
endif (FLUID_OS_WINDOWS)


# Setup project folder
set_property(TARGET ${BIN_NAME} PROPERTY FOLDER "Kernel")


message(STATUS "Generating project : ${BIN_NAME} - done")
