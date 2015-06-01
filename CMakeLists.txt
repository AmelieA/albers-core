cmake_minimum_required(VERSION 2.8)

# Name of the project (will be the name of the plugin)
project (addon)


# Essential include files to build a node addon,
# you should add this line in every CMake.js based project.
include_directories(${CMAKE_JS_INC})

# Declare the location of the source files
file(GLOB SOURCE_FILES "src/*.cc")

# build dependency
# set up include-directories
include_directories(
  "${PROJECT_SOURCE_DIR}/deps/datamodel"
  )
add_subdirectory (deps)

#--------------Part of deps/CMakeLists.txt--------------

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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -DDROP_CGAL ${CPP11FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-variable -Wno-unused-parameter -Wl,-rpath,${ROOTSYS}'/lib/' -L/home/amelie/Desktop/root/lib/ -lCore")


set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/deps/cmake)
find_package(ROOT)

include_directories(
  "${PROJECT_SOURCE_DIR}/deps"
  "${PROJECT_BINARY_DIR}/deps"
  "${ROOT_INCLUDE_DIR}"
  )

# The interesting stuff goes here
# ===============================

# Add all targets to the build-tree export set
export(TARGETS albers albers-write albers-read
  FILE "${PROJECT_BINARY_DIR}/deps/albersCoreTargets.cmake")


# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE alberscore)

# Create the albersConfig.cmake and albersConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(deps/alberscoreConfig.cmake.in
  "${PROJECT_BINARY_DIR}/alberscoreConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${ALBERSCORE_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(deps/alberscoreConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/alberscoreConfig.cmake" @ONLY)
# ... for both
configure_file(deps/alberscoreConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/deps/alberscoreConfigVersion.cmake" @ONLY)

# Install the alberscoreConfig.cmake and alberscoreConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/deps/alberscoreConfig.cmake"
  "${PROJECT_BINARY_DIR}/deps/alberscoreConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT alberscoreTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)

message(${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY})
message(${INSTALL_CMAKE_DIR})

#-------------- END Part of deps/CMakeLists.txt--------------


# This line will tell CMake that we're building a shared library
# from the above source files
# named after the project's name
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# This line will give our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Essential library files to link to a node addon,
# you should add this line in every CMake.js based project.
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

message("ROOTSYS")
message(${ROOTSYS})