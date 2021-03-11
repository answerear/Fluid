
FIND_PATH(GLEW_INCLUDE_DIR 
  NAMES glew.h GL/glew.h
  HINTS
  ${GLEW_HOME}
  PATH_SUFFIXES include include/GL
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/GLEW
  /usr/include/GLEW
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(GLEW_LIBRARY_TEMP
  NAMES glew32s glew32
  HINTS
  ${GLEW_HOME}
  PATH_SUFFIXES lib64 lib prebuilt/win32/${MSVC_CXX_ARCHITECTURE_ID}
  PATHS
  /sw
  /opt/local
  /opt/csw
  /opt
)


SET(GLEW_FOUND "NO")
IF(GLEW_LIBRARY_TEMP)
  # Set the final string here so the GUI reflects the final state.
  SET(GLEW_LIBRARY ${GLEW_LIBRARY_TEMP} CACHE STRING "Where the glew Library can be found")
  # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
  SET(GLEW_LIBRARY_TEMP "${GLEW_LIBRARY_TEMP}" CACHE INTERNAL "")
  
  SET(GLEW_FOUND "YES")
ENDIF(GLEW_LIBRARY_TEMP)

