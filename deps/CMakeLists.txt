cmake_minimum_required(VERSION 2.8)
project(alberscore CXX)

set(ALBERSCORE_MAJOR_VERSION 1)
set(ALBERSCORE_MINOR_VERSION 0)
set(ALBERSCORE_PATCH_VERSION 0)
set(ALBERSCORE_VERSION
  ${ALBERSCORE_MAJOR_VERSION}.${ALBERSCORE_MINOR_VERSION}.${ALBERSCORE_PATCH_VERSION})

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
# if(WIN32 AND NOT CYGWIN)
#  set(DEF_INSTALL_CMAKE_DIR CMake)
#else()
#  set(DEF_INSTALL_CMAKE_DIR lib/CMake/alberscore)
#endif()
set(DEF_INSTALL_CMAKE_DIR cmake)
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# Set up C++11
set(CPP11FLAGS "-std=c++11")
if (${APPLE})
    set(CPP11FLAGS "-std=c++11\ -stdlib=libc++")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -DDROP_CGAL ${CPP11FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-variable -Wno-unused-parameter")


# Make sure we find the Find*.cmake functions distributed with this package
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(ROOT)

# set up include-directories
include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}"
  "${ROOT_INCLUDE_DIR}"
  )  

# Add sub-directories
add_subdirectory(albers)
add_subdirectory(datamodel)
add_subdirectory(examples)
add_subdirectory(python)

# The interesting stuff goes here
# ===============================

# Add all targets to the build-tree export set
export(TARGETS albers albers-write albers-read
  FILE "${PROJECT_BINARY_DIR}/albersCoreTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE alberscore)

# Create the albersConfig.cmake and albersConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(alberscoreConfig.cmake.in
  "${PROJECT_BINARY_DIR}/alberscoreConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${ALBERSCORE_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(alberscoreConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/alberscoreConfig.cmake" @ONLY)
# ... for both
configure_file(alberscoreConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/alberscoreConfigVersion.cmake" @ONLY)

# Install the alberscoreConfig.cmake and alberscoreConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/alberscoreConfig.cmake"
  "${PROJECT_BINARY_DIR}/alberscoreConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT alberscoreTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)

message(${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY})
message(${INSTALL_CMAKE_DIR})
