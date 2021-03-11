
message(STATUS "Looking for protobuf ...")

FIND_PATH(PROTOBUF_INCLUDE_DIR 
  NAMES google
  HINTS ${PROTOBUF_HOME}
  PATH_SUFFIXES include/
#  PATHS include
)

FIND_LIBRARY(PROTOBUF_LIBRARY_TEMP
  NAMES "libprotobuf" "libprotobuf.a"
  HINTS ${PROTOBUF_HOME}
  PATH_SUFFIXES ${PROTOBUF_SUFFIXES}
#  PATHS .
)

FIND_FILE(PROTOBUF_BINARY
  NAMES "libprotobuf.dll" "libprotobuf.so" "libprotobuf.dylib"
  HINTS ${PROTOBUF_HOME}
  PATH_SUFFIXES ${PROTOBUF_SUFFIXES}
)

FIND_LIBRARY(PROTOBUF_LITE_LIBRARY_TEMP
  NAMES "libprotobuf-lite" "libprotobuf-lite.a"
  HINTS ${PROTOBUF_HOME}
  PATH_SUFFIXES ${PROTOBUF_SUFFIXES}
#  PATHS .
)

FIND_FILE(PROTOBUF_LITE_BINARY
  NAMES "libprotobuf-lite.dll" "libprotobuf-lite.so" "libprotobuf-lite.dylib"
  HINTS ${PROTOBUF_HOME}
  PATH_SUFFIXES ${PROTOBUF_SUFFIXES}
)



message(STATUS "${PROTOBUF_INCLUDE_DIR}")
message(STATUS "${PROTOBUF_LIBRARY_TEMP}")
message(STATUS "${PROTOBUF_BINARY}")
message(STATUS "${PROTOBUF_LITE_LIBRARY_TEMP}")
message(STATUS "${PROTOBUF_LITE_BINARY}")

SET(PROTOBUF_FOUND "NO")
IF(PROTOBUF_LIBRARY_TEMP)
  # Set the final string here so the GUI reflects the final state.
  SET(PROTOBUF_LIBRARY ${PROTOBUF_LIBRARY_TEMP} CACHE STRING "Where the protobuf Library can be found")
  # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
  SET(PROTOBUF_LIBRARY_TEMP "${PROTOBUF_LIBRARY_TEMP}" CACHE INTERNAL "")

  SET(PROTOBUF_FOUND "YES")
ENDIF(PROTOBUF_LIBRARY_TEMP)

SET(PROTOBUF_LITE_FOUND "NO")
IF(PROTOBUF_LITE_LIBRARY_TEMP)
  # Set the final string here so the GUI reflects the final state.
  SET(PROTOBUF_LITE_LIBRARY ${PROTOBUF_LITE_LIBRARY_TEMP} CACHE STRING "Where the protobuf-lite Library can be found")
  # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
  SET(PROTOBUF_LITE_LIBRARY_TEMP "${PROTOBUF_LITE_LIBRARY_TEMP}" CACHE INTERNAL "")

  SET(PROTOBUF_LITE_FOUND "YES")
ENDIF(PROTOBUF_LITE_LIBRARY_TEMP)


#---------------------------------------- For Debug ---------------------------------------

FIND_LIBRARY(PROTOBUF_LIBRARY_TEMP_D
  NAMES "libprotobufd" "libprotobuf.a"
  HINTS ${PROTOBUF_HOME}
  PATH_SUFFIXES ${PROTOBUF_SUFFIXES}
#  PATHS .
)

FIND_FILE(PROTOBUF_BINARY_D
  NAMES "libprotobufd.dll" "libprotobuf.so" "libprotobuf.dylib"
  HINTS ${PROTOBUF_HOME}
  PATH_SUFFIXES ${PROTOBUF_SUFFIXES}
)

FIND_LIBRARY(PROTOBUF_LITE_LIBRARY_TEMP_D
  NAMES "libprotobuf-lited" "libprotobuf-lite.a"
  HINTS ${PROTOBUF_HOME}
  PATH_SUFFIXES ${PROTOBUF_SUFFIXES}
#  PATHS .
)

FIND_FILE(PROTOBUF_LITE_BINARY_D
  NAMES "libprotobuf-lited.dll" "libprotobuf-lite.so" "libprotobuf-lite.dylib"
  HINTS ${PROTOBUF_HOME}
  PATH_SUFFIXES ${PROTOBUF_SUFFIXES}
)

message(STATUS "${PROTOBUF_LIBRARY_TEMP_D}")
message(STATUS "${PROTOBUF_BINARY_D}")
message(STATUS "${PROTOBUF_LITE_LIBRARY_TEMP_D}")
message(STATUS "${PROTOBUF_LITE_BINARY_D}")

SET(PROTOBUFD_FOUND "NO")
IF(PROTOBUF_LIBRARY_TEMP_D)
  # Set the final string here so the GUI reflects the final state.
  SET(PROTOBUF_LIBRARY_D ${PROTOBUF_LIBRARY_TEMP_D} CACHE STRING "Where the protobuf Library for debug can be found")
  # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
  SET(PROTOBUF_LIBRARY_TEMP_D "${PROTOBUF_LIBRARY_TEMP_D}" CACHE INTERNAL "")

  SET(PROTOBUFD_FOUND "YES")
ENDIF(PROTOBUF_LIBRARY_TEMP_D)

SET(PROTOBUF_LITED_FOUND "NO")
IF(PROTOBUF_LITE_LIBRARY_TEMP_D)
  # Set the final string here so the GUI reflects the final state.
  SET(PROTOBUF_LITE_LIBRARY_D ${PROTOBUF_LITE_LIBRARY_TEMP_D} CACHE STRING "Where the protobuf-lite Library for debug can be found")
  # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
  SET(PROTOBUF_LITE_LIBRARY_TEMP_D "${PROTOBUF_LITE_LIBRARY_TEMP_D}" CACHE INTERNAL "")

  SET(PROTOBUF_LITED_FOUND "YES")
ENDIF(PROTOBUF_LITE_LIBRARY_TEMP_D)

