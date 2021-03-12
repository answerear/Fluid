#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain.
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

set_project_name(T3DPlatform)

message(STATUS "Generating project : ${BIN_NAME}")


if (MSVC)
	# Add definition only for Windows.
	if (TINY3D_BUILD_SHARED_LIBS)
		add_definitions(-D${LIB_NAME_TOUPPER}_EXPORT -D_USRDLL)
	endif (TINY3D_BUILD_SHARED_LIBS)
endif (MSVC)


# Setup search header path for this project.
include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/Include"
	"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Common"
	"${CMAKE_CURRENT_SOURCE_DIR}/Include/Application"
	"${CMAKE_CURRENT_SOURCE_DIR}/Include/Window"
	"${CMAKE_CURRENT_SOURCE_DIR}/Include/Time"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/IO"
	"${SDL2_INCLUDE_DIR}"
	)

if (TINY3D_OS_WINDOWS)
	# Windows
	include_directories(
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Windows"
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Desktop"
		)
elseif (TINY3D_OS_MACOSX)
	# Mac OS X
	include_directories(
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Unix"
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/OSX"
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Desktop"
		)
elseif (TINY3D_OS_LINUX)
	# Linux
	include_directories(
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Unix"
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Linux"
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Desktop"
		)
elseif (TINY3D_OS_IOS)
	# iOS
	include_directories(
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Unix"
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/iOS"
		)
elseif (TINY3D_OS_ANDROID)
	# Android
	include_directories(
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Unix"
		"${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Android"
		)
endif (TINY3D_OS_WINDOWS)




# Setup header files for this project.
set_project_files(Include ${CMAKE_CURRENT_SOURCE_DIR}/Include/ .h)
set_project_files(Include\\\\Adapter ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/ .h)
set_project_files(Include\\\\Adapter\\\\Common ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Common/ .h)
set_project_files(Include\\\\Application ${CMAKE_CURRENT_SOURCE_DIR}/Include/Application/ .h)
set_project_files(Include\\\\Window ${CMAKE_CURRENT_SOURCE_DIR}/Include/Window/ .h)
set_project_files(Include\\\\Time ${CMAKE_CURRENT_SOURCE_DIR}/Include/Time/ .h)
set_project_files(Include\\\\IO ${CMAKE_CURRENT_SOURCE_DIR}/Include/IO/ .h)
set_project_files(Include\\\\Device ${CMAKE_CURRENT_SOURCE_DIR}/Include/Device/ .h)
set_project_files(Include\\\\Console ${CMAKE_CURRENT_SOURCE_DIR}/Include/Console/ .h)
set_project_files(Include\\\\Reflection ${CMAKE_CURRENT_SOURCE_DIR}/Include/Reflection/ .h)

if (TINY3D_OS_WINDOWS)
	# Windows
	set_project_files(Include\\\\Adapter\\\\Windows ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Windows/ .h)
	set_project_files(Include\\\\Adapter\\\\Desktop ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Desktop/ .h)
elseif (TINY3D_OS_MACOSX)
	# Mac OS X
	set_project_files(Include\\\\Adapter\\\\Unix ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Unix/ .h)
	set_project_files(Include\\\\Adapter\\\\OSX ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/OSX/ .h)
	set_project_files(Include\\\\Adapter\\\\Desktop ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Desktop/ .h)
elseif (TINY3D_OS_LINUX)
	# Linux
	set_project_files(Include\\\\Adapter\\\\Unix ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Unix/ .h)
	set_project_files(Include\\\\Adapter\\\\Linux ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Linux/ .h)
	set_project_files(Include\\\\Adapter\\\\Desktop ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Desktop/ .h)
elseif (TINY3D_OS_IOS)
	# iOS
	set_project_files(Include\\\\Adapter\\\\Unix ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Unix/ .h)
	set_project_files(Include\\\\Adapter\\\\iOS ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/iOS/ .h)
elseif (TINY3D_OS_ANDROID)
	# Android
	set_project_files(Include\\\\Adapter\\\\Unix ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Unix/ .h)
	set_project_files(Include\\\\Adapter\\\\Android ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Android/ .h)
endif (TINY3D_OS_WINDOWS)

if (TINY3D_OS_DESKTOP)
	set_project_files(Include\\\\Adapter\\\\Desktop ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Desktop/ .h)
elseif (TINY3D_OS_MOBILE)
	set_project_files(Include\\\\Adapter\\\\Mobile ${CMAKE_CURRENT_SOURCE_DIR}/Include/Adapter/Mobile/ .h)
endif (TINY3D_OS_DESKTOP)


# Setup source files for this project.
set_project_files(Source ${CMAKE_CURRENT_SOURCE_DIR}/Source/ .cpp)
set_project_files(Source\\\\Adapter ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/ .cpp)
set_project_files(Source\\\\Adapter\\\\Common ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Common/ .cpp)
set_project_files(Source\\\\Application ${CMAKE_CURRENT_SOURCE_DIR}/Source/Application/ .cpp)
set_project_files(Source\\\\Window ${CMAKE_CURRENT_SOURCE_DIR}/Source/Window/ .cpp)
set_project_files(Source\\\\Time ${CMAKE_CURRENT_SOURCE_DIR}/Source/Time/ .cpp)
set_project_files(Source\\\\IO ${CMAKE_CURRENT_SOURCE_DIR}/Source/IO/ .cpp)
set_project_files(Source\\\\Device ${CMAKE_CURRENT_SOURCE_DIR}/Source/Device/ .cpp)
set_project_files(Source\\\\Console ${CMAKE_CURRENT_SOURCE_DIR}/Source/Console/ .cpp)
set_project_files(Source\\\\Reflection ${CMAKE_CURRENT_SOURCE_DIR}/Source/Reflection/ .cpp)

