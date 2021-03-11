
message(STATUS "Looking for FBX SDK ...")

#if (MSVC)
#    if (${MSVC_VERSION} MATCHES "1900")
#        # Visual Studio 2015
#        set (FBXSDK_LIB_SUFFIXES "lib/vs2015/${MSVC_CXX_ARCHITECTURE_ID}")
#    elseif (${MSVC_VERSION} GREATER_EQUAL  "1910" AND ${MSVC_VERSION} LESS "1920")
#        # Visual Studio 2017
#        set (FBXSDK_LIB_SUFFIXES "lib/vs2017/${MSVC_CXX_ARCHITECTURE_ID}")
#    elseif (${MSVC_VERSION} GREATER_EQUAL "1920" AND ${MSVC_VERSION} LESS "1929")
#        # Visual Studio 2019
#        set (FBXSDK_LIB_SUFFIXES "lib/vs2019/${MSVC_CXX_ARCHITECTURE_ID}")
#    endif (${MSVC_VERSION} MATCHES "1900")
#
#    if (CMAKE_BUILD_TYPE MATCHES "Debug")
#        set (FBXSDK_LIB_SUFFIXES "${FBXSDK_LIB_SUFFIXES}/debug")
#    elseif (CMAKE_BUILD_TYPE MATCHES "Release")
#        set (FBXSDK_LIB_SUFFIXES "${FBXSDK_LIB_SUFFIXES}/release")
#    endif (CMAKE_BUILD_TYPE MATCHES "Debug")
#else (MSVC)
#    set (FBXSDK_LIB_SUFFIXES "lib")
#endif (MSVC)

if (WIN32)
    set (FBXSDK_LIB_SUFFIXES "prebuilt/Windows/${MSVC_CXX_ARCHITECTURE_ID}")
elseif (APPLE AND NOT IOS)
    set (FBXSDK_LIB_SUFFIXES "prebuilt/OSX")
elseif (UNIX AND NOT APPLE)
    set (FBXSDK_LIB_SUFFIXES "prebuilt/Linux")
endif (WIN32)


message(STATUS "Looking for FSDK SDK suffixes : ${FBXSDK_LIB_SUFFIXES}")

FIND_PATH(FBXSDK_INCLUDE_DIR 
  NAMES fbxsdk.h
  HINTS ${FBXSDK_HOME}
  PATH_SUFFIXES include
#  PATHS include
)

FIND_LIBRARY(FBXSDK_LIBRARY_TEMP
  NAMES libfbxsdk.lib libfbxsdk.a
  HINTS ${FBXSDK_HOME}
  PATH_SUFFIXES ${FBXSDK_LIB_SUFFIXES}
#  PATHS .
)

FIND_FILE(FBXSDK_BINARY
  NAMES "libfbxsdk.dll" "libfbxsdk.so" "libfbxsdk.dylib"
  HINTS ${FBXSDK_HOME}
  PATH_SUFFIXES ${FBXSDK_LIB_SUFFIXES}
)

message(STATUS "${FBXSDK_INCLUDE_DIR}")
message(STATUS "${FBXSDK_LIBRARY_TEMP}")
message(STATUS "${FBXSDK_BINARY}")

SET(FBXSDK_FOUND "NO")
IF(FBXSDK_LIBRARY_TEMP)
  # Set the final string here so the GUI reflects the final state.
  SET(FBXSDK_LIBRARY ${FBXSDK_LIBRARY_TEMP} CACHE STRING "Where the FBX SDK Library can be found")
  # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
  SET(FBXSDK_LIBRARY_TEMP "${FBXSDK_LIBRARY_TEMP}" CACHE INTERNAL "")

  SET(FBXSDK_FOUND "YES")
ENDIF(FBXSDK_LIBRARY_TEMP)

