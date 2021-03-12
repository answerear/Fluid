#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain.
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

set_project_name(T3DCore)

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


# Setup search header path for this project.
include_directories(
    "${TINY3D_PLATFORM_DIR}/Include"
    "${TINY3D_MATH_DIR}/Include"
    "${TINY3D_LOG_DIR}/Include"
    "${TINY3D_UTILS_DIR}/Include"
    "${TINY3D_FRAMEWORK_DIR}/Include"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${SDL2_INCLUDE_DIR}"
    "${TINY3D_DEP_DIR}/rapidjson"
    "${PROTOBUF_INCLUDE_DIR}"
    "${TINY3D_DEP_DIR}/zlib/include"    # only for windows
    )

if (TINY3D_OS_WINDOWS)
    set(TINY3D_ZLIB_LIBRARY "${TINY3D_DEP_DIR}/zlib/prebuilt/win32/${MSVC_CXX_ARCHITECTURE_ID}/zlibstatic.lib")
endif (TINY3D_OS_WINDOWS)

# Setup header files for this project.
set_project_files(Include ${CMAKE_CURRENT_SOURCE_DIR}/Include/ .h)
set_project_files(Include\\\\Kernel ${CMAKE_CURRENT_SOURCE_DIR}/Include/Kernel/ .h)
set_project_files(Include\\\\Kernel ${CMAKE_CURRENT_SOURCE_DIR}/Include/Kernel/ .inl)
set_project_files(Include\\\\Resource ${CMAKE_CURRENT_SOURCE_DIR}/Include/Resource/ .h)
set_project_files(Include\\\\Resource ${CMAKE_CURRENT_SOURCE_DIR}/Include/Resource/ .inl)
set_project_files(Include\\\\Memory ${CMAKE_CURRENT_SOURCE_DIR}/Include/Memory/ .h)
set_project_files(Include\\\\Render ${CMAKE_CURRENT_SOURCE_DIR}/Include/Render/ .h)
set_project_files(Include\\\\Render ${CMAKE_CURRENT_SOURCE_DIR}/Include/Render/ .inl)
set_project_files(Include\\\\ImageCodec ${CMAKE_CURRENT_SOURCE_DIR}/Include/ImageCodec/ .h)
set_project_files(Include\\\\ImageCodec ${CMAKE_CURRENT_SOURCE_DIR}/Include/ImageCodec/ .inl)
set_project_files(Include\\\\Scene ${CMAKE_CURRENT_SOURCE_DIR}/Include/Scene/ .h)
set_project_files(Include\\\\Scene ${CMAKE_CURRENT_SOURCE_DIR}/Include/Scene/ .inl)
set_project_files(Include\\\\Bound ${CMAKE_CURRENT_SOURCE_DIR}/Include/Bound/ .h)
set_project_files(Include\\\\Bound ${CMAKE_CURRENT_SOURCE_DIR}/Include/Bound/ .inl)
set_project_files(Include\\\\Component ${CMAKE_CURRENT_SOURCE_DIR}/Include/Component/ .h)
set_project_files(Include\\\\Component ${CMAKE_CURRENT_SOURCE_DIR}/Include/Component/ .inl)
set_project_files(Include\\\\Serializer ${CMAKE_CURRENT_SOURCE_DIR}/Include/Serializer/ .h)

# Setup source files for this project.
set_project_files(Source ${CMAKE_CURRENT_SOURCE_DIR}/Source/ .cpp)
set_project_files(Source\\\\Kernel ${CMAKE_CURRENT_SOURCE_DIR}/Source/Kernel/ .cpp)
set_project_files(Source\\\\Resource ${CMAKE_CURRENT_SOURCE_DIR}/Source/Resource/ .cpp)
set_project_files(Source\\\\Memory ${CMAKE_CURRENT_SOURCE_DIR}/Source/Memory/ .cpp)
set_project_files(Source\\\\Render ${CMAKE_CURRENT_SOURCE_DIR}/Source/Render/ .cpp)
set_project_files(Source\\\\ImageCodec ${CMAKE_CURRENT_SOURCE_DIR}/Source/ImageCodec/ .cpp)
set_project_files(Source\\\\Scene ${CMAKE_CURRENT_SOURCE_DIR}/Source/Scene/ .cpp)
set_project_files(Source\\\\Bound ${CMAKE_CURRENT_SOURCE_DIR}/Source/Bound/ .cpp)
set_project_files(Source\\\\Component ${CMAKE_CURRENT_SOURCE_DIR}/Source/Component/ .cpp)
set_project_files(Source\\\\Serializer ${CMAKE_CURRENT_SOURCE_DIR}/Source/Serializer/ .cpp)

