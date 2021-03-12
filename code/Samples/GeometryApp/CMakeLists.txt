#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain.
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

set_project_name(GeometryApp)


if (MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup ")
endif (MSVC)

# Setup project include files path
include_directories(
    "${TINY3D_PLATFORM_INC_DIR}"
    "${TINY3D_MATH_INC_DIR}"
    "${TINY3D_FRAMEWORK_INC_DIR}"
    "${TINY3D_LOG_INC_DIR}"
	"${TINY3D_UTILS_INC_DIR}"
    "${TINY3D_CORE_INC_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${SDL2_INCLUDE_DIR}"
    )

# Setup project header files
set_project_files(include ${CMAKE_CURRENT_SOURCE_DIR}/ .h)
set_project_files(common ${CMAKE_CURRENT_SOURCE_DIR}/../Common/ .h)


# Setup project source files
set_project_files(source ${CMAKE_CURRENT_SOURCE_DIR}/ .cpp)
set_project_files(common ${CMAKE_CURRENT_SOURCE_DIR}/../Common/ .cpp)


if (TINY3D_OS_WINDOWS)
    # Setup executable project for Windows.
    add_executable(
        ${BIN_NAME} WIN32
        ${SOURCE_FILES}
        )

    target_link_libraries(
        ${LIB_NAME}
        T3DPlatform
        T3DLog
		T3DUtils
        T3DMath
        T3DFramework
        T3DCore
        )
    
    # Setup install files and path for Windows.
    install(TARGETS ${BIN_NAME}
        RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
        LIBRARY DESTINATION bin/debug CONFIGURATIONS Debug
        ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
        )
elseif (TINY3D_OS_ANDROID)
    # Setup dynamic library (.so) project for Android. Because all libraries in Android is dynamics (.so).
    add_library(${LIB_NAME} SHARED ${SOURCE_FILES})

    target_link_libraries(
        ${LIB_NAME}
        T3DPlatform
        T3DLog
		T3DUtils
        T3DMath
        T3DFramework
        T3DCore
        )

    # Setup all files (.so) for Android APK
    set(T3D_ANDROID_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Android/app/libs/${ANDROID_ABI}")

    add_custom_command(TARGET ${BIN_NAME}
        PRE_LINK
        COMMAND ${CMAKE_COMMAND} -E make_directory ${T3D_ANDROID_LIB_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_BINARY} ${T3D_ANDROID_LIB_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIBRARY} ${T3D_ANDROID_LIB_PATH}
        )
elseif (TINY3D_OS_IOS OR TINY3D_OS_MACOSX)
    # Setup executable project for iOS or Mac OS X.
    add_executable(
        ${BIN_NAME} MACOSX_BUNDLE
        ${SOURCE_FILES}
        )

    if (TINY3D_OS_IOS)
        find_library(FWK_SECURITY Security)

        # Setup all link libraries and frameworks for iOS.
        target_link_libraries(
            ${LIB_NAME}
            T3DPlatform
            T3DLog
			T3DUtils
            T3DMath
            T3DFramework
            T3DCore
            #T3DXRenderer
            #FileSystemArchive
            #ZipArchive
            #FreeImageCodec
            #z
            #${SDL2_LIBRARY}
            #${SDL2_OSX_FRAMEWORKS}
            #${FWK_SECURITY}
            )

        # Setup all properties for this iOS project.
        set_target_properties(${BIN_NAME}
            PROPERTIES
            MACOSX_BUNDLE_BUNDLE_NAME ${BIN_NAME}                                   # Bundle name for this app.
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/iOS/Info.plist"   # Info.plist for this app.
            MACOSX_BUNDLE_GUI_IDENTIFIER "com.tiny3d.hello"                         # Bundle ID for this app.
            XCODE_ATTRIBUTE_SDKROOT "iphoneos"                                      # SDK root for this app.
            XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "9.0"                        # Minimum deployment target for this app.
            XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "F2KJRUV5HC"                           # Development team id for this app.
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"                   # Code sign identity for this app.
            MACOSX_BUNDLE_LONG_VERSION_STRING "0.1.0.0"                             # Long version string for this app.
            MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1.0"                              # Short version string for this app.
            XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@executable_path"
            )

        set(APPS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/${BIN_NAME}.app")
        set(DIRS "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}")

        install(CODE "
            include(BundleUtilities)
            fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
            " COMPONENT Runtime)

        set(ASSETS_DIR "${APPS}/Assets/")

        add_custom_command(TARGET ${BIN_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/../../assets/config/iOS/Tiny3D.cfg" "${APPS}"
            COMMAND cp "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}/*.dylib" "${APPS}"
#            COMMAND install_name_tool -change "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}/libT3DPlatform.dylib" "@rpath/libT3DPlatform.dylib" "${APPS}/${BIN_NAME}"
#            COMMAND install_name_tool -change "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}/libT3DLog.dylib" "@rpath/libT3DLog.dylib" "${APPS}/${BIN_NAME}"
#            COMMAND install_name_tool -change "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}/libT3DMath.dylib" "@rpath/libT3DMath.dylib" "${APPS}/${BIN_NAME}"
#            COMMAND install_name_tool -change "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}/libT3DFramework.dylib" "@rpath/libT3DFramework.dylib" "${APPS}/${BIN_NAME}"
#            COMMAND install_name_tool -change "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}/libT3DCore.dylib" "@rpath/libT3DCore.dylib" "${APPS}/${BIN_NAME}"
#            COMMAND install_name_tool -change "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}/libT3DPlatform.dylib" "@rpath/libT3DPlatform.dylib" "${APPS}/libT3DCore.dylib"
#            COMMAND install_name_tool -change "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}/libT3DLog.dylib" "@rpath/libT3DLog.dylib" "${APPS}/libT3DCore.dylib"
            COMMAND codesign --force --verbose --sign "iPhone Developer" "${APPS}/*.dylib"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${ASSETS_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../../Assets/Icon ${ASSETS_DIR}/Icon
            )
    elseif (TINY3D_OS_MACOSX)
        # Setup all link libraries frameworks for Mac OS X
        target_link_libraries(
            ${LIB_NAME}
            T3DPlatform
            T3DLog
			T3DUtils
            T3DMath
            T3DFramework
            T3DCore
            )

        # Setup all properties for this Mac OS X project.
        set_target_properties(${BIN_NAME}
            PROPERTIES
            MACOSX_BUNDLE_BUNDLE_NAME ${BIN_NAME}                                   # Bundle name for this app.
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/OSX/Info.plist"   # Info.plist for this app.
            MACOSX_BUNDLE_GUI_IDENTIFIER "com.tiny3d.hello"                         # Bundle ID for this app.
            MACOSX_BUNDLE_LONG_VERSION_STRING "0.1.0.0"                             # Long version string for this app.
            MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1.0"                              # Short version string for this app.
            XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@executable_path"
            )

        # Setup installing files for making a *.app for this project
        set(APPS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/${BIN_NAME}.app")
        set(DIRS "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}")
        install(CODE "
            include(BundleUtilities)
            fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
            " COMPONENT Runtime)

        install(TARGETS ${BIN_NAME}
            BUNDLE DESTINATION bin/debug CONFIGURATIONS Debug
            RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
            LIBRARY DESTINATION bin/debug CONFIGURATIONS Debug
            ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
            )

        set(ASSETS_DIR "${APPS}/Contents/MacOS/Assets/")

        add_custom_command(TARGET ${BIN_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/../../assets/config/OSX/Tiny3D.cfg" "${APPS}/Contents/MacOS"
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}/*" "${APPS}/Contents/MacOS"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${ASSETS_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../../Assets/Icon ${ASSETS_DIR}/Icon
            )
    endif (TINY3D_OS_IOS)
elseif (TINY3D_OS_LINUX)
    # Setup executable project for Linux.
    add_executable(
        ${BIN_NAME}
        ${SOURCE_FILES}
        )

    target_link_libraries(
        ${LIB_NAME}
        T3DPlatform
        T3DLog
		T3DUtils
        T3DMath
        T3DFramework
        T3DCore
        )

    # Setup install files and path for Windows.
    install(TARGETS ${BIN_NAME}
        RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
        LIBRARY DESTINATION bin/debug CONFIGURATIONS Debug
        ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
        )
endif (TINY3D_OS_WINDOWS)


# Setup project folder
set_property(TARGET ${BIN_NAME} PROPERTY FOLDER "Samples")
