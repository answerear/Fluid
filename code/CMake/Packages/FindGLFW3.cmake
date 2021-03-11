
FIND_PATH(GLFW3_INCLUDE_DIR 
  NAMES glfw3.h GLFW/glfw3.h
  HINTS
  ${GLFW3_HOME}
  PATH_SUFFIXES include include/GLFW
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/GLFW
  /usr/include/GLFW
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(GLFW3_LIBRARY_TEMP
  NAMES glfw3
  HINTS
  ${GLFW3_HOME}
  PATH_SUFFIXES lib64 lib prebuilt/win32/${MSVC_CXX_ARCHITECTURE_ID}
  PATHS
  /sw
  /opt/local
  /opt/csw
  /opt
)


SET(GLFW3_FOUND "NO")
IF(GLFW3_LIBRARY_TEMP)
  # Set the final string here so the GUI reflects the final state.
  SET(GLFW3_LIBRARY ${GLFW3_LIBRARY_TEMP} CACHE STRING "Where the glfw3 Library can be found")
  # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
  SET(GLFW3_LIBRARY_TEMP "${GLFW3_LIBRARY_TEMP}" CACHE INTERNAL "")
  
  SET(GLFW3_FOUND "YES")
ENDIF(GLFW3_LIBRARY_TEMP)

