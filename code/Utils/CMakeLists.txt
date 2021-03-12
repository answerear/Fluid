#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain. 
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

set_project_name(T3DUtils)

message(STATUS "Generating project : ${BIN_NAME}")

if (MSVC)
	# Add definition only for Windows.
	if (TINY3D_BUILD_SHARED_LIBS)
		add_definitions(-D${LIB_NAME_TOUPPER}_EXPORT -D_USRDLL)
	endif (TINY3D_BUILD_SHARED_LIBS)
endif (MSVC)



# Setup all cmake variables for this project.
set(TINY3D_PLATFORM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Platform")


# Setup search header path for this project.
include_directories(
	"${TINY3D_PLATFORM_DIR}/Include"
	"${CMAKE_CURRENT_SOURCE_DIR}/Include"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source"
	)


# Setup header files for this project.
set_project_files(Include ${CMAKE_CURRENT_SOURCE_DIR}/Include/ .h)
set_project_files(Include ${CMAKE_CURRENT_SOURCE_DIR}/Include/ .inl)

# Setup source files for this project.
set_project_files(Source ${CMAKE_CURRENT_SOURCE_DIR}/Source/ .cpp)


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
			LINK_PRIVATE legacy_stdio_definitions
			)
	else ()
		# Visual Studio version is older than 2015
		target_link_libraries(
			${LIB_NAME}
			LINK_PRIVATE T3DPlatform
			)
	endif ()
	

	install(TARGETS ${LIB_NAME}
		RUNTIME DESTINATION bin/Debug CONFIGURATIONS Debug
		LIBRARY DESTINATION bin/Debug CONFIGURATIONS Debug
		ARCHIVE DESTINATION lib/Debug CONFIGURATIONS Debug
		)

	install(DIRECTORY 
		${CMAKE_CURRENT_SOURCE_DIR}/Include/ DESTINATION include/Log
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
		LINK_PRIVATE T3DPlatform
		)
elseif (TINY3D_OS_LINUX)
	# Linux
	target_link_libraries(
		${LIB_NAME}
		LINK_PRIVATE T3DPlatform
		)

	add_custom_command(TARGET ${BIN_NAME}
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/lib${BIN_NAME}.so" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib${BIN_NAME}.so"
		)
elseif (TINY3D_OS_IOS OR TINY3D_OS_MACOSX)
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
        )
elseif (TINY3D_OS_ANDROID)
	# Android
	target_link_libraries(
        ${LIB_NAME}
        LINK_PRIVATE T3DPlatform
        )
endif (TINY3D_OS_WINDOWS)


# Setup project folder
set_property(TARGET ${BIN_NAME} PROPERTY FOLDER "Kernel")


message(STATUS "Generating project : ${BIN_NAME} - done")
