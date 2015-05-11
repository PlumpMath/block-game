function(add_sources)
  foreach(SOURCE ${ARGN})
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}.cpp")
  endforeach()
  set_property(GLOBAL APPEND PROPERTY SOURCES_PROPERTY ${SOURCES})
endfunction()

add_sources(
  main
)

add_subdirectory(game)
add_subdirectory(general)
add_subdirectory(opengl)
add_subdirectory(shader)
