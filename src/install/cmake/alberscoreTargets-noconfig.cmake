#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "albers" for configuration ""
set_property(TARGET albers APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(albers PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "-L/home/amelie/Desktop/root/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic"
  IMPORTED_LOCATION_NOCONFIG "/home/amelie/workspace/albers-core/install/lib/libalbers.so"
  IMPORTED_SONAME_NOCONFIG "libalbers.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS albers )
list(APPEND _IMPORT_CHECK_FILES_FOR_albers "/home/amelie/workspace/albers-core/install/lib/libalbers.so" )

# Import target "albers-write" for configuration ""
set_property(TARGET albers-write APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(albers-write PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/amelie/workspace/albers-core/install/bin/albers-write"
  )

list(APPEND _IMPORT_CHECK_TARGETS albers-write )
list(APPEND _IMPORT_CHECK_FILES_FOR_albers-write "/home/amelie/workspace/albers-core/install/bin/albers-write" )

# Import target "albers-read" for configuration ""
set_property(TARGET albers-read APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(albers-read PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/amelie/workspace/albers-core/install/bin/albers-read"
  )

list(APPEND _IMPORT_CHECK_TARGETS albers-read )
list(APPEND _IMPORT_CHECK_FILES_FOR_albers-read "/home/amelie/workspace/albers-core/install/bin/albers-read" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
