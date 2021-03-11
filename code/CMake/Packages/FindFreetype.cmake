
FIND_PATH(FREETYPE_INCLUDE_DIR 
  NAMES freetype.h freetype/freetype.h
  HINTS
  ${FREETYPE_HOME}
  PATH_SUFFIXES include include/freetype
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/freetype
  /usr/include/freetype
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_PATH(FREETYPE_FT2BUILD_INCLUDE_DIR 
  NAMES ft2build.h
  HINTS
  ${FREETYPE_HOME}
  PATH_SUFFIXES include include/freetype
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/freetype
  /usr/include/freetype
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(FREETYPE_LIBRARY_TEMP
  NAMES freetype28
  HINTS
  ${FREETYPE_HOME}
  PATH_SUFFIXES lib64 lib prebuilt/win32/${MSVC_CXX_ARCHITECTURE_ID}
  PATHS
  /sw
  /opt/local
  /opt/csw
  /opt
)


SET(FREETYPE_FOUND "NO")
IF(FREETYPE_LIBRARY_TEMP)
  # Set the final string here so the GUI reflects the final state.
  SET(FREETYPE_LIBRARY ${FREETYPE_LIBRARY_TEMP} CACHE STRING "Where the FreeType Library can be found")
  # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
  SET(FREETYPE_LIBRARY_TEMP "${FREETYPE_LIBRARY_TEMP}" CACHE INTERNAL "")

  IF (NOT FREETYPE_FT2BUILD_INCLUDE_DIR STREQUAL FREETYPE_INCLUDE_DIR)
    set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIRS} ${FREETYPE_FT2BUILD_INCLUDE_DIR})
  ENDIF ()
  
  SET(FREETYPE_FOUND "YES")
ENDIF(FREETYPE_LIBRARY_TEMP)

