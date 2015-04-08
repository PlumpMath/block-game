cmake_minimum_required(VERSION 2.8.9)
project("Block Game")
set(LIBRARY_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(GLFW_NAME         3.1.1)
set(GLFW_URL          https://github.com/glfw/glfw/archive/${GLFW_NAME}.tar.gz)
set(GLFW_DIRECTORY    ${LIBRARY_DIRECTORY}/glfw)
set(GLFW_TGZ          glfw.tgz)
set(GLFW_TGZ_ABSOLUTE ${GLFW_DIRECTORY}/${GLFW_TGZ})
set(GLFW_SOURCE       ${GLFW_DIRECTORY}/glfw-${GLFW_NAME})
set(GLFW_CMAKE_LISTS  ${GLFW_SOURCE}/CMakeLists.txt)
set(GLFW_INCLUDE      ${GLFW_SOURCE}/include)
set(GLFW_BINARY       ${GLFW_DIRECTORY}/bin)

if(NOT EXISTS ${GLFW_CMAKE_LISTS})

  message(STATUS "Downloading ${GLFW_URL}")
  file(DOWNLOAD ${GLFW_URL} ${GLFW_TGZ_ABSOLUTE})

  message(STATUS "Opening ${GLFW_TGZ}")
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${GLFW_TGZ}
    WORKING_DIRECTORY ${GLFW_DIRECTORY}
  )

endif()

file(APPEND ${GLFW_CMAKE_LISTS})
add_subdirectory(${GLFW_SOURCE} ${GLFW_BINARY})
include_directories(${GLFW_INCLUDE})

set(GLAD_NAME         c)
set(GLAD_URL          https://github.com/Dav1dde/glad/archive/${GLAD_NAME}.tar.gz)
set(GLAD_DIRECTORY    ${LIBRARY_DIRECTORY}/glad)
set(GLAD_TGZ          glad.tgz)
set(GLAD_TGZ_ABSOLUTE ${GLAD_DIRECTORY}/${GLAD_TGZ})
set(GLAD_SOURCE       ${GLAD_DIRECTORY}/glad-${GLAD_NAME})
set(GLAD_CMAKE_LISTS  ${GLAD_SOURCE}/CMakeLists.txt)
set(GLAD_INCLUDE      ${GLAD_SOURCE}/include)
set(GLAD_BINARY       ${GLAD_DIRECTORY}/bin)

if(NOT EXISTS ${GLAD_CMAKE_LISTS})

  message(STATUS "Downloading ${GLAD_URL}")
  file(DOWNLOAD ${GLAD_URL} ${GLAD_TGZ_ABSOLUTE})

  message(STATUS "Opening ${GLAD_TGZ}")
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${GLAD_TGZ}
    WORKING_DIRECTORY ${GLAD_DIRECTORY}
  )

endif()

file(APPEND ${GLAD_CMAKE_LISTS})
add_subdirectory(${GLAD_SOURCE} ${GLAD_BINARY})
include_directories(${GLAD_INCLUDE})

set_property(GLOBAL APPEND PROPERTY SOURCE_PROPERTY
  ${GLAD_SOURCE}/src/glad.c
  ${GLAD_INCLUDE}/glad/glad.h
  ${GLAD_INCLUDE}/KHR/khrplatform.h
)

add_subdirectory(src)
include_directories(src)

get_property(SOURCE GLOBAL PROPERTY SOURCE_PROPERTY)
add_executable(block_game ${SOURCE})
target_link_libraries(block_game glfw ${GLFW_LIBRARIES})