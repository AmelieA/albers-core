include_directories(
        ${CMAKE_SOURCE_DIR}/datamodel
)

message(STATUS "include_directories = ${${CMAKE_SOURCE_DIR}/datamodel}")

add_executable(albers-read-adapter readAdapter.cc)

target_link_libraries(albers-read-adapter datamodel albers)

install(TARGETS albers-read-adapter
  # IMPORTANT: Add the write executable to the "export-set"
  EXPORT alberscoreTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)