if (TINY3D_OS_WINDOWS)
	# Windows
	set_project_files(Source\\\\Adapter\\\\Windows ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Windows/ .cpp)
	set_project_files(Source\\\\Adapter\\\\Desktop ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Desktop/ .cpp)
elseif (TINY3D_OS_MACOSX)
	# Mac OS X
	set_project_files(Source\\\\Adapter\\\\Unix ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Unix/ .cpp)
	set_project_files(Source\\\\Adapter\\\\OSX ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/OSX/ .cpp)
	set_project_files(Source\\\\Adapter\\\\OSX ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/OSX/ .mm)
	set_project_files(Source\\\\Adapter\\\\Desktop ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Desktop/ .cpp)

	#foreach(FW ${TINY3D_FRAMEWORKS})
    #    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework ${FW}")
    #endforeach()
    message(STATUS "Link flags : ${CMAKE_EXE_LINKER_FLAGS}")
elseif (TINY3D_OS_LINUX)
	# Linux
	set_project_files(Source\\\\Adapter\\\\Unix ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Unix/ .cpp)
	set_project_files(Source\\\\Adapter\\\\Linux ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Linux/ .cpp)
	set_project_files(Source\\\\Adapter\\\\Desktop ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Desktop/ .cpp)
elseif (TINY3D_OS_IOS)
	# iOS
	set_project_files(Source\\\\Adapter\\\\Unix ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Unix/ .cpp)
	set_project_files(Source\\\\Adapter\\\\iOS ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/iOS/ .cpp)
	set_project_files(Source\\\\Adapter\\\\iOS ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/iOS/ .mm)
    set_project_files(Include\\\\Adapter\\\\iOS ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/iOS/ .h)
    set_project_files(Source\\\\Adapter\\\\iOS ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/iOS/ .m)
elseif (TINY3D_OS_ANDROID)
	# Android
	set_project_files(Source\\\\Adapter\\\\Unix ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Unix/ .cpp)
	set_project_files(Source\\\\Adapter\\\\Android ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Android/ .cpp)
endif (TINY3D_OS_WINDOWS)

if (TINY3D_OS_DESKTOP)
	set_project_files(Source\\\\Adapter\\\\Desktop ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Desktop/ .cpp)
elseif (TINY3D_OS_MOBILE)
	set_project_files(Source\\\\Adapter\\\\Mobile ${CMAKE_CURRENT_SOURCE_DIR}/Source/Adapter/Mobile/ .cpp)
endif (TINY3D_OS_DESKTOP)

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
	target_link_libraries(
		${LIB_NAME}
		LINK_PRIVATE ${SDL2_LIBRARY}
		)

	install(TARGETS ${LIB_NAME}
		RUNTIME DESTINATION bin/Debug CONFIGURATIONS Debug
		LIBRARY DESTINATION bin/Debug CONFIGURATIONS Debug
		ARCHIVE DESTINATION lib/Debug CONFIGURATIONS Debug
		)

	install(DIRECTORY
		${CMAKE_CURRENT_SOURCE_DIR}/Include/ DESTINATION include/Platform
		FILE_PERMISSIONS GROUP_READ OWNER_READ
		PATTERN "Android" EXCLUDE
		PATTERN "iOS" EXCLUDE
		PATTERN "Linux" EXCLUDE
		PATTERN "MacOSX" EXCLUDE
		PATTERN "Unix" EXCLUDE
		PATTERN "Windows" EXCLUDE)
elseif (TINY3D_OS_MACOSX)
	# Mac OS X
	target_link_libraries(
		${LIB_NAME}
		${SDL2_LIBRARY}
		${SDL2_OSX_FRAMEWORKS}
		)
elseif (TINY3D_OS_LINUX)
	# Linux
    add_definitions(-DSDL_VIDEO_DRIVER_X11=1)
	target_link_libraries(
		${LIB_NAME}
		LINK_PRIVATE X11
		LINK_PRIVATE ${SDL2_LIBRARY}
		)

	add_custom_command(TARGET ${BIN_NAME}
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/lib${BIN_NAME}.so" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib${BIN_NAME}.so"
		)
elseif (TINY3D_OS_IOS)
	# iOS
    find_library(FWK_SECURITY Security)

    set(CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG "-Wl,-rpath")

    set_target_properties (${LIB_NAME} PROPERTIES
        BUILD_WITH_INSTALL_RPATH 1
        MACOSX_RPATH 1
        INSTALL_NAME_DIR "@rpath"
        )

	target_link_libraries(
        ${LIB_NAME}
        ${SDL2_LIBRARY}
        ${SDL2_OSX_FRAMEWORKS}
        ${FWK_SECURITY}
		)
elseif (TINY3D_OS_ANDROID)
	# Android
	target_link_libraries(
		${LIB_NAME}
		LINK_PRIVATE ${SDL2_BINARY}
		log
		)
endif (TINY3D_OS_WINDOWS)


# Setup project folder
set_property(TARGET ${BIN_NAME} PROPERTY FOLDER "Kernel")


message(STATUS "Generating project : ${BIN_NAME} - done")
