set_property(GLOBAL APPEND PROPERTY SOURCE_PROPERTY
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_subdirectory(game)
add_subdirectory(general)
add_subdirectory(opengl)
add_subdirectory(shader)
