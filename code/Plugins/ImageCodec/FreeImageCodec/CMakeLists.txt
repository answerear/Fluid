#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain. 
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

set_project_name(FreeImageCodec)

if (MSVC)
    if (TINY3D_BUILD_SHARED_LIBS)
        add_definitions(-D${LIB_NAME_TOUPPER}_EXPORT -D_USRDLL)
    endif (TINY3D_BUILD_SHARED_LIBS)
endif (MSVC)


if (TINY3D_OS_WINDOWS)
    # Windows
    set(FREEIMAGE_LIB_SUFFIXES "prebuilt/win32/${MSVC_CXX_ARCHITECTURE_ID}")
elseif (TINY3D_OS_ANDROID)
    set(FREEIMAGE_LIB_SUFFIXES "prebuilt/Android/${ANDROID_ABI}")
elseif (TINY3D_OS_IOS)
    set(FREEIMAGE_LIB_SUFFIXES "prebuilt/iOS")

    add_definitions(-DPNG_ARM_NEON_OPT=0)
elseif (TINY3D_OS_MACOSX)
    set(FREEIMAGE_LIB_SUFFIXES "prebuilt/OSX")
elseif (TINY3D_OS_LINUX)
    set(FREEIMAGE_LIB_SUFFIXES "prebuilt/Linux")
endif (TINY3D_OS_WINDOWS)


set(FREEIMAGE_HOME "${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/freeimage" CACHE PATH "FreeImage library path")
find_package(FreeImage)

# Setup project include files path
include_directories(
    "${TINY3D_CORE_SOURCE_DIR}/Include"
    "${TINY3D_MATH_SOURCE_DIR}/Include"
    "${TINY3D_FRAMEWORK_SOURCE_DIR}/Include"
    "${TINY3D_PLATFORM_SOURCE_DIR}/Include"
    "${TINY3D_LOG_SOURCE_DIR}/Include"
	"${TINY3D_UTILS_SOURCE_DIR}/Include"
    "${SDL2_INCLUDE_DIR}"
    "${FREEIMAGE_INCLUDE_DIR}"
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

set_property(TARGET ${LIB_NAME} PROPERTY FOLDER "Plugins/ImageCodec")

if (TINY3D_OS_IOS)
#    find_library(FWK_SECURITY Security)

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
        LINK_PRIVATE T3DMath
        LINK_PRIVATE T3DCore
        LINK_PRIVATE ${FREEIMAGE_LIBRARY}
        )
elseif (TINY3D_OS_LINUX)
    target_link_libraries(
        ${LIB_NAME}
        LINK_PRIVATE T3DPlatform
        LINK_PRIVATE T3DLog
		LINK_PRIVATE T3DUtils
        LINK_PRIVATE T3DMath
        LINK_PRIVATE T3DCore
        LINK_PRIVATE ${FREEIMAGE_LIBRARY}
        )

    add_custom_command(TARGET ${BIN_NAME}
        POST_BUILD
        #COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Plugins"
        #COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/lib${BIN_NAME}.so" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Plugins/lib${BIN_NAME}.so"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/lib${BIN_NAME}.so" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib${BIN_NAME}.so"
        )
elseif (TINY3D_OS_WINDOWS)
    target_link_libraries(
        ${LIB_NAME}
        LINK_PRIVATE T3DPlatform
        LINK_PRIVATE T3DLog
		LINK_PRIVATE T3DUtils
        LINK_PRIVATE T3DMath
        LINK_PRIVATE T3DCore
        LINK_PRIVATE ${FREEIMAGE_LIBRARY}
        )
    
    add_custom_command(TARGET ${BIN_NAME}
        PRE_LINK
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
        COMMAND ${CMAKE_COMMAND} -E copy ${FREEIMAGE_BINARY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
        COMMAND ${CMAKE_COMMAND} -E copy ${FREEIMAGE_BINARY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
        )
#    add_custom_command(TARGET ${BIN_NAME}
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy "${FREEIMAGE_BINARY}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
elseif (TINY3D_OS_MACOSX)
    target_link_libraries(
        ${LIB_NAME}
        LINK_PRIVATE T3DPlatform
        LINK_PRIVATE T3DLog
		LINK_PRIVATE T3DUtils
        LINK_PRIVATE T3DMath
        LINK_PRIVATE T3DCore
        LINK_PRIVATE ${FREEIMAGE_LIBRARY}
        )
elseif (TINY3D_OS_ANDROID)
    target_link_libraries(
        ${LIB_NAME}
        LINK_PRIVATE T3DPlatform
        LINK_PRIVATE T3DLog
		LINK_PRIVATE T3DUtils
        LINK_PRIVATE T3DMath
        LINK_PRIVATE T3DCore
        LINK_PRIVATE ${FREEIMAGE_LIBRARY}
        )
    
#    set(T3D_ANDROID_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Android/app/libs/${ANDROID_ABI}")

#    add_custom_command(TARGET ${BIN_NAME}
#        PRE_LINK
#        COMMAND ${CMAKE_COMMAND} -E make_directory ${T3D_ANDROID_LIB_PATH}
#        COMMAND ${CMAKE_COMMAND} -E copy ${FREEIMAGE_BINARY} ${T3D_ANDROID_LIB_PATH}
#        #COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIBRARY} ${T3D_ANDROID_LIB_PATH}
#        )
endif (TINY3D_OS_IOS)



#install(TARGETS ${LIB_NAME}
#    RUNTIME DESTINATION bin/Debug CONFIGURATIONS Debug
#    LIBRARY DESTINATION bin/Debug CONFIGURATIONS Debug
#    )
