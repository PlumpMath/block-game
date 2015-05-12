function(add_sources)
  foreach(SOURCE ${ARGN})
    list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}.cpp)
  endforeach()
  set_property(GLOBAL APPEND PROPERTY SOURCES_PROPERTY ${SOURCES})
endfunction()

function(add_strings)
  foreach(STRING_FILE ${ARGN})
    file(RELATIVE_PATH STRING_PATH ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${STRING_FILE})
    list(APPEND STRING_PATHS ${STRING_PATH})
  endforeach()
  set_property(GLOBAL APPEND PROPERTY STRING_PATHS_PROPERTY ${STRING_PATHS})
endfunction()

add_sources(
  main
)

add_subdirectory(game)
add_subdirectory(general)
add_subdirectory(opengl)
add_subdirectory(shader)