# tinyxml2
set_project_files(Source\\\\Support\\\\tinyxml2 ${CMAKE_CURRENT_SOURCE_DIR}/Source/Support/tinyxml2/ .h)
set_project_files(Source\\\\Support\\\\tinyxml2 ${CMAKE_CURRENT_SOURCE_DIR}/Source/Support/tinyxml2/ .cpp)

# protobuf source files
set_project_files(protobuf ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/ .pb.h)
set_project_files(protobuf ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/ .pb.cc)


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
            LINK_PRIVATE legacy_stdio_definitions
            LINK_PRIVATE ${SDL2_LIBRARY}
            LINK_PRIVATE ${PROTOBUF_LIBRARY}
            #LINK_PRIVATE ${FREEIMAGE_LIBRARY}
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
            LINK_PRIVATE ${SDL2_LIBRARY}
            LINK_PRIVATE ${PROTOBUF_LIBRARY}
            #LINK_PRIVATE ${FREEIMAGE_LIBRARY}
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
    
    add_custom_command(TARGET ${BIN_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/../assets/config/Windows/Tiny3D.cfg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Tiny3D.cfg
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/../assets/config/Windows/Tiny3D.cfg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Tiny3D.cfg
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/icon"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/icon"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/models"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/models"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/textures"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/textures"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/builtin/icon"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/builtin/icon"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/builtin/program"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/builtin/program"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/builtin/materials"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/builtin/materials"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/icon" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/icon"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/icon" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/icon"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/models" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/models"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/models" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/models"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/textures" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/textures"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/textures" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/textures"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/builtin/icon" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/builtin/icon"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/builtin/icon" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/builtin/icon"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/builtin/program" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/builtin/program"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/builtin/program" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/builtin/program"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/builtin/materials" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/builtin/materials"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../assets/builtin/materials" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/builtin/materials"
        )
elseif (TINY3D_OS_MACOSX)
    # Mac OS X

    target_link_libraries(
        ${LIB_NAME}
        LINK_PRIVATE T3DPlatform
        LINK_PRIVATE T3DLog
        LINK_PRIVATE T3DUtils
        LINK_PRIVATE T3DFramework
        LINK_PRIVATE T3DMath
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
        LINK_PRIVATE ${SDL2_LIBRARY}
#       LINK_PRIVATE z
        )

    add_custom_command(TARGET ${BIN_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/../../assets/config/Linux/Tiny3D.cfg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Tiny3D.cfg
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/lib${BIN_NAME}.so" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib${BIN_NAME}.so"
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/icon
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/icon
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/scripts
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/scripts
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Assets/textures
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Assets/textures
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../assets/icon ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets/icon
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../assets/scripts ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets/scripts
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../assets/textures ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets/textures
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
        LINK_PRIVATE ${SDL2_BINARY}
#       LINK_PRIVATE z
        )
    
    set(ANDROID_ASSETS_DIR "${CMAKE_CURRENT_BINARY_DIR}/../../../../../src/main/assets")
    
    add_custom_command(TARGET ${BIN_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/../assets/config/Android/Tiny3D.cfg ${ANDROID_ASSETS_DIR}/Tiny3D.cfg
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ANDROID_ASSETS_DIR}/icon
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../Assets/Icon ${ANDROID_ASSETS_DIR}/icon
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ANDROID_ASSETS_DIR}/scripts
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PORJECT_SOURCE_DIR}/../Assets/scripts ${ANDROID_ASSETS_DIR}/scripts
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ANDROID_ASSETS_DIR}/textures
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PORJECT_SOURCE_DIR}/../Assets/textures ${ANDROID_ASSETS_DIR}/textures
    #   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/../../assets/config/Tiny3D.cfg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Tiny3D.cfg
    #   #COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../../assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../assets
        )
endif (TINY3D_OS_WINDOWS)


# Setup project folder
set_property(TARGET ${BIN_NAME} PROPERTY FOLDER "Kernel")


message(STATUS "Generating project : ${BIN_NAME} - done")
