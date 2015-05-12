include_directories(
        ${CMAKE_SOURCE_DIR}/datamodel
)

add_executable(albers-read-adapter readAdapter.cc)

include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES "*.cc" "*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

target_link_libraries(albers-read-adapter datamodel albers)

install(TARGETS albers-read-adapter
  # IMPORTANT: Add the write executable to the "export-set"
  EXPORT alberscoreTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)

